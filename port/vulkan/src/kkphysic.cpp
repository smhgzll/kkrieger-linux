// This file is distributed under a BSD license. See LICENSE.txt for details.
//
// linux port: the particle physics of the 2004 release of .kkrieger.
//
// The public werkkzeug3_kkrieger source is a later revision in which this
// code was removed (only commented-out declarations survived, see
// kkriegergame.hpp). Everything here was recovered from the disassembly of
// pno0001.exe (image base 0x800000); the address of the original function is
// given above each one. Particles are points (no radius), moved with verlet
// integration, joined by distance constraints into bodies (player, monsters,
// crates) and collided against the convex cells of the level, sliding along
// up to two planes.

#include "_types.hpp"
#include "kdoc.hpp"
#include "kkriegergame.hpp"
#include <stdio.h>
#include <stdlib.h>

#define SKIN 1e-4f                          // 0x81f380

static sBool KKStuckInSub;                  // 0x14a0980: a ray started inside a sub
sInt KKGameRestartFrames;                   // 0x14a0984

/****************************************************************************/
/***                                                                      ***/
/***   Cells                                                              ***/
/***                                                                      ***/
/****************************************************************************/

// 0x819fea: bit i set when v is outside plane i (plane normals point inside).
// A positive radius enlarges the cell.

sInt KKriegerCell::OutsideMask(const sVector &v,sF32 radius)
{
  sInt i,mask;

  mask = 0;
  for(i=0;i<PlaneCount;i++)
    if(Planes[i].z*v.z+Planes[i].x*v.x+Planes[i].y*v.y+Planes[i].w+radius < 0.0f)
      mask |= 1<<i;
  return mask;
}

// 0x81a047: the ray end p is outside this cell; find where the ray leaves it
// (dist <= 0, a multiple of d measured back from p)

sBool KKriegerCell::IntersectOut(const sVector &p,const sVector &d,sVector &plane,sF32 &dist)
{
  sInt i,bestplane;
  sF32 f,t,best;

  best = 0.0f;
  bestplane = -1;
  for(i=0;i<PlaneCount;i++)
  {
    f = Planes[i].Dot3(p)+Planes[i].w;
    if(f<0.0f)
    {
      t = (-1.0f/Planes[i].Dot3(d))*f;
      if(t<best)
      {
        best = t;
        bestplane = i;
      }
    }
  }
  if(bestplane>=0)
  {
    plane = Planes[bestplane];
    dist = best;
    return sTRUE;
  }
  return sFALSE;
}

// 0x81a0e3: where the ray enters this convex cell (largest entry parameter)

sBool KKriegerCell::IntersectIn(const sVector &p,const sVector &d,sVector &plane,sF32 &dist)
{
  sInt i,bestplane;
  sF32 f,det,t,best;

  best = -1024*1024;
  bestplane = -1;
  for(i=0;i<PlaneCount;i++)
  {
    f = Planes[i].Dot3(p)+Planes[i].w;
    det = Planes[i].Dot3(d);
    if(det>1e-16)
    {
      t = -(f/det);
      if(t>best)
      {
        best = t;
        bestplane = i;
      }
    }
  }
  if(bestplane>=0)
  {
    plane = Planes[bestplane];
    dist = best;
    return sTRUE;
  }
  return sFALSE;
}

// 0x81a7f8

void KKriegerCellDynamic::PrepareDynamic(const sMatrix &mat)
{
  sInt i;
  for(i=0;i<PlaneCount;i++)
    OrigPlanes[i] = Planes[i];
  for(i=0;i<8;i++)
    OrigVertices[i] = Vertices[i];          // (port: ApplyMatrix also moves the vertices)
  Mode |= KCM_UNCONFIRMED;
  Blocked = 0;
  ConfirmedMatrix = mat;
  CurrentMatrix = mat;
  Matrix0 = mat;
  Matrix1 = mat;
  PartBox = 0;
  Monster = 0;
}

/****************************************************************************/
/***                                                                      ***/
/***   Ray casting                                                        ***/
/***                                                                      ***/
/****************************************************************************/

// 0x81a258: ray vs one sub cell. dist is in/out: only a hit nearer to p0
// than the current dist is taken.

