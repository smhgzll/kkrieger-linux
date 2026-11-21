// This file is distributed under a BSD license. See LICENSE.txt for details.
//
// OpenGL 4.5 renderer of the Linux port (see glrender.hpp).
//
// Core profile with direct state access. The engine draws into an
// off-screen back buffer (the render resolution); present blits it to the
// window, flipped and scaled. glClipControl(GL_UPPER_LEFT,GL_ZERO_TO_ONE)
// gives the engine's clip space and puts row 0 of every image at the top;
// the viewport is shifted by half a pixel (pixel centres at integers).
// The game's shaders are GLSL text (shaders.inc, made by tools/shaderpack.py
// from port/src/shaders), compiled by the driver at start as separable
// programs and combined per material in program pipelines.

#define GL_GLEXT_PROTOTYPES               // GL 4.5 straight from libOpenGL (GLVND)
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "glrender.hpp"
#include "shaders.inc"

/****************************************************************************/
/***   Objects and state                                                   ***/
/****************************************************************************/

#define GLR_MAXFORMATS  16
#define GLR_MAXSAMPLERS 32

struct GlrTexture
{
  GLuint Tex,Fbo;                         // Fbo: render targets only
  int Type,Format,XS,YS,ZS,Levels;
  int Depth;                              // depth buffer attached to Fbo
  int Dead;                               // destroyed while bound: freed once unbound
};

struct GlrBuffer
{
  GLuint Buf;
  uint8_t *Data;                          // CPU copy the engine writes
  int Size,LockOfs,LockSize;
};

static struct GlrState
{
  SDL_Window *Window;
  GlrTexture BackBuffer;
  GLuint Depth,DepthFbo,CopyFbo;
  int DepthXS,DepthYS;
  GLuint Ubo[2];
  GLuint Programs[SHADER_COUNT];
  GLuint Pipelines[SHADER_COUNT*SHADER_COUNT];
  GLuint Vao[GLR_MAXFORMATS];
  int Stride[GLR_MAXFORMATS];
  GlrTexture *Dummy;

  GlrTexture *Target;                     // 0 = back buffer
  int VPX,VPY,VPW,VPH;
  int ScX0,ScY0,ScX1,ScY1;

  uint32_t States[GLR_STATES];
  int VS,PS;
  GlrTexture *Tex[4];
  float Const[2][16*4];                   // VS c0..c15, PS c0..c7
  int ConstDirty[2];
  int Format;
  GlrBuffer *VB,*IB;
  int Index32;

  struct { uint32_t Key; GLuint Sampler; } Samplers[GLR_MAXSAMPLERS];
  int NumSamplers;
  int Dirty;                              // states, viewport or target changed
} GL;

static void __attribute__((noinline,noreturn)) Fatal(const char *msg)
{
  fprintf(stderr,"opengl: %s\n",msg);
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"kkrieger",msg,GL.Window);
  _exit(1);
}

static GlrTexture *TargetTex() { return GL.Target ? GL.Target : &GL.BackBuffer; }

/****************************************************************************/
/***   Textures and render targets                                         ***/
/****************************************************************************/

static void MakeTarget(GlrTexture *t)    // framebuffer object of a render target
{
  glCreateFramebuffers(1,&t->Fbo);
  glNamedFramebufferTexture(t->Fbo,GL_COLOR_ATTACHMENT0,t->Tex,0);
  t->Depth = t->XS<=GL.DepthXS && t->YS<=GL.DepthYS;     // a bigger target renders without depth
  if(t->Depth)
    glNamedFramebufferRenderbuffer(t->Fbo,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,GL.Depth);
}

