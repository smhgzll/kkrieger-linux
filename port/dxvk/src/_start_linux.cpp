// This file is distributed under a BSD license. See LICENSE.txt for details.
//
// Linux platform layer for the .kkrieger player.
//
// Derived from farbrausch's _start.cpp (fr_public/werkkzeug3_kkrieger).
// All Direct3D 9 code is kept as-is and runs on DXVK-native (D3D9 -> Vulkan).
// Replaced parts:
//   Win32 window / message loop   -> SDL3
//   DirectSound (+3D buffers)     -> SDL3 audio stream + small software mixer
//   GDI font rendering            -> fontconfig + FreeType (system libraries)
//   Win32 file / heap / timer API -> stdio / malloc / SDL timer

#include "_types.hpp"
#include "_start.hpp"
#include "_startdx.hpp"
#include "material11.hpp"

#define sPLAYER_SCREENX     1024    // the 2004 release was hardwired to 1024x768
#define sPLAYER_SCREENY     768
#define sPLAYER_FULLSCREEN  0       // windowed by default on Linux, -f for fullscreen
#define sPLAYER_DIALOG      1

#define sINTRO_NO_ALT_TAB   0

const sChar *sWindowTitle=".kkrieger (linux port)";

#include <windows.h>                // dxvk-native: minimal win32 types
#include <d3d9.h>
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>


#define WINZERO(x) {sSetMem(&x,0,sizeof(x));}
#define WINSET(x) {sSetMem(&x,0,sizeof(x));x.dwSize = sizeof(x);}
#define RELEASE(x) {if(x)x->Release();x=0;}
#ifdef KK_SMALL                 // size build: one small call per check, no file/line
static void __attribute__((noinline,noreturn)) DXErrorFatal(HRESULT hr) { sFatal("directx error %08x",hr); }
#define DXERROR(hr) {if(FAILED(hr))DXErrorFatal(hr);}
#else
#define DXERROR(hr) {if(FAILED(hr))sFatal("%s(%d) : directx error %08x (%d)",__FILE__,__LINE__,hr,hr&0x3fff);}
#endif

#undef DeleteFile
#undef GetCurrentDirectory
#undef LoadBitmap

#define LOGGING 0

sMAKEZONE(FlipLock,"FlipLock",0xffff0000);
sMAKEZONE(MtrlSet,"MtrlSet",0xff404040);
sMAKEZONE(MtrlSetSetup,"MtrlSetSetup",0xff203040);
sMAKEZONE(Sound3D,"Sound3D",0xff804040);

/****************************************************************************/
/***                                                                      ***/
/***   Win32 compatibility shims used by the (unchanged) D3D code         ***/
/***                                                                      ***/
/****************************************************************************/

static SDL_Window *SDLWin;
static sBool QuitRequested;

static inline sU32 timeGetTime() { return (sU32) SDL_GetTicks(); }

// verification aid: KK_FIXEDTIME=ms makes every frame exactly ms long (and the
// random seed fixed), so two builds render identical frames for KK_SHOT
static sInt FixedTimeStep = -1,FixedTimeFrames;

static sBool FixedTime()
{
  if(FixedTimeStep<0)
    FixedTimeStep = getenv("KK_FIXEDTIME") ? atoi(getenv("KK_FIXEDTIME")) : 0;
  return FixedTimeStep>0;
}

static inline void Sleep(sU32 ms) { SDL_Delay(ms); }
static inline void ExitProcess(sInt code) { SDL_Quit(); _exit(code); }
#define VK_SPACE 0x20
static inline sInt GetAsyncKeyState(sInt vk)
{
  const bool *ks = SDL_GetKeyboardState(0);
  return (vk==VK_SPACE && ks[SDL_SCANCODE_SPACE]) ? 0x8000 : 0;
}

// the game code declares these itself (kkriegergame.cpp)
extern "C" int __cdecl wsprintfA(sChar *buffer,const sChar *format,...)
{
  va_list ap;
  va_start(ap,format);
  int r = vsprintf(buffer,format,ap);
  va_end(ap);
  return r;
}
extern "C" void __stdcall OutputDebugStringA(const sChar *str)
{
  fputs(str,stderr);
}
extern "C" int __stdcall wvsprintfA(char *buffer,const char *fmt,va_list args)
{
  return vsprintf(buffer,fmt,args);
}

/****************************************************************************/
/***                                                                      ***/
/***   System Initialisation                                              ***/
/***                                                                      ***/
/****************************************************************************/

class sBroker_ *sBroker;

static char WCmdLineBuf[1024];
sChar *WCmdLine = WCmdLineBuf;

sSystem_ *sSystem;

static sU64 sPerfFrame;
static sF64 sPerfKalibFactor = 1.0f/1000;
static sU64 sPerfKalibRDTSC;
static sU64 sPerfKalibQuery;

sInt IntroScreenX=sPLAYER_SCREENX;
sInt IntroScreenY=sPLAYER_SCREENY;
sInt IntroFlags = sPLAYER_FULLSCREEN ? sSF_FULLSCREEN : 0;
sInt IntroTargetAspect = 0;
sBool IntroHighTexRes = sTRUE;
sInt IntroLoop;
sBool IntroStereo3D = sTRUE;

sInt sFatality;

/****************************************************************************/
/***                                                                      ***/
/***   FVF Codes                                                          ***/
/***                                                                      ***/
/****************************************************************************/


struct FVFTableStruct
{
  sInt Size;                      // size in bytes!
  D3DVERTEXELEMENT9 *Info;        // dx declaration
  IDirect3DVertexDeclaration9 *Decl;    // declaration object
};

static D3DVERTEXELEMENT9 DeclDefault[] = 
{
  { 0, 0,D3DDECLTYPE_FLOAT3    ,0,D3DDECLUSAGE_POSITION  ,0 },
  { 0,12,D3DDECLTYPE_FLOAT3    ,0,D3DDECLUSAGE_NORMAL    ,0 },
  { 0,24,D3DDECLTYPE_FLOAT2    ,0,D3DDECLUSAGE_TEXCOORD  ,0 },
  D3DDECL_END()
};
static D3DVERTEXELEMENT9 DeclDouble[] = 
{
  { 0, 0,D3DDECLTYPE_FLOAT3    ,0,D3DDECLUSAGE_POSITION  ,0 },
  { 0,12,D3DDECLTYPE_D3DCOLOR  ,0,D3DDECLUSAGE_COLOR     ,0 },
  { 0,16,D3DDECLTYPE_FLOAT2    ,0,D3DDECLUSAGE_TEXCOORD  ,0 },
  { 0,24,D3DDECLTYPE_FLOAT2    ,0,D3DDECLUSAGE_TEXCOORD  ,1 },
  D3DDECL_END()
};
static D3DVERTEXELEMENT9 DeclTSpace[] = 
{
  { 0, 0,D3DDECLTYPE_FLOAT3    ,0,D3DDECLUSAGE_POSITION  ,0 },
  { 0,12,D3DDECLTYPE_FLOAT3    ,0,D3DDECLUSAGE_NORMAL    ,0 },
  { 0,24,D3DDECLTYPE_D3DCOLOR  ,0,D3DDECLUSAGE_COLOR     ,0 },
  { 0,28,D3DDECLTYPE_D3DCOLOR  ,0,D3DDECLUSAGE_COLOR     ,1 },
  { 0,32,D3DDECLTYPE_FLOAT2    ,0,D3DDECLUSAGE_TEXCOORD  ,0 },
  { 0,40,D3DDECLTYPE_FLOAT3    ,0,D3DDECLUSAGE_TANGENT   ,0 },
  { 0,52,D3DDECLTYPE_FLOAT3    ,0,D3DDECLUSAGE_BINORMAL  ,0 },
  D3DDECL_END()
};
static D3DVERTEXELEMENT9 DeclCompact[] = 
{
  { 0, 0,D3DDECLTYPE_FLOAT3    ,0,D3DDECLUSAGE_POSITION  ,0 },
  { 0,12,D3DDECLTYPE_D3DCOLOR  ,0,D3DDECLUSAGE_COLOR     ,0 },
  D3DDECL_END()
};
static D3DVERTEXELEMENT9 DeclTSpace3[] = 
{
  { 0, 0,D3DDECLTYPE_FLOAT3    ,0,D3DDECLUSAGE_POSITION  ,0 },
  { 0,12,D3DDECLTYPE_D3DCOLOR  ,0,D3DDECLUSAGE_NORMAL    ,0 },
  { 0,16,D3DDECLTYPE_D3DCOLOR  ,0,D3DDECLUSAGE_TANGENT   ,0 },
  { 0,20,D3DDECLTYPE_D3DCOLOR  ,0,D3DDECLUSAGE_COLOR     ,0 },
  { 0,24,D3DDECLTYPE_FLOAT2    ,0,D3DDECLUSAGE_TEXCOORD  ,0 },
  D3DDECL_END()
};
static D3DVERTEXELEMENT9 DeclTSpace3Big[] =
{
  { 0, 0,D3DDECLTYPE_FLOAT3    ,0,D3DDECLUSAGE_POSITION  ,0 },
  /*{ 0,12,D3DDECLTYPE_D3DCOLOR  ,0,D3DDECLUSAGE_NORMAL    ,0 },
  { 0,16,D3DDECLTYPE_D3DCOLOR  ,0,D3DDECLUSAGE_TANGENT   ,0 },
  { 0,20,D3DDECLTYPE_D3DCOLOR  ,0,D3DDECLUSAGE_COLOR     ,0 },
  { 0,24,D3DDECLTYPE_FLOAT2    ,0,D3DDECLUSAGE_TEXCOORD  ,0 },*/
  { 0,12,D3DDECLTYPE_FLOAT3    ,0,D3DDECLUSAGE_NORMAL    ,0 },
  { 0,24,D3DDECLTYPE_FLOAT3    ,0,D3DDECLUSAGE_TANGENT   ,0 },
  { 0,36,D3DDECLTYPE_D3DCOLOR  ,0,D3DDECLUSAGE_COLOR     ,0 },
  { 0,40,D3DDECLTYPE_FLOAT2    ,0,D3DDECLUSAGE_TEXCOORD  ,0 },
  D3DDECL_END()
};
static D3DVERTEXELEMENT9 DeclXYZW[] = 
{
  { 0, 0,D3DDECLTYPE_FLOAT4    ,0,D3DDECLUSAGE_POSITION  ,0 },
  D3DDECL_END()
};

static FVFTableStruct FVFTable[] = 
{
  {  0,0                },
  { 32,DeclDefault      },
  { 32,DeclDouble       },
  { 64,DeclTSpace       },
  { 16,DeclCompact      },
  { 16,DeclXYZW         },
  { 32,DeclTSpace3      },
  { 48,DeclTSpace3Big   },
};

#define FVFMax (sizeof(FVFTable)/sizeof(FVFTableStruct))

/****************************************************************************/
/***                                                                      ***/
/***   Audio state (replaces the DirectSound streaming buffer + thread)  ***/
/***                                                                      ***/
/****************************************************************************/

static SDL_AudioStream *AudioStream;
static volatile sSoundHandler DXSHandler;
static sInt DXSHandlerAlign = 64;
static void *DXSHandlerUser;
static volatile sInt DXSLastTotalSample;
static volatile sU32 AudioFramesOut;      // frames handed to SDL so far
static sListener3D Listener3D;
static sInt Num3DSamples;                 // Sample3DCommit has nothing to do without

static void MixVoices(sS16 *out,sInt frames);

static void SDLCALL AudioCallback(void *user,SDL_AudioStream *stream,int additional,int total)
{
  static sS16 buffer[4096*2];
  sInt frames = additional/4;

  while(frames>0)
  {
    sInt count = sMin<sInt>(frames,4096);
    if(DXSHandlerAlign>1)                 // handler wants aligned block sizes
      count = (count + DXSHandlerAlign-1) & ~(DXSHandlerAlign-1);
    if(count>4096) count = 4096;

    if(DXSHandler)
      (*DXSHandler)(buffer,count,DXSHandlerUser);
    else
      sSetMem(buffer,0,count*4);
    MixVoices(buffer,count);

    SDL_PutAudioStreamData(stream,buffer,count*4);
    AudioFramesOut += count;
    frames -= count;
  }
}

/****************************************************************************/
/***                                                                      ***/
/***   Heap Memory Management                                             ***/
/***                                                                      ***/
/****************************************************************************/

sDInt MemoryUsedCount;

void checkHeap()
{
}

// zeroed like fresh Windows heap pages, which the 2004 code silently relied on
// (e.g. KKriegerGame::DCellUsed is read before it is first reset)
void * __cdecl operator new(unsigned int size)    { return calloc(1,size?size:1); }
void * __cdecl operator new[](unsigned int size)  { return calloc(1,size?size:1); }
void __cdecl operator delete(void *ptr)           { free(ptr); }
void __cdecl operator delete[](void *ptr)         { free(ptr); }
void __cdecl operator delete(void *ptr,unsigned int) { free(ptr); }
void __cdecl operator delete[](void *ptr,unsigned int) { free(ptr); }

/****************************************************************************/
/***                                                                      ***/
/***   Event handling (replaces MainWndProc + MessagePump)                ***/
/***                                                                      ***/
/****************************************************************************/

static sInt MouseRelX,MouseRelY;

// Same mapping as the original VKTable: letters/digits are reported as
// their (upper case) ASCII code, plus a handful of special keys.
static sU32 MapKey(SDL_Keycode k)
{
  if(k>='a' && k<='z') return k-'a'+'A';
  if(k>='0' && k<='9') return k;
  switch(k)
  {
  case SDLK_RETURN:   return sKEY_ENTER;
  case SDLK_ESCAPE:   return sKEY_ESCAPE;
  case SDLK_SPACE:    return sKEY_SPACE;
  case SDLK_LEFT:     return sKEY_LEFT;
  case SDLK_UP:       return sKEY_UP;
  case SDLK_RIGHT:    return sKEY_RIGHT;
  case SDLK_DOWN:     return sKEY_DOWN;
  }
  return 0;
}

static void PushKey(sU32 key)
{
  if(sSystem->KeyIndex < MAX_KEYBUFFER-1)
    sSystem->KeyBuffer[sSystem->KeyIndex++] = key;
}

static sBool MessagePump()
{
  SDL_Event ev;
  sU32 key;

  static sBool automated = getenv("KK_KEYS")!=0;   // tests: ignore real input
  while(SDL_PollEvent(&ev))
  {
    if(automated && ev.type!=SDL_EVENT_QUIT && ev.type!=SDL_EVENT_WINDOW_CLOSE_REQUESTED)
      continue;
    switch(ev.type)
    {
    case SDL_EVENT_QUIT:
    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
      sSystem->Exit();
      break;
    case SDL_EVENT_KEY_DOWN:
      key = MapKey(ev.key.key);
      if(key) PushKey(key);
      break;
    case SDL_EVENT_KEY_UP:
      key = MapKey(ev.key.key);
      if(key) PushKey(key|sKEYQ_BREAK);
      break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      if(ev.button.button==SDL_BUTTON_LEFT)
      {
        sSystem->MouseButtons |= 1;
        PushKey(sKEY_MOUSEL);
      }
      break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
      if(ev.button.button==SDL_BUTTON_LEFT)
      {
        sSystem->MouseButtons &= ~1;
        PushKey(sKEY_MOUSEL|sKEYQ_BREAK);
      }
      break;
    case SDL_EVENT_MOUSE_MOTION:
      MouseRelX += (sInt) ev.motion.xrel;
      MouseRelY += (sInt) ev.motion.yrel;
      break;
    }
  }
  return !QuitRequested;
}

