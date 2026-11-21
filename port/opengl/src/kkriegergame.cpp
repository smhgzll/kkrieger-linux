#include <stdio.h>
#include <stdlib.h>
// linux port: minimal thread interface implemented in _start_linux.cpp
void *kkStartThread(int (*fn)(void *),void *user);
void kkWaitThread(void *thread);
// This file is distributed under a BSD license. See LICENSE.txt for details.

#include "kkriegergame.hpp"
#include "genmesh.hpp"
#include "engine.hpp"
#include "genoverlay.hpp"
#include "genscene.hpp"


//#define OVERLAP   (0.005f)
//#define EPSILON   (0.0001f)
#define EPSILON   (4.010e-3f) // determined from level size
#define OVERLAP   (EPSILON*2)
#define MOVE_EPSILON  (1e-6f)
#define DOUBLECHECK 0

#define GAMEPERF(x) ;

#pragma lekktor(off)

//static sInt SomethingBadHasHappened;    // collision panic

/****************************************************************************/

KKriegerMesh::KKriegerMesh(GenMesh *mesh)
{
  CellCount = mesh->Coll.Count;
  Cell = new KKriegerMeshCell[CellCount];

  for(sInt i=0;i<CellCount;i++)
  {
    GenMeshColl *inCell = &mesh->Coll[i];
    KKriegerMeshCell *outCell = &Cell[i];

    for(sInt j=0;j<8;j++)
      outCell->Vert[j] = mesh->VertPos(inCell->Vert[j]);

    outCell->Mode = inCell->Mode;
    outCell->Logic = inCell->Logic;
  }
}

KKriegerMesh::~KKriegerMesh()
{
  delete[] Cell;
}

void  KKriegerMesh::Copy(KObject *)
{
  // KKriegerMeshes should *never* get copied around
  sVERIFYFALSE;
}

/****************************************************************************/

#define LOGGING 0

/****************************************************************************/
/****************************************************************************/

/****************************************************************************/

void KKriegerPlayer::Init()
{
  Life = 100;
  Armor = 0;
  Alpha = 0;
  Beta = 0;
  Ammo[0] = 100;
  Ammo[1] = 50;
  Ammo[2] = 0;
  Ammo[3] = 0;
  Weapon[0] = 1;
  Weapon[1] = 1;
  Weapon[2] = 1;
  Weapon[3] = 0;
  Weapon[4] = 0;
  Weapon[5] = 0;
  Weapon[6] = 0;
  Weapon[7] = 0;
  LifeMax = 100;
  ArmorMax = 100;
  AlphaMax = 100;
  BetaMax = 8;
  AmmoMax[0] = 500;
  AmmoMax[1] = 200;
  AmmoMax[2] = 100;
  AmmoMax[3] = 1000;
  WeaponMax[0] = 1;
  WeaponMax[1] = 1;
  WeaponMax[2] = 1;
  WeaponMax[3] = 1;
  WeaponMax[4] = 1;
  WeaponMax[5] = 1;
  WeaponMax[6] = 1;
  WeaponMax[7] = 1;

  CurrentWeapon = 1;
  NextWeapon = 0;
  FireKey = 0;
  UseKey = 0;
  CoolTimer = 0;
}

void KKriegerPlayer::Hit(sInt hits)
{
  if(hits>Armor)
    Life -= (hits-Armor)+(Armor/4);
  else
    Life -= hits/4;
  if(Life<0)
    Life = 0;
  if(hits>4)
    Sound(10);
}

void KKriegerPlayer::Sound(sInt handle,sF32 volume)
{
  sSystem->SamplePlay(handle,volume);       // 2004: plain sample, no 3d
}
/****************************************************************************/
/****************************************************************************/

void KKriegerGame::Init()
{
  sInputData id;


  CellAdd.Init(128);
  CellSub.Init(4096);
  CellZone.Init(1024);

  Monsters.Init(64);

  PlayerPos.Init();
  PlayerDir = 0;
  PlayerLook = 0;
  PlayerMat.Init();
  PlayerCell = 0;
  Player.Init();

  LastTime = sSystem->GetTime();
  sSystem->GetInput(0,id);
  LastMouseX = id.Analog[0];
  LastMouseY = id.Analog[1];
  LastCamY = 0;
  CamPos.Init();
  Environment = 0;
  TickCount = 0;
  PlayerAdds = 0;
  

  sSetMem(Respawn,0,sizeof(Respawn));


  WeaponEvent.Init();
  Flush();
  Panic();

  sSetMem(Switches,0,KKRIEGER_SWITCHES);
  Switches[KGS_ONE] = 1;
  Switches[KGS_GLARE] = 2;
  Switches[KGS_RESOLUTION] = 1;
  Switches[KGS_TEXTURES] = 1;
  Switches[KGS_SHADOWS] = 1;
  Switches[KGS_MOUSESPEED] = 5;
  Switches[KGS_BRIGHTNESS] = 5;
  Switches[KGS_SPECULAR] = 1;
  WasInOptions = sFALSE;

  OnOptionsChanged();
}

void KKriegerGame::Exit()
{

  Flush();
  CellAdd.Exit();
  CellSub.Exit();
  CellZone.Exit();
  Monsters.Exit();
  WeaponEvent.Exit();
}

void KKriegerGame::Flush()
{
  sInt i,j;
  for(i=0;i<CellAdd.Count;i++)
  {
    CellAdd[i]->Adds.Exit(); 
    CellAdd[i]->Subs.Exit();   
    CellAdd[i]->Zones.Exit();
    delete CellAdd[i];
  }
  for(i=0;i<CellSub.Count;i++)
    delete CellSub[i];
  for(i=0;i<CellZone.Count;i++)
  {
    for(j=0;j<2;j++)
    {
      if(CellZone[i]->Event[j])
      {
        CellZone[i]->Event[j]->Exit();
        delete CellZone[i]->Event[j];
        CellZone[i]->Event[j] = 0;
      }
    }
    delete CellZone[i];
  }

  for(i=0;i<8;i++)
  {
    WeaponShot[i] = 0;
    WeaponOptics[i] = 0;
    WeaponExplode[0][i] = 0;
    WeaponExplode[1][i] = 0;
  }
  CellAdd.Count = 0;
  CellSub.Count = 0;
  CellZone.Count = 0;

  PartUsed = 0;
  ConsUsed = 0;
  WeaponTimer = 0;
  StepTimer = 0;
  StepFoot = 0;
  OffGroundTime = 0;
  Player.CurrentWeapon = 1;
  Player.NextWeapon = 0;
}

#pragma lekktor(on)

void KKriegerGame::Panic()
{
  sVector speed,scale;
  sInputData id;

  SpeedForw = 0;
  AccelForw = 0;
  SpeedSide = 0;
  AccelSide = 0;
  SpeedUp = 0;
  OnGround = 0;
  ResetByOp = 1;
  JumpTimer = 0;
  CollisionForMonsterMode = 0;

  Gravity = 0.0002f;
  GravityPlayer = 0.01f;
  DampPlayerAir = 0.05f;
  DampPlayerCam = 0.05f;
  DampPlayerGround = 0.05f;
  DampPlayerHeight = 0.05f;
  StairHeight = 0.55f;
  EyeHeight = 1.60f;
  MouseTurnSpeed = 0.01f;
  MouseLookSpeed = 0.01f;
  AccelSideFactor = 0.005f;
  AccelForwFactor = 0.005f;
  AccelBackFactor = 0.005f;
  JumpForce = 0.35f;
  FlyMode =0;
  SplashEnable = 0;

  CamOffset = EyeHeight-StairHeight;
  CamZoomPos = 0;
     
  scale.Init(0.5f,1.0f/4,0.5f);
  speed.Init();

//  PlayerPart = MakeBody((const sS8 *)playerv,7-2,(const sU8 *)playere,18-8,scale,0x09,PlayerPos,speed);
//  PlayerPart->Kind = 0x08;

  sSystem->GetInput(0,id);
  LastMouseX = id.Analog[0];
  LastMouseY = id.Analog[1];

  // gameplay init

#if LOGGING
  sDPrintF("KKriegerGame::Panic() called\n");
#endif
}

