#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
// This file is distributed under a BSD license. See LICENSE.txt for details.

#include "genmaterial.hpp"
#include "genmesh.hpp"
#include "genoverlay.hpp"
#include "engine.hpp"
#include "_start.hpp"
#include "material11.hpp"
#include "material20.hpp"
#include "rtmanager.hpp"

#ifdef KK_SMALL                 // the 2004 data never fails one (KK_HASHOPS)
#define SCRIPTVERIFY(x) {}
#else
#define SCRIPTVERIFY(x) {if(!(x)) return 0;}
#endif
#define REALMAT 1 // 1 for multipass texturing, 0 for fat shader

/****************************************************************************/

class Material11Insert : public EngMaterialInsert
{
public:
  sInt GetPriority()
  {
    return 0x10;
  }

  void BeforeUsage(sInt pass,sInt usage,const EngLight *light)
  {
    switch(usage)
    {
    case ENGU_POSTLIGHT:
      sSystem->SetScissor(0);
      break;
    }
  }

  void AfterUsage(sInt pass,sInt usage,const EngLight *light)
  {
    switch(usage)
    {
    case ENGU_BASE:
      if(GenOverlayManager->CurrentShader >= sPS_11)
      {
        GenOverlayManager->FXQuad(GENOVER_CLRDESTALPHA);
        
      }

      Engine->ApplyViewProject();
      break;

    case ENGU_SHADOW:
      sMaterial11::SetShadowStates(0);
      break;

    case ENGU_LIGHT:
      // clear stencil after each light
      sSystem->Clear(sVCF_STENCIL);
      sSystem->SetScissor(0);
      break;

    case ENGU_POSTLIGHT:
      // add specular
      if(GenOverlayManager->CurrentShader >= sPS_11)
      {
        GenOverlayManager->FXQuad(GENOVER_ADDDESTALPHA);
        Engine->ApplyViewProject();
      }
      break;
    }
  }
};

class Material20Insert : public EngMaterialInsert
{
public:
  sInt GetPriority()
  {
    return 0x20;
  }

  void BeforeUsage(sInt pass,sInt usage,const EngLight *light)
  {
  }

  void AfterUsage(sInt pass,sInt usage,const EngLight *light)
  {
    switch(usage)
    {
    case ENGU_PRELIGHT:
      // copy render (=texture pass) to render target, then clear
#if REALMAT
      RenderTargetManager->GrabToTarget(0x00010000);
#endif
      /*GenOverlayManager->FXQuad(GENOVER_MASKEDCLEAR);
      Engine->ApplyViewProject();*/
      break;

    case ENGU_SHADOW:
      sMaterial11::SetShadowStates(0);
      break;

    case ENGU_LIGHT:
      sSystem->Clear(sVCF_STENCIL);
      sSystem->SetScissor(0);
      break;
    }
  }
};

/****************************************************************************/
/****************************************************************************/

GenMaterial::GenMaterial()
{
  ClassId = KC_MATERIAL;
  Passes.Init();
  Insert = 0;
}

GenMaterial::~GenMaterial()
{
  for(sInt i=0;i<Passes.Count;i++)
    Passes[i].Mtrl->Release();

  Passes.Exit();
}

void GenMaterial::Copy(KObject *obj)
{
#ifndef KK_SMALL   // never called (materials are not copied on write)
  sFatal("can not copy GenMaterial!");
#endif
}

KObject *GenMaterial::Copy()
{
  GenMaterial *mtrl;
  mtrl = new GenMaterial;
  mtrl->Copy(this);
  return mtrl;
}

void GenMaterial::AddPass(sMaterial *mtrl,sInt use,sInt program,sInt pass,sF32 size,sF32 aspect)
{
  GenMaterialPass *ps = Passes.Add();

  ps->Mtrl = mtrl;
  ps->Usage = use;
  ps->Program = program;
  ps->Pass = pass;
  ps->Size = size;
  ps->Aspect = aspect;
}

/****************************************************************************/
/****************************************************************************/

struct MultiPara
{
  sU32 MultiFlags;          // 48
  sU32 RenderPass;          // 49
  sU32 ShaderMask;          // 50
  sF32 MultiSpecPower;      // 51
  sU32 MultiDiffuse;        // 52
  sU32 MultiAmbient;        // 53
  sInt VSOps,PSOps;         // 54,55
  sU32 MultiTFlags[4];      // 56..59
  sF32 MultiTScale[4];      // 60..63
};