sBool KKriegerGame::FindSubIntersect2(const sVector &d,const sVector &p1,const sVector &p0,
                                      KKriegerCell *cell,sVector &plane,sF32 &dist)
{
  sInt m0,m1;
  sVector planei,v;
  sF32 besti;

  if(cell->Mode==KCM_SUB || (cell->Mode==(KCM_SUB|KCM_ONLYMONSTER) && CollisionForMonsterMode))
  {
    m0 = cell->OutsideMask(p0,0);
    m1 = cell->OutsideMask(p1,0);
    if(m0==0)                               // the start point is inside the sub: stuck
    {
      plane.Init(1,0,0,0);
      KKStuckInSub = 1;
      dist = 0;
      return sTRUE;
    }
    if(m0&m1)                               // both outside the same plane
      return sFALSE;
    if(cell->IntersectIn(p1,d,planei,besti))
    {
      if(besti<dist)
      {
        v = p1;
        v.AddScale3(d,besti);
        if(cell->OutsideMask(v,SKIN)==0)    // entry point inside the cell enlarged by 1e-4
        {
          dist = besti;
          plane = planei;
          plane.Neg4();                     // faces out of the sub
          return sTRUE;
        }
      }
    }
  }
  return sFALSE;
}

// 0x81b213: nearest hit among the static subs of the visited adds and the
// dynamic cells. part decides the "player" rule and enables hit cells;
// hitpart (first ray of MoveParticle only) gets Collided bits and Hit().

sBool KKriegerGame::FindSubIntersect(const sVector &d,const sVector &p1,const sVector &p0,
                                     KKriegerCellAdd **list,sInt count,sVector &plane,sF32 &dist,
                                     KKriegerParticle *part,KKriegerParticle *hitpart)
{
  sInt i,j;
  sBool isnotplayer,collided;
  KKriegerCellAdd *cadd;
  KKriegerCell *cell;
  KKriegerCellDynamic *dcell;
  sVector v;

  isnotplayer = !(part && (part->Kind==KPK_PLAYER || part->Kind==KPK_PLAYERAUX));
  dist = SKIN;
  collided = 0;

  for(j=0;j<count;j++)
  {
    cadd = list[j];
    for(i=0;i<cadd->Subs.Count;i++)
    {
      cell = cadd->Subs[i];
      if(cell->Mode==KCM_SUB || (cell->Mode==(KCM_SUB|KCM_ONLYMONSTER) && CollisionForMonsterMode))
      {
        if(isnotplayer && cell->OnlyForShot) // such subs only block the player
          continue;
        if(FindSubIntersect2(d,p1,p0,cell,plane,dist))
        {
          collided = 1;
          if(KKStuckInSub)
            return sTRUE;
        }
      }
    }
  }

  for(i=0;i<DCellUsed;i++)
  {
    dcell = DCellPtr[i];
    if(dcell->Mode!=KCM_SUB)                // excludes KCM_DISABLED, KCM_UNCONFIRMED
      continue;
    if(isnotplayer && dcell->OnlyForShot)
      continue;
    if((dcell->Monster || dcell==&Player.Body.HitCell) && part==0)
      continue;                             // hit boxes only for rays that carry a particle
    if(FindSubIntersect2(d,p1,p0,dcell,plane,dist))
    {
      collided = 1;
      if(KKStuckInSub)
        return sTRUE;
      if(hitpart && (hitpart->ShotEvent==0 || hitpart->ShotEvent->Select==0))
      {
        dcell->Collided |= 1<<hitpart->Kind;  // this is how shots damage monsters (Zones)
        v = p1;
        v.AddScale3(d,dist);
        hitpart->Hit(this,v,plane,0.0f,dcell->Monster!=0);
      }
      // (0x81ab9a, pushing crates, is an empty function in the release)
    }
  }
  return collided;
}

// 0x81b45a: follow the ray end through the connected adds, then check the
// subs. Returns sTRUE when it hit an add wall or a sub; cadd is updated to
// the last add the ray reached. A hit is at p1 + d*dist (dist <= 0).

sBool KKriegerGame::FindFirstIntersect(const sVector &d,const sVector &p1,const sVector &p0,
                                       KKriegerCellAdd *&cadd,sVector &plane,sF32 &dist,
                                       KKriegerParticle *part,KKriegerParticle *hitpart)
{
  KKriegerCellAdd *list[16];
  KKriegerCellAdd *next;
  sInt count,i,j;
  sBool isnotplayer;
  sVector v;
  sF32 dist2;

  list[0] = cadd;
  count = 1;

  while(cadd->IntersectOut(p1,d,plane,dist))  // ray end is outside this add
  {
    isnotplayer = !(part && (part->Kind==KPK_PLAYER || part->Kind==KPK_PLAYERAUX));
    v = p1;
    v.AddScale3(d,dist);                    // where the ray leaves the add
    if(count>=16)
      goto outside;
    for(i=0;i<cadd->Adds.Count;i++)
    {
      next = cadd->Adds[i];
      if(next->OutsideMask(v,0)!=0)
        continue;
      if(!isnotplayer && next->OnlyForShot) // the player never enters such an add
        continue;
      for(j=0;j<count;j++)
        if(list[j]==next)
          goto nextadd;
      list[count++] = cadd;                 // 2004: the add being LEFT is stored
      cadd = next;
      goto again;
nextadd:;
    }
    goto outside;
again:;
  }

  return FindSubIntersect(d,p1,p0,list,count,plane,dist,part,hitpart);

outside:
  if(FindSubIntersect(d,p1,p0,list,count,v,dist2,part,hitpart))
  {
    if(dist2<dist)
    {
      dist = dist2;
      plane = v;
    }
  }
  return sTRUE;
}

