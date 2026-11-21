// This file is distributed under a BSD license. See LICENSE.txt for details.

#include "kdoc.hpp"
#include "genbitmap.hpp"
#include "genmaterial.hpp"
#include "genmesh.hpp"
#include "genoverlay.hpp"
#include "genscene.hpp"
#include "geneffect.hpp"
#include "kkriegergame.hpp"

 
KHandler KHandlers[] =
{
  // misc
#ifndef KK_SMALL                 // not used by the 2004 data
  0x01, (void *)Init_Misc_Load, (void *)Exec_Misc_Load,             // load
#endif
#ifndef KK_SMALL                 // not used by the 2004 data
  0x02, (void *)Init_Misc_Nop, (void *)Exec_Misc_Nop,              // store
#endif
#ifndef KK_SMALL                 // not used by the 2004 data
  0x03, (void *)Init_Misc_Nop, (void *)Exec_Misc_Nop,              // nop
#endif
  0x05, (void *)Init_Misc_Nop, (void *)Exec_Misc_Time,             // time
  0x06, (void *)Init_Misc_Event, (void *)Exec_Misc_Event,            // event
#ifndef KK_SMALL                 // not used by the 2004 data
  0x07, (void *)Init_Misc_Trigger, (void *)Exec_Misc_Trigger,          // trigger
#endif
  0x08, (void *)Init_Misc_Nop, (void *)Exec_Misc_Delay,            // delay
  0x09, (void *)Init_Misc_Nop, (void *)Exec_Misc_If,               // if
#ifndef KK_SMALL                 // not used by the 2004 data
  0x0a, (void *)Init_Misc_Nop, (void *)Exec_Misc_SetIf,            // setif
#endif
  0x0b, (void *)Init_Misc_Nop, (void *)Exec_Misc_State,            // state
  0x0c, (void *)Init_Misc_Nop, (void *)Exec_Misc_PlaySample,       // play sample
#ifndef KK_SMALL                 // not used by the 2004 data
  0x0d, (void *)Init_Misc_Demo, (void *)Exec_Misc_Demo,             // demo 
#endif
#ifndef KK_SMALL                 // not used by the 2004 data
  0x0e, (void *)Init_Misc_Nop, (void *)Exec_Misc_Menu,             // menu
#endif

  // kkrieger
  0x10, (void *)Init_KKrieger_Para, (void *)Exec_KKrieger_Para,         // KKriegerPara
  0x11, (void *)Init_KKrieger_Monster, (void *)Exec_KKrieger_Monster,      // KKriegerMonster
  0x12, (void *)Init_KKrieger_Events, (void *)Exec_KKrieger_Events,       // KKriegerEvents
  0x13, (void *)Init_KKrieger_Respawn, (void *)Exec_KKrieger_Respawn,
  0x14, (void *)Init_KKrieger_SplashDamage, (void *)Exec_KKrieger_SplashDamage,
#ifndef KK_SMALL                 // not used by the 2004 data
  0x15, (void *)Init_KKrieger_MonsterFlags, (void *)Exec_KKrieger_MonsterFlags,
#endif

  // bitmap
  0x21, (void *)Bitmap_Flat, (void *)Exec_Misc_Nop,              // flat
  0x22, (void *)Bitmap_Perlin, (void *)Exec_Misc_Nop,              // perlin
  0x23, (void *)Bitmap_Color, (void *)Exec_Misc_Nop,              // color
  0x24, (void *)Bitmap_Merge, (void *)Exec_Misc_Nop,              // merge
  0x25, (void *)Bitmap_Format, (void *)Exec_Misc_Nop,              // format
#ifndef KK_SMALL                 // not used by the 2004 data
  0x26, (void *)Bitmap_RenderTarget, (void *)Exec_Misc_Nop,              // render target
#endif
  0x27, (void *)Bitmap_GlowRect, (void *)Exec_Misc_Nop,              // glowrect (old)
#ifndef KK_SMALL                 // not used by the 2004 data
  0x28, (void *)Bitmap_Dots, (void *)Exec_Misc_Nop,              // dots
#endif
  0x29, (void *)Bitmap_Blur, (void *)Exec_Misc_Nop,              // blur
  0x2a, (void *)Bitmap_Mask, (void *)Exec_Misc_Nop,              // mask
  0x2b, (void *)Bitmap_HSCB, (void *)Exec_Misc_Nop,              // hscb
  0x2c, (void *)Bitmap_Rotate, (void *)Exec_Misc_Nop,              // rotate
  0x2d, (void *)Bitmap_Distort, (void *)Exec_Misc_Nop,              // distort
  0x2e, (void *)Bitmap_Normals, (void *)Exec_Misc_Nop,              // normals
#ifndef KK_SMALL                 // not used by the 2004 data
  0x2f, (void *)Bitmap_Light, (void *)Exec_Misc_Nop,              // light
#endif
  0x30, (void *)Bitmap_Bump, (void *)Exec_Misc_Nop,              // bump
  0x31, (void *)Bitmap_Text2004, (void *)Exec_Misc_Nop,              // text
  0x32, (void *)Bitmap_Cell, (void *)Exec_Misc_Nop,              // cell
  0x34, (void *)Bitmap_Gradient, (void *)Exec_Misc_Nop,              // gradient
  0x35, (void *)Bitmap_Range, (void *)Exec_Misc_Nop,              // range
  0x36, (void *)Bitmap_RotateMul, (void *)Exec_Misc_Nop,              // rotatemul
  0x37, (void *)Bitmap_Twirl, (void *)Exec_Misc_Nop,              // twirl
  0x38, (void *)Bitmap_Sharpen, (void *)Exec_Misc_Nop,              // sharpen
  0x39, (void *)Bitmap_GlowRect, (void *)Exec_Misc_Nop,              // glowrect
#ifndef KK_SMALL                 // not used by the 2004 data
  0x3b, (void *)Bitmap_ColorBalance, (void *)Exec_Misc_Nop,              // color balance
#endif

  // effecte
//  0x60, (void *)Init_Effect_Dummy, (void *)Exec_Effect_Dummy,          // dummy-effect
  0x61, (void *)Init_Effect_Print, (void *)Exec_Effect_Print,          // print text/menu
  0x63, (void *)Init_Effect_PartEmitter, (void *)Exec_Effect_PartEmitter,    // particles
  0x64, (void *)Init_Effect_PartSystem, (void *)Exec_Effect_PartSystem,     // particles

  // mesh
  0x81, (void *)Mesh_Cube, (void *)Exec_Misc_Nop,              // cube
  0x82, (void *)Mesh_Cylinder, (void *)Exec_Misc_Nop,              // cylinder
//  0x83, (void *)Mesh_Torus, (void *)Exec_Misc_Nop,              // torus
//  0x84, (void *)Mesh_Sphere, (void *)Exec_Misc_Nop,              // sphere
//  0x85, (void *)Mesh_SelectAll, (void *)Exec_Misc_Nop,              // select all
  0x86, (void *)Mesh_SelectCube, (void *)Exec_Misc_Nop,              // select cube
  0x87, (void *)Mesh_Subdivide, (void *)Exec_Misc_Nop,              // subdivide
  0x88, (void *)Mesh_Transform, (void *)Exec_Misc_Nop,              // transform
  0x89, (void *)Mesh_TransformEx, (void *)Exec_Misc_Nop,              // transformex
#ifndef KK_SMALL                 // not used by the 2004 data
  0x8a, (void *)Mesh_Crease, (void *)Exec_Misc_Nop,              // crease
#endif
//  0x8b, (void *)Mesh_UnCrease, (void *)Exec_Misc_Nop,              // uncrease
  0x8c, (void *)Mesh_Triangulate, (void *)Exec_Misc_Nop,              // triangulate
//  0x8d, (void *)Mesh_Cut, (void *)Exec_Misc_Nop,              // cut
//  0x8e, (void *)Mesh_ExtrudeNormal, (void *)Exec_Misc_Nop,              // extrudenormal
  0x8f, (void *)Mesh_Displace, (void *)Exec_Misc_Nop,              // displace
// bevel ONLY used in full level!
#ifndef KK_SMALL                 // not used by the 2004 data
  0x90, (void *)Mesh_Bevel, (void *)Exec_Misc_Nop,              // bevel
#endif
  0x91, (void *)Mesh_Perlin, (void *)Exec_Misc_Nop,              // perlin
  0x92, (void *)Mesh_Add, (void *)Exec_Misc_Nop,              // add
// deletefaces ONLY used in full level! (and kkrieger-logo)
#ifndef KK_SMALL                 // not used by the 2004 data
  0x93, (void *)Mesh_DeleteFaces, (void *)Exec_Misc_Nop,              // delete faces
#endif
//  0x94, (void *)Mesh_SelectRandom, (void *)Exec_Misc_Nop,              // select random
  0x95, (void *)Mesh_Multiply, (void *)Exec_Misc_Nop,              // multiply
  0x96, (void *)Mesh_MatLink, (void *)Exec_Misc_Nop,              // matlink
//  0x99, (void *)Mesh_BeginRecord, (void *)Exec_Misc_Nop,              // beginrec
  0x9a, (void *)Mesh_Extrude, (void *)Exec_Misc_Nop,              // extrude
  0x9c, (void *)Mesh_CollisionCube, (void *)Exec_Misc_Nop,              // collcube
// grid ONLY used in full level! (and kkrieger-logo)
#ifndef KK_SMALL                 // not used by the 2004 data
  0x9d, (void *)Mesh_Grid, (void *)Exec_Misc_Nop,              // grid
#endif
  0xa0, (void *)Mesh_Bend, (void *)Exec_Misc_Nop,              // bend
//  0xa1, (void *)Mesh_SelectLogic, (void *)Exec_Misc_Nop,              // select logic
//  0xa2, (void *)Mesh_SelectGrow, (void *)Exec_Misc_Nop,              // select grow
//  0xa3, (void *)Mesh_Invert, (void *)Exec_Misc_Nop,              // invert
//  0xa4, (void *)Mesh_SetPivot, (void *)Exec_Misc_Nop,              // set pivot
  0xa5, (void *)Mesh_UVProjection, (void *)Exec_Misc_Nop,              // uvproject
  0xa6, (void *)Mesh_Center, (void *)Exec_Misc_Nop,              // center
  0xa7, (void *)Mesh_AutoCollision, (void *)Exec_Misc_Nop,              // autocoll
#ifndef KK_SMALL                 // not used by the 2004 data
  0xa8, (void *)Mesh_SelectSphere, (void *)Exec_Misc_Nop,              // selectsphere
#endif
//  0xa9, (void *)Mesh_SelectFace, (void *)Exec_Misc_Nop,              // selectface
//  0xaa, (void *)Mesh_SelectAngle, (void *)Exec_Misc_Nop,              // selectangle
  0xab, (void *)Mesh_Bend2, (void *)Exec_Misc_Nop,              // bend 2
//  0xac, (void *)Mesh_SmoothAngle, (void *)Exec_Misc_Nop,              // smangle
  0xad, (void *)Mesh_Color, (void *)Exec_Misc_Nop,              // color
//  0xae, (void *)Mesh_BendS, (void *)Exec_Misc_Nop,              // bend spline
  0xaf, (void *)Mesh_LightSlot, (void *)Exec_Misc_Nop,              // light slot
  0xb0, (void *)Mesh_ShadowEnable, (void *)Exec_Misc_Nop,              // shadowenable
#ifndef KK_SMALL                 // not used by the 2004 data
  0xb3, (void *)Mesh_SingleVert, (void *)Exec_Misc_Nop,              // single vertex
#endif

  // scene
  0xc0, (void *)Init_Scene_Scene, (void *)Exec_Scene_Scene,           // scene
  0xc1, (void *)Init_Scene_Add, (void *)Exec_Scene_Add,             // add
  0xc2, (void *)Init_Scene_Multiply, (void *)Exec_Scene_Multiply,        // multiply
  0xc3, (void *)Init_Scene_Transform, (void *)Exec_Scene_Transform,       // transform
  0xc4, (void *)Init_Scene_Light, (void *)Exec_Scene_Light,           // light
#ifndef KK_SMALL                 // not used by the 2004 data
  0xc5, (void *)Init_Scene_Particles, (void *)Exec_Scene_Particles,       // scene multply particles
#endif
  0xc6, (void *)Init_Scene_Camera, (void *)Exec_Scene_Camera,          // camera

  0xc7, (void *)Init_Scene_Limb, (void *)Exec_Scene_Limb,            // limb
  0xc8, (void *)Init_Scene_Walk, (void *)Exec_Scene_Walk,            // walk
  0xc9, (void *)Init_Scene_Rotate, (void *)Exec_Scene_Rotate,          // rotate
//  0xca, (void *)Init_Scene_Forward, (void *)Exec_Scene_Forward,         // forward
  0xcb, (void *)Init_Scene_Sector, (void *)Exec_Scene_Sector,          // sector
  0xcd, (void *)Init_Scene_Portal, (void *)Exec_Scene_Portal,          // portal
  0xce, (void *)Init_Scene_Physic, (void *)Exec_Scene_Physic,          // physic
  0xce, (void *)Init_Scene_Physic, (void *)Exec_Scene_Physic,          // physic

  // material
  0xd0, (void *)Init_Material_Material, (void *)Exec_Material_Material,     // material
#ifndef KK_SMALL                 // not used by the 2004 data
  0xd1, (void *)Material_Add, (void *)Exec_Misc_Nop,              // add material
#endif
#ifndef KK_SMALL                 // not used by the 2004 data
  0xd2, (void *)Init_Scene_MatHack, (void *)Exec_Scene_MatHack,         // link material for animation
#endif

  // ipp
  0xe0, (void *)Init_Misc_Root2004, (void *)Exec_Misc_Nop,    // 2004 only
#ifndef KK_SMALL                 // not used by the 2004 data
  0xe2, (void *)Init_IPP_Copy, (void *)Exec_IPP_Copy,              // copy
#endif
  0xe3, (void *)Init_IPP_Blur, (void *)Exec_IPP_Blur,              // blur
//  0xe4, (void *)Init_IPP_Crashzoom, (void *)Exec_IPP_Crashzoom,         // crashzoom
//  0xe5, (void *)Init_IPP_Sharpen, (void *)Exec_IPP_Sharpen,           // sharpen
  0xe6, (void *)Init_IPP_Color, (void *)Exec_IPP_Color,             // color
  0xe7, (void *)Init_IPP_Merge, (void *)Exec_IPP_Merge,             // merge
  0xe8, (void *)Init_IPP_Mask, (void *)Exec_IPP_Mask,              // mask
//  0xe9, (void *)Init_IPP_Layer2D, (void *)Exec_IPP_Layer2D,           // layer2d
  0xea, (void *)Init_IPP_Select, (void *)Exec_IPP_Select,            // select
#ifndef KK_SMALL                 // not used by the 2004 data
  0xeb, (void *)Init_IPP_RenderTarget, (void *)Exec_IPP_RenderTarget,      // render target
#endif
  0xf0, (void *)Init_IPP_Viewport, (void *)Exec_IPP_Viewport,          // viewport

  // minmesh
//  0x100, (void *)MinMesh_SingleVert, (void *)Exec_Misc_Nop,              // single vert
//  0x101, (void *)MinMesh_Grid, (void *)Exec_Misc_Nop,              // grid
//  0x102, (void *)MinMesh_Cube, (void *)Exec_Misc_Nop,              // cube
//  0x103, (void *)MinMesh_Torus, (void *)Exec_Misc_Nop,              // torus
//  0x104, (void *)MinMesh_Sphere, (void *)Exec_Misc_Nop,              // sphere
//  0x105, (void *)MinMesh_Cylinder, (void *)Exec_Misc_Nop,              // cylinder
//  0x106, (void *)MinMesh_XSI, (void *)Exec_Misc_Nop,              // xsi

//  0x110, (void *)MinMesh_MatLink, (void *)Exec_Misc_Nop,              // matlink
//  0x111, (void *)MinMesh_Add, (void *)Exec_Misc_Nop,              // add
//  0x112, (void *)MinMesh_SelectAll, (void *)Exec_Misc_Nop,              // select all
//  0x113, (void *)MinMesh_SelectCube, (void *)Exec_Misc_Nop,              // select cube
//  0x114, (void *)MinMesh_DeleteFaces, (void *)Exec_Misc_Nop,              // delete faces
//  0x115, (void *)MinMesh_Invert, (void *)Exec_Misc_Nop,              // invert

//  0x120, (void *)MinMesh_TransformEx, (void *)Exec_Misc_Nop,              // transform
//  0x121, (void *)MinMesh_TransformEx, (void *)Exec_Misc_Nop,              // transform ex
//  0x122, (void *)MinMesh_ExtrudeNormal, (void *)Exec_Misc_Nop,              // extrude normal
//  0x123, (void *)MinMesh_Displace, (void *)Exec_Misc_Nop,              // displace
//  0x124, (void *)MinMesh_Perlin, (void *)Exec_Misc_Nop,              // perlin
//  0x125, (void *)MinMesh_Bend2, (void *)Exec_Misc_Nop,              // bend 2

  // end!
  0,0,0,
};
