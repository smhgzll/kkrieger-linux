// x86 code filter from kkrunchy_k7 (dis.cpp, Fabian "ryg" Giesen, public
// domain), without the MSVC/debug-info parts. Splits the instruction stream
// into 20 separate streams (opcodes, modrm, sib, displacements, immediates,
// call targets via a move-to-front cache, jump targets as deltas) that
// compress much better than the mixed byte stream.
//
//   DisFilter(code,size,out)   -> filtered size (out must hold size*2+128)
//   DisUnfilter(filtered,dest) -> writes the original code to dest
//
// Both sides read the opcode tables below; the stub gets them as data
// (DisPackTable), so the tables may be tuned for the compiler at hand as
// long as fMO keeps the hard-coded meaning (f6/f7/fe/ff group decoding).

#include <stdint.h>
#include <string.h>

namespace dis {

typedef uint8_t sU8;
typedef uint16_t sU16;
typedef uint32_t sU32;
typedef int32_t sInt;

enum {
  fNM = 0x0, fAM = 0x1, fMR = 0x2, fMO = 0x3, fMODE = 0x3,
  fNI = 0x0, fBI = 0x4, fDI = 0x8, fWI = 0xc, fTYPE = 0xc,
  fAD = 0x0, fBR = 0x4, fDR = 0xc,
  fERR = 0x9,
};

#define NBUFFERS 20

static sU8 Table0[256] =
{
  // 0       1       2       3       4       5       6       7       8       9       a       b       c       d       e       f
  fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fNM|fBI,fNM|fDI,fNM|fNI,fNM|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fNM|fBI,fNM|fDI,fNM|fNI,fNM|fNI, // 0
  fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fNM|fBI,fNM|fDI,fNM|fNI,fNM|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fNM|fBI,fNM|fDI,fNM|fNI,fNM|fNI, // 1
  fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fNM|fBI,fNM|fDI,fNM|fNI,fNM|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fNM|fBI,fNM|fDI,fNM|fNI,fNM|fNI, // 2
  fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fNM|fBI,fNM|fDI,fNM|fNI,fNM|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fNM|fBI,fNM|fDI,fNM|fNI,fNM|fNI, // 3

  fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI, // 4
  fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI, // 5
  fNM|fNI,fNM|fNI,fMR|fNI,fMR|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fDI,fMR|fDI,fNM|fBI,fMR|fBI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI, // 6
  fAM|fBR,fAM|fBR,fAM|fBR,fAM|fBR,fAM|fBR,fAM|fBR,fAM|fBR,fAM|fBR,fAM|fBR,fAM|fBR,fAM|fBR,fAM|fBR,fAM|fBR,fAM|fBR,fAM|fBR,fAM|fBR, // 7

  fMR|fBI,fMR|fDI,fMR|fBI,fMR|fBI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI, // 8
  fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fERR   ,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI, // 9
  fAM|fAD,fAM|fAD,fAM|fAD,fAM|fAD,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fBI,fNM|fDI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI, // a
  fNM|fBI,fNM|fBI,fNM|fBI,fNM|fBI,fNM|fBI,fNM|fBI,fNM|fBI,fNM|fBI,fNM|fDI,fNM|fDI,fNM|fDI,fNM|fDI,fNM|fDI,fNM|fDI,fNM|fDI,fNM|fDI, // b

  fMR|fBI,fMR|fBI,fNM|fWI,fNM|fNI,fMR|fNI,fMR|fNI,fMR|fBI,fMR|fDI,fERR   ,fNM|fNI,fNM|fWI,fNM|fNI,fNM|fNI,fNM|fBI,fERR   ,fNM|fNI, // c
  fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fNM|fBI,fNM|fBI,fNM|fNI,fNM|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI, // d
  fAM|fBR,fAM|fBR,fAM|fBR,fAM|fBR,fNM|fBI,fNM|fBI,fNM|fBI,fNM|fBI,fAM|fDR,fAM|fDR,fAM|fAD,fAM|fBR,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI, // e
  fNM|fNI,fERR   ,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fMO|fNI,fMO|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fMO|fNI,fMO|fNI, // f
};

static sU8 Table0f[256] =
{
  // 0       1       2       3       4       5       6       7       8       9       a       b       c       d       e       f
  fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   , // 0
  fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fMR|fNI, // 1
  fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fERR   ,fERR   ,fERR   ,fERR   ,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI, // 2
  fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   , // 3

  fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI, // 4
  fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI, // 5
  fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI, // 6
  fMR|fBI,fMR|fBI,fMR|fBI,fMR|fBI,fMR|fNI,fMR|fNI,fMR|fNI,fNM|fNI,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fMR|fNI,fMR|fNI, // 7

  fAM|fDR,fAM|fDR,fAM|fDR,fAM|fDR,fAM|fDR,fAM|fDR,fAM|fDR,fAM|fDR,fAM|fDR,fAM|fDR,fAM|fDR,fAM|fDR,fAM|fDR,fAM|fDR,fAM|fDR,fAM|fDR, // 8
  fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI, // 9
  fNM|fNI,fNM|fNI,fNM|fNI,fMR|fNI,fMR|fBI,fMR|fNI,fMR|fNI,fMR|fNI,fERR   ,fERR   ,fERR   ,fMR|fNI,fMR|fBI,fMR|fNI,fERR   ,fMR|fNI, // a
  fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fERR   ,fERR   ,fMR|fBI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI, // b

  fMR|fNI,fMR|fNI,fMR|fBI,fMR|fNI,fMR|fBI,fMR|fBI,fMR|fBI,fMR|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI,fNM|fNI, // c
  fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI, // d
  fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI, // e
  fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fERR   , // f
};

// changes against the 2003 tables (all SSE-era opcodes clang emits):
//   0f 1f  nop r/m           fERR    -> fMR|fNI
//   0f ba  bt/bts.. r/m,imm8 fERR    -> fMR|fBI
//   0f c2  cmpps xmm,imm8    fMR|fNI -> fMR|fBI
//   0f c4  pinsrw imm8       fMR|fNI -> fMR|fBI
//   0f c5  pextrw imm8       fMR|fNI -> fMR|fBI
//   0f c6  shufps imm8       fMR|fNI -> fMR|fBI

static sU8 Tablefx[32] =
{
  fMR|fBI,fERR   ,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fDI,fERR   ,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,fMR|fNI,
  fMR|fNI,fMR|fNI,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fERR   ,fMR|fNI,fMR|fNI,fMR|fNI,fERR   ,fMR|fNI,fERR   ,fMR|fNI,fERR   ,
};

static sU32 bswap(sU32 x) { return __builtin_bswap32(x); }

struct Buf
{
  sU8 *Data; sInt Size;
  void Put(sU32 v,sInt n) { memcpy(Data+Size,&v,n); Size += n; }
  void Append(const sU8 *p,sInt n) { memcpy(Data+Size,p,n); Size += n; }
};

static sInt CountInstr(const sU8 *instr)
{
  const sU8 *start = instr;
  sInt code = *instr++, code2, modrm, sib, flags;
  bool o16 = false;
  if(code == 0x66) { o16 = true; code = *instr++; }
  if(code == 0x0f) { code2 = *instr++; flags = Table0f[code2]; }
  else flags = Table0[code];
  if((flags & fMODE) == fMO)
    flags = Tablefx[((*instr & 0x38) >> 3) | ((code & 0x01) << 3) | ((code & 0x08) << 1)];
  if(flags == fERR)
    return 1;
  if(flags & fMR)
  {
    modrm = *instr++;
    sib = ((modrm & 0x07) == 4 && (modrm & 0xc0) != 0xc0) ? *instr++ : 0;
    if((modrm & 0xc0) == 0x40) instr++;
    if((modrm & 0xc0) == 0x80 || (modrm & 0xc7) == 0x05 || ((modrm & 0xc0) == 0 && (sib & 0x07) == 5))
      instr += 4;
  }
  if((flags & fMODE) == fAM)
  {
    switch(flags & fTYPE) { case fAD: instr += 4; break; case fBR: instr += 1; break; case fDR: instr += 4; break; }
  }
  else
  {
    switch(flags & fTYPE) { case fBI: instr += 1; break; case fDI: instr += o16 ? 2 : 4; break; case fWI: instr += 2; break; }
  }
  return sInt(instr - start);
}

struct Filterer
{
  Buf B[NBUFFERS];
  sU32 FuncTable[255];
  sInt FuncTablePos;
  bool NextFunc;
  sU32 LastJump;

