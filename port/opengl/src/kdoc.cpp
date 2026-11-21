#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// This file is distributed under a BSD license. See LICENSE.txt for details.

#include "kdoc.hpp"
#include "_viruz2.hpp"

#include "genbitmap.hpp"
#include "genmaterial.hpp"
#include "genmesh.hpp"
#include "genminmesh.hpp"
#include "genoverlay.hpp"
#include "genscene.hpp"
#include "geneffect.hpp"
#include "kkriegergame.hpp"


#define sUSE_TIME_OF_YEAR 0   // linux port: not in the 2004 release (pno0001.exe imports no GetSystemTime)
#define sOP_PERFORMANCE 0

#if sUSE_TIME_OF_YEAR
struct SYSTEMTIME
{
  sU16 wYear;
  sU16 wMonth;
  sU16 wDayOfWeek;
  sU16 wDay;
  sU16 wHour;
  sU16 wMinute;
  sU16 wSecond;
  sU16 wMilliseconds;
};

typedef sU64 FILETIME;

extern "C" void __stdcall GetSystemTime(SYSTEMTIME *lpSystemTime);
extern "C" sBool __stdcall SystemTimeToFileTime(const SYSTEMTIME *lpSystemTime,FILETIME *lpFileTime);
#endif

#if sOP_PERFORMANCE
extern "C" int __cdecl wsprintfA(char *dest,const char *format,...);
extern "C" void __stdcall OutputDebugStringA(const char *str);
#endif


/****************************************************************************/
/***                                                                      ***/
/***   Objects                                                            ***/
/***                                                                      ***/
/****************************************************************************/

KObject::KObject() 
{ 
  ClassId=KC_NULL; 
  RefCount = 1;
}

KObject::~KObject() 
{
}

void KObject::Copy(KObject *o) 
{
  ClassId=o->ClassId;
}

KObject *KObject::Copy()
{
  KObject *r;
  r = new KObject;
  r->Copy(this);
  return r;
}

/****************************************************************************/
/***                                                                      ***/
/***   Execution                                                          ***/
/***                                                                      ***/
/****************************************************************************/

static sInt PrecalcCount,PrecalcMax;

#if sOP_PERFORMANCE
static sInt OpPerf[256];
#endif

sInt KOp::Calc(KEnvironment *env,sInt flags)
{
  sInt i;
  sInt pops;
  sInt changed;

// early break recursion
  if(SkipCalc && !Changed && Cache)
    return 0;

  sFloatFix();

// cycle check start


// calculate animation

  if(Changed||!Cache)
    sCopyMem(DataAnim,DataEdit,DataMax*4);

  SkipCalc = sTRUE;
  pops = env->ExecuteAnim(this,AnimCode);

// find changed

  changed = Changed;
  if(Cache==0 && (flags&KCF_NEED))
    changed = sTRUE;
  if(Cache && !changed)
    flags &= ~KCF_NEED;

// skip exec calculation

  SkipExec = sFALSE;
  if(Convention&OPC_SKIPEXEC)
    SkipExec = sTRUE;
  if(AnimCode[0]!=KA_END)
    SkipExec = sFALSE;

// recursion

  for(i=0;i<InputCount;i++)
  {
    if(Input[i])
    {
      changed |= Input[i]->Calc(env,flags&~KCF_ROOT);
      UpdateVar(Input[i]->VarStart,Input[i]->VarCount);
      SkipExec &= Input[i]->SkipExec;
      SkipCalc &= Input[i]->SkipCalc;
    }
  }
  if(!(Convention & OPC_DONTCALLLINK))
  {
    for(i=0;i<LinkMax;i++)
    {
      if(Link[i])
      {
        changed |= Link[i]->Calc(env,flags&~KCF_ROOT);
        UpdateVar(Link[i]->VarStart,Link[i]->VarCount);
        SkipExec &= Link[i]->SkipExec;
        SkipCalc &= Link[i]->SkipCalc;
      }
    }
  }

  if(changed)
    sVERIFY(flags & KCF_NEED);

// calculate

  if(changed)
  {
    if(Cache)
    {
      Cache->Release();
      Cache = 0;
    }

#if sOP_PERFORMANCE
    sU32 stime = sSystem->GetTime();
#endif

    Cache = Call(env);
#if !defined(KK_SMALL) || defined(KK_COVERAGE)
    {
      // verification aid for the size build: KK_HASHOPS=file appends a hash
      // of every generated bitmap/mesh (op id, class, hash) when it is made
      static const char *hashfile = getenv("KK_HASHOPS");
      if(hashfile && Cache && (Cache->ClassId==KC_BITMAP || Cache->ClassId==KC_MESH))
      {
        sU32 h = 2166136261u;
        #define KKHASH(ptr,len) for(sInt hk=0;hk<(sInt)(len);hk++) h = (h ^ ((const sU8 *)(ptr))[hk]) * 16777619u;
        if(Cache->ClassId==KC_BITMAP)
        {
          GenBitmap *bm = (GenBitmap *) Cache;
          KKHASH(&bm->XSize,8);
          if(bm->Data) KKHASH(bm->Data,bm->Size*8);
        }
        else
        {
          // (only the meaningful fields: Temp* are scratch and may be uninitialised)
          GenMesh *m = (GenMesh *) Cache;
          KKHASH(&m->Vert.Count,4);
          for(sInt k=0;k<m->Vert.Count;k++) { GenMeshVert *v = &m->Vert[k]; KKHASH(v,4); KKHASH(&v->Next,8); KKHASH(v->Weight,8); }
          KKHASH(&m->Edge.Count,4);
          for(sInt k=0;k<m->Edge.Count;k++) { GenMeshEdge *e = &m->Edge[k]; KKHASH(e,4); KKHASH(e->Next,32); KKHASH(&e->Crease,4); }
          KKHASH(&m->Face.Count,4);
          for(sInt k=0;k<m->Face.Count;k++) { GenMeshFace *fc = &m->Face[k]; KKHASH(fc,4); KKHASH(&fc->Material,8); }
          KKHASH(&m->VertCount,4);
          for(sInt k=0;m->VertBuf && k<m->VertCount;k++)
            for(sInt c=0;c<m->VertSize();c++) { sVector *vb = &m->VertBuf[k*m->VertSize()+c]; KKHASH(vb,12); }
        }
        #undef KKHASH
        FILE *f = fopen(hashfile,"a");
        if(f) { fprintf(f,"op %d class %d hash %08x\n",OpId,Cache->ClassId,h); fclose(f); }
      }
    }
#endif
    {
      // debug: KK_DUMPOP="id,id,.." writes the bitmap of these ops as bmp_op<id>.tga
      static const char *dumpops = getenv("KK_DUMPOP");
      if(dumpops && Cache && Cache->ClassId==KC_BITMAP)
      {
        for(const char *q=dumpops;q && *q;q=strchr(q,',')?strchr(q,',')+1:0)
        {
          if(atoi(q)!=OpId) continue;
          GenBitmap *bm = (GenBitmap *) Cache;
          char name[64];
          snprintf(name,sizeof(name),"bmp_op%04d.tga",OpId);
          FILE *f = fopen(name,"wb");
          sU8 hdr[18] = {0,0,2, 0,0,0,0,0, 0,0,0,0, 0,0,0,0, 32,0x28};
          hdr[12] = bm->XSize&255; hdr[13] = bm->XSize>>8; hdr[14] = bm->YSize&255; hdr[15] = bm->YSize>>8;
          fwrite(hdr,1,18,f);
          for(sInt k=0;k<bm->XSize*bm->YSize;k++)
          {
            sU16 *c = (sU16 *)&bm->Data[k];   // 15 bit per channel, b g r a
            sU8 px[4] = { (sU8)(c[0]>>7), (sU8)(c[1]>>7), (sU8)(c[2]>>7), (sU8)(c[3]>>7) };
            fwrite(px,1,4,f);
          }
          fclose(f);
          fprintf(stderr,"dumped bitmap op%d %dx%d\n",OpId,bm->XSize,bm->YSize);
        }
      }
    }

#if sOP_PERFORMANCE
    OpPerf[Command] += sSystem->GetTime() - stime;
#endif


    CalcError = (Cache==0);
    CacheCount = OutputCount;
    Changed = 0;
  }

// done

  env->Pop(pops);

  if(flags & KCF_PRECALC)
  {
    for(sInt j=0;j<GetInputCount();j++)
      GetInput(j)->CalcUsed();

    for(sInt j=0;j<GetLinkMax();j++)
      GetLink(j)->CalcUsed();

    sSystem->Progress(PrecalcCount,PrecalcMax);
    if(changed)
      PrecalcCount++;
  }
  return changed;
}

/****************************************************************************/

#pragma warning(disable : 4731)   // EPB CHANGED WARNING

// linux port: implemented in NASM (linux/callcode.asm): the MSVC inline asm
// version rebuilt the frame in ebp/esi, which conflicts with clang's frame
// and stack realignment handling.
extern "C" sInt kkCallCode(sInt code,const sInt *para,sInt count);
static sInt CallCode(sInt code,sInt *para,sInt count)
{
  return kkCallCode(code,para,count);
}

#pragma warning(default : 4731)

/****************************************************************************/

KObject *KOp::Call(KEnvironment *kenv)
{
  sU32 data[KK_MAXINPUT+128];
  sInt p,pNoPara;
  sInt i,max;
  KObject *o;
  KOp *op;
  KObject *result;
  sInt error;

  p = 0;

// update

  if(Convention&(OPC_KOP|OPC_ALTINIT))
  {
    data[p++] = (sU32) this;
  }
  if(Convention&OPC_KENV)
  {
    data[p++] = (sU32) kenv;
  }

  pNoPara = p;

// inputs
  max = OPC_GETINPUT(Convention);
  for(i=0;i<max;i++)
  {
    op = GetInput(i);

    if(op)
    {
      o = op->Cache;
      if(o==0)
        error = 1;
      else
        o->AddRef();
      data[p++] = (sU32) o;
    }
    else
    {
      data[p++] = 0;
    }
  }

// links

  max = OPC_GETLINK(Convention);
  for(i=0;i<max;i++)
  {
    if(Convention & OPC_DONTCALLLINK)
    {
      data[p++] = (sU32) Link[i];
    }
    else
    {
      o = (Link[i] ? Link[i]->Cache : 0);
      if(o)
        o->AddRef();
      data[p++] = (sU32) o;
    }
  }

// normal parameters

  max = OPC_GETDATA(Convention);
  for(i=0;i<max;i++)
    data[p++] = *GetAnimPtrU(i);

// strings

  max = OPC_GETSTRING(Convention);
  for(i=0;i<max;i++)
    data[p++] = (sU32) GetString(i);

// splines

  max = OPC_GETSPLINE(Convention);
  for(i=0;i<max;i++)
    data[p++] = (sU32) GetSpline(i);

// outputcount

  if(Convention&OPC_OUTPUTCOUNT)
    data[p++] = OutputCount;

// unlimited inputs

  if(Convention&OPC_VARIABLEINPUT)
  {
    data[p++] = InputCount;
    for(i=0;i<InputCount;i++)
    {
      if(Input[i] && Input[i]->Cache && p<KK_MAXINPUT+128)
      {
        Input[i]->Cache->AddRef();
        data[p++] = (sU32) Input[i]->Cache;
      }
      else
        error = 1;
    }
  }

// call!


  {
    if(Convention&OPC_ALTINIT)
      p = pNoPara;

    result = (KObject *)CallCode((sInt)InitHandler,(sInt *)data,p);
  }

// cleanup in case of failure


  return result;
}