GlrTexture *glrCreateTexture(int type,int format,int xs,int ys,int zs,int levels)
{
  static const GLenum targets[3] = { GL_TEXTURE_2D,GL_TEXTURE_CUBE_MAP,GL_TEXTURE_3D };
  GlrTexture *t = (GlrTexture *) calloc(1,sizeof(GlrTexture));
  t->Type = type;
  t->Format = format;
  t->XS = xs; t->YS = ys; t->ZS = zs>0 ? zs : 1;
  t->Levels = levels>0 ? levels : 1;
  GLenum internal = format==GLR_RGBA8S ? GL_RGBA8_SNORM : GL_RGBA8;
  glCreateTextures(targets[type],1,&t->Tex);
  if(type==GLR_TEX3D)
    glTextureStorage3D(t->Tex,t->Levels,internal,xs,ys,t->ZS);
  else
    glTextureStorage2D(t->Tex,t->Levels,internal,xs,ys);
  for(int l=0;l<t->Levels;l++)                  // new images read as zero
    glClearTexImage(t->Tex,l,GL_RGBA,GL_UNSIGNED_BYTE,0);
  if(levels==0)
    MakeTarget(t);
  return t;
}

static void FreeTexture(GlrTexture *t)
{
  if(t->Fbo) glDeleteFramebuffers(1,&t->Fbo);
  glDeleteTextures(1,&t->Tex);
  free(t);
}

static int Bound(GlrTexture *t)
{
  return t==GL.Target || t==GL.Tex[0] || t==GL.Tex[1] || t==GL.Tex[2] || t==GL.Tex[3];
}

static void Unbound(GlrTexture *t)
{
  if(t && t->Dead && !Bound(t))
    FreeTexture(t);
}

void glrDestroyTexture(GlrTexture *t)
{
  if(!t) return;
  t->Dead = 1;
  Unbound(t);
}

static struct { GlrTexture *Tex; int Face,Level,XS,YS,ZS; uint8_t *Data; int Size; } Lock;

void *glrLockTexture(GlrTexture *t,int face,int level,int *pitch)
{
  int xs = t->XS>>level; if(xs<1) xs = 1;
  int ys = t->YS>>level; if(ys<1) ys = 1;
  int zs = t->ZS>>level; if(zs<1) zs = 1;
  int size = xs*ys*zs*4;
  if(size>Lock.Size)
  {
    free(Lock.Data);
    Lock.Data = (uint8_t *) malloc(size);
    Lock.Size = size;
  }
  Lock.Tex = t; Lock.Face = face; Lock.Level = level;
  Lock.XS = xs; Lock.YS = ys; Lock.ZS = zs;
  if(pitch) *pitch = xs*4;
  return Lock.Data;
}

void glrUnlockTexture()
{
  GlrTexture *t = Lock.Tex;
  GLenum format = t->Format==GLR_RGBA8S ? GL_RGBA : GL_BGRA;
  GLenum type = t->Format==GLR_RGBA8S ? GL_BYTE : GL_UNSIGNED_BYTE;
  if(t->Type==GLR_TEX2D)
    glTextureSubImage2D(t->Tex,Lock.Level,0,0,Lock.XS,Lock.YS,format,type,Lock.Data);
  else                                          // cube: face = layer, 3d: depth
    glTextureSubImage3D(t->Tex,Lock.Level,0,0,Lock.Face,Lock.XS,Lock.YS,Lock.ZS,format,type,Lock.Data);
}

void glrReadTexture(GlrTexture *t,void *dest)
{
  glGetTextureImage(t->Tex,0,GL_BGRA,GL_UNSIGNED_BYTE,t->XS*t->YS*4,dest);
}

void glrReadBackBuffer(void *dest) { glrReadTexture(&GL.BackBuffer,dest); }

/****************************************************************************/
/***   Buffers                                                             ***/
/****************************************************************************/

GlrBuffer *glrCreateBuffer(int size)
{
  GlrBuffer *b = (GlrBuffer *) calloc(1,sizeof(GlrBuffer));
  b->Size = size;
  b->Data = (uint8_t *) malloc(size);
  glCreateBuffers(1,&b->Buf);
  glNamedBufferData(b->Buf,size,0,GL_DYNAMIC_DRAW);
  return b;
}

void glrDestroyBuffer(GlrBuffer *b)
{
  if(!b) return;
  glDeleteBuffers(1,&b->Buf);
  free(b->Data);
  free(b);
}

void *glrLockBuffer(GlrBuffer *b,int offset,int size)
{
  b->LockOfs = offset;
  b->LockSize = size;
  return b->Data+offset;
}