/****************************************************************************/
/****************************************************************************/

void KKriegerGame::SetPainter(KOp *op,KEnvironment *kenv)
{
  while(op && op->Cache)
  {
    // linux port: like the 2004 player (FUN_0081da41) also walk through ops
    // whose exec is Exec_Misc_Nop (e.g. op 0xe0 between viewport and scene)
    if(op->Cache->ClassId == KC_IPP || op->Cache->ClassId == KC_DEMO
      || op->ExecHandler == (void *)Exec_Misc_Nop)
      op = op->GetInput(0);
    else if(op->CheckOutput(KC_SCENE))
    {
      SetScene((GenScene *)op->Cache);
      break;
    }
    else
      break;
  }
}

void KKriegerGame::SetScene(GenScene *scene)
{
  sMatrix mat;

  Flush();
  mat.Init();

  CellList.Init();
  
  sInt t0 = sSystem->GetTime();
  SetSceneR(scene,mat,scene,0);
  sInt t1 = sSystem->GetTime();
  SetSceneR(scene,mat,scene,1);
  sInt t2 = sSystem->GetTime();

  CellConnect();
  if(getenv("KK_GAMELOG"))
    fprintf(stderr,"SetScene: pass0 %d ms, pass1 %d ms, CellConnect %d ms, add=%d sub=%d zone=%d\n",
      t1-t0,t2-t1,sSystem->GetTime()-t2,CellAdd.Count,CellSub.Count,CellZone.Count);


  CellList.Exit();
}

void KKriegerGame::SetMesh(GenMesh *mesh)
{
  sMatrix mat;
  KKriegerMesh *tempMesh;

  Flush();
  mat.Init();

  CellList.Init();

  tempMesh = new KKriegerMesh(mesh);
  AddMesh(tempMesh,mat,0);
  tempMesh->Release();

  CellConnect();
  CellList.Exit();
}

// 2004: 0x81cb71. The player is a body of 5 particles (KKriegerBody).

void KKriegerGame::SetPlayer(sVector pos,sF32 dir,sF32 look)
{
  sInputData id;
  KKriegerCellAdd *cell;

  sSystem->GetInput(0,id);
  PlayerPos = pos;
  LastMouseX = id.Analog[0];
  LastMouseY = id.Analog[1];
  PlayerDir = dir;
  PlayerLook = look;
  cell = FindCell(pos);
  if(getenv("KK_GAMELOG"))
    fprintf(stderr,"SetPlayer: p=(%g %g %g) cell=%p cells=%d\n",pos.x,pos.y,pos.z,cell,CellAdd.Count);
  CamPos = pos;
  PlayerCell = cell;                        // may be 0: OnTick then does nothing
  LastCamY = pos.y;
  Player.Body.Init(PlayerPos,cell,KPK_PLAYER);
}
/****************************************************************************/

void KKriegerGame::SetSceneR(GenScene *scene,const sMatrix &base,GenScene *usescene,sInt phase)
{
  sMatrix mat,srt,tmat;
  sInt i,j,max;

  srt.InitSRT(scene->SRT);

  max = scene->Count;
  if(max==0)
    max = 1;

  if(scene->IsSector)
    usescene = scene;

  mat = base;

  for(i=0;i<max;i++)
  {
    if(scene->Count==0 || i!=0)
    {
      tmat.MulA(srt,mat);
      mat = tmat;
    }

    for(j=0;j<scene->Childs.Count;j++)
      SetSceneR(scene->Childs.Get(j),mat,usescene,phase);

    if(scene->CollMesh)
    {
      if(phase == 0)
        AddMesh(scene->CollMesh,mat,usescene);
      else
      {
//        scene->CollMesh->Release();
//        scene->CollMesh = 0;
      }
    }
  }  
}


void KKriegerGame::AddMesh(KKriegerMesh *mesh,const sMatrix &mat,GenScene *usescene)
{
  sInt i,j,k;
  KKriegerCell *kc;
  KKriegerCellAdd *kca;
  KKriegerMeshCell *mc;
  sVector va[8];
  sInt mode;

  for(j=0;j<mesh->CellCount;j++)
  {
    mc = &mesh->Cell[j];
    mode = mc->Mode & 3;

    for(k=0;k<8;k++)
      va[k].Rotate34(mat,mc->Vert[k]);

    switch(mode)
    {
    default:
    case KCM_ADD:
      kca = new KKriegerCellAdd;
      *CellAdd.Add() = kca;
      kca->Adds.Init();
      kca->Subs.Init();
      kca->Zones.Init();
      kc = kca;
      break;
    case KCM_SUB:
      kc = new KKriegerCell;
      *CellSub.Add() = kc;
      break;
    case KCM_ZONE:
      kc = new KKriegerCell;
      *CellZone.Add() = kc;
      break;
    }

    kc->Init(va,mc->Mode);
    kc->Logic = mc->Logic;
    kc->Scene = usescene;

    for(i=0;i<2;i++)
    {
      kc->Event[i] = 0;
      if(kc->Logic.Event[i])
      {
        kc->Event[i] = new KEvent;
        kc->Event[i]->Init();
        kc->Event[i]->Op = kc->Logic.Event[i];
        kc->Event[i]->Translate.x = (kc->BBMin.x + kc->BBMax.x)/2;
        kc->Event[i]->Translate.y =  kc->BBMin.y;
        kc->Event[i]->Translate.z = (kc->BBMin.z + kc->BBMax.z)/2;
        kc->Event[i]->CullDist = 35;
      }
    }


    *CellList.Add() = kc;
  }
}

/****************************************************************************/

// For heapsort in CellConnect.
void KKriegerGame::CellSiftDown(sInt n,sInt k)
{
  KKriegerCell *v = CellList[k];
  sF32 key = v->BBMin.x;

  while(k < (n >> 1))
  {
    sInt j = k*2+1;
    if(j+1 < n && CellList[j]->BBMin.x < CellList[j+1]->BBMin.x)
      j++;

    if(key >= CellList[j]->BBMin.x)
      break;

    CellList[k] = CellList[j];
    k = j;
  }

  CellList[k] = v;
}

//sInt debug_count_splits;

