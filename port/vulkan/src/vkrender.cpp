// This file is distributed under a BSD license. See LICENSE.txt for details.
//
// Vulkan renderer of the Linux port (see vkrender.hpp).
//
// Vulkan 1.3: dynamic rendering, extended dynamic state (cull mode, depth and
// stencil state, topology), push descriptors. Pipelines are keyed by
// shaders, vertex format, blend state and colour mask. The engine draws into
// an off-screen back buffer (B8G8R8A8, the render resolution); present
// blits it to the swapchain image, scaled to the window. All images stay in
// VK_IMAGE_LAYOUT_GENERAL; a global barrier separates rendering passes,
// copies and uploads.
//
// The shaders are the game's precompiled SPIR-V (shaders.inc, made by
// tools/shaderpack.py from port/src/shaders). The viewport is flipped
// (negative height, the engine's y points up) and shifted by half a pixel
// (the engine's pixel centres are at integer coordinates).

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "vkrender.hpp"
#include "shaders.inc"

/****************************************************************************/
/***   Function pointers                                                   ***/
/****************************************************************************/

#define VKR_INSTANCE_FUNCS(X) \
  X(vkEnumeratePhysicalDevices) X(vkGetPhysicalDeviceProperties) \
  X(vkGetPhysicalDeviceQueueFamilyProperties) X(vkGetPhysicalDeviceMemoryProperties) \
  X(vkGetPhysicalDeviceFormatProperties) X(vkGetPhysicalDeviceSurfaceSupportKHR) \
  X(vkGetPhysicalDeviceSurfaceCapabilitiesKHR) X(vkGetPhysicalDeviceSurfaceFormatsKHR) \
  X(vkGetPhysicalDeviceSurfacePresentModesKHR) X(vkEnumerateDeviceExtensionProperties) \
  X(vkCreateDevice) X(vkGetDeviceProcAddr)

#define VKR_DEVICE_FUNCS(X) \
  X(vkGetDeviceQueue) X(vkDeviceWaitIdle) X(vkQueueSubmit) X(vkQueuePresentKHR) \
  X(vkCreateSwapchainKHR) X(vkDestroySwapchainKHR) X(vkGetSwapchainImagesKHR) X(vkAcquireNextImageKHR) \
  X(vkCreateCommandPool) X(vkAllocateCommandBuffers) X(vkBeginCommandBuffer) X(vkEndCommandBuffer) \
  X(vkResetCommandBuffer) X(vkCreateFence) X(vkWaitForFences) X(vkResetFences) X(vkCreateSemaphore) \
  X(vkCreateImage) X(vkDestroyImage) X(vkGetImageMemoryRequirements) X(vkAllocateMemory) X(vkFreeMemory) \
  X(vkBindImageMemory) X(vkCreateImageView) X(vkDestroyImageView) X(vkCreateBuffer) X(vkDestroyBuffer) \
  X(vkGetBufferMemoryRequirements) X(vkBindBufferMemory) X(vkMapMemory) X(vkCreateSampler) \
  X(vkCreateShaderModule) X(vkDestroyShaderModule) X(vkCreateDescriptorSetLayout) X(vkCreatePipelineLayout) \
  X(vkCreateGraphicsPipelines) X(vkCmdBeginRendering) X(vkCmdEndRendering) X(vkCmdBindPipeline) \
  X(vkCmdSetViewport) X(vkCmdSetScissor) X(vkCmdSetCullMode) X(vkCmdSetFrontFace) X(vkCmdSetPrimitiveTopology) \
  X(vkCmdSetDepthTestEnable) X(vkCmdSetDepthWriteEnable) X(vkCmdSetDepthCompareOp) X(vkCmdSetStencilTestEnable) \
  X(vkCmdSetStencilOp) X(vkCmdSetStencilCompareMask) X(vkCmdSetStencilWriteMask) X(vkCmdSetStencilReference) \
  X(vkCmdBindVertexBuffers) X(vkCmdBindIndexBuffer) X(vkCmdDraw) X(vkCmdDrawIndexed) \
  X(vkCmdPushDescriptorSetKHR) X(vkCmdPipelineBarrier) X(vkCmdCopyBufferToImage) X(vkCmdCopyImageToBuffer) \
  X(vkCmdBlitImage) X(vkCmdClearAttachments) X(vkCmdClearColorImage) X(vkCmdSetDepthBias) X(vkCmdSetDepthBiasEnable)

#define VKR_DECLARE(f) static PFN_##f f;
#define VKR_SLOT(f) (void **)&f,
#define VKR_NAME(f) #f "\0"
static PFN_vkCreateInstance vkCreateInstance;
VKR_INSTANCE_FUNCS(VKR_DECLARE)
VKR_DEVICE_FUNCS(VKR_DECLARE)
static void **const InstanceSlots[] = { VKR_INSTANCE_FUNCS(VKR_SLOT) 0 };
static const char InstanceNames[] = VKR_INSTANCE_FUNCS(VKR_NAME);
static void **const DeviceSlots[] = { VKR_DEVICE_FUNCS(VKR_SLOT) 0 };
static const char DeviceNames[] = VKR_DEVICE_FUNCS(VKR_NAME);

/****************************************************************************/
/***   Objects and state                                                   ***/
/****************************************************************************/

#define VKR_FRAMES      2
#define VKR_UBOSIZE     (16<<20)          // constant ring per frame
#define VKR_STAGINGSIZE (32<<20)          // texture upload ring
#define VKR_MAXFORMATS  16
#define VKR_MAXPIPES    1024
#define VKR_MAXSAMPLERS 32
#define VKR_MAXDELETE   4096
#define VKR_LOCATIONS   10                // vertex shader input locations

struct VkrTexture
{
  VkImage Image;
  VkDeviceMemory Mem;
  VkImageView View;
  int Type,Format,XS,YS,ZS,Levels;
  int Dead;                               // destroyed while bound: freed once unbound
};

struct VkrBuffer
{
  VkBuffer Buf[VKR_FRAMES];
  VkDeviceMemory Mem[VKR_FRAMES];
  uint8_t *Data[VKR_FRAMES];
  uint64_t LastUse[VKR_FRAMES];           // serial of the last submission reading it
  int Size,Dynamic;
};

struct VkrPipeKey                         // memcmp'd: no padding holes
{
  uint32_t VS,PS,Format,Topology,Blend,ColorMask,Depth;
};

struct VkrPipe { VkrPipeKey Key; VkPipeline Pipe; };
struct VkrSampler { uint32_t Key; VkSampler Sampler; };
struct VkrDelete { int Kind; void *Ptr; };

struct VkrFrame
{
  VkCommandBuffer Cmd;
  VkFence Fence;
  VkSemaphore Acquire;
  VkrBuffer *Ubo;
  int UboUsed;
  VkrDelete Delete[VKR_MAXDELETE];
  int NumDelete;
  uint64_t Submitted;                     // serial of its last submission
};

static struct VkrState
{
  VkInstance Instance;
  VkPhysicalDevice Phys;
  VkDevice Dev;
  VkQueue Queue;
  uint32_t QueueFamily;
  VkSurfaceKHR Surface;
  VkPhysicalDeviceMemoryProperties MemProps;
  VkDeviceSize UboAlign;
  SDL_Window *Window;
  int VSync;

  VkSwapchainKHR Swapchain;
  VkFormat SwapFormat;
  VkExtent2D SwapExtent;
  uint32_t SwapCount;
  VkImage SwapImages[8];
  VkSemaphore SwapDone[8];

  VkCommandPool Pool;
  VkrFrame Frames[VKR_FRAMES];
  int Frame;
  uint64_t Serial;                        // serial of the commands being recorded
  uint64_t Completed;                     // all submissions up to this one are done
  VkCommandBuffer Cmd;                    // = Frames[Frame].Cmd

  VkrTexture BackBuffer;
  VkFormat DepthFormat;
  VkImage DepthImage;
  VkDeviceMemory DepthMem;
  VkImageView DepthView;
  int DepthXS,DepthYS;

  VkrBuffer *Staging;
  int StagingUsed;
  VkrBuffer *Readback;
  VkrBuffer *Zero;                        // source of missing vertex inputs

  VkDescriptorSetLayout SetLayout;
  VkPipelineLayout Layout;
  VkrTexture *Dummy[3];
  VkShaderModule Shaders[SHADER_COUNT];

  // render pass state
  VkrTexture *Target;                     // 0 = back buffer
  int Rendering,RenderDepth;
  int VPX,VPY,VPW,VPH;
  int ScX0,ScY0,ScX1,ScY1;

  // draw state
  uint32_t States[VKR_STATES];
  int VS,PS;
  VkrTexture *Tex[4];
  float VSConst[256*4];
  float PSConst[8*4];
  int Format;
  VkrBuffer *VB,*IB;
  int VBOffset,Index32;