// 0x81c852: segment p0 -> p1; on a hit p1 is moved to the hit point

sBool KKriegerGame::FindFirstIntersect(const sVector &p0,sVector &p1,KKriegerCellAdd *&cadd,sVector *plane)
{
  sVector d,pl;
  sF32 dist;

  d.Sub3(p1,p0);
  if(!FindFirstIntersect(d,p1,p0,cadd,pl,dist,0,0))
    return sFALSE;
  p1.AddScale3(d,dist);
  if(plane)
    *plane = pl;
  return sTRUE;
}

// 0x81b15a: zone enter/leave/collided marking for one particle

void KKriegerGame::CheckZones(const sVector &p0,KKriegerCellAdd *c0,const sVector &p1,
                              KKriegerCellAdd *c1,KKriegerParticle *part)
{
  sU32 mask;
  sInt i;
  sBool in0,in1;
  KKriegerCellAdd *cadd;
  KKriegerCell *zone;

  if(part->ShotEvent && part->ShotEvent->Select!=0)
    return;
  mask = 1<<part->Kind;
  cadd = c0;
  for(;;)
  {
    for(i=0;i<cadd->Zones.Count;i++)
    {
      zone = cadd->Zones[i];
      in0 = (zone->OutsideMask(p0,0)==0);
      in1 = (zone->OutsideMask(p1,0)==0);
      if(in0 && !in1) zone->Leave |= mask;
      if(!in0 && in1) zone->Enter |= mask;
      if(in1)         zone->Collided |= mask;
    }
    if(cadd==c1 || c1==0)
      break;
    cadd = c1;
  }
}

/****************************************************************************/
/***                                                                      ***/
/***   Particles                                                          ***/
/***                                                                      ***/
/****************************************************************************/

// 0x81a939

void KKriegerParticle::Init(const sVector &pos,const sVector &speed,KKriegerCellAdd *cell)
{
  sSetMem(this,0,sizeof(*this));
  Kind = 0;
  Cell = cell;
  Pos = pos;
  NewPos = pos;
  UseNewPos = 0;
  VerifyPos = 1;
  OldCollPos = pos;
  OldPos.Sub3(pos,speed);
}

// 0x819d55: displace the whole particle array (Verlet turns it into speed)

void KKriegerParticle::Control(const sVector &v)
{
  KKriegerParticle *p;
  for(p=this;;p++)
  {
    p->Pos.Add3(v);
    if(p->EndMarker)
      break;
  }
}

// 0x81a98d: a shot particle hit something

void KKriegerParticle::Hit(KKriegerGame *game,const sVector &pos,const sVector &v,sF32 dist,sInt hitmonster)
{
  KEvent *ev,*e;
  KOp *op;

  ev = ShotEvent;
  if(ev==0)
    return;

  if(Kind>=KPK_WEAPON0 && Kind<KPK_WEAPON0+8 && ev->Start>0 && ev->Select==0)
  {
    op = game->WeaponExplode[hitmonster?1:0][Kind-KPK_WEAPON0];
    if(op && (hitmonster || ev->ShotTime+10<game->TickCount))  // wall impacts at most every 10 ticks
    {
      ev->Velocity = 5.0f;
      e = new KEvent;
      e->Init();
      e->Op = op;
      e->Translate = pos;
      e->Rotate.x = sFATan2(-v.y,sFSqrt(v.x*v.x+v.z*v.z))*0.15915494f;
      e->Rotate.y = sFATan2(v.x,v.z)*0.15915494f;
      e->Rotate.z = 0;
      e->Rotate.w = 0;
      game->Environment->AddDynamicEvent(e);
    }
  }

  if(Kind<KPK_WEAPON0 || !(game->WeaponFlags[Kind-KPK_WEAPON0]&KWF_REFLECT) || hitmonster)
  {
    ev->Select = 1;                         // shot finished
    ev->Stop();
  }
  ev->ShotTime = game->TickCount;
}

/****************************************************************************/

// 0x81b5bd: move p from OldCollPos to Pos, sliding along up to two planes.
// 0: no collision, 1: collided and slid, 2: blocked (back to OldCollPos, no
// speed). onlyoldcoll: only advance OldCollPos/Cell (pushing by moving cells).