void glrUnlockBuffer(GlrBuffer *b)
{
  if(b->LockSize>0)                             // the driver orders this against earlier draws
    glNamedBufferSubData(b->Buf,b->LockOfs,b->LockSize,b->Data+b->LockOfs);
  b->LockSize = 0;
}

/****************************************************************************/
/***   Initialisation                                                      ***/
/****************************************************************************/

int glrInit(SDL_Window *window,int xs,int ys,int vsync)
{
  GL.Window = window;
  if(!SDL_GL_CreateContext(window))
    Fatal("OpenGL 4.5 is required");
  SDL_GL_SetSwapInterval(vsync ? 1 : 0);

#ifndef KK_SMALL
  fprintf(stderr,"opengl: %s\n",(const char *)glGetString(GL_RENDERER));
  if(getenv("KK_GLDEBUG"))                      // print driver errors and warnings
  {
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback([](GLenum,GLenum type,GLuint,GLenum severity,GLsizei,const GLchar *msg,const void *)
      { if(severity!=GL_DEBUG_SEVERITY_NOTIFICATION) fprintf(stderr,"gl: %s\n",msg); },0);
  }
#endif
  glClipControl(GL_UPPER_LEFT,GL_ZERO_TO_ONE);
  glFrontFace(GL_CW);
  glEnable(GL_SCISSOR_TEST);                    // always on: the scissor rect is the target when unused
  for(int i=0;i<10;i++)                         // vertex inputs a format lacks read zero
    glVertexAttrib4f(i,0.0f,0.0f,0.0f,0.0f);

  // depth/stencil (at least 1024x512 like the 2004 version) and back buffer
  GL.DepthXS = xs>1024 ? xs : 1024;
  GL.DepthYS = ys>512 ? ys : 512;
  glCreateRenderbuffers(1,&GL.Depth);
  glNamedRenderbufferStorage(GL.Depth,GL_DEPTH24_STENCIL8,GL.DepthXS,GL.DepthYS);
  glCreateFramebuffers(1,&GL.DepthFbo);
  glNamedFramebufferRenderbuffer(GL.DepthFbo,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,GL.Depth);
  glCreateFramebuffers(1,&GL.CopyFbo);
  GlrTexture *bb = glrCreateTexture(GLR_TEX2D,GLR_BGRA8,xs,ys,1,0);
  GL.BackBuffer = *bb;
  free(bb);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,GL.BackBuffer.Fbo);

  // constants: binding 0 = vertex shader, 1 = pixel shader
  glCreateBuffers(2,GL.Ubo);
  for(int i=0;i<2;i++)
  {
    glNamedBufferData(GL.Ubo[i],sizeof(GL.Const[i]),0,GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER,i,GL.Ubo[i]);
  }

  // the game's shaders
  const char *text = ShaderText;
  for(int i=0;i<SHADER_COUNT;i++)
  {
    GL.Programs[i] = glCreateShaderProgramv(i<SHADER_VS ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER,1,&text);
#ifndef KK_SMALL
    GLint ok = 0;
    glGetProgramiv(GL.Programs[i],GL_LINK_STATUS,&ok);
    if(!ok)
    {
      char log[2048];
      glGetProgramInfoLog(GL.Programs[i],sizeof(log),0,log);
      fprintf(stderr,"shader %d: %s\n",i,log);
      Fatal("shader compile failed");
    }
#endif
    text += strlen(text)+1;
  }

  // unbound stages sample (0,0,0,1)
  GL.Dummy = glrCreateTexture(GLR_TEX2D,GLR_BGRA8,1,1,1,1);
  *(uint32_t *) glrLockTexture(GL.Dummy,0,0,0) = 0xff000000;
  glrUnlockTexture();

  static const uint8_t defaults[][2] =          // the rest starts as 0
  {
    { GLR_ZWRITE,1 }, { GLR_COLORMASK,15 }, { GLR_STENCILMASK,255 }, { GLR_STENCILWRITEMASK,255 },
  };
  for(unsigned i=0;i<sizeof(defaults)/sizeof(defaults[0]);i++)
    GL.States[defaults[i][0]] = defaults[i][1];
  GL.States[GLR_ZFUNC] = GL_LEQUAL;
  GL.States[GLR_CULL] = GL_BACK;
  GL.States[GLR_BLENDSRC] = GL_ONE;
  GL.States[GLR_BLENDOP] = GL_FUNC_ADD;
  GL.States[GLR_STENCILFUNC] = GL.States[GLR_BACKFUNC] = GL_ALWAYS;
  for(int i=GLR_STENCILFAIL;i<=GLR_BACKPASS;i++)
    if(i!=GLR_STENCILFUNC) GL.States[i] = GL_KEEP;
  for(int s=0;s<4;s++)
  {
    uint32_t *st = GL.States+GLR_SAMPLER+s*8;
    st[GLR_MAGFILTER] = st[GLR_MINFILTER] = GL_NEAREST;
    st[GLR_ADDRESSU] = st[GLR_ADDRESSV] = st[GLR_ADDRESSW] = GL_REPEAT;
  }
  GL.VS = GL.PS = -1;
  GL.VPW = xs; GL.VPH = ys;
  GL.Dirty = 1;
  return 1;
}