// Connect cells. Uses CellHeapSort.
void KKriegerGame::CellConnect()
{
  // Heapsort the list of cells by minimum x coordinate of bbox.
  sInt n = CellList.Count;
  for(sInt k=n/2-1;k>=0;k--)
    CellSiftDown(n,k);

  while(--n > 0)
  {
    sSwap(CellList[0],CellList[n]);
    CellSiftDown(n,0);
  }

  // Verify the resulting list is sorted
  for(sInt i=0;i<CellList.Count-1;i++)
    sVERIFY(CellList[i]->BBMin.x <= CellList[i+1]->BBMin.x);

  // Sweep-and-prune the list, connecting cells as we identify pairs.
  n = CellList.Count;
  for(sInt box1=0;box1 < n;box1++)
  {
    KKriegerCell *cell1 = CellList[box1];
    sInt cell1m = cell1->Mode & 3;
    sF32 maxKey = cell1->BBMax.x;

    for(sInt box2=box1+1;box2 < n && CellList[box2]->BBMin.x <= maxKey;box2++)
    {
      KKriegerCell *cell2 = CellList[box2];
      sInt cell2m = cell2->Mode & 3;

      if(cell1m == KCM_ADD || cell2m == KCM_ADD)
      {
        // BBoxes overlap in x direction, and at least one of them is an add.
        // Check whether bboxes really intersect.

        if(cell1->BBMax.z < cell2->BBMin.z || cell1->BBMin.z > cell2->BBMax.z)
          continue;

        if(cell1->BBMax.y < cell2->BBMin.y || cell1->BBMin.y > cell2->BBMax.y)
          continue;

        // We have actual overlap (of bboxes atleast). Now connect.
        if(cell1m == KCM_ADD && cell2m == KCM_ADD)
        {
          // Adds need to link to each other, so this is a special case.
          KKriegerCellAdd *c1a = (KKriegerCellAdd *) cell1;
          KKriegerCellAdd *c2a = (KKriegerCellAdd *) cell2;

          *c1a->Adds.Add() = c2a;
          *c2a->Adds.Add() = c1a;
        }
        else // only is one add
        {
          KKriegerCellAdd *cella; // add cell
          KKriegerCell *cello; // other cell
          sInt type;

          if(cell1m == KCM_ADD) // first is add
          {
            cella = (KKriegerCellAdd *) cell1;
            cello = cell2;
            type = cell2m;
          }
          else // second is add
          {
            cella = (KKriegerCellAdd *) cell2;
            cello = cell1;
            type = cell1m;
          }

          if(type == KCM_SUB)
            *cella->Subs.Add() = cello;
          else if(type == KCM_ZONE)
            *cella->Zones.Add() = cello;
        }
      }
    }
  }

}

/****************************************************************************/
/****************************************************************************/

#pragma lekktor(off)

sBool KKriegerGame::OnKey(sU32 key)
{
  sInt i;
  static sInt CheatOn;
  static sS8 weaponswap[8] = {-1,0,1,2,4,6,-1,-1};

  LastKey = key&0x8001ffff;

  switch(key&(0x8001ffff))
  {
  case ' ':
    if(OnGround && JumpTimer==0)
    {
      SpeedUp = JumpForce;
      PlayerSound(4,0.9f);
      JumpTimer = 10;
    }
    break;
  case 'k':
  case 'K':
    Player.Hit(10);
    break;
  case 'r':
  case 'R':
    break;
  case 'w':
  case 'W':
    AccelForw = AccelForwFactor;
    CheatOn = 0;
    return sTRUE;
  case 's':
  case 'S':
    AccelForw = -AccelBackFactor;
    CheatOn = 0;
    return sTRUE;
  case 'd':
  case 'D':
    AccelSide = AccelSideFactor;
    CheatOn = 0;
    return sTRUE;
  case 'a':
  case 'A':
    AccelSide = -AccelSideFactor;
    CheatOn = 0;
    return sTRUE;
  case 'w'|sKEYQ_BREAK:
  case 'W'|sKEYQ_BREAK:
  case 's'|sKEYQ_BREAK:
  case 'S'|sKEYQ_BREAK:
    AccelForw = 0;
    CheatOn = 0;
    return sTRUE;
  case 'd'|sKEYQ_BREAK:
  case 'D'|sKEYQ_BREAK:
  case 'a'|sKEYQ_BREAK:
  case 'A'|sKEYQ_BREAK:
    AccelSide = 0;
    CheatOn = 0;
    return sTRUE;

  case 'y':
  case 'Y':
    FlyMode = !FlyMode;
    return sTRUE;

  case sKEY_SHIFTL:
    Player.UseKey = 1;
    return sTRUE;

  case sKEY_CTRLR:
  case sKEY_MOUSEL:
    Player.FireKey = 1;
    return sTRUE;
  case sKEY_CTRLR|sKEYQ_BREAK:
  case sKEY_MOUSEL|sKEYQ_BREAK:
    Player.FireKey = 0;
    return sTRUE;


  case 'm':
  case 'M':
    CheatOn = 1;
    return sTRUE;
  case 'n':
  case 'N':
    if(CheatOn)
      sCopyMem(&Player.Life,&Player.LifeMax,16*4);
    CheatOn = 0;
    return sTRUE;

  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    if(CheatOn)
    {
      RespawnAt(key&15);
      CheatOn = 0;
    }
    else
    {
      i = weaponswap[key&7];
      if(i>=0 && Player.Weapon[i])
        Player.NextWeapon = i;
    }
    return sTRUE;
  }
  return sFALSE;
}

/****************************************************************************/

void KKriegerGame::AddEvents(KEnvironment *kenv)
{
  sInt i;
  KKriegerCell *cell;


  for(i=0;i<CellZone.Count;i++)
  {
    cell = CellZone[i];
    if(cell->Event[0] && cell->Respawn==0)
      kenv->AddStaticEvent(cell->Event[0]);
    if(cell->Event[1] && cell->Respawn>0)
      kenv->AddStaticEvent(cell->Event[1]);
  }

  if(Player.NextWeapon!=Player.CurrentWeapon && WeaponTimer>=1.0f)
  {
    Player.CurrentWeapon = Player.NextWeapon;
    WeaponEvent.Exit();
    WeaponEvent.Init();
    WeaponEvent.Op = WeaponOptics[Player.CurrentWeapon];
    WeaponTimer = 0.0f;
  }

  if(WeaponEvent.Op)
  {
    WeaponEvent.Translate = PlayerPos;
    WeaponEvent.Translate.y = LastCamY+CamOffset,
    WeaponEvent.Rotate.Init(PlayerLook/sPI2F,PlayerDir/sPI2F,0,0);
    WeaponEvent.Velocity = WeaponTimer;
    WeaponEvent.Modulation = 0;
    if(WeaponCool[Player.CurrentWeapon]>0.01f)
      WeaponEvent.Modulation = (WeaponCool[Player.CurrentWeapon]-Player.CoolTimer)/WeaponCool[Player.CurrentWeapon];
    kenv->AddStaticEvent(&WeaponEvent);
  }
}

/****************************************************************************/

void KKriegerGame::ResetRoot(KEnvironment *env,KOp *root,sBool firsttime)
{
  SetPainter(root,env);
  Restart();
  if(firsttime)
    Switches[KGS_GAME] = KGS_GAME_INTRO;
}

sInt KKriegerGame::GetNewRoot()
{
  sInt sw = Switches[KGS_GAME];
  sInt mode = 1;

  if(sw==KGS_GAME_RUN || sw==KGS_GAME_INGAME || sw==KGS_GAME_RESTART)
    mode = 2;
  if(sw==KGS_GAME_INTRO)
    mode = 0;
  if(sw==KGS_GAME_QUIT)
  {
    sSystem->Exit();
    Switches[KGS_GAME] = KGS_GAME_START;
  }
  if(sw==KGS_GAME_RESTART)
  {
    Switches[KGS_GAME] = KGS_GAME_RUN;
    Restart();
  }


  return mode;
}

// 2004: 0x81ccee

void KKriegerGame::Restart()
{
  sInt i;

  ResetByOp = 1;
  for(i=0;i<CellZone.Count;i++)
    CellZone[i]->DoRespawn();
  if(getenv("KK_STARTPOS"))   // linux port: debug override "x,y,z[,dir]"
  {
    sF32 startdir = 0,startlook = 0;      // "x,y,z[,dir[,look]]"
    sscanf(getenv("KK_STARTPOS"),"%f,%f,%f,%f,%f",&PlayerStartPos.x,&PlayerStartPos.y,&PlayerStartPos.z,&startdir,&startlook);
    SetPlayer(PlayerStartPos,startdir,startlook);
  }
  else
    SetPlayer(PlayerStartPos,0,0);
  CamPos = PlayerPos;
  LastCamY = PlayerPos.y;
  // 2004 clears Switches[1..255]; the port keeps its option switches (8..15)
  sSetMem(Switches+16,0,KKRIEGER_SWITCHES-16);
  KKGameRestartFrames = 2;                  // monsters re-init for 2 frames
}
// 2004: 0x81cd76 (living monsters are not reset)