GenMaterial * __stdcall Init_Material_Material(KOp *op)
{
  GenMaterial *gm;
  sInt texhandle[8];
  GenBitmap *texbitmap[8];
  sMaterial11 *info,*base;
  GenMaterialPass *pass;
  MultiPara *multi;
  static Material11Insert insert;
  sInt i;

// check texture handles

  for(i=0;i<8;i++)
  {
    texhandle[i] = sINVALID;
    texbitmap[i] = 0;
    if(op->GetLink(i) && op->GetLink(i)->Cache->ClassId==KC_BITMAP)
    {
      texbitmap[i] = (GenBitmap *) op->GetLink(i)->Cache;
      if(texbitmap[i]->Texture==sINVALID)
        texbitmap[i]->MakeTexture(texbitmap[i]->Format);
      texhandle[i] = texbitmap[i]->Texture;
    }
  }

  gm = new GenMaterial;

  base = new sMaterial11;
  base->ShaderLevel = sMin(GenOverlayManager->CurrentShader,sPS_11);
  sCopyMem(&base->BaseFlags,op->GetAnimPtrU(0),48*4);
  multi = (MultiPara *)(op->GetAnimPtrU(48));

  if(GenOverlayManager->CurrentShader>=sPS_11)
  {
    if((multi->MultiFlags&0x1e)==0)
    {
      pass = gm->Passes.Add();
      pass->Mtrl = info = new sMaterial11;

      info->CopyFrom(base);
      pass->Program = MPP_STATIC;
      pass->Pass = multi->RenderPass;
      pass->Size = pass->Aspect = 1.0f;
      info->SetTex(0,texhandle[0]);
      info->SetTex(1,texhandle[1]);
      info->SetTex(2,texhandle[2]);
      info->SetTex(3,texhandle[3]);

#ifndef KK_SMALL   // no 2004 material sets a finalizer (sprites/thick lines)
      if(multi->MultiFlags & 0x30000) // finalizer set
      {
        info->BaseFlags |= sMBF_NONORMAL;
        pass->Size = multi->MultiTScale[0];
        pass->Aspect = multi->MultiTScale[2];

        switch((multi->MultiFlags & 0x30000) >> 16)
        {
        case 1: pass->Program = MPP_SPRITES;    break;
        case 2: pass->Program = MPP_THICKLINES; break;
        }
      }
#endif

      sInt phaseInsert = (multi->MultiFlags >> 20) & 0xf;
      if(phaseInsert == 0) // default
        pass->Usage = ENGU_OTHER;
      else
        pass->Usage = phaseInsert - 1;
    }
    else
    {
      if(multi->MultiFlags & 0x1e)                 // base phase
      {
        info = new sMaterial11;
        info->ShaderLevel = base->ShaderLevel;

        info->BaseFlags = sMBF_ZON|sMBF_NONORMAL/*|sMBF_ZONLY*/;
        info->BaseFlags |= base->BaseFlags & sMBF_DOUBLESIDED;
        info->Color[0] = (multi->MultiFlags & 2) ? multi->MultiAmbient : 0x00ffffff;
        info->Combiner[sMCS_COLOR0] = sMCOA_SET;
        info->Combiner[sMCS_VERTEX] = sMCOA_ADD;
        info->AlphaCombiner = sMCA_ZERO;

        if(multi->MultiFlags&0x0400)               // alpha test
        {
          info->SetTex(0,texhandle[0]);
          info->TFlags[0] = base->TFlags[0];
          info->TScale[0] = base->TScale[0];
          info->AlphaCombiner = sMCA_TEX0;
          info->BaseFlags |= sMBF_ALPHATEST;
        }
        
        gm->AddPass(info,ENGU_BASE,MPP_STATIC,multi->RenderPass);
      }

      if(multi->MultiFlags & 0x02)                 // light phase
      {
        info = new sMaterial11;
        //info->ShaderLevel = sPS_20;
        info->ShaderLevel = base->ShaderLevel;

        info->BaseFlags = sMBF_ZREAD|sMBF_ZEQUAL|sMBF_STENCILTEST;
        info->BaseFlags |= base->BaseFlags & sMBF_DOUBLESIDED;
        if(multi->MultiFlags & 0x4000) // smooth light
          info->BaseFlags |= sMBF_BLENDSMOOTH;
        else
          info->BaseFlags |= sMBF_BLENDADD;
        info->LightFlags = sMLF_BUMPX;
        info->SpecPower = multi->MultiSpecPower;
        info->Color[0] = multi->MultiDiffuse;
        info->Combiner[sMCS_LIGHT] = sMCOA_SET;
        info->Combiner[sMCS_COLOR0] = sMCOA_MUL;
        info->AlphaCombiner = sMCA_ZERO;
        sCopyMem(info->SRT1,base->SRT1,(9+5)*4);

        if(texhandle[4]!=sINVALID)
        {
          info->SetTex(1,texhandle[4]);
          info->TFlags[1] = multi->MultiTFlags[0];
          info->TScale[1] = multi->MultiTScale[0];
        }

        if(!(multi->MultiFlags & 0x0200)) // no specular?
          info->SpecialFlags |= sMSF_NOSPECULAR;
          //info->Color[0] &= 0x00ffffff; // mask out specular color
        else if(multi->MultiFlags & 0x2000) // specularity map
          info->SpecialFlags |= sMSF_SPECMAP;

        gm->AddPass(info,ENGU_LIGHT,MPP_STATIC,multi->RenderPass);
      }
   
      if(multi->MultiFlags & 0x04)                 // shadow phase
      {
        info = new sMaterial11;
        info->ShaderLevel = base->ShaderLevel;

        info->BaseFlags = sMBF_ZREAD|sMBF_SHADOWMASK|sMBF_ZONLY|sMBF_NOTEXTURE|sMBF_NONORMAL;

        /*info->BaseFlags |= sMBF_BLENDADD|sMBF_DOUBLESIDED;
        info->BaseFlags &= ~sMBF_ZONLY;
        info->Color[0] = 0xff0c000c;
        info->AlphaCombiner = sMCA_ZERO;*/

        info->Combiner[sMCS_COLOR0] = sMCOA_SET;
        gm->AddPass(info,ENGU_SHADOW,MPP_SHADOW,multi->RenderPass);
      }

      if(multi->MultiFlags & 0x08)                 // texture phase
      {
        info = new sMaterial11;
        info->CopyFrom(base);

        info->BaseFlags = sMBF_BLENDMUL2|sMBF_ZREAD|sMBF_ZEQUAL;
        info->SetTex(0,texhandle[0]);
        info->SetTex(1,texhandle[1]);
        info->SetTex(2,texhandle[2]);
        info->SetTex(3,texhandle[3]);
        info->AlphaCombiner = sMCA_HALF;
        gm->AddPass(info,ENGU_POSTLIGHT,MPP_STATIC,multi->RenderPass);
      }

      if(multi->MultiFlags & 0x10)                 // envi phase
      {
        info = new sMaterial11;
        info->ShaderLevel = base->ShaderLevel;
        info->BaseFlags = (multi->MultiFlags & 0x8000 ? sMBF_BLENDOFF : sMBF_BLENDADD)|sMBF_ZREAD|sMBF_ZEQUAL;
        info->SpecialFlags = (multi->MultiFlags&0x100)?sMSF_ENVISPHERE:sMSF_ENVIREFLECT;
        info->SetTex(2,texhandle[6]);
        info->Color[2] = multi->MultiAmbient;
        info->TFlags[2] = multi->MultiTFlags[2];
        info->TScale[2] = multi->MultiTScale[2];
        info->Combiner[sMCS_TEX2] = sMCOA_SET;
        sCopyMem(info->SRT1,base->SRT1,(9+5)*4);

        if(multi->MultiFlags & 0x4000) // env alpha mask
        {
          info->SetTex(0,texhandle[0]);
          info->TFlags[0] = base->TFlags[0];
          info->TScale[0] = base->TScale[0];
          info->Combiner[sMCS_TEX2] |= sMCA_TEX0;
        }
        
        gm->AddPass(info,ENGU_POSTLIGHT2,MPP_STATIC,multi->RenderPass);
      }

      gm->Insert = &insert;
    }
  }

  for(i=0;i<gm->Passes.Count;i++)
  {
    info = (sMaterial11 *) gm->Passes[i].Mtrl;
    if(!info->Compile())
    {
      info->Reset();
      info->Color[0] = 0xffff2020;
      info->Combiner[sMCS_COLOR0] = sMCOA_SET;
      sBool ok = info->Compile();
      sVERIFY(ok);
    }
  }

  sRelease(base);

  for(i=0;i<8;i++)
    if(texbitmap[i])
      texbitmap[i]->Release();

  if(op->GetInput(0) && op->GetInput(0)->Cache && op->GetInput(0)->Cache->ClassId==KC_MATERIAL)
    return Material_Add(2,(GenMaterial *)op->GetInput(0)->Cache,gm);
  else
    return gm;
}

