// This file is distributed under a BSD license. See LICENSE.txt for details.
//
// Linux platform layer for the .kkrieger player.
//
// Derived from farbrausch's _start.cpp (fr_public/werkkzeug3_kkrieger).
// Replaced parts:
//   graphics                      -> OpenGL 4.5 (glrender.cpp) with the game's
//                                    GLSL shaders (shaders/, tools/shaderpack.py)
//   Win32 window / message loop   -> SDL3
//   sound buffers (+3D)           -> SDL3 audio stream + small software mixer
//   GDI font rendering            -> fontconfig + FreeType (system libraries)
//   Win32 file / heap / timer API -> stdio / malloc / SDL timer

#include "_types.hpp"
#include "_start.hpp"
#include "material11.hpp"

#define sPLAYER_SCREENX     1024    // the 2004 release was hardwired to 1024x768
#define sPLAYER_SCREENY     768
#define sPLAYER_FULLSCREEN  0       // windowed by default on Linux, -f for fullscreen
#define sPLAYER_DIALOG      1

#define sINTRO_NO_ALT_TAB   0

const sChar *sWindowTitle=".kkrieger (linux port)";

#include "glrender.hpp"
#include <SDL3/SDL.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>


#define LOGGING 0

sMAKEZONE(FlipLock,"FlipLock",0xffff0000);
sMAKEZONE(MtrlSet,"MtrlSet",0xff404040);
sMAKEZONE(MtrlSetSetup,"MtrlSetSetup",0xff203040);
sMAKEZONE(Sound3D,"Sound3D",0xff804040);

/****************************************************************************/
/***                                                                      ***/
/***   Win32 compatibility shims used by the (unchanged) engine code      ***/
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


// vertex formats: { offset, floats (or GL_BGRA = 4 byte colour), shader input location }
// locations: 0 position, 1 normal, 2/3 colour 0/1, 4..7 uv 0..3, 8 tangent, 9 binormal

struct FVFTableStruct
{
  sInt Size;                      // size in bytes!
  const GlrVertexElement *Info;
  sInt Count;
};

#define F2 2
#define F3 3
#define F4 4
#define C4 GL_BGRA                             // 32 bit colour, 0xaarrggbb
static const GlrVertexElement DeclDefault[] =
  { { 0,F3,0 },{ 12,F3,1 },{ 24,F2,4 } };
static const GlrVertexElement DeclDouble[] =
  { { 0,F3,0 },{ 12,C4,2 },{ 16,F2,4 },{ 24,F2,5 } };
static const GlrVertexElement DeclTSpace[] =
  { { 0,F3,0 },{ 12,F3,1 },{ 24,C4,2 },{ 28,C4,3 },{ 32,F2,4 },{ 40,F3,8 },{ 52,F3,9 } };
static const GlrVertexElement DeclCompact[] =
  { { 0,F3,0 },{ 12,C4,2 } };
static const GlrVertexElement DeclTSpace3[] =
  { { 0,F3,0 },{ 12,C4,1 },{ 16,C4,8 },{ 20,C4,2 },{ 24,F2,4 } };
static const GlrVertexElement DeclTSpace3Big[] =
  { { 0,F3,0 },{ 12,F3,1 },{ 24,F3,8 },{ 36,C4,2 },{ 40,F2,4 } };
static const GlrVertexElement DeclXYZW[] =
  { { 0,F4,0 } };
#undef F2
#undef F3
#undef F4
#undef C4

#define DECL(x) x,sizeof(x)/sizeof(x[0])
static const FVFTableStruct FVFTable[] =
{
  {  0,0,0                 },
  { 32,DECL(DeclDefault)   },
  { 32,DECL(DeclDouble)    },
  { 64,DECL(DeclTSpace)    },
  { 16,DECL(DeclCompact)   },
  { 16,DECL(DeclXYZW)      },
  { 32,DECL(DeclTSpace3)   },
  { 48,DECL(DeclTSpace3Big)},
};
#undef DECL

#define FVFMax (sizeof(FVFTable)/sizeof(FVFTableStruct))