void KKriegerGame::Continue()
{
  sInt i;
  SetPlayer(PlayerStartPos,0,0);
  for(i=0;i<16;i++)
  {
    if(Switches[KGS_RESPAWN+i] && Respawn[i].Valid)
      SetPlayer(Respawn[i].Pos,Respawn[i].Dir,0);
  }
  Player.Life = 100;
  if(Player.Ammo[0]<200)
    Player.Ammo[0] = 200;
}
// 2004: 0x81ce11

sInt KKriegerGame::SplashCalc(const sVector &pos,KKriegerCellAdd *cell)
{
  sVector v,p1;
  sF32 dist;

  v.Sub3(pos,SplashPos);
  dist = v.Abs3();
  if(dist>=SplashRange)
    return 0;
  p1 = pos;
  p1.y += 0.5f;
  if(cell && FindFirstIntersect(SplashPos,p1,cell,0))
    return 0;
  return (sInt)floorf((1.0f-dist/SplashRange)*SplashHits);    // fistp, rounding down (FPU 0x143f)
}
// 2004: 0x81dd4c. The player and the monsters are particle bodies; the
// slice loop pushes the player body (control + ground spring) and runs one
// physics step per 10ms tick.

void KKriegerGame::OnTick(KEnvironment *kenv,sInt slices)
{
  sInputData id;
  sInt time;
  sF32 d,testh,fslices;
  sVector speed,p0,p1,dir,plane,v;
  sInt i;
  sInt sl;
  sBool inOptions;
  sF32 f;
  KKriegerCellAdd *cell;
  KKriegerParticle *p;
  KEvent *e;

  inOptions = Switches[KGS_GAME] == KGS_GAME_OPTIONS
    || Switches[KGS_GAME] == KGS_GAME_INGAME && Switches[KGS_INGAME_MENU] == 1;

  if(WasInOptions && !inOptions)
    OnOptionsChanged();

  WasInOptions = inOptions;

  if(getenv("KK_GAMELOG"))              // linux port: debug log
  {
    static sInt lastLog = 0;
    sInt now = sSystem->GetTime();
    if(now-lastLog>=1000)
    {
      lastLog = now;
      fprintf(stderr,"game: t=%d state=%d cell=%p pos=(%.2f %.2f %.2f) dir=%.2f look=%.2f accel=%g/%g onground=%d parts=%d cons=%d dcells=%d life=%d wpn=%d/%d ammo=%d,%d,%d,%d\n",
        now,Switches[KGS_GAME],PlayerCell,PlayerPos.x,PlayerPos.y,PlayerPos.z,PlayerDir,PlayerLook,AccelForw,AccelSide,OnGround,
        PartUsed,ConsUsed,DCellUsed,Player.Life,Player.CurrentWeapon,Player.NextWeapon,Player.Ammo[0],Player.Ammo[1],Player.Ammo[2],Player.Ammo[3]);
      for(sInt mi=0;mi<Monsters.Count && mi<6;mi++)
      {
        KKriegerMonster *m = Monsters[mi];
        sVector dd; dd.Sub3(m->Body.Part[0].Pos,PlayerPos);
        fprintf(stderr,"  mon%d: active=%d life=%d pos=(%.2f %.2f %.2f) dist=%.2f mat.l=(%.2f %.2f %.2f) ret.l=(%.2f %.2f %.2f) hit.m1.l=(%.2f %.2f %.2f) blocked=%d\n",mi,m->Active,m->Life,
          m->Body.Part[0].Pos.x,m->Body.Part[0].Pos.y,m->Body.Part[0].Pos.z,sFSqrt(dd.x*dd.x+dd.z*dd.z),
          m->Matrix.l.x,m->Matrix.l.y,m->Matrix.l.z,m->Event.ReturnMatrix.l.x,m->Event.ReturnMatrix.l.y,m->Event.ReturnMatrix.l.z,
          m->Body.HitCell.ConfirmedMatrix.l.x,m->Body.HitCell.ConfirmedMatrix.l.y,m->Body.HitCell.ConfirmedMatrix.l.z,m->Body.HitCell.Blocked);
      }
    }
  }

  if(PlayerCell==0 || Player.Body.Part[0].Cell==0)
    return;
  if(Switches[KGS_GAME]!=KGS_GAME_RUN)      // (restart/quit are handled by GetNewRoot)
    return;
  TickCount += slices;

  Environment = kenv;

  // mouse look (the port's options scale it; with the defaults this is the 2004 formula)

  time = sSystem->GetTime()-LastTime;
  LastTime += time;
  sSystem->GetInput(0,id);
  if(time<1000)
  {
    f = MouseTurnSpeed*(Switches[KGS_MOUSESPEED]+2)/7;
    PlayerDir  += (id.Analog[0] - LastMouseX)*f;
    f = MouseLookSpeed*(Switches[KGS_MOUSESPEED]+2)/7*(-Switches[KGS_MOUSEINVERT]*2+1);
    PlayerLook += (id.Analog[1] - LastMouseY)*f;
    PlayerLook = sRange<sF32>(PlayerLook,sPIF/2,-sPIF/2);
  }
  LastMouseX = id.Analog[0];
  LastMouseY = id.Analog[1];
  PlayerMat.InitEuler(FlyMode?PlayerLook:0,PlayerDir,0);

  // weapon animation

  if(Player.NextWeapon!=Player.CurrentWeapon)
  {
    if(WeaponTimer<0.75f)
      WeaponTimer += slices*0.05f;
    WeaponTimer += slices*0.01f;
  }
  else
  {
    if(WeaponTimer<0.25f)
    {
      WeaponTimer+=slices*0.01f;
      if(WeaponTimer>0.25f)
        WeaponTimer = 0.25f;
    }
    else if(WeaponTimer>0.251f || AccelForw>0)
    {
      WeaponTimer+=slices*0.003f;
      if(WeaponTimer>0.75f)
      {
        if(AccelForw>0)
        {
          WeaponTimer-=0.5f;
          if(WeaponTimer>0.75)
            WeaponTimer = 0.25f;
        }
        else
          WeaponTimer = 0.25f;
      }
    }
  }

  // player step (2004: no OnGround test, plain sample)

  if(AccelForw!=0 || AccelSide!=0)
  {
    StepTimer+=slices*0.01f;
    if(StepTimer>0.5f)
    {
      StepTimer -= 0.5f;
      StepFoot = 1-StepFoot;
      sSystem->SamplePlay(StepFoot,0.8f);
    }
  }

  // splash damage

  if(SplashEnable)
  {
    cell = FindCell(SplashPos);
    for(i=0;i<Monsters.Count;i++)
      Monsters[i]->Hit(SplashCalc(Monsters[i]->Matrix.l,cell),this);
    SplashHits = SplashHits/2;
    Player.Hit(SplashCalc(PlayerPos,cell));
    SplashEnable = 0;
  }

  // fire: the shot op is started as a dynamic event; its Scene_Physic op
  // creates the shot particle (2004: weapon 0 needs ammo too)

  if(Player.FireKey)
  {
    sInt *ammo = &Player.Ammo[Player.CurrentWeapon/2];
    if(*ammo==0)
      sSystem->SamplePlay(15,0.8f);
    if(*ammo>0 && Player.CurrentWeapon==Player.NextWeapon && Player.CoolTimer<=0 && WeaponTimer>=0.25f)
    {
      (*ammo)--;
      Player.CoolTimer = WeaponCool[Player.CurrentWeapon];
      if(!(WeaponFlags[Player.CurrentWeapon]&KWF_CONTINUOUS))
        Player.FireKey = 0;
      if(WeaponShot[Player.CurrentWeapon])
      {
        e = new KEvent;
        e->Init();
        e->Rotate.Init(PlayerLook*0.15915494f,PlayerDir*0.15915494f,0,0);
        e->Translate = PlayerPos;
        e->Translate.y = LastCamY+CamOffset;
        e->Op = WeaponShot[Player.CurrentWeapon];
        kenv->AddDynamicEvent(e);
      }
    }
  }
  if(Player.CoolTimer>=0)
    Player.CoolTimer -= slices*0.01f;

  // particles with UseNewPos get the speed that reaches NewPos this frame

  if(slices>0)
  {
    fslices = (sF32)slices;
    for(i=0;i<PartUsed;i++)
      for(p=PartPtr[i];;p++)
      {
        if(p->UseNewPos)
        {
          v.Sub3(p->Pos,p->OldPos);
          v.Scale3(fslices);
          v.Add3(p->Pos);
          v.Sub3(p->NewPos);
          p->OldPos.AddScale3(v,1.0f/fslices);
          p->UseNewPos = 0;
        }
        if(p->EndMarker) break;
      }
  }

  // the timesliced loop

  fslices = (sF32)slices;
  for(sl=0;sl<slices;sl++)
  {
    if(JumpTimer>0)
      JumpTimer--;

    // ground ray from the centre particle, Gravity+StairHeight long

    testh = GravityPlayer+StairHeight;
    d = testh;
    if(Player.Body.Part[0].Cell && PlayerCell)
    {
      p0 = Player.Body.Part[0].Pos;
      p1 = Player.Body.Part[0].Pos;
      p1.y = p1.y-testh;
      Player.Body.HitCell.Mode |= KCM_DISABLED;
      cell = PlayerCell;
      dir.Init(0,-1.0f,0,0);
      if(FindFirstIntersect(dir,p1,p0,cell,plane,f,&Player.Body.Part[0],0))
        d = f+d;
      Player.Body.HitCell.Mode &= ~KCM_DISABLED;
    }

    // control impulse

    speed.Init(0,0,0,0);
    speed.AddScale3(PlayerMat.i,AccelSide);
    speed.AddScale3(PlayerMat.k,AccelForw);
    speed.y += SpeedUp;
    OnGround = 0;
    SpeedUp = 0;

    if(d<GravityPlayer+StairHeight)
    {
      if(OffGroundTime>=0.4f)               // player was flying: "land" sample
      {
        sSystem->SamplePlay(5,1.0f);
        StepFoot = 0;
        StepTimer = 0;
      }
      OnGround = 1;
      speed.y += ((StairHeight-GravityPlayer)-d)*DampPlayerHeight+GravityPlayer;
      OffGroundTime = 0;
    }
    else
    {
      OffGroundTime += fslices*0.01f;
    }

    Player.Body.Part[0].Control(speed);

    // own hit box follows the body

    Player.Body.HitCell.Matrix1.InitEuler(0,PlayerDir,0);
    Player.Body.HitCell.Matrix1.l = PlayerPos;
    Player.Body.HitCell.Matrix1.l.y += 0.85f;
    Player.Body.HitCell.Matrix1.l.w = 1;
    Player.Body.HitCell.Matrix0.l = Player.Body.HitCell.Matrix1.l;

    Physic((sl+1.0f)/fslices);

    PlayerPos = Player.Body.Part[0].Pos;
    Zones(kenv);

    // camera

    CamPos = PlayerPos;
    LastCamY = (PlayerPos.y-LastCamY)*DampPlayerCam+LastCamY;
    CamPos.y = LastCamY+CamOffset;

    // AI

    for(i=0;i<Monsters.Count;i++)
      MonsterAI(Monsters[i],kenv);

    Player.UseKey = 0;

    if(PlayerCell==0 || PlayerCell->OutsideMask(PlayerPos,0)!=0)
    {
      cell = FindCell(PlayerPos);
      if(cell)
        PlayerCell = cell;
    }
  }

  // frame end: dynamic cells that moved take Matrix1 as next frame's start

  for(i=0;i<DCellUsed;i++)
    if(!DCellPtr[i]->Blocked)
      DCellPtr[i]->Matrix0 = DCellPtr[i]->Matrix1;

  Environment = 0;

  if(Player.Life==0 && Switches[KGS_GAME]==KGS_GAME_RUN)
    Continue();

  if(KKGameRestartFrames>0)
    KKGameRestartFrames--;
}
/****************************************************************************/

