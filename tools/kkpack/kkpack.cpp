// kkpack - compress a file with the kkrunchy_k7 context mixing model
// (reference/fr_public/kkrunchy_k7: rangecoder.cpp + model_asm.asm by
// Fabian "ryg" Giesen, public domain), for the Linux build of .kkrieger.
//
//   kkpack in out        pack, then unpack again and verify
//
// Stream format (as kkrunchy_k7): range coded bits; every 8 KB a "zero
// block" flag; the model predicts each bit from the bytes before it.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t sU8;
typedef uint32_t sU32;
typedef int32_t sInt;
typedef uint64_t sU64;
typedef uint16_t sU16;

extern "C" void __attribute__((fastcall)) modelInitASM();
extern "C" sInt __attribute__((fastcall)) modelASM(sInt bit);
extern "C" { sU8 *bufPtr,*startBufPtr; extern sU8 masks[],bitm[],WorkData[]; extern sInt nmodel,workSize; }

static inline sU32 mulShift12(sU32 a,sU32 b) { return (sU32)(((sU64)a*b)>>12); }

// ---- encoder (rangecoder.cpp)

static sU8 *outPtr;
static sInt ffNum,cache;
static sU64 low;
static sU32 range;
static bool firstByte;

static void shiftLow()
{
  sU32 carry = sU32(low >> 32);
  if(low < 0xff000000 || carry == 1)
  {
    if(!firstByte)
      *outPtr++ = cache + carry;
    else
      firstByte = false;
    for(;ffNum;ffNum--)
      *outPtr++ = 0xff + carry;
    cache = sInt((low >> 24) & 0xff);
  }
  else
    ffNum++;
  low = (low << 8) & 0xffffffff;
}

static void codeBit(sU32 prob,sInt bit)
{
  sU32 newBound = mulShift12(range,prob);
  if(bit)
    range = newBound;
  else
  {
    low += newBound;
    range -= newBound;
  }
  while(range < 0x01000000)
  {
    range <<= 8;
    shiftLow();
  }
}

sU32 Pack(const sU8 *in,sU32 inSize,sU8 *out)
{
  sU32 prob = 2048,zeroProb = 1;

  outPtr = out; ffNum = 0; low = 0; range = ~0U; cache = 0; firstByte = true;
  // the model may look at bufPtr[0] (match search); the decoder has a zero
  // there, so show the model a buffer that is filled in only as we go
  // (the model also reads up to 8 bytes before the start: keep them zero)
  sU8 *workmem = (sU8 *) calloc(inSize+16384+32,1);
  sU8 *work = workmem+32;
  memset(WorkData,0,workSize);   // modelInitASM expects zeroed memory
  modelInitASM();
  bufPtr = startBufPtr = work;

  for(sU32 pos=0;pos<inSize;pos++)
  {
    if((pos & 8191) == 0)
    {
      sInt isZero = (inSize - pos) > 8192;
      if(isZero)
        for(sInt i=0;i<8192;i++)
          if(in[pos+i] != 0) { isZero = 0; break; }
      codeBit(zeroProb,isZero);
      zeroProb = (zeroProb + (isZero ? 4096 : 1)) >> 1;
      if(isZero)
      {
        bufPtr += 8192;
        pos += 8192-1;
        continue;
      }
    }
    for(sInt i=0;i<8;i++)
    {
      sInt bit = (in[pos] >> (7-i)) & 1;
      codeBit(prob,bit);
      if(i == 7)
        *bufPtr++ = in[pos];
      prob = modelASM(bit);
    }
  }
  free(workmem);
  for(sInt i=0;i<5;i++)
    shiftLow();
  __asm__ volatile("emms");
  return sU32(outPtr - out);
}

// ---- decoder (with the zero blocks, like depacker.asm)