/****************************************************************************/
/***                                                                      ***/
/***   Audio state (SDL audio stream, rendered in its callback)          ***/
/***                                                                      ***/
/****************************************************************************/

static SDL_AudioStream *AudioStream;
static volatile sSoundHandler AudioHandler;
static sInt AudioHandlerAlign = 64;
static void *AudioHandlerUser;
static volatile sInt AudioLastTotalSample;
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
    if(AudioHandlerAlign>1)                 // handler wants aligned block sizes
      count = (count + AudioHandlerAlign-1) & ~(AudioHandlerAlign-1);
    if(count>4096) count = 4096;

    if(AudioHandler)
      (*AudioHandler)(buffer,count,AudioHandlerUser);
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

  sSystem->ConfigFlags = 0;
  sSystem->ConfigX = IntroScreenX;
  sSystem->ConfigY = IntroScreenY;

  if(!SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS))
    sFatal("SDL_Init failed: %s",SDL_GetError());

// set up some more stuff

  WStartTime = timeGetTime();
  sSetRndSeed(FixedTime() ? 1 : timeGetTime()&0x7fffffff);

// create window

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,5);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,0);
#ifndef KK_SMALL
  if(getenv("KK_GLDEBUG"))
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,SDL_GL_CONTEXT_DEBUG_FLAG);
#endif
  SDL_WindowFlags wflags = SDL_WINDOW_OPENGL;
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

  for(i=0;i<MAX_TEXTURE;i++)
    Textures[i].Flags = 0;
  sSetMem(Setups,0,sizeof(Setups));
  MtrlClearCaches();
  InitScreens();

  sFloatFix();

  if(!InitAudio())
    sFatal("could not initialize audio: %s",SDL_GetError());

  // main loop

  sAppHandler(sAPPCODE_CONFIG,0);

  sAppHandler(sAPPCODE_INIT,0);

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
    MarkAudio();
  }

  ExitAudio();
  SDL_Quit();
  _exit(0);   // like the original: no orderly teardown of the engine
}

/****************************************************************************/