// check all collision zones...

void KKriegerGame::Zones(KEnvironment *kenv)
{
  sInt *valp;
  sInt i,action,out;
  KKriegerCell *cell;
  KKriegerCellDynamic *dcell;


  for(i=0;i<CellZone.Count;i++)
  {
    cell = CellZone[i];
    sVERIFY(cell->Mode==KCM_ZONE);

    // respawn

    if(cell->Respawn>0 && cell->Respawn<0x40000000)
    {
      if(cell->Respawn<=10)
        cell->DoRespawn();
      else
        cell->Respawn -= 10;
    }

    // logic

    if(Switches[cell->Logic.Condition])
    {
      action = 0;
      switch(cell->Logic.Code&0xf0)
      {
      case KKEE_ENTER:
        if(cell->Enter&KPM_PLAYER)
          action = 1;
        break;
      case KKEE_LEAVE:
        if(cell->Leave&KPM_PLAYER)
          action = 1;
        break;
      case KKEE_COLLECT:
        if((cell->Collided&KPM_PLAYER) && cell->Respawn==0)
        {
          action = 1;
          cell->Respawn = 0x7fffffff;
        }
        break;
      case KKEE_RESPAWN0:
        if((cell->Collided&KPM_PLAYER) && cell->Respawn==0)
        {
          action = 1;
          cell->Respawn = 10*1000;
        }
        break;
      case KKEE_RESPAWN1:
        if((cell->Collided&KPM_PLAYER) && cell->Respawn==0)
        {
          action = 1;
          cell->Respawn = 30*1000;
        }
        break;
      case KKEE_RESPAWN2:
        if((cell->Collided&KPM_PLAYER) && cell->Respawn==0)
        {
          action = 1;
          cell->Respawn = 60*1000;
        }
        break;
      case KKEE_RESPAWN3:
        if((cell->Collided&KPM_PLAYER) && cell->Respawn==0)
        {
          action = 1;
          cell->Respawn = 5*60000;
        }
        break;
      case KKEE_HIT:
        if(cell->Enter&KPM_WEAPONS)
          action = 1;
        break;
      case KKEE_USE:
        if((cell->Collided&KPM_PLAYER) && Player.UseKey)
          action = 1;
        break;
      case KKEE_ALWAYS:
        action = 1;
        break;
      case KKEE_INSIDE:
        action = (cell->Collided&KPM_PLAYER)?1:0;
        break;
      case KKEE_HITORENTER:
        if(cell->Enter&(KPM_PLAYER|KPM_WEAPONS))
          action = 1;
        break;
      }

      valp = (&Player.Life)+(cell->Logic.Output&15);
      if(action && getenv("KK_GAMELOG") && (cell->Logic.Code&0xf0)!=KKEE_ALWAYS)   // linux port: debug log
        fprintf(stderr,"zone: %p code=%02x out=%d val=%d cond=%d bb=(%.2f %.2f %.2f)-(%.2f %.2f %.2f) planes=%d c=(%.2f %.2f %.2f)\n",
          cell,cell->Logic.Code,cell->Logic.Output,cell->Logic.Value,cell->Logic.Condition,
          cell->BBMin.x,cell->BBMin.y,cell->BBMin.z,cell->BBMax.x,cell->BBMax.y,cell->BBMax.z,cell->PlaneCount,
          cell->Center.x,cell->Center.y,cell->Center.z);
      switch(cell->Logic.Code&0x0f)
      {
      case KKEC_ENABLESWITCH:
        if(action) 
          Switches[cell->Logic.Output] = 1;
        break;
      case KKEC_DISABLESWITCH:
        if(action) 
          Switches[cell->Logic.Output] = 0;
        break;
      case KKEC_TOGGLESWITCH:
        if(action) 
          Switches[cell->Logic.Output] = !Switches[cell->Logic.Output];
        break;
      case KKEC_SETSWITCH:
        Switches[cell->Logic.Output] = action;
        break;
      case KKEC_SETVALUE:
        if(action) 
          *valp = cell->Logic.Value;
        break;
      case KKEC_MAXVALUE:
        if(action) 
          *valp = sMax<sInt>(*valp,cell->Logic.Value);
        break;
      case KKEC_MINVALUE:
        if(action) 
          *valp = sMin<sInt>(*valp,cell->Logic.Value);
        break;
      case KKEC_INCVALUE:
        if(action) 
        {
          out = cell->Logic.Output&15;
          if((&Player.Life)[out]==0 && out>=8)  // 2004: switch only to a new weapon
            Player.NextWeapon = out-8;
          *valp = sMin<sInt>(*valp+cell->Logic.Value,(&Player.LifeMax)[out]);
        }
        break;
      case KKEC_DECVALUE:
        if(action) 
          *valp = sMax<sInt>(*valp-cell->Logic.Value,0);
        break;

      case KKEC_JUMP:
        if(action)
          SpeedUp += 0.001f * cell->Logic.Value;
        break;
      case KKEC_RESPAWN:
        if(action)
          Switches[KGS_RESPAWN+(cell->Logic.Value&15)]=1;
        break;
      }
    }

    // done

    cell->Enter = 0;
    cell->Leave = 0;
    cell->Collided = 0;
  }

  // 2004 (0x81cea2): weapon particles that hit a hit box

  for(i=0;i<8;i++)
    if((Player.Body.HitCell.Enter|Player.Body.HitCell.Collided) & (1<<(KPK_WEAPON0+i)))
      Player.Hit(WeaponHits[i]);

  // reset cell enter/leave info

  for(i=0;i<DCellUsed;i++)
  {
    dcell = DCellPtr[i];

    if(dcell->Monster)
    {
      sInt j;
      for(j=0;j<8;j++)
        if((dcell->Enter|dcell->Collided) & (1<<(KPK_WEAPON0+j)))
          dcell->Monster->Hit(WeaponHits[j],this);
    }
    dcell->Enter = 0;
    dcell->Leave = 0;
    dcell->Collided = 0;
  }
}