/****************************************************************************/
/***                                                                      ***/
/***   Startup                                                            ***/
/***                                                                      ***/
/****************************************************************************/

#ifdef KK_CRASHHANDLER
#include <signal.h>
#include <ucontext.h>
#include <execinfo.h>
static void CrashHandler(int sig,siginfo_t *si,void *ctx)
{
  ucontext_t *uc = (ucontext_t *) ctx;
  void *bt[64];
  sInt n;
  fprintf(stderr,"*** signal %d at eip=%08x addr=%p\n",sig,(unsigned)uc->uc_mcontext.gregs[REG_EIP],si->si_addr);
  n = backtrace(bt,64);
  backtrace_symbols_fd(bt,n,2);
  // walk the ebp chain as well (backtrace() can't see through some frames)
  unsigned *bp = (unsigned *) uc->uc_mcontext.gregs[REG_EBP];
  for(sInt i=0;i<32 && bp && ((unsigned)bp&3)==0;i++)
  {
    fprintf(stderr,"  frame %08x\n",bp[1]);
    bp = (unsigned *) bp[0];
  }
  _exit(1);
}
#endif

static void Usage()
{
#ifdef KK_SMALL
  fprintf(stderr,"kkrieger [-f] [-r WxH]\n");
#else
  fprintf(stderr,
    "usage: kkrieger [-f] [-r WIDTHxHEIGHT] [datafile.kx]\n"
    "  -f            fullscreen (desktop resolution, picture is scaled)\n"
    "  -r WxH        render resolution (default 1024x768, like the original)\n"
    "  datafile      load an exported werkkzeug document instead of the\n"
    "                embedded one\n");
#endif
}

int main(int argc,char **argv)
{
  sInt i;

#ifdef KK_CRASHHANDLER
  {
    struct sigaction sa;
    memset(&sa,0,sizeof(sa));
    sa.sa_sigaction = CrashHandler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV,&sa,0);
    sigaction(SIGILL,&sa,0);
    sigaction(SIGFPE,&sa,0);
    sigaction(SIGBUS,&sa,0);
  }
#endif
  WCmdLineBuf[0] = 0;
  for(i=1;i<argc;i++)
  {
    if(!strcmp(argv[i],"-f"))
      IntroFlags |= sSF_FULLSCREEN;
    else if(!strcmp(argv[i],"-r") && i+1<argc)
    {
      const char *r = argv[++i], *x = strchr(r,'x');
      IntroScreenX = atoi(r);
      IntroScreenY = x ? atoi(x+1) : 0;
      if(IntroScreenX<=0 || IntroScreenY<=0)
      {
        Usage();
        return 1;
      }
    }
#ifdef KK_SMALL                 // size build: only the embedded document
    else
#else
    else if(argv[i][0]=='-')
#endif
    {
      Usage();
      return 1;
    }
#ifndef KK_SMALL
    else
      snprintf(WCmdLineBuf,sizeof(WCmdLineBuf),"%s",argv[i]);
#endif
  }

  sSystem = new sSystem_;
  sSetMem(sSystem,0,sizeof(sSystem_));
  sSystem->InitX();
  delete sSystem;
  return 0;
}

/****************************************************************************/

void sSystem_::InitX()
{
  sInt i;

// init system

  sSystem->ConfigFlags = sSF_DIRECT3D;
  sSystem->ConfigX = IntroScreenX;
  sSystem->ConfigY = IntroScreenY;

  // DXVK-native picks its window system integration from this variable
  setenv("DXVK_WSI_DRIVER","SDL3",0);
#ifdef KK_SMALL
  // the packed build runs from a memfd: DXVK would name its log file after
  // "memfd:kkrieger (deleted)" in the current directory
  setenv("DXVK_LOG_PATH","none",0);
#endif

  if(!SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS))
    sFatal("SDL_Init failed: %s",SDL_GetError());

// set up some more stuff

  WStartTime = timeGetTime();
  sSetRndSeed(FixedTime() ? 1 : timeGetTime()&0x7fffffff);

// create window

  SDL_WindowFlags wflags = SDL_WINDOW_VULKAN;
  if(IntroFlags & sSF_FULLSCREEN)
    wflags |= SDL_WINDOW_FULLSCREEN;
  SDLWin = SDL_CreateWindow(sWindowTitle,IntroScreenX,IntroScreenY,wflags);
  if(!SDLWin)
    sFatal("could not create window: %s",SDL_GetError());
  if(!getenv("KK_NOGRAB"))          // KK_NOGRAB: automated tests, leave the mouse alone
    SDL_SetWindowRelativeMouseMode(SDLWin,true);

  Screen[0].Window = (sU32) SDLWin;
  sSystem->WScreenCount = 1;
  sSetMem(GeoBuffer,0,sizeof(GeoBuffer));
  sSetMem(GeoHandle,0,sizeof(GeoHandle));

  ZBufFormat = 0;
  ZBuffer = 0;
  for(i=0;i<MAX_TEXTURE;i++)
    Textures[i].Flags = 0;
  sSetMem(Setups,0,sizeof(Setups));
  MtrlClearCaches();
  InitScreens();

  sFloatFix();

  if(!InitDS())
    sFatal("could not initialize audio: %s",SDL_GetError());

  // main loop

  sAppHandler(sAPPCODE_CONFIG,0);

  DXDev->BeginScene();
  sAppHandler(sAPPCODE_INIT,0);
  DXDev->EndScene();

  while(MessagePump())
  {
    // debug aid: KK_KEYS="ms:key,ms:key,..." injects key presses (program time,
    // key = single character or ENTER/ESC/SPACE/UP/DOWN/LEFT/RIGHT/MOUSE)
    {
      static const char *keys = getenv("KK_KEYS");
      static const char *kp = keys;
      static sU32 pendingRelease[16];         // keys may be held at the same time
      static sInt releaseAt[16];
      for(sInt pr=0;pr<16;pr++)
      {
        if(pendingRelease[pr] && GetTime()>=releaseAt[pr])
        {
          PushKey(pendingRelease[pr]);
          pendingRelease[pr] = 0;
        }
      }
      while(kp && *kp && atoi(kp)<=GetTime())
      {
        const char *k = strchr(kp,':');
        if(!k) { kp = 0; break; }
        k++;
        sU32 code = 0;
        if(!strncmp(k,"ENTER",5)) code = sKEY_ENTER;
        else if(!strncmp(k,"ESC",3)) code = sKEY_ESCAPE;
        else if(!strncmp(k,"SPACE",5)) code = sKEY_SPACE;
        else if(!strncmp(k,"UP",2)) code = sKEY_UP;
        else if(!strncmp(k,"DOWN",4)) code = sKEY_DOWN;
        else if(!strncmp(k,"LEFT",4)) code = sKEY_LEFT;
        else if(!strncmp(k,"RIGHT",5)) code = sKEY_RIGHT;
        else if(!strncmp(k,"MOUSE",5)) code = sKEY_MOUSEL;
        else code = (k[0]>='a' && k[0]<='z') ? k[0]-32 : k[0];
        fprintf(stderr,"inject key %08x at %d ms\n",code,GetTime());
        PushKey(code);
        {
          const char *h = strchr(k,':');
          const char *c = strchr(k,',');
          sInt pr;
          for(pr=0;pr<15 && pendingRelease[pr];pr++);
          pendingRelease[pr] = code|sKEYQ_BREAK;
          releaseAt[pr] = GetTime() + ((h && (!c || h<c)) ? atoi(h+1) : 100);
        }
        kp = strchr(k,',');
        if(kp) kp++;
      }
    }

    for(i=0;i<KeyIndex;i++)
      sAppHandler(sAPPCODE_KEY,KeyBuffer[i]);
    KeyIndex = 0;

    Render();
    MarkDS();
  }

  ExitDS();
  SDL_Quit();
  _exit(0);   // like the original: no orderly teardown of the engine
}

/****************************************************************************/


void sSystem_::InitScreens()
{
  HRESULT hr;
  D3DPRESENT_PARAMETERS d3dpp;
  sInt i;
  sU32 create;
  sU16 *iblock;
  D3DCAPS9 caps;

  sREGZONE(FlipLock);

  if(!DXD)
  {
    DXD = Direct3DCreate9(D3D_SDK_VERSION);
    if(!DXD)
      sFatal("DirectX 9.0c not present.");
  }

	ZBufFormat=D3DFMT_D24S8;

  Screen[0].SFormat=D3DFMT_A8R8G8B8;
  Screen[0].ZFormat=ZBufFormat;

  WINZERO(d3dpp);
  d3dpp.BackBufferFormat = (D3DFORMAT) Screen[0].SFormat;
  d3dpp.EnableAutoDepthStencil = sFALSE;
  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  if(IntroFlags & sSF_WAITVSYNC)
  {
    d3dpp.BackBufferCount = 2;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
  }
  else
  {
    d3dpp.BackBufferCount = 1;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
  }

  d3dpp.Flags = 0;
  d3dpp.hDeviceWindow = (HWND) Screen[0].Window;

  // Linux: always a windowed swapchain with a fixed backbuffer size; SDL
  // handles (desktop) fullscreen and the presentation scales the image.
  d3dpp.Windowed = TRUE;
  d3dpp.BackBufferWidth = ConfigX;
  d3dpp.BackBufferHeight = ConfigY;
  Screen[0].XSize = ConfigX;
  Screen[0].YSize = ConfigY;

  hr=DXD->GetDeviceCaps(0,D3DDEVTYPE_HAL,&caps);
  sVERIFY(!FAILED(hr));

  if(!DXDev)
  {
    if((caps.PixelShaderVersion&0xffff)==0x0000)
      sFatal("pixel shaders required");

    create = D3DCREATE_HARDWARE_VERTEXPROCESSING;

    hr = DXD->CreateDevice(0,D3DDEVTYPE_HAL,(HWND) Screen[0].Window,create,&d3dpp,&DXDev);
    if(FAILED(hr))
    {
      create = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

      hr = DXD->CreateDevice(0,D3DDEVTYPE_HAL,(HWND) Screen[0].Window,create,&d3dpp,&DXDev);
      if(FAILED(hr))
      {
        sFatal("could not create screen");
      }
    }
    for(i=1;i<FVFMax;i++)
      DXDev->CreateVertexDeclaration(FVFTable[i].Info,&FVFTable[i].Decl);

    // create dummy texture
    sU16 bmp[4*4*4];
    sSetMem(bmp,0,sizeof(bmp));
    AddTexture(4,4,sTF_A8R8G8B8,bmp,1);
  }
  else 
  {
#if !sINTRO_NO_ALT_TAB
    if(DXNormalCube)
    {
      DXNormalCube->Release();
      DXNormalCube = 0;
    }
		if(ZBuffer)
		{
			ZBuffer->Release();
			ZBuffer = 0;
		}
    for(i=0;i<2;i++)
    {
      DXBlockSurface[i]->Release();
      DXBlockSurface[i] = 0;
    }

    for(i=0;i<3;i++)
    {
      if(GeoBuffer[i].VB)
        GeoBuffer[i].VB->Release();
      
      GeoBuffer[i].Init();
    }

		for(i=0;i<MAX_TEXTURE;i++)
		{
			if(Textures[i].Flags & sTIF_RENDERTARGET)
			{
#if LOGGING
        sDPrintF("Release Rendertarget\n");
#endif
				Textures[i].Tex->Release();
				Textures[i].Tex=0;
			}
		}

    DXERROR(DXDev->Reset(&d3dpp));
#endif
  }

// zbuffer
  sInt zBufX = sMax(ConfigX,1024);
  sInt zBufY = sMax(ConfigY, 512);

	DXERROR(DXDev->CreateDepthStencilSurface(zBufX,zBufY,(D3DFORMAT) ZBufFormat,D3DMULTISAMPLE_NONE,0,FALSE,&ZBuffer,0));
	DXERROR(DXDev->SetDepthStencilSurface(ZBuffer));

// initialize gpumask

  if(caps.StencilCaps & D3DSTENCILCAPS_TWOSIDED) GpuMask |= sGPU_TWOSIDESTENCIL;

// init buffer management

  CreateGeoBuffer(0,1,0,MAX_DYNVBSIZE);
  CreateGeoBuffer(1,1,1,MAX_DYNIBSIZE);
  CreateGeoBuffer(2,1,2,MAX_DYNIBSIZE*2);

// set some defaults
  WDeviceLost = 0;

#if !sINTRO_NO_ALT_TAB
  for(i=0;i<MAX_TEXTURE;i++)
	{
		if(Textures[i].Flags & sTIF_RENDERTARGET)
    {
      sHardTex *tex = &Textures[i];
	    DXERROR(DXDev->CreateTexture(tex->XSize,tex->YSize,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&tex->Tex,0));
    }
	}
#endif

  for(i=0;i<2;i++)
    DXDev->CreateOffscreenPlainSurface(16,16,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&DXBlockSurface[i],0);

// create managed resources
  CreateGeoBuffer(3,0,1,2*0x8000/4*6);
  DXERROR(GeoBuffer[3].IB->Lock(0,2*0x8000/4*6,(void **) &iblock,0));
  for(i=0;i<0x8000/6;i++)
    sQuad(iblock,i*4+0,i*4+1,i*4+2,i*4+3);
  DXERROR(GeoBuffer[3].IB->Unlock());
  MakeCubeNormalizer();
  MakeAttenuationVolume();

  DiscardCount[0] = DiscardCount[1] = DiscardCount[2] = 1;

  LastDecl = -1;
  LastVB = -1;
  LastVSize = 0;
  LastIB = -1;
  MtrlReset = sTRUE;

  CurrentTarget = -1;
}

/****************************************************************************/
/***                                                                      ***/
/***   Init/Exit/Debug                                                    ***/
/***                                                                      ***/
/****************************************************************************/

void sSystem_::Exit()
{
  QuitRequested = sTRUE;
}

void sSystem_::Tag()
{
}

/*sNORETURN*/ void sSystem_::Abort(sChar *msg)
{
  if(msg)
  {
    fprintf(stderr,"Fatal Error: %s\n",msg);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Fatal Error",msg,SDLWin);
  }
  ExitProcess(0);
}

void sSystem_::Log(sChar *s)
{
  static sBool verbose = getenv("KK_GAMELOG")!=0;
  if(verbose)
    fputs(s,stderr);
  else if(!sFatality && !sAppHandler(sAPPCODE_DEBUGPRINT,(sDInt) s))
    fputs(s,stderr);
}

sChar *sSystem_::GetCmdLine()
{
  return WCmdLine;
}