/****************************************************************************/

void KOp::ExecWithNewMem(KEnvironment *kenv,KInstanceMem **link)
{
  KInstanceMem *oldnext,**oldlink;

  oldnext = kenv->NextInstance;
  oldlink = kenv->LinkInstance;

  if(*link)
  {
    kenv->NextInstance = *link;
    kenv->LinkInstance = 0;
  }
  else
  {
    kenv->NextInstance = 0;
    kenv->LinkInstance = link;
  }

  Exec(kenv);

  kenv->NextInstance = oldnext;
  kenv->LinkInstance = oldlink;
}

sBool kkDebugIPPDump = sFALSE;
void kkDebugSaveTexture(sInt handle,const char *name);

void KOp::Exec(KEnvironment *kenv)
{
  sU32 data[KK_MAXINPUT+128];
  sInt p;
  sInt i,max;
  sInt pops;

  p = 0;

  if(Result==KC_BITMAP)       // Warum dürfen Bitmaps hier raus?
    return;


// do animation

  pops = kenv->ExecuteAnim(this,AnimCode);

// the simple case...

  if(Convention&OPC_ALTEXEC)
  {
    ((void (__stdcall *)(KOp *,KEnvironment *))ExecHandler)(this,kenv);
  }
  else
  {

// parameter-case

    data[p++] = (sU32) this;              // obligatorische parameter
    data[p++] = (sU32) kenv;              

    max = OPC_GETDATA(Convention);        // normal parameters
    sCopyMem(data+p,GetAnimPtrU(0),max*sizeof(sU32));
    p += max;

    max = OPC_GETSTRING(Convention);      // strings
    for(i=0;i<max;i++)
      data[p++] = (sU32) GetString(i);

    max = OPC_GETSPLINE(Convention);      // splines
    for(i=0;i<max;i++)
      data[p++] = (sU32) GetSpline(i);

    if(Convention&OPC_OUTPUTCOUNT)        // outputcount
      data[p++] = OutputCount;

    CallCode((sInt)ExecHandler,(sInt *)data,p);   // call
  }

// end animation

  kenv->Pop(pops);
  WheelSpeed = sMax(WheelSpeed,96);

  // debug: dump every IPP op's output in the frame flagged by mainplayer
#ifndef KK_SMALL
  if(kkDebugIPPDump && Cache && Cache->ClassId==KC_IPP && GenOverlayManager->LastOutput
     && GenOverlayManager->LastOutput->Bitmap)
  {
    char name[64];
    snprintf(name,sizeof(name),"ipp_op%04d_%02x.tga",OpId,Command);
    kkDebugSaveTexture(GenOverlayManager->LastOutput->Bitmap->Texture,name);
  }
#endif
}

/****************************************************************************/
/****************************************************************************/

void KOp::ExecInputs(KEnvironment *kenv)
{
  sInt i,max;
  KOp *op;
  
  max = GetInputCount();
  for(i=0;i<max;i++)
  {
    op = GetInput(i);
    sVERIFY(op);
    op->Exec(kenv);
  }
  if(!(Convention & OPC_DONTCALLLINK))
  {
    max = GetLinkMax();
    for(i=0;i<max;i++)
    {
      op = GetLink(i);
      if(op)
        op->Exec(kenv);
    }
  }
}

void KOp::ExecInput(KEnvironment *kenv,sInt i)
{
  KOp *op;

  op = GetInput(i);
  if(op)
    op->Exec(kenv);
}


void KOp::ExecEvent(KEnvironment *kenv,KEvent *event,sBool)
{
  sVector save[8];
  KEvent *ce;
  sInt i;
  sF32 time;

  KSpline *oldspline;
  struct KKriegerMonster *oldmon;

  for(i=0;i<8;i++)                          // save all
    save[i] = kenv->Var[i];

  oldmon = kenv->EventMonster;
  oldspline = kenv->EventSpline;
  //oldsector = kenv->CurrentSector;
  ce = kenv->CurrentEvent;

  time = 0;                                 // calculate time
  if(event->Start<event->End)
    time = 1.0f * (kenv->BeatTime - event->Start) / (event->End-event->Start);

  time = sRange<sF32>(time,1,0);
  time = event->StartInterval + time * (event->EndInterval - event->StartInterval);

//  sDPrintF("%08x:%08x / %08x / %08x -> %f\n",this,event->Start,event->End,kenv->BeatTime,time);

  kenv->Var[0].InitS(time); // set variables
  kenv->Var[1].InitS(event->Velocity);
  kenv->Var[2].InitS(event->Modulation);
  kenv->Var[3].InitS(sFtol(event->Select));
  kenv->Var[4] = event->Scale;
  kenv->Var[5] = event->Rotate;
  kenv->Var[6] = event->Translate;
  kenv->Var[7].InitColor(event->Color);

  // time of year computation
#if sUSE_TIME_OF_YEAR
  SYSTEMTIME systemTime;
  sU64 timeYear,startYear,endYear;

  GetSystemTime(&systemTime);
  SystemTimeToFileTime(&systemTime,(FILETIME *) &timeYear);

  systemTime.wMonth = 1;
  systemTime.wDay = 1;
  systemTime.wHour = systemTime.wMinute = systemTime.wSecond = 0;
  systemTime.wMilliseconds = 0;
  SystemTimeToFileTime(&systemTime,(FILETIME *) &startYear);

  systemTime.wYear++;
  SystemTimeToFileTime(&systemTime,(FILETIME *) &endYear);

  kenv->Var[3].w = 1.0 * (timeYear - startYear) / (endYear - startYear);
#endif

  if(event->Spline)                         // set spline
    kenv->EventSpline = event->Spline;
  kenv->EventMonster = event->Monster;
  kenv->CurrentEvent = event;               // set event

  kenv->ExecStack.PushMul(event->Matrix);
  ExecWithNewMem(kenv,&event->FirstInstance);
  kenv->ExecStack.Pop();

  kenv->EventSpline = oldspline;
  kenv->EventMonster = oldmon;
  kenv->CurrentEvent = ce;
  for(i=0;i<8;i++)
    kenv->Var[i] = save[i];
}

void KOp::Change(sInt input)
{
  sInt i;

  if(Changed) return;
/*
  if(Update && input>=0 && input<32 && (ChangeMask & (1<<input)))
  {
    sCopyMem(Update->Data,GetAnimPtr(0),sMax(4*DataMax,128));
    return;
  }
*/
  WheelSpeed = 255;
  Changed = 1;
  for(i=0;i<OutputCount;i++)
    if(Output[i])
      Output[i]->Change(-1);
}

sBool KOp::CheckOutput(sInt kc)
{
  if(!this) return sFALSE;
  if(!Cache || CacheFreed)
  {
    if(!Result)
      return sFALSE;
    else if(kc!=KC_ANY && Result!=kc)
      return sFALSE;
  }
  else
    if(kc!=KC_ANY && Cache->ClassId!=kc)
      return sFALSE;
  return sTRUE;
}

void KOp::UpdateVar(sInt start,sInt count)
{
  sInt min,max;
  if(count)
  {
    if(VarCount==0)
    {
      VarStart = start;
      VarCount = count;
    }
    else
    {
      min = VarStart;
      max = VarStart+VarCount;

      if(start<min)
        min = start;
      if(start+count>max)
        max = start+count;

      VarStart = min;
      VarCount = max-min;
    }
  }
}

sBool AnimCodeWritesTo(sU8 *code,sInt offset)
{
  sU8 mask,val;

  while(*code!=KA_END)
  {
    if(*code>=0x80)
    {
      mask = code[0];
      val = code[1];
      if((mask&1) && val+0==offset) return sTRUE;
      if((mask&2) && val+1==offset) return sTRUE;
      if((mask&4) && val+2==offset) return sTRUE;
      if((mask&8) && val+3==offset) return sTRUE;
    }
    code += CalcCmdSize(code);
  }
  return sFALSE;
}

void KOp::CalcUsed()
{
  if(this && !--CacheCount && Cache && !CacheFreed)
  {
    if(Cache->ClassId == KC_BITMAP || Cache->ClassId == KC_MESH)
    {
      Result = Cache->ClassId;
      Cache->Release();
      CacheFreed = sTRUE;
      // sollte die variable nicht auch auf 0 gesetzt werden?
      // nein, sollte sie nicht! -ryg
    }
  }
}

/****************************************************************************/
/***                                                                      ***/
/***   Environment                                                        ***/
/***                                                                      ***/
/****************************************************************************/

void KInstanceMem::DeleteChain()
{
  KInstanceMem *next,*mem;

  next = this;
  while(next)
  {
    mem = next;
    next = mem->Next;
    if(mem->DeleteArray)
      delete[] mem->DeleteArray;
    if(mem->DeleteChild && *(mem->DeleteChild))
    {
      (*(mem->DeleteChild))->DeleteChain();
      (*(mem->DeleteChild)) = 0;
    }
    if(mem->DeleteChild2 && *(mem->DeleteChild2))
    {
      (*(mem->DeleteChild2))->DeleteChain();
      (*(mem->DeleteChild2)) = 0;
    }
    delete mem;
  }
}

KEnvironment::KEnvironment()
{
  sInt i;

  EventSpline = 0;
  EventMonster = 0;
  Splines = 0;
  SplineCount = 0;
  //Mem.Init(256*1024);
  Mem.Init(256*1024);
  LastTime = 0;
  TimeReset = 1;
  DefaultInstance = 0;
  NextInstance = 0;
  LinkInstance = 0;
  DynamicEvents.Init();
  EventOpsCleanup.Init();
  InitFrame(0,0);
  ClearInstanceMem = 0;
  sSetMem(Letters,0,sizeof(Letters));
  for(i=0;i<64;i++)
  {
    Letters[0][i+0x40].UV.x0 = (i&7)*0.125f;
    Letters[0][i+0x40].UV.y0 = (i/8)*0.125f;
    Letters[0][i+0x40].UV.x1 = (i&7)*0.125f+0.125f;
    Letters[0][i+0x40].UV.y1 = (i/8)*0.125f+0.125f;
  }
  Game = 0;
  ExecStack.Init();
}

