
#include <inttypes.h>
#include "hal.h"
               
#include "code_MFP500_monty.c"
               
#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#endif

void bench_modarith_modmul_MFP500_monty() {
    spint a[Nlimbs_MFP500_ct], b[Nlimbs_MFP500_ct], c[2 * Nlimbs_MFP500_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmul_MFP500_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("MFP500, monty, modarith, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsqr_MFP500_monty() {
    spint a[Nlimbs_MFP500_ct], c[2 * Nlimbs_MFP500_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modsqr_MFP500_ct(a, c);
    DoNotOptimize(c);
    bm_end();

    printf("MFP500, monty, modarith, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modadd_MFP500_monty() {
    spint a[Nlimbs_MFP500_ct], b[Nlimbs_MFP500_ct], c[Nlimbs_MFP500_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modadd_MFP500_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("MFP500, monty, modarith, modadd, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsub_MFP500_monty() {
    spint a[Nlimbs_MFP500_ct], b[Nlimbs_MFP500_ct], c[Nlimbs_MFP500_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modsub_MFP500_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("MFP500, monty, modarith, modsub, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}



void bench_modarith_MFP500_monty() {
    bench_modarith_modmul_MFP500_monty();
    bench_modarith_modsqr_MFP500_monty();
    bench_modarith_modadd_MFP500_monty();
    bench_modarith_modsub_MFP500_monty();
    
    printf("\n");
}