/****************************************************************************/

void KKriegerGame::RespawnAt(sInt i)
{
  if(Respawn[i].Valid || i==1)
  {
    SetPlayer(Respawn[i].Pos,Respawn[i].Dir,0);
    PlayerSound(11);
  }
}

/****************************************************************************/

void KKriegerGame::OnPaint(sMaterialEnv *env)
{
}

/****************************************************************************/

void KKriegerGame::OnOptionsChanged()
{
  // update engine usage mask using "shadows" switch
  sU32 usageMask = ~0U & ~(1<<ENGU_SHADOW);

  if(Switches[KGS_SHADOWS])
    usageMask |= 1<<ENGU_SHADOW;

  Engine->SetUsageMask(usageMask);

  // update resolution if necessary
  static const sInt xRes[] = { 640,800,1024,1280 };
  static const sInt yRes[] = { 480,600, 768,1024 };
  sInt res = Switches[KGS_RESOLUTION];
  static sInt lastRes = -1;         // linux port: keep the startup resolution
  if(lastRes<0) lastRes = res;      // (the 2004 release had no options menu)

  if(res != lastRes && xRes[res] != sSystem->ConfigX) // resolution changed?
  {
    sSystem->ConfigX = xRes[res];
    sSystem->ConfigY = yRes[res];

    sSystem->InitScreens();
  }
  lastRes = res;
}

/****************************************************************************/
/****************************************************************************/

void KKriegerGame::GetCamera(sMaterialEnv &env)
{
  if(CamZoomPos)
  {
    env.CameraSpace.InitEuler(0,PlayerDir,0);
    env.CameraSpace.l = PlayerPos;
    env.CameraSpace.l.w = 1.0f;
    env.CameraSpace.l.AddScale3(env.CameraSpace.k,-2.0f);
  }
  else
  {
    env.CameraSpace.InitEuler(PlayerLook,PlayerDir,0);
    env.CameraSpace.l = CamPos;
    env.CameraSpace.l.w = 1.0f;
  }
  env.ZoomX = env.ZoomY = 1.0f;
  env.Orthogonal =  sMEO_PERSPECTIVE;
}

void KKriegerGame::GetPlayer(sMatrix &m)
{
  m.Init();
  m.l.z = -5;
}

/****************************************************************************/
/***                                                                      ***/
/***   Sound                                                              ***/
/***                                                                      ***/
/****************************************************************************/

void KKriegerGame::PlayerSound(sInt sound,sF32 volume)
{
  sInt buf;
  sVector zero;

  zero.Init(0,0,0,0);
  {
    buf = sSystem->SamplePlay(sound,volume);
    sSystem->Sample3DParam(sound,buf,PlayerPos,zero,0.2f,1.0f);
  }
}

/****************************************************************************/
/***                                                                      ***/
/***   Game Logic                                                         ***/
/***                                                                      ***/
/****************************************************************************/




// gegenseitige abstoßung der monster

/****************************************************************************/
/***                                                                      ***/
/***   Particles and Collision                                            ***/
/***                                                                      ***/
/****************************************************************************/

/****************************************************************************/

/****************************************************************************/
/***                                                                      ***/
/***   Totally new math                                                   ***/
/***                                                                      ***/
/****************************************************************************/


// find nearest intersection with subcell.
// .. add code to check zones here ..

/****************************************************************************/
/***                                                                      ***/
/***   New Math                                                           ***/
/***                                                                      ***/
/****************************************************************************/


// calculate which planes are out
// positive epsilons will enlarge the box!


// calculate intersection point ray -> cell when casting from inside to outside

// calculate intersection point ray -> cell when casting from the outside

/****************************************************************************/

// find an ADD cell.

KKriegerCellAdd *KKriegerGame::FindCell(const sVector &v)
{
  sInt i;
  for(i=0;i<CellAdd.Count;i++)
  {
    if(CellAdd[i]->OutsideMask(v)==0)
      return CellAdd[i];
  }
  return 0;
}

// faked code to check CollideRay

// cool code that does not work


/****************************************************************************/
/***                                                                      ***/
/***   Operators                                                          ***/
/***                                                                      ***/
/****************************************************************************/

#pragma lekktor(on)