KEnvironment::~KEnvironment()
{
  InitView();
  InitFrame(0,0);
  ExitFrame();
  Mem.Exit();
  DynamicEvents.Exit();
  EventOpsCleanup.Exit();
  ExecStack.Exit();
}

void KEnvironment::InitView()
{
  sInt i;

  for(i=0;i<DynamicEvents.Count;i++)
  {
    DynamicEvents[i]->FirstInstance->DeleteChain();
    delete DynamicEvents[i];
  }
  DynamicEvents.Count = 0;
  ClearInstanceMem = 1;
  DefaultInstance->DeleteChain();
  DefaultInstance = 0;
  NextInstance = 0;
  LinkInstance = 0;
  Aspect = 1.0f;

  BeatTime = 0;
  CurrentTime = 0;
  LastTime = 0;
  TimeDelta = 0;
  TimeSlices = 0;
  TimeJitter = 0;
  TimeReset = 1;

  for(sInt i=0;i<sCOUNTOF(Markers);i++)
    Markers[i].Init();

  if(Game)
    Game->Monsters.Count=0;
}

void KEnvironment::InitFrame(sInt timebeat,sInt timems)
{
  sInt i;

  sSetMem(Var,0,sizeof(Var));
  Var[0].Init(timebeat/65536.0f,timebeat/65536.0f,timebeat/65536.0f,timebeat/65536.0f);
  Var[4].Init(1,1,1,0);
  sSetMem(Stack,0,sizeof(Stack));
  sSetMem(StackAdr,0,sizeof(StackAdr));
  Index = 0;
  GameCam.Init();
  CurrentCam.Init();
  ExecStack.PopAll();
  EventSpline = 0;
  EventMonster = 0;
  CurrentEvent = 0;

  BeatTime = timebeat;
  LastTime = CurrentTime;
  CurrentTime = timems;
  TimeDelta = CurrentTime-LastTime;
  if(TimeDelta<0)
  {
    TimeReset = 1;
  }
  else
  {
    TimeSlices = (CurrentTime/10)-(LastTime/10);
    TimeJitter = (CurrentTime%10);
    TimeReset =0;
  }
  if(TimeReset)
  {
    TimeDelta = 0;
    TimeSlices = 0;
    TimeJitter = 0;
  }

  // add dynamic events

  sVERIFY(EventOpsCleanup.Count == 0);
  for(i=0;i<DynamicEvents.Count;i++)
    AddStaticEvent(DynamicEvents[i]);

  // set up instance memory

  NextInstance = DefaultInstance;
  LinkInstance = 0;
  if(!DefaultInstance)
    LinkInstance = &DefaultInstance;

  NextMonsterOverride=0;
  NextMonsterKillSwitch=0;
  NextMonsterSpawnSwitch=0;
  NextMonsterFlags=0;
}

void KEnvironment::ExitFrame()
{
  sInt i;
  KEvent *ev;

  for(i=0;i<EventOpsCleanup.Count;i++)
    EventOpsCleanup[i]->FirstEvent = 0;

  for(i=0;i<DynamicEvents.Count;)
  {
    ev = DynamicEvents[i];
    if(ev->End!=ev->Start && BeatTime >= ev->End)
    {
      ev->FirstInstance->DeleteChain();
      DynamicEvents[i]= DynamicEvents[--DynamicEvents.Count];
      delete ev;
    }
    else
    {
      i++;
    }
  }
  EventOpsCleanup.Count = 0;
  ClearInstanceMem = 0;
}

void KEnvironment::AddDynamicEvent(KEvent *event)
{
  *DynamicEvents.Add() = event;
}

void KEnvironment::AddStaticEvent(KEvent *event)
{
  if(event->Start==event->End || (BeatTime>=event->Start && BeatTime<event->End))
  {
    if(ClearInstanceMem)
    {
      event->FirstInstance->DeleteChain();
      event->FirstInstance = 0;
    }
    if(event->Op->FirstEvent==0)
      *EventOpsCleanup.Add() = event->Op;
    event->NextOp = event->Op->FirstEvent;
    event->Op->FirstEvent = event;
  }  
}

/****************************************************************************/
/***                                                                      ***/
/***   Animation                                                          ***/
/***                                                                      ***/
/****************************************************************************/

#define STACKMAX 256

sInt KEnvironment::ExecuteAnim(struct KOp *op,sU8 *bytecode)
{
  sInt pop;
  sInt cmd,cmd2;
  sInt index;
  static sVector stack[STACKMAX+4];
  sVector *p;
  sS32 *destint;
  sU8 *destbyte;
  sU8 bval;
  sF32 *destfloat;
  sF32 fval;
  sBool changed,cp;
  sInt i;
  sMatrix *mat;

  pop=0;
  changed = 0;
  p = &stack[2];

  for(;;)
  {
    cmd2 = cmd = *bytecode++;
    if(cmd2>=0x80)
      cmd2 &= 0xf0;
    // if you change something here, remember to also change KDoc::Init

    switch(cmd2)
    {
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_NOP:
      break;
#endif
    case KA_END:
      goto ende;
    case KA_LOADVAR:
      index = *bytecode++;
      sVERIFY(index<KK_MAXVAR);
      *p = Var[index];
      p++;
      op->UpdateVar(index,1);
      break;
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_LOADPARA1:
      index = *bytecode++;
      sVERIFY(index<op->GetDataWords());
      fval = ((sF32 *)op->DataEdit)[index];
      p->x = fval;
      p->y = fval;
      p->z = fval;
      p->w = fval;
      p++;
      break;
#endif
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_LOADPARA2:
      index = *bytecode++;
      sVERIFY(index+1<op->GetDataWords());
      p->x = ((sF32 *)op->DataEdit)[index+0];
      p->y = ((sF32 *)op->DataEdit)[index+1];
      p->z = 0;
      p->w = 0;
      p++;
      break;
#endif
    case KA_LOADPARA3:
      index = *bytecode++;
      sVERIFY(index+2<op->GetDataWords());
      p->x = ((sF32 *)op->DataEdit)[index+0];
      p->y = ((sF32 *)op->DataEdit)[index+1];
      p->z = ((sF32 *)op->DataEdit)[index+2];
      p->w = 0;
      p++;
      break;
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_LOADPARA4:
      index = *bytecode++;
      sVERIFY(index+3<op->GetDataWords());
      p->x = ((sF32 *)op->DataEdit)[index+0];
      p->y = ((sF32 *)op->DataEdit)[index+1];
      p->z = ((sF32 *)op->DataEdit)[index+2];
      p->w = ((sF32 *)op->DataEdit)[index+3];
      p++;
      break;
#endif
    case KA_SWIZZLEX:
      p[-1].x = p[-1].x;
      p[-1].y = p[-1].x;
      p[-1].z = p[-1].x;
      p[-1].w = p[-1].x;
      break;
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_SWIZZLEY:
      p[-1].x = p[-1].y;
      p[-1].y = p[-1].y;
      p[-1].z = p[-1].y;
      p[-1].w = p[-1].y;
      break;
#endif
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_SWIZZLEZ:
      p[-1].x = p[-1].z;
      p[-1].y = p[-1].z;
      p[-1].z = p[-1].z;
      p[-1].w = p[-1].z;
      break;
#endif
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_SWIZZLEW:
      p[-1].x = p[-1].w;
      p[-1].y = p[-1].w;
      p[-1].z = p[-1].w;
      p[-1].w = p[-1].w;
      break;
#endif
    case KA_ADD:
      p--;
      p[-1].Add4(*p);
      break;
    case KA_SUB:
      p--;
      p[-1].Sub4(*p);
      break;
    case KA_MUL:
      p--;
      p[-1].Mul4(*p);
      break;
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_DIV:
      p--;
      p[-1].x /= p->x;
      p[-1].y /= p->y;
      p[-1].z /= p->z;
      p[-1].w /= p->w;
      break;
#endif
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_MOD:
      p--;
      p[-1].x = sFMod(p[-1].x,p->x);
      p[-1].y = sFMod(p[-1].y,p->y);
      p[-1].z = sFMod(p[-1].z,p->z);
      p[-1].w = sFMod(p[-1].w,p->w);
      break;
#endif
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_NEG:
      p[-1].x = -p[-1].x;
      p[-1].y = -p[-1].y;
      p[-1].z = -p[-1].z;
      p[-1].w = -p[-1].w;
      break;
#endif
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_INVERT:
      p[-1].x = 1-p[-1].x;
      p[-1].y = 1-p[-1].y;
      p[-1].z = 1-p[-1].z;
      p[-1].w = 1-p[-1].w;
      break;
#endif
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_SIN:
      p[-1].x = p[-1].y = p[-1].z = p[-1].w = sFSin(p[-1].x*sPI2F);
      break;
#endif
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_COS:
      p[-1].x = p[-1].y = p[-1].z = p[-1].w = sFCos(p[-1].x*sPI2F);
      break;
#endif
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_PULSE:
      fval = sFMod(p[-1].x,1.0);
      if(fval < 0.0f)
        fval += 1.0f;
      p[-1].x = p[-1].y = p[-1].z = p[-1].w = fval<0.5f ? 1.0f : 0.0f;
      break;
#endif
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_RAMP:
      fval = sFMod(p[-1].x,1.0f);
      if(fval < 0.0f)
        fval += 1.0f;
      p[-1].x = p[-1].y = p[-1].z = p[-1].w = fval;
      break;
#endif
    case KA_CONSTV:
      *p = *(sVector *)bytecode;
      bytecode+=16;
      p++;
      break;
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_CONSTC:
      p->x = (*bytecode++)/255.0f;
      p->y = (*bytecode++)/255.0f;
      p->z = (*bytecode++)/255.0f;
      p->w = (*bytecode++)/255.0f;
      p++;
      break;
#endif
    case KA_CONSTS:
      fval = *(sF32 *)bytecode;
      bytecode+=4;
      p->x = fval;
      p->y = fval;
      p->z = fval;
      p->w = fval;
      p++;
      break;
    case KA_SPLINE:
      i = *(sU16 *)bytecode;
      bytecode+=2;
      fval = p[-1].x;
      p[-1].Init();
      (*Splines)[i].Eval(fval,p[-1]);
      break;
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_EVENTSPLINE:
      fval = p[-1].x;
      p[-1].Init();
      if(EventSpline)
        EventSpline->Eval(fval,p[-1]);
      break;
#endif
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_MATRIX:
      mat = (sMatrix *) &Var[KV_MATRIX_I];
      p[-1].Rotate4(*mat);
      break;
#endif
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_NOISE:
      fval = sFMod(p[-1].x,1.0);
      if(fval < 0.0f)
        fval += 1.0f;
      i = fval * 65536;
      i = sPerlinPermute[(i >> 8) & 0xff] | (sPerlinPermute[i & 0xff] << 8);
      p[-1].x = p[-1].y = p[-1].z = p[-1].w = i / 65535.0f;
      break;
#endif
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_EASE:
      {
        sF32 ei,eo,d;
        ei = *(sF32 *)bytecode; bytecode+=4;
        eo = *(sF32 *)bytecode; bytecode+=4;

        if(ei>0.5f) ei = 0.5f;
        if(eo>0.5f) eo = 0.5f;
        eo = 1-eo;
        d = eo-ei;
        if(d<0.1f)
        {
          eo += (0.1-d)/2;
          ei -= (0.1-d)/2;
          d = eo-ei;
        }

        sF32 a,c,s;
        s = 1/d;

        for(sInt i=0;i<4;i++)
        {
          fval = (&p[-1].x)[i];
          if(fval<0)                        // too small
          {
            fval = -ei*s/2;
          }
          else if(fval<ei)                  // ease in
          {
            a = -ei*s/2;
            c = s/(2*ei);
            fval = a+fval*fval*c;
          }
          else if(fval<eo)                  // linear
          {
            fval = (fval-ei)*s;
          }
          else if(fval<1)                   // ease out
          {
            a = -(1-eo)*s/2;
            c = s/(2*(1-eo));
            fval = 1-a-(1-fval)*(1-fval)*c;
          }
          else                              // too large
          {
            fval = 1+(1-eo)*s/2;
          }

          fval = (fval+(ei*s/2))/(1+ei*s/2+(1-eo)*s/2);

          (&p[-1].x)[i] = fval;
        }
      }
      break;
#endif
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_STOREVAR:
      index = *bytecode++;
      sVERIFY(index<KK_MAXVAR);
      p--;
      sVERIFY(Index<KK_MAXVARSAVE);
      Stack[Index] = Var[index];
      StackAdr[Index] = index;
      Index++;
      pop++;
      if(cmd&0x01) Var[index].x = p->x;
      if(cmd&0x02) Var[index].y = p->y;
      if(cmd&0x04) Var[index].z = p->z;
      if(cmd&0x08) Var[index].w = p->w;
      break;
#endif
    case KA_STOREPARAFLOAT:
    case KA_CHANGEPARAFLOAT:
      index = *bytecode++;
      sVERIFY(index<op->GetDataWords());
      p--;
      destfloat = (sF32 *)(op->DataAnim+index);
      cp = 0;

      if(cmd&0x01) { if(destfloat[0]!=p->x) cp=1; destfloat[0]=p->x; }
      if(cmd&0x02) { if(destfloat[1]!=p->y) cp=1; destfloat[1]=p->y; }
      if(cmd&0x04) { if(destfloat[2]!=p->z) cp=1; destfloat[2]=p->z; }
      if(cmd&0x08) { if(destfloat[3]!=p->w) cp=1; destfloat[3]=p->w; }
      if(cmd2==KA_CHANGEPARAFLOAT) changed|=cp;
      break;
#ifndef KK_SMALL   // not used by the kkrieger data (KK_OPSTATS)
    case KA_STOREPARAINT:
    case KA_CHANGEPARAINT:
      index = *bytecode++;
      sVERIFY(index<op->GetDataWords());
      p--;
      destint = (sS32 *)(op->DataAnim+index);
      cp = 0;
      if(cmd&0x01) { if(destint[0]!=p->x) cp=1; destint[0]=p->x; }
      if(cmd&0x02) { if(destint[1]!=p->y) cp=1; destint[1]=p->y; }
      if(cmd&0x04) { if(destint[2]!=p->z) cp=1; destint[2]=p->z; }
      if(cmd&0x08) { if(destint[3]!=p->w) cp=1; destint[3]=p->w; }
      if(cmd2==KA_CHANGEPARAINT) changed|=cp;
      break;
#endif
    case KA_STOREPARABYTE:
    case KA_CHANGEPARABYTE:
      index = *bytecode++;
      sVERIFY(index<op->GetDataWords());
      p--;
      destbyte = (sU8 *)(op->DataAnim+index);
      cp = 0;

      if(cmd&0x01) { bval=sRange<sInt>(p->x*255,255,0); if(destbyte[0]!=bval) cp=1; destbyte[0]=bval; }
      if(cmd&0x02) { bval=sRange<sInt>(p->y*255,255,0); if(destbyte[1]!=bval) cp=1; destbyte[1]=bval; }
      if(cmd&0x04) { bval=sRange<sInt>(p->z*255,255,0); if(destbyte[2]!=bval) cp=1; destbyte[2]=bval; }
      if(cmd&0x08) { bval=sRange<sInt>(p->w*255,255,0); if(destbyte[3]!=bval) cp=1; destbyte[3]=bval; }
      if(cmd2==KA_CHANGEPARABYTE) changed|=cp;
      break;

    default:
#ifndef KK_SMALL
      sFatal("unknown opcode in animation bytecode");
#endif
      break;
    }

    sVERIFY(p>=stack+2);
    sVERIFY(p<stack+2+STACKMAX);
  }
ende:

  sVERIFY(p==stack+2);
  if(changed)
  {
    op->WheelSpeed = 255;
    op->SkipCalc = 0;
//    op->Changed = 1;
  }
  return pop;
}