sInt KKriegerGame::MoveParticle(KKriegerParticle *p,sBool onlyoldcoll)
{
  sVector p0,p1,d,v;
  sVector plane1,plane2,plane3;
  sVector pa,pb,e,x,t1,t2,t3;
  sF32 len2,ilen,dist1,dist2,c,f,idet;
  KKriegerCellAdd *cadd;
  sInt result;

  p0 = p->OldCollPos;
  p1 = p->Pos;
  cadd = p->Cell;
  result = 0;
  if(p->SkipCell)
    p->SkipCell->Mode |= KCM_DISABLED;

  d.Sub3(p1,p0);
  len2 = d.Dot3(d);
  if(len2<1e-16)
    goto stay;
  ilen = 1.0f/sFSqrt(len2);
  d.Scale3(ilen);                           // unit direction: dist1 is in world units

  // first ray: the original move

  KKStuckInSub = 0;
  if(!FindFirstIntersect(d,p1,p0,cadd,plane1,dist1,p,p))
    goto done;
  result = 1;
  if(KKStuckInSub)
    goto stay;

  p0 = p1;
  p0.AddScale3(d,dist1);                    // contact point
  if(p->ShotEvent)
    p->Hit(this,p0,plane1,0.0f,0);
  p0.AddScale3(plane1,SKIN);
  f = plane1.Dot3(p1)+plane1.w;
  p1.AddScale3(plane1,SKIN-f);              // project the target onto the plane

  // second ray: slide along plane1

  v.Sub3(p1,p0);
  if(v.Dot3(v)>1e-16)
    d.Scale3(v,ilen);
  if(!FindFirstIntersect(d,p1,p0,cadd,plane2,dist2,p,0))
    goto done;
  if(KKStuckInSub)
    goto stay;

  c = plane1.Dot3(plane2);
  p0 = p1;
  p0.AddScale3(d,dist2);                    // second contact point

  if(c<-0.9f)                               // planes almost opposite (narrow gap)
  {
    p->OldPos = p->OldCollPos;
    p->Pos = p->OldCollPos;
    p1 = p->OldCollPos;
  }
  else if(c>SKIN)                           // acute: slide along plane2 only
  {
    p0.AddScale3(plane2,SKIN);
    f = plane2.Dot3(p1)+plane2.w;
    p1.AddScale3(plane2,SKIN-f);
  }
  else                                      // crease: move along the edge of both planes
  {
    pa = plane1; pa.w -= SKIN;
    pb = plane2; pb.w -= SKIN;
    e.Cross3(plane1,plane2);
    e.w = 0;
    x.Init(0,0,0,0);
    t1.Cross3(pb,e);  x.AddScale3(t1,-pa.w);
    t2.Cross3(e,pa);  x.AddScale3(t2,-pb.w);
    t3.Cross3(pa,pb);
    idet = 1.0f/( e.y*pb.x*pa.z + e.x*pb.z*pa.y + e.z*pb.y*pa.x
                - e.y*pb.z*pa.x - pb.x*pa.y*e.z - pa.z*e.x*pb.y );
    f = e.Dot3(p1);
    p1 = x;
    p1.AddScale3(t3,f);
    p1.Scale3(idet);
    f = e.Dot3(p0);
    p0 = x;
    p0.AddScale3(t3,f);
    p0.Scale3(idet);
  }

  // third ray: the new move must be free, otherwise give up

  v.Sub3(p1,p0);
  if(v.Dot3(v)>1e-16)
    d.Scale3(v,ilen);
  d.Scale3(ilen);
  if(FindFirstIntersect(d,p1,p0,cadd,plane3,dist2,p,0))
    goto stay;

done:
  if(p->Kind!=0)
    CheckZones(p->OldCollPos,p->Cell,p1,cadd,p);
  p->OldCollPos = p1;
  p->Cell = cadd;
  if(!onlyoldcoll)
    p->Pos = p1;
  if(p->SkipCell)
    p->SkipCell->Mode &= ~KCM_DISABLED;
  return result;

stay:
  if(p->Kind!=0)
    CheckZones(p->OldCollPos,p->Cell,p1,cadd,p);
  if(!onlyoldcoll)
  {
    p->OldPos = p->OldCollPos;
    p->Pos = p->OldCollPos;
  }
  if(p->SkipCell)
    p->SkipCell->Mode &= ~KCM_DISABLED;
  return 2;
}

// 0x819f7c: square-root free stick constraint (masses ignored)

