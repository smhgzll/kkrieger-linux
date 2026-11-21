// kxconv: convert the V2 tunes of a 2004 .kx export to the format of the
// newer V2 synth in this source tree, offline. KDoc::Init does the same at
// load time; the size build embeds the converted file instead and drops the
// converter (V2ConvertSong + its parameter tables).
//
//   kxconv in.kx out.kx
//
// File layout (KDoc::Init): song size, song, pad to 4, fx size, fx block,
// pad to 4, rest. The fx block is VFX0 | v2m size | v2m | tail.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t sU8;
typedef uint32_t sU32;
typedef int sInt;

sU8 *V2ConvertSong(const sU8 *in,sInt inlen,sInt &outlen);

static sU32 Align4(sU32 x) { return (x+3)&~3u; }

int main(int argc,char **argv)
{
  if(argc!=3) { fprintf(stderr,"usage: kxconv in.kx out.kx\n"); return 1; }
  FILE *f = fopen(argv[1],"rb");
  if(!f) { perror(argv[1]); return 1; }
  fseek(f,0,SEEK_END); sU32 size = ftell(f); fseek(f,0,SEEK_SET);
  sU8 *d = (sU8 *) malloc(size);
  if(fread(d,1,size,f)!=size) { perror(argv[1]); return 1; }
  fclose(f);

  sU8 *p = d;
  sU32 songSize; memcpy(&songSize,p,4); p += 4;
  sU8 *song = p; p += Align4(songSize);
  sU32 fxSize; memcpy(&fxSize,p,4); p += 4;
  sU8 *fx = p; p += Align4(fxSize);
  sU8 *rest = p;
  sU32 restSize = size - sU32(rest-d);

  sInt newSongSize;
  sU8 *newSong = V2ConvertSong(song,songSize,newSongSize);
  if(!newSong) { fprintf(stderr,"song conversion failed\n"); return 1; }

  sU8 *newFx = fx;
  sU32 newFxSize = fxSize;
  sU32 v2size;
  if(fxSize>=12 && !memcmp(fx,"VFX0",4) && (memcpy(&v2size,fx+4,4),v2size<=fxSize-8))
  {
    sInt len;
    sU8 *conv = V2ConvertSong(fx+8,v2size,len);
    if(!conv) { fprintf(stderr,"fx conversion failed\n"); return 1; }
    sU32 tail = fxSize-(8+v2size);
    newFxSize = 8+len+tail;
    newFx = (sU8 *) malloc(newFxSize);
    memcpy(newFx,fx,4);
    memcpy(newFx+4,&len,4);
    memcpy(newFx+8,conv,len);
    memcpy(newFx+8+len,fx+8+v2size,tail);
  }

  FILE *o = fopen(argv[2],"wb");
  static const sU8 zero[4] = {0,0,0,0};
  fwrite(&newSongSize,4,1,o); fwrite(newSong,1,newSongSize,o); fwrite(zero,1,Align4(newSongSize)-newSongSize,o);
  fwrite(&newFxSize,4,1,o); fwrite(newFx,1,newFxSize,o); fwrite(zero,1,Align4(newFxSize)-newFxSize,o);
  fwrite(rest,1,restSize,o);
  fclose(o);
  printf("%s: song %u -> %d, fx %u -> %u\n",argv[2],songSize,newSongSize,fxSize,newFxSize);
  return 0;
}
