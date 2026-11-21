// function coverage for the size work (lekktor-style, but only as a guide):
//   build with -fsanitize-coverage=func,trace-pc-guard and link this file;
//   every second (the game leaves with _exit) and on SIGTERM / SIGINT the
//   entry PCs of all executed functions are written to $KK_COVOUT (default
//   kkcov.txt), one hex address per line.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

static uintptr_t *pcs;
static uint32_t npcs;

static void dump()
{
  const char *name = getenv("KK_COVOUT");
  FILE *f = fopen(name ? name : "kkcov.txt","w");
  if(!f) return;
  for(uint32_t i=1;i<=npcs;i++)
    if(pcs[i]) fprintf(f,"%lx\n",(unsigned long)pcs[i]);
  fclose(f);
}

static void onsig(int) { dump(); _exit(0); }

static void *dumper(void *)
{
  for(;;) { sleep(1); dump(); }
  return 0;
}

extern "C" void __sanitizer_cov_trace_pc_guard_init(uint32_t *start,uint32_t *stop)
{
  if(start == stop || *start) return;
  for(uint32_t *x=start;x<stop;x++) *x = ++npcs;
  pcs = (uintptr_t *) calloc(npcs+1,sizeof(uintptr_t));
  atexit(dump);
  signal(SIGTERM,onsig);
  signal(SIGINT,onsig);
  pthread_t t;
  pthread_create(&t,0,dumper,0);
}

extern "C" void __sanitizer_cov_trace_pc_guard(uint32_t *guard)
{
  if(!*guard) return;
  pcs[*guard] = (uintptr_t) __builtin_return_address(0);
  *guard = 0;
}