void KKriegerGame::PhysicCons(KKriegerConstraint *c)
{
  sVector v;
  sF32 dd,f;

  v.Sub3(c->PartB->Pos,c->PartA->Pos);
  dd = c->Dist*c->Dist;
  f = dd/(dd+v.Dot3(v)) - 0.5f;
  v.Scale3(f);
  c->PartB->Pos.Add3(v);
  c->PartA->Pos.Sub3(v);
}

// 0x81c341: verlet step + collision for one particle

void KKriegerGame::PhysicPart(KKriegerParticle *p)
{
  sF32 gravity,d,sum;
  sVector n;
  sInt i;
  KKriegerCellAdd *cell;

  if(p->VerifyPos)                          // new particle: make sure Cell contains OldCollPos
  {
    if(p->Cell==0 || p->Cell->OutsideMask(p->OldCollPos,0)!=0)
    {
      cell = FindCell(p->OldCollPos);
      if(cell==0)
        return;
      p->Cell = cell;
    }
    p->VerifyPos = 0;
  }
  if(p->Cell==0)
    return;

  gravity = Gravity;
  switch(p->Kind)
  {
  case KPK_PLAYER:
  case KPK_MONSTER:
    // "flat body": pull the y of the 5 body particles towards their mean
    sum = 0;
    for(i=0;i<5;i++)
      sum += p[i].Pos.y;
    sum = sum*0.2f*0.25f;
    for(i=0;i<5;i++)
      p[i].Pos.y = p[i].Pos.y*0.75f + sum;
    // fall through
  case KPK_PLAYERAUX:
  case KPK_MONSTERAUX:
    gravity = GravityPlayer;                // monsters use the player's values too
    if(FlyMode)
      gravity = 0;
    p->Damp = DampPlayerGround;
    if(!OnGround)
      p->Damp = DampPlayerAir;
    break;
  }

  d = 1.0f-p->Damp;
  p->Damp = 0;
  n.x = d*p->Pos.x + (p->Pos.x - d*p->OldPos.x);
  n.y = (d*p->Pos.y - gravity) + (p->Pos.y - d*p->OldPos.y);
  n.z = d*p->Pos.z + (p->Pos.z - d*p->OldPos.z);
  n.w = 1.0f;
  p->OldPos = p->Pos;
  p->Pos = n;

  if(MoveParticle(p,0))
  {
    p->Damp = 0.1f;
    p->OldPos.y += gravity;                 // cancel this step's gravity in the velocity
  }
}

// 0x81c4c4: try to move a dynamic cell to CurrentMatrix, pushing particles
// out of it; if one can not be pushed, the cell stays and is Blocked.

void KKriegerGame::PhysicDCell(KKriegerCellDynamic *cell)
{
  static KKriegerCellDynamic tmp;
  sMatrix inv,delta;
  sVector pos,moved,dir,plane,save;
  sF32 len2,dist;
  sBool blocked;
  sInt i;
  KKriegerParticle *p;

  if(cell->PartBox)
    cell->PartBox->GetMatrix(cell->CurrentMatrix);
  tmp = *cell;
  tmp.ApplyMatrix(tmp.CurrentMatrix);
  inv = tmp.ConfirmedMatrix;
  inv.InvCheap4();
  delta.Mul4(inv,tmp.CurrentMatrix);

  blocked = 0;
  for(i=0;i<PartUsed;i++)
  {
    for(p=PartPtr[i];;p++)
    {
      pos = p->Pos;
      if((cell->Monster==0 || (p->Kind>=KPK_WEAPON0 && p->Kind<KPK_WEAPON0+8))
        && p->SkipCell!=cell
        && tmp.OutsideMask(pos,0)==0)       // particle is inside the moved cell
      {
        moved = pos;
        moved.w = 1;
        moved.Rotate4(delta);               // where the cell carries this point
        dir.Sub3(pos,moved);
        len2 = dir.z*dir.z + dir.y*dir.y + dir.x*dir.x;
        if(len2<1e-16)
        {
          blocked = 1;
        }
        else
        {
          dir.Scale3(1.0f/sFSqrt(len2));
          if(!tmp.IntersectIn(pos,dir,plane,dist))
            blocked = 1;
          else
          {
            pos.AddScale3(dir,dist);        // pushed along the cell motion
            pos.AddScale3(plane,-SKIN);
            pos.w = 1.0f;
            save = p->Pos;
            p->Pos = pos;
            if(MoveParticle(p,1))           // only OldCollPos/Cell move
              blocked = 1;
            p->Pos = save;
          }
        }
      }
      if(p->EndMarker)
        break;
    }
  }

  if(!blocked)
  {
    cell->Mode &= ~KCM_UNCONFIRMED;
    cell->ConfirmedMatrix = cell->CurrentMatrix;
    cell->Blocked = 0;
    cell->ApplyMatrix(cell->ConfirmedMatrix);
  }
  else
  {
    cell->Blocked = 1;
  }
}

