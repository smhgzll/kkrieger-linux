// basic block coverage (lekktor-style guide for the size work):
//   build with -fsanitize-coverage=trace-pc-guard,pc-table and link this file;
//   every second / on SIGTERM writes "pc hit" for every instrumented block to
//   $KK_COVOUT (default kkcovbb.txt). Map with addr2line -f -e <binary>.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

static uint8_t *hit;
static const uintptr_t *pcs;
static uint32_t npcs,nguards;

static void dump()
{
  const char *name = getenv("KK_COVOUT");
  FILE *f = fopen(name ? name : "kkcovbb.txt","w");
  if(!f) return;
  for(uint32_t i=0;i<npcs;i++)
    fprintf(f,"%lx %d\n",(unsigned long)pcs[i*2],hit[i+1]);
  fclose(f);
}

static void onsig(int) { dump(); _exit(0); }
static void *dumper(void *) { for(;;) { sleep(1); dump(); } return 0; }

extern "C" void __sanitizer_cov_trace_pc_guard_init(uint32_t *start,uint32_t *stop)
{
  if(start == stop || *start) return;
  for(uint32_t *x=start;x<stop;x++) *x = ++nguards;
  hit = (uint8_t *) calloc(nguards+1,1);
}

extern "C" void __sanitizer_cov_pcs_init(const uintptr_t *beg,const uintptr_t *end)
{
  pcs = beg;
  npcs = (uint32_t)((end-beg)/2);
  signal(SIGTERM,onsig);
  signal(SIGINT,onsig);
  pthread_t t;
  pthread_create(&t,0,dumper,0);
}

extern "C" void __sanitizer_cov_trace_pc_guard(uint32_t *guard)
{
  hit[*guard] = 1;
}
