/*
 * kkrunpack - native kkrunchy unpacker for Linux (i386 process).
 *
 * Maps the packed PE at its preferred ImageBase, fakes the Windows loader
 * (LoadLibraryA / GetProcAddress), runs the original kkrunchy depacker stub
 * natively and single-steps the second stage with the trap flag until the
 * original entry point (OEP) is reached. Then the whole image is dumped.
 *
 * Build: gcc -m32 -O1 -o kkrunpack kkrunpack.c
 * Usage: kkrunpack packed.exe outdir
 *
 * Output: outdir/image.bin   ImageBase..ImageBase+SizeOfImage at OEP
 *         outdir/imports.txt "<slot_addr> <dll> <func>" for every IAT slot
 *         outdir/info.txt    image base, size, OEP
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <ucontext.h>
#include <sys/mman.h>
#include <ctype.h>

#define TRAP_BASE 0x60000000u
#define MAX_IMP 4096

static uint32_t g_base, g_size, g_entry;
static char g_out[512];

static struct { char dll[64]; char name[96]; } g_imp[MAX_IMP];
static int g_nimp;
static char g_mods[64][64];
static int g_nmods;

static uint32_t g_stage2;          /* return address of stage 1 */
static uint32_t g_stub_lo, g_stub_hi;
static int g_stepping;
static uint64_t g_steps;

static void *__attribute__((stdcall)) fake_LoadLibraryA(const char *name)
{
    int i;
    for (i = 0; i < g_nmods; i++)
        if (!strcasecmp(g_mods[i], name)) return (void *)(uintptr_t)(0x10000000u + i * 0x10000u);
    snprintf(g_mods[g_nmods], 64, "%s", name);
    for (char *p = g_mods[g_nmods]; *p; p++) *p = toupper((unsigned char)*p);
    fprintf(stderr, "LoadLibraryA(%s)\n", name);
    return (void *)(uintptr_t)(0x10000000u + (g_nmods++) * 0x10000u);
}

static void *__attribute__((stdcall)) fake_GetProcAddress(void *h, const char *name)
{
    int m = ((uint32_t)(uintptr_t)h - 0x10000000u) / 0x10000u;
    int i = g_nimp++;
    snprintf(g_imp[i].dll, 64, "%s", (m >= 0 && m < g_nmods) ? g_mods[m] : "?");
    if ((uintptr_t)name < 0x10000)
        snprintf(g_imp[i].name, 96, "#%u", (unsigned)(uintptr_t)name);
    else
        snprintf(g_imp[i].name, 96, "%s", name);
    return (void *)(uintptr_t)(TRAP_BASE + i * 16);
}

static void dump_and_exit(uint32_t oep)
{
    char path[600];
    FILE *f;
    snprintf(path, sizeof path, "%s/image.bin", g_out);
    f = fopen(path, "wb");
    fwrite((void *)(uintptr_t)g_base, 1, g_size, f);
    fclose(f);

    snprintf(path, sizeof path, "%s/imports.txt", g_out);
    f = fopen(path, "w");
    /* locate IAT slots: scan image for trap addresses */
    for (uint32_t a = g_base; a + 4 <= g_base + g_size; a += 4) {
        uint32_t v = *(uint32_t *)(uintptr_t)a;
        if (v >= TRAP_BASE && v < TRAP_BASE + MAX_IMP * 16 && !(v & 15)) {
            int i = (v - TRAP_BASE) / 16;
            if (i < g_nimp) fprintf(f, "%08x %s %s\n", a, g_imp[i].dll, g_imp[i].name);
        }
    }
    fclose(f);

    snprintf(path, sizeof path, "%s/info.txt", g_out);
    f = fopen(path, "w");
    fprintf(f, "image_base %08x\nsize_image %08x\noep %08x\nstage2 %08x\nsteps %llu\nimports %d\n",
            g_base, g_size, oep, g_stage2, (unsigned long long)g_steps, g_nimp);
    fclose(f);
    fprintf(stderr, "OEP = %08x after %llu single steps, %d imports\n", oep,
            (unsigned long long)g_steps, g_nimp);
    _exit(0);
}

static void on_trap(int sig, siginfo_t *si, void *ctx)
{
    ucontext_t *uc = ctx;
    greg_t *r = uc->uc_mcontext.gregs;
    uint32_t eip = r[REG_EIP];
    (void)si;

    if (!g_stepping) {
        /* int3 we planted on stage 1's final "ret" (eip is past the 0xCC) */
        uint32_t esp = r[REG_ESP];
        g_stage2 = *(uint32_t *)(uintptr_t)esp;
        r[REG_ESP] = esp + 4;
        r[REG_EIP] = g_stage2;
        r[REG_EFL] |= 0x100;          /* TF: single step from now on */
        g_stepping = 1;
        fprintf(stderr, "stage 1 done, stage 2 at %08x\n", g_stage2);
        return;
    }
    g_steps++;
    /* OEP: first instruction executed outside the depacker areas. Stage-2
     * code lives right where stage 1 decompressed it (g_stage2..), stage 1
     * lives in [g_stub_lo,g_stub_hi). The real code starts at base+0x1000. */
    if (eip >= g_base + 0x1000 && eip < g_base + g_size &&
        !(eip >= g_stub_lo && eip < g_stub_hi) &&
        !(eip >= g_stage2 && eip < g_stage2 + 0x2000))
        dump_and_exit(eip);
    if (eip >= TRAP_BASE && eip < TRAP_BASE + MAX_IMP * 16) {
        fprintf(stderr, "API %s!%s called before OEP detection\n",
                g_imp[(eip - TRAP_BASE) / 16].dll, g_imp[(eip - TRAP_BASE) / 16].name);
        dump_and_exit(0);
    }
    r[REG_EFL] |= 0x100;
}