// 0x81c728: one 10ms physics step

void KKriegerGame::Physic(sF32 fade)
{
  sInt i;
  KKriegerConstraint *c;
  KKriegerParticle *p;
  KKriegerCellDynamic *cell;

  for(i=0;i<ConsUsed;i++)
    for(c=ConsPtr[i];;c++)
    {
      PhysicCons(c);
      if(c->EndMarker) break;
    }

  for(i=0;i<PartUsed;i++)
    for(p=PartPtr[i];;p++)
    {
      PhysicPart(p);
      if(p->EndMarker) break;
    }

  for(i=0;i<DCellUsed;i++)
  {
    cell = DCellPtr[i];
    cell->CurrentMatrix.Lin4(cell->Matrix0,cell->Matrix1,fade);
    PhysicDCell(cell);
  }

  for(i=0;i<PartUsed;i++)
    for(p=PartPtr[i];;p++)
    {
      p->Pos.Add3(p->Force);
      p->Force.Init(0,0,0,0);
      if(p->EndMarker) break;
    }
}

/****************************************************************************/
/***                                                                      ***/
/***   Registration (rebuilt every frame by the op tree)                  ***/
/***                                                                      ***/
/****************************************************************************/

void KKriegerGame::AddPart(KKriegerParticle *p)                 // 0x819f28
{
  if(PartUsed<KKRIEGER_MAXPARTICLE)
    PartPtr[PartUsed++] = p;
}

void KKriegerGame::AddCons(KKriegerConstraint *c)               // 0x819f42
{
  if(ConsUsed<KKRIEGER_MAXCONSTRAINT)
    ConsPtr[ConsUsed++] = c;
}

void KKriegerGame::AddDCell(KKriegerCellDynamic *d)             // 0x819f5f
{
  if(DCellUsed<KKRIEGER_MAXDCELL)
    DCellPtr[DCellUsed++] = d;
}

// 0x81b0f1: called before the op tree runs

void KKriegerGame::FlushPhysic()
{
  PartUsed = 0;
  ConsUsed = 0;
  DCellUsed = 0;
  Monsters.Count = 0;
  Player.Body.Add(this);
}

/****************************************************************************/
/***                                                                      ***/
/***   Bodies and boxes                                                   ***/
/***                                                                      ***/
/****************************************************************************/

static const sS8 BodyPartOffset[5][3] =     // 0x81fdc0
{ { 0,0, 0},{-1,0, 0},{ 0,0,-1},{ 1,0, 0},{ 0,0, 1} };
static const sU8 BodyConsPair[10][2] =      // 0x81fdac
{ {0,1},{0,2},{0,3},{0,4},{1,2},{2,3},{3,4},{4,1},{1,3},{2,4} };

// 0x81c9c1: kpk = KPK_PLAYER (SetPlayer) or KPK_MONSTER

void KKriegerBody::Init(const sVector &pos,KKriegerCellAdd *cell,sInt kpk)
{
  sVector s,zero,v;
  sMatrix m;
  sInt i;

  s.Init(0.5f,0.25f,0.5f,0);
  zero.Init(0,0,0,0);
  for(i=0;i<5;i++)
  {
    v.Init(BodyPartOffset[i][0],BodyPartOffset[i][1],BodyPartOffset[i][2],0);
    v.Mul3(s);
    v.Add3(pos);
    v.w = 0;
    Part[i].Init(v,zero,cell);
    Part[i].Kind = kpk+1;
    Part[i].OldCollPos = pos;               // all start "collision free" at the centre
    Part[i].Mass = 1.0f;
    Part[i].SkipCell = &HitCell;            // never collide with the own hit box
  }
  Part[0].Kind = kpk;
  Part[4].EndMarker = 1;

  for(i=0;i<10;i++)
  {
    Cons[i].EndMarker = 0;
    Cons[i].Next = 0;
    Cons[i].PartA = &Part[BodyConsPair[i][0]];
    Cons[i].PartB = &Part[BodyConsPair[i][1]];
    v.Sub3(Cons[i].PartA->Pos,Cons[i].PartB->Pos);
    Cons[i].Dist = v.Abs3();
  }
  Cons[9].EndMarker = 1;

  m.Init();
  v.Init(0.5f,1.5f,0.5f,0);
  HitCell.Init(m,v,KCM_SUB);
  m.Init();
  m.l = pos;
  m.l.y += 0.85f;
  m.l.w = 1.0f;
  HitCell.PrepareDynamic(m);
}

// 0x81ae0f