void __stdcall Exec_KKrieger_Para(KOp *op,KEnvironment *kenv)
{
  sU32 *du;
  sF32 *df;
  sInt i;

  du = op->GetAnimPtrU(0);
  df = op->GetAnimPtrF(0);

  kenv->Game->Player.LifeMax    = du[1];
  kenv->Game->Player.ArmorMax  = du[3];
  kenv->Game->Player.AlphaMax   = du[5];
  kenv->Game->Player.BetaMax    = du[7];
  kenv->Game->Player.AmmoMax[0] = du[9];
  kenv->Game->Player.AmmoMax[1] = du[11];
  kenv->Game->Player.AmmoMax[2] = du[13];
  kenv->Game->Player.AmmoMax[3] = du[15];
  if(kenv->Game->ResetByOp)
  {
    kenv->Game->ResetByOp = 0;
    kenv->Game->Player.Life    = du[0];
    kenv->Game->Player.Armor  = du[2];
    kenv->Game->Player.Alpha   = du[4];
    kenv->Game->Player.Beta    = du[6];
    kenv->Game->Player.Ammo[0] = du[8];
    kenv->Game->Player.Ammo[1] = du[10];
    kenv->Game->Player.Ammo[2] = du[12];
    kenv->Game->Player.Ammo[3] = du[14];
    for(i=0;i<8;i++)
      kenv->Game->Player.Weapon[i] = (du[16]>>i)&1;;
  }

  kenv->Game->GravityPlayer     = df[17];
  kenv->Game->DampPlayerGround  = df[18];
  kenv->Game->DampPlayerAir     = df[19];
  kenv->Game->DampPlayerHeight  = df[20];
  kenv->Game->StairHeight       = df[21];
  kenv->Game->EyeHeight         = df[22];
  kenv->Game->MouseTurnSpeed    = df[23];
  kenv->Game->MouseLookSpeed    = df[24];
  kenv->Game->AccelSideFactor   = df[25];
  kenv->Game->AccelForwFactor   = df[26];
  kenv->Game->AccelBackFactor   = df[27];
  kenv->Game->JumpForce         = df[28];
  kenv->Game->PlayerStartPos.Init(df[29],df[30],df[31]);
  kenv->Game->DampPlayerCam     = df[56];


  sCopyMem(kenv->Game->WeaponHits,du+32,24*4);

  kenv->Game->CamOffset = kenv->Game->EyeHeight-kenv->Game->StairHeight;

  op->ExecInputs(kenv);
}

void __stdcall Exec_KKrieger_Events(KOp *op,KEnvironment *kenv)
{
  KOp **ptr;
  sInt i;

  switch(*op->GetAnimPtrU(0))
  {
  case 0:
  default:
    ptr = kenv->Game->WeaponShot;
    break;
  case 1:
    ptr = kenv->Game->WeaponOptics;
    break;
  case 2:
    ptr = kenv->Game->WeaponExplode[0];
    break;
  case 3:
    ptr = kenv->Game->WeaponExplode[1];
    break;
  }

  for(i=0;i<8;i++)
    ptr[i] = op->GetLink(i);

  op->ExecInputs(kenv);
}

class KObject * __stdcall Init_KKrieger_Para(KOp *op,KEnvironment *kenv)
{
  // linux port: the 2004 Init_KKrieger_Para is the same function as
  // Init_KKrieger_Events (0x81a649) - the start position is only set by
  // Exec. Setting it here let the last loaded Para op (menu scene, op 4383,
  // start (0,0,0)) win over the game's.
  //kenv->Game->PlayerStartPos.Init(df[29],df[30],df[31]);

  if(op->GetInput(0))
    return op->GetInput(0)->Cache;
  else
    return new GenScene;
}

class KObject * __stdcall Init_KKrieger_Events(KOp *op)
{
  if(op->GetInput(0))
    return op->GetInput(0)->Cache;
  else
    return new GenScene;
}

/****************************************************************************/

struct MonsterMem : public KInstanceMem
{
  KKriegerMonster Monster;
};

// linux port: the 2004 monster op has no weapon kind. Its link 0 is the event
// op of a ranged attack, e.g. Misc_Event -> Scene_Transform (rotated by the
// event) -> Scene_Transform (start offset) -> Scene_Physic (flags 0x20 =
// monster shot: speed, particle kind) -> visual. FUN_0081d33e starts it as a
// dynamic event (see FireShot2004).
// 2004: 0x81d7d6. The monster is a particle body (KKriegerBody) with a SUB
// hit box; MonsterAI moves the body, the monster's event graph positions
// itself from the event's Rotate/Translate and its Scene_Walk op passes the
// resulting matrix back in Event.ReturnMatrix.

void __stdcall Exec_KKrieger_Monster(KOp *op,KEnvironment *kenv)
{
  KKriegerMonster *mon;
  MonsterMem *mem;
  sF32 *fp;
  sMatrix m;
  sVector scale,ofs,p;
  KKriegerCellAdd *cell;

  mem = kenv->GetInst<MonsterMem>(op);
  mon = &mem->Monster;
  if(mem->Reset)
    sSetMem(mon,0,sizeof(KKriegerMonster));

  if(mem->Reset || KKGameRestartFrames!=0)  // re-init for 2 frames after a restart
  {
    const sMatrix &top = kenv->ExecStack.Top();
    fp = op->GetAnimPtrF(0);

    mon->Event.Init();
    mon->Event.Rotate.Init(fp[0],fp[1],fp[2],0);
    mon->Event.Translate.Init(fp[3],fp[4],fp[5],0);
    sCopyMem(&mon->Speed,fp+6,14*4);        // Speed..MinRadius
    mon->Speed *= 0.001f;
    mon->ShotOp = op->GetLink(0);
    mon->Life = mon->LifeMax;
    mon->Matrix = top;
    mon->Event.Translate.Add3(top.l);
    mon->Event.Op = 0;
    mon->Event.ReturnMatrix.Init();
    mon->Event.ReturnMatrix.l = mon->Event.Translate;
    mon->Event.ReturnMatrix.l.w = 1.0f;
    mon->Event.Monster = mon;
    mon->DeathEvent.Init();

    m.InitEuler(mon->Event.Rotate.x,mon->Event.Rotate.y,mon->Event.Rotate.z);
    scale.Init(fp[20],fp[21],fp[22],0);
    ofs.Init(fp[23],fp[24],fp[25],0);
    m.l.Rotate3(m,ofs);
    m.l.w = 1.0f;

    p = top.l;
    p.y += 0.5f;
    cell = kenv->Game->FindCell(p);
    mon->Body.Init(p,cell,KPK_MONSTER);
    mon->Body.HitCell.Init(m,scale,KCM_SUB);
    mon->Body.HitCell.PrepareDynamic(top);
    mon->Body.HitCell.Monster = mon;        // Zones() turns weapon hits into mon->Hit()
    mem->DeleteChild = &mon->Event.FirstInstance;
  }

  if(mon->Life>0)                           // dead monsters: nothing at all
  {
    mon->Body.HitCell.Matrix1 = mon->Matrix;
    *kenv->Game->Monsters.Add() = mon;
    if(mon->Active)
      mon->Body.Add(kenv->Game);
    if(op->GetInput(0))
    {
      kenv->ExecStack.PushIdentity();
      op->GetInput(0)->ExecEvent(kenv,&mon->Event,1);
      kenv->ExecStack.Pop();
    }
  }
}
class KObject * __stdcall Init_KKrieger_Monster(KOp *op)
{
  sInt i;

  for(i=0;i<op->GetInputCount();i++)
  {
    sVERIFY(op->GetInput(i));
    sVERIFY(op->GetInput(i)->Cache);
    op->GetInput(i)->Cache->Release();
  }
  return new GenScene();
}

/****************************************************************************/

void __stdcall Exec_KKrieger_MonsterFlags(KOp *op,KEnvironment *kenv,sInt kill,sInt spawn,sInt flags)
{
  kenv->NextMonsterOverride = 1;
  kenv->NextMonsterKillSwitch = kill;
  kenv->NextMonsterSpawnSwitch = spawn;
  kenv->NextMonsterFlags = flags;

  op->ExecInputs(kenv);

  kenv->NextMonsterOverride = 0;
}

