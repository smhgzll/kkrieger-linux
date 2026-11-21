#include <stdlib.h>
#include <stdio.h>
// This file is distributed under a BSD license. See LICENSE.txt for details.

#include "_types.hpp"
#include "_start.hpp"
#include "_viruz2.hpp"
#include "_ogg.hpp"
#include "kdoc.hpp"
#include "kkriegergame.hpp"
#include "engine.hpp"
#include "genoverlay.hpp"
#include "rtmanager.hpp"

#define WAITFORKEY  0   // linux port: the 2004 player starts right away

/****************************************************************************/

static CV2MPlayer *Sound;
static sMusicPlayer *Player = 0;
static sInt SoundTimer;
KDoc *Document;
KEnvironment *Environment;
KKriegerGame *Game;
sF32 GlobalFps;


extern "C" sU8 kkrieger_data[];
extern "C" sU32 kkrieger_data_size;
static sU8* PtrTable[] =
{
  (sU8 *) 0x54525450,     // entry 0: export data ('PTRT')
  (sU8 *) 0x454C4241,     // entry 1: viruzII tune ('ABLE')
};

extern sInt IntroTargetAspect;
extern sInt IntroLoop;

/****************************************************************************/

/****************************************************************************/

struct VFXEntry
{
  sU8 MajorId;
  sU8 MinorId;
  sS8 Gain;
  sU8 reserved;
  sU32 StartPos;
  sU32 EndPos;
  sU32 LoopSize;
};

static void RenderSoundEffects(KDoc *doc,sU8 *data)
{
  const sInt maxsamples = 0x10000;
  static sF32 smpf[maxsamples*2];
  static sS16 *smps = (sS16 *) smpf;
  sU32 *data32,size;
  sU8 *v2m;
  sInt i,j,count,start,len,fade;
  sF32 amp,ampx;
  VFXEntry *ent;

  sVERIFY(Sound);

  data32 = (sU32 *) data;
  sVERIFY(data32[0] == sMAKE4('V','F','X','0'));
  size = data32[1];
  v2m = (sU8 *) &data32[2];
  data32 = (sU32 *) (((sU8 *)data32)+size+12);
  count = *data32++;
  ent = (VFXEntry *) data32;

  if(Sound->Open(v2m))
  {
    for(i=0;i<count;i++)
    {
      start = ent->StartPos;
      if(ent->LoopSize)
        start = ent->EndPos - ent->LoopSize;
      len = sMin<sInt>(ent->EndPos - start,maxsamples);
      ampx = sFPow(10.0f,(ent->Gain / 5.0f) / 20.0f);

      Sound->Play(ent->StartPos);
      Sound->Render(smpf,len);
      fade = 1000;
      if(ent->MajorId & 1)
        fade = 44100;

      for(j=0;j<len;j++)
      {
        amp = ampx;
        if(j<fade)
          amp = amp*j/fade;
        if(j>len-fade)
          amp = amp*(len-j)/fade;

        smps[j*2+0] = sRange<sInt>(smpf[j*2+0]*amp*0x7fff,0x7fff,-0x7fff);
        smps[j*2+1] = sRange<sInt>(smpf[j*2+1]*amp*0x7fff,0x7fff,-0x7fff);
      }

      // 2004 (FUN_0081e670): plain stereo samples, there was no 3d flag
      sSystem->SampleAdd(smps,len,4,ent->MinorId,sFALSE);
      sSystem->Progress(doc->Ops.Count+i,doc->Ops.Count+count);
      ent++;
    }

    Sound->Close();
  }
}

/****************************************************************************/

void IntroSoundHandler(sS16 *stream,sInt left,void *user)
{
  static sF32 buffer[4096*2];
  sF32 *fp;
  sInt count;
  sInt i;

  SoundTimer += left;
  if(Sound)
  {
    while(left>0)
    {
      count = sMin<sInt>(4096,left);
      Sound->Render(buffer,count);
      fp = buffer;
      for(i=0;i<count*2;i++)
        //*stream++ = 0;
        *stream++ = sRange<sInt>(*fp++*0x7fff,0x7fff,-0x7fff);
      left-=count;
    }
#pragma lekktor(off)
    if(SoundTimer>=(2*60+25)*44100)
    {
      Sound->Open(Document->SongData);
      Sound->Play(0);
      SoundTimer = 0;
    }
#pragma lekktor(on)
  }
  else
  {
    for(i=0;i<left*2;i++)
      *stream++ = 0;
    SoundTimer = 0;
  }
}