void sSystem_::InitScreens()
{
  sInt i;
  sU16 *iblock;

  sREGZONE(FlipLock);

  // Linux: a fixed size back buffer; SDL handles (desktop) fullscreen and
  // the presentation scales the image to the window.
  Screen[0].XSize = ConfigX;
  Screen[0].YSize = ConfigY;
  glrInit(SDLWin,ConfigX,ConfigY,(IntroFlags & sSF_WAITVSYNC) ? 1 : 0);

  {
    sInt strides[FVFMax];
    const GlrVertexElement *elements[FVFMax];
    sInt counts[FVFMax];
    for(i=0;i<FVFMax;i++)
    {
      strides[i] = FVFTable[i].Size;
      elements[i] = FVFTable[i].Info;
      counts[i] = FVFTable[i].Count;
    }
    glrSetVertexFormats(FVFMax,strides,elements,counts);
  }

  // create dummy texture
  sU16 bmp[4*4*4];
  sSetMem(bmp,0,sizeof(bmp));
  AddTexture(4,4,sTF_A8R8G8B8,bmp,1);

  GpuMask |= sGPU_TWOSIDESTENCIL;

// init buffer management

  CreateGeoBuffer(0,1,0,MAX_DYNVBSIZE);
  CreateGeoBuffer(1,1,1,MAX_DYNIBSIZE);
  CreateGeoBuffer(2,1,2,MAX_DYNIBSIZE*2);

// create managed resources
  CreateGeoBuffer(3,0,1,2*0x8000/4*6);
  iblock = (sU16 *) glrLockBuffer(GeoBuffer[3].Buf,0,2*0x8000/4*6);
  for(i=0;i<0x8000/6;i++)
    sQuad(iblock,i*4+0,i*4+1,i*4+2,i*4+3);
  glrUnlockBuffer(GeoBuffer[3].Buf);
  MakeCubeNormalizer();
  MakeAttenuationVolume();

  DiscardCount[0] = DiscardCount[1] = DiscardCount[2] = 1;

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

  time = timeGetTime();
  if(time > lasttime+450 || done==max)
  {
    lasttime = time;

    sViewport vp;
    vp.Init();
    SetViewport(vp);
    Clear(sVCF_COLOR);

    sZONE(FlipLock);

    r.Init(20+step*0,ConfigY/2-20+step*0,ConfigX-20-step*0,ConfigY/2+20-step*0);
    glrFillRect(r.x0,r.y0,r.x1,r.y1,0xffffffff);

    r.Init(20+step*1,ConfigY/2-20+step*1,ConfigX-20-step*1,ConfigY/2+20-step*1);
    glrFillRect(r.x0,r.y0,r.x1,r.y1,0xff000000);

    r.Init(20+step*2,ConfigY/2-20+step*2,ConfigX-20-step*2,ConfigY/2+20-step*2);
    r.x1 = r.x0 + 1 + sMin(max,done)*(r.x1-r.x0-1)/max;
    glrFillRect(r.x0,r.y0,r.x1,r.y1,0xffffffff);

    Present();


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

    Present();

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

  LastCamera.Init();
  LastMatrix.Init();
  LastViewProject.Init();

  time = sSystem->GetTime();
  ticks = 0;
  if(LastTime==-1)
    LastTime = time;

  sAppHandler(sAPPCODE_FRAME,0);


  sAppHandler(sAPPCODE_PAINT,0);

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
          {
            sU8 *pixels = new sU8[ConfigX*ConfigY*4];
            glrReadBackBuffer(pixels);
            char name[64];
            snprintf(name,sizeof(name),"kkshot_%06d.tga",getenv("KK_SHOT_MS") ? GetTime() : frame);
            FILE *out = fopen(name,"wb");
            sU8 hdr[18] = {0,0,2, 0,0,0,0,0, 0,0,0,0, 0,0,0,0, 32,0x28};
            hdr[12] = ConfigX&255; hdr[13] = ConfigX>>8; hdr[14] = ConfigY&255; hdr[15] = ConfigY>>8;
            fwrite(hdr,1,18,out);
            fwrite(pixels,4,ConfigX*ConfigY,out);
            fclose(out);
            delete[] pixels;
            fprintf(stderr,"saved %s (t=%d ms)\n",name,GetTime());
            if(byTime) lastShotTime = f;
          }
        }
        while(*p && *p!=',') p++;
        if(*p==',') p++;
      }
      static sInt firstT = GetTime();
      if((getenv("KK_SHOT_MS") ? GetTime() - (getenv("KK_SHOT_REL") ? firstT : 0) : frame)>last && getenv("KK_SHOT_EXIT"))
        Exit();
    }
  }

  Present();
  FixedTimeFrames++;
}

void sSystem_::Present()
{
  glrPresent();
}

/****************************************************************************/
/****************************************************************************/

void sSystem_::Clear(sU32 flags,sU32 color)
{
  // NOTE: we don't support automatically clear textures fully anymore,
  // because in the current rendering architecture we either set full
  // texture viewports or render to the backbuffer then blit to textures.

  sU32 clear = 0;

  if(flags & sVCF_COLOR)    clear |= GLR_CLEAR_COLOR;
  if(flags & sVCF_Z)        clear |= GLR_CLEAR_DEPTH | GLR_CLEAR_STENCIL;
  if(flags & sVCF_STENCIL)  clear |= GLR_CLEAR_STENCIL;

  if(clear)
    glrClear(clear,color);
}

void sSystem_::SetViewport(const sViewport &vp)
{
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

  // set render target and viewport
  if(CurrentTarget != tgtid)
  {
    glrSetTarget(vp.RenderTarget == sINVALID ? 0 : Textures[vp.RenderTarget].Tex);
    CurrentTarget = tgtid;
  }

  glrSetViewport(CurrentViewport.Window.x0,CurrentViewport.Window.y0,ViewportX,ViewportY);
}