class KObject * __stdcall Init_KKrieger_MonsterFlags(KOp *op)
{
  sVERIFY(op->GetInput(0));
  sVERIFY(op->GetInput(0)->Cache);
  return op->GetInput(0)->Cache;
//  op->GetInput(0)->Cache->Release();
//  return new GenScene();
}

/****************************************************************************/

class KObject * __stdcall Init_KKrieger_Respawn(sF323 pos,sInt zone,sF32 dir)
{
  return new GenScene;
}

void __stdcall Exec_KKrieger_Respawn(KOp *op,KEnvironment *kenv,sF323 pos,sInt zone,sF32 dir)
{
  kenv->Game->Respawn[zone].Valid = 1;
  kenv->Game->Respawn[zone].Pos.Init(pos.x,pos.y,pos.z);
  kenv->Game->Respawn[zone].Dir = dir*sPI2F;
}

/****************************************************************************/

class KObject * __stdcall Init_KKrieger_SplashDamage(sInt hits,sF32 range,sF32 enable)
{
  return new GenScene;
}

struct SplashDamageMem : public KInstanceMem
{
  sInt old;
};

void __stdcall Exec_KKrieger_SplashDamage(KOp *op,KEnvironment *kenv,sInt hits,sF32 range,sF32 enable)
{
  SplashDamageMem *mem;
  sBool ok;

  mem = kenv->GetInst<SplashDamageMem>(op);
  
  ok = (enable>0);
  if(ok && !mem->old)
  {
    kenv->Game->SplashEnable = 1;
    kenv->Game->SplashPos = kenv->ExecStack.Top().l;
    kenv->Game->SplashRange = range;
    kenv->Game->SplashHits = hits;
  }
  mem->old = ok;
}

/****************************************************************************/
/***                                                                      ***/
/***   Helpers                                                            ***/
/***                                                                      ***/
/****************************************************************************/

static sBool sMakePlane(sVector &p,const sVector &v0,const sVector &v1,const sVector &v2)
{
  sVector d0,d1,v;
  sF64 e;

  d0.Sub3(v0,v1);
  d1.Sub3(v1,v2);
  v.Cross3(d0,d1);

  if(v.Dot3(v)<1e-10) return sFALSE;
  
  e = sFSqrt(v.Dot3(v));                    // we need some really normal normals here
  v.x = v.x/e;
  v.y = v.y/e;
  v.z = v.z/e;
  v.w = v.Dot3(v1);

  p = v;
  return sTRUE;
}

void KKriegerCell::Init(const sMatrix &mat,const sVector &scale,sInt mode)
{
  sVector va[8];
  sInt i;

  for(i=0;i<8;i++)
  {
    va[i].x = scale.x * -(((i>>0)&1)-0.5f);
    va[i].y = scale.y * -(((i>>1)&1)-0.5f);
    va[i].z = scale.z * -(((i>>2)&1)-0.5f);
    va[i].w = 1;
    va[i].Rotate34(mat);
  }
  Init(va,mode);
}

void KKriegerCell::Init(const sVector *va,sInt mode)
{
  sInt k;
  sF32 d;
  sVector p;
  sBool ok;
  static sInt order[6][4] = 
  {
    { 0,2,3,1 },
    { 2,6,7,3 },
    { 3,7,5,1 },
    { 4,0,1,5 },
    { 2,0,4,6 },
    { 7,6,4,5 },
  };

  sSetMem(this,0,sizeof(*this));

  for(k=0;k<8;k++)
    Vertices[k] = va[k];

  Mode = mode&(3|8);                       // 2004: 3|8 (9 = sub that only collides for monster feet)
  OnlyForShot = (mode&4)?1:0;
//  NotForPlayer = (mode&KCM_NOTFORPLAYER)?1:0;

  for(k=0;k<6;k++)
  {
    ok = sFALSE;
    if(!sMakePlane(p,va[order[k][0]],va[order[k][1]],va[order[k][2]]))
    {
      if(!sMakePlane(p,va[order[k][1]],va[order[k][2]],va[order[k][3]]))
        if(!sMakePlane(p,va[order[k][2]],va[order[k][3]],va[order[k][0]]))
          if(!sMakePlane(p,va[order[k][3]],va[order[k][0]],va[order[k][1]]))
            ; // no way finding even a single plane, no        
          else
            ok = sTRUE; // it's just a triange
        else
          ok = sTRUE; // it's just a triange
      else
        ok = sTRUE; // it's just a triange
    }
    else  // it's a quad. lets check if it's a plane one!
    {
      ok = sTRUE;
      d = p.Dot3(va[order[k][3]])-p.w;
      if(d<-0.005f)    // it's a bad one, and even inconvex
      {
        sMakePlane(p,va[order[k][1]],va[order[k][2]],va[order[k][3]]);
        sVERIFY(PlaneCount<=KKRIEGER_MAXPLANES);
        Planes[PlaneCount++] = p;
        sMakePlane(p,va[order[k][3]],va[order[k][0]],va[order[k][1]]);
      }
      else if(d>0.005f)   // it's a bad one, but convex
      {
        sVERIFY(PlaneCount<=KKRIEGER_MAXPLANES);
        Planes[PlaneCount++] = p;
        sMakePlane(p,va[order[k][2]],va[order[k][3]],va[order[k][0]]);
      }
    }
    if(ok)
    {
      sVERIFY(PlaneCount<=KKRIEGER_MAXPLANES);
      Planes[PlaneCount++] = p;
    }
  }

  for(k=0;k<PlaneCount;k++)
  {
    Planes[k].w = -Planes[k].w+OVERLAP;
    if((Mode&3)==KCM_SUB)         // extrude subs twice, so that subs directly on add's still overlap
      Planes[k].w += OVERLAP;
  }
  Center = BBMin = BBMax = va[0];
  for(k=1;k<8;k++)
  {
    Center.Add3(va[k]);
    BBMin.x = sMin(BBMin.x,va[k].x);
    BBMin.y = sMin(BBMin.y,va[k].y);
    BBMin.z = sMin(BBMin.z,va[k].z);
    BBMax.x = sMax(BBMax.x,va[k].x);
    BBMax.y = sMax(BBMax.y,va[k].y);
    BBMax.z = sMax(BBMax.z,va[k].z);
  }
  BBMin.x -= OVERLAP;
  BBMin.y -= OVERLAP;
  BBMin.z -= OVERLAP;
  BBMax.x += OVERLAP;
  BBMax.y += OVERLAP;
  BBMax.z += OVERLAP;
  Center.Scale3(1.0f/8);
  Center.w = 1;
}

/****************************************************************************/

void KKriegerCell::DoRespawn()
{
  Respawn = 0;
  if(Event[1])
  {
    if(Event[1]->FirstInstance)
      Event[1]->FirstInstance->DeleteChain();
    Event[1]->FirstInstance = 0;
  }
}

/****************************************************************************/

void KKriegerCellDynamic::ApplyMatrix(sMatrix &mat)
{
  sInt i;
  for(i=0;i<PlaneCount;i++)
  {
    Planes[i].RotatePl(mat,OrigPlanes[i]);
    Planes[i].Scale4(1.0f / Planes[i].Abs3());
  }

  for(i = 0; i < 8; i++)
  {
    Vertices[i].Rotate3(mat, OrigVertices[i]);
    Vertices[i].Add3(mat.l);
  }

  Center = mat.l;
  CurrentMatrix = mat;
  Blocked = 0;
}

/****************************************************************************/