static void on_segv(int sig, siginfo_t *si, void *ctx)
{
    ucontext_t *uc = ctx;
    fprintf(stderr, "signal %d at eip=%08x addr=%p\n", sig,
            (unsigned)uc->uc_mcontext.gregs[REG_EIP], si->si_addr);
    _exit(2);
}

int main(int argc, char **argv)
{
    FILE *f;
    long len;
    uint8_t *d;
    uint32_t pe, opt, optsz, nsec, imp_rva, size_hdrs, i;

    if (argc < 3) { fprintf(stderr, "usage: %s packed.exe outdir\n", argv[0]); return 1; }
    snprintf(g_out, sizeof g_out, "%s", argv[2]);
    f = fopen(argv[1], "rb");
    if (!f) { perror(argv[1]); return 1; }
    fseek(f, 0, SEEK_END); len = ftell(f); fseek(f, 0, SEEK_SET);
    d = malloc(len); fread(d, 1, len, f); fclose(f);

    pe = *(uint32_t *)(d + 0x3c);
    nsec = *(uint16_t *)(d + pe + 6);
    optsz = *(uint16_t *)(d + pe + 20);
    opt = pe + 24;
    g_entry = *(uint32_t *)(d + opt + 16);
    g_base = *(uint32_t *)(d + opt + 28);
    g_size = *(uint32_t *)(d + opt + 56);
    size_hdrs = *(uint32_t *)(d + opt + 60);
    imp_rva = *(uint32_t *)(d + opt + 96 + 8);

    if (mmap((void *)(uintptr_t)g_base, g_size, PROT_READ | PROT_WRITE | PROT_EXEC,
             MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0) == MAP_FAILED) {
        perror("mmap image"); return 1;
    }
    if (mmap((void *)(uintptr_t)TRAP_BASE, MAX_IMP * 16, PROT_READ | PROT_EXEC,
             MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0) == MAP_FAILED) {
        perror("mmap traps"); return 1;
    }
    memcpy((void *)(uintptr_t)g_base, d, size_hdrs);
    for (i = 0; i < nsec; i++) {
        uint8_t *s = d + opt + optsz + i * 40;
        uint32_t va = *(uint32_t *)(s + 12), rs = *(uint32_t *)(s + 16), ro = *(uint32_t *)(s + 20);
        memcpy((void *)(uintptr_t)(g_base + va), d + ro, rs);
        g_stub_hi = g_base + va + rs;
    }
    /* the stub's own import directory: fill its IAT */
    for (uint32_t off = imp_rva;; off += 20) {
        uint32_t *desc = (uint32_t *)(uintptr_t)(g_base + off);
        if (!desc[3]) break;
        uint32_t *thunk = (uint32_t *)(uintptr_t)(g_base + (desc[0] ? desc[0] : desc[4]));
        uint32_t *iat = (uint32_t *)(uintptr_t)(g_base + desc[4]);
        for (int k = 0; thunk[k]; k++) {
            const char *fn = (const char *)(uintptr_t)(g_base + thunk[k] + 2);
            if (!strcmp(fn, "LoadLibraryA")) iat[k] = (uint32_t)(uintptr_t)fake_LoadLibraryA;
            else if (!strcmp(fn, "GetProcAddress")) iat[k] = (uint32_t)(uintptr_t)fake_GetProcAddress;
            else { fprintf(stderr, "unexpected stub import %s\n", fn); return 1; }
        }
    }

    /* plant int3 on stage 1's final 'ret' (found by disassembly: pop ebp; ret) */
    {
        uint32_t ret_at = strtoul(argc > 3 ? argv[3] : "7d7aef", 0, 16);
        *(uint8_t *)(uintptr_t)ret_at = 0xCC;
    }

    struct sigaction sa = {0};
    sa.sa_sigaction = on_trap; sa.sa_flags = SA_SIGINFO;
    sigaction(SIGTRAP, &sa, 0);
    sa.sa_sigaction = on_segv;
    sigaction(SIGSEGV, &sa, 0);
    sigaction(SIGILL, &sa, 0);
    sigaction(SIGBUS, &sa, 0);

    g_stub_lo = g_base + g_entry;
    fprintf(stderr, "image %08x+%08x entry %08x\n", g_base, g_size, g_base + g_entry);
    ((void (*)(void))(uintptr_t)(g_base + g_entry))();
    fprintf(stderr, "stub returned?!\n");
    return 3;
}
