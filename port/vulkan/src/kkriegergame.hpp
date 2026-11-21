// This file is distributed under a BSD license. See LICENSE.txt for details.

#ifndef __KKRIEGERGAME_HPP__
#define __KKRIEGERGAME_HPP__

#include "_types.hpp"
#include "_start.hpp"
#include "genscene.hpp"

/****************************************************************************/
/****************************************************************************/

// obsolete
#define KKRIEGER_MAXCELL        0x8000

// new and improved!
#define KKRIEGER_MAXDCELL       0x0200
#define KKRIEGER_MAXPARTICLE    0x4000
#define KKRIEGER_MAXCONSTRAINT  0x1000
#define KKRIEGER_MAXMONSTER     0x0200
#define KKRIEGER_MAXSHOT        0x0200
#define KKRIEGER_MAXPLANES      12

#define KKRIEGER_SWITCHES       256
#define KKRIEGER_AMMOKIND       4
#define KKRIEGER_WEAPONKIND     8
#define KKRIEGER_STATS          16          // 4 stats+AMMOKIND+WEAPONKIND

struct KKriegerCell;
//struct KKriegerParticle;
//struct KKriegerConstraint;
struct KKriegerGame;


// cell mode

#define KCM_ADD                 0
#define KCM_SUB                 1
#define KCM_ZONE                2
#define KCM_MAX                 3

#define KCM_NOTFORPLAYER        0x04        // (sub/add only) forbidden for KCRF_ISPLAYER
#define KCM_ONLYMONSTER         0x08        // (sub/add only) allowed only for KCRF_ISMONSTER
#define KCM_DISABLED            0x10        // (dynamic only) the box has been temporarly disabled
#define KCM_UNCONFIRMED         0x20        // (dynamic only) the box has not yet been confirmed

// particle kind

#define KPK_UNUSED               0          // this particle has no special effects
#define KPK_PLAYER               1          // the main particle of the player
#define KPK_PLAYERAUX            2          // auxilary particle for player collision
#define KPK_MONSTER              3          // the main particle of the player
#define KPK_MONSTERAUX           4          // auxilary particle for player collision
#define KPK_WEAPON0              8          // the weapons
#define KPK_WEAPON1              9
#define KPK_WEAPON2             10
#define KPK_WEAPON3             11
#define KPK_WEAPON4             12
#define KPK_WEAPON5             13
#define KPK_WEAPON6             14
#define KPK_WEAPON7             15

#define KPM_PLAYER              0x00000002  // bitmask to find any player
#define KPM_WEAPONS             0x0000ff00  // bitmask to find any weapon-hit

// weapon flags

#define KWF_CONTINUOUS          0x01        // hold button to continue
#define KWF_REFLECT             0x02        // old shells reflect away

// special switches
// see this as "recommended usage", since few are really enforced by the code

#define KGS_ONE                 0x00        // always one
#define KGS_GAME                0x01        // game runs when switch==0. use for ingame-menu
#define KGS_RESOLUTION          0x08        // screen 640/800/1024/1280, needs to be checked by code when restarting game
#define KGS_TEXTURES            0x09        // textures low/normal, needs to be checked by code when restarting game
#define KGS_SHADOWS             0x0a        // shadows on/off, code or ops ???
#define KGS_GLARE               0x0b        // IPP low/med/high, handled with ops
#define KGS_MOUSEINVERT         0x0c        // invert mouse on/off
#define KGS_MOUSESPEED          0x0d        // mouse-speed 0..9
#define KGS_BRIGHTNESS          0x0e        // gamma-correction 0..9
#define KGS_SPECULAR            0x0f        // specular on/off
#define KGS_INGAME_MENU         0x10        // ingame menu state

#define KGS_RESPAWN             0x20        // switches 32-48 for respawn flags

#define KGS_GAME_RUN            0x00        // game runs
#define KGS_GAME_INGAME         0x01        // ingame menu state
#define KGS_GAME_RESTART        0x02        // restart game.
#define KGS_GAME_QUIT           0x03        // termiante program
#define KGS_GAME_WON            0x04        // game is won
#define KGS_GAME_LOST           0x05        // game is lost
#define KGS_GAME_START          0x06        // program just started. main menu
#define KGS_GAME_CREDITS        0x07        // credit scroller
#define KGS_GAME_INTRO          0x08        // intro sequence, shown onyl once
#define KGS_GAME_OPTIONS        0x09        // options menu