void Depack(sU8 *out,const sU8 *in,sU32 outSize)
{
  sU32 code=0,range=~0U,prob=2048,zeroProb=1;

  for(sInt i=0;i<4;i++)
    code = (code << 8) | *in++;
  memset(WorkData,0,workSize);   // modelInitASM expects zeroed memory
  modelInitASM();
  bufPtr = startBufPtr = out;

  for(sU32 pos=0;pos<outSize;pos++)
  {
    if((pos & 8191) == 0)
    {
      sU32 bound = mulShift12(range,zeroProb);
      sInt isZero;
      if(code < bound) { range = bound; isZero = 1; }
      else { code -= bound; range -= bound; isZero = 0; }
      while(range < 0x01000000) { code = (code << 8) | *in++; range <<= 8; }
      zeroProb = (zeroProb + (isZero ? 4096 : 1)) >> 1;
      if(isZero)
      {
        memset(bufPtr,0,8192);
        bufPtr += 8192;
        pos += 8192-1;
        continue;
      }
    }
    sInt byte = 0;
    for(sInt i=0;i<8;i++)
    {
      sInt bit;
      sU32 bound = mulShift12(range,prob);
      if(code < bound) { range = bound; bit = 1; }
      else { code -= bound; range -= bound; bit = 0; }
      byte += byte+bit;
      if(i == 7)
        *bufPtr++ = byte;
      while(range < 0x01000000) { code = (code << 8) | *in++; range <<= 8; }
      prob = modelASM(bit);
    }
  }
  __asm__ volatile("emms");
}

#include "disfilter.hpp"

static sU8 *ReadFile(const char *name,sU32 &size,sU32 slack)
{
  FILE *f = fopen(name,"rb");
  if(!f) { perror(name); exit(1); }
  fseek(f,0,SEEK_END); size = ftell(f); fseek(f,0,SEEK_SET);
  sU8 *d = (sU8 *) calloc(size+slack,1);
  if(fread(d,1,size,f) != size) { perror(name); exit(1); }
  fclose(f);
  return d;
}

static void WriteFile(const char *name,const void *d,sU32 size)
{
  FILE *f = fopen(name,"wb");
  if(!f || fwrite(d,1,size,f) != size) { perror(name); exit(1); }
  fclose(f);
}

// find a section of a 32-bit ELF by name
static bool FindSection(const sU8 *elf,sU32 size,const char *want,sU32 &off,sU32 &len)
{
  if(size < 52 || memcmp(elf,"\x7f" "ELF\x01",5)) return false;
  sU32 shoff; memcpy(&shoff,elf+32,4);
  sU16 shentsize,shnum,shstrndx;
  memcpy(&shentsize,elf+46,2); memcpy(&shnum,elf+48,2); memcpy(&shstrndx,elf+50,2);
  const sU8 *strsh = elf + shoff + shstrndx*shentsize;
  sU32 stroff; memcpy(&stroff,strsh+16,4);
  for(sInt i=0;i<shnum;i++)
  {
    const sU8 *sh = elf + shoff + i*shentsize;
    sU32 name; memcpy(&name,sh,4);
    if(!strcmp((const char *)elf+stroff+name,want))
    {
      memcpy(&off,sh+16,4); memcpy(&len,sh+20,4);
      return true;
    }
  }
  return false;
}