/****************************************************************************/
/***                                                                      ***/
/***   Render                                                             ***/
/***                                                                      ***/
/****************************************************************************/


#pragma lekktor(off)


void sSystem_::Progress(sInt done,sInt max)
{
  static sInt lasttime;
  const int step = 3;
  sInt time;
  sRect r;
  IDirect3DSurface9 *backbuffer;
  IDirect3DSwapChain9 *swapchain;

  time = timeGetTime();
  if(time > lasttime+450 || done==max)
  {
    lasttime = time;

    sViewport vp;
    vp.Init();
    SetViewport(vp);
    Clear(sVCF_COLOR);

    sZONE(FlipLock);

    DXDev->GetSwapChain(0,&swapchain);
    swapchain->GetBackBuffer(0,D3DBACKBUFFER_TYPE_MONO,&backbuffer);
    
    r.Init(20+step*0,ConfigY/2-20+step*0,ConfigX-20-step*0,ConfigY/2+20-step*0);
    DXDev->ColorFill(backbuffer,(RECT *)&r,0xffffffff);
    
    r.Init(20+step*1,ConfigY/2-20+step*1,ConfigX-20-step*1,ConfigY/2+20-step*1);
    DXDev->ColorFill(backbuffer,(RECT *)&r,0xff000000);
    
    r.Init(20+step*2,ConfigY/2-20+step*2,ConfigX-20-step*2,ConfigY/2+20-step*2);
    r.x1 = r.x0 + 1 + sMin(max,done)*(r.x1-r.x0-1)/max;
    DXDev->ColorFill(backbuffer,(RECT *)&r,0xffffffff);
    
    swapchain->Release();
    backbuffer->Release();

    DXDev->EndScene();
    DXDev->Present(0,0,0,0);
    DXDev->BeginScene();


    if(!MessagePump())
      ExitProcess(0);
  }
}


void sSystem_::WaitForKey()
{
//  static sInt lasttime;
//  const int step = 3;
//  sInt time;

  while(1)
  {
    sViewport vp;
    vp.Init();
    SetViewport(vp);
    Clear(sVCF_COLOR,0xff000000);

    sZONE(FlipLock);

    DXDev->EndScene();
    DXDev->Present(0,0,0,0);
    DXDev->BeginScene();

    sInt key;
    key = GetAsyncKeyState(VK_SPACE);
    if(key&0x8000)
      break;

    if(!MessagePump())
      ExitProcess(0);
  }
}

#pragma lekktor(on)


/****************************************************************************/

void sSystem_::Render()
{
  static sInt LastTime=-1;
  sInt time,ticks;
  HRESULT hr;

  LastCamera.Init();
  LastMatrix.Init();
  LastViewProject.Init();

#pragma lekktor(off)
  if(WDeviceLost)
  {
#if !sINTRO_NO_ALT_TAB
    Sleep(100);
    hr = DXDev->TestCooperativeLevel();
    if(hr!=D3DERR_DEVICENOTRESET)
      return;
    InitScreens();
    if(WDeviceLost)
      return;
#else
    ExitProcess(0);
#endif
  }
#pragma lekktor(on)

  time = sSystem->GetTime();
  ticks = 0;
  if(LastTime==-1)
    LastTime = time;

  sAppHandler(sAPPCODE_FRAME,0);


  DXERROR(DXDev->BeginScene());
  sAppHandler(sAPPCODE_PAINT,0);
  DXERROR(DXDev->EndScene());


  {
    static sInt dblock = 0;
    D3DLOCKED_RECT lr;

    DXDev->ColorFill(DXBlockSurface[dblock],0,0);
    dblock = 1-dblock;

    DXERROR(DXBlockSurface[dblock]->LockRect(&lr,0,D3DLOCK_READONLY));
    DXBlockSurface[dblock]->UnlockRect();
  }

  // debug aid: KK_SHOT="frame,frame,..." saves the backbuffer as kkshot_<frame>.tga,
  // KK_SHOT_EXIT=1 quits after the last one
  {
    static sInt frame = 0;
    static const char *shots = getenv("KK_SHOT");
    frame++;
    if(shots)
    {
      const char *p = shots;
      sInt last = 0;
      while(*p)
      {
        sInt f = atoi(p);
        sBool byTime = getenv("KK_SHOT_MS")!=0;   // values are milliseconds
        static sInt lastShotTime = -1;
        last = sMax(last,f);
        static sInt firstFrameTime = GetTime();   // KK_SHOT_REL: relative to the first frame
        sInt now = byTime ? GetTime() - (getenv("KK_SHOT_REL") ? firstFrameTime : 0) : frame;
        if(byTime ? (f>lastShotTime && f<=now) : f==frame)
        {
          IDirect3DSurface9 *bb=0,*sysmem=0;
          D3DLOCKED_RECT lr;
          if(SUCCEEDED(DXDev->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&bb)) &&
             SUCCEEDED(DXDev->CreateOffscreenPlainSurface(ConfigX,ConfigY,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM,&sysmem,0)) &&
             SUCCEEDED(DXDev->GetRenderTargetData(bb,sysmem)) &&
             SUCCEEDED(sysmem->LockRect(&lr,0,D3DLOCK_READONLY)))
          {
            char name[64];
            snprintf(name,sizeof(name),"kkshot_%06d.tga",getenv("KK_SHOT_MS") ? GetTime() : frame);
            FILE *out = fopen(name,"wb");
            sU8 hdr[18] = {0,0,2, 0,0,0,0,0, 0,0,0,0, 0,0,0,0, 32,0x28};
            hdr[12] = ConfigX&255; hdr[13] = ConfigX>>8; hdr[14] = ConfigY&255; hdr[15] = ConfigY>>8;
            fwrite(hdr,1,18,out);
            for(sInt y=0;y<ConfigY;y++)
              fwrite(((sU8 *)lr.pBits)+y*lr.Pitch,4,ConfigX,out);
            fclose(out);
            sysmem->UnlockRect();
            fprintf(stderr,"saved %s (t=%d ms)\n",name,GetTime());
            if(byTime) lastShotTime = f;
          }
          if(sysmem) sysmem->Release();
          if(bb) bb->Release();
        }
        while(*p && *p!=',') p++;
        if(*p==',') p++;
      }
      static sInt firstT = GetTime();
      if((getenv("KK_SHOT_MS") ? GetTime() - (getenv("KK_SHOT_REL") ? firstT : 0) : frame)>last && getenv("KK_SHOT_EXIT"))
        Exit();
    }
  }

  hr = DXDev->Present(0,0,0,0);
  FixedTimeFrames++;
  if(hr==D3DERR_DEVICELOST)
    WDeviceLost = 1;
}

void sSystem_::SetGamma(sF32 gamma)
{
  D3DGAMMARAMP ramp;

  sInt i;
  for(i=0;i<256;i++)
    ramp.red[i] = ramp.green[i] = ramp.blue[i] = sFPow(i/255.0f,1.0f/gamma)*0xffff;
  DXDev->SetGammaRamp(0,D3DSGR_NO_CALIBRATION,&ramp);
}

/****************************************************************************/
/****************************************************************************/

void sSystem_::Clear(sU32 flags,sU32 color)
{
  // NOTE: we don't support automatically clear textures fully anymore,
  // because in the current rendering architecture we either set full
  // texture viewports or render to the backbuffer then blit to textures.

  sU32 d3dClear = 0;

  if(flags & sVCF_COLOR)    d3dClear |= D3DCLEAR_TARGET;
  if(flags & sVCF_Z)        d3dClear |= D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL;
  if(flags & sVCF_STENCIL)  d3dClear |= D3DCLEAR_STENCIL;

  if(d3dClear)
    DXDev->Clear(0,0,d3dClear,color,1.0f,0);
}

void sSystem_::SetViewport(const sViewport &vp)
{
  IDirect3DSurface9 *target;
  sInt txs,tys,tgtid;

  CurrentViewport = vp;

  // get target surface and its extents
  if(vp.RenderTarget == sINVALID)
  {
    // get screen extents and target surface
    sInt nr = vp.Screen;

    sVERIFY(nr >= 0 && nr < WScreenCount);
    txs = Screen[nr].XSize;
    tys = Screen[nr].YSize;
    tgtid = -nr - 1;
  }
  else
  {
    // get the target texture and verify that it's a rendertarget
    sVERIFY(vp.RenderTarget >= 0);
    sHardTex *tex = &Textures[vp.RenderTarget];
    sVERIFY(tex->Flags & sTIF_RENDERTARGET);

    // get extents and surface
    txs = tex->XSize;
    tys = tex->YSize;
    tgtid = vp.RenderTarget;
  }

  // if the given window has zero extents, use full surface
  if(!vp.Window.XSize() || !vp.Window.YSize())
  {
    CurrentViewport.Window.x0 = 0;
    CurrentViewport.Window.y0 = 0;
    CurrentViewport.Window.x1 = txs;
    CurrentViewport.Window.y1 = tys;
  }

  ViewportX = CurrentViewport.Window.XSize();
  ViewportY = CurrentViewport.Window.YSize();

  // prepare d3d viewport
  D3DVIEWPORT9 d3dvp;

  d3dvp.X = CurrentViewport.Window.x0;
  d3dvp.Y = CurrentViewport.Window.y0;
  d3dvp.Width = ViewportX;
  d3dvp.Height = ViewportY;
  d3dvp.MinZ = 0.0f;
  d3dvp.MaxZ = 1.0f;

  // set render target and viewport
  if(CurrentTarget != tgtid)
  {
    if(vp.RenderTarget == sINVALID)
    {
      IDirect3DSwapChain9 *swapchain;
      DXERROR(DXDev->GetSwapChain(vp.Screen,&swapchain));
      DXERROR(swapchain->GetBackBuffer(0,D3DBACKBUFFER_TYPE_MONO,&target));
      swapchain->Release();
    }
    else
      DXERROR(Textures[vp.RenderTarget].Tex->GetSurfaceLevel(0,&target));

    DXDev->SetRenderTarget(0,target);
    target->Release();

    CurrentTarget = tgtid;
  }

  DXDev->SetViewport(&d3dvp);
}

void sSystem_::GrabScreen(sInt sourceRT,const sRect &win,sInt tex,sBool stretch)
{
  IDirect3DSurface9 *backbuffer;
  IDirect3DSwapChain9 *swapchain;
  IDirect3DSurface9 *texbuffer;
  sHardTex *ht;

  ht = &Textures[tex];
  if(sourceRT == -1)
  {
	  DXERROR(DXDev->GetSwapChain(0,&swapchain));
	  DXERROR(swapchain->GetBackBuffer(0,D3DBACKBUFFER_TYPE_MONO,&backbuffer));
  }
  else
  {
    DXERROR(Textures[sourceRT].Tex->GetSurfaceLevel(0,&backbuffer));
  }

	DXERROR(ht->Tex->GetSurfaceLevel(0,&texbuffer));

  RECT tgtRect;
  tgtRect.left = 0;
  tgtRect.top = 0;
  tgtRect.right = win.XSize();
  tgtRect.bottom = win.YSize();

  DXERROR(DXDev->StretchRect(backbuffer,(const RECT *)&win,texbuffer,stretch ? 0 : &tgtRect,D3DTEXF_NONE));

  if(sourceRT == -1)
	  swapchain->Release();

  backbuffer->Release();
  texbuffer->Release();
}

void sSystem_::Begin2D(sU32 **buffer,sInt &stride)
{
  IDirect3DSurface9 *backbuffer;
  IDirect3DSwapChain9 *swapchain;
  D3DLOCKED_RECT lr;

	DXERROR(DXDev->GetSwapChain(0,&swapchain));
	DXERROR(swapchain->GetBackBuffer(0,D3DBACKBUFFER_TYPE_MONO,&backbuffer));
  DXERROR(backbuffer->LockRect(&lr,0,0));

	swapchain->Release();
  backbuffer->Release();

  *buffer = (sU32 *) lr.pBits;
  stride = lr.Pitch;
}

void sSystem_::End2D()
{
  IDirect3DSurface9 *backbuffer;
  IDirect3DSwapChain9 *swapchain;

  DXERROR(DXDev->GetSwapChain(0,&swapchain));
	DXERROR(swapchain->GetBackBuffer(0,D3DBACKBUFFER_TYPE_MONO,&backbuffer));
  DXERROR(backbuffer->UnlockRect());

	swapchain->Release();
  backbuffer->Release();
}

void sSystem_::GetTransform(sInt mode,sMatrix &mat)
{
  switch(mode)
  {
  case sGT_VIEW:
    mat = LastCamera;
    break;

  case sGT_MODELVIEW:
    mat = LastMatrix;
    mat.TransR();
    mat.MulA(mat,LastCamera);
    break;

  case sGT_MODEL:
    mat = LastMatrix;
    break;

  case sGT_PROJECT:
    mat = LastProjection;
    break;

  default:
    mat.Init();
    break;
  }
}


/****************************************************************************/
/****************************************************************************/

sInt sSystem_::AddTexture(const sTexInfo &ti)
{
  sInt i;
  sHardTex *tex;

  tex = Textures;
  for(i=0;i<MAX_TEXTURE;i++)
  {
    if(tex->Flags==0)
    {
      tex->RefCount = 1;
      tex->XSize = ti.XSize;
      tex->YSize = ti.YSize;
      tex->Flags = ti.Flags|sTIF_ALLOCATED;
      tex->Format = sTF_A8R8G8B8;
      tex->Tex = 0;

	    if(tex->Flags & sTIF_RENDERTARGET)
	    {
        if(tex->XSize==0)
        {
          tex->XSize = Screen[0].XSize;
          tex->YSize = Screen[0].YSize;
        }

#if LOGGING
        sDPrintF("Create Rendertarget %dx%d\n",tex->XSize,tex->YSize);
#endif
		    DXERROR(DXDev->CreateTexture(tex->XSize,tex->YSize,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&tex->Tex,0));
	    }
	    else
	    {
#if LOGGING
        sDPrintF("Create Texture %dx%d\n",tex->XSize,tex->YSize);
#endif
		    DXERROR(DXDev->CreateTexture(tex->XSize,tex->YSize,0,0,D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,&tex->Tex,0));
        UpdateTexture(i,ti.Bitmap);
	    }

      return i;
    }
    tex++;
  }

  return sINVALID;
}

extern sInt DebugTexMem;