// vertex formats: one vertex array object each, buffer binding 0
void glrSetVertexFormats(int count,const int *strides,const GlrVertexElement *const *elements,const int *elementCounts)
{
  if(count>GLR_MAXFORMATS) count = GLR_MAXFORMATS;
  for(int f=0;f<count;f++)
  {
    GLuint vao;
    glCreateVertexArrays(1,&vao);
    for(int e=0;e<elementCounts[f];e++)
    {
      const GlrVertexElement &el = elements[f][e];
      int bgra = el.Size==GL_BGRA;
      glEnableVertexArrayAttrib(vao,el.Location);
      glVertexArrayAttribFormat(vao,el.Location,el.Size,bgra ? GL_UNSIGNED_BYTE : GL_FLOAT,bgra,el.Offset);
      glVertexArrayAttribBinding(vao,el.Location,0);
    }
    GL.Vao[f] = vao;
    GL.Stride[f] = strides[f];
  }
}

/****************************************************************************/
/***   Targets, clears, copies, present                                    ***/
/****************************************************************************/

void glrSetTarget(GlrTexture *rt)
{
  if(rt!=GL.Target)
  {
    GlrTexture *old = GL.Target;
    GL.Target = rt;
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,TargetTex()->Fbo);
    GL.Dirty = 1;
    Unbound(old);
  }
}

void glrSetViewport(int x,int y,int w,int h)
{
  GL.VPX = x; GL.VPY = y; GL.VPW = w; GL.VPH = h;
  GL.Dirty = 1;
}

void glrSetScissorRect(int x0,int y0,int x1,int y1)
{
  GL.ScX0 = x0; GL.ScY0 = y0; GL.ScX1 = x1; GL.ScY1 = y1;
  GL.Dirty = 1;
}

// clears ignore the write masks, but honour the scissor rect
static void ClearRect(GLuint fbo,int x0,int y0,int x1,int y1,int flags,uint32_t argb)
{
  if(x0<0) x0 = 0;
  if(y0<0) y0 = 0;
  if(x1<=x0 || y1<=y0) return;
  glScissor(x0,y0,x1-x0,y1-y0);
  glColorMask(1,1,1,1);
  glDepthMask(1);
  glStencilMask(255);
  GL.Dirty = 1;
  if(flags & GLR_CLEAR_COLOR)
  {
    float c[4] = { ((argb>>16)&255)/255.0f,((argb>>8)&255)/255.0f,(argb&255)/255.0f,(argb>>24)/255.0f };
    glClearNamedFramebufferfv(fbo,GL_COLOR,0,c);
  }
  static const float one = 1.0f;
  static const GLint zero = 0;
  switch(flags & (GLR_CLEAR_DEPTH|GLR_CLEAR_STENCIL))
  {
  case GLR_CLEAR_DEPTH:   glClearNamedFramebufferfv(fbo,GL_DEPTH,0,&one); break;
  case GLR_CLEAR_STENCIL: glClearNamedFramebufferiv(fbo,GL_STENCIL,0,&zero); break;
  case GLR_CLEAR_DEPTH|GLR_CLEAR_STENCIL: glClearNamedFramebufferfi(fbo,GL_DEPTH_STENCIL,0,1.0f,0); break;
  }
}

