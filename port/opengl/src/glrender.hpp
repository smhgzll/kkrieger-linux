// This file is distributed under a BSD license. See LICENSE.txt for details.
//
// OpenGL 4.5 renderer of the Linux port: a small immediate mode API for what
// the engine draws (render states, the game's shaders, textures,
// vertex/index buffers, render targets). _start_linux.cpp implements the
// engine's sSystem_ graphics interface on top of it.
//
// Engine conventions the renderer follows: clip space z is 0..1 and y points
// up, front faces are clockwise, pixel centres are at integer coordinates,
// texture row 0 is the top (glClipControl(GL_UPPER_LEFT,GL_ZERO_TO_ONE)).

#ifndef __GLRENDER_HPP__
#define __GLRENDER_HPP__

#include <stdint.h>
#include <GL/glcorearb.h>

struct SDL_Window;
struct GlrTexture;
struct GlrBuffer;

enum
{
  GLR_TEX2D = 0, GLR_TEXCUBE = 1, GLR_TEX3D = 2,   // texture types
  GLR_BGRA8 = 0, GLR_RGBA8S = 1,                    // formats: 8 bit unsigned / signed normalized

  GLR_CLEAR_COLOR = 1, GLR_CLEAR_DEPTH = 2, GLR_CLEAR_STENCIL = 4,
};

// render states: glrSetState(token,value), values are OpenGL enums; a state
// keeps its value until it is set again
enum
{
  GLR_ZTEST,                      // 0/1
  GLR_ZWRITE,                     // 0/1
  GLR_ZFUNC,                      // GL_LESS ...
  GLR_CULL,                       // 0 (none), GL_FRONT, GL_BACK (front faces are clockwise)
  GLR_COLORMASK,                  // bit 0..3 = r,g,b,a
  GLR_BLEND,                      // 0/1
  GLR_BLENDSRC,                   // GL_ONE ... (colour and alpha)
  GLR_BLENDDST,
  GLR_BLENDOP,                    // GL_FUNC_ADD ...
  GLR_DEPTHBIAS,                  // float bits, in depth range units
  GLR_SLOPEBIAS,                  // float bits
  GLR_SCISSOR,                    // 0/1: clip to glrSetScissorRect
  GLR_STENCIL,                    // 0/1
  GLR_STENCIL2SIDED,              // 0/1: back faces use the GLR_BACK* set
  GLR_STENCILFAIL,                // GL_KEEP ...
  GLR_STENCILZFAIL,
  GLR_STENCILPASS,
  GLR_STENCILFUNC,                // GL_ALWAYS ...
  GLR_BACKFAIL, GLR_BACKZFAIL, GLR_BACKPASS, GLR_BACKFUNC,
  GLR_STENCILREF,
  GLR_STENCILMASK,
  GLR_STENCILWRITEMASK,
  GLR_SAMPLER = 32,               // + 8*stage + GLR_MAGFILTER..GLR_ADDRESSW
  GLR_STATES = GLR_SAMPLER+4*8,

  GLR_MAGFILTER = 0,              // GL_NEAREST / GL_LINEAR
  GLR_MINFILTER,                  // GL_NEAREST / GL_LINEAR
  GLR_MIPFILTER,                  // GLR_MIP_*
  GLR_ADDRESSU,                   // GL_REPEAT, GL_CLAMP_TO_EDGE ...
  GLR_ADDRESSV,
  GLR_ADDRESSW,

  GLR_MIP_NONE = 0, GLR_MIP_NEAREST, GLR_MIP_LINEAR,
};

struct GlrVertexElement
{
  int Offset;
  int Size;                       // 2,3,4 floats, or GL_BGRA (4 bytes, normalized)
  int Location;                   // shader input location
};

// setup (creates the GL context on an SDL_WINDOW_OPENGL window)
int glrInit(SDL_Window *window,int xs,int ys,int vsync);
void glrSetVertexFormats(int count,const int *strides,const GlrVertexElement *const *elements,const int *elementCounts);

// textures (type, format, size; levels = mip count, 0 = render target)
GlrTexture *glrCreateTexture(int type,int format,int xs,int ys,int zs,int levels);
void glrDestroyTexture(GlrTexture *tex);
void *glrLockTexture(GlrTexture *tex,int face,int level,int *pitch);   // write only, 4 bytes per texel
void glrUnlockTexture();                               // uploads what the last lock returned
void glrReadTexture(GlrTexture *tex,void *dest);       // level 0, tightly packed

// buffers: write between lock and unlock, unlock uploads the locked range
GlrBuffer *glrCreateBuffer(int size);
void glrDestroyBuffer(GlrBuffer *buf);
void *glrLockBuffer(GlrBuffer *buf,int offset,int size);
void glrUnlockBuffer(GlrBuffer *buf);

// render target, viewport, clears, copies
void glrSetTarget(GlrTexture *rt);                     // 0 = back buffer
void glrSetViewport(int x,int y,int w,int h);
void glrSetScissorRect(int x0,int y0,int x1,int y1);   // used while GLR_SCISSOR is set
void glrClear(int flags,uint32_t argb);                // inside the viewport (and scissor)
void glrFillRect(int x0,int y0,int x1,int y1,uint32_t argb);   // back buffer
void glrCopyToTexture(GlrTexture *src,int x0,int y0,int x1,int y1,GlrTexture *dst,int stretch);
void glrReadBackBuffer(void *dest);                    // BGRA8, xs*ys
void glrPresent();

// draw state
void glrSetState(int token,uint32_t value);
void glrSetShaders(int vs,int ps);                     // index into the game's shaders (shaders.inc)
void glrSetTexture(int stage,GlrTexture *tex);
void glrSetVSConst(int start,const float *v,int count);
void glrSetPSConst(int start,const float *v,int count);
void glrSetStreams(int format,GlrBuffer *vb,GlrBuffer *ib,int index32);
void glrDraw(int mode,int first,int count);           // GL_TRIANGLES ...
void glrDrawIndexed(int mode,int baseVertex,int firstIndex,int count);

#endif