sInt sSystem_::AddTexture(sInt xs,sInt ys,sInt format,sU16 *data,sInt mipcount,sInt miptresh)
{
  sInt i;
  sHardTex *tex;
  static D3DFORMAT formats[] = 
  {
    D3DFMT_UNKNOWN,
    D3DFMT_A8R8G8B8,
    D3DFMT_A8,
    D3DFMT_R16F,
    D3DFMT_A2R10G10B10,
    D3DFMT_Q8W8V8U8,
    D3DFMT_A2W10V10U10,
    D3DFMT_A1R5G5B5,
  };

  sVERIFY(format>0 && format<sTF_MAX);

  tex = Textures;
  for(i=0;i<MAX_TEXTURE;i++)
  {
    if(tex->Flags==0)
    {
      mipcount = sMin(mipcount,sGetPower2(xs));
      mipcount = sMin(mipcount,sGetPower2(ys));
      if(xs & (xs-1) || ys & (ys-1)) // xs/ys not a power of 2? no mips.
        mipcount = 1;

      tex->RefCount = 1;
      tex->XSize = xs;
      tex->YSize = ys;
      tex->Flags = sTIF_ALLOCATED;
      tex->Format = format;
      tex->MipLevels = mipcount;
      tex->Tex = 0;

	    if(data==0)
	    {
        if(tex->XSize==0)
        {
          tex->XSize = Screen[0].XSize;
          tex->YSize = Screen[0].YSize;
        }
        tex->Flags |= sTIF_RENDERTARGET;

#if LOGGING
        sDPrintF("Create Rendertarget %dx%d\n",tex->XSize,tex->YSize);
#endif
        DebugTexMem += tex->XSize * tex->YSize * 4;

        DXDev->EvictManagedResources();
		    DXERROR(DXDev->CreateTexture(tex->XSize,tex->YSize,1,D3DUSAGE_RENDERTARGET,formats[format],D3DPOOL_DEFAULT,&tex->Tex,0));
	    }
	    else
	    {
#if LOGGING
        sDPrintF("Create Texture %dx%d\n",tex->XSize,tex->YSize);
#endif
        DebugTexMem += tex->XSize * tex->YSize * 4 * (mipcount ? 4 : 3) / 3;

        DXERROR(DXDev->CreateTexture(tex->XSize,tex->YSize,mipcount,0,formats[format],D3DPOOL_MANAGED,&tex->Tex,0));
        UpdateTexture(i,data,miptresh);
	    }

      return i;
    }
    tex++;
  }
  return sINVALID;
}

/****************************************************************************/

void sSystem_::AddRefTexture(sInt handle)
{
//  sHardTex *tex;

  if(handle!=sINVALID)
  {
    sVERIFY(handle>=0 && handle<MAX_TEXTURE);
    sVERIFY(Textures[handle].RefCount>0);
    Textures[handle].RefCount++;
  }
}

/****************************************************************************/

void sSystem_::RemTexture(sInt handle)
{
  sHardTex *tex;

  if(handle!=sINVALID)
  {
    sVERIFY(handle>=0 && handle<MAX_TEXTURE);
    tex = &Textures[handle];
    sVERIFY(tex->RefCount>=1);
    tex->RefCount--;
    if(tex->RefCount==0)
    {
      if(tex->Tex)
        tex->Tex->Release();

      tex->Flags = 0;
      tex->Tex = 0;
    }
  }
}

/****************************************************************************/

void sSystem_::GetTextureSize(sInt handle,sInt &w,sInt &h)
{
  if(handle != sINVALID)
  {
    sVERIFY(handle>=0 && handle<MAX_TEXTURE);
    sHardTex *tex = &Textures[handle];
    sVERIFY(tex->RefCount >= 1);

    w = tex->XSize;
    h = tex->YSize;
  }
}

/****************************************************************************/

void sSystem_::MakeCubeNormalizer()
{
  const sInt size = 64;
  sInt i,x,y;
  D3DLOCKED_RECT lr;
  sU8 *p;
  sVector v;

  static sVector faces[6][2] = 
  {
    {{ 0, 0,-1},{ 0, 1, 0}},
    {{ 0, 0, 1},{ 0, 1, 0}},
    {{ 1, 0, 0},{ 0, 0,-1}},
    {{ 1, 0, 0},{ 0, 0, 1}},
    {{ 1, 0, 0},{ 0, 1, 0}},
    {{-1, 0, 0},{ 0, 1, 0}}
  };

	DXERROR(DXDev->CreateCubeTexture(size,1,0,D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,&DXNormalCube,0));
  for(i=0;i<6;i++)
  {
    DXERROR(DXNormalCube->LockRect((D3DCUBEMAP_FACES)i,0,&lr,0,0));
    for(y=0;y<size;y++)
    {
      p = ((sU8*)lr.pBits)+y*lr.Pitch;
      for(x=0;x<size;x++)
      {
        v.Cross3(faces[i][0],faces[i][1]);
        v.Scale3((size-1)*0.5f);
        v.AddScale3(faces[i][0],(x-(size-1)*0.5f));
        v.AddScale3(faces[i][1],(-y+(size-1)*0.5f));
        v.Unit3();
        p[0] = sFtol(128.0f+v.z*127);
        p[1] = sFtol(128.0f+v.y*127);
        p[2] = sFtol(128.0f+v.x*127);
        p[3] = 0;
        p+=4;
      }
    }
    DXERROR(DXNormalCube->UnlockRect((D3DCUBEMAP_FACES)i,0));
  }
}

/****************************************************************************/

void sSystem_::MakeAttenuationVolume()
{
  const sInt size = 32;
  const sF32 scale = 2.0f / (size - 2.0f);
  const sF32 mid = size / 2.0f;
  D3DLOCKED_BOX lb;
  sInt x,y,z;
  sVector v;
  sF32 attn;
  sU8 *p;

  DXERROR(DXDev->CreateVolumeTexture(size,size,size,1,0,D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,&DXAttenuationVolume,0));
  DXERROR(DXAttenuationVolume->LockBox(0,&lb,0,0));

  for(z=0;z<size;z++)
  {
    v.z = (z - mid) * scale;

    for(y=0;y<size;y++)
    {
      v.y = (y - mid) * scale;
      p = ((sU8 *)lb.pBits)+z*lb.SlicePitch+y*lb.RowPitch;

      for(x=0;x<size;x++)
      {
        v.x = (x - mid) * scale;
        attn = sMax(1.0f - v.Dot3(v),0.0f);
        p[0] = p[1] = p[2] = p[3] = sFtol(attn * 255);
        p += 4;
      }
    }
  }

  DXERROR(DXAttenuationVolume->UnlockBox(0));
}

/****************************************************************************/

sBool sSystem_::StreamTextureStart(sInt handle,sInt level,sBitmapLock &lock)
{
  sHardTex *tex;
  IDirect3DTexture9 *mst;
  D3DLOCKED_RECT dxlock;

  tex = &Textures[handle];
  mst = tex->Tex;

  sVERIFY(!DXStreamTexture);
  DXStreamTexture = mst;
  DXStreamLevel = level;

  if(FAILED(mst->LockRect(level,&dxlock,0,0)))
    return sFALSE;

  lock.Data = (sU8 *)dxlock.pBits;
  lock.XSize = tex->XSize>>level;
  lock.YSize = tex->YSize>>level;
  lock.Kind = tex->Format;
  lock.BPR = dxlock.Pitch;

  return sTRUE;
}

/****************************************************************************/

void sSystem_::StreamTextureEnd()
{
  sVERIFY(DXStreamTexture);
  DXStreamTexture->UnlockRect(DXStreamLevel);
  DXStreamTexture=0;
}

/****************************************************************************/
/****************************************************************************/

void sSystem_::SetStates(sU32 *stream)
{
//  DXDev->SetPixelShader(0);
//  DXDev->SetVertexShader(0);
  while(*stream!=0xffffffff)
  {
    if(CurrentStates[stream[0]] != stream[1])
    {
      SetState(stream[0],stream[1]);
      CurrentStates[stream[0]] = stream[1];
    }

    stream+=2;
  }
}

/****************************************************************************/

void sSystem_::SetState(sU32 token,sU32 value)
{
  if(CurrentStates[token] == value)
    return;

  if(token<0x0310)
  {
    if(token<0x0100)
    {
      DXDev->SetRenderState((D3DRENDERSTATETYPE)token,value);
    }
    else if(token<0x0200)
    {
      DXDev->SetTextureStageState(((token>>5)&7),(D3DTEXTURESTAGESTATETYPE)(token&31),value);
    }
    else if(token<0x0300)
    {
      DXDev->SetSamplerState(((token>>4)&15),(D3DSAMPLERSTATETYPE)(token&15),value);
    }
    else if(token<0x0310)
    {
      DXDev->SetSamplerState(D3DDMAPSAMPLER,(D3DSAMPLERSTATETYPE)(token&15),value);
    }
  }

  CurrentStates[token] = value;
}

/****************************************************************************/

void sSystem_::SetScissor(const sFRect *scissor)
{
  RECT rc;

  if(!scissor)
    SetState(sD3DRS_SCISSORTESTENABLE,0);
  else
  {
    rc.left   = CurrentViewport.Window.x0 + (CurrentViewport.Window.x1 - CurrentViewport.Window.x0) * (1.0f + scissor->x0) * 0.5f;
    rc.right  = CurrentViewport.Window.x0 + (CurrentViewport.Window.x1 - CurrentViewport.Window.x0) * (1.0f + scissor->x1) * 0.5f;
    rc.top    = CurrentViewport.Window.y0 + (CurrentViewport.Window.y1 - CurrentViewport.Window.y0) * (1.0f - scissor->y1) * 0.5f;
    rc.bottom = CurrentViewport.Window.y0 + (CurrentViewport.Window.y1 - CurrentViewport.Window.y0) * (1.0f - scissor->y0) * 0.5f;

    DXDev->SetScissorRect(&rc);
    SetState(sD3DRS_SCISSORTESTENABLE,1);
  }
}

/****************************************************************************/
/****************************************************************************/

void sSystem_::CreateGeoBuffer(sInt i,sInt dyn,sInt index,sInt size)
{
  sInt usage;
  D3DPOOL pool;

  sVERIFY(dyn==0 || dyn==1);
  sVERIFY(index>=0 || index<=2);

  GeoBuffer[i].Type = 1+index;
  GeoBuffer[i].Size = size;
  GeoBuffer[i].Used = 0;
  GeoBuffer[i].UserCount = 0;
  GeoBuffer[i].VB = 0;

  usage = D3DUSAGE_WRITEONLY;
  pool = D3DPOOL_MANAGED;
  if(dyn)
  {
    usage |= D3DUSAGE_DYNAMIC;
    pool = D3DPOOL_DEFAULT;
  }

  if(!index)
  {
    DXERROR(DXDev->CreateVertexBuffer(size,usage,0,pool,&GeoBuffer[i].VB,0));
  }
  else
  {
    DXERROR(DXDev->CreateIndexBuffer(size,usage,index == 1 ? D3DFMT_INDEX16 : D3DFMT_INDEX32,pool,&GeoBuffer[i].IB,0));
  }
#if LOGGING
  sDPrintF("Create %s %s-Buffer (%d bytes) id %d\n",dyn?"dynamic":"static",index?"index":"vertex",size,i);
#endif
}

sInt sSystem_::GeoAdd(sInt fvf,sInt prim)
{
  sInt i;
  sGeoHandle *gh;

  sVERIFY(fvf>=1 && fvf<FVFMax);
  for(i=1;i<MAX_GEOHANDLE;i++)
  {
    gh = &GeoHandle[i];
    if(gh->Mode==0)
    {
      sSetMem(gh,0,sizeof(*gh));
      gh->VertexSize = FVFTable[fvf].Size;
      gh->FVF = fvf;
      gh->Mode = prim;
      gh->Locked = 0;
      return i;
    }
  }
  sFatal("GeoAdd() ran out of handles");
	return 0;
}

void sSystem_::GeoRem(sInt handle)
{
  sVERIFY(handle>=1 && handle<MAX_GEOHANDLE);
  sVERIFY(GeoHandle[handle].Mode!=0);

  if(GeoHandle[handle].Vertex.Buffer>=4)
    GeoBuffer[GeoHandle[handle].Vertex.Buffer].Free();
  if(GeoHandle[handle].Index.Buffer>=4)
    GeoBuffer[GeoHandle[handle].Index.Buffer].Free();
  GeoHandle[handle].Mode = 0;
}

void sSystem_::GeoFlush()
{
  sInt i;

  for(i=1;i<MAX_GEOHANDLE;i++)
    GeoHandle[i].Vertex.Count = 0;
  for(i=3;i<MAX_GEOBUFFER;i++)
  {
    if(GeoBuffer[i].VB)
      GeoBuffer[i].VB->Release();
    GeoBuffer[i].Init();
  }
}

void sSystem_::GeoFlush(sInt handle,sInt what)
{
  sVERIFY(handle>=1 && handle<MAX_GEOHANDLE);
  if(what & sGEO_VERTEX)  GeoHandle[handle].Vertex.DiscardCount = 0;
  if(what & sGEO_INDEX)   GeoHandle[handle].Index.DiscardCount = 0;
}

sInt sSystem_::GeoDraw(sInt &handle)
{
  sGeoHandle *gh;
  D3DPRIMITIVETYPE mode;
  sInt count;
  sInt update;

// buffer correctly loaded?

  sVERIFY(handle>=1 && handle<MAX_GEOHANDLE);
  sVERIFY(GeoHandle[handle].Mode!=0);

  gh = &GeoHandle[handle];
  update = 0;

  if(gh->Vertex.Count == 0)
    update |= sGEO_VERTEX | sGEO_INDEX;
  if(gh->Vertex.Buffer == 0 && gh->Vertex.DiscardCount != DiscardCount[0])
    update |= sGEO_VERTEX;
  if(gh->Index.Buffer == 1 && gh->Index.DiscardCount != DiscardCount[1])
    update |= sGEO_INDEX;
  if(gh->Index.Buffer == 2 && gh->Index.DiscardCount != DiscardCount[2])
    update |= sGEO_INDEX;

  if(update)
    return update;

// set up buffers
  if(gh->FVF != LastDecl)
  {
    DXDev->SetVertexDeclaration(FVFTable[gh->FVF].Decl);
    LastDecl = gh->FVF;
  }

  if(gh->Index.Count && LastIB != gh->Index.Buffer)
  {
    sInt ib = gh->Index.Buffer;

    sVERIFY(ib>=0 && ib<MAX_GEOBUFFER);
    sVERIFY(GeoBuffer[ib].Type >= 2 && GeoBuffer[ib].Type <= 3);
    sVERIFY(GeoBuffer[ib].IB);
    DXDev->SetIndices(GeoBuffer[ib].IB);
    LastIB = ib;
  }
  if(LastVB != gh->Vertex.Buffer || LastVSize != gh->VertexSize)
  {
    sInt vb = gh->Vertex.Buffer;

    sVERIFY(vb>=0 && vb<MAX_GEOBUFFER);
    sVERIFY(GeoBuffer[vb].Type == 1);
    sVERIFY(GeoBuffer[vb].VB);
    DXDev->SetStreamSource(0,GeoBuffer[vb].VB,0,gh->VertexSize);
    LastVB = vb;
    LastVSize = gh->VertexSize;
  }

// start drawing

  count = gh->Index.Count;
  if(count == 0)
    count = gh->Vertex.Count;


  switch(gh->Mode&7)
  {
  case sGEO_POINT:
    mode = D3DPT_POINTLIST;
    count = count;
    sVERIFY(gh->Index.Count==0);
    break;
  case sGEO_LINE:
    mode = D3DPT_LINELIST;
    count = count/2;
    break;
  case sGEO_LINESTRIP:
    mode = D3DPT_LINESTRIP;
    count = count-1;
    break;
  case sGEO_TRI:
    mode = D3DPT_TRIANGLELIST;
    count = count/3;
    break;
  case sGEO_TRISTRIP:
    mode = D3DPT_TRIANGLESTRIP;
    count = count-2;
    break;
  case sGEO_QUAD:
    sVERIFY(gh->Index.Count==0);
    LastIB = 3;
    DXDev->SetIndices(GeoBuffer[3].IB);
    DXDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,gh->Vertex.Start,0,gh->Vertex.Count,0,count/4*2);
    return sFALSE;
  default:
    sVERIFYFALSE;
  }
  
  if(gh->Index.Count)
    DXDev->DrawIndexedPrimitive(mode,gh->Vertex.Start,0,gh->Vertex.Count,gh->Index.Start,count);
  else if(count)
    DXDev->DrawPrimitive(mode,gh->Vertex.Start,count);

  return sFALSE;
}

