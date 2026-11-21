// This file is distributed under a BSD license. See LICENSE.txt for details.

#include "_types.hpp"
#include "material11.hpp"
#include "glrender.hpp"

/****************************************************************************/

void sMaterial11::FreeEverything()
{
  for(sInt i=0;i<4;i++)
    SetTex(i,sINVALID);

  if(Setup != sINVALID)
  {
    sSystem->MtrlRemSetup(Setup);
    Setup = sINVALID;
  }
}

/****************************************************************************/

void sMaterial11::LoadDefaults()
{
  HasTexSRT = sFALSE;
  Setup = sINVALID;

  BaseFlags = sMBF_ZON;
  SpecialFlags = LightFlags = pad1 = 0;
  pad3 = pad4 = AlphaCombiner = pad5 = 0;
  SpecPower = 8.0f;
  ShaderLevel = sPS_00;

  sSetMem(Combiner,0,sizeof(Combiner));
  sSetMem(SRT1,0,sizeof(SRT1));
  sSetMem(SRT2,0,sizeof(SRT2));
  
  for(sInt i=0;i<4;i++)
  {
    TFlags[i] = sMTF_MIPMAPS;
    Color[i] = ~0U;
    TScale[i] = 0.0f;
    Tex[i] = sINVALID;
  }

}

/****************************************************************************/

sMaterial11::sMaterial11()
{
  LoadDefaults();
}

/****************************************************************************/

sMaterial11::~sMaterial11()
{
  FreeEverything();
}

/****************************************************************************/

void sMaterial11::Reset()
{
  FreeEverything();
  LoadDefaults();
}

/****************************************************************************/

void sMaterial11::CopyFrom(const sMaterial11 *x)
{
  FreeEverything();

  BaseFlags = x->BaseFlags;
  SpecialFlags = x->SpecialFlags;
  LightFlags = x->LightFlags;
  sCopyMem(Combiner,x->Combiner,sizeof(Combiner));
  AlphaCombiner = x->AlphaCombiner;
  SpecPower = x->SpecPower;
  sCopyMem(SRT1,x->SRT1,sizeof(SRT1));
  sCopyMem(SRT2,x->SRT2,sizeof(SRT2));
  ShaderLevel = x->ShaderLevel;

  for(sInt i=0;i<4;i++)
  {
    TFlags[i] = x->TFlags[i];
    TScale[i] = x->TScale[i];
    Color[i] = x->Color[i];
    SetTex(i,x->Tex[i]);
    TexUse[i] = x->TexUse[i];
  }


  HasTexSRT = x->HasTexSRT;
  Setup = x->Setup;
  if(Setup != sINVALID)
    sSystem->MtrlAddRefSetup(Setup);
}

/****************************************************************************/

void sMaterial11::DefaultCombiner(sBool *tex)
{
  sBool mytex[4];
  sInt i;
  sU32 light;

// find out which textures are set

  if(tex==0)
  {
    tex = mytex;
    for(i=0;i<4;i++)
      tex[i] = (Tex[i]!=sINVALID);
  }

// prepare

  for(i=0;i<sMCS_MAX;i++)
    Combiner[i] = 0;

  light = LightFlags&sMLF_MODEMASK;

// set textures

  if(tex[0] && !(SpecialFlags&sMSF_BUMPDETAIL))
    Combiner[sMCS_TEX0] = sMCOA_MUL;
  if(tex[1] && light<sMLF_BUMPX)
    Combiner[sMCS_TEX1] = sMCOA_MUL;
  if(tex[2])
    Combiner[sMCS_TEX2] = sMCOA_ADD;
  if(tex[3])
    Combiner[sMCS_TEX3] = sMCOA_ADD;

// set light

  if(light)
  {
    Combiner[sMCS_LIGHT] = sMCOA_MUL;
    Combiner[sMCS_COLOR0] = sMCOA_MUL;
    Combiner[sMCS_COLOR1] = sMCOA_ADD;
  }

// set first combiner to mul

  for(i=0;i<sMCS_MAX;i++)
  {
    if(Combiner[i])
    {
      Combiner[i] = sMCOA_SET;
      return;
    }
  }

  Combiner[sMCS_COLOR0] = sMCOA_SET;  // no texture, set color
}

/****************************************************************************/

void sMaterial11::SetTex(sInt i,sInt handle)
{
  sVERIFY(i >= 0 && i <= 3);

  if(handle != sINVALID)
    sSystem->AddRefTexture(handle);

  if(Tex[i] != sINVALID)
    sSystem->RemTexture(Tex[i]);

  Tex[i] = handle;
}