void glrClear(int flags,uint32_t argb)
{
  GlrTexture *t = TargetTex();
  int x0 = GL.VPX, y0 = GL.VPY, x1 = GL.VPX+GL.VPW, y1 = GL.VPY+GL.VPH;
  if(GL.States[GLR_SCISSOR])
  {
    if(x0<GL.ScX0) x0 = GL.ScX0;
    if(y0<GL.ScY0) y0 = GL.ScY0;
    if(x1>GL.ScX1) x1 = GL.ScX1;
    if(y1>GL.ScY1) y1 = GL.ScY1;
  }
  if(x1>t->XS) x1 = t->XS;
  if(y1>t->YS) y1 = t->YS;
  if(!t->Depth && (flags & (GLR_CLEAR_DEPTH|GLR_CLEAR_STENCIL)))
  {
    // the depth buffer is smaller than the target (so not attached): clear it on its own
    ClearRect(GL.DepthFbo,x0,y0,x1,y1,flags & ~GLR_CLEAR_COLOR,0);
    flags &= GLR_CLEAR_COLOR;
  }
  ClearRect(t->Fbo,x0,y0,x1,y1,flags,argb);
}

void glrFillRect(int x0,int y0,int x1,int y1,uint32_t argb)
{
  ClearRect(GL.BackBuffer.Fbo,x0,y0,x1,y1,GLR_CLEAR_COLOR,argb);
}

void glrCopyToTexture(GlrTexture *src,int x0,int y0,int x1,int y1,GlrTexture *dst,int stretch)
{
  if(!src) src = &GL.BackBuffer;
  GLuint fbo = dst->Fbo;
  if(!fbo)
  {
    fbo = GL.CopyFbo;
    glNamedFramebufferTexture(fbo,GL_COLOR_ATTACHMENT0,dst->Tex,0);
  }
  glDisable(GL_SCISSOR_TEST);
  glBlitNamedFramebuffer(src->Fbo,fbo,x0,y0,x1,y1,0,0,stretch ? dst->XS : x1-x0,stretch ? dst->YS : y1-y0,
                         GL_COLOR_BUFFER_BIT,GL_NEAREST);
  glEnable(GL_SCISSOR_TEST);
}

void glrPresent()
{
  int w,h;
  SDL_GetWindowSizeInPixels(GL.Window,&w,&h);
  glDisable(GL_SCISSOR_TEST);
  glBlitNamedFramebuffer(GL.BackBuffer.Fbo,0,0,0,GL.BackBuffer.XS,GL.BackBuffer.YS,0,h,w,0,   // row 0 is the top
                         GL_COLOR_BUFFER_BIT,GL_LINEAR);
  glEnable(GL_SCISSOR_TEST);
  SDL_GL_SwapWindow(GL.Window);
}

/****************************************************************************/
/***   Draw state                                                          ***/
/****************************************************************************/

void glrSetState(int token,uint32_t value)
{
  if(token>=0 && token<GLR_STATES && GL.States[token]!=value)
  {
    GL.States[token] = value;
    GL.Dirty = 1;
  }
}

void glrSetShaders(int vs,int ps) { GL.VS = vs; GL.PS = ps; }

void glrSetTexture(int stage,GlrTexture *tex)
{
  if(stage<4)
  {
    GlrTexture *old = GL.Tex[stage];
    GL.Tex[stage] = tex;
    Unbound(old);
  }
}

void glrSetVSConst(int start,const float *v,int count)
{
  if(start+count>16) count = 16-start;
  if(count>0) { memcpy(GL.Const[0]+start*4,v,count*16); GL.ConstDirty[0] = 1; }
}