void sSystem_::AllocBufferInternal(sGeoBufferRef &ref,sInt size,sBool stat,sInt index,void **ptr)
{
  sInt i,lockf;
  sBool ok;

  if(stat) // static buffer
  {
    for(i=4;i<MAX_GEOBUFFER;i++)
      if(GeoBuffer[i].Alloc(ref.Count,size,ref.Start,index+1))
        break;

    if(i == MAX_GEOBUFFER)
    {
      for(i=4;i<MAX_GEOBUFFER;i++)
      {
#pragma lekktor(off)
        if(GeoBuffer[i].Type == 0)
        {
          sInt bufSize = index ? MAX_DYNIBSIZE * index : MAX_DYNVBSIZE;
          if(bufSize < ref.Count * size)
            bufSize = ref.Count * size;

          CreateGeoBuffer(i,0,index,bufSize);
          ok = GeoBuffer[i].Alloc(ref.Count,size,ref.Start,index+1);
          sVERIFY(ok);
          break;
#pragma lekktor(on)
        }
      }

      if(i == MAX_GEOBUFFER)
        sFatal("AllocInternal(): out of static geobuffers");
    }

    ref.Buffer = i;
    lockf = 0;
  }
  else // dynamic buffer
  {
    ok = GeoBuffer[index].Alloc(ref.Count,size,ref.Start,index+1);
    ref.Buffer = index;

    if(!ok)
    {
#pragma lekktor(off)
      GeoBuffer[index].Used = 0;
      DiscardCount[index]++;
      ok = GeoBuffer[index].Alloc(ref.Count,size,ref.Start,index+1);
      sVERIFY(ok);
#pragma lekktor(on)
    }

    ref.DiscardCount = DiscardCount[index];
    lockf = ref.Start ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD;
  }
  
  DXERROR(GeoBuffer[ref.Buffer].VB->Lock(ref.Start*size,ref.Count*size,(void **)ptr,lockf));
}

void sSystem_::GeoBegin(sInt handle,sInt vc,sInt ic,sF32 **fp,void **ip,sInt upd)
{
  sGeoHandle *gh;

  sVERIFY(handle>=1 && handle<MAX_GEOHANDLE);
  sVERIFY(GeoHandle[handle].Mode!=0);
  sVERIFY(ic*2<=MAX_DYNIBSIZE);

  gh = &GeoHandle[handle];

  if(fp)
    *fp = 0;
  if(ip)
    *ip = 0;

  if(upd & sGEO_VERTEX)
  {
    if(gh->Vertex.Buffer>=4)
      GeoBuffer[gh->Vertex.Buffer].Free();

    gh->Vertex.Buffer = 0;
    gh->Vertex.Start = 0;
    gh->Vertex.Count = vc;

    AllocBufferInternal(gh->Vertex,gh->VertexSize,gh->Mode & sGEO_STATVB,0,(void **)fp);
    gh->Locked |= sGEO_VERTEX;

    sVERIFY(vc*GeoHandle[handle].VertexSize <= GeoBuffer[gh->Vertex.Buffer].Size);
  }

  if(upd & sGEO_INDEX)
  {
    if(gh->Index.Buffer>=4)
      GeoBuffer[gh->Index.Buffer].Free();

    gh->Index.Buffer = 0;
    gh->Index.Start = 0;
    gh->Index.Count = ic;

    if(ic)
    {
      sBool is32b = (gh->Mode & sGEO_IND32B);

      AllocBufferInternal(gh->Index,is32b ? 4 : 2,gh->Mode & sGEO_STATIB,is32b ? 2 : 1,(void **)ip);
      gh->Locked |= sGEO_INDEX;
    }
  }
}

void sSystem_::GeoEnd(sInt handle,sInt vc,sInt ic)
{
  sGeoHandle *gh;
//  sBool load;

  sVERIFY(handle>=1 && handle<MAX_GEOHANDLE);
  sVERIFY(GeoHandle[handle].Mode!=0);

  gh = &GeoHandle[handle];

  if(gh->Locked & sGEO_VERTEX)
  {
    GeoBuffer[gh->Vertex.Buffer].VB->Unlock();
    gh->Locked &= ~sGEO_VERTEX;
  }

  if(gh->Locked & sGEO_INDEX)
  {
    GeoBuffer[gh->Index.Buffer].IB->Unlock();
    gh->Locked &= ~sGEO_INDEX;
  }

  if(vc!=-1)
    gh->Vertex.Count = vc;
  if(ic!=-1)
    gh->Index.Count = ic;
}

/****************************************************************************/
/****************************************************************************/


/****************************************************************************/
/****************************************************************************/

void sSystem_::FlushTexture(sInt handle)
{
  sHardTex *tex;

  sVERIFY(handle>=0 && handle<MAX_TEXTURE);
  tex = &Textures[handle];
  sVERIFY(tex->Flags);

  if(tex->Tex)
  {
    tex->Tex->Release();
    tex->Tex = 0;
  }
}

/****************************************************************************/

void sSystem_::UpdateTexture(sInt handle,sBitmap *bm)
{
  sHardTex *tex;
  sInt xs,ys,level;
  sInt miptresh;
  sInt mipdir;
  sInt filter;
  IDirect3DTexture9 *mst;
  D3DLOCKED_RECT dxlock;

  sInt x,y;
  sInt bpr,oxs;
  sU32 *d,*s,*data;
  sU8 *db,*sb;

  miptresh = 0;
  tex = &Textures[handle];
  mst = tex->Tex;
  mipdir = miptresh & 16;
  miptresh = miptresh & 15;

  sVERIFY(bm->XSize == tex->XSize);
  sVERIFY(bm->YSize == tex->YSize);

	if(!(tex->Flags & sTIF_RENDERTARGET))
	{
		xs = tex->XSize;
		ys = tex->YSize;
		oxs = xs;
		level = 0;

		data = new sU32[xs*ys];
		sCopyMem4(data,bm->Data,xs*ys);

    {    
      for(;;)
		  {
        if(FAILED(mst->LockRect(level,&dxlock,0,0)))
          break;
        bpr = dxlock.Pitch;
			  d = (sU32 *)dxlock.pBits;
			  s = data;
			  for(y=0;y<ys;y++)
			  {
				  sCopyMem4(d,s,xs);
				  d+=bpr/4;
				  s+=oxs;
			  }
        mst->UnlockRect(level);
			  if(xs<=1 || ys<=1)
				  break;
  	    
        filter = (miptresh <= level);
        if(mipdir) filter = !filter;

			  s = data;
			  d = data;
			  for(y=0;y<ys/2;y++)
			  {
				  sb = (sU8 *) s;
				  db = (sU8 *) d;
				  s+=oxs*2;
				  d+=oxs;
				  for(x=0;x<xs/2;x++)
				  {
            if(filter)
            {
					    db[0] = (sb[0]+sb[4]+sb[oxs*4+0]+sb[oxs*4+4]+2)>>2;
					    db[1] = (sb[1]+sb[5]+sb[oxs*4+1]+sb[oxs*4+5]+2)>>2;
					    db[2] = (sb[2]+sb[6]+sb[oxs*4+2]+sb[oxs*4+6]+2)>>2;
					    db[3] = (sb[3]+sb[7]+sb[oxs*4+3]+sb[oxs*4+7]+2)>>2;
            }
            else
            {
					    db[0] = sb[0];
					    db[1] = sb[1];
					    db[2] = sb[2];
					    db[3] = sb[3];
            }
					  db+=4;
					  sb+=8;
				  }
			  }

			  xs=xs>>1;
			  ys=ys>>1;
			  level++;
		  }
    }
	  delete[] data;
	}
}

/****************************************************************************/

void sSystem_::UpdateTexture(sInt handle,sU16 *source,sInt miptresh)
{
  sHardTex *tex;
  IDirect3DTexture9 *mst;
  D3DLOCKED_RECT dxlock;
  sInt xs,ys,level;
  sInt mipdir;
  sInt filter;
  sInt alpha;

  sInt x,y;
  sInt bpr,oxs;
  sU32 *d,*s,*data;
  sU16 *d16,*s16;
//  sU8 *d8;

  mipdir = miptresh & 16;
  alpha = miptresh & 32;
  miptresh = miptresh & 15;
 
  tex = &Textures[handle];
  mst = tex->Tex;

	if(!(tex->Flags & sTIF_RENDERTARGET))
	{
		xs = tex->XSize;
		ys = tex->YSize;
		oxs = xs;
		level = 0;

		data = new sU32[xs*ys*2];
		sCopyMem4(data,(sU32 *)source,xs*ys*2);

    {
      for(;;)
		  {
        if(FAILED(mst->LockRect(level,&dxlock,0,0)))
          break;
        bpr = dxlock.Pitch;
			  d = (sU32 *)dxlock.pBits;
			  s = data;
			  for(y=0;y<ys;y++)
			  {
          if(tex->Format==sTF_Q8W8V8U8)
          {
            s16 = (sU16 *)s;
            for(x=0;x<xs;x++)
            {
              d[x] = (((((sInt)s16[2]-0x4000)>>7)&0xff)    ) | 
                    (((((sInt)s16[1]-0x4000)>>7)&0xff)<< 8) | 
                    (((((sInt)s16[0]-0x4000)>>7)&0xff)<<16) | 
                    (((((sInt)s16[3]-0x4000)>>7)&0xff)<<24);

              s16+=4;
            }
          }
          else
          {
            s16 = (sU16 *)s;
            for(x=0;x<xs;x++)
            {
              d[x] = (((s16[0]>>7)&0xff)    ) | 
                      (((s16[1]>>7)&0xff)<< 8) | 
                      (((s16[2]>>7)&0xff)<<16) | 
                      (((s16[3]>>7)&0xff)<<24);
              s16+=4;
            }
          }

          /*
          switch(tex->Format+alpha)
          {
          case sTF_A8R8G8B8:
            s16 = (sU16 *)s;
            for(x=0;x<xs;x++)
            {
              d[x] = (((s16[0]>>7)&0xff)    ) | 
                     (((s16[1]>>7)&0xff)<< 8) | 
                     (((s16[2]>>7)&0xff)<<16) | 
                     (((s16[3]>>7)&0xff)<<24);
              s16+=4;
            }
            break;

          case sTF_A8R8G8B8+32:
            s16 = (sU16 *)s;
            for(x=0;x<xs;x++)
            {
              d[x] = (((s16[0]>>7)&0xff)    ) | 
                     (((s16[1]>>7)&0xff)<< 8) | 
                     (((s16[2]>>7)&0xff)<<16) | 
                     (s16[3]>0x4000?0xff000000:0);
              s16+=4;
            }
            break;

          case sTF_A8:
            s16 = (sU16 *)s;
            d8 = (sU8 *)d;

            for(x=0;x<xs;x++)
            {
              d8[x] = (((s16[3]>>7)&0xff)    );
              s16+=4;
            }
            break;

          case sTF_A8+32:
            s16 = (sU16 *)s;
            d8 = (sU8 *)d;

            for(x=0;x<xs;x++)
            {
              d8[x] = s16[3]>0x4000?0xff:0;
              s16+=4;
            }
            break;

          case sTF_Q8W8V8U8:
          case sTF_Q8W8V8U8+32:
            s16 = (sU16 *)s;
            for(x=0;x<xs;x++)
            {
              d[x] = (((((sInt)s16[2]-0x4000)>>7)&0xff)    ) | 
                    (((((sInt)s16[1]-0x4000)>>7)&0xff)<< 8) | 
                    (((((sInt)s16[0]-0x4000)>>7)&0xff)<<16) | 
                    (((((sInt)s16[3]-0x4000)>>7)&0xff)<<24);
              s16+=4;
            }
            break;
          }
*/
				  d+=bpr/4;
				  s+=oxs*2;
			  }
        mst->UnlockRect(level);

        if(xs<=1 || ys<=1 || (tex->MipLevels && level+1>=tex->MipLevels))
				  break;

        filter = (miptresh <= level);
        if(mipdir) filter = !filter;


			  s = data;
			  d = data;
			  for(y=0;y<ys/2;y++)
			  {
				  s16 = (sU16 *) s;
				  d16 = (sU16 *) d;
				  s+=oxs*4;
				  d+=oxs*2;
				  for(x=0;x<xs/2;x++)
				  {
            if(filter)
            {
					    d16[0] = (s16[0]+s16[4]+s16[oxs*4+0]+s16[oxs*4+4]+2)>>2;
					    d16[1] = (s16[1]+s16[5]+s16[oxs*4+1]+s16[oxs*4+5]+2)>>2;
					    d16[2] = (s16[2]+s16[6]+s16[oxs*4+2]+s16[oxs*4+6]+2)>>2;
					    d16[3] = (s16[3]+s16[7]+s16[oxs*4+3]+s16[oxs*4+7]+2)>>2;
            }
            else
            {
              d16[0] = s16[0];
					    d16[1] = s16[1];
					    d16[2] = s16[2];
					    d16[3] = s16[3];
            }
					  d16+=4;
					  s16+=8;
				  }
			  }

			  xs=xs>>1;
			  ys=ys>>1;
			  level++;
		  }
    }
	  delete[] data;
	}
}

void sSystem_::ReadTexture(sInt handle,sU16 *dest)
{
  sHardTex *tex;
  IDirect3DTexture9 *mst;
  IDirect3DSurface9 *surf;
  IDirect3DSurface9 *rsurf;
  IDirect3DSurface9 *tsurf;
  D3DLOCKED_RECT dxlock;
  sInt xs,ys;

  sInt x,y;
  sInt bpr;
  sU32 *s;
 
  tex = &Textures[handle];
  mst = tex->Tex;
  DXERROR(mst->GetSurfaceLevel(0,&tsurf));
  DXERROR(DXDev->CreateRenderTarget(tex->XSize,tex->YSize,D3DFMT_A8R8G8B8,D3DMULTISAMPLE_NONE,0,1,&rsurf,0));
  DXERROR(DXDev->CreateOffscreenPlainSurface(tex->XSize,tex->YSize,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM,&surf,0));
  DXERROR(DXDev->StretchRect(tsurf,0,rsurf,0,D3DTEXF_NONE));
  DXERROR(DXDev->GetRenderTargetData(rsurf,surf));

  xs = tex->XSize;
  ys = tex->YSize;

  DXERROR(surf->LockRect(&dxlock,0,0));

  bpr = dxlock.Pitch;
  s = (sU32 *)dxlock.pBits;
  for(y=0;y<ys;y++)
  {
    for(x=0;x<xs;x++)
    {
      sU32 val = s[x];
      for(sInt i=0;i<4;i++)
      {
        sU32 bits = ((val>>(i*8))&255);
        dest[i] = (bits<<7) | (bits>>1);
      }
      dest+=4;
    }
	  s+=bpr/4;
  }
  surf->UnlockRect();
  sRelease(surf);
  sRelease(rsurf);
  sRelease(tsurf);
}