void sSystem_::GrabScreen(sInt sourceRT,const sRect &win,sInt tex,sBool stretch)
{
  glrCopyToTexture(sourceRT == -1 ? 0 : Textures[sourceRT].Tex,win.x0,win.y0,win.x1,win.y1,Textures[tex].Tex,stretch);
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

static sInt FullMips(sInt xs,sInt ys)   // mip chain length for "all levels"
{
  sInt n = 1;
  for(xs=sMax(xs,ys);xs>1;xs>>=1)
    n++;
  return n;
}

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
        tex->Tex = glrCreateTexture(GLR_TEX2D,GLR_BGRA8,tex->XSize,tex->YSize,1,0);
	    }
	    else
	    {
#if LOGGING
        sDPrintF("Create Texture %dx%d\n",tex->XSize,tex->YSize);
#endif
        tex->Tex = glrCreateTexture(GLR_TEX2D,GLR_BGRA8,tex->XSize,tex->YSize,1,FullMips(tex->XSize,tex->YSize));
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
  sInt glformat = format==sTF_SIGNED8 ? GLR_RGBA8S : GLR_BGRA8;   // the only formats in use

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

        tex->Tex = glrCreateTexture(GLR_TEX2D,glformat,tex->XSize,tex->YSize,1,0);
	    }
	    else
	    {
#if LOGGING
        sDPrintF("Create Texture %dx%d\n",tex->XSize,tex->YSize);
#endif
        DebugTexMem += tex->XSize * tex->YSize * 4 * (mipcount ? 4 : 3) / 3;

        tex->Tex = glrCreateTexture(GLR_TEX2D,glformat,tex->XSize,tex->YSize,1,mipcount ? mipcount : FullMips(xs,ys));
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
      glrDestroyTexture(tex->Tex);

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
  sInt pitch;
  sU8 *bits;
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

  NormalCube = glrCreateTexture(GLR_TEXCUBE,GLR_BGRA8,size,size,1,1);
  for(i=0;i<6;i++)
  {
    bits = (sU8 *) glrLockTexture(NormalCube,i,0,&pitch);
    for(y=0;y<size;y++)
    {
      p = bits+y*pitch;
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
    glrUnlockTexture();
  }
}

/****************************************************************************/

void sSystem_::MakeAttenuationVolume()
{
  const sInt size = 32;
  const sF32 scale = 2.0f / (size - 2.0f);
  const sF32 mid = size / 2.0f;
  sU8 *bits;
  sInt x,y,z;
  sVector v;
  sF32 attn;
  sU8 *p;

  AttenuationVolume = glrCreateTexture(GLR_TEX3D,GLR_BGRA8,size,size,size,1);
  bits = (sU8 *) glrLockTexture(AttenuationVolume,0,0,0);

  for(z=0;z<size;z++)
  {
    v.z = (z - mid) * scale;

    for(y=0;y<size;y++)
    {
      v.y = (y - mid) * scale;
      p = bits+(z*size+y)*size*4;

      for(x=0;x<size;x++)
      {
        v.x = (x - mid) * scale;
        attn = sMax(1.0f - v.Dot3(v),0.0f);
        p[0] = p[1] = p[2] = p[3] = sFtol(attn * 255);
        p += 4;
      }
    }
  }

  glrUnlockTexture();
}

/****************************************************************************/

sBool sSystem_::StreamTextureStart(sInt handle,sInt level,sBitmapLock &lock)
{
  sHardTex *tex;
  sInt pitch;

  tex = &Textures[handle];

  sVERIFY(!StreamTexture);
  StreamTexture = tex->Tex;
  StreamLevel = level;

  lock.Data = (sU8 *) glrLockTexture(tex->Tex,0,level,&pitch);
  lock.XSize = tex->XSize>>level;
  lock.YSize = tex->YSize>>level;
  lock.Kind = tex->Format;
  lock.BPR = pitch;

  return sTRUE;
}

/****************************************************************************/

void sSystem_::StreamTextureEnd()
{
  sVERIFY(StreamTexture);
  glrUnlockTexture();
  StreamTexture=0;
}

/****************************************************************************/
/****************************************************************************/

void sSystem_::SetStates(sU32 *stream)
{
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

  glrSetState(token,value);   // GLR_* render and sampler states

  CurrentStates[token] = value;
}

/****************************************************************************/

void sSystem_::SetScissor(const sFRect *scissor)
{
  struct { sInt left,top,right,bottom; } rc;

  if(!scissor)
    SetState(GLR_SCISSOR,0);
  else
  {
    rc.left   = CurrentViewport.Window.x0 + (CurrentViewport.Window.x1 - CurrentViewport.Window.x0) * (1.0f + scissor->x0) * 0.5f;
    rc.right  = CurrentViewport.Window.x0 + (CurrentViewport.Window.x1 - CurrentViewport.Window.x0) * (1.0f + scissor->x1) * 0.5f;
    rc.top    = CurrentViewport.Window.y0 + (CurrentViewport.Window.y1 - CurrentViewport.Window.y0) * (1.0f - scissor->y1) * 0.5f;
    rc.bottom = CurrentViewport.Window.y0 + (CurrentViewport.Window.y1 - CurrentViewport.Window.y0) * (1.0f - scissor->y0) * 0.5f;

    glrSetScissorRect(rc.left,rc.top,rc.right,rc.bottom);
    SetState(GLR_SCISSOR,1);
  }
}

/****************************************************************************/
/****************************************************************************/

void sSystem_::CreateGeoBuffer(sInt i,sInt dyn,sInt index,sInt size)
{
  sVERIFY(dyn==0 || dyn==1);
  sVERIFY(index>=0 || index<=2);

  GeoBuffer[i].Type = 1+index;      // 1 = vertex, 2 = index16, 3 = index32
  GeoBuffer[i].Size = size;
  GeoBuffer[i].Used = 0;
  GeoBuffer[i].UserCount = 0;
  GeoBuffer[i].Buf = glrCreateBuffer(size);
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
  for(i=4;i<MAX_GEOBUFFER;i++)
  {
    glrDestroyBuffer(GeoBuffer[i].Buf);
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
  sInt mode;
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

// start drawing: count = number of vertices/indices that form whole primitives

  count = gh->Index.Count;
  if(count == 0)
    count = gh->Vertex.Count;

  switch(gh->Mode&7)
  {
  case sGEO_POINT:
    mode = GL_POINTS;
    sVERIFY(gh->Index.Count==0);
    break;
  case sGEO_LINE:
    mode = GL_LINES;
    count = count/2*2;
    break;
  case sGEO_LINESTRIP:
    mode = GL_LINE_STRIP;
    if(count<2) count = 0;
    break;
  case sGEO_TRI:
    mode = GL_TRIANGLES;
    count = count/3*3;
    break;
  case sGEO_TRISTRIP:
    mode = GL_TRIANGLE_STRIP;
    if(count<3) count = 0;
    break;
  case sGEO_QUAD:
    sVERIFY(gh->Index.Count==0);
    glrSetStreams(gh->FVF,GeoBuffer[gh->Vertex.Buffer].Buf,GeoBuffer[3].Buf,0);
    glrDrawIndexed(GL_TRIANGLES,gh->Vertex.Start,0,count/4*6);
    return sFALSE;
  default:
    sVERIFYFALSE;
  }

  if(gh->Index.Count)
  {
    glrSetStreams(gh->FVF,GeoBuffer[gh->Vertex.Buffer].Buf,GeoBuffer[gh->Index.Buffer].Buf,GeoBuffer[gh->Index.Buffer].Type==3);
    glrDrawIndexed(mode,gh->Vertex.Start,gh->Index.Start,count);
  }
  else if(count)
  {
    glrSetStreams(gh->FVF,GeoBuffer[gh->Vertex.Buffer].Buf,0,0);
    glrDraw(mode,gh->Vertex.Start,count);
  }

  return sFALSE;
}

void sSystem_::AllocBufferInternal(sGeoBufferRef &ref,sInt size,sBool stat,sInt index,void **ptr)
{
  sInt i;
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
  }

  *ptr = glrLockBuffer(GeoBuffer[ref.Buffer].Buf,ref.Start*size,ref.Count*size);   // GeoEnd uploads
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
    glrUnlockBuffer(GeoBuffer[gh->Vertex.Buffer].Buf);
  if(gh->Locked & sGEO_INDEX)
    glrUnlockBuffer(GeoBuffer[gh->Index.Buffer].Buf);
  gh->Locked &= ~(sGEO_VERTEX|sGEO_INDEX);

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

  glrDestroyTexture(tex->Tex);
  tex->Tex = 0;
}

/****************************************************************************/

void sSystem_::UpdateTexture(sInt handle,sBitmap *bm)
{
  sHardTex *tex;
  sInt xs,ys,level;
  sInt miptresh;
  sInt mipdir;
  sInt filter;
  GlrTexture *mst;

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
        d = (sU32 *) glrLockTexture(mst,0,level,&bpr);
			  s = data;
			  for(y=0;y<ys;y++)
			  {
				  sCopyMem4(d,s,xs);
				  d+=bpr/4;
				  s+=oxs;
			  }
        glrUnlockTexture();
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
  GlrTexture *mst;
  sInt xs,ys,level;
  sInt mipdir;
  sInt filter;

  sInt x,y;
  sInt bpr,oxs;
  sU32 *d,*s,*data;
  sU16 *d16,*s16;

  mipdir = miptresh & 16;
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
        d = (sU32 *) glrLockTexture(mst,0,level,&bpr);
			  s = data;
			  for(y=0;y<ys;y++)
			  {
          if(tex->Format==sTF_SIGNED8)
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

				  d+=bpr/4;
				  s+=oxs*2;
			  }
        glrUnlockTexture();

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
  sInt n;
  sU32 *pixels;

  tex = &Textures[handle];
  n = tex->XSize*tex->YSize;
  pixels = new sU32[n];
  glrReadTexture(tex->Tex,pixels);
  for(sInt p=0;p<n;p++)
  {
    sU32 val = pixels[p];
    for(sInt i=0;i<4;i++)
    {
      sU32 bits = ((val>>(i*8))&255);
      dest[i] = (bits<<7) | (bits>>1);
    }
    dest+=4;
  }
  delete[] pixels;
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

#define AUDIO_SAMPLES 0x20000

sBool sSystem_::InitAudio()
{
  SDL_AudioSpec spec;
  spec.format = SDL_AUDIO_S16LE;
  spec.channels = 2;
  spec.freq = 44100;

  // ~23ms device buffer, comparable to the 2004 version
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

void sSystem_::ExitAudio()
{
  if(AudioStream)
  {
    SDL_DestroyAudioStream(AudioStream);
    AudioStream = 0;
  }
  SampleRemAll();
}

/****************************************************************************/

void sSystem_::MarkAudio()
{
  // only GetCurrentSample() (werkkzeug's timeline) needs this; taking the
  // stream lock every frame made the game wait for the synth. Approximate.
  AudioLastTotalSample = AudioFramesOut;
}

/****************************************************************************/

void sSystem_::SetSoundHandler(sSoundHandler hnd,sInt align,void *user)
{
  if(!AudioStream) return;
  SDL_LockAudioStream(AudioStream);

  AudioHandler = hnd;           // 0 = silence
  if(align<=0)
    align=64;
  AudioHandlerAlign = align;
  AudioHandlerUser = user;
  AudioLastTotalSample = 0;
  AudioFramesOut = 0;

  SDL_UnlockAudioStream(AudioStream);
}

/****************************************************************************/

sInt sSystem_::GetCurrentSample()
{
  return AudioLastTotalSample;
}

/****************************************************************************/
/***                                                                      ***/
/***   Sample Player (software mixer for the sound effects)               ***/
/***                                                                      ***/
/****************************************************************************/

// Volume/pan are in 1/100 dB (millibel). The original converted a linear
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

static sInt lin2mb(sF32 volume)
{
  volume = sRange(volume,1.0f,1e-20f);
  return sMax<sInt>(sFLog(volume)*20*100,-10000);
}

sInt sSystem_::SamplePlay(sInt handle,sF32 volume,sF32 pan,sInt freq)
{
  sSample *sam;
  sSampleBuffer *buf;
  sInt panmb,r;

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
    panmb = sRange<sInt>(pan*100,10000,-10000);

    sam->LRU = (sam->LRU+1)%sam->Count;
    buf = &sam->Buffers[sam->LRU];

    buf->Volume = MBToGain(lin2mb(volume));
    if(!sam->Is3D)
    {
      buf->Gain[0] = panmb>0 ? MBToGain(-panmb) : 1.0f;
      buf->Gain[1] = panmb<0 ? MBToGain( panmb) : 1.0f;
    }
    buf->PlayTime = SoundTime;
    __atomic_store_n(&buf->Pos,0,__ATOMIC_RELEASE);
    r = ++sam->Uses;
    return r;
  }
  else
    return -1;
}

// 3D sound, reduced to what matters here:
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
  Buf = 0;
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
  States = 0;
}

sMaterialInstance sMaterialInstance::Null = { 0 };

/****************************************************************************/


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

sInt sSystem_::MtrlAddSetup(const sU32 *states,sInt vs,sInt ps)
{
  // calculate length of state array
  sInt stateLen;
  for(stateLen=0;states[stateLen] != ~0U;stateLen+=2);
  stateLen += 2;

  sInt firstFree;
  for(firstFree=0;firstFree<MAX_SETUPS && Setups[firstFree].RefCount;firstFree++);
  if(firstFree == MAX_SETUPS)
    return sINVALID;

  sMaterialSetup *setup = &Setups[firstFree];
  setup->RefCount = 1;
  setup->States = new sU32[stateLen];
  sCopyMem4(setup->States,states,stateLen);
  setup->VS = vs;
  setup->PS = ps;

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
  CurrentVS = -1;
  CurrentPS = -1;

  for(sInt i=0;i<MAX_TEXSTAGE;i++)
    CurrentTextures[i] = sINVALID;

  for(sInt i=0;i<GLR_STATES;i++)
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
    sVERIFY(state < GLR_STATES);

    if(st[1] != CurrentStates[state])
    {
      SetState(state,st[1]);
      CurrentStates[state] = st[1];
    }
  }

  // set shaders
  CurrentVS = setup->VS;
  CurrentPS = setup->PS;
  glrSetShaders(CurrentVS,CurrentPS);

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
      GlrTexture *tex = 0;
      if(texIndex >= 0 && texIndex < MAX_TEXTURE)
        tex = Textures[texIndex].Tex;
      else if(texIndex == -2)
        tex = NormalCube;
      else if(texIndex == -3)
        tex = AttenuationVolume;

      glrSetTexture(i,tex);
      CurrentTextures[i] = texIndex;
    }
  }

  // vertex+pixel shader constants (no special caching)
  if(inst.NumVSConstants)
    glrSetVSConst(0,(sF32 *) inst.VSConstants,inst.NumVSConstants);

  if(inst.NumPSConstants)
    glrSetPSConst(0,(sF32 *) inst.PSConstants,inst.NumPSConstants);
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
  sHardTex *tex = &sSystem->Textures[handle];
  sU8 *pixels = new sU8[tex->XSize*tex->YSize*4];
  glrReadTexture(tex->Tex,pixels);
  FILE *out = fopen(name,"wb");
  sU8 hdr[18] = {0,0,2, 0,0,0,0,0, 0,0,0,0, 0,0,0,0, 32,0x28};
  hdr[12] = tex->XSize&255; hdr[13] = tex->XSize>>8; hdr[14] = tex->YSize&255; hdr[15] = tex->YSize>>8;
  fwrite(hdr,1,18,out);
  fwrite(pixels,4,tex->XSize*tex->YSize,out);
  fclose(out);
  delete[] pixels;
  fprintf(stderr,"dumped texture %d (%dx%d) -> %s\n",handle,tex->XSize,tex->YSize,name);
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