void KKriegerBody::Add(KKriegerGame *game)
{
  game->AddPart(&Part[0]);
  game->AddCons(&Cons[0]);
  game->AddDCell(&HitCell);
}

static const sS8 PartBoxCorner[8][3] =      // 0x81fd80
{
  {-1,-1,-1},{-1, 1,-1},{ 1, 1,-1},{ 1,-1,-1},
  {-1,-1, 1},{-1, 1, 1},{ 1, 1, 1},{ 1,-1, 1},
};
static const sU8 PartBoxCons[16][2] =       // 0x81fd60: 12 edges + 4 space diagonals
{
  {0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},
  {0,4},{1,5},{2,6},{3,7},{0,6},{1,7},{2,4},{3,5},
};

// 0x81aaa4

void KKriegerPartBox::Init(const sMatrix &mat,const sVector &scale,const sVector &speed,KKriegerCellAdd *cell)
{
  sVector v;
  sInt i;

  for(i=0;i<8;i++)
  {
    v.Init(PartBoxCorner[i][0],PartBoxCorner[i][1],PartBoxCorner[i][2],0);
    v.Scale3(0.5f);
    v.Mul3(scale);
    v.w = 1;
    v.Rotate34(mat);
    Part[i].Init(v,speed,cell);
  }
  Part[7].EndMarker = 1;

  for(i=0;i<16;i++)
  {
    Cons[i].EndMarker = 0;
    Cons[i].Next = 0;
    Cons[i].PartA = &Part[PartBoxCons[i][0]];
    Cons[i].PartB = &Part[PartBoxCons[i][1]];
    v.Sub3(Cons[i].PartA->Pos,Cons[i].PartB->Pos);
    Cons[i].Dist = v.Abs3();
  }
  Cons[15].EndMarker = 1;
}

// 0x81ab9d

void KKriegerPartBox::Register(KKriegerGame *game)
{
  game->AddPart(&Part[0]);
  game->AddCons(&Cons[0]);
}

// 0x81abbd: frame from the 8 particles (axes not re-orthogonalised)

void KKriegerPartBox::GetMatrix(sMatrix &mat)
{
  sMatrix m;
  sVector p[8],d;
  sInt i;

  m.i.Init(0,0,0,0);
  m.j.Init(0,0,0,0);
  m.k.Init(0,0,0,0);
  m.l.Init(0,0,0,1);
  for(i=0;i<8;i++)
  {
    p[i] = Part[i].Pos;
    m.l.Add3(p[i]);
  }
  d.Sub3(p[3],p[0]); m.i.Add3(d);
  d.Sub3(p[2],p[1]); m.i.Add3(d);
  d.Sub3(p[7],p[4]); m.i.Add3(d);
  d.Sub3(p[6],p[5]); m.i.Add3(d);
  d.Sub3(p[1],p[0]); m.j.Add3(d);
  d.Sub3(p[2],p[3]); m.j.Add3(d);
  d.Sub3(p[5],p[4]); m.j.Add3(d);
  d.Sub3(p[6],p[7]); m.j.Add3(d);
  d.Sub3(p[4],p[0]); m.k.Add3(d);
  d.Sub3(p[5],p[1]); m.k.Add3(d);
  d.Sub3(p[6],p[2]); m.k.Add3(d);
  d.Sub3(p[7],p[3]); m.k.Add3(d);
  m.i.Unit3();
  m.j.Unit3();
  m.k.Unit3();
  m.l.Scale3(0.125f);
  mat = m;
}

/****************************************************************************/
/***                                                                      ***/
/***   Monsters                                                           ***/
/***                                                                      ***/
/****************************************************************************/

// 0x81c2e4

void KKriegerGame::MonsterActivate(KKriegerMonster *mon,sBool on)
{
  KKriegerCellAdd *cell;
  sInt i;

  if(on && mon->Active==0)
  {
    cell = FindCell(mon->Body.Part[0].Pos);
    if(cell)                                // stays inactive when outside all cells
    {
      mon->Active = on;
      for(i=0;i<5;i++)
        mon->Body.Part[i].Cell = cell;
    }
  }
  else
  {
    mon->Active = on;
  }
}

// 0x81c951

void KKriegerMonster::Hit(sInt hits,KKriegerGame *game)
{
  if(Life>0)
  {
    game->MonsterActivate(this,1);
    if(hits>Armor)
      Life -= (hits-Armor)+(Armor/4);
    else
      Life -= hits/4;
    if(Life<=0)
    {
      Life = 0;
      if(KillSwitch>0)
        game->Switches[KillSwitch]++;
    }
  }
}

// 0x81d33e: once per tick for every monster registered this frame