void __stdcall Exec_Material_Material(KOp *op,KEnvironment *kenv)
{
  sInt i,use;
  GenMaterial *mat;
  GenMaterialPass *pass;
  sMaterial11 *mtrl;
  MultiPara *multi;

  op->ExecInputs(kenv);  
  mat = (GenMaterial *)op->Cache;
  if(getenv("KK_MTRLLOG") && op->OpId==atoi(getenv("KK_MTRLLOG")))
  {
    static sInt last = 0;
    if(sSystem->GetTime()-last>500)
    {
      last = sSystem->GetTime();
      fprintf(stderr,"mtrl op%d exec: passes=%d usage0=%d color0=%08x var0=%f\n",op->OpId,mat->Passes.Count,
        mat->Passes.Count?mat->Passes[0].Usage:-1,*op->GetAnimPtrU(28),kenv->Var[0].x);
    }
  }
  sVERIFY(mat && mat->ClassId==KC_MATERIAL);
  multi = (MultiPara *)(op->GetAnimPtrU(48));
  for(i=0;i<mat->Passes.Count;i++)
  {
    pass = &mat->Passes[i];
    use = pass->Usage;
    mtrl = (sMaterial11 *) pass->Mtrl;

    switch(use)
    {
    case ENGU_BASE:
      break;
    case ENGU_SHADOW:
      break;
    case ENGU_LIGHT:
      mtrl->SpecPower = multi->MultiSpecPower;
      mtrl->Color[0] = multi->MultiDiffuse;
      if(!(multi->MultiFlags & 0x0200)) // no specular?
        mtrl->Color[0] &= 0x00ffffff; // mask out specular color
      mtrl->TScale[0] = multi->MultiTScale[1];    // detail nump
      mtrl->TScale[1] = multi->MultiTScale[0];
      if(multi->MultiFlags & 0x1400)            // alpha fade bump or alpha test
        mtrl->TScale[0] = *op->GetAnimPtrF(24);
      sCopyMem(&mtrl->SRT1[0],op->GetAnimPtrU(34),(48-34)*4);
      break;
    case ENGU_POSTLIGHT:
      sCopyMem(&mtrl->TScale[0],op->GetAnimPtrU(24),(48-24)*4);
      if(multi->MultiFlags&0x0400)
        mtrl->Color[3] = 0xff808080;
      break;
    case ENGU_POSTLIGHT2:
      mtrl->Color[2] = multi->MultiAmbient;
      mtrl->TScale[2] = multi->MultiTScale[2];
      break;
    case ENGU_OTHER:      // single
      sCopyMem(&mtrl->TScale[0],op->GetAnimPtrU(24),(48-24)*4);

#ifndef KK_SMALL
      if(multi->MultiFlags & 0x30000) // finalizer set
      {
        pass->Size = *op->GetAnimPtrF(60);
        pass->Aspect = *op->GetAnimPtrF(62);
      }
#endif
      break;
    }
  }
}