sInt CalcCmdSize(sU8 *bytecode)
{
  static sU8 CmdSize[] =
  {
      0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x00-0x0f
      0, 0, 0, 0, 0, 0,16, 4, 4, 2, 0, 0, 0, 8,       // 0x10-0x1d
  };
  sU8 j;

  j = *bytecode;
  if(j >= 0x80)
    return 1+1;
  else
    return 1+CmdSize[j];
}

sInt CalcCodeSize(sU8 *bytecode)
{
  sU8 *data,j;

  data = bytecode;
  do
  {
    j = *data;
    data += CalcCmdSize(data);
  }
  while(j!=KA_END);

  return data - bytecode;
}

void KEnvironment::Pop(sInt count)
{
  while(count>0)
  {
    Index--;
    count--;
    sVERIFY(Index>=0);
    Var[StackAdr[Index]] = Stack[Index];
  }
}

void *KEnvironment::GetInstImpl(KOp *me,sInt size)
{
  KInstanceMem *mem;
  if(NextInstance)
  {
    mem = NextInstance;
    sVERIFY(mem->Operator == me);
    sVERIFY(LinkInstance==0);
    mem->Reset = 0;
    NextInstance = mem->Next;
  }
  else
  {
    sVERIFY(LinkInstance);
    mem = (KInstanceMem *) new sU8[size];
    sSetMem(mem,0,size);
    *LinkInstance = mem;
    LinkInstance = &mem->Next;
    mem->Operator = me;
    mem->Reset = 1;
  }
  return mem;
}

void KEnvironment::SetMatrix(sMatrix &mat,sMatrix &save)
{
  sMatrix *var;

  var = (sMatrix *) &Var[KV_MATRIX_I];
  save = *var;
  *var = mat;
}

void KEnvironment::RestoreMatrix(sMatrix &save)
{
  sMatrix *var;

  var = (sMatrix *) &Var[KV_MATRIX_I];
  *var = save;
}

/****************************************************************************/
/***                                                                      ***/
/***   Splines                                                            ***/
/***                                                                      ***/
/****************************************************************************/

sF32 KSplineChannel::Eval(sF32 time,sInt inter)
{
  //sF32 val;
  sInt k;
  //sF32 *keyp[4];
  sF32 t,tdif,dif;
  sF32 d0,d1;

  if(!KeyCount)
    return 0;

  if(time<=Keys[0].Time)
    return Keys[0].Value;
  if(time>=Keys[KeyCount-1].Time)
    return Keys[KeyCount-1].Value;

  for(k=0;k<KeyCount-1;k++)
  {
    if(Keys[k+1].Time>time)
    {
      KSplineKey *key = &Keys[k];
      dif = key[1].Value - key->Value;
      tdif = key[1].Time - key->Time;
      t = (time - key->Time) / tdif;

      switch(inter)
      {
      case KSI_CUBIC:
        // this is equivalent to the sHermite call used before...
        // only about 180 bytes shorter ;)
        if(k == 0) // first key
          d0 = dif;
        else
          d0 = tdif * (key[1].Value - key[-1].Value) / (key[1].Time - key[-1].Time);

        if(k == KeyCount - 2) // last key
          d1 = dif;
        else
          d1 = tdif * (key[2].Value - key[0].Value) / (key[2].Time - key[0].Time);

        return (((d0 + d1 - 2*dif) * t + 3*dif - 2*d0 - d1)*t + d0)*t + key->Value;

        /*keyp[0] = (k == 0) ? 0 : &key[-1].Value;
        keyp[1] = &key[0].Value;
        keyp[2] = &key[1].Value;
        keyp[3] = (k == KeyCount - 2) ? 0 : &key[2].Value;

        sHermite(&val,keyp[0],keyp[1],keyp[2],keyp[3],1,t,0,0,0);
        return val;*/

      case KSI_LINEAR:
        return t * dif + key->Value;

      case KSI_STEP:
        return key->Value;
      }
    }
  }
  return 0;
}

void KSpline::Eval(sF32 time,sVector &v)
{
  sInt i;

  for(i=0;i<Count;i++)
    (&v.x)[i] = Channel[i].Eval(time,Interpolation);
}

/****************************************************************************/

void KEvent::Init()
{
  sSetMem(this,0,sizeof(*this));
  Matrix.Init();
  EndInterval = 1.0f;
}

void KEvent::Exit()
{
  if(FirstInstance)
  {
    FirstInstance->DeleteChain();
    FirstInstance = (KInstanceMem*)0xffffffff;
  }
}

void KEvent::Stop()
{
  Start = 0;
  End = 1;
}

/****************************************************************************/
/***                                                                      ***/
/***   Import                                                             ***/
/***                                                                      ***/
/****************************************************************************/

static KClass KClasses[256];

static sBool DistributeAnimR(KOp *start)
{
  sInt i;

  sBool flag = start->GetAnimCode()[0] != KA_END;

  for(i=0;i<start->GetInputCount();i++)
    if(start->GetInput(i))
      flag |= DistributeAnimR(start->GetInput(i));

  start->AnimFlag = flag;
  return flag;
}