void glrSetPSConst(int start,const float *v,int count)
{
  if(start+count>8) count = 8-start;
  if(count>0) { memcpy(GL.Const[1]+start*4,v,count*16); GL.ConstDirty[1] = 1; }
}

void glrSetStreams(int format,GlrBuffer *vb,GlrBuffer *ib,int index32)
{
  GL.Format = format;
  GL.VB = vb;
  GL.IB = ib;
  GL.Index32 = index32;
}

// cube maps clamp; mip filter none: the top level only
static GLuint Sampler(int stage,GlrTexture *t)
{
  const uint32_t *s = GL.States+GLR_SAMPLER+stage*8;
  uint32_t mag = s[GLR_MAGFILTER]==GL_LINEAR, min = s[GLR_MINFILTER]==GL_LINEAR, mip = s[GLR_MIPFILTER]&3;
  static const uint16_t wrap[5] = { GL_REPEAT,GL_CLAMP_TO_EDGE,GL_MIRRORED_REPEAT,GL_CLAMP_TO_BORDER,GL_MIRROR_CLAMP_TO_EDGE };
  uint32_t key = mag | (min<<1) | (mip<<2);
  for(int i=0;i<3;i++)
  {
    uint32_t a = t->Type==GLR_TEXCUBE ? GL_CLAMP_TO_EDGE : s[GLR_ADDRESSU+i];
    uint32_t n = 0;
    while(n<4 && wrap[n]!=a) n++;
    key |= n<<(4+i*3);
  }
  for(int i=0;i<GL.NumSamplers;i++)
    if(GL.Samplers[i].Key==key)
      return GL.Samplers[i].Sampler;
  if(GL.NumSamplers==GLR_MAXSAMPLERS) Fatal("too many samplers");
  static const uint16_t minf[3][2] =            // [mip][min]
  {
    { GL_NEAREST,GL_LINEAR },
    { GL_NEAREST_MIPMAP_NEAREST,GL_LINEAR_MIPMAP_NEAREST },
    { GL_NEAREST_MIPMAP_LINEAR,GL_LINEAR_MIPMAP_LINEAR },
  };
  GLuint smp;
  glCreateSamplers(1,&smp);
  glSamplerParameteri(smp,GL_TEXTURE_MAG_FILTER,mag ? GL_LINEAR : GL_NEAREST);
  glSamplerParameteri(smp,GL_TEXTURE_MIN_FILTER,minf[mip][min]);
  glSamplerParameteri(smp,GL_TEXTURE_WRAP_S,wrap[(key>>4)&7]);
  glSamplerParameteri(smp,GL_TEXTURE_WRAP_T,wrap[(key>>7)&7]);
  glSamplerParameteri(smp,GL_TEXTURE_WRAP_R,wrap[(key>>10)&7]);
  GL.Samplers[GL.NumSamplers].Key = key;
  GL.Samplers[GL.NumSamplers++].Sampler = smp;
  return smp;
}