GenMesh * __stdcall Mesh_MatLink(GenMesh *mesh,GenMaterial *mtrl,sInt mask,sInt pass)
{
  sInt i,j;
  GenMeshMtrl *mm;

  // check input mesh

  SCRIPTVERIFY(mtrl);
  SCRIPTVERIFY(mtrl->ClassId==KC_MATERIAL);
  if(CheckMesh(mesh,mask<<8)) return 0;

  j = mesh->Mtrl.Count;
  mm = mesh->Mtrl.Add();
  mm->Material = mtrl;
  mm->Pass = pass;
  for(i=0;i<mesh->Face.Count;i++)
    if(mesh->Face[i].Select)
      mesh->Face[i].Material = j;

  return mesh;
}

GenMaterial * __stdcall Material_Add(sInt count,GenMaterial *m0,...)
{
  sInt i,j;
  GenMaterial **mp,*mtrl,*madd;
  GenMaterialPass *pc;

  // linux port: va_list instead of walking the MSVC argument area
  static GenMaterial * va_m0[KK_MAXINPUT+1];
  {
    va_list ap;
    va_m0[0] = m0;
    va_start(ap,m0);
    for(sInt vi=1;vi<count && vi<=KK_MAXINPUT;vi++)
      va_m0[vi] = va_arg(ap,GenMaterial *);
    va_end(ap);
  }
  mp = va_m0;
  mtrl = new GenMaterial;

  for(i=0;i<count;i++)
  {
    madd = mp[i];
    if(madd)
    {
      for(j=0;j<madd->Passes.Count;j++)
      {
        pc = mtrl->Passes.Add();
        *pc = madd->Passes[j];
        pc->Mtrl->AddRef();
      }
      madd->Release();
    }
  }

  return mtrl;
}

/****************************************************************************/


/****************************************************************************/
/****************************************************************************/