/****************************************************************************/
/****************************************************************************/
/***                                                                      ***/
/***   Input                                                              ***/
/***                                                                      ***/
/****************************************************************************/
/****************************************************************************/


/****************************************************************************/
/***                                                                      ***/
/***   Windows User Interface Access                                      ***/
/***                                                                      ***/
/****************************************************************************/


/****************************************************************************/
/***                                                                      ***/
/***   Misc Input/Timing stuff                                            ***/
/***                                                                      ***/
/****************************************************************************/

void sSystem_::GetInput(sInt id,sInputData &data)
{
  // the original warped the cursor to (400,300) every frame and summed up
  // the deltas; SDL's relative mouse mode gives us those deltas directly.
  static sInt x,y;
  x += MouseRelX;
  y += MouseRelY;
  MouseRelX = MouseRelY = 0;
  data.Analog[0]=x;
  data.Analog[1]=y;
}

#if !defined(KK_SMALL) || defined(KK_COVERAGE)
unsigned long long kkNanoTime() { return SDL_GetTicksNS(); }   // KK_FRAMELOG
#endif

sInt sSystem_::GetTime()
{
  if(FixedTime())
    return FixedTimeFrames*FixedTimeStep;
  return timeGetTime()-WStartTime;
}

/****************************************************************************/
/***                                                                      ***/
/***   Sound                                                              ***/
/***                                                                      ***/
/****************************************************************************/

#define DXSSAMPLES 0x20000

sBool sSystem_::InitDS()
{
  SDL_AudioSpec spec;
  spec.format = SDL_AUDIO_S16LE;
  spec.channels = 2;
  spec.freq = 44100;

  // ~23ms device buffer, comparable to the DirectSound setup
  SDL_SetHint(SDL_HINT_AUDIO_DEVICE_SAMPLE_FRAMES,"1024");

  AudioStream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,&spec,AudioCallback,0);
  if(!AudioStream)
    return sFALSE;

  Listener3D.Pos.Init(0,0,0,0);
  Listener3D.Up.Init(0,1,0,0);
  Listener3D.Fwd.Init(0,0,1,0);
  Listener3D.Rolloff = 1.0f;

  SoundTime = 1;
  SDL_ResumeAudioStreamDevice(AudioStream);
  return sTRUE;
}

/****************************************************************************/

void sSystem_::ExitDS()
{
  if(AudioStream)
  {
    SDL_DestroyAudioStream(AudioStream);
    AudioStream = 0;
  }
  SampleRemAll();
}

/****************************************************************************/

void sSystem_::MarkDS()
{
  // only GetCurrentSample() (werkkzeug's timeline) needs this; taking the
  // stream lock every frame made the game wait for the synth. Approximate.
  DXSLastTotalSample = AudioFramesOut;
}

/****************************************************************************/

void sSystem_::SetSoundHandler(sSoundHandler hnd,sInt align,void *user)
{
  if(!AudioStream) return;
  SDL_LockAudioStream(AudioStream);

  DXSHandler = hnd;           // 0 = silence (DSNullHandler in the original)
  if(align<=0)
    align=64;
  DXSHandlerAlign = align;
  DXSHandlerUser = user;
  DXSLastTotalSample = 0;
  AudioFramesOut = 0;

  SDL_UnlockAudioStream(AudioStream);
}

/****************************************************************************/

sInt sSystem_::GetCurrentSample()
{
  return DXSLastTotalSample;
}

/****************************************************************************/
/***                                                                      ***/
/***   Sample Player (software replacement for DirectSound buffers)       ***/
/***                                                                      ***/
/****************************************************************************/

// DirectSound volume/pan are in 1/100 dB. The original converted a linear
// volume with ln() instead of log10() - keep that, it defines the mix.
static sF32 MBToGain(sInt mb)
{
  if(mb<=-10000) return 0.0f;
  return (sF32) pow(10.0,mb/2000.0);
}

static void MixVoices(sS16 *out,sInt frames)
{
  static sInt mix[4096*2];
  sInt i,j,k,n,active;
  sSample *sam;
  sSampleBuffer *buf;

  if(!sSystem) return;
  active = 0;
  for(i=0;i<sMAXSAMPLEHANDLE;i++)
  {
    sam = &sSystem->Sample[i];
    for(j=0;j<sam->Count;j++)
    {
      buf = &sam->Buffers[j];
      sInt pos = *(volatile sInt *)&buf->Pos;   // SamplePlay may restart it any time
      if(pos<0) continue;

      if(!active)
      {
        for(k=0;k<frames*2;k++) mix[k] = out[k];
        active = 1;
      }

      sF32 gl,gr;
      if(sam->Is3D && buf->Mode3D)
      {
        gl = buf->Volume*buf->Gain3D[0];
        gr = buf->Volume*buf->Gain3D[1];
      }
      else
      {
        gl = buf->Volume*buf->Gain[0];
        gr = buf->Volume*buf->Gain[1];
      }
      sInt il = (sInt)(gl*65536.0f), ir = (sInt)(gr*65536.0f);

      n = sMin<sInt>(frames,sam->Frames-pos);
      if(sam->Channels==1)
      {
        const sS16 *s = sam->Data + pos;
        for(k=0;k<n;k++)
        {
          mix[k*2+0] += (s[k]*il)>>16;
          mix[k*2+1] += (s[k]*ir)>>16;
        }
      }
      else
      {
        const sS16 *s = sam->Data + pos*2;
        for(k=0;k<n;k++)
        {
          mix[k*2+0] += (s[k*2+0]*il)>>16;
          mix[k*2+1] += (s[k*2+1]*ir)>>16;
        }
      }
      // advance, unless SamplePlay restarted the buffer meanwhile
      __sync_bool_compare_and_swap(&buf->Pos,pos,(pos+n>=sam->Frames) ? -1 : pos+n);
    }
  }
  if(active)
    for(k=0;k<frames*2;k++)
      out[k] = sRange<sInt>(mix[k],0x7fff,-0x8000);
}

sInt sSystem_::SampleAdd(sS16 *data,sInt size,sInt buffers,sInt handle,sBool is3d)
{
  sInt i;
  sSample *sam;

  sVERIFY(buffers>=1 && buffers<=sMAXSAMPLEBUFFER);
#if !defined(KK_SMALL) || defined(KK_COVERAGE)
  if(getenv("KK_SOUNDLOG"))             // debug: sound effects as rendered at load
  {
    sInt peak = 0;
    for(i=0;i<size*2;i++) peak = sMax<sInt>(peak,sAbs(data[i]));
    fprintf(stderr,"sound: add %d size %d peak %d 3d %d\n",handle,size,peak,is3d);
  }
#endif
  if(handle==sINVALID)
  {
    for(i=0;i<sMAXSAMPLEHANDLE;i++)
    {
      if(Sample[i].Count==0)
      {
        handle = i;
        break;
      }
    }
  }
  else
  {
    sVERIFY(handle>=0 && handle<sMAXSAMPLEHANDLE);
    if(Sample[handle].Count!=0)
      handle = sINVALID;
  }

  if(handle!=sINVALID)
  {
    sS16 *copy;
    if(!is3d)                         // stereo samples are kept as they are
    {
      copy = new sS16[size*2];
      sCopyMem(copy,data,size*4);
    }
    else                              // 3d buffers are mono: downmix
    {
      copy = new sS16[size];
      for(i=0;i<size;i++)
        copy[i] = (data[i*2+0] + data[i*2+1]) >> 1;
    }

    if(AudioStream) SDL_LockAudioStream(AudioStream);
    sam = &Sample[handle];
    sam->Data = copy;
    sam->Frames = size;
    sam->Channels = is3d ? 1 : 2;
    for(i=0;i<buffers;i++)
    {
      sSetMem(&sam->Buffers[i],0,sizeof(sSampleBuffer));
      sam->Buffers[i].Pos = -1;
      sam->Buffers[i].Volume = 1.0f;
      sam->Buffers[i].Gain[0] = sam->Buffers[i].Gain[1] = 1.0f;
    }
    sam->LRU = 0;
    sam->Count = buffers;
    sam->Uses = 0;
    sam->Is3D = is3d;
    if(is3d) Num3DSamples++;
    sam->LenMs = sMulDiv(size*(is3d?2:4),1000,44100*(is3d?2:4)) + 10;
    if(AudioStream) SDL_UnlockAudioStream(AudioStream);
  }
  return handle;
}


void sSystem_::SampleRem(sInt handle)
{
  sSample *sam;
  sVERIFY(handle>=0 && handle<sMAXSAMPLEHANDLE);

  if(AudioStream) SDL_LockAudioStream(AudioStream);
  sam = &Sample[handle];
  if(sam->Count && sam->Is3D)
    Num3DSamples--;
  if(sam->Count)
    delete[] sam->Data;
  sam->Data = 0;
  sam->Count = 0;
  sam->LRU = 0;
  if(AudioStream) SDL_UnlockAudioStream(AudioStream);
}

void sSystem_::SampleRemAll()
{
  sInt i;
  for(i=0;i<sMAXSAMPLEHANDLE;i++)
    SampleRem(i);
}

static sInt lin2d3d(sF32 volume)
{
  volume = sRange(volume,1.0f,1e-20f);
  return sMax<sInt>(sFLog(volume)*20*100,-10000);
}

sInt sSystem_::SamplePlay(sInt handle,sF32 volume,sF32 pan,sInt freq)
{
  sSample *sam;
  sSampleBuffer *buf;
  sInt d3dpan,r;

  sVERIFY(handle>=0 && handle<sMAXSAMPLEHANDLE);
  sam = &Sample[handle];
#if !defined(KK_SMALL) || defined(KK_COVERAGE)
  if(getenv("KK_SOUNDLOG"))             // debug: sound effect calls
    fprintf(stderr,"sound: play %d vol %.2f (%d buffers) t=%d\n",handle,volume,sam->Count,GetTime());
#endif
  if(sam->Count>0)
  {
    // no stream lock: the audio callback holds it while it renders the music,
    // so locking here made the game wait for the synth (frame time spikes).
    // Set the buffer up, then (re)start it by storing Pos last (see MixVoices)
    d3dpan = sRange<sInt>(pan*100,10000,-10000);

    sam->LRU = (sam->LRU+1)%sam->Count;
    buf = &sam->Buffers[sam->LRU];

    buf->Volume = MBToGain(lin2d3d(volume));
    if(!sam->Is3D)
    {
      buf->Gain[0] = d3dpan>0 ? MBToGain(-d3dpan) : 1.0f;
      buf->Gain[1] = d3dpan<0 ? MBToGain( d3dpan) : 1.0f;
    }
    buf->PlayTime = SoundTime;
    __atomic_store_n(&buf->Pos,0,__ATOMIC_RELEASE);
    r = ++sam->Uses;
    return r;
  }
  else
    return -1;
}

// DirectSound3D "normal" mode, reduced to what matters here:
// inverse distance rolloff between min/max distance and a simple pan law.
static void Calc3DGain(sSampleBuffer *buf)
{
  sVector d,right;
  sF32 dist,g,p,len;

  d.Sub3(buf->Pos3D,Listener3D.Pos);
  dist = d.Abs3();
  if(dist<buf->MinDist) dist = buf->MinDist;
  if(dist>buf->MaxDist) dist = buf->MaxDist;
  g = (dist>0) ? (sF32) pow(buf->MinDist/dist,Listener3D.Rolloff) : 1.0f;

  right.Cross3(Listener3D.Up,Listener3D.Fwd);
  len = right.Abs3();
  p = 0;
  if(len>1e-6f && d.Abs3()>1e-6f)
    p = right.Dot3(d)/(len*d.Abs3());
  buf->Gain3D[0] = g*sMin(1.0f,1.0f-p);
  buf->Gain3D[1] = g*sMin(1.0f,1.0f+p);
}

void sSystem_::Sample3DParam(sInt handle,sInt bufnum,const sVector &pos,const sVector &vel,sF32 minDist,sF32 maxDist)
{
  sSample *sam;
  sSampleBuffer *buf;

  sVERIFY(handle>=0 && handle<sMAXSAMPLEHANDLE);
  sam = &Sample[handle];

  if(sam->Is3D && sam->Uses - bufnum < sam->Count) // if buffer has not been reallocated yet
  {
    bufnum %= sam->Count;
    buf = &sam->Buffers[bufnum];
    if(buf->PlayTime) // if buffer hasn't been stopped yet
    {
      if(AudioStream) SDL_LockAudioStream(AudioStream);
      buf->Pos3D = pos;
      buf->MinDist = minDist;
      buf->MaxDist = maxDist;
      buf->Mode3D = 1;
      Calc3DGain(buf);
      if(AudioStream) SDL_UnlockAudioStream(AudioStream);
    }
  }
}

void sSystem_::Sample3DListener(const sVector &pos,const sVector &vel,const sVector &up,const sVector &fwd,sF32 doppler,sF32 rolloff)
{
  Listener3D.Pos = pos;
  Listener3D.Up = up;
  Listener3D.Fwd = fwd;
  Listener3D.Rolloff = rolloff;
}

void sSystem_::Sample3DCommit()
{
  sInt i,j;
  sSample *sam;
  sSampleBuffer *buf;

  sZONE(Sound3D);

  if(!Num3DSamples)                      // the 2004 sound effects are all 2d
    return;
  if(AudioStream) SDL_LockAudioStream(AudioStream);
  for(i=0;i<sMAXSAMPLEHANDLE;i++)
  {
    sam = &Sample[i];
    if(sam->Is3D)
    {
      for(j=0;j<sam->Count;j++)
      {
        buf = &sam->Buffers[j];

        // disable hanging 3d sounds
        if(buf->PlayTime && buf->PlayTime + sam->LenMs < SoundTime)
        {
          buf->PlayTime = 0;
          buf->Mode3D = 0;
        }
        // deferred listener settings get applied to all 3d buffers
        if(buf->Mode3D)
          Calc3DGain(buf);
      }
    }
  }
  if(AudioStream) SDL_UnlockAudioStream(AudioStream);
  SoundTime = sSystem->GetTime();
}

/****************************************************************************/
/***                                                                      ***/
/***   File                                                               ***/
/***                                                                      ***/
/****************************************************************************/