static void ApplyState()
{
  if(!GL.Dirty) return;
  GL.Dirty = 0;
  const uint32_t *s = GL.States;
  GlrTexture *t = TargetTex();
  glViewportIndexedf(0,GL.VPX+0.5f,GL.VPY+0.5f,(float)GL.VPW,(float)GL.VPH);   // pixel centres at integers
  int x0 = 0, y0 = 0, x1 = t->XS, y1 = t->YS;
  if(s[GLR_SCISSOR])                            // scissor rect clipped to the viewport
  {
    x0 = GL.ScX0>GL.VPX ? GL.ScX0 : GL.VPX;
    y0 = GL.ScY0>GL.VPY ? GL.ScY0 : GL.VPY;
    x1 = GL.ScX1<GL.VPX+GL.VPW ? GL.ScX1 : GL.VPX+GL.VPW;
    y1 = GL.ScY1<GL.VPY+GL.VPH ? GL.ScY1 : GL.VPY+GL.VPH;
    if(x0<0) x0 = 0;
    if(y0<0) y0 = 0;
    if(x1<x0) x1 = x0;
    if(y1<y0) y1 = y0;
  }
  glScissor(x0,y0,x1-x0,y1-y0);
  (s[GLR_CULL] ? glEnable : glDisable)(GL_CULL_FACE);
  if(s[GLR_CULL]) glCullFace(s[GLR_CULL]);
  (s[GLR_ZTEST] ? glEnable : glDisable)(GL_DEPTH_TEST);
  glDepthMask(s[GLR_ZWRITE]);
  glDepthFunc(s[GLR_ZFUNC]);
  (s[GLR_BLEND] ? glEnable : glDisable)(GL_BLEND);
  glBlendFunc(s[GLR_BLENDSRC],s[GLR_BLENDDST]);
  glBlendEquation(s[GLR_BLENDOP]);
  uint32_t m = s[GLR_COLORMASK];
  glColorMask(m&1,(m>>1)&1,(m>>2)&1,(m>>3)&1);
  (s[GLR_STENCIL] ? glEnable : glDisable)(GL_STENCIL_TEST);
  glStencilMask(s[GLR_STENCILWRITEMASK]&255);
  int back = s[GLR_STENCIL2SIDED] ? GLR_BACKFAIL : GLR_STENCILFAIL;   // two sided: the back face set
  glStencilOpSeparate(GL_FRONT,s[GLR_STENCILFAIL],s[GLR_STENCILZFAIL],s[GLR_STENCILPASS]);
  glStencilOpSeparate(GL_BACK,s[back],s[back+1],s[back+2]);
  glStencilFuncSeparate(GL_FRONT,s[GLR_STENCILFUNC],s[GLR_STENCILREF]&255,s[GLR_STENCILMASK]&255);
  glStencilFuncSeparate(GL_BACK,s[back+3],s[GLR_STENCILREF]&255,s[GLR_STENCILMASK]&255);
#ifndef KK_SMALL
  float bias,slope;                             // depth range units -> 24 bit depth units
  memcpy(&bias,&s[GLR_DEPTHBIAS],4);
  memcpy(&slope,&s[GLR_SLOPEBIAS],4);
  (bias!=0.0f || slope!=0.0f ? glEnable : glDisable)(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(slope,bias*16777216.0f);
#endif
}

static int Prepare()
{
  if(GL.VS<0 || GL.PS<0 || !GL.VB) return 0;
  GLuint &pipe = GL.Pipelines[GL.VS*SHADER_COUNT+GL.PS];
  if(!pipe)
  {
    glCreateProgramPipelines(1,&pipe);
    glUseProgramStages(pipe,GL_VERTEX_SHADER_BIT,GL.Programs[GL.VS]);
    glUseProgramStages(pipe,GL_FRAGMENT_SHADER_BIT,GL.Programs[GL.PS]);
  }
  glBindProgramPipeline(pipe);
  ApplyState();
  for(int i=0;i<4;i++)                          // stage n = unit 2+n (the shaders' bindings)
  {
    GlrTexture *t = GL.Tex[i] ? GL.Tex[i] : GL.Dummy;
    glBindTextureUnit(2+i,t->Tex);
    glBindSampler(2+i,Sampler(i,t));
  }
  for(int i=0;i<2;i++)
    if(GL.ConstDirty[i])
    {
      glNamedBufferSubData(GL.Ubo[i],0,sizeof(GL.Const[i]),GL.Const[i]);
      GL.ConstDirty[i] = 0;
    }
  GLuint vao = GL.Vao[GL.Format];
  glVertexArrayVertexBuffer(vao,0,GL.VB->Buf,0,GL.Stride[GL.Format]);
  glVertexArrayElementBuffer(vao,GL.IB ? GL.IB->Buf : 0);
  glBindVertexArray(vao);
  return 1;
}

void glrDraw(int mode,int first,int count)
{
  if(count>0 && Prepare())
    glDrawArrays(mode,first,count);
}

void glrDrawIndexed(int mode,int baseVertex,int firstIndex,int count)
{
  if(count>0 && GL.IB && Prepare())
    glDrawElementsBaseVertex(mode,count,GL.Index32 ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT,
                             (void *)(intptr_t)(firstIndex*(GL.Index32 ? 4 : 2)),baseVertex);
}