int main(int argc,char **argv)
{
  // model tuning (tools/kkpack/tune.py): KKPACK_MASKS = 2*NMODEL hex
  // bytes, the context masks then the byte masks of model.asm
  if(const char *m = getenv("KKPACK_MASKS"))
    for(sInt i=0;i<2*nmodel && m[2*i] && m[2*i+1];i++)
    {
      char h[3] = { m[2*i],m[2*i+1],0 };
      (i<nmodel ? masks[i] : bitm[i-nmodel]) = (sU8) strtoul(h,0,16);
    }
  if(argc==5 && !strcmp(argv[1],"-d"))    // kkpack -d packed out size
  {
    sU32 psize;
    sU8 *in = ReadFile(argv[2],psize,64);
    sU32 size = atoi(argv[4]);
    sU8 *out = (sU8 *) calloc(size+8192+32,1) + 32;   // zero bytes before, see Pack
    Depack(out,in,size);
    WriteFile(argv[3],out,size);
    return 0;
  }
  if(argc==5 && !strcmp(argv[1],"-x"))    // kkpack -x game.elf payload.bin payload.inc
  {
    // stream = [DisFilter tables (256)] [DisFilter(.text)] [file without .text]
    sU32 size,toff,tlen;
    sU8 *elf = ReadFile(argv[2],size,16);
    if(!FindSection(elf,size,".text",toff,tlen)) { fprintf(stderr,"%s: no .text\n",argv[2]); return 1; }
    // drop what only the linker/debuggers look at: everything behind the
    // last segment (non-alloc sections like .comment/.annobin.notes,
    // .shstrtab, the section header table)
    {
      sU32 phoff,end = 0; sU16 phentsize,phnum;
      memcpy(&phoff,elf+28,4); memcpy(&phentsize,elf+42,2); memcpy(&phnum,elf+44,2);
      for(sInt i=0;i<phnum;i++)
      {
        sU32 off,filesz;
        memcpy(&off,elf+phoff+i*phentsize+4,4);
        memcpy(&filesz,elf+phoff+i*phentsize+16,4);
        if(off+filesz > end) end = off+filesz;
      }
      if(end < toff+tlen || end > size) { fprintf(stderr,"%s: odd segment layout\n",argv[2]); return 1; }
      size = end;
      memset(elf+32,0,4);       // e_shoff
      memset(elf+46,0,6);       // e_shentsize, e_shnum, e_shstrndx
    }
    sU8 *stream = (sU8 *) calloc(size+tlen+1024,1);
    dis::DisPackTable(stream);
    sInt fsize = 256 + dis::DisFilter(elf+toff,tlen,stream+256);
    sU8 *check = (sU8 *) calloc(tlen+64,1);
    if(dis::DisUnfilter(stream+256,check) != (sInt)tlen || memcmp(check,elf+toff,tlen))
      { fprintf(stderr,"DisFilter roundtrip failed\n"); return 1; }
    memcpy(stream+fsize,elf,toff);
    memcpy(stream+fsize+toff,elf+toff+tlen,size-toff-tlen);
    sU32 usize = fsize + size - tlen;
    sU8 *out = (sU8 *) calloc(usize*2+1024,1);
    sU32 psize = Pack(stream,usize,out);
    WriteFile(argv[3],out,psize);
    if(!getenv("KKPACK_NOVERIFY"))      // tune.py: compressed size only
    {
      sU8 *dec = (sU8 *) calloc(usize+8192+64,1) + 32;
      Depack(dec,out,usize);
      if(memcmp(dec,stream,usize)) { fprintf(stderr,"depack check failed\n"); return 1; }
    }

    FILE *o = fopen(argv[4],"w");
    fprintf(o,"; generated by kkpack -x %s\n",argv[2]);
    fprintf(o,"%%define USIZE %u\n%%define FSIZE %d\n%%define TEXTOFF %u\n%%define TEXTSIZE %u\n%%define FILESIZE %u\n%%define PSIZE %u\n",
      usize,fsize,toff,tlen,size,psize);
    fclose(o);
    printf("%s: %u bytes (.text %u -> %d filtered) -> %u packed\n",argv[2],size,tlen,fsize-256,psize);
    return 0;
  }
  if(argc<3) { fprintf(stderr,"usage: kkpack in out | kkpack -d packed out size | kkpack -x elf payload inc\n"); return 1; }
  sU32 size;
  sU8 *in = ReadFile(argv[1],size,16);
  sU8 *out = (sU8 *) calloc(size*2+1024,1);
  sU32 psize = Pack(in,size,out);
  WriteFile(argv[2],out,psize);
  printf("%s: %u -> %u bytes (%.1f%%)\n",argv[1],size,psize,100.0*psize/size);
  return 0;
}