  // vertex formats
  int NumFormats;
  int Stride[VKR_MAXFORMATS];
  VkVertexInputAttributeDescription Attr[VKR_MAXFORMATS][VKR_LOCATIONS];
  int NumAttr[VKR_MAXFORMATS];

  VkrPipe Pipes[VKR_MAXPIPES];
  int NumPipes;
  VkPipeline BoundPipe;
  VkrSampler Samplers[VKR_MAXSAMPLERS];
  int NumSamplers;

  // dynamic state shadow (re-sent after each vkCmdBeginRendering)
  int DynValid;
} VK;

#ifdef KK_SMALL                 // size build: no details
static void __attribute__((noinline,noreturn)) Fatal(const char *msg,int code=0)
{
  fprintf(stderr,"vulkan: %s\n",msg);
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"kkrieger",msg,VK.Window);
  _exit(1);
}
static void __attribute__((noinline)) Check(VkResult r) { if(r<0) Fatal("Vulkan error"); }
#define VKCHECK(x) Check(x)
#else
static void Fatal(const char *msg,int code=0)
{
  char buf[256];
  snprintf(buf,sizeof(buf),"%s (%d)",msg,code);
  fprintf(stderr,"vulkan: %s\n",buf);
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"kkrieger",buf,VK.Window);
  _exit(1);
}
#define VKCHECK(x) { VkResult r_ = (x); if(r_<0) Fatal(#x,r_); }
#endif

typedef PFN_vkVoidFunction (VKAPI_PTR *GetProc)(void *,const char *);

static void LoadFuncs(GetProc get,void *obj,void **const *slot,const char *name)
{
  for(;*slot;slot++)
  {
    if(!(**slot = (void *) get(obj,name)))
      Fatal(name);
    name += strlen(name)+1;
  }
}

static void Flush();
static void RunDeletes(VkrFrame &f);
static void WaitFrame(VkrFrame &f);

/****************************************************************************/
/***   Memory, buffers, images                                             ***/
/****************************************************************************/

static VkDeviceMemory Allocate(VkMemoryRequirements &req,VkMemoryPropertyFlags want)
{
  for(int pass=0;pass<2;pass++)
  {
    for(uint32_t i=0;i<VK.MemProps.memoryTypeCount;i++)
    {
      VkMemoryPropertyFlags f = VK.MemProps.memoryTypes[i].propertyFlags;
      if((req.memoryTypeBits & (1u<<i)) && (f & want)==want)
      {
        VkMemoryAllocateInfo ai = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
        ai.allocationSize = req.size;
        ai.memoryTypeIndex = i;
        VkDeviceMemory mem;
        if(vkAllocateMemory(VK.Dev,&ai,0,&mem)==VK_SUCCESS)
          return mem;
      }
    }
    want &= ~VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;   // second try: any host visible type
  }
  Fatal("out of video memory");
  return 0;
}