/****************************************************************************/

struct KKriegerMeshCell
{
  sVector Vert[8];
  sInt Mode;
  KLogic Logic;
};

class KKriegerMesh : public KObject
{
public:
  KKriegerMesh(GenMesh *mesh);
  ~KKriegerMesh();
  void Copy(KObject *);

  KKriegerMeshCell *Cell;
  sInt CellCount;
};

struct KKriegerCell
{
  sVector BBMin,BBMax;                      // (obsolete) bounding box
  sVector Planes[KKRIEGER_MAXPLANES];       // .. with PlaneCount. normal points INSIDE
  sVector Center;                           // center, for hit-reaction
  sInt PlaneCount;
  GenScene *Scene;                          // scene op this cell belongs to
  KEvent *Event[2];                         // item of collectable, event for item gone

  sInt Mode;                                // add or sub
  sInt OnlyForShot;                         // not used in MoveCollider 
  KLogic Logic;                             // what to do..
  sU32 Enter;                               // particle of that (1<<kind) has entered (KCM_ZONE only)
  sU32 Leave;                               // particle of that (1<<kind) has left (KCM_ZONE only)
  sU32 Collided;                            // particle of that (1<<kind) is inside (KCM_ZONE) or has collided (KCM_SUB)
  sInt Respawn;                             // backward-counter to rewspawn

  sVector Vertices[8];                      // original vertices in world space

  // interface

  // linux port: 2004 versions (kkphysic.cpp). OutsideMask: a positive radius
  // ENLARGES the cell; IntersectIn/Out have no radius (particles are points)
  sInt OutsideMask(const sVector &v,sF32 radius=0);   // bitmask for each plane if v is outside
  sBool IntersectOut(const sVector &p,const sVector &d,sVector &plane,sF32 &dist); 
  sBool IntersectIn (const sVector &p,const sVector &d,sVector &plane,sF32 &dist); 

  void Init(const sMatrix &mat,const sVector &scale,sInt mode);
  void Init(const sVector *v,sInt mode);

  void DoRespawn();
};

struct KKriegerCellAdd : KKriegerCell
{
  sArray<KKriegerCellAdd*> Adds;            // neighbourhood adds
  sArray<KKriegerCell*> Subs;               // subs inside this add
  sArray<KKriegerCell*> Zones;              // zones inside this add
};


struct KKriegerCellDynamic : KKriegerCell
{
  sVector Delta;                            // inverted matrix-movement
  sInt Blocked;                             // during movement, cell was blocked.
  sVector OrigPlanes[6];                    // original planes.
  sVector OrigVertices[8];                  // original vertices

  struct KKriegerPartBox *PartBox;          // link to partbox, for smashing crates (always 0 in 2004)
  struct KKriegerMonster *Monster;          // connect to monster for hitting

  sMatrix ConfirmedMatrix;                  // the matrix, where the particles are outside (if Active==1)
  sMatrix CurrentMatrix;                    // the matrix that is checked now
  sMatrix Matrix0;                          // matrix at beginning of FRAME (not Tick)
  sMatrix Matrix1;                          // matrix at end of FRAME (not Tick)
  void PrepareDynamic(const sMatrix &);     // copy Orig-values from KKriegerCell, set initial matrix

  void ApplyMatrix(sMatrix &mat);           // apply the matrix, called by Physic
};

/****************************************************************************/
/***                                                                      ***/
/***   2004 particle physics (linux port: recovered from pno0001.exe,     ***/
/***   the public source only kept these declarations as comments)        ***/
/***                                                                      ***/
/****************************************************************************/

struct KKriegerParticle
{
  sInt EndMarker;                           // last in array.
  KKriegerParticle *Next;                   // linked list (unused)
  struct KKriegerConstraint *Cons;          // (unused)
  sInt Kind;                                // KPK_*
  sInt UseNewPos;
  sInt VerifyPos;                           // this particle is new, verify position!
  sInt DCellState;                          // (unused)
  KKriegerCellAdd *Cell;                    // the particle is in this add
  KKriegerCellDynamic *SkipCell;            // skip this sub
  KEvent *ShotEvent;                        // if this is a shot, here it kills itself on impact
  sF32 Damp;                                // one-step damping
  sF32 Mass;