  sInt Process(const sU8 *instr,sU32 memory)
  {
    const sU8 *start = instr;
    sU8 code,code2=0,modrm=0,sib=0,flags;
    sU32 val,tmp;
    bool o16 = false;
    sInt i;

    code = *instr++;
    if(NextFunc && code != 0xcc)
    {
      FuncTable[FuncTablePos] = memory;
      if(++FuncTablePos == 255) FuncTablePos = 0;
      NextFunc = false;
    }
    if(code == 0x66) { o16 = true; code = *instr++; }
    if(code == 0x0f) { code2 = *instr++; flags = Table0f[code2]; }
    else flags = Table0[code];
    if(code == 0xc2 || code == 0xc3 || code == 0xcc)
      NextFunc = true;
    if((flags & fMODE) == fMO)
      flags = Tablefx[((*instr & 0x38) >> 3) | ((code & 0x01) << 3) | ((code & 0x08) << 1)];

    if(flags == fERR)
    {
      B[0].Put(0xce,1);
      B[0].Put(*start,1);
      return 1;
    }

    if(o16) B[0].Put(0x66,1);
    B[0].Put(code,1);
    if(code == 0x0f) B[0].Put(code2,1);

    if(flags & fMR)     // fMR or fMO
    {
      modrm = *instr++;
      B[0].Put(modrm,1);
      if((modrm & 0x07) == 4 && (modrm & 0xc0) != 0xc0)
      {
        sib = *instr++;
        B[19].Put(sib,1);
      }
      if((modrm & 0xc0) == 0x40)
        B[(modrm & 0x07)+1].Put(*instr++,1);
      if((modrm & 0xc0) == 0x80 || (modrm & 0xc7) == 0x05 || ((modrm & 0xc0) == 0 && (sib & 0x07) == 5))
      {
        memcpy(&val,instr,4); instr += 4;
        B[(modrm & 0xc7) == 5 ? 14 : 13].Put(bswap(val),4);
      }
    }

    if((flags & fMODE) == fAM)
    {
      switch(flags & fTYPE)
      {
      case fAD: memcpy(&val,instr,4); instr += 4; B[15].Put(val,4); break;
      case fBR: B[9].Put(*instr++,1); break;
      case fDR:
        memcpy(&val,instr,4); instr += 4;
        val += sU32(instr - start) + memory;
        if(code != 0xe8)
        {
          i = sInt(val - LastJump);
          tmp = (i < 0) ? -i * 2 - 1 : i * 2;
          B[17].Put(tmp,4);
          LastJump = val;
        }
        else
        {
          for(i=0;i<255;i++)
            if(FuncTable[i] == val)
              break;
          B[16].Put(i+1,1);
          if(i == 255)
          {
            B[18].Put(val,4);
            FuncTable[FuncTablePos] = val;
            if(++FuncTablePos == 255) FuncTablePos = 0;
          }
        }
        break;
      }
    }
    else
    {
      switch(flags & fTYPE)
      {
      case fBI: B[10].Put(*instr++,1); break;
      case fDI:
        if(!o16) { B[12].Append(instr,4); instr += 4; break; }
        // fall-through
      case fWI: B[11].Append(instr,2); instr += 2; break;
      }
    }
    return sInt(instr - start);
  }
};

// returns the filtered size; out = [NBUFFERS sizes][streams]
static sInt DisFilter(const sU8 *code,sInt size,sU8 *out)
{
  // first pass: find where the last complete instruction ends
  sInt curSize = size, lastSize = size;
  const sU8 *cur = code;
  while(curSize > 0)
  {
    lastSize = curSize;
    sInt n = CountInstr(cur);
    cur += n; curSize -= n;
  }

  Filterer *f = new Filterer;
  for(sInt i=0;i<NBUFFERS;i++) { f->B[i].Data = new sU8[size*2+64]; f->B[i].Size = 0; }
  for(sInt i=0;i<255;i++) f->FuncTable[i] = ~0U;
  f->FuncTablePos = 0; f->NextFunc = true; f->LastJump = 0;

  sInt rest = lastSize;
  curSize = size - rest;
  cur = code;
  sU32 memory = 0;
  while(curSize > 0)
  {
    sInt n = f->Process(cur,memory);
    memory += n; cur += n; curSize -= n;
  }
  while(rest--)
  {
    f->B[0].Put(0xce,1);
    f->B[0].Put(*cur++,1);
  }

  sU8 *o = out;
  for(sInt i=0;i<NBUFFERS;i++) { memcpy(o,&f->B[i].Size,4); o += 4; }
  for(sInt i=0;i<NBUFFERS;i++) { memcpy(o,f->B[i].Data,f->B[i].Size); o += f->B[i].Size; delete[] f->B[i].Data; }
  delete f;
  return sInt(o - out);
}

// the nibble-packed table the stub uses: [0..127] Table0, [128..255] Table0f,
// two opcodes per byte (low nibble = even opcode); fERR becomes 0 (never
// reaches the decoder: those bytes are escaped)
static void DisPackTable(sU8 *table)
{
  for(sInt i=0;i<512;i+=2)
  {
    sInt v = (i < 256) ? (Table0[i] | (Table0[i+1] << 4)) : (Table0f[i-256] | (Table0f[i-255] << 4));
    if((v & 0x0f) == fERR) v &= 0xf0;
    if((v >> 4) == fERR) v &= 0x0f;
    table[i/2] = sU8(v);
  }
}

// reference decoder (the stub has the same thing in asm); returns the size
static sInt DisUnfilter(const sU8 *packed,sU8 *dest)
{
  sU8 table[256];
  DisPackTable(table);

  const sU8 *buffer[NBUFFERS];
  const sU8 *start = packed + NBUFFERS*4;
  for(sInt i=0;i<NBUFFERS;i++)
  {
    sU32 v; memcpy(&v,packed+i*4,4);
    buffer[i] = start; start += v;
  }
  const sU8 *finish = buffer[1];
  sU32 funcTable[256];
  sInt funcTablePos = 1;
  sU32 lastJump = 0, memory = 0, val;
  bool nextFunc = true;
  sU8 *oldDest = dest;

  while(buffer[0] < finish)
  {
    sU8 *istart = dest;
    const sU8 *corei = buffer[0];
    sU8 code = *corei++, modrm, sib;
    sInt flags, i;
    bool o16 = false;

    if(nextFunc && code != 0xcc)
    {
      funcTable[funcTablePos] = memory;
      if(++funcTablePos == 256) funcTablePos = 1;
      nextFunc = false;
    }

    if(code == 0xce)
      *dest++ = *corei++;
    else
    {
      *dest++ = code;
      modrm = sib = 0;
      if(code == 0x66) { o16 = true; code = *corei++; *dest++ = code; }
      if(code == 0xc2 || code == 0xc3 || code == 0xcc)
        nextFunc = true;
      if(code == 0x0f)
      {
        sU8 code2 = *corei++;
        *dest++ = code2;
        flags = (table[128 + code2/2] >> ((code2 & 1)*4)) & 15;
      }
      else
        flags = (table[code/2] >> ((code & 1)*4)) & 15;

      if(flags & fMR)
      {
        modrm = *corei++;
        *dest++ = modrm;
        if((flags & fMODE) == fMO)
        {
          flags = fMR|fNI;
          if(!(modrm & 0x38) && !(code & 8))
            flags += (code & 1) ? fDI : fBI;
        }
        if((modrm & 0x07) == 4 && (modrm & 0xc0) != 0xc0)
          *dest++ = sib = *buffer[19]++;
        if((modrm & 0xc0) == 0x40)
          *dest++ = *buffer[(modrm & 0x07) + 1]++;
        if((modrm & 0xc0) == 0x80 || (modrm & 0xc7) == 0x05 || ((modrm & 0xc0) == 0x00 && (sib & 0x07) == 0x05))
        {
          i = (modrm & 0xc7) == 5 ? 14 : 13;
          memcpy(&val,buffer[i],4); buffer[i] += 4;
          val = bswap(val);
          memcpy(dest,&val,4); dest += 4;
        }
      }

      if((flags & fMODE) == fAM)
      {
        switch(flags & fTYPE)
        {
        case fAD: memcpy(dest,buffer[15],4); buffer[15] += 4; dest += 4; break;
        case fBR: *dest++ = *buffer[9]++; break;
        case fDR:
          if(code == 0xe8)
          {
            i = *buffer[16]++;
            if(i)
              val = funcTable[i];
            else
            {
              memcpy(&val,buffer[18],4); buffer[18] += 4;
              funcTable[funcTablePos] = val;
              if(++funcTablePos == 256) funcTablePos = 1;
            }
          }
          else
          {
            memcpy(&val,buffer[17],4); buffer[17] += 4;
            val = (val & 1) ? ~(val >> 1) : (val >> 1);
            lastJump += val;
            val = lastJump;
          }
          val -= sU32(dest + 4 - istart) + memory;
          memcpy(dest,&val,4); dest += 4;
          break;
        }
      }
      else
      {
        switch(flags & fTYPE)
        {
        case fBI: *dest++ = *buffer[10]++; break;
        case fDI:
          if(!o16) { memcpy(dest,buffer[12],4); dest += 4; buffer[12] += 4; break; }
          // fall-through
        case fWI: memcpy(dest,buffer[11],2); dest += 2; buffer[11] += 2; break;
        }
      }
    }
    buffer[0] = corei;
    memory += sU32(dest - istart);
  }
  return sInt(dest - oldDest);
}

} // namespace dis