sU8 *sSystem_::LoadFile(const sChar *name,sInt &size)
{
  FILE *f;
  sU8 *mem = 0;
  long len;

  size = 0;
  if(!name || !name[0]) return 0;
  f = fopen(name,"rb");
  if(f)
  {
    fseek(f,0,SEEK_END);
    len = ftell(f);
    fseek(f,0,SEEK_SET);
    mem = new sU8[len+1];
    if(fread(mem,1,len,f)!=(size_t)len)
    {
      delete[] mem;
      mem = 0;
    }
    else
    {
      mem[len] = 0;
      size = len;
    }
    fclose(f);
  }
  return mem;
}

sU8 *sSystem_::LoadFile(const sChar *name)
{
  sInt dummy;
  return LoadFile(name,dummy);
}

sChar *sSystem_::LoadText(const sChar *name)
{
  sInt dummy;
  return (sChar *) LoadFile(name,dummy);   // LoadFile zero-terminates
}

// image import (Bitmap_Import op) is a tool feature; not used by the game data
sBool sSystem_::LoadBitmapCore(const sU8 *data,sInt size,sInt &xout,sInt &yout,sU8 *&dataout)
{
  xout = yout = 0;
  dataout = 0;
  return sFALSE;
}

sBool sSystem_::SaveFile(const sChar *name,const sU8 *data,sInt size)
{
  FILE *f = fopen(name,"wb");
  sBool ok;
  if(!f) return sFALSE;
  ok = fwrite(data,1,size,f)==(size_t)size;
  fclose(f);
  return ok;
}


/****************************************************************************/
/****************************************************************************/
/***                                                                      ***/
/***   Helper Structures                                                  ***/
/***                                                                      ***/
/****************************************************************************/
/****************************************************************************/

void sGeoBuffer::Init()
{
  Type = 0;
  Size = 0;
  Used = 0;
  VB = 0;
  UserCount = 0;
}

sBool sGeoBuffer::Alloc(sInt count,sInt size,sInt &firstp,sInt type)
{
  sInt pos,first;

  if(Type!=type)
    return sFALSE;

  first = (Used+size-1)/size;
  pos = (first+count)*size;
  if(pos>Size)
    return sFALSE;

  Used = pos;
  firstp = first;
  UserCount++;
  return sTRUE;
}

void sGeoBuffer::Free()
{
  sVERIFY(UserCount>0);
  UserCount--;
  if(UserCount==0)
    Used = 0;
}

void sTexInfo::Init(sBitmap *bm,sInt format,sU32 flags)
{
  XSize = bm->XSize;
  YSize = bm->YSize;
  Bitmap = bm;
  Flags = flags;
  Format = format;
}

void sTexInfo::InitRT(sInt xs,sInt ys)
{
  XSize = xs;
  YSize = ys;
  Flags = sTIF_RENDERTARGET;
  Format = 0;
}

void sMaterialEnv::Init()
{
  sSetMem(this,0,sizeof(*this));

  ModelSpace.Init();
  CameraSpace.Init();
  NearClip = 0.125f;
  FarClip = 4096.0f;
  ZoomX = 1.0f;
  ZoomY = 1.0f;
  CenterX = 0.0f;
  CenterY = 0.0f;
  FogStart = 0;
  FogEnd = FarClip;
  FogColor = 0xff808080;
}

void sMaterialEnv::MakeProjectionMatrix(sMatrix &pmat) const
{
  sF32 q;
  sF32 shiftX = 1.0f / sSystem->ViewportX;
  sF32 shiftY = 1.0f / sSystem->ViewportY;

  switch(Orthogonal)
  {

  case sMEO_NORMALISED: // -1 .. 1
    pmat.i.Init(ZoomX                  ,0                       ,0 ,0);
    pmat.j.Init(0                      ,ZoomY                   ,0 ,0);
    pmat.k.Init(0                      ,0                       ,1.0f/FarClip,0);
    pmat.l.Init(-shiftX                ,shiftY                  ,0 ,1);
    break;

  case sMEO_PERSPECTIVE:
    //q = FarClip/(FarClip-NearClip);
    q = 1.0f;
    pmat.i.Init(ZoomX         ,0               , 0              ,0);
    pmat.j.Init(0             ,ZoomY           , 0              ,0);
    pmat.k.Init(CenterX       ,CenterY         , q              ,1);
    pmat.l.Init(-shiftX       ,shiftY          ,-q*NearClip     ,0);
    break;
  }
}

/****************************************************************************/

sMaterial::~sMaterial()
{
}

/****************************************************************************/

void sMaterialSetup::Cleanup()
{
  delete[] States;
  delete[] VSCode;
  delete[] PSCode;

  sRelease(VS);
  sRelease(PS);

  States = 0;
  VSCode = 0;
  PSCode = 0;
}

sMaterialInstance sMaterialInstance::Null = { 0 };

/****************************************************************************/

sSimpleMaterial::sSimpleMaterial(sInt tex,sU32 flags,sU32 flags2,sU32 color)
{
  sU32 states[64],*st = states;
  static const sU32 vShaderTex[] =
  {
    0xfffe0101,                                         // vs.1.1
    0x0000001f, 0x80000000, 0x900f0000,                 // dcl_position v0
    0x0000001f, 0x80000005, 0x900f0001,                 // dcl_texcoord v1
    0x0000001f, 0x8000000a, 0x900f0002,                 // dcl_color v2
    0x00000014, 0xc00f0000, 0x90e40000, 0xa0e40000,     // m4x4 oPos,v0,c0
    0x00000001, 0xe00f0000, 0x90e40001,                 // mov oT0,v1
    0x00000001, 0xd00f0000, 0x90e40002,                 // mov oD0,v2
    0x0000ffff,                                         // end
  };
  static const sU32 vShaderNoTex[] =
  {
    0xfffe0101,                                         // vs.1.1
    0x0000001f, 0x80000000, 0x900f0000,                 // dcl_position v0
    0x0000001f, 0x8000000a, 0x900f0001,                 // dcl_color v1
    0x00000014, 0xc00f0000, 0x90e40000, 0xa0e40000,     // m4x4 oPos,v0,c0
    0x00000001, 0xd00f0000, 0x90e40001,                 // mov oD0,v1
    0x0000ffff,                                         // end
  };

  sInt blendMode = flags & sMBF_BLENDMASK;

  // zbias calc
  sF32 zBias = 0.0f;
  if(flags & sMBF_ZBIASBACK) zBias =  1.0f / 65536.0f;
  if(flags & sMBF_ZBIASFORE) zBias = -1.0f / 65536.0f;

  // render state setup
  *st++ = sD3DRS_ALPHATESTENABLE;     *st++ = 0;
  *st++ = sD3DRS_ZENABLE;             *st++ = sD3DZB_TRUE;
  *st++ = sD3DRS_ZWRITEENABLE;        *st++ = (flags & sMBF_ZWRITE) ? 1 : 0;
  *st++ = sD3DRS_ZFUNC;               *st++ = (flags & sMBF_ZREAD) ? sD3DCMP_LESS : sD3DCMP_ALWAYS;
  *st++ = sD3DRS_CULLMODE;            *st++ = (flags & sMBF_DOUBLESIDED) ? sD3DCULL_NONE : (flags & sMBF_INVERTCULL ? sD3DCULL_CW : sD3DCULL_CCW);
  *st++ = sD3DRS_COLORWRITEENABLE;    *st++ = 15;
  *st++ = sD3DRS_SLOPESCALEDEPTHBIAS; *st++ = *(sU32 *) &zBias;
  *st++ = sD3DRS_DEPTHBIAS;           *st++ = *(sU32 *) &zBias;
  *st++ = sD3DRS_FOGENABLE;           *st++ = 0;
  *st++ = sD3DRS_STENCILENABLE;       *st++ = 0;

  switch(flags & sMBF_BLENDMASK)
  {
  case sMBF_BLENDADD:
    *st++ = sD3DRS_ALPHABLENDENABLE;  *st++ = 1;
    *st++ = sD3DRS_SRCBLEND;          *st++ = sD3DBLEND_ONE;
    *st++ = sD3DRS_DESTBLEND;         *st++ = sD3DBLEND_ONE;
    *st++ = sD3DRS_BLENDOP;           *st++ = sD3DBLENDOP_ADD;
    break;

  case sMBF_BLENDALPHA:
    *st++ = sD3DRS_ALPHABLENDENABLE;  *st++ = 1;
    *st++ = sD3DRS_SRCBLEND;          *st++ = sD3DBLEND_SRCALPHA;
    *st++ = sD3DRS_DESTBLEND;         *st++ = sD3DBLEND_INVSRCALPHA;
    *st++ = sD3DRS_BLENDOP;           *st++ = sD3DBLENDOP_ADD;
    break;

  default:
    *st++ = sD3DRS_ALPHABLENDENABLE;  *st++ = 0;
    break;
  }

  // texture stages
  *st++ = sD3DTSS_0|sD3DTSS_TEXCOORDINDEX;          *st++ = 0;
  *st++ = sD3DTSS_0|sD3DTSS_TEXTURETRANSFORMFLAGS;  *st++ = 0;

  sU32 colorSource = (flags2 & 1) ? sD3DTA_TFACTOR : sD3DTA_DIFFUSE;

  if(tex != sINVALID)
  {
    *st++ = sD3DTSS_0|sD3DTSS_COLORARG1;              *st++ = sD3DTA_TEXTURE;
    *st++ = sD3DTSS_0|sD3DTSS_COLORARG2;              *st++ = colorSource;
    *st++ = sD3DTSS_0|sD3DTSS_COLOROP;                *st++ = sD3DTOP_MODULATE;
    *st++ = sD3DTSS_0|sD3DTSS_ALPHAARG1;              *st++ = sD3DTA_TEXTURE;
    *st++ = sD3DTSS_0|sD3DTSS_ALPHAOP;                *st++ = sD3DTOP_SELECTARG1;
  }
  else
  {
    *st++ = sD3DTSS_0|sD3DTSS_COLORARG2;              *st++ = colorSource;
    *st++ = sD3DTSS_0|sD3DTSS_COLOROP;                *st++ = sD3DTOP_SELECTARG2;
    *st++ = sD3DTSS_0|sD3DTSS_ALPHAARG2;              *st++ = colorSource;
    *st++ = sD3DTSS_0|sD3DTSS_ALPHAOP;                *st++ = sD3DTOP_SELECTARG2;
  }
  *st++ = sD3DTSS_1|sD3DTSS_COLOROP;                *st++ = sD3DTOP_DISABLE;
  *st++ = sD3DTSS_1|sD3DTSS_ALPHAOP;                *st++ = sD3DTOP_DISABLE;
  
  // sampler
  sU32 addressMode = (flags2 & 2) ? sD3DTADDRESS_CLAMP : sD3DTADDRESS_WRAP;

  *st++ = sD3DSAMP_0|sD3DSAMP_MAGFILTER;            *st++ = sD3DTEXF_LINEAR;
  *st++ = sD3DSAMP_0|sD3DSAMP_MINFILTER;            *st++ = sD3DTEXF_LINEAR;
  *st++ = sD3DSAMP_0|sD3DSAMP_MIPFILTER;            *st++ = (flags2 & 4) ? sD3DTEXF_NONE : sD3DTEXF_LINEAR;
  *st++ = sD3DSAMP_0|sD3DSAMP_ADDRESSU;             *st++ = addressMode;
  *st++ = sD3DSAMP_0|sD3DSAMP_ADDRESSV;             *st++ = addressMode;

  // terminator
  *st++ = ~0U;                                      *st++ = ~0U;

  // other stuff
  Color = color;
  Tex = sINVALID;
  SetTex(tex);

  // create setup
  Setup = sSystem->MtrlAddSetup(states,(tex == sINVALID) ? vShaderNoTex : vShaderTex,0);
}

sSimpleMaterial::~sSimpleMaterial()
{
  SetTex(sINVALID);
  sSystem->MtrlRemSetup(Setup);
}

void sSimpleMaterial::SetTex(sInt tex)
{
  if(tex != sINVALID)
    sSystem->AddRefTexture(tex);

  if(Tex != sINVALID)
    sSystem->RemTexture(Tex);

  Tex = tex;
}

void sSimpleMaterial::Set(const sMaterialEnv &env)
{
  sMaterialInstance inst;
  sMatrix mat;

  inst.NumTextures = 1;
  inst.Textures[0] = Tex;
  inst.NumVSConstants = 4;
  inst.VSConstants = &mat.i;
  inst.NumPSConstants = 0;

  mat.Mul4(env.ModelSpace,sSystem->LastViewProject);
  mat.Trans4();

  sSystem->MtrlSetSetup(Setup);
  sSystem->MtrlSetInstance(inst);
  sSystem->SetState(sD3DRS_TEXTUREFACTOR,Color);
}

/****************************************************************************/
/***                                                                      ***/
/***   Viewport                                                           ***/
/***                                                                      ***/
/****************************************************************************/

void sViewport::Init(sInt screen)
{
  Screen = screen;
  RenderTarget = -1;
  Window.Init(0,0,sSystem->Screen[screen].XSize,sSystem->Screen[screen].YSize);
}

/****************************************************************************/

void sViewport::InitTex(sInt handle)
{
  Screen = -1;
  RenderTarget = handle;
  Window.x0 = 0;
  Window.y0 = 0;
  sSystem->GetTextureSize(handle,Window.x1,Window.y1);
}


/****************************************************************************/
/***                                                                      ***/
/***   Host Font Interface (GDI replacement, used by Bitmap_Text)         ***/
/***                                                                      ***/
/****************************************************************************/
//
// The original created a GDI font (CreateFont, -height = em size, width =
// average char width), drew white text into a 32bit DIB with ExtTextOut and
// handed the DIB to the texture generator. Here fontconfig maps the GDI face
// name to a font file (arial -> Liberation Sans, times new roman -> Liberation
// Serif: the metric aliases) and FreeType renders it. Both are system
// libraries, like gdi32 was for the original. No headers are needed: only the
// functions below and the public, ABI-stable struct fields (32 bit offsets).

extern "C"
{
  int FT_Init_FreeType(void **lib);
  int FT_New_Face(void *lib,const char *path,long index,sU8 **face);
  int FT_Set_Char_Size(sU8 *face,long w,long h,unsigned hres,unsigned vres);
  int FT_Load_Char(sU8 *face,unsigned long ch,int flags);
  int FT_Done_Face(sU8 *face);
  sU8 *FT_Get_Sfnt_Table(sU8 *face,int tag);
  void *FcNameParse(const char *name);
  int FcConfigSubstitute(void *config,void *pat,int kind);
  void FcDefaultSubstitute(void *pat);
  void *FcFontMatch(void *config,void *pat,int *result);
  int FcPatternGetString(void *pat,const char *object,int n,char **s);
  void FcPatternDestroy(void *pat);
}