  sVector Force;                            // position-delta created by "hit"
  sVector Pos;                              // current position
  sVector OldCollPos;                       // last collision-free position
  sVector OldPos;                           // old position (verlet)
  sVector NewPos;                           // target for UseNewPos

  void Init(const sVector &pos,const sVector &speed,KKriegerCellAdd *cell);
  void Hit(struct KKriegerGame *,const sVector &pos,const sVector &v,sF32 dist,sInt hitmonster);
  void Control(const sVector &v);           // move the whole particle array
};

struct KKriegerConstraint                   // connect two particles
{
  sInt EndMarker;                           // last in array.
  KKriegerConstraint *Next;                 // (unused)
  KKriegerParticle *PartA,*PartB;
  sF32 Dist;
};

struct KKriegerPartBox                      // tumbling box (Scene_Physic mode 1)
{
  KKriegerParticle Part[8];
  KKriegerConstraint Cons[16];

  void Init(const sMatrix &mat,const sVector &scale,const sVector &speed,KKriegerCellAdd *cell);
  void Register(struct KKriegerGame *game);
  void GetMatrix(sMatrix &mat);
};

struct KKriegerBody                         // player and monster body
{
  KKriegerParticle Part[5];                 // centre + 4 around
  KKriegerConstraint Cons[10];              // constraints that link them
  KKriegerCellDynamic HitCell;              // cell used for hitting
  void Init(const sVector &pos,KKriegerCellAdd *cell,sInt kpk);
  void Add(struct KKriegerGame *game);
  void MoveDelta(const sVector &v) { Part[0].Control(v); }
};

struct KKriegerMonster                      // a monster (2004 layout)
{
  sMatrix Matrix;                           // output matrix of the monster's walk op (Event.ReturnMatrix)

  // no not change order of this block
  sF32 Speed;
  sF32 NoticeRadius;
  sF32 ChargeRadius;
  sInt Flags;

  sInt LifeMax;
  sInt Armor;
  sInt MeeleeHits;
  sF32 MeeleeTime;
  sInt RangedHits;
  sF32 RangedTime;
  sF32 RangedAim;
  sInt KillSwitch;

  sF32 WaitRadius;
  sF32 MinRadius;

  // end of parameter block

  KEvent Event;                             // the monster itself
  KEvent DeathEvent;                        // (never executed in 2004)
  KOp *ShotOp;                              // link 0: event op of a ranged attack
  sInt Life;
  sF32 MeeleeTimer;                         // 0..MeeleeTime
  sF32 RangedTimer;                         // 0..RangedTime
  sInt Active;                              // body registered + AI running
  KKriegerBody Body;

  void Hit(sInt hits,struct KKriegerGame *game);
};

struct KKriegerPlayer
{
  sInt CurrentWeapon;                       // current weapon
  sInt NextWeapon;                          // weapon change...
  sInt UseKey;                              // press the use-key
  sInt FireKey;
  sF32 CoolTimer;                           // cooldown for weapon

// Collectables... don't change order

  sInt Life;                                // hitpoints
  sInt Armor;                              // absorb before hit
  sInt Alpha;                               // free for use
  sInt Beta;                                // free for use
  sInt Ammo[KKRIEGER_AMMOKIND];             // count for ammo
  sInt Weapon[KKRIEGER_WEAPONKIND];         // possesion of weapon

// max for collectables.

  sInt LifeMax;
  sInt ArmorMax;
  sInt AlphaMax;
  sInt BetaMax;
  sInt AmmoMax[KKRIEGER_AMMOKIND];
  sInt WeaponMax[KKRIEGER_WEAPONKIND];      // max. 1 weapon

// physics

  KKriegerBody Body;                        // 5 particles, constraints and the hit cell

// interface

  void Init();
  void Hit(sInt hits);
  void Sound(sInt handle,sF32 volume=1.0f); // (internal) helper
};

