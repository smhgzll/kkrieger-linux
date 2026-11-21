// This file is distributed under a BSD license. See LICENSE.txt for details.
//
// Import by hash (size build, see tools/mkimports.py): fills ImportTable
// before anything else runs (linux/start.asm). For each GNU hash in
// ImportHashes the loaded objects are searched in load order, like the
// dynamic linker does, through their own GNU hash tables: the bucket of the
// hash, then its chain. Hidden (old) symbol versions are skipped, indirect
// functions (glibc's memcpy & co.) are asked for their implementation.
// Data imports (stderr) get the variable's value.
//
// No library function may be called here: nothing is resolved yet.

#include <elf.h>
#include <link.h>

extern "C"
{
  extern const int ImportCount;
  extern const unsigned ImportHashes[];
  extern const int ImportData[];          // index, variable, ..., -1
  extern void *ImportTable[];
  void ResolveImports();                  // (_DYNAMIC: link.h)
}

void ResolveImports()
{
  r_debug *debug = 0;
  for(ElfW(Dyn) *d=_DYNAMIC;d->d_tag;d++)
    if(d->d_tag==DT_DEBUG)
      debug = (r_debug *) d->d_un.d_ptr;

  for(int i=0;i<ImportCount;i++)
  {
    unsigned h = ImportHashes[i];
    for(link_map *l=debug->r_map;l && !ImportTable[i];l=l->l_next)
    {
      const unsigned *gh = 0;
      const ElfW(Sym) *sym = 0;
      const ElfW(Half) *ver = 0;
      for(ElfW(Dyn) *d=l->l_ld;d->d_tag;d++)
      {
        ElfW(Addr) p = d->d_un.d_ptr;
        if(p<l->l_addr) p += l->l_addr;   // ld.so relocated most of these in place
        if(d->d_tag==DT_GNU_HASH) gh = (const unsigned *) p;
        if(d->d_tag==DT_SYMTAB)   sym = (const ElfW(Sym) *) p;
        if(d->d_tag==DT_VERSYM)   ver = (const ElfW(Half) *) p;
      }
      if(!gh) continue;
      const unsigned *bucket = gh+4+gh[2];            // nbuckets, symoffset, bloom size, bloom shift, bloom
      const unsigned *chain = bucket+gh[0]-gh[1];
      for(unsigned k=bucket[h%gh[0]];k;k++)
      {
        if(!((chain[k]^h)>>1) && !(ver && (ver[k]&0x8000)))
        {
          void *a = (void *)(l->l_addr+sym[k].st_value);
          if(ELF32_ST_TYPE(sym[k].st_info)==STT_GNU_IFUNC)
            a = ((void *(*)()) a)();
          ImportTable[i] = a;
          break;
        }
        if(chain[k]&1) break;
      }
    }
  }
  for(const int *d=ImportData;*d>=0;d+=2)
    *(unsigned *)d[1] = *(unsigned *)ImportTable[d[0]];
}