/****************************************************************************/

// render states: (token,value) pairs, OpenGL values (see glrender.hpp)
#define ST(token,value) { *data++ = (token); *data++ = (value); }

static sU32 cullMode(sU32 flags)                // front faces are clockwise
{
  return (flags & sMBF_DOUBLESIDED) ? 0 : (flags & sMBF_INVERTCULL) ? GL_FRONT : GL_BACK;
}

static void makeStencilStates(sU32 *&pt,sU32 flags)
{
  sU32 *data = pt;
  sU32 zfail = flags & sMBF_STENCILZFAIL;

  switch(flags & sMBF_STENCILMASK)
  {
  default:
    ST(GLR_STENCIL,0);
    ST(GLR_STENCIL2SIDED,0);
    ST(GLR_STENCILFUNC,GL_ALWAYS);
    break;
  case sMBF_STENCILINC:                         // shadow volume, one side per pass
  case sMBF_STENCILDEC:
    {
      sU32 op = (flags & sMBF_STENCILMASK)==sMBF_STENCILINC ? GL_INCR_WRAP : GL_DECR_WRAP;
      ST(GLR_STENCIL,1);
      ST(GLR_STENCIL2SIDED,0);
      ST(GLR_STENCILFUNC,GL_ALWAYS);
      ST(GLR_STENCILFAIL,GL_KEEP);
      ST(GLR_STENCILZFAIL,zfail ? op : GL_KEEP);
      ST(GLR_STENCILPASS,zfail ? GL_KEEP : op);
    }
    break;
  case sMBF_STENCILTEST:
    ST(GLR_STENCIL,1);
    ST(GLR_STENCIL2SIDED,0);
    ST(GLR_STENCILFUNC,GL_EQUAL);
    ST(GLR_STENCILFAIL,GL_KEEP);
    ST(GLR_STENCILZFAIL,GL_KEEP);
    ST(GLR_STENCILPASS,GL_KEEP);
    break;
  case sMBF_STENCILCLR:
    ST(GLR_STENCIL,1);
    ST(GLR_STENCIL2SIDED,0);
    ST(GLR_STENCILFUNC,GL_ALWAYS);
    ST(GLR_STENCILFAIL,GL_ZERO);
    ST(GLR_STENCILZFAIL,GL_ZERO);
    ST(GLR_STENCILPASS,GL_ZERO);
    break;
  case sMBF_STENCILINDE:                        // shadow volume, both sides in one pass
    ST(GLR_CULL,0);
    ST(GLR_STENCIL,1);
    ST(GLR_STENCIL2SIDED,1);
    ST(GLR_STENCILFUNC,GL_ALWAYS);
    ST(GLR_BACKFUNC,GL_ALWAYS);
    ST(GLR_STENCILFAIL,GL_KEEP);
    ST(GLR_BACKFAIL,GL_KEEP);
    ST(GLR_STENCILZFAIL,zfail ? GL_DECR_WRAP : GL_KEEP);
    ST(GLR_BACKZFAIL,zfail ? GL_INCR_WRAP : GL_KEEP);
    ST(GLR_STENCILPASS,zfail ? GL_KEEP : GL_INCR_WRAP);
    ST(GLR_BACKPASS,zfail ? GL_KEEP : GL_DECR_WRAP);
    break;
  case sMBF_STENCILRENDER:
    ST(GLR_STENCIL,1);
    ST(GLR_STENCIL2SIDED,0);
    ST(GLR_STENCILFUNC,GL_NOTEQUAL);
    ST(GLR_STENCILFAIL,GL_KEEP);
    ST(GLR_STENCILZFAIL,GL_KEEP);
    ST(GLR_STENCILPASS,GL_ZERO);
    break;
  }

  pt = data;
}

// The shaders of a material come from the game's precompiled shaders:
// shaders/materials.txt lists every material of the game data by the fields
// its shaders depend on (below), tools/shaderpack.py turns it into a table of
// key hashes.
#include "materialshaders.inc"