VkrBuffer *vkrCreateBuffer(int size,int dynamic)
{
  VkrBuffer *b = (VkrBuffer *) calloc(1,sizeof(VkrBuffer));
  b->Size = size;
  b->Dynamic = dynamic;
  for(int i=0;i<(dynamic ? VKR_FRAMES : 1);i++)
  {
    VkBufferCreateInfo ci = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
    ci.size = size;
    ci.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT|VK_BUFFER_USAGE_INDEX_BUFFER_BIT|VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT|
               VK_BUFFER_USAGE_TRANSFER_SRC_BIT|VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    VKCHECK(vkCreateBuffer(VK.Dev,&ci,0,&b->Buf[i]));
    VkMemoryRequirements req;
    vkGetBufferMemoryRequirements(VK.Dev,b->Buf[i],&req);
    b->Mem[i] = Allocate(req,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    VKCHECK(vkBindBufferMemory(VK.Dev,b->Buf[i],b->Mem[i],0));
    VKCHECK(vkMapMemory(VK.Dev,b->Mem[i],0,VK_WHOLE_SIZE,0,(void **)&b->Data[i]));
  }
  return b;
}

static int Slot(VkrBuffer *b) { return b->Dynamic ? VK.Frame : 0; }

void *vkrBufferData(VkrBuffer *b) { return b->Data[Slot(b)]; }

void vkrBufferSync(VkrBuffer *b)
{
  uint64_t use = b->LastUse[Slot(b)];
  if(use<=VK.Completed) return;
  if(use==VK.Serial)                      // read by the commands being recorded
    Flush();
  else
    for(int i=0;i<VKR_FRAMES;i++)
      if(i!=VK.Frame && VK.Frames[i].Submitted>=use)
        WaitFrame(VK.Frames[i]);
}

static void Defer(int kind,void *ptr)
{
  VkrFrame &f = VK.Frames[VK.Frame];
  if(f.NumDelete==VKR_MAXDELETE)            // everything recorded so far done -> free all
  {
    Flush();
    for(int i=0;i<VKR_FRAMES;i++)
      RunDeletes(VK.Frames[i]);
  }
  f.Delete[f.NumDelete].Kind = kind;
  f.Delete[f.NumDelete].Ptr = ptr;
  f.NumDelete++;
}

static void FreeBuffer(VkrBuffer *b)
{
  for(int i=0;i<(b->Dynamic ? VKR_FRAMES : 1);i++)
  {
    vkDestroyBuffer(VK.Dev,b->Buf[i],0);
    vkFreeMemory(VK.Dev,b->Mem[i],0);
  }
  free(b);
}

static void FreeTexture(VkrTexture *t)
{
  vkDestroyImageView(VK.Dev,t->View,0);
  vkDestroyImage(VK.Dev,t->Image,0);
  vkFreeMemory(VK.Dev,t->Mem,0);
  free(t);
}

void vkrDestroyBuffer(VkrBuffer *b) { if(b) Defer(0,b); }
static int Bound(VkrTexture *t)
{
  return t==VK.Target || t==VK.Tex[0] || t==VK.Tex[1] || t==VK.Tex[2] || t==VK.Tex[3];
}

static void Unbound(VkrTexture *t)
{
  if(t && t->Dead && !Bound(t))
    Defer(1,t);
}

void vkrDestroyTexture(VkrTexture *t)
{
  if(!t) return;
  t->Dead = 1;
  Unbound(t);
}

static void Barrier()                     // everything before -> everything after
{
  VkMemoryBarrier mb = { VK_STRUCTURE_TYPE_MEMORY_BARRIER };
  mb.srcAccessMask = VK_ACCESS_MEMORY_WRITE_BIT;
  mb.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT|VK_ACCESS_MEMORY_WRITE_BIT;
  vkCmdPipelineBarrier(VK.Cmd,VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,0,1,&mb,0,0,0,0);
}

static void EndRendering()
{
  if(VK.Rendering)
  {
    vkCmdEndRendering(VK.Cmd);
    VK.Rendering = 0;
    Barrier();
  }
}

static void ImageToGeneral(VkImage image,VkImageAspectFlags aspect,int levels,int layers)
{
  VkImageMemoryBarrier ib = { VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
  ib.srcAccessMask = 0;
  ib.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT|VK_ACCESS_MEMORY_WRITE_BIT;
  ib.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  ib.newLayout = VK_IMAGE_LAYOUT_GENERAL;
  ib.srcQueueFamilyIndex = ib.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  ib.image = image;
  ib.subresourceRange.aspectMask = aspect;
  ib.subresourceRange.levelCount = levels;
  ib.subresourceRange.layerCount = layers;
  vkCmdPipelineBarrier(VK.Cmd,VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,0,0,0,0,0,1,&ib);
}

static void CreateImage(VkrTexture *t,VkImageUsageFlags usage)
{
  VkImageCreateInfo ci = { VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO };
  ci.imageType = t->Type==VKR_TEX3D ? VK_IMAGE_TYPE_3D : VK_IMAGE_TYPE_2D;
  ci.format = t->Format==VKR_RGBA8S ? VK_FORMAT_R8G8B8A8_SNORM : VK_FORMAT_B8G8R8A8_UNORM;
  ci.extent.width = t->XS;
  ci.extent.height = t->YS;
  ci.extent.depth = t->ZS;
  ci.mipLevels = t->Levels;
  ci.arrayLayers = t->Type==VKR_TEXCUBE ? 6 : 1;
  ci.samples = VK_SAMPLE_COUNT_1_BIT;
  ci.tiling = VK_IMAGE_TILING_OPTIMAL;
  ci.usage = usage;
  ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  if(t->Type==VKR_TEXCUBE) ci.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
  VKCHECK(vkCreateImage(VK.Dev,&ci,0,&t->Image));
  VkMemoryRequirements req;
  vkGetImageMemoryRequirements(VK.Dev,t->Image,&req);
  t->Mem = Allocate(req,VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
  VKCHECK(vkBindImageMemory(VK.Dev,t->Image,t->Mem,0));

  VkImageViewCreateInfo vi = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
  vi.image = t->Image;
  vi.viewType = t->Type==VKR_TEX3D ? VK_IMAGE_VIEW_TYPE_3D : t->Type==VKR_TEXCUBE ? VK_IMAGE_VIEW_TYPE_CUBE : VK_IMAGE_VIEW_TYPE_2D;
  vi.format = ci.format;
  vi.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  vi.subresourceRange.levelCount = t->Levels;
  vi.subresourceRange.layerCount = ci.arrayLayers;
  VKCHECK(vkCreateImageView(VK.Dev,&vi,0,&t->View));

  EndRendering();
  ImageToGeneral(t->Image,VK_IMAGE_ASPECT_COLOR_BIT,t->Levels,ci.arrayLayers);
  VkClearColorValue zero = {};                  // new images read as zero
  VkImageSubresourceRange range = { VK_IMAGE_ASPECT_COLOR_BIT,0,(uint32_t)t->Levels,0,ci.arrayLayers };
  vkCmdClearColorImage(VK.Cmd,t->Image,VK_IMAGE_LAYOUT_GENERAL,&zero,1,&range);
  Barrier();
}

VkrTexture *vkrCreateTexture(int type,int format,int xs,int ys,int zs,int levels)
{
  VkrTexture *t = (VkrTexture *) calloc(1,sizeof(VkrTexture));
  t->Type = type;
  t->Format = format;
  t->XS = xs; t->YS = ys; t->ZS = zs>0 ? zs : 1;
  t->Levels = levels>0 ? levels : 1;
  VkImageUsageFlags usage = VK_IMAGE_USAGE_SAMPLED_BIT|VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
  if(levels==0) usage |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  CreateImage(t,usage);
  return t;
}

/****************************************************************************/
/***   Frames                                                              ***/
/****************************************************************************/

static void BeginCommands()
{
  VkCommandBufferBeginInfo bi = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
  bi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  VKCHECK(vkResetCommandBuffer(VK.Cmd,0));
  VKCHECK(vkBeginCommandBuffer(VK.Cmd,&bi));
  VK.BoundPipe = 0;
}

static void RunDeletes(VkrFrame &f)
{
  for(int i=0;i<f.NumDelete;i++)
  {
    if(f.Delete[i].Kind==0) FreeBuffer((VkrBuffer *)f.Delete[i].Ptr);
    else FreeTexture((VkrTexture *)f.Delete[i].Ptr);
  }
  f.NumDelete = 0;
}

static void Submit(VkSubmitInfo &si)
{
  VkrFrame &f = VK.Frames[VK.Frame];
  VKCHECK(vkQueueSubmit(VK.Queue,1,&si,f.Fence));
  f.Submitted = VK.Serial++;
}

static void WaitFrame(VkrFrame &f)
{
  VKCHECK(vkWaitForFences(VK.Dev,1,&f.Fence,VK_TRUE,~0ull));
  if(f.Submitted>VK.Completed) VK.Completed = f.Submitted;
}

static void BeginFrame()
{
  VkrFrame &f = VK.Frames[VK.Frame];
  WaitFrame(f);
  VKCHECK(vkResetFences(VK.Dev,1,&f.Fence));
  RunDeletes(f);
  f.UboUsed = 0;
  VK.Cmd = f.Cmd;
  BeginCommands();
}

// submit what was recorded so far and wait for it (uploads, read backs)
static void Flush()
{
  EndRendering();
  VkrFrame &f = VK.Frames[VK.Frame];
  VKCHECK(vkEndCommandBuffer(VK.Cmd));
  VkSubmitInfo si = { VK_STRUCTURE_TYPE_SUBMIT_INFO };
  si.commandBufferCount = 1;
  si.pCommandBuffers = &VK.Cmd;
  Submit(si);
  WaitFrame(f);
  VKCHECK(vkResetFences(VK.Dev,1,&f.Fence));
  f.UboUsed = 0;
  VK.StagingUsed = 0;
  BeginCommands();
}

/****************************************************************************/
/***   Swapchain                                                           ***/
/****************************************************************************/

static void CreateSwapchain()
{
  VkSurfaceCapabilitiesKHR caps;
  VKCHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VK.Phys,VK.Surface,&caps));
  VkExtent2D ext = caps.currentExtent;
  if(ext.width==0xffffffff)
  {
    int w,h;
    SDL_GetWindowSizeInPixels(VK.Window,&w,&h);
    ext.width = w; ext.height = h;
  }
  if(ext.width==0 || ext.height==0) return;             // minimised

  uint32_t n = 0;
  VkSurfaceFormatKHR formats[64];
  vkGetPhysicalDeviceSurfaceFormatsKHR(VK.Phys,VK.Surface,&n,0);
  if(n>64) n = 64;
  vkGetPhysicalDeviceSurfaceFormatsKHR(VK.Phys,VK.Surface,&n,formats);
  VkSurfaceFormatKHR fmt = formats[0];
  for(uint32_t i=0;i<n;i++)
    if(formats[i].format==VK_FORMAT_B8G8R8A8_UNORM || formats[i].format==VK_FORMAT_R8G8B8A8_UNORM)
      { fmt = formats[i]; break; }

  VkPresentModeKHR modes[16],mode = VK_PRESENT_MODE_FIFO_KHR;
  n = 16;
  vkGetPhysicalDeviceSurfacePresentModesKHR(VK.Phys,VK.Surface,&n,modes);
  if(!VK.VSync)
    for(uint32_t i=0;i<n;i++)
      if(modes[i]==VK_PRESENT_MODE_IMMEDIATE_KHR || (modes[i]==VK_PRESENT_MODE_MAILBOX_KHR && mode==VK_PRESENT_MODE_FIFO_KHR))
        mode = modes[i];

  uint32_t count = caps.minImageCount+1;
  if(caps.maxImageCount && count>caps.maxImageCount) count = caps.maxImageCount;

  VkSwapchainCreateInfoKHR ci = { VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR };
  ci.surface = VK.Surface;
  ci.minImageCount = count;
  ci.imageFormat = fmt.format;
  ci.imageColorSpace = fmt.colorSpace;
  ci.imageExtent = ext;
  ci.imageArrayLayers = 1;
  ci.imageUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;
  ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  ci.preTransform = caps.currentTransform;
  ci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  if(!(caps.supportedCompositeAlpha & ci.compositeAlpha))
    ci.compositeAlpha = (VkCompositeAlphaFlagBitsKHR)(caps.supportedCompositeAlpha & -caps.supportedCompositeAlpha);
  ci.presentMode = mode;
  ci.clipped = VK_TRUE;
  ci.oldSwapchain = VK.Swapchain;
  VkSwapchainKHR sc;
  VKCHECK(vkCreateSwapchainKHR(VK.Dev,&ci,0,&sc));
  if(VK.Swapchain)
  {
    vkDeviceWaitIdle(VK.Dev);
    vkDestroySwapchainKHR(VK.Dev,VK.Swapchain,0);
  }
  VK.Swapchain = sc;
  VK.SwapFormat = fmt.format;
  VK.SwapExtent = ext;
  VK.SwapCount = 8;
  VKCHECK(vkGetSwapchainImagesKHR(VK.Dev,sc,&VK.SwapCount,VK.SwapImages));
  for(uint32_t i=0;i<VK.SwapCount;i++)
  {
    if(!VK.SwapDone[i])
    {
      VkSemaphoreCreateInfo si = { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
      VKCHECK(vkCreateSemaphore(VK.Dev,&si,0,&VK.SwapDone[i]));
    }
  }
}

static void SwapBarrier(VkImage image,VkImageLayout from,VkImageLayout to,VkAccessFlags src,VkAccessFlags dst)
{
  VkImageMemoryBarrier ib = { VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
  ib.srcAccessMask = src;
  ib.dstAccessMask = dst;
  ib.oldLayout = from;
  ib.newLayout = to;
  ib.srcQueueFamilyIndex = ib.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  ib.image = image;
  ib.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  ib.subresourceRange.levelCount = 1;
  ib.subresourceRange.layerCount = 1;
  vkCmdPipelineBarrier(VK.Cmd,VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,0,0,0,0,0,1,&ib);
}

void vkrPresent()
{
  EndRendering();
  VkrFrame &f = VK.Frames[VK.Frame];

  uint32_t index = ~0u;
  if(VK.Swapchain)
  {
    VkResult r = vkAcquireNextImageKHR(VK.Dev,VK.Swapchain,~0ull,f.Acquire,0,&index);
    if(r==VK_ERROR_OUT_OF_DATE_KHR) index = ~0u;
    else if(r<0) Fatal("vkAcquireNextImageKHR",r);
  }

  if(index!=~0u)
  {
    VkImage img = VK.SwapImages[index];
    SwapBarrier(img,VK_IMAGE_LAYOUT_UNDEFINED,VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,0,VK_ACCESS_TRANSFER_WRITE_BIT);
    VkImageBlit blit = {};
    blit.srcSubresource.aspectMask = blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    blit.srcSubresource.layerCount = blit.dstSubresource.layerCount = 1;
    blit.srcOffsets[1].x = VK.BackBuffer.XS; blit.srcOffsets[1].y = VK.BackBuffer.YS; blit.srcOffsets[1].z = 1;
    blit.dstOffsets[1].x = VK.SwapExtent.width; blit.dstOffsets[1].y = VK.SwapExtent.height; blit.dstOffsets[1].z = 1;
    vkCmdBlitImage(VK.Cmd,VK.BackBuffer.Image,VK_IMAGE_LAYOUT_GENERAL,img,VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,1,&blit,VK_FILTER_LINEAR);
    SwapBarrier(img,VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,VK_ACCESS_TRANSFER_WRITE_BIT,0);
  }
  Barrier();

  VKCHECK(vkEndCommandBuffer(VK.Cmd));
  VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
  VkSubmitInfo si = { VK_STRUCTURE_TYPE_SUBMIT_INFO };
  si.commandBufferCount = 1;
  si.pCommandBuffers = &VK.Cmd;
  if(index!=~0u)
  {
    si.waitSemaphoreCount = 1;
    si.pWaitSemaphores = &f.Acquire;
    si.pWaitDstStageMask = &waitStage;
    si.signalSemaphoreCount = 1;
    si.pSignalSemaphores = &VK.SwapDone[index];
  }
  Submit(si);

  int recreate = (index==~0u);
  if(index!=~0u)
  {
    VkPresentInfoKHR pi = { VK_STRUCTURE_TYPE_PRESENT_INFO_KHR };
    pi.waitSemaphoreCount = 1;
    pi.pWaitSemaphores = &VK.SwapDone[index];
    pi.swapchainCount = 1;
    pi.pSwapchains = &VK.Swapchain;
    pi.pImageIndices = &index;
    VkResult r = vkQueuePresentKHR(VK.Queue,&pi);
    if(r==VK_ERROR_OUT_OF_DATE_KHR || r==VK_SUBOPTIMAL_KHR) recreate = 1;
    else if(r<0) Fatal("vkQueuePresentKHR",r);
  }
  if(recreate)
  {
    vkDeviceWaitIdle(VK.Dev);
    CreateSwapchain();
  }

  VK.Frame = (VK.Frame+1) % VKR_FRAMES;
  BeginFrame();
}

/****************************************************************************/
/***   Initialisation                                                      ***/
/****************************************************************************/

static void InitStates()
{
  static const uint8_t defaults[][2] =          // the rest starts as 0
  {
    { VKR_ZWRITE,1 }, { VKR_ZFUNC,VK_COMPARE_OP_LESS_OR_EQUAL }, { VKR_CULL,VK_CULL_MODE_BACK_BIT },
    { VKR_COLORMASK,15 }, { VKR_BLENDSRC,VK_BLEND_FACTOR_ONE }, { VKR_STENCILFUNC,VK_COMPARE_OP_ALWAYS },
    { VKR_BACKFUNC,VK_COMPARE_OP_ALWAYS }, { VKR_STENCILMASK,255 }, { VKR_STENCILWRITEMASK,255 },
  };
  for(unsigned i=0;i<sizeof(defaults)/sizeof(defaults[0]);i++)
    VK.States[defaults[i][0]] = defaults[i][1];
}

int vkrInit(SDL_Window *window,int xs,int ys,int vsync)
{
  VK.Window = window;
  VK.VSync = vsync;

  PFN_vkGetInstanceProcAddr gipa = (PFN_vkGetInstanceProcAddr) SDL_Vulkan_GetVkGetInstanceProcAddr();
  if(!gipa) Fatal("no Vulkan loader");
  vkCreateInstance = (PFN_vkCreateInstance) gipa(0,"vkCreateInstance");

  // instance
  Uint32 extCount = 0;
  const char *const *ext = SDL_Vulkan_GetInstanceExtensions(&extCount);
  VkApplicationInfo app = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
  app.pApplicationName = ".kkrieger";
  app.apiVersion = VK_API_VERSION_1_3;
  VkInstanceCreateInfo ici = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
  ici.pApplicationInfo = &app;
  ici.enabledExtensionCount = extCount;
  ici.ppEnabledExtensionNames = ext;
  VKCHECK(vkCreateInstance(&ici,0,&VK.Instance));
  LoadFuncs((GetProc)gipa,VK.Instance,InstanceSlots,InstanceNames);
  if(!SDL_Vulkan_CreateSurface(window,VK.Instance,0,&VK.Surface))
    Fatal(SDL_GetError());

  // physical device: Vulkan 1.3, graphics+present queue, push descriptors;
  // discrete GPUs first (KK_GPU=n picks one by index)
  VkPhysicalDevice devs[16];
  uint32_t n = 16;
  VKCHECK(vkEnumeratePhysicalDevices(VK.Instance,&n,devs));
  int best = -1,bestScore = -1;
  const char *gpu = getenv("KK_GPU");
  for(uint32_t d=0;d<n;d++)
  {
    VkPhysicalDeviceProperties p;
    vkGetPhysicalDeviceProperties(devs[d],&p);
    if(p.apiVersion<VK_API_VERSION_1_3) continue;
    VkExtensionProperties exts[512];
    uint32_t ne = 512;
    vkEnumerateDeviceExtensionProperties(devs[d],0,&ne,exts);
    int push = 0;
    for(uint32_t e=0;e<ne;e++)
      if(!strcmp(exts[e].extensionName,VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME)) push = 1;
    if(!push) continue;
    VkQueueFamilyProperties qf[16];
    uint32_t nq = 16;
    vkGetPhysicalDeviceQueueFamilyProperties(devs[d],&nq,qf);
    for(uint32_t q=0;q<nq;q++)
    {
      VkBool32 present = 0;
      vkGetPhysicalDeviceSurfaceSupportKHR(devs[d],q,VK.Surface,&present);
      if((qf[q].queueFlags & VK_QUEUE_GRAPHICS_BIT) && present)
      {
        int score = p.deviceType==VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ? 2 : 1;
        if(gpu) score = atoi(gpu)==(int)d ? 3 : 0;
        if(score>bestScore) { bestScore = score; best = d; VK.QueueFamily = q; }
        break;
      }
    }
  }
  if(best<0) Fatal("no Vulkan 1.3 GPU with push descriptors");
  VK.Phys = devs[best];
  vkGetPhysicalDeviceMemoryProperties(VK.Phys,&VK.MemProps);
  {
    VkPhysicalDeviceProperties p;
    vkGetPhysicalDeviceProperties(VK.Phys,&p);
    VK.UboAlign = p.limits.minUniformBufferOffsetAlignment;
    if(VK.UboAlign<16) VK.UboAlign = 16;
#ifndef KK_SMALL
    fprintf(stderr,"vulkan: %s (device %d of %d, KK_GPU=n selects)\n",p.deviceName,best,n);
#endif
  }

  // device
  float prio = 1.0f;
  VkDeviceQueueCreateInfo qci = { VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO };
  qci.queueFamilyIndex = VK.QueueFamily;
  qci.queueCount = 1;
  qci.pQueuePriorities = &prio;
  VkPhysicalDeviceVulkan13Features f13 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES };
  f13.dynamicRendering = VK_TRUE;
  const char *dext[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME, VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME };
  VkDeviceCreateInfo dci = { VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };
  dci.pNext = &f13;
  dci.queueCreateInfoCount = 1;
  dci.pQueueCreateInfos = &qci;
  dci.enabledExtensionCount = 2;
  dci.ppEnabledExtensionNames = dext;
  VKCHECK(vkCreateDevice(VK.Phys,&dci,0,&VK.Dev));
  LoadFuncs((GetProc)vkGetDeviceProcAddr,VK.Dev,DeviceSlots,DeviceNames);
  vkGetDeviceQueue(VK.Dev,VK.QueueFamily,0,&VK.Queue);

  // frames
  VkCommandPoolCreateInfo pci = { VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
  pci.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  pci.queueFamilyIndex = VK.QueueFamily;
  VKCHECK(vkCreateCommandPool(VK.Dev,&pci,0,&VK.Pool));
  for(int i=0;i<VKR_FRAMES;i++)
  {
    VkrFrame &f = VK.Frames[i];
    VkCommandBufferAllocateInfo ai = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
    ai.commandPool = VK.Pool;
    ai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    ai.commandBufferCount = 1;
    VKCHECK(vkAllocateCommandBuffers(VK.Dev,&ai,&f.Cmd));
    VkFenceCreateInfo fi = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
    fi.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    VKCHECK(vkCreateFence(VK.Dev,&fi,0,&f.Fence));
    VkSemaphoreCreateInfo si = { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
    VKCHECK(vkCreateSemaphore(VK.Dev,&si,0,&f.Acquire));
    f.Ubo = vkrCreateBuffer(VKR_UBOSIZE,0);
  }
  VK.Frame = 0;
  VK.Serial = 1;
  BeginFrame();
  CreateSwapchain();

  VK.Staging = vkrCreateBuffer(VKR_STAGINGSIZE,0);
  VK.Zero = vkrCreateBuffer(64,0);
  memset(VK.Zero->Data[0],0,64);

  // back buffer + depth/stencil (at least 1024x512 like the 2004 version)
  VK.BackBuffer.Type = VKR_TEX2D;
  VK.BackBuffer.Format = VKR_BGRA8;
  VK.BackBuffer.XS = xs; VK.BackBuffer.YS = ys; VK.BackBuffer.ZS = 1; VK.BackBuffer.Levels = 1;
  CreateImage(&VK.BackBuffer,VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT|VK_IMAGE_USAGE_TRANSFER_SRC_BIT|VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_SAMPLED_BIT);

  VK.DepthFormat = VK_FORMAT_D24_UNORM_S8_UINT;
  VkFormatProperties fp;
  vkGetPhysicalDeviceFormatProperties(VK.Phys,VK.DepthFormat,&fp);
  if(!(fp.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT))
    VK.DepthFormat = VK_FORMAT_D32_SFLOAT_S8_UINT;
  VK.DepthXS = xs>1024 ? xs : 1024;
  VK.DepthYS = ys>512 ? ys : 512;
  {
    VkImageCreateInfo ci = { VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO };
    ci.imageType = VK_IMAGE_TYPE_2D;
    ci.format = VK.DepthFormat;
    ci.extent.width = VK.DepthXS; ci.extent.height = VK.DepthYS; ci.extent.depth = 1;
    ci.mipLevels = ci.arrayLayers = 1;
    ci.samples = VK_SAMPLE_COUNT_1_BIT;
    ci.tiling = VK_IMAGE_TILING_OPTIMAL;
    ci.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    VKCHECK(vkCreateImage(VK.Dev,&ci,0,&VK.DepthImage));
    VkMemoryRequirements req;
    vkGetImageMemoryRequirements(VK.Dev,VK.DepthImage,&req);
    VK.DepthMem = Allocate(req,VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    VKCHECK(vkBindImageMemory(VK.Dev,VK.DepthImage,VK.DepthMem,0));
    VkImageViewCreateInfo vi = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
    vi.image = VK.DepthImage;
    vi.viewType = VK_IMAGE_VIEW_TYPE_2D;
    vi.format = VK.DepthFormat;
    vi.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT|VK_IMAGE_ASPECT_STENCIL_BIT;
    vi.subresourceRange.levelCount = vi.subresourceRange.layerCount = 1;
    VKCHECK(vkCreateImageView(VK.Dev,&vi,0,&VK.DepthView));
    ImageToGeneral(VK.DepthImage,VK_IMAGE_ASPECT_DEPTH_BIT|VK_IMAGE_ASPECT_STENCIL_BIT,1,1);
  }

  // one descriptor set layout for everything: VS + PS constants, 4 samplers
  VkDescriptorSetLayoutBinding b[6] = {};
  for(int i=0;i<6;i++)
  {
    b[i].binding = i;
    b[i].descriptorCount = 1;
    b[i].descriptorType = i<2 ? VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER : VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    b[i].stageFlags = i==0 ? VK_SHADER_STAGE_VERTEX_BIT : VK_SHADER_STAGE_FRAGMENT_BIT;
  }
  VkDescriptorSetLayoutCreateInfo dl = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
  dl.flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR;
  dl.bindingCount = 6;
  dl.pBindings = b;
  VKCHECK(vkCreateDescriptorSetLayout(VK.Dev,&dl,0,&VK.SetLayout));
  VkPipelineLayoutCreateInfo pl = { VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
  pl.setLayoutCount = 1;
  pl.pSetLayouts = &VK.SetLayout;
  VKCHECK(vkCreatePipelineLayout(VK.Dev,&pl,0,&VK.Layout));

  // dummy textures for unbound stages: sample as (0,0,0,1)
  for(int t=0;t<3;t++)
  {
    VK.Dummy[t] = vkrCreateTexture(t,VKR_BGRA8,1,1,1,1);
    for(int face=0;face<(t==VKR_TEXCUBE ? 6 : 1);face++)
    {
      *(uint32_t *)vkrLockTexture(VK.Dummy[t],face,0,0) = 0xff000000;
      vkrUnlockTexture();
    }
  }

  // the game's shaders
  const uint32_t *code = ShaderCode;
  for(int i=0;i<SHADER_COUNT;i++)
  {
    VkShaderModuleCreateInfo ci = { VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
    ci.codeSize = ShaderWords[i]*4;
    ci.pCode = code;
    VKCHECK(vkCreateShaderModule(VK.Dev,&ci,0,&VK.Shaders[i]));
    code += ShaderWords[i];
  }
  VK.VS = VK.PS = -1;

  InitStates();
  VK.VPW = xs; VK.VPH = ys;
  return 1;
}

// vertex formats: every location the format lacks reads zero from binding 1,
// so any shader can be used with any format
void vkrSetVertexFormats(int count,const int *strides,const VkrVertexElement *const *elements,const int *elementCounts)
{
  if(count>VKR_MAXFORMATS) count = VKR_MAXFORMATS;
  VK.NumFormats = count;
  for(int f=0;f<count;f++)
  {
    VK.Stride[f] = strides[f];
    int n = 0;
    uint32_t have = 0;
    for(int e=0;e<elementCounts[f];e++)
    {
      VkVertexInputAttributeDescription &a = VK.Attr[f][n++];
      a.location = elements[f][e].Location;
      a.binding = 0;
      a.format = (VkFormat) elements[f][e].Format;
      a.offset = elements[f][e].Offset;
      have |= 1u<<a.location;
    }
    for(int loc=0;loc<VKR_LOCATIONS;loc++)
    {
      if(have & (1u<<loc)) continue;
      VkVertexInputAttributeDescription &a = VK.Attr[f][n++];
      a.location = loc;
      a.binding = 1;
      a.format = VK_FORMAT_R32G32B32A32_SFLOAT;
      a.offset = 0;
    }
    VK.NumAttr[f] = n;
  }
}

/****************************************************************************/
/***   Textures                                                            ***/
/****************************************************************************/

static struct { VkrTexture *Tex; int Face,Level,XS,YS,ZS,Offset; } Lock;

void *vkrLockTexture(VkrTexture *t,int face,int level,int *pitch)
{
  int xs = t->XS>>level; if(xs<1) xs = 1;
  int ys = t->YS>>level; if(ys<1) ys = 1;
  int zs = t->ZS>>level; if(zs<1) zs = 1;
  int size = xs*ys*zs*4;
  if(size>VKR_STAGINGSIZE) Fatal("texture too large");
  if(VK.StagingUsed+size>VKR_STAGINGSIZE)
    Flush();
  Lock.Tex = t; Lock.Face = face; Lock.Level = level;
  Lock.XS = xs; Lock.YS = ys; Lock.ZS = zs;
  Lock.Offset = VK.StagingUsed;
  VK.StagingUsed = (VK.StagingUsed+size+15)&~15;
  if(pitch) *pitch = xs*4;
  return VK.Staging->Data[0]+Lock.Offset;
}

void vkrUnlockTexture()
{
  EndRendering();
  VkBufferImageCopy c = {};
  c.bufferOffset = Lock.Offset;
  c.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  c.imageSubresource.mipLevel = Lock.Level;
  c.imageSubresource.baseArrayLayer = Lock.Face;
  c.imageSubresource.layerCount = 1;
  c.imageExtent.width = Lock.XS; c.imageExtent.height = Lock.YS; c.imageExtent.depth = Lock.ZS;
  vkCmdCopyBufferToImage(VK.Cmd,VK.Staging->Buf[0],Lock.Tex->Image,VK_IMAGE_LAYOUT_GENERAL,1,&c);
  Barrier();
}

static void ReadImage(VkrTexture *t,void *dest)
{
  EndRendering();
  if(!VK.Readback || VK.Readback->Size<t->XS*t->YS*4)
  {
    if(VK.Readback) vkrDestroyBuffer(VK.Readback);
    VK.Readback = vkrCreateBuffer(t->XS*t->YS*4,0);
  }
  VkBufferImageCopy c = {};
  c.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  c.imageSubresource.layerCount = 1;
  c.imageExtent.width = t->XS; c.imageExtent.height = t->YS; c.imageExtent.depth = 1;
  vkCmdCopyImageToBuffer(VK.Cmd,t->Image,VK_IMAGE_LAYOUT_GENERAL,VK.Readback->Buf[0],1,&c);
  Flush();
  memcpy(dest,VK.Readback->Data[0],t->XS*t->YS*4);
}

void vkrReadTexture(VkrTexture *t,void *dest) { ReadImage(t,dest); }
void vkrReadBackBuffer(void *dest) { ReadImage(&VK.BackBuffer,dest); }

/****************************************************************************/
/***   Render targets, clears, copies                                      ***/
/****************************************************************************/

static VkrTexture *TargetTex() { return VK.Target ? VK.Target : &VK.BackBuffer; }

static void BeginRendering()
{
  if(VK.Rendering) return;
  VkrTexture *t = TargetTex();
  VkRenderingAttachmentInfo color = { VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO };
  color.imageView = t->View;
  color.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
  color.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
  color.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  VkRenderingAttachmentInfo depth = { VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO };
  depth.imageView = VK.DepthView;
  depth.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
  depth.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
  depth.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  VK.RenderDepth = t->XS<=VK.DepthXS && t->YS<=VK.DepthYS;
  VkRenderingInfo ri = { VK_STRUCTURE_TYPE_RENDERING_INFO };
  ri.renderArea.extent.width = t->XS;
  ri.renderArea.extent.height = t->YS;
  ri.layerCount = 1;
  ri.colorAttachmentCount = 1;
  ri.pColorAttachments = &color;
  if(VK.RenderDepth)
  {
    ri.pDepthAttachment = &depth;
    ri.pStencilAttachment = &depth;
  }
  vkCmdBeginRendering(VK.Cmd,&ri);
  VK.Rendering = 1;
  VK.BoundPipe = 0;
  VK.DynValid = 0;
  vkCmdSetFrontFace(VK.Cmd,VK_FRONT_FACE_CLOCKWISE);
}

void vkrSetTarget(VkrTexture *rt)
{
  if(rt!=VK.Target)
  {
    EndRendering();
    VkrTexture *old = VK.Target;
    VK.Target = rt;
    Unbound(old);
  }
}

void vkrSetViewport(int x,int y,int w,int h)
{
  VK.VPX = x; VK.VPY = y; VK.VPW = w; VK.VPH = h;
}

void vkrSetScissorRect(int x0,int y0,int x1,int y1)
{
  VK.ScX0 = x0; VK.ScY0 = y0; VK.ScX1 = x1; VK.ScY1 = y1;
}

static void ClearAttachments(int x0,int y0,int x1,int y1,int xs,int ys,int flags,uint32_t argb)
{
  if(x0<0) x0 = 0;
  if(y0<0) y0 = 0;
  if(x1>xs) x1 = xs;
  if(y1>ys) y1 = ys;
  if(x0>=x1 || y0>=y1) return;
  VkClearAttachment ca[2];
  int n = 0;
  if(flags & VKR_CLEAR_COLOR)
  {
    ca[n].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    ca[n].colorAttachment = 0;
    ca[n].clearValue.color.float32[0] = ((argb>>16)&255)/255.0f;
    ca[n].clearValue.color.float32[1] = ((argb>> 8)&255)/255.0f;
    ca[n].clearValue.color.float32[2] = ((argb    )&255)/255.0f;
    ca[n].clearValue.color.float32[3] = ((argb>>24)&255)/255.0f;
    n++;
  }
  if(flags & (VKR_CLEAR_DEPTH|VKR_CLEAR_STENCIL))
  {
    ca[n].aspectMask = ((flags & VKR_CLEAR_DEPTH) ? VK_IMAGE_ASPECT_DEPTH_BIT : 0) | ((flags & VKR_CLEAR_STENCIL) ? VK_IMAGE_ASPECT_STENCIL_BIT : 0);
    ca[n].colorAttachment = 0;
    ca[n].clearValue.depthStencil.depth = 1.0f;
    ca[n].clearValue.depthStencil.stencil = 0;
    n++;
  }
  VkClearRect cr = {};
  cr.rect.offset.x = x0; cr.rect.offset.y = y0;
  cr.rect.extent.width = x1-x0; cr.rect.extent.height = y1-y0;
  cr.layerCount = 1;
  vkCmdClearAttachments(VK.Cmd,n,ca,1,&cr);
}

static void ClearRect(int x0,int y0,int x1,int y1,int flags,uint32_t argb)
{
  VkrTexture *t = TargetTex();
  BeginRendering();
  if((flags & (VKR_CLEAR_DEPTH|VKR_CLEAR_STENCIL)) && !VK.RenderDepth)
  {
    // depth buffer smaller than the target (so not attached): clear it on its own
    EndRendering();
    VkRenderingAttachmentInfo depth = { VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO };
    depth.imageView = VK.DepthView;
    depth.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
    depth.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
    depth.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    VkRenderingInfo ri = { VK_STRUCTURE_TYPE_RENDERING_INFO };
    ri.renderArea.extent.width = VK.DepthXS;
    ri.renderArea.extent.height = VK.DepthYS;
    ri.layerCount = 1;
    ri.pDepthAttachment = &depth;
    ri.pStencilAttachment = &depth;
    vkCmdBeginRendering(VK.Cmd,&ri);
    ClearAttachments(x0,y0,x1,y1,VK.DepthXS,VK.DepthYS,flags & ~VKR_CLEAR_COLOR,0);
    vkCmdEndRendering(VK.Cmd);
    Barrier();
    flags &= VKR_CLEAR_COLOR;
    if(!flags) return;
    BeginRendering();
  }
  ClearAttachments(x0,y0,x1,y1,t->XS,t->YS,flags,argb);
}

void vkrClear(int flags,uint32_t argb)
{
  int x0 = VK.VPX, y0 = VK.VPY, x1 = VK.VPX+VK.VPW, y1 = VK.VPY+VK.VPH;
  if(VK.States[VKR_SCISSOR])               // clears honour the scissor rect
  {
    if(x0<VK.ScX0) x0 = VK.ScX0;
    if(y0<VK.ScY0) y0 = VK.ScY0;
    if(x1>VK.ScX1) x1 = VK.ScX1;
    if(y1>VK.ScY1) y1 = VK.ScY1;
  }
  ClearRect(x0,y0,x1,y1,flags,argb);
}

void vkrFillRect(int x0,int y0,int x1,int y1,uint32_t argb)
{
  VkrTexture *old = VK.Target;
  vkrSetTarget(0);
  ClearRect(x0,y0,x1,y1,VKR_CLEAR_COLOR,argb);
  vkrSetTarget(old);
}

void vkrCopyToTexture(VkrTexture *src,int x0,int y0,int x1,int y1,VkrTexture *dst,int stretch)
{
  if(!src) src = &VK.BackBuffer;
  EndRendering();
  VkImageBlit blit = {};
  blit.srcSubresource.aspectMask = blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  blit.srcSubresource.layerCount = blit.dstSubresource.layerCount = 1;
  blit.srcOffsets[0].x = x0; blit.srcOffsets[0].y = y0;
  blit.srcOffsets[1].x = x1; blit.srcOffsets[1].y = y1; blit.srcOffsets[1].z = 1;
  blit.dstOffsets[1].x = stretch ? dst->XS : x1-x0;
  blit.dstOffsets[1].y = stretch ? dst->YS : y1-y0;
  blit.dstOffsets[1].z = 1;
  vkCmdBlitImage(VK.Cmd,src->Image,VK_IMAGE_LAYOUT_GENERAL,dst->Image,VK_IMAGE_LAYOUT_GENERAL,1,&blit,VK_FILTER_NEAREST);
  Barrier();
}

/****************************************************************************/
/***   Shaders, states, pipelines                                          ***/
/****************************************************************************/

void vkrSetState(int token,uint32_t value)
{
  if(token>=0 && token<VKR_STATES)
    VK.States[token] = value;
}

void vkrSetShaders(int vs,int ps) { VK.VS = vs; VK.PS = ps; }

void vkrSetTexture(int stage,VkrTexture *tex)
{
  if(stage<4)
  {
    VkrTexture *old = VK.Tex[stage];
    VK.Tex[stage] = tex;
    Unbound(old);
  }
}

void vkrSetVSConst(int start,const float *v,int count)
{
  if(start+count>256) count = 256-start;
  if(count>0) memcpy(VK.VSConst+start*4,v,count*16);
}

void vkrSetPSConst(int start,const float *v,int count)
{
  if(start+count>8) count = 8-start;
  if(count>0) memcpy(VK.PSConst+start*4,v,count*16);
}

void vkrSetStreams(int format,VkrBuffer *vb,int vbOffset,VkrBuffer *ib,int index32)
{
  VK.Format = format;
  VK.VB = vb;
  VK.VBOffset = vbOffset;
  VK.IB = ib;
  VK.Index32 = index32;
}

// pipeline create info: constant parts are static templates, Pipeline()
// fills in shaders, vertex layout, topology class, blending and formats
static VkPipelineShaderStageCreateInfo PStages[2] =
{
  { .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, .stage = VK_SHADER_STAGE_VERTEX_BIT, .pName = "main" },
  { .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, .stage = VK_SHADER_STAGE_FRAGMENT_BIT, .pName = "main" },
};
static VkVertexInputBindingDescription PBind[2] = { { 0,0,VK_VERTEX_INPUT_RATE_VERTEX },{ 1,0,VK_VERTEX_INPUT_RATE_INSTANCE } };
static VkVertexInputAttributeDescription PAttr[16];
static VkPipelineVertexInputStateCreateInfo PVertex =
  { .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO, .pVertexBindingDescriptions = PBind, .pVertexAttributeDescriptions = PAttr };
static VkPipelineInputAssemblyStateCreateInfo PAssembly = { .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
static const VkPipelineViewportStateCreateInfo PViewport =
  { .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO, .viewportCount = 1, .scissorCount = 1 };
static const VkPipelineRasterizationStateCreateInfo PRaster =
  { .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO, .polygonMode = VK_POLYGON_MODE_FILL, .lineWidth = 1.0f };
static const VkPipelineMultisampleStateCreateInfo PMultisample =
  { .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO, .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT };
static const VkPipelineDepthStencilStateCreateInfo PDepth = { .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
static VkPipelineColorBlendAttachmentState PBlendAtt;
static const VkPipelineColorBlendStateCreateInfo PBlend =
  { .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO, .attachmentCount = 1, .pAttachments = &PBlendAtt,
    .blendConstants = { 1.0f,1.0f,1.0f,1.0f } };
static const VkDynamicState PDynList[] =
{
  VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR, VK_DYNAMIC_STATE_CULL_MODE, VK_DYNAMIC_STATE_FRONT_FACE,
  VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY, VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE, VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE,
  VK_DYNAMIC_STATE_DEPTH_COMPARE_OP, VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE, VK_DYNAMIC_STATE_STENCIL_OP,
  VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK, VK_DYNAMIC_STATE_STENCIL_WRITE_MASK, VK_DYNAMIC_STATE_STENCIL_REFERENCE,
  VK_DYNAMIC_STATE_DEPTH_BIAS, VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE,
};
static const VkPipelineDynamicStateCreateInfo PDynamic =
  { .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO, .dynamicStateCount = sizeof(PDynList)/sizeof(PDynList[0]), .pDynamicStates = PDynList };
static const VkFormat PColorFormat = VK_FORMAT_B8G8R8A8_UNORM;
static VkPipelineRenderingCreateInfo PRendering =
  { .sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO, .colorAttachmentCount = 1, .pColorAttachmentFormats = &PColorFormat };
static VkGraphicsPipelineCreateInfo PCreate =
{
  .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO, .pNext = &PRendering, .stageCount = 2, .pStages = PStages,
  .pVertexInputState = &PVertex, .pInputAssemblyState = &PAssembly, .pViewportState = &PViewport,
  .pRasterizationState = &PRaster, .pMultisampleState = &PMultisample, .pDepthStencilState = &PDepth,
  .pColorBlendState = &PBlend, .pDynamicState = &PDynamic,
};

static VkPipeline Pipeline(int topoClass)
{
  const uint32_t *s = VK.States;
  VkrPipeKey key;
  key.VS = VK.VS;
  key.PS = VK.PS;
  key.Format = VK.Format;
  key.Topology = topoClass;
  key.Blend = s[VKR_BLEND] ? (s[VKR_BLENDSRC]&31) | ((s[VKR_BLENDDST]&31)<<5) | ((s[VKR_BLENDOP]&7)<<10) | 0x10000 : 0;
  key.ColorMask = s[VKR_COLORMASK]&15;
  key.Depth = VK.RenderDepth;
  for(int i=0;i<VK.NumPipes;i++)
    if(!memcmp(&VK.Pipes[i].Key,&key,sizeof(key)))
      return VK.Pipes[i].Pipe;
  if(VK.NumPipes==VKR_MAXPIPES) Fatal("too many pipelines");

  PStages[0].module = VK.Shaders[VK.VS];
  PStages[1].module = VK.Shaders[VK.PS];
  PBind[0].stride = VK.Stride[VK.Format];
  PVertex.vertexBindingDescriptionCount = 2;
  PVertex.vertexAttributeDescriptionCount = VK.NumAttr[VK.Format];
  PVertex.pVertexAttributeDescriptions = VK.Attr[VK.Format];
  PAssembly.topology = (VkPrimitiveTopology)(topoClass==2 ? VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST : topoClass);   // POINT_LIST 0, LINE_LIST 1
  PBlendAtt.blendEnable = key.Blend!=0;
  PBlendAtt.srcColorBlendFactor = PBlendAtt.srcAlphaBlendFactor = (VkBlendFactor) s[VKR_BLENDSRC];
  PBlendAtt.dstColorBlendFactor = PBlendAtt.dstAlphaBlendFactor = (VkBlendFactor) s[VKR_BLENDDST];
  PBlendAtt.colorBlendOp = PBlendAtt.alphaBlendOp = (VkBlendOp) s[VKR_BLENDOP];
  PBlendAtt.colorWriteMask = key.ColorMask;
  PRendering.depthAttachmentFormat = PRendering.stencilAttachmentFormat = key.Depth ? VK.DepthFormat : VK_FORMAT_UNDEFINED;
  PCreate.layout = VK.Layout;

  VkPipeline pipe;
  VKCHECK(vkCreateGraphicsPipelines(VK.Dev,0,1,&PCreate,0,&pipe));
  VK.Pipes[VK.NumPipes].Key = key;
  VK.Pipes[VK.NumPipes].Pipe = pipe;
  VK.NumPipes++;
  return pipe;
}

// cube maps clamp; LOD range: single level textures 0..1, VKR_MIP_NONE 0..0,
// otherwise 0..16
static VkSamplerCreateInfo SamplerInfo = { .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO };

static VkSampler Sampler(int stage,VkrTexture *t)
{
  const uint32_t *s = VK.States+VKR_SAMPLER+stage*8;
  uint32_t key = 0;
  for(int i=2;i>=0;i--)
    key = (key<<3) | (t->Type==VKR_TEXCUBE ? VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE : s[VKR_ADDRESSU+i]&7);
  uint32_t mip = s[VKR_MIPFILTER];
  uint32_t lod = t->Levels==1 ? 0 : mip ? 2 : 1;
  key |= ((s[VKR_MAGFILTER]&1)<<9) | ((s[VKR_MINFILTER]&1)<<10) | ((mip==VKR_MIP_LINEAR)<<11) | (lod<<12);
  for(int i=0;i<VK.NumSamplers;i++)
    if(VK.Samplers[i].Key==key)
      return VK.Samplers[i].Sampler;
  if(VK.NumSamplers==VKR_MAXSAMPLERS) Fatal("too many samplers");
  VkSamplerCreateInfo &ci = SamplerInfo;
  ci.addressModeU = (VkSamplerAddressMode)(key&7);
  ci.addressModeV = (VkSamplerAddressMode)((key>>3)&7);
  ci.addressModeW = (VkSamplerAddressMode)((key>>6)&7);
  ci.magFilter = (VkFilter)((key>>9)&1);
  ci.minFilter = (VkFilter)((key>>10)&1);
  ci.mipmapMode = (VkSamplerMipmapMode)((key>>11)&1);
  ci.maxLod = lod==0 ? 1.0f : lod==1 ? 0.0f : 16.0f;
  VKCHECK(vkCreateSampler(VK.Dev,&ci,0,&VK.Samplers[VK.NumSamplers].Sampler));
  VK.Samplers[VK.NumSamplers].Key = key;
  return VK.Samplers[VK.NumSamplers++].Sampler;
}

static VkDeviceSize UboAlloc(const float *data,int count)
{
  VkrFrame &f = VK.Frames[VK.Frame];
  int size = count*16;
  if(f.UboUsed+size>VKR_UBOSIZE)
    Flush();
  VkDeviceSize ofs = f.UboUsed;
  memcpy(f.Ubo->Data[0]+ofs,data,size);
  f.UboUsed = (int)((ofs+size+VK.UboAlign-1) & ~(VK.UboAlign-1));
  return ofs;
}

// all dynamic state of a draw; re-sent completely when anything changed
struct VkrDynState
{
  VkViewport Viewport;
  VkRect2D Scissor;
  uint32_t Cull,Topology,ZTest,ZWrite,ZFunc,Stencil,BiasOn;
  float Bias,SlopeBias;
  uint32_t Front[4],Back[4];                // fail, pass, zfail, func
  uint32_t Mask,WriteMask,Ref;
};

static void SetDynamicState(int topology)
{
  const uint32_t *s = VK.States;
  VkrDynState d;
  memset(&d,0,sizeof(d));
  // flipped (y up) and shifted by half a pixel (pixel centres at integers)
  d.Viewport.x = VK.VPX+0.5f;
  d.Viewport.y = VK.VPY+VK.VPH+0.5f;
  d.Viewport.width = (float)VK.VPW;
  d.Viewport.height = -(float)VK.VPH;
  d.Viewport.maxDepth = 1.0f;

  // VKR_SCISSOR: scissor rect clipped to the viewport
  VkrTexture *t = TargetTex();
  int x0 = 0, y0 = 0, x1 = t->XS, y1 = t->YS;
  if(s[VKR_SCISSOR])
  {
    x0 = VK.ScX0>VK.VPX ? VK.ScX0 : VK.VPX;
    y0 = VK.ScY0>VK.VPY ? VK.ScY0 : VK.VPY;
    x1 = VK.ScX1<VK.VPX+VK.VPW ? VK.ScX1 : VK.VPX+VK.VPW;
    y1 = VK.ScY1<VK.VPY+VK.VPH ? VK.ScY1 : VK.VPY+VK.VPH;
    if(x0<0) x0 = 0;
    if(y0<0) y0 = 0;
    if(x1<x0) x1 = x0;
    if(y1<y0) y1 = y0;
  }
  d.Scissor.offset.x = x0;
  d.Scissor.offset.y = y0;
  d.Scissor.extent.width = x1-x0;
  d.Scissor.extent.height = y1-y0;

  d.Cull = s[VKR_CULL];
  static const uint8_t topo[6] =
  {
    VK_PRIMITIVE_TOPOLOGY_POINT_LIST, VK_PRIMITIVE_TOPOLOGY_POINT_LIST, VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
    VK_PRIMITIVE_TOPOLOGY_LINE_STRIP, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,
  };
  d.Topology = topo[topology];

  d.ZTest = s[VKR_ZTEST] && VK.RenderDepth;
  d.ZWrite = s[VKR_ZWRITE] && VK.RenderDepth;
  d.ZFunc = s[VKR_ZFUNC];
  d.Stencil = s[VKR_STENCIL] && VK.RenderDepth;
  for(int i=0;i<4;i++)                          // fail, pass, zfail, func
  {
    d.Front[i] = s[VKR_STENCILFAIL+i];
    d.Back[i] = s[(s[VKR_STENCIL2SIDED] ? VKR_BACKFAIL : VKR_STENCILFAIL)+i];
  }
  d.Mask = s[VKR_STENCILMASK]&255;
  d.WriteMask = s[VKR_STENCILWRITEMASK]&255;
  d.Ref = s[VKR_STENCILREF]&255;

  // the depth bias is in depth range units (1.0 = full range)
  memcpy(&d.Bias,&s[VKR_DEPTHBIAS],4);
  memcpy(&d.SlopeBias,&s[VKR_SLOPEBIAS],4);
  d.BiasOn = d.Bias!=0.0f || d.SlopeBias!=0.0f;
  d.Bias *= VK.DepthFormat==VK_FORMAT_D24_UNORM_S8_UINT ? 16777216.0f : 8388608.0f;

  static VkrDynState last;
  if(VK.DynValid && !memcmp(&d,&last,sizeof(d)))
    return;
  last = d;
  VK.DynValid = 1;
  VkCommandBuffer c = VK.Cmd;
  vkCmdSetViewport(c,0,1,&d.Viewport);
  vkCmdSetScissor(c,0,1,&d.Scissor);
  vkCmdSetCullMode(c,d.Cull);
  vkCmdSetPrimitiveTopology(c,(VkPrimitiveTopology)d.Topology);
  vkCmdSetDepthTestEnable(c,d.ZTest);
  vkCmdSetDepthWriteEnable(c,d.ZWrite);
  vkCmdSetDepthCompareOp(c,(VkCompareOp)d.ZFunc);
  vkCmdSetDepthBiasEnable(c,d.BiasOn);
  vkCmdSetDepthBias(c,d.Bias,0.0f,d.SlopeBias);
  vkCmdSetStencilTestEnable(c,d.Stencil);
  vkCmdSetStencilOp(c,VK_STENCIL_FACE_FRONT_BIT,(VkStencilOp)d.Front[0],(VkStencilOp)d.Front[1],(VkStencilOp)d.Front[2],(VkCompareOp)d.Front[3]);
  vkCmdSetStencilOp(c,VK_STENCIL_FACE_BACK_BIT,(VkStencilOp)d.Back[0],(VkStencilOp)d.Back[1],(VkStencilOp)d.Back[2],(VkCompareOp)d.Back[3]);
  vkCmdSetStencilCompareMask(c,VK_STENCIL_FACE_FRONT_AND_BACK,d.Mask);
  vkCmdSetStencilWriteMask(c,VK_STENCIL_FACE_FRONT_AND_BACK,d.WriteMask);
  vkCmdSetStencilReference(c,VK_STENCIL_FACE_FRONT_AND_BACK,d.Ref);
}

// push descriptor template: VS constants, PS constants, 4 texture stages
static VkDescriptorBufferInfo DescBuffers[2];
static VkDescriptorImageInfo DescImages[4];
#define VKR_UBO(n)  { .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, .dstBinding = n, .descriptorCount = 1, \
                      .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, .pBufferInfo = &DescBuffers[n] }
#define VKR_TEX(n)  { .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, .dstBinding = 2+n, .descriptorCount = 1, \
                      .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, .pImageInfo = &DescImages[n] }
static const VkWriteDescriptorSet DescWrites[6] = { VKR_UBO(0),VKR_UBO(1),VKR_TEX(0),VKR_TEX(1),VKR_TEX(2),VKR_TEX(3) };

static int PrepareDraw(int topology)
{
  if(VK.VS<0 || VK.PS<0 || !VK.VB) return 0;
  BeginRendering();

  VkPipeline pipe = Pipeline(topology<=1 ? 0 : topology<=3 ? 1 : 2);
  if(pipe!=VK.BoundPipe)
  {
    vkCmdBindPipeline(VK.Cmd,VK_PIPELINE_BIND_POINT_GRAPHICS,pipe);
    VK.BoundPipe = pipe;
  }
  SetDynamicState(topology);

  // descriptors (a shader without constants still gets a valid range)
  for(int i=0;i<2;i++)
  {
    int n = ShaderConsts[i ? VK.PS : VK.VS];
    if(!n) n = 1;
    DescBuffers[i].buffer = VK.Frames[VK.Frame].Ubo->Buf[0];
    DescBuffers[i].offset = UboAlloc(i ? VK.PSConst : VK.VSConst,n);
    DescBuffers[i].range = n*16;
  }
  for(int i=0;i<4;i++)
  {
    VkrTexture *t = VK.Tex[i] ? VK.Tex[i] : VK.Dummy[0];
    DescImages[i].sampler = Sampler(i,t);
    DescImages[i].imageView = t->View;
    DescImages[i].imageLayout = VK_IMAGE_LAYOUT_GENERAL;
  }
  vkCmdPushDescriptorSetKHR(VK.Cmd,VK_PIPELINE_BIND_POINT_GRAPHICS,VK.Layout,0,6,DescWrites);

  VK.VB->LastUse[Slot(VK.VB)] = VK.Serial;
  VkBuffer vb[2] = { VK.VB->Buf[Slot(VK.VB)],VK.Zero->Buf[0] };
  VkDeviceSize ofs[2] = { (VkDeviceSize)VK.VBOffset,0 };
  vkCmdBindVertexBuffers(VK.Cmd,0,2,vb,ofs);
  return 1;
}

void vkrDraw(int topology,int first,int count)
{
  if(count<=0 || !PrepareDraw(topology)) return;
  vkCmdDraw(VK.Cmd,count,1,first,0);
}

void vkrDrawIndexed(int topology,int baseVertex,int firstIndex,int count)
{
  if(count<=0 || !VK.IB || !PrepareDraw(topology)) return;
  VK.IB->LastUse[Slot(VK.IB)] = VK.Serial;
  vkCmdBindIndexBuffer(VK.Cmd,VK.IB->Buf[Slot(VK.IB)],0,VK.Index32 ? VK_INDEX_TYPE_UINT32 : VK_INDEX_TYPE_UINT16);
  vkCmdDrawIndexed(VK.Cmd,count,1,firstIndex,baseVertex,0);
}