struct KKriegerRespawn
{
  sInt Valid;                               // was set by Respawn op
  sInt Active;                              // was activated by player
  sVector Pos;                              // position
  sF32 Dir;                                 // look-direction
};

struct KKriegerGame
{
  KEnvironment *Environment;

  // static allocated stuff

  sArray<KKriegerCellAdd *> CellAdd;
  sArray<KKriegerCell *> CellSub;
  sArray<KKriegerCell *> CellZone;

  sArray<KKriegerCell *> CellList;

  // stuff added each frame

  sArray<KKriegerMonster *> Monsters;

  KKriegerParticle *PartPtr[KKRIEGER_MAXPARTICLE];
  KKriegerConstraint *ConsPtr[KKRIEGER_MAXCONSTRAINT];
  KKriegerCellDynamic *DCellPtr[KKRIEGER_MAXDCELL];

  sInt PartUsed;
  sInt ConsUsed;
  sInt DCellUsed;


  // player statistics

  sVector PlayerPos;                        // movement
  sF32 PlayerLook;
  sF32 PlayerDir;
  KKriegerCellAdd *PlayerCell;              // current cell
  sInt CamZoomPos;                          // toogle 1st and 3rd person

  KKriegerPlayer Player;
  sU8 Switches[KKRIEGER_SWITCHES];          // logical switches
  sInt WeaponHits[KKRIEGER_WEAPONKIND];
  sF32 WeaponCool[KKRIEGER_WEAPONKIND];
  sInt WeaponFlags[KKRIEGER_WEAPONKIND];

  KKriegerRespawn Respawn[16];

  // player dynamics

  sMatrix PlayerMat;
  sF32 CamOffset;

  sF32 SpeedForw;                           // dynaimc player
  sF32 SpeedSide;
  sF32 SpeedUp;
  sF32 AccelForw;
  sF32 AccelSide;
  sInt FlyMode;                             // toggle "fly" mode with 'y'
  sBool OnGround;
  sBool ResetByOp;
  sInt JumpTimer;
  sU32 LastCancel;
  sInt LastTime;
  sInt LastMouseX;
  sInt LastMouseY;
  sF32 LastCamY;
  sVector CamPos;

  sF32 Gravity;                             // Static player
  sF32 GravityPlayer;
  sF32 DampPlayerAir;
  sF32 DampPlayerGround;
  sF32 DampPlayerHeight;
  sF32 StairHeight;
  sF32 EyeHeight;
  sF32 MouseTurnSpeed;
  sF32 MouseLookSpeed;
  sF32 AccelSideFactor;
  sF32 AccelForwFactor;
  sF32 AccelBackFactor;
  sF32 JumpForce;
  sVector PlayerStartPos;
  sF32 DampPlayerCam;

  // Stuff
  sBool WasInOptions;                       // some switches are checked after leaving options

  KEvent WeaponEvent;                       // event for displaying weapon
  sF32 WeaponTimer;                         // time for weapon animation
  KOp *WeaponShot[8];                       // event for the shot 
  KOp *WeaponOptics[8];                     // event for the weapon mesh
  KOp *WeaponExplode[2][8];                 // event for hit/miss 
  sF32 StepTimer;                           // steptime for player
  sInt StepFoot;                            // stepfoot for player
  sF32 OffGroundTime;                       // time off ground

  sInt SplashEnable;
  sVector SplashPos;
  sF32 SplashRange;
  sInt SplashHits;

  sInt CollisionForMonsterMode;
  sInt LastKey;
  sInt TickCount;
  sInt PlayerAdds;
 
  // statistics


  // interface

  void Init();
  void Exit();
  void Flush();

  void SetMesh(GenMesh *);
  void SetPainter(KOp *,KEnvironment *kenv);
  void SetScene(GenScene *);
  void SetPlayer(sVector pos,sF32 dir,sF32 look);
  void SetSceneR(GenScene *scene,const sMatrix &base,GenScene *usescene,sInt phase);
  void AddMesh(KKriegerMesh *,const sMatrix &mat,GenScene *usescene);

  void CellSiftDown(sInt n,sInt k);
  void CellConnect();