sBool sMaterial11::Compile()
{
  static const sU32 psatoc[16] =
  {
    0,1<<sMCS_LIGHT,(1<<sMCS_LIGHT),1<<sMCS_LIGHT,
    1<<sMCS_TEX0,1<<sMCS_TEX1,1<<sMCS_TEX2,1<<sMCS_TEX3,
    1<<sMCS_COLOR0,1<<sMCS_COLOR1,1<<sMCS_COLOR2,1<<sMCS_COLOR3,
    0,0,0,0,
  };
  static const sU32 psttoc[4] =
  {
    sMCS_TEX0,sMCS_TEX1,sMCS_TEX2,sMCS_TEX3
  };

  sU32 *data;
  sInt i;
  sU32 flags;
  static sU32 states[256];
  sInt combinermask;
  sInt TCount;

// modify material

  switch(ShaderLevel)
  {
  case sPS_11:
  case sPS_14:
  case sPS_20:
    if(SpecialFlags & sMSF_BUMPDETAIL)
    {
      SetTex(0,sINVALID);
      SpecialFlags &= ~sMSF_BUMPDETAIL;
    }
    break;
  }

//*** initialize compile

  Setup = sINVALID;
  HasTexSRT = sFALSE;
  data = states;
  TCount = 0;
  combinermask = 0;

  for(i=0;i<4;i++)
    TexUse[i] = -1;

//*** base flags (the alpha test is part of the pixel shader)

  flags = BaseFlags;
  sF32 f = 0;
  if(flags & sMBF_ZBIASBACK) f=1.0f / 65536.0f;
  if(flags & sMBF_ZBIASFORE) f=-1.0f / 65536.0f;

  if(!(flags & sMBF_ZREAD))
    i = GL_ALWAYS;
  else if(flags & sMBF_ZEQUAL)
    i = GL_EQUAL;
  else if(flags & sMBF_SHADOWMASK)
    i = GL_LESS;
  else
    i = GL_LEQUAL;

  ST(GLR_ZTEST,1);
  ST(GLR_ZWRITE,(flags & sMBF_ZWRITE) ? 1 : 0);
  ST(GLR_ZFUNC,i);
  ST(GLR_CULL,cullMode(flags));
  ST(GLR_COLORMASK,(flags & sMBF_ZONLY) ? 0 : 15);
  ST(GLR_SLOPEBIAS,*(sU32 *)&f);
  ST(GLR_DEPTHBIAS,*(sU32 *)&f);

  flags = BaseFlags & sMBF_BLENDMASK;
  ST(GLR_BLEND,flags ? 1 : 0);

  if(flags && flags <= sMBF_BLENDADDSA)
  {
    static const sU16 blendOp[10][2] =
    {
      { 0,0 },
      { GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA },
      { GL_ONE,GL_ONE },
      { GL_ZERO,GL_SRC_COLOR },
      { GL_DST_COLOR,GL_SRC_COLOR },
      { GL_ONE,GL_ONE_MINUS_SRC_COLOR },
      { GL_ONE,GL_ONE },
      { GL_ONE_MINUS_DST_COLOR,GL_ONE_MINUS_SRC_COLOR },
      { GL_DST_ALPHA,GL_ONE },
      { GL_SRC_ALPHA,GL_ONE }
    };

    ST(GLR_BLENDOP,(flags == sMBF_BLENDSUB) ? GL_FUNC_REVERSE_SUBTRACT : GL_FUNC_ADD);
    ST(GLR_BLENDSRC,blendOp[flags >> 12][0]);
    ST(GLR_BLENDDST,blendOp[flags >> 12][1]);
  }

  makeStencilStates(data,BaseFlags);

//*** textures: one stage per texture, then the lighting stages

  for(i=0;i<4;i++)
  {
    static const sU16 filters[8][3] =            // mag, min, mip
    {
      { GL_NEAREST,GL_NEAREST,GLR_MIP_NONE },
      { GL_LINEAR,GL_LINEAR,GLR_MIP_NONE },
      { GL_LINEAR,GL_LINEAR,GLR_MIP_LINEAR },
      { GL_LINEAR,GL_LINEAR,GLR_MIP_LINEAR },   // was anisotropic
      { GL_NEAREST,GL_NEAREST,GLR_MIP_NEAREST },
      { GL_LINEAR,GL_LINEAR,GLR_MIP_NEAREST },
      { GL_NEAREST,GL_NEAREST,GLR_MIP_NONE },
      { GL_NEAREST,GL_NEAREST,GLR_MIP_NONE },
    };
    if(Tex[i]!=sINVALID)
    {
      flags = TFlags[i];
      sInt sam = GLR_SAMPLER+TCount*8;
      TexUse[TCount++] = i;

      ST(sam+GLR_MAGFILTER,filters[flags&7][0]);
      ST(sam+GLR_MINFILTER,filters[flags&7][1]);
      ST(sam+GLR_MIPFILTER,filters[flags&7][2]);
      ST(sam+GLR_ADDRESSU,(flags&sMTF_CLAMP) ? GL_CLAMP_TO_EDGE : GL_REPEAT);
      ST(sam+GLR_ADDRESSV,(flags&sMTF_CLAMP) ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    }
  }

  if(LightFlags & sMLF_MODEMASK)
  {
    sInt dospecular = (SpecialFlags & sMSF_NOSPECULAR) ? 0 : 1;

    // cube normalizes (L+H)
    for(i=0;i<=dospecular;i++)
    {
      TexUse[TCount+i] = -2;
      sInt sam = GLR_SAMPLER+(TCount+i)*8;
      ST(sam+GLR_MAGFILTER,GL_LINEAR);
      ST(sam+GLR_MINFILTER,GL_LINEAR);
      ST(sam+GLR_MIPFILTER,GLR_MIP_NONE);
      ST(sam+GLR_ADDRESSU,GL_REPEAT);
      ST(sam+GLR_ADDRESSV,GL_REPEAT);
    }

    // attenuation
    sInt attnTex = TCount+1+dospecular;
    TexUse[attnTex] = -3;
    sInt sam = GLR_SAMPLER+attnTex*8;
    ST(sam+GLR_MAGFILTER,GL_LINEAR);
    ST(sam+GLR_MINFILTER,GL_LINEAR);
    ST(sam+GLR_MIPFILTER,GLR_MIP_NONE);
    ST(sam+GLR_ADDRESSU,GL_CLAMP_TO_EDGE);
    ST(sam+GLR_ADDRESSV,GL_CLAMP_TO_EDGE);
    ST(sam+GLR_ADDRESSW,GL_CLAMP_TO_EDGE);
  }

  *data++ = ~0;
  *data++ = ~0;

//*** texture transforms needed?

  for(i=0;i<sMCS_MAX;i++)
  {
    flags = Combiner[i];
    combinermask |= psatoc[flags&15];
    if(flags & 0xff0)
      combinermask |= 1<<i;
  }
  flags = AlphaCombiner;
  combinermask |= psatoc[flags&15];
  combinermask |= psatoc[(flags>>4)&15];

  if(ShaderLevel != sPS_00 && (LightFlags & sMLF_MODEMASK) == sMLF_BUMPX && Tex[1] != sINVALID)
    combinermask |= 1 << sMCS_TEX1;

  for(i=0;i<4;i++)
    if((combinermask & (1 << psttoc[i])) && (TFlags[i]&sMTF_TRANSMASK) >= sMTF_TRANS1)
      HasTexSRT = sTRUE;

//*** shaders: look up the material key

  sU32 key[22],hash;
  key[0] = BaseFlags & (sMBF_ALPHATEST|sMBF_FOG|sMBF_NOTEXTURE|sMBF_NONORMAL|sMBF_SHADOWMASK);
  key[1] = SpecialFlags & 0xff0;
  key[2] = LightFlags & sMLF_MODEMASK;
  for(i=0;i<4;i++)
    key[3+i] = TFlags[i] & 0xf030;                // uv set, transform
  for(i=0;i<sMCS_MAX;i++)
    key[7+i] = Combiner[i] & 0x1ff;               // source, operation, INVERTA
  if(Combiner[sMCS_VERTEX] & 0xff0)
    key[7+sMCS_VERTEX] |= 0x1000;
  key[20] = AlphaCombiner & 0x3ff;
  key[21] = 0;
  for(i=0;i<4;i++)
    if(Tex[i]!=sINVALID)
      key[21] |= 1<<i;

  hash = 2166136261U;                             // FNV-1a
  for(i=0;i<22;i++)
    hash = (hash ^ key[i]) * 16777619U;
  for(i=0;i<MATERIAL_SHADERS && MaterialShaderKey[i]!=hash;i++);
  if(i==MATERIAL_SHADERS)
  {
#ifndef KK_SMALL
    sDPrintF("material shader missing (key %08x): not in shaders/materials.txt\n",hash);
#endif
    return sFALSE;
  }

  Setup = sSystem->MtrlAddSetup(states,MaterialShaderVS[i],MaterialShaderPS[i]);
  return Setup != sINVALID;
}

/****************************************************************************/

void sMaterial11::Set(const sMaterialEnv &env)
{
  sMaterialInstance inst;
  sMatrix vc[9];
  sVector pc[8];

  // matrices: world-view-projection + basic light setup
  sSystem->LastMatrix = env.ModelSpace;
  sSystem->LastMatrix.TransR();

  vc[0].Mul4(env.ModelSpace,sSystem->LastViewProject);    // c0-c3: wvp
  vc[0].Trans4();
  vc[1].i.Rotate34(sSystem->LastMatrix,env.LightPos);     // c4: light pos (mdl)

  inst.VSConstants = (sVector *) vc;
  inst.PSConstants = pc;
  inst.NumPSConstants = 0;

  // actual setup
  if(BaseFlags & sMBF_SHADOWMASK)
  {
    // fast path for shadow materials: only update light position
    vc[1].i.w = 0.0f;
    inst.NumVSConstants = 5;
  }
  else
  {
    // light attenuation
    if(env.LightRange)
    {
      vc[1].j.Scale4(vc[1].i,-0.5f / env.LightRange);     // c5: light attn
      vc[1].j.x += 0.5f;
      vc[1].j.y += 0.5f;
      vc[1].j.z += 0.5f;
      vc[1].j.w = 0.5f / env.LightRange;
    }
    else
      vc[1].j.Init(0.5f,0.5f,0.5f,0.0f);

    vc[1].k.Rotate34(sSystem->LastMatrix,env.CameraSpace.l); // c6: cam (mdl)
    vc[1].l.Init(TScale[0],TScale[1],TScale[2],TScale[3]); // c7: tex scale

    inst.NumVSConstants = 8;

    // texture srt (if necessary)
    if(HasTexSRT)
    {
      vc[2].InitSRT(SRT1);                            // c8-c9: tex srt1
      vc[2].Trans4();

      sF32 fs,fc;
      sFSinCos(SRT2[2],fs,fc);

      vc[2].k.Init( SRT2[0]*fc,SRT2[1]*fs,0,SRT2[3]); // c10-c11: tex srt2
      vc[2].l.Init(-SRT2[0]*fs,SRT2[1]*fc,0,SRT2[4]);
      inst.NumVSConstants = 12;
    }

    if(SpecialFlags & sMSF_ENVIMASK)                  // c12-c15: tex special 1
    {
      vc[3].MulA(env.ModelSpace,sSystem->LastCamera);
      vc[3].Trans4();
      inst.NumVSConstants = 16;
    }

    if(SpecialFlags & sMSF_PROJMASK)                  // c16-c19: tex special 2
    {
      sInt mask = SpecialFlags & sMSF_PROJMASK;

      if(mask == sMSF_PROJWORLD)
        vc[4] = env.ModelSpace;
      else if(mask == sMSF_PROJEYE)
        vc[4].MulA(env.ModelSpace,sSystem->LastCamera);

      vc[4].Trans4();
      inst.NumVSConstants = 20;
    }

    if(BaseFlags & sMBF_FOG)                          // c20: fog
    {
      sMatrix temp;
      temp.MulA(env.ModelSpace,sSystem->LastCamera);
      temp.Trans4();

      vc[5].i = temp.k;
      vc[5].i.w -= env.FogEnd;
      vc[5].i.Scale4(1.0f / (env.FogStart - env.FogEnd));
      inst.NumVSConstants = 21;
    }

    if((LightFlags & sMLF_MODEMASK) == sMLF_OFF)
    {
      for(sInt i=0;i<4;i++) // c0-c3: colors 0-3
        pc[i].InitColor(Color[i]);

      inst.NumPSConstants = 4;
    }
    else
    {
      pc[0].InitColor(Color[0]);                      // c0: light color
      pc[0].Mul4(env.LightColor);
      pc[0].Scale4(env.LightAmplify);

      // magic values derive from the construction of muls/mads in the
      // pixel shader.
      sF32 usePower = sRange(SpecPower,60.0f,8.0f);
      sF32 invScale = 1.0f / 7.336032f;

      pc[1].x = SpecPower;                            // c1: specular param
      pc[1].z = invScale + (usePower - 8.0f) * 0.01565302f;
      pc[1].w = invScale - pc[1].z;
      inst.NumPSConstants = 2;
    }
  }

  // texture setup
  inst.NumTextures = 4;
  for(sInt i=0;i<4;i++)
  {
    sInt use = TexUse[i];
    inst.Textures[i] = (use >= 0 && use <= 3) ? Tex[use] : use;
  }

  if(ShaderLevel==sPS_00)
    inst.NumPSConstants = 0;

  // set everything
  sSystem->MtrlSetSetup(Setup);
  sSystem->MtrlSetInstance(inst);

}

/****************************************************************************/

void sMaterial11::SetShadowStates(sU32 flags)
{
  sU32 states[32],*data=states;

  ST(GLR_CULL,cullMode(flags));
  makeStencilStates(data,flags);
  *data++ = ~0;
  *data++ = ~0;
  
  sSystem->SetStates(states);
}

/****************************************************************************/
