// This file is distributed under a BSD license. See LICENSE.txt for details.
//
// Vulkan renderer of the Linux port: a small immediate mode API for what the
// engine draws (render states, the game's precompiled shaders, textures,
// vertex/index buffers, render targets). _start_linux.cpp implements the
// engine's sSystem_ graphics interface on top of it.
//
// Engine conventions the renderer follows: clip space z is 0..1 and y points
// up, front faces are clockwise, pixel centres are at integer coordinates.

#ifndef __VKRENDER_HPP__
#define __VKRENDER_HPP__

#include <stdint.h>
#ifndef VK_NO_PROTOTYPES
#define VK_NO_PROTOTYPES
#endif
#include <vulkan/vulkan_core.h>

struct SDL_Window;
struct VkrTexture;
struct VkrBuffer;

enum
{
  VKR_TEX2D = 0, VKR_TEXCUBE = 1, VKR_TEX3D = 2,   // texture types
  VKR_BGRA8 = 0, VKR_RGBA8S = 1,                    // formats: 8 bit unsigned / signed normalized

  VKR_POINTS = 1, VKR_LINES, VKR_LINESTRIP, VKR_TRIS, VKR_TRISTRIP,   // topologies

  VKR_CLEAR_COLOR = 1, VKR_CLEAR_DEPTH = 2, VKR_CLEAR_STENCIL = 4,
};

// render states: vkrSetState(token,value), values are Vulkan enum values;
// a state keeps its value until it is set again
enum
{
  VKR_ZTEST,                      // 0/1
  VKR_ZWRITE,                     // 0/1
  VKR_ZFUNC,                      // VkCompareOp
  VKR_CULL,                       // VkCullModeFlags (front faces are clockwise)
  VKR_COLORMASK,                  // VkColorComponentFlags
  VKR_BLEND,                      // 0/1
  VKR_BLENDSRC,                   // VkBlendFactor (colour and alpha)
  VKR_BLENDDST,                   // VkBlendFactor
  VKR_BLENDOP,                    // VkBlendOp
  VKR_DEPTHBIAS,                  // float bits, in depth range units
  VKR_SLOPEBIAS,                  // float bits
  VKR_SCISSOR,                    // 0/1: clip to vkrSetScissorRect
  VKR_STENCIL,                    // 0/1
  VKR_STENCIL2SIDED,              // 0/1: back faces use the VKR_BACK* set
  VKR_STENCILFAIL,                // VkStencilOp
  VKR_STENCILPASS,                // VkStencilOp
  VKR_STENCILZFAIL,               // VkStencilOp
  VKR_STENCILFUNC,                // VkCompareOp
  VKR_BACKFAIL, VKR_BACKPASS, VKR_BACKZFAIL, VKR_BACKFUNC,
  VKR_STENCILREF,
  VKR_STENCILMASK,
  VKR_STENCILWRITEMASK,
  VKR_SAMPLER = 32,               // + 8*stage + VKR_MAGFILTER..VKR_ADDRESSW
  VKR_STATES = VKR_SAMPLER+4*8,

  VKR_MAGFILTER = 0,              // VkFilter
  VKR_MINFILTER,                  // VkFilter
  VKR_MIPFILTER,                  // VKR_MIP_*
  VKR_ADDRESSU,                   // VkSamplerAddressMode
  VKR_ADDRESSV,
  VKR_ADDRESSW,

  VKR_MIP_NONE = 0, VKR_MIP_NEAREST, VKR_MIP_LINEAR,
};

struct VkrVertexElement
{
  int Offset;
  int Format;                     // VkFormat
  int Location;                   // shader input location
};

// setup
int vkrInit(SDL_Window *window,int xs,int ys,int vsync);
void vkrSetVertexFormats(int count,const int *strides,const VkrVertexElement *const *elements,const int *elementCounts);

// textures (type, format, size; levels = mip count, 0 = render target)
VkrTexture *vkrCreateTexture(int type,int format,int xs,int ys,int zs,int levels);
void vkrDestroyTexture(VkrTexture *tex);
void *vkrLockTexture(VkrTexture *tex,int face,int level,int *pitch);   // write only, 4 bytes per texel
void vkrUnlockTexture();                               // uploads what the last lock returned
void vkrReadTexture(VkrTexture *tex,void *dest);       // level 0, tightly packed

// buffers (persistently mapped; dynamic ones have a copy per frame in flight)
VkrBuffer *vkrCreateBuffer(int size,int dynamic);
void vkrDestroyBuffer(VkrBuffer *buf);
void *vkrBufferData(VkrBuffer *buf);
void vkrBufferSync(VkrBuffer *buf);                    // wait until the GPU no longer reads it

// render target, viewport, clears, copies
void vkrSetTarget(VkrTexture *rt);                     // 0 = back buffer
void vkrSetViewport(int x,int y,int w,int h);
void vkrSetScissorRect(int x0,int y0,int x1,int y1);   // used while VKR_SCISSOR is set
void vkrClear(int flags,uint32_t argb);                // inside the viewport (and scissor)
void vkrFillRect(int x0,int y0,int x1,int y1,uint32_t argb);   // back buffer
void vkrCopyToTexture(VkrTexture *src,int x0,int y0,int x1,int y1,VkrTexture *dst,int stretch);
void vkrReadBackBuffer(void *dest);                    // BGRA8, xs*ys
void vkrPresent();

// draw state
void vkrSetState(int token,uint32_t value);
void vkrSetShaders(int vs,int ps);                     // index into the packed shaders (shaders.inc)
void vkrSetTexture(int stage,VkrTexture *tex);
void vkrSetVSConst(int start,const float *v,int count);
void vkrSetPSConst(int start,const float *v,int count);
void vkrSetStreams(int format,VkrBuffer *vb,int vbOffset,VkrBuffer *ib,int index32);
void vkrDraw(int topology,int first,int count);
void vkrDrawIndexed(int topology,int baseVertex,int firstIndex,int count);

#endif