/****************************************************************************/
/***                                                                      ***/
/***   2004 export format (.kkrieger / pno0001.exe)                       ***/
/***                                                                      ***/
/****************************************************************************/
//
// Reconstructed from the decompiled KDoc::Init of the original binary
// (FUN_0081859c). The repository version of this file is a later revision
// with an incompatible export format, and a few operators changed their
// parameter layout after the release. KDoc::Init below reads the 2004 format
// and maps those operators onto the newer implementations
// (see Compat2004Convention / Compat2004Defaults).

static sU32 Compat2004Convention(sInt id,sU32 conv)
{
  switch(id)
  {
  case 0x10:  // KKriegerPara: newer Init_KKrieger_Para also takes kenv
    return conv | OPC_KENV;
  case 0x2c:  // Bitmap_Rotate: + newWidth,newHeight (0 = keep size)
    return (conv & ~0xff) | 8;
  case 0x82:  // Mesh_Cylinder: + arc (0 = closed)
    return (conv & ~0xff) | 5;
  case 0x64:  // Effect_PartSystem: + flags
    return (conv & ~0xff) | 12;
  case 0x61:  // Effect_Print: + radius (0 = flat)
    return (conv & ~0xff) | 6;
  case 0x11:  // KKriegerMonster: + walkstyle,weaponkind,spawnswitch, a spline slot.
              // (2004 link 0 = ranged attack event, handled in kkriegergame.cpp)
    return (conv & ~0x00f0f0ff) | 29 | (1<<20);
  case 0xf0:  // IPP_Viewport: 2004 version always rendered the game camera
    return 0x08000218;
  }
  return conv;
}

static void Compat2004Defaults(sInt id,KOp *op)
{
  sU32 *d = op->GetEditPtrU(0);
  sF32 *f = op->GetEditPtrF(0);
  switch(id)
  {
  case 0x61:
    // Effect_Print flags: 2004 had bit0 = center, bits 4-6 = font page and
    // nothing else; the newer code centers via bits 8-9 and uses bits 1/2
    // for vertical offset / screen space
    d[0] = (d[0] & 0x70) | ((d[0] & 1) ? 0x100 : 0);
    break;
  case 0xf0:
    // size is d[0] (from file). flags: game camera (4) + clear color/z (3)
    d[1] = 4|3;
    d[2] = 0;                             // clear color incl. alpha (2004: ClearColor=0)
    // rot[3] pos[3] = 0
    f[9] = 4096.0f; f[10] = 0.125f;       // far/nearclip (overridden by GameCam)
    f[11] = 0; f[12] = 0; f[13] = 1; f[14] = 1;   // center/zoom (GameCam)
    d[15] = 0xff808080;                   // fog: sMaterialEnv defaults
    f[16] = 4096.0f; f[17] = 0.0f;        // fogend, fogstart
    f[18] = 0.0f; f[19] = 1.0f;           // eye distance, focal length
    f[20] = 0; f[21] = 0; f[22] = 1; f[23] = 1;   // full viewport
    break;
  case 0x11:
    // KKriegerMonster: the 2004 version has no weapon kind. A ranged attack
    // starts the op of link 0 as an event (FUN_0081d33e), see
    // KKriegerGame::FireShot2004. Walk style and spawn switch stay 0.
    d[27] = (sU32)-1;
    break;
  }
}