void KKriegerGame::MonsterAI(KKriegerMonster *mon,KEnvironment *kenv)
{
  sVector pos,delta,p0,p1,move,down,plane;
  sF32 dist,f,h,hd;
  KKriegerCellAdd *cell;
  KEvent *ev;

  if(mon->Life<=0)
    return;

  mon->Matrix = mon->Event.ReturnMatrix;    // output of the Scene_Walk op in the event graph

  pos = mon->Body.Part[0].Pos;
  delta.Sub3(pos,PlayerPos);
  delta.y = 0;
  dist = delta.UnitAbs3();                  // horizontal distance; delta = unit dir player->monster

  // notice / forget the player (line of sight at +0.5)

  p0 = PlayerPos;  p0.y += 0.5f;
  p1 = pos;        p1.y += 0.5f;
  cell = PlayerCell;
  if(!mon->Active)
  {
    if(dist<mon->NoticeRadius && cell && !FindFirstIntersect(p0,p1,cell,0))
      MonsterActivate(mon,1);
  }
  if(mon->Active)
  {
    p1 = pos;        p1.y += 0.5f;
    cell = PlayerCell;
    if(dist>mon->NoticeRadius && cell && FindFirstIntersect(p0,p1,cell,0))
      MonsterActivate(mon,0);
  }

  if(mon->Active)
  {
    mon->MeeleeTimer += 0.01f/mon->MeeleeTime;
    if(mon->MeeleeTimer>=1.0f) mon->MeeleeTimer = 1.0f;
    mon->RangedTimer += 0.01f/mon->RangedTime;
    if(mon->RangedTimer>=1.0f) mon->RangedTimer = 1.0f;

    if(dist<1.5f)
    {
      if(mon->RangedTimer==1.0f && mon->MeeleeTimer==1.0f && mon->MeeleeHits>0)
      {
        mon->MeeleeTimer = 0;
        Player.Hit(mon->MeeleeHits);
      }
    }
    else
    {
      if(mon->RangedTimer==1.0f && mon->MeeleeTimer==1.0f && mon->RangedHits>0 && mon->ShotOp)
      {
        mon->RangedTimer = 0;
        p0 = PlayerPos;      p0.y += 1.0f;
        p1 = mon->Matrix.l;  p1.y += 1.0f;
        cell = PlayerCell;
        if(cell && !FindFirstIntersect(p0,p1,cell,0))
        {
          ev = new KEvent;
          ev->Init();
          ev->Rotate = mon->Event.Rotate;   // heading from the previous tick (turns)
          ev->Translate = mon->Event.Translate;
          ev->Op = mon->ShotOp;
          ev->Monster = mon;
          kenv->AddDynamicEvent(ev);
        }
      }
    }

    // walk towards / away from the player

    if(dist<mon->ChargeRadius)
      f = dist-mon->MinRadius;
    else
      f = dist-mon->WaitRadius;
    if(f>=mon->Speed) f = mon->Speed;
    else if(f<=-mon->Speed) f = -mon->Speed;
    move.Scale3(delta,-f);
    move.w = 0;

    // ground spring, same as the player

    h = GravityPlayer+StairHeight;
    p0 = mon->Body.Part[0].Pos;
    p1 = p0; p1.y -= h;
    cell = mon->Body.Part[0].Cell;
    if(cell)
    {
      mon->Body.HitCell.Mode |= KCM_DISABLED;
      down.Init(0,-1.0f,0,0);
      if(FindFirstIntersect(down,p1,p0,cell,plane,hd,0,0))
        h += hd;                            // hd<=0 -> h = distance to the ground
      mon->Body.HitCell.Mode &= ~KCM_DISABLED;
    }
    if(GravityPlayer+StairHeight>h)
      move.y += ((StairHeight-GravityPlayer)-h)*DampPlayerHeight+GravityPlayer;

    mon->Body.MoveDelta(move);
  }

  // event variables for painting (also for inactive monsters)

  mon->Event.Translate = mon->Body.Part[0].Pos;
  mon->Event.Translate.w = 0;
  mon->Event.Rotate.x = 0;
  mon->Event.Rotate.y = sFATan2(-delta.x,-delta.z)*0.15915494f;
  mon->Event.Rotate.z = 0;
  mon->Event.Rotate.w = 0;
  mon->Event.Scale.x = mon->MeeleeTimer-0.5f;
  if(mon->Event.Scale.x<0) mon->Event.Scale.x+=1.0f;
  mon->Event.Scale.y = mon->RangedTimer-0.5f;
  if(mon->Event.Scale.y<0) mon->Event.Scale.y+=1.0f;
  mon->Event.CullDist = 35;
  mon->Event.Scale.z = 1.0f*mon->Life/mon->LifeMax;
}