static void MusicPlayerHandler(sS16 *buffer,sInt samples,void *user)
{
  sMusicPlayer *player = (sMusicPlayer *) user;
  player->Render(buffer,samples);
}

extern sBool ConfigDialog(sInt nr,const sChar *title);

extern sInt DebugTextMem;

sInt DebugTexMem = 0;
#if !defined(KK_SMALL) || defined(KK_COVERAGE)
unsigned long long kkNanoTime();       // _start_linux.cpp
#endif

sBool sAppHandler(sInt code,sDInt value)
{
  static const sInt aspectRatios[][2] = { { 4,3 }, { 5,4 }, { 16,9 }, { 16,10 }, { 2,1 } };

  sInt beat;
  static sU8 *data;
  sViewport vp,clearvp;
  sInt i,max;
  sF32 curfps;
  static sF32 oldfps;
  static sInt FirstTime,ThisTime,LastTime;
  static sInt framectr=0;
  sRect r;
  sInt targetHeight;

  KOp *root;
#if !defined(KK_SMALL) || defined(KK_COVERAGE)
  static const char *framelog = getenv("KK_FRAMELOG");   // see sAPPCODE_PAINT
  static unsigned long long flLast,flTickNS,flPaintNS;
  static sInt flSteps;
  unsigned long long flStart = 0,flTick = 0;
#endif

  //GenBitmapTextureSizeOffset = -1;
  switch(code)
  {
  case sAPPCODE_CONFIG:
    data = PtrTable[0];

//#if !sINTRO
    if(((sInt)data)==0x54525450)
    {
#ifdef KK_SMALL
      data = kkrieger_data;     // size build: only the embedded document
#else
      data = sSystem->LoadFile(sSystem->GetCmdLine());
      if(data==0)
        data = kkrieger_data;   // linux port: document embedded by data_linux.asm
#endif
    }
//#endif

    break;

  case sAPPCODE_INIT:
    Document = new KDoc;

    {
      const sU8 *cdata = data;
      Document->Init(cdata);
#ifdef KK_VERBOSE
      fprintf(stderr,"document parsed: %d bytes\n",(sInt)(cdata-data));
#endif
#ifndef KK_SMALL
      // analysis aid for the size work: KK_OPSTATS=file writes every op
      // (command, parameters, strings) and the opcodes of its animation code
      if(getenv("KK_OPSTATS"))
      {
        static const sU8 animLen[0x1e] = { 0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,4,4,2,0,0,0,8 };
        FILE *f = fopen(getenv("KK_OPSTATS"),"w");
        for(sInt i=0;f && i<Document->Ops.Count;i++)
        {
          KOp *op = &Document->Ops[i];
          sInt type = 0;
          for(KHandler *h=KHandlers;h->Id;h++)
            if(h->InitHandler==op->InitHandler && h->ExecHandler==op->ExecHandler) { type = h->Id; break; }
          fprintf(f,"op %d id %d type %02x in %d data",i,op->OpId,type,op->GetInputCount());
          for(sInt j=0;j<op->GetDataWords();j++)
            fprintf(f," %08x",*op->GetEditPtrU(j));
          for(sInt j=0;j<op->GetStringMax();j++)
            fprintf(f," str%d \"%s\"",j,op->GetString(j) ? op->GetString(j) : "");
          fprintf(f," anim");
          sU8 *bc = op->GetAnimCode();
          while(bc)
          {
            sInt c = *bc++;
            fprintf(f," %02x",c);
            if(c==0x01) break;
            if(c>=0x80) bc++;
            else if(c<0x1e) bc += animLen[c];
            else { fprintf(f," ?"); break; }
          }
          fprintf(f,"\n");
        }
        if(f) fclose(f);
      }
#endif
    }
    Environment = new KEnvironment;
    Sound = 0;

    sInitPerlin();   
    GenOverlayInit();

    RenderTargetManager = new RenderTargetManager_;
    Engine = new Engine_;

    Game = new KKriegerGame;
    Game->Init();

    sFloatFix();
    i = sSystem->GetTime();
    Environment->Splines = &Document->Splines.Array;
    Environment->SplineCount = Document->Splines.Count;
    Environment->Game = Game;
    Environment->InitView();
    Environment->InitFrame(0,0);
    Document->Precalc(Environment);
    Environment->ExitFrame();

#if WAITFORKEY
    sSystem->WaitForKey();
#endif

    if(Document->SongSize)
    {
      // the VFX table (RenderSoundEffects) gives positions in samples, so
      // the player runs with 44100 ticks/s (music only ever plays from 0)
      Sound = new CV2MPlayer(44100);

      if(Document->SampleSize)
        RenderSoundEffects(Document,Document->SampleData);

      Sound->Open(Document->SongData);
      Sound->Play(0);
      SoundTimer = 0;
      sSystem->SetSoundHandler(IntroSoundHandler,64);
    }

    Game->ResetRoot(Environment,Document->RootOps[Document->CurrentRoot],1);
    if(getenv("KK_STARTSTATE"))         // debug: e.g. 0 = start directly in the game
    {
      Game->Switches[KGS_GAME] = atoi(getenv("KK_STARTSTATE"));
      Document->CurrentRoot = Game->GetNewRoot();
    }

    FirstTime = sSystem->GetTime();
    LastTime = 0;
    oldfps = 0.0f;

    sDPrintF("%d bytes of texture memory used\n",DebugTexMem);

    break;

  case sAPPCODE_PAINT:
    // tick processing (moved up to reduce input lag by 1 frame)

    ThisTime = sSystem->GetTime() - FirstTime;

    beat = sMulDiv(ThisTime,Document->SongBPM,60000);


    curfps = ThisTime - LastTime;
    oldfps += (curfps - oldfps) * 0.1f;
    GlobalFps = 1000.0f / oldfps;

    max = ThisTime/10-LastTime/10;
    if(max>10) max = 10;

    sFloatFix();
#if !defined(KK_SMALL) || defined(KK_COVERAGE)
    // debug: KK_FRAMELOG=1 prints every frame slower than 8 ms, split into
    // game tick / painting / rest (present, events, input), with the place
    flStart = framelog ? kkNanoTime() : 0;
    if(framelog && flLast && flStart-flLast>8000000)    // the frame that just ended
      fprintf(stderr,"frame %.1f ms: tick %.1f (%d steps) paint %.1f rest %.1f  pos=(%.1f %.1f %.1f) t=%d\n",
        (flStart-flLast)/1e6,flTickNS/1e6,flSteps,flPaintNS/1e6,(flStart-flLast-flTickNS-flPaintNS)/1e6,
        Game->PlayerPos.x,Game->PlayerPos.y,Game->PlayerPos.z,ThisTime);
#endif
    // linux port: the 2004 frame driver ran the game tick with the FPU set to
    // round toward -infinity (sFloatDen0, 0x143f). In that mode the Verlet
    // step (PhysicPart) pushes a resting player a little towards -x/-z every
    // frame, so he slowly slides (measured in the original too: 0.0002-0.007
    // units/s). The port keeps the default round-to-nearest: no sliding.
    Game->OnTick(Environment,max);
#if !defined(KK_SMALL) || defined(KK_COVERAGE)
    if(framelog) flTick = kkNanoTime();
#endif
    sSystem->Sample3DCommit();
    LastTime = ThisTime;

    sFloatFix();

    // root-switching logic and outermost stuff

    vp.Init();
    r = vp.Window;

    targetHeight = aspectRatios[IntroTargetAspect][0] * r.YSize() / (2 * aspectRatios[IntroTargetAspect][1]);

    vp.Window.y0 = (r.YSize() - targetHeight) / 2;
    vp.Window.y1 = (r.YSize() + targetHeight) / 2;

    /*vp.Window.y0 = r.YSize()/2 - r.XSize()/2/2;
    vp.Window.y1 = r.YSize()/2 + r.XSize()/2/2;*/
    vp.Window.Init(0,sSystem->ConfigY*1/6,sSystem->ConfigX,sSystem->ConfigY*5/6);
    GenOverlayManager->SetMasterViewport(vp);
    RenderTargetManager->SetMasterViewport(vp);

    sInt mode;
    mode = Game->GetNewRoot();

#ifdef KK_SMALL
    Document->CurrentRoot = mode;   // single root (KDoc::Init sets all RootOps to the last op)
#else
    if(mode!=Document->CurrentRoot && Document->RootOps[mode]==Document->RootOps[Document->CurrentRoot])
    {
      // linux port: the 2004 data has a single root; the 2004 player never
      // rebuilt the world (precalc, collision, music restart) on menu changes
      Document->CurrentRoot = mode;
    }
    else if(mode!=Document->CurrentRoot)
    {
      sSystem->SetSoundHandler(0,0);
      Document->CurrentRoot = mode;
      Environment->InitView();
      Environment->InitFrame(0,0);
      Document->Precalc(Environment);
      Environment->ExitFrame();
      Game->ResetRoot(Environment,Document->RootOps[Document->CurrentRoot],0);

      Sound->Open(Document->SongData);
      Sound->Play(0);
      sSystem->SetSoundHandler(IntroSoundHandler,64);
    }
#endif

    // timing

    Environment->InitFrame(beat,ThisTime);
    Document->AddEvents(Environment);
    Game->AddEvents(Environment);
    Game->FlushPhysic();

    // game painting

    clearvp.Init();

    sSystem->SetViewport(clearvp);
    sSystem->Clear(sVCF_ALL,0);

    Environment->GameCam.Init();
    Game->GetCamera(Environment->GameCam);
    

    //Environment->Aspect =  1.0f*vp.Window.XSize()/vp.Window.YSize();
    Environment->Aspect = 2.0f;

    root = Document->RootOps[Document->CurrentRoot];

#ifdef KK_VERBOSE
    {
      static sInt lastPrint = -100000;
      if(ThisTime-lastPrint>5000)
      {
        lastPrint = ThisTime;
        fprintf(stderr,"t=%d beat=%d root op%d cache=%p class=%d game state=%d\n",ThisTime,beat,root->OpId,
          root->Cache,root->Cache?root->Cache->ClassId:-1,Game->Switches[KGS_GAME]);
      }
    }
#endif
    if(beat>=0 && root->Cache && (root->Cache->ClassId==KC_DEMO || root->Cache->ClassId==KC_IPP))
    {
      GenOverlayManager->Reset(Environment);
      GenOverlayManager->RealPaint = sTRUE;
      GenOverlayManager->Game = Game;

      sFloatFix();
      {
        extern sBool kkDebugIPPDump;
        static const char *dumpAt = getenv("KK_IPPDUMP");
        static sBool dumped = sFALSE;
        kkDebugIPPDump = dumpAt && !dumped && ThisTime>=atoi(dumpAt);
        if(kkDebugIPPDump) dumped = sTRUE;
      }
      root->Exec(Environment);

      // 2004 data: the root is the last IPP operator, its result is copied
      // to the screen (what Exec_Misc_Demo does in the newer data)
      if(root->Cache->ClassId==KC_IPP && GenOverlayManager->LastOutput)
        GenOverlayManager->Copy(GenOverlayManager->LastOutput,
          GenOverlayManager->Alloc(0,GENOVER_RTSIZES,1),0,0xffffffff,1);

      GenOverlayManager->RealPaint = sFALSE;
      GenOverlayManager->Reset(Environment);
    }

    sFloatFix();
    Environment->ExitFrame();
    Environment->Mem.Flush();
//    sSystem->SetWinMouse(vp.Window.x1/2,vp.Window.y1/2);
#if !defined(KK_SMALL) || defined(KK_COVERAGE)
    if(framelog)
    {
      flTickNS = flTick-flStart;
      flPaintNS = kkNanoTime()-flTick;
      flSteps = max;
      flLast = flStart;
    }
#endif
    break;

  case sAPPCODE_KEY:
    Game->OnKey(value);
    if(value == (sKEY_ESCAPE|sKEYQ_SHIFT) || value==sKEY_CLOSE)
      sSystem->Exit();
    break;
  }

  return sTRUE;
}