void KDoc::Init(const sU8 *&dataPtr)
{
  const sU8 *data;
  sChar *pack;
  sInt i,j,k,in,nOps,nSplines,typeByte,delta,nClasses,max,n;
  sInt eventCount;
  sU32 conv;
  KClass *cls;
  KEvent *event;
  KSpline *spline;
  KOp *op,*dest;
  static sU32 FileConv[256];      // convention as stored in the file
  static sInt ClassIds[256];

  data = dataPtr;

  // header: tune + sound effects, no flags/bpm/root table in 2004
  BuzzTiming = 0;
  SongSize = *(sU32 *)data; data+=4;
  SongData = (sU8 *)data; data+=sAlign(SongSize,4);
  SampleSize = *(sU32 *)data; data+=4;
  SampleData = (sU8 *)data; data+=sAlign(SampleSize,4);
  SongBPM = 118<<16;              // hardcoded in the 2004 player

  // the newer V2 synth needs the 2004 tunes converted (the editor did this
  // on load): the song itself and the tune inside the sound effect block.
  // The size build embeds data converted offline (linux/kxconv.cpp).
#ifndef KK_SMALL
  {
    sInt len;
    sU8 *conv = V2ConvertSong(SongData,SongSize,len);
    if(conv)
    {
      SongData = conv;
      SongSize = len;
    }
    sU32 *vfx = (sU32 *) SampleData;
    if(SampleSize>=12 && vfx[0]==sMAKE4('V','F','X','0'))
    {
      sInt v2size = vfx[1];
      conv = V2ConvertSong((sU8 *)(vfx+2),v2size,len);
      if(conv)
      {
        // VFX0 | v2m size | v2m | 4 bytes | count | entries...
        sInt tail = SampleSize - (8+v2size);
        sU8 *nb = new sU8[8+len+tail];
        ((sU32 *)nb)[0] = vfx[0];
        ((sU32 *)nb)[1] = len;
        sCopyMem(nb+8,conv,len);
        sCopyMem(nb+8+len,((sU8 *)vfx)+8+v2size,tail);
        delete[] conv;
        SampleData = nb;
        SampleSize = 8+len+tail;
      }
    }
  }
#endif
  SongLength = 0;
  nOps = sReadShort(data);
  nSplines = sReadShort(data);

  Ops.Init(nOps); Ops.Count = nOps;
  Splines.Init(nSplines); Splines.Count = nSplines;

  // class list: u32 convention, u8 id, packing string
  cls = KClasses;
  nClasses = 0;
  while((conv = *((sU32 *) data)))
  {
    data += 4;
    i = *data++;
    FileConv[nClasses] = conv;
    ClassIds[nClasses] = i;
    cls->Convention = Compat2004Convention(i,conv);
    cls->Packing = (sChar *) data;
    while(*data++);

    KHandler *handler = KHandlers;
    while(handler->Id && handler->Id != i)
      handler++;
#ifndef KK_SMALL   // the embedded document only uses known classes
    if(!handler->Id)
      sFatal("Unknown operator class %02x in class list.",i);
#endif

    cls->InitHandler = handler->InitHandler;
    cls->ExecHandler = handler->ExecHandler;
    cls++;
    nClasses++;
  }
  data += 4;

  // op types + connections
  // (size build: tools/kxtranspose.py stores all types (+input counts) first,
  // then all input deltas)
#ifdef KK_SMALL
  sInt *opInputs = new sInt[nOps];
#endif
  for(i=0;i<nOps;i++)
  {
    typeByte = *data++;
    cls = KClasses + (typeByte & 0x7f);
    conv = FileConv[typeByte & 0x7f];

    op = &Ops[i];
    sSetMem(op,0,sizeof(KOp));
    op->Init(cls->Convention);
    op->Command = typeByte & 0x7f;
    op->Convention = cls->Convention;
    op->InitHandler = cls->InitHandler;
    op->ExecHandler = cls->ExecHandler;
    op->WheelSpeed = (sInt) cls->Packing; // abuse, yes.
    op->OpId = i;
    op->AnimFlag = sTRUE;

    if(typeByte & 0x80)
      max = 1;
    else
      max = (conv & OPC_FLEXINPUT) ? *data++ : OPC_GETINPUT(conv);

    if(max>op->InputMax)            // 2004 flex-input ops can exceed the declared count
    {
      op->Input = new KOp*[max];
      op->InputMax = max;
    }

#ifdef KK_SMALL
    opInputs[i] = (typeByte & 0x80) ? -1 : max;
  }
  for(i=0;i<nOps;i++)
  {
    op = &Ops[i];
    max = opInputs[i];
    if(max<0) max = 1, typeByte = 0x80;
    else typeByte = 0;
#endif
    for(in=0;in<max;in++)
    {
      delta = (typeByte & 0x80) ? 0 : sReadShort(data);
      dest = &Ops[i - 1 - delta];
      op->AddInput(dest);
      dest->AddOutput(op);
    }
  }
#ifdef KK_SMALL
  delete[] opInputs;
#endif

  // links (counts as in the file, surplus ones are dropped)
  for(i=0;i<nOps;i++)
  {
    op = &Ops[i];
    n = (FileConv[op->Command]>>12)&15;
    for(in=0;in<n;in++)
    {
      delta = sReadShort(data);
      dest = delta ? &Ops[delta - 1] : 0;
      if(in<op->LinkMax)
      {
        op->SetLink(in,dest);
        if(dest)
          dest->AddOutput(op);
      }
    }
  }

  // op parameters, sorted by class
  // (size build: column-major, see tools/kxtranspose.py: parameter j of all
  // ops of the class, then strings + splines of each op)
  for(i=0;i<nClasses;i++)
  {
    conv = FileConv[i];
#ifdef KK_SMALL
    pack = KClasses[i].Packing;
    for(j=0;pack[j];j++)
    for(in=0;in<nOps;in++)
    {
      op = &Ops[in];
      if(op->Command != i)
        continue;
      {
#else
    for(in=0;in<nOps;in++)
    {
      op = &Ops[in];
      if(op->Command != i)
        continue;

      pack = (sChar *) op->WheelSpeed;
      for(j=0;pack[j];j++)
      {
#endif
        typeByte = pack[j];
        if(typeByte>='A' && typeByte<='Z')
          typeByte += 0x20;

        switch(typeByte)
        {
        case 'g': *op->GetEditPtrF(j) = sReadF16(data);                          break;
        case 'f': *op->GetEditPtrF(j) = sReadF24(data);                          break;
        case 'e': *op->GetEditPtrF(j) = sReadX16(data);                          break;
        case 'i': *op->GetEditPtrS(j) = *((sS32 *) data); data += 4;             break;
        case 's': *op->GetEditPtrS(j) = *((sS16 *) data); data += 2;             break;
        case 'b': *op->GetEditPtrU(j) = *data++;                                 break;
        case 'c': *op->GetEditPtrU(j) = *((sU32 *) data); data += 4;             break;
        case 'm': *op->GetEditPtrU(j) = *((sU32 *) data) & 0xffffff; data += 3;  break;
        }
      }
#ifdef KK_SMALL
    }
    for(in=0;in<nOps;in++)
    {
      op = &Ops[in];
      if(op->Command != i)
        continue;
#endif

      // 2004 used 4 bit string/spline counts
      n = (conv>>16)&15;
      for(j=0;j<n;j++)
      {
        if(j<op->StringMax)
          op->SetString(j,(sChar *)data);
        while(*data)
          data++;
        data++;
      }

      n = (conv>>20)&15;
      for(j=0;j<n;j++)
      {
        k = *((sU16 *) data); data += 2;
        if(j<op->SplineMax)
          op->SetSpline(j,k ? &Splines[k-1] : 0);
      }

      Compat2004Defaults(ClassIds[i],op);
    }
  }

  // anim codes
  for(i=0;i<nOps;i++)
  {
    j = CalcCodeSize((sU8*)data);
    Ops[i].SetAnimCode((sU8*)data,j);
    data += j;
  }

  // events
  Events.Init();
  eventCount = sReadShort(data);
  Events.AtLeast(eventCount);
  while(eventCount--)
  {
    event = Events.Add();
    event->Init();

    event->Op = &Ops[sReadShort(data)];
    event->Start = *((sInt *) data); data += 4;
    event->End = *((sInt *) data); data += 4;
    event->Velocity = sReadF24(data);
    event->Modulation = sReadF24(data);
    event->Select = *data++;
    event->Scale.x = sReadF24(data);
    event->Scale.y = sReadF24(data);
    event->Scale.z = sReadF24(data);
    event->Rotate.x = sReadF24(data);
    event->Rotate.y = sReadF24(data);
    event->Rotate.z = sReadF24(data);
    event->Translate.x = sReadF24(data);
    event->Translate.y = sReadF24(data);
    event->Translate.z = sReadF24(data);
    event->Color = *((sU32 *) data); data += 4;
    sReadShort(data);             // spline index: read but ignored by the 2004 player
    event->Spline = 0;
  }

  // splines
  for(i=0;i<nSplines;i++)
  {
    spline = &Splines[i];
    j = *data++;
    spline->Count = j & 7;
    spline->Interpolation = j >> 3;

    for(j=0;j<spline->Count;j++)
    {
      spline->Channel[j].KeyCount = k = sReadShort(data);
      if(k)
        spline->Channel[j].Keys = new KSplineKey[k];
      else
        spline->Channel[j].Keys = 0;
      for(k=0;k<spline->Channel[j].KeyCount;k++)
      {
        spline->Channel[j].Keys[k].Time = *data++ / 255.0f;
        spline->Channel[j].Keys[k].Value = sReadF16(data);
      }
    }
  }

  // the 2004 player has exactly one root: the last operator
  for(i=0;i<MAX_OP_ROOT;i++)
    RootOps[i] = &Ops[nOps-1];
  {
    const char *dbg = getenv("KK_ROOT");          // debug: render another op as root
    if(dbg && atoi(dbg)>=0 && atoi(dbg)<nOps)
      for(i=0;i<MAX_OP_ROOT;i++)
        RootOps[i] = &Ops[atoi(dbg)];
  }
  CurrentRoot = 0;

  dataPtr = data;
}

/****************************************************************************/

// later (repository) export format, kept for reference
void KDoc::InitRepoFormat(const sU8 *&dataPtr)
{
  const sU8 *data;
  sChar *pack;
  sInt i,j,k,in,nOps,nSplines,typeByte,delta,nClasses,max;
  sInt eventCount;
  sU32 conv;
  KClass *cls;
  KEvent *event;
  KSpline *spline;
  KOp *op,*dest;
  sInt rootindex[MAX_OP_ROOT];
  sInt flags;

  data = dataPtr;

  flags = *(sU32 *)data; data+=4;
  BuzzTiming = (flags&4);
  if(flags&1) data+=32;
  SongSize = *(sU32 *)data; data+=4;
  SongData = (sU8 *)data; data+=sAlign(SongSize,4);
  if(flags&2)
  {
    SampleSize = *(sU32 *)data; data+=4;
    SampleData = (sU8 *)data; data+=sAlign(SampleSize,4);
  }
  SongBPM = *(sU32 *)data; data+=4;
  SongLength = *(sU32 *)data; data+=4;
  nOps = sReadShort(data);
  nSplines = sReadShort(data);
  for(i=0;i<MAX_OP_ROOT;i++)
    rootindex[i] = sReadShort(data);  

  Ops.Init(nOps); Ops.Count = nOps;
  Splines.Init(nSplines); Splines.Count = nSplines;

  cls = KClasses;
  nClasses = 0;

  while((conv = *((sU32 *) data)))
  {
    data += 4;
    cls->Convention = conv;
    i = *((sU16 *)data); data+=2;
    cls->Packing = (sChar *) data;
    while(*data++);

    KHandler *handler = KHandlers;
    while(handler->Id && handler->Id != i)
      handler++;

#ifndef KK_SMALL   // the embedded document only uses known classes
    if(!handler->Id)
      sFatal("Unknown operator class %02x in class list.",i);
#endif

#if sOP_PERFORMANCE
    sChar buffer[64];
    wsprintfA(buffer,"%02x->[%02x]\n",nClasses,i);
    OutputDebugStringA(buffer);
#endif
 
    cls->InitHandler = handler->InitHandler;
    cls->ExecHandler = handler->ExecHandler;
    cls++;
    nClasses++;
  }

  data += 4;

  // read op types+connections, build the tree
  for(i=0;i<nOps;i++)
  {
    typeByte = *data++;
    cls = KClasses + (typeByte & 0x7f);

    op = &Ops[i];
    sSetMem(op,0,sizeof(KOp));
    op->Init(cls->Convention);
    op->Command = typeByte & 0x7f;
    op->Convention = cls->Convention;
    op->InitHandler = cls->InitHandler;
    op->ExecHandler = cls->ExecHandler;
    op->WheelSpeed = (sInt) cls->Packing; // abuse, yes.
    op->OpId = i;
    op->AnimFlag = sTRUE; // first, assume that ops are all animated

    if(typeByte & 0x80)
      max = 1;
    else
      max = (cls->Convention & OPC_FLEXINPUT) ? *data++ : OPC_GETINPUT(cls->Convention);

    for(in=0;in<max;in++)
    {
      delta = (typeByte & 0x80) ? 0 : sReadShort(data);
      dest = &Ops[i - 1 - delta];

      op->AddInput(dest);
      dest->AddOutput(op);
    }
  }

  for(i=0;i<nOps;i++)
  {
    op = &Ops[i];
    for(in=0;in<OPC_GETLINK(op->Convention);in++)
    {
      delta = sReadShort(data);
      dest = delta ? &Ops[delta - 1] : 0;
      op->SetLink(in,dest);
      if(dest)
        dest->AddOutput(op);
    }
  }

  // read ops sorted by type
  for(i=0;i<nClasses;i++)
  {
    for(in=0;in<nOps;in++)
    {
      op = &Ops[in];
      if(op->Command == i)
      {
        // read data
        pack = (sChar *) op->WheelSpeed;

        for(j=0;pack[j];j++)
        {
          typeByte = pack[j];
          if(typeByte>='A' && typeByte<='Z')
            typeByte += 0x20;

          switch(typeByte)
          {
          case 'g': *op->GetEditPtrF(j) = sReadF16(data);                          break;
          case 'f': *op->GetEditPtrF(j) = sReadF24(data);                          break;
          case 'e': *op->GetEditPtrF(j) = sReadX16(data);                          break;
          case 'i': *op->GetEditPtrS(j) = *((sS32 *) data); data += 4;             break;
          case 's': *op->GetEditPtrS(j) = *((sS16 *) data); data += 2;             break;
          case 'b': *op->GetEditPtrU(j) = *data++;                                 break;
          case 'c': *op->GetEditPtrU(j) = *((sU32 *) data); data += 4;             break;
          case 'm': *op->GetEditPtrU(j) = *((sU32 *) data) & 0xffffff; data += 3;  break;
          }
        }

        for(j=0;j<OPC_GETSTRING(op->Convention);j++)
        {
          op->SetString(j,(sChar *)data);
          while(*data)
            data++;
          data++;
        }

        for(j=0;j<OPC_GETSPLINE(op->Convention);j++)
        {
          k = *((sU16 *) data); data += 2;
          op->SetSpline(j,k ? &Splines[k-1] : 0);
        }

        if(op->Convention&OPC_BLOB)
        {
          k = *((sInt *) data); data += 4;
          op->SetBlob(0,k);
        }
      }
    }
  }

  // read anim codes
  for(i=0;i<nOps;i++)
  {
    j = CalcCodeSize((sU8*)data);
    Ops[i].SetAnimCode((sU8*)data,j);
    data += j;
  }

  // read events
  Events.Init();
  eventCount = sReadShort(data);
  Events.AtLeast(eventCount);
  while(eventCount--)
  {
    event = Events.Add();
    event->Init();
    
    // read op
    event->Op = &Ops[sReadShort(data)];

    // read data
    event->Start = *((sInt *) data); data += 4;
    event->End = *((sInt *) data); data += 4;
    event->Velocity = sReadF24(data);
    event->Modulation = sReadF24(data);
    event->Select = *data++;

    event->Scale.x = sReadF24(data);
    event->Scale.y = sReadF24(data);
    event->Scale.z = sReadF24(data);
    event->Rotate.x = sReadF24(data);
    event->Rotate.y = sReadF24(data);
    event->Rotate.z = sReadF24(data);
    event->Translate.x = sReadF24(data);
    event->Translate.y = sReadF24(data);
    event->Translate.z = sReadF24(data);
    event->Color = *((sU32 *) data); data += 4;
    i = sReadShort(data);
    if(i)
      event->Spline = &Splines[i-1];
    else
      event->Spline = 0;
//    event->ReturnMatrix.Init();
    event->StartInterval = sReadF16(data);
    event->EndInterval = sReadF16(data);
  }

  // read splines
  for(i=0;i<nSplines;i++)
  {
    spline = &Splines[i];
    j = *data++;
    spline->Count = j & 7;
    spline->Interpolation = j >> 3;

    for(j=0;j<spline->Count;j++)
    {
      spline->Channel[j].KeyCount = k = sReadShort(data);
      if(k)
        spline->Channel[j].Keys = new KSplineKey[k];
      else
        spline->Channel[j].Keys = 0;
      for(k=0;k<spline->Channel[j].KeyCount;k++)
      {
        spline->Channel[j].Keys[k].Time = *data++ / 255.0f;
        spline->Channel[j].Keys[k].Value = sReadF16(data);
      }
    }
  }

  // read blobs
  for(i=0;i<nOps;i++)
  {
    j = Ops[i].GetBlobSize();
    if(j)
    {
      Ops[i].SetBlobData(data);
      data += j;
    }
  }

  // distribute anim flag
  DistributeAnimR(&Ops[Ops.Count-1]);

  for(i=0;i<MAX_OP_ROOT;i++)
  {
    if(rootindex[i]<nOps)
      RootOps[i] = &Ops[rootindex[i]];
    else
      RootOps[i] = 0;
  }
  CurrentRoot = 0;

  dataPtr = data;
}


void KDoc::Exit()
{
  sInt i,j;
  KOp *op;

  for(i=0;i<Ops.Count;i++)
  {
    op = &Ops[i];
    if(op->Cache && !op->CacheFreed)
      op->Cache->Release();

    op->Exit();
//    if(op->Update)
//      op->Update->Release();
  }

  for(i=0;i<Splines.Count;i++)
  {
    for(j=0;j<Splines[i].Count;j++)
      delete[] Splines[i].Channel[j].Keys;
  }

  Ops.Exit();
  Events.Exit();
  Splines.Exit();
}

void KDoc::Precalc(KEnvironment *kenv)
{
//  KOp *op;

#if sOP_PERFORMANCE
  for(sInt i=0;i<256;i++)
    OpPerf[i] = 0;
#endif

/*
  for(i=0;i<Ops.Count;i++)
  {
    op = &Ops[i];

#if sOP_PERFORMANCE
    sU32 stime = sSystem->GetTime();
#endif
    op->Calc(kenv,KCF_ROOT|KCF_NEED);
#if sOP_PERFORMANCE
    perf[op->Command] += sSystem->GetTime() - stime;
#endif

    for(sInt j=0;j<op->GetInputCount();j++)
      op->GetInput(j)->CalcUsed();

    for(sInt j=0;j<op->GetLinkMax();j++)
      op->GetLink(j)->CalcUsed();

    sSystem->Progress(i,Ops.Count);
  }
*/

  PrecalcCount = 0;
  PrecalcMax = CountOps(RootOps[CurrentRoot]);
  RootOps[CurrentRoot]->Calc(kenv,KCF_ROOT|KCF_NEED|KCF_PRECALC);

#if sOP_PERFORMANCE
  sInt perft = 0;

  for(sInt i=0;i<256;i++)
  {
    if(OpPerf[i])
    {
      sChar buffer[64];
      wsprintfA(buffer,"%02x: %d ms\n",i,OpPerf[i]);
      OutputDebugStringA(buffer);
      perft += OpPerf[i];
    }
  }
  sChar buffer[64];
  wsprintfA(buffer,"%d ms total (ops)\n",perft);
  OutputDebugStringA(buffer);
#endif
}

void KDoc::AddEvents(KEnvironment *kenv)
{
  sInt i;

  for(i=0;i<Events.Count;i++)
    kenv->AddStaticEvent(&Events[i]);
}

static sInt CountOpsR(KOp *op)
{
  sInt count = 1;
  op->Tag = 1;

  for(sInt i=0;i<op->GetInputCount();i++)
  {
    KOp *in = op->GetInput(i);
    if(in && !in->Tag)
      count += CountOpsR(in);
  }

  for(sInt i=0;i<op->GetLinkMax();i++)
  {
    KOp *link = op->GetLink(i);
    if(link && !link->Tag)
      count += CountOpsR(link);
  }
  
  return count;
}

sInt KDoc::CountOps(KOp *start)
{
  for(sInt i=0;i<Ops.Count;i++)
    Ops[i].Tag = Ops[i].Cache && !Ops[i].Changed;

  return CountOpsR(start);
}

/****************************************************************************/
/***                                                                      ***/
/***   Operator. Mostly used by Tool                                      ***/
/***                                                                      ***/
/****************************************************************************/

void KOp::Init(sU32 convention)
{
  sInt size;
  sU32 *mem;
  sInt i;

  DataMax   = OPC_GETDATA(convention);
  InputMax  = OPC_GETINPUT(convention);
  LinkMax   = OPC_GETLINK(convention);
  StringMax = OPC_GETSTRING(convention);
  SplineMax = OPC_GETSPLINE(convention);
  AnimMax = 1;

  if(convention & OPC_VARIABLEINPUT)
    InputMax = 255;
  OutputMax = 0;

  size = DataMax*2+InputMax+LinkMax+OutputMax+StringMax*2+SplineMax+AnimMax;
  mem = Memory = new sU32[size];
  sSetMem(mem,0,size*4);

  Input = (KOp**) mem; mem+=InputMax;
  Link = (KOp**) mem; mem+=LinkMax;
  Output = (KOp**) mem; mem+=OutputMax;
  String = (sChar**)mem; mem+=StringMax;
  Spline = (KSpline**)mem; mem+=SplineMax;
  DataEdit = mem; mem+=DataMax;
  DataAnim = mem; mem+=DataMax;
  for(i=0;i<StringMax;i++)
  {
    String[i] = (sChar *)mem;
    String[i][0] = 0;
    mem++;
  }
  AnimCode = (sU8 *)mem; mem+=AnimMax; *AnimCode = KA_END;
  InputCount = 0;
  OutputCount = 0;
  BlobData = 0;
  BlobSize = 0;
}

void KOp::Exit()
{

  if(Memory)
  {
    delete[] Memory;
    Memory = 0;
  }
}

/****************************************************************************/


void KOp::SetBlob(const sU8 *data,sInt size)
{
  BlobData = data;
  BlobSize = size;
}


/****************************************************************************/
/***                                                                      ***/
/***  Memory Management (Tool only)                                       ***/
/***                                                                      ***/
/****************************************************************************/


/****************************************************************************/
/***                                                                      ***/
/***   Classless Operators                                                ***/
/***                                                                      ***/
/****************************************************************************/

#pragma lekktor(off)

KObject * __stdcall Init_Misc_Load(KObject *o)
{
  return o;
}

KObject * __stdcall Init_Misc_Nop(KOp *op)
{
  return op->GetInput(0)->Cache;
}

KObject * __stdcall Init_Misc_If(KOp *op)
{
  if(op->GetInput(1)->Cache)
    op->GetInput(1)->Cache->Release();
  return op->GetInput(0)->Cache;
}

KObject * __stdcall Init_Misc_Event(KObject *o,sF32 duration)
{
  return o;
}

KObject * __stdcall Init_Misc_Trigger(KObject *o,KOp *event,
  sF32 trigger,sF32 tresh,sF32 delay,sF32 duration,sInt flags,
  sF32 mod,sF32 vel,sInt sel,sF323 s,sF323 r,sF323 t,sU32 col,KSpline *spline)
{
  return o;
}

// Linux port: operator class 0xe0 of the 2004 release (not in the repository).
// Reconstructed from 0x815166: releases its (up to 15) inputs and returns an
// empty object of class 7; exec is Exec_Misc_Nop, i.e. it just executes its
// inputs. It sits between the scene graph and IPP_Viewport.
KObject * __stdcall Init_Misc_Root2004(KObject *i0,KObject *i1,KObject *i2,KObject *i3,KObject *i4,
  KObject *i5,KObject *i6,KObject *i7,KObject *i8,KObject *i9,KObject *i10,KObject *i11,
  KObject *i12,KObject *i13,KObject *i14)
{
  KObject *in[15] = { i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14 };
  KObject *o;
  for(sInt i=0;i<15;i++)
    if(in[i]) in[i]->Release();
  o = new KObject;
  o->ClassId = 7;
  return o;
}

void __stdcall Exec_Misc_Nop(KOp *op,KEnvironment *kenv)
{
  op->ExecInputs(kenv);
}

void __stdcall Exec_Misc_Load(KOp *op,KEnvironment *kenv)
{
  sVERIFY(op->GetLink(0));

  op->GetLink(0)->Exec(kenv);
}

/****************************************************************************/

void __stdcall Exec_Misc_Time(KOp *op,KEnvironment *kenv)
{
  sVERIFY(op->GetInput(0));
  if(op->FirstEvent)
    op->GetInput(0)->ExecEvent(kenv,op->FirstEvent,0);
}

void __stdcall Exec_Misc_Event(KOp *op,KEnvironment *kenv,sF32 duration)
{
  KEvent *event;
  
  sVERIFY(op->GetInput(0));
  event = op->FirstEvent;
  while(event)
  {
    if(event->Start == event->End)
    {
      event->Start = kenv->BeatTime;
      event->End = event->Start + sFtol(duration * 0x10000);
    }
    op->GetInput(0)->ExecEvent(kenv,event,0);
    event = event->NextOp;
  }
}

/****************************************************************************/

struct TriggerMem : KInstanceMem
{
  sInt Active;
  sInt Time;
};

void __stdcall Exec_Misc_Trigger(KOp *op,KEnvironment *kenv,
  sF32 trigger,sF32 tresh,sF32 delay,sF32 duration,sInt flags,
  sF32 vel,sF32 mod,sInt sel,sF323 s,sF323 r,sF323 t,sU32 col,KSpline *spline)
{
  KEvent *ev;
  KOp *eop;
  TriggerMem *mem;
  sBool doit;

  eop = op->GetLink(0);

  if(eop && eop->ExecHandler == Exec_Misc_Event)
  {
    mem = kenv->GetInst<TriggerMem>(op);
    if(mem->Reset)
    {
      mem->Active = 1;
      mem->Time = kenv->BeatTime;
    }

//    sDPrintF("%f %f %08x %08x (%d)\n",trigger,tresh,kenv->BeatTime,mem->Time,flags);

    doit = (trigger>tresh);
    if(flags&1)
      doit = !doit;
    if(!doit)
      mem->Time = kenv->BeatTime;
    if((flags&2) && mem->Active && kenv->BeatTime>=mem->Time)
      mem->Active = 0;

    if(doit && !mem->Active)
    {
      ev = new KEvent;
      ev->Init();

      ev->Op = eop;
      ev->Start = mem->Time;
      ev->End = ev->Start+duration*0x10000;
      ev->Dynamic = 1;

      ev->Velocity = vel;
      ev->Modulation = mod;
      ev->Select = sel;
      ev->Scale.Init(s.x,s.y,s.z,0);
      ev->Rotate.Init(r.x,r.y,r.z,0);
      ev->Translate.Init(t.x,t.y,t.z,0);
      if(flags&4)
      {
        ev->Translate = kenv->ExecStack.Top().l;
        ev->Translate.w = 0;
      }
      kenv->AddDynamicEvent(ev);
//      sVERIFY(ev->Active == 1);

//      sDPrintF("-> %08x %08x\n",ev->Start,ev->End);

      mem->Active = 1;
      mem->Time += delay*0x10000;
    }
    if(!doit)
      mem->Active = 0;
  }

  op->ExecInput(kenv,0);
}

/****************************************************************************/

struct DelayMem : KInstanceMem
{
  sInt Phase;     // 0 = off, 1=rise, 2=hold, 3=decline
  sF32 Time;
};

void __stdcall Exec_Misc_Delay(KOp *op,KEnvironment *kenv,sInt flags,sInt sw,sF32 tresh,sF32 hyst,sF32 time0,sF32 time1,sF32 time2)
{
  sF32 val;
  sF32 delta;
  DelayMem *mem;

  mem = kenv->GetInst<DelayMem>(op);
  if(mem->Reset)
  {
    mem->Phase = 0;
    mem->Time = 0;
  }

  if(flags&0xc0)
  {
    val = kenv->Var[(flags&0xc0)>>6].x;
  }
  else
  {
    val = 0;
    tresh = 0.5f;
    hyst = 0.0f;
    if(kenv->Game->Switches) 
      val = kenv->Game->Switches[sw];
  }

  if(mem->Phase==2 && val<tresh-hyst)
  {
    mem->Phase = 3;
    mem->Time = 0;
  }
  if(mem->Phase==0 && val>tresh+hyst)
  {
    mem->Phase = 1;
    mem->Time = 0;
  }

  delta = (kenv->CurrentTime-kenv->LastTime)/1000.0f;
  if(delta<0) delta =0;
  switch(mem->Phase)
  {
  case 1:
    if(time0>0)
      mem->Time += delta/time0;
    else
      mem->Time = 1.0f;
    if(mem->Time>=1.0f)
    {
      mem->Phase = 2;
      mem->Time = 0;
    }
    break;
  case 2:
    if(time1>0)
    {
      mem->Time += delta/time1;
      if(mem->Time>1.0f)
        mem->Time = mem->Time -1;
      if(mem->Time>1.0f)
        mem->Time = 0;
    }
    break;
  case 3:
    if(time2>0)
      mem->Time += delta/time2;
    else
      mem->Time = 1.0f;
    if(mem->Time>=1.0f)
    {
      mem->Phase = 0;
      mem->Time = 0;
    }
    break;
  }

  val = 0;
  if(mem->Phase==1) val = mem->Time;
  if(mem->Phase==2) val = 1;
  switch(flags&0x0f)
  {
  case 0:
    if(mem->Phase==3) val = 1-mem->Time;
    break;
  case 1:
    if(mem->Phase==3) val = 1+mem->Time;
    val = val*0.5f;
    break;
  case 2:
    if(mem->Phase==2) val = 1+mem->Time*2;
    if(mem->Phase==3) val = 3+mem->Time;
    val = val*0.25f;
    break;
  }

  kenv->Var[(flags&0x30)>>4].Init(val,val,val,val);

  op->ExecInput(kenv,0);
}

/****************************************************************************/

void __stdcall Exec_Misc_If(KOp *op,KEnvironment *kenv,sInt sw,sInt val)
{
  KOp *child;

  sVERIFY(op->GetInputCount()>=1);
  if(kenv->Game->Switches[sw]==val)
  {
    child = op->GetInput(0);
  }
  else
  {
    if(op->GetInputCount()<2)
      return;
    child = op->GetInput(1);
  }
  child->ExecWithNewMem(kenv,&child->SceneMemLink);
}

/****************************************************************************/

void __stdcall Exec_Misc_SetIf(KOp *op,KEnvironment *kenv,sInt sw,sInt val,sInt flags,sInt osw)
{
  sVector v;
  sInt var;
  sInt compare;

  var = flags&15;

  compare = kenv->Game->Switches[sw]-val;
  if(flags&0x20)
    compare = compare<0;
  compare = compare?0:1;
  if(flags&0x10)
    compare = 1-compare;

  switch(var)
  {
  case 0:
  case 1:
  case 2:
  case 3:
    v = kenv->Var[var];
    kenv->Var[var].Init(compare,compare,compare,compare);
    op->ExecInputs(kenv);
    kenv->Var[var] = v;
    break;
  case 4:
    kenv->Game->Switches[osw] = compare;
    op->ExecInputs(kenv);
    break;
  case 5:
  case 6:
    if(compare)
      kenv->Game->Switches[osw] = 6-var;
    op->ExecInputs(kenv);
    break;
  }
}

/****************************************************************************/

void __stdcall Exec_Misc_State(KOp *op,KEnvironment *kenv,sInt sw,sInt val,sInt cond,sInt condsw,sInt condval)
{
  sInt ok;

  ok = 0;
  switch(cond)
  {
  case 4:
    if(kenv->Game->LastKey==sKEY_UP)
      ok = 1;
    break;
  case 5:
    if(kenv->Game->LastKey==sKEY_DOWN)
      ok = 1;
    break;
  case 6:
    if(kenv->Game->LastKey==sKEY_LEFT)
      ok = 1;
    break;
  case 7:
    if(kenv->Game->LastKey==sKEY_RIGHT)
      ok = 1;
    break;
  case 0:
    ok = 1;
    break;
  case 1:
    if(kenv->Game->LastKey==' ')
      ok = 1;
    break;
  case 2:
    if(kenv->Game->LastKey==sKEY_ENTER || kenv->Game->LastKey==sKEY_MOUSEL)
      ok = 1;
    break;
  case 3:
    if(kenv->Game->LastKey==sKEY_BACKSPACE || kenv->Game->LastKey==sKEY_ESCAPE)
      ok = 1;
    break;
  }

  if(ok && kenv->Game->Switches[condsw]==condval && sw!=0)
  {
    kenv->Game->Switches[sw] = val;
    if(cond!=0)
      kenv->Game->LastKey = 0;
  }

  op->ExecInputs(kenv);
}

void __stdcall Exec_Misc_Menu(KOp *op,KEnvironment *kenv,sInt sw,sInt max,sInt flags)
{
  sInt i;

  i = 0;
  if( (flags&1) && kenv->Game->LastKey==sKEY_UP   ) i = -1;
  if( (flags&1) && kenv->Game->LastKey==sKEY_DOWN ) i = 1;
  if(!(flags&1) && kenv->Game->LastKey==sKEY_LEFT ) i = -1;
  if(!(flags&1) && kenv->Game->LastKey==sKEY_RIGHT) i = 1;

  if(i!=0)
  {
    kenv->Game->Switches[sw] = sRange<sInt>(kenv->Game->Switches[sw]+i,max-1,0);
    kenv->Game->LastKey = 0;
  }

  op->ExecInputs(kenv);
}

struct PlaySampleMem : public KInstanceMem
{
  sInt On;
  sInt Retrigger;
  sInt OldValue;
  sVector OldPos;
  sInt Buffer3D;
};


void __stdcall Exec_Misc_PlaySample(KOp *op,KEnvironment *kenv,sInt sw,sInt val,sF32 tresh,sInt sample,sF32 volume,sF32 retrigger,sF32 halfrange)
{
  PlaySampleMem *mem;
  sInt ok,buf;
  sVector v;

  mem = kenv->GetInst<PlaySampleMem>(op);
  if(mem->Reset)
  {
    mem->Retrigger = -1;
    mem->OldValue = kenv->Game->Switches[sw];
    mem->OldPos.Init4(0,0,0,0);
    mem->Buffer3D = -1;
  }

  ok = (kenv->Game->Switches[sw]==val && tresh>0);
  if(val==-1)
    ok = kenv->Game->Switches[sw]!=mem->OldValue;
  mem->OldValue = kenv->Game->Switches[sw];
  if(mem->Retrigger>=0)
  {
    mem->Retrigger -= kenv->TimeDelta;
    if(mem->Retrigger<0)
      mem->On = 0;
  }
  if(ok && !mem->On)
  {
    {
      buf = sSystem->SamplePlay(sample,sFPow(10.0f,-volume/20.0f),0);
      if(retrigger>0)
        mem->Retrigger = sFtol(retrigger*1000);

      if(halfrange)
        mem->Buffer3D = buf;
    }
  }
  
  // update 3d parameters
  if(mem->Buffer3D != -1)
  {
    const sMatrix &matrix = kenv->ExecStack.Top();

    v.Sub3(matrix.l,mem->OldPos);
    v.Scale3(1000.0f / (kenv->TimeDelta + 1.0f));
    sSystem->Sample3DParam(sample,mem->Buffer3D,matrix.l,v,1.0f,halfrange*8.0f);
    mem->OldPos = matrix.l;
  }

  mem->On = ok;
  op->ExecInputs(kenv);
}


#pragma lekktor(on)

/****************************************************************************/


GenDemo::GenDemo()
{
  ClassId = KC_DEMO;
}

GenDemo::~GenDemo()
{
}

KObject * __stdcall Init_Misc_Demo(KOp *op)
{
  sInt i;
  KObject *obj;

  for(i=0;i<op->GetInputCount();i++)
  {
    obj = op->GetInput(i)->Cache;
    if(obj->ClassId!=KC_DEMO && obj->ClassId!=KC_IPP)
      return 0;
  }

  for(i=0;i<op->GetInputCount();i++)
  {
    obj = op->GetInput(i)->Cache;
    obj->Release();
  }
  return new GenDemo;
}

void __stdcall Exec_Misc_Demo(KOp *op,KEnvironment *kenv)
{
  sInt i;
  KOp *in;

  for(i=0;i<op->GetInputCount();i++)
  {
    in = op->GetInput(i);
    if(in->Cache->ClassId==KC_DEMO)
    {
      op->ExecInput(kenv,i);
    }
    else if(in->Cache->ClassId==KC_IPP)
    {
      GenOverlayManager->Reset(kenv);

      op->ExecInput(kenv,i);
      if(GenOverlayManager->LastOutput!=0)
      {
        GenOverlayManager->Copy(GenOverlayManager->LastOutput,
          GenOverlayManager->Alloc(0,GENOVER_RTSIZES,1),0,0xffffffff,1);    // owner is 0 because noone should find this!
      }
    }
  }
}

/****************************************************************************/

KObject * __stdcall Init_Misc_MasterCam(sF323 rot,sF323 pos,sF32 farclip,sF32 nearclip,sF32 centerx,sF32 centery,sF32 zoomx,sF32 zoomy)
{
  return new GenDemo;
}

void __stdcall Exec_Misc_MasterCam(KOp *op,KEnvironment *kenv,sF323 rot,sF323 pos,sF32 farclip,sF32 nearclip,sF32 centerx,sF32 centery,sF32 zoomx,sF32 zoomy)
{
  sMaterialEnv env;

  // CurrentCam is the way to tell camera details
  env.Init();

  {
    env.FarClip = farclip;
    env.NearClip = nearclip;
    env.CenterX = centerx;
    env.CenterY = centery;
    env.ZoomX = zoomx;
    env.ZoomY = zoomy;
    env.CameraSpace.InitEulerPI2(&rot.x);
    env.CameraSpace.l.Init3(pos.x,pos.y,pos.z);

    kenv->GameCam = env;
  }
}

/****************************************************************************/
/****************************************************************************/