#define FT_UNITS_PER_EM(f)  (*(sU16 *)((f)+68))     // FT_FaceRec
#define FT_GLYPH(f)         (*(sU8 **)((f)+84))
#define FT_LINEARADV(g)     (*(sInt *)((g)+56))     // FT_GlyphSlotRec (16.16 pixels)
#define FT_ROWS(g)          (*(sU32 *)((g)+76))
#define FT_WIDTH(g)         (*(sU32 *)((g)+80))
#define FT_PITCH(g)         (*(sInt *)((g)+84))
#define FT_BUFFER(g)        (*(sU8 **)((g)+88))
#define FT_LEFT(g)          (*(sInt *)((g)+100))
#define FT_TOP(g)           (*(sInt *)((g)+104))
#define FT_SFNT_OS2         2                       // TT_OS2: xAvgCharWidth at +2
#define FT_SFNT_HHEA        3                       // TT_HoriHeader: Ascender +4, Descender +6
#define FT_LOADFLAGS        (2|4)                   // FT_LOAD_NO_HINTING | FT_LOAD_RENDER

static void *FontLib;
static sU8 *FontFace;
static sInt FontAscent,FontPageX,FontPageY;

sInt sSystem_::FontBegin(sInt pagex,sInt pagey,const sChar *name,sInt xs,sInt ys,sInt style)
{
  char *file = 0;
  void *pat,*match;
  sInt res,upem,avg;
  sU8 *os2,*hhea;
  sF32 sx,sy;

  FontPageX = pagex;
  FontPageY = pagey;
  FontMem = new sU32[pagex*pagey];
  sSetMem(FontMem,0,pagex*pagey*4);

  if(!name || name[0]==0) name = "arial";
  pat = FcNameParse(name);
  FcConfigSubstitute(0,pat,0);                // FcMatchPattern
  FcDefaultSubstitute(pat);
  match = FcFontMatch(0,pat,&res);
  FcPatternDestroy(pat);
  if(!FontLib) FT_Init_FreeType(&FontLib);
  if(match)
  {
    FcPatternGetString(match,"file",0,&file);
    if(!file || FT_New_Face(FontLib,file,0,&FontFace)) FontFace = 0;
    FcPatternDestroy(match);
  }
  if(!FontFace)
    return ys;

  // GDI: negative height = em height in pixels, width = average char width
  upem = FT_UNITS_PER_EM(FontFace);
  sx = sy = sAbs(ys)/(sF32)upem;
  os2 = FT_Get_Sfnt_Table(FontFace,FT_SFNT_OS2);
  avg = os2 ? *(sS16 *)(os2+2) : 0;
  if(xs>0 && avg>0)
    sx = xs/(sF32)avg;
  FT_Set_Char_Size(FontFace,(long)(sx*upem*64.0f+0.5f),sAbs(ys)*64,72,72);

  hhea = FT_Get_Sfnt_Table(FontFace,FT_SFNT_HHEA);
  FontAscent = (sInt) floorf(*(sS16 *)(hhea+4)*sy+0.5f);
  return FontAscent + (sInt) floorf(-*(sS16 *)(hhea+6)*sy+0.5f);   // tmHeight
}

static sU8 *FontGlyph(sInt ch)
{
  FT_Load_Char(FontFace,ch,FT_LOADFLAGS);
  return FT_GLYPH(FontFace);
}

static sInt FontAdvance(sU8 *g)
{
  return (FT_LINEARADV(g)+0x8000)>>16;
}

sInt sSystem_::FontWidth(const sChar *string,sInt len)
{
  sInt w = 0;
  if(len==-1)
  {
    len++;
    while(string[len]) len++;
  }
  if(FontFace)
    for(sInt i=0;i<len;i++)
      w += FontAdvance(FontGlyph(string[i]&0xff));
  return w;
}

void sSystem_::FontCharWidth(sInt ch,sInt *widths)
{
  widths[0] = widths[1] = widths[2] = 0;
  if(!FontFace) return;
  sU8 *g = FontGlyph(ch);
  widths[0] = FT_LEFT(g);
  widths[1] = FT_WIDTH(g);
  widths[2] = FontAdvance(g)-FT_LEFT(g)-FT_WIDTH(g);
}

void sSystem_::FontPrint(sInt x,sInt y,const sChar *string,sInt len)
{
  sInt i,px,py,gx,gy;
  sU8 *g;
  sU32 v;

  if(len==-1)
  {
    len++;
    while(string[len]) len++;
  }
  if(!FontFace) return;

  for(i=0;i<len;i++)
  {
    g = FontGlyph(string[i]&0xff);
    for(gy=0;gy<(sInt)FT_ROWS(g);gy++)
    {
      py = y + FontAscent - FT_TOP(g) + gy;
      if(py<0 || py>=FontPageY) continue;
      for(gx=0;gx<(sInt)FT_WIDTH(g);gx++)
      {
        px = x + FT_LEFT(g) + gx;
        if(px<0 || px>=FontPageX) continue;
        v = FT_BUFFER(g)[gy*FT_PITCH(g)+gx];
        sU32 &d = FontMem[py*FontPageX+px];
        if(v > (d&0xff))            // white text, transparent background
          d = v | (v<<8) | (v<<16);
      }
    }
    x += FontAdvance(g);
  }
}

void sSystem_::FontPrint(sInt x,sInt y,const sU16 *string,sInt len)
{
  sChar buffer[1024];
  sInt i;
  if(len==-1)
  {
    len++;
    while(string[len]) len++;
  }
  for(i=0;i<len && i<1023;i++) buffer[i] = (sChar) string[i];
  FontPrint(x,y,buffer,i);
}

void sSystem_::FontEnd()
{
  delete[] FontMem;
  FontMem = 0;
  if(FontFace) FT_Done_Face(FontFace);
  FontFace = 0;
}


/****************************************************************************/

void sSystem_::SetViewProject(const sMaterialEnv *env)
{
  sVERIFY(env);

  sFloatDouble();

  env->MakeProjectionMatrix(LastProjection);
  LastCamera = env->CameraSpace;
  LastCamera.TransR();

  LastViewProject.Mul4(LastCamera,LastProjection);
}

/****************************************************************************/
/****************************************************************************/
/***                                                                      ***/
/***   Shader                                                             ***/
/***                                                                      ***/
/****************************************************************************/
/****************************************************************************/


/****************************************************************************/

// Compare two state lists.
static sBool checkStatesEqual(const sU32 *st1,const sU32 *st2)
{
  sInt i;
  for(i=0;st1[i] == st2[i] && ((i&1) || st1[i] != ~0U);i++);

  return st1[i] == st2[i];
}

// Compare two shaders, return length if equal.
static sInt checkShadersEqual(const sU32 *sh1,const sU32 *sh2)
{
  if(!sh1 && !sh2)
    return 1;

  if(!sh1 || !sh2)
    return 0;

  sInt i;
  for(i=0;sh1[i] == sh2[i] && sh1[i] != XO_END;i++);

  return sh1[i] == sh2[i] ? i + 1 : 0;
}

sInt sSystem_::MtrlAddSetup(const sU32 *states,const sU32 *vs,const sU32 *ps)
{
  // calculate length of state array
  sInt stateLen;
  for(stateLen=0;states[stateLen] != ~0U;stateLen+=2);
  stateLen += 2;

  sInt firstFree;
  HRESULT hr;

  for(firstFree=0;firstFree<MAX_SETUPS;firstFree++)
  {
    if(!Setups[firstFree].RefCount)
      break;
  }

  if(firstFree == MAX_SETUPS)
    return sINVALID;

  sMaterialSetup *setup = &Setups[firstFree];
  hr = DXDev->CreateVertexShader((DWORD *) vs,&setup->VS);
  if(FAILED(hr))
  {
#ifndef KK_SMALL
    fprintf(stderr,"CreateVertexShader failed (%08x), version token %08x\n",(unsigned)hr,vs?vs[0]:0);
#endif
    return sINVALID;
  }

  hr = DXDev->CreatePixelShader((DWORD *) ps,&setup->PS);
  if(FAILED(hr))
  {
#ifndef KK_SMALL
    fprintf(stderr,"CreatePixelShader failed (%08x), version token %08x\n",(unsigned)hr,ps?ps[0]:0);
#endif
    if(getenv("KK_DUMPSHADER"))
    {
      static sInt n = 0;
      char name[64];
      snprintf(name,sizeof(name),"badps_%02d.bin",n++);
      FILE *f = fopen(name,"wb");
      sInt len = 0;
      while(ps[len]!=0x0000ffff && len<4096) len++;
      fwrite(ps,4,len+1,f);
      fclose(f);
    }
    return sINVALID;
  }

  if(getenv("KK_DUMPSHADER"))
  {
    char name[64];
    for(sInt w=0;w<2;w++)
    {
      const sU32 *code = w ? ps : vs;
      if(!code) continue;
      snprintf(name,sizeof(name),"setup%03d.%s",firstFree,w?"ps":"vs");
      FILE *f = fopen(name,"wb");
      sInt len = 0;
      while(code[len]!=0x0000ffff && len<8192) len++;
      fwrite(code,4,len+1,f);
      fclose(f);
    }
    FILE *f;
    snprintf(name,sizeof(name),"setup%03d.states",firstFree);
    f = fopen(name,"wb"); fwrite(states,4,stateLen,f); fclose(f);
    fprintf(stderr,"  new setup %d\n",firstFree);
  }
  setup->RefCount = 1;
  setup->States = new sU32[stateLen];
  setup->VSCode = setup->PSCode = 0;
  sCopyMem4(setup->States,states,stateLen);

  return firstFree;
}

void sSystem_::MtrlAddRefSetup(sInt sid)
{
  // sanity checks
  sVERIFY(sid >= 0 && sid < MAX_SETUPS);
  sVERIFY(Setups[sid].RefCount);

  Setups[sid].AddRef();
}

void sSystem_::MtrlRemSetup(sInt sid)
{
  // sanity checks
  sVERIFY(sid >= 0 && sid < MAX_SETUPS);
  sVERIFY(Setups[sid].RefCount);

  Setups[sid].Release();
}

void sSystem_::MtrlClearCaches()
{
  CurrentSetupId = sINVALID;
  CurrentVS = 0;
  CurrentPS = 0;

  for(sInt i=0;i<MAX_TEXSTAGE;i++)
    CurrentTextures[i] = sINVALID;

  for(sInt i=0;i<0x310;i++)
    CurrentStates[i] = 0xfefefefe; // let's hope we never actually want this value
}

void sSystem_::MtrlSetSetup(sInt sid)
{
  if(sid == CurrentSetupId)
    return;

  sZONE(MtrlSetSetup);
  
  // sanity checks
  sVERIFY(sid >= 0 && sid < MAX_SETUPS);
  sMaterialSetup *setup = &Setups[sid];
  sVERIFY(setup->RefCount > 0);

  if(CurrentSetupId != sINVALID)
    Setups[CurrentSetupId].Release();

  setup->AddRef();

  // set states
  for(sU32 *st = setup->States;st[0] != ~0U;st += 2)
  {
    sU32 state = st[0]; 
    sVERIFY(state < 0x310);

    if(st[1] != CurrentStates[state])
    {
      SetState(state,st[1]);
      CurrentStates[state] = st[1];
    }
  }

  // set vertex shader
  if(setup->VS != CurrentVS)
  {
    HRESULT hr = DXDev->SetVertexShader(setup->VS);
    sVERIFY(SUCCEEDED(hr));
    CurrentVS = setup->VS;
  }

  // set pixel shader
  if(setup->PS != CurrentPS)
  {
    HRESULT hr = DXDev->SetPixelShader(setup->PS);
    sVERIFY(SUCCEEDED(hr));
    CurrentPS = setup->PS;
  }

  CurrentSetupId = sid;
}

void sSystem_::MtrlSetInstance(const sMaterialInstance &inst)
{
  // set textures
  for(sInt i=0;i<inst.NumTextures;i++)
  {
    sInt texIndex = inst.Textures[i];

    if(texIndex != CurrentTextures[i])
    {
      IDirect3DBaseTexture9 *tex = 0;
      if(texIndex >= 0 && texIndex < MAX_TEXTURE)
        tex = Textures[texIndex].Tex;
      else if(texIndex == -2)
        tex = DXNormalCube;
      else if(texIndex == -3)
        tex = DXAttenuationVolume;

      HRESULT hr = DXDev->SetTexture(i,tex);
      sVERIFY(SUCCEEDED(hr));
      CurrentTextures[i] = texIndex;
    }
  }

  // vertex+pixel shader constants (no special caching)
  if(inst.NumVSConstants)
    DXDev->SetVertexShaderConstantF(0,(sF32 *) inst.VSConstants,inst.NumVSConstants);

  if(inst.NumPSConstants)
    DXDev->SetPixelShaderConstantF(0,(sF32 *) inst.PSConstants,inst.NumPSConstants);
}

/****************************************************************************/


/****************************************************************************/
/****************************************************************************/


/****************************************************************************/
// debug aid: save a (render target) texture as TGA
#ifndef KK_SMALL
void kkDebugSaveTexture(sInt handle,const char *name)
{
  if(handle<0 || !sSystem->Textures[handle].Tex) return;
  IDirect3DDevice9 *dev = sSystem->DXDev;
  IDirect3DTexture9 *tex = sSystem->Textures[handle].Tex;
  IDirect3DSurface9 *surf=0,*sysmem=0;
  D3DSURFACE_DESC desc;
  D3DLOCKED_RECT lr;
  tex->GetLevelDesc(0,&desc);
  tex->GetSurfaceLevel(0,&surf);
  if(SUCCEEDED(dev->CreateOffscreenPlainSurface(desc.Width,desc.Height,desc.Format,D3DPOOL_SYSTEMMEM,&sysmem,0)) &&
     SUCCEEDED(dev->GetRenderTargetData(surf,sysmem)) &&
     SUCCEEDED(sysmem->LockRect(&lr,0,D3DLOCK_READONLY)))
  {
    FILE *out = fopen(name,"wb");
    sU8 hdr[18] = {0,0,2, 0,0,0,0,0, 0,0,0,0, 0,0,0,0, 32,0x28};
    hdr[12] = desc.Width&255; hdr[13] = desc.Width>>8; hdr[14] = desc.Height&255; hdr[15] = desc.Height>>8;
    fwrite(hdr,1,18,out);
    for(sU32 y=0;y<desc.Height;y++)
      fwrite(((sU8 *)lr.pBits)+y*lr.Pitch,4,desc.Width,out);
    fclose(out);
    sysmem->UnlockRect();
    fprintf(stderr,"dumped texture %d (%dx%d fmt %d) -> %s\n",handle,desc.Width,desc.Height,desc.Format,name);
  }
  else
    fprintf(stderr,"could not dump texture %d (fmt %d)\n",handle,desc.Format);
  if(sysmem) sysmem->Release();
  if(surf) surf->Release();
}
#endif

/****************************************************************************/
#ifndef KK_SMALL
// linux port: minimal thread interface for the game code
void *kkStartThread(int (*fn)(void *),void *user)
{
  return SDL_CreateThread((SDL_ThreadFunction)fn,"kkworker",user);
}
#endif

void kkWaitThread(void *thread)
{
  SDL_WaitThread((SDL_Thread *)thread,0);
}