  sBool OnKey(sU32 key);
  void OnTick(KEnvironment *kenv,sInt slices);
  void AddEvents(KEnvironment *kenv);
  void OnPaint(sMaterialEnv *env);
  void OnOptionsChanged();

  void Panic();
  void ResetRoot(KEnvironment *kenv,KOp *root,sBool firsttime);
  sInt GetNewRoot();
  void Restart();
  void Continue();
  sInt SplashCalc(const sVector &pos,KKriegerCellAdd *cell);
  void GetCamera(sMaterialEnv &);
  void GetPlayer(sMatrix &);

  // sound
  void PlayerSound(sInt sound,sF32 volume=1.0f); // sound at player position with player velocity

  // game

  void MonsterActivate(KKriegerMonster *mon,sBool on);
  void MonsterAI(KKriegerMonster *mon,KEnvironment *kenv);
  void Zones(KEnvironment *kenv);
  void RespawnAt(sInt i);

  // add dynamically managed resources per frame

  void FlushPhysic();
  void AddPart(KKriegerParticle *);
  void AddCons(KKriegerConstraint *);
  void AddDCell(KKriegerCellDynamic *);

  // particles (intern, kkphysic.cpp)

  sInt MoveParticle(KKriegerParticle *part,sBool onlyoldcoll);
  void Physic(sF32 fade);
  void PhysicCons(KKriegerConstraint *cons);
  void PhysicPart(KKriegerParticle *p);
  void PhysicDCell(KKriegerCellDynamic *cell);
  KKriegerCellAdd *FindCell(const sVector &v);

  sBool FindFirstIntersect(const sVector &p0,sVector &p1,KKriegerCellAdd *&cadd,sVector *plane=0);
  sBool FindFirstIntersect(const sVector &d,const sVector &p1,const sVector &p0,KKriegerCellAdd *&cadd,sVector &plane,sF32 &dist,KKriegerParticle *part,KKriegerParticle *hitpart);
  sBool FindSubIntersect(const sVector &d,const sVector &p1,const sVector &p0,KKriegerCellAdd **list,sInt count,sVector &plane,sF32 &dist,KKriegerParticle *part,KKriegerParticle *hitpart);
  sBool FindSubIntersect2(const sVector &d,const sVector &p1,const sVector &p0,KKriegerCell *cell,sVector &plane,sF32 &distresult);
  void CheckZones(const sVector &p0,KKriegerCellAdd *c0,const sVector &p1,KKriegerCellAdd *c1,KKriegerParticle *part);
};

extern sInt KKGameRestartFrames;            // 2004 global 0x14a0984: monsters re-init for 2 frames after Restart()

/****************************************************************************/
/***                                                                      ***/
/***   Operators                                                          ***/
/***                                                                      ***/
/****************************************************************************/

class KObject * __stdcall Init_KKrieger_Para(KOp *op,KEnvironment *kenv);
class KObject * __stdcall Init_KKrieger_Monster(KOp *op);
class KObject * __stdcall Init_KKrieger_Events(KOp *op);
class KObject * __stdcall Init_KKrieger_Respawn(sF323 pos,sInt zone,sF32 dir);
class KObject * __stdcall Init_KKrieger_SplashDamage(sInt hits,sF32 range,sF32 enable);
class KObject * __stdcall Init_KKrieger_MonsterFlags(KOp *op);
void __stdcall Exec_KKrieger_Para(KOp *op,KEnvironment *kenv);
void __stdcall Exec_KKrieger_Monster(KOp *op,KEnvironment *kenv);
void __stdcall Exec_KKrieger_Events(KOp *op,KEnvironment *kenv);
void __stdcall Exec_KKrieger_Respawn(KOp *op,KEnvironment *kenv,sF323 pos,sInt zone,sF32 dir);
void __stdcall Exec_KKrieger_SplashDamage(KOp *op,KEnvironment *kenv,sInt hits,sF32 range,sF32 enable);
void __stdcall Exec_KKrieger_MonsterFlags(KOp *op,KEnvironment *kenv,sInt kill,sInt spawn,sInt flags);

/****************************************************************************/
/***                                                                      ***/
/***   Helpers                                                            ***/
/***                                                                      ***/
/****************************************************************************/


/****************************************************************************/
/****************************************************************************/

#endif
