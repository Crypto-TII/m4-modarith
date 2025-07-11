
#include <inttypes.h>
#include "hal.h"
               
#include "code_MFP376_monty.c"
               
#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#endif

void bench_modarith_modmul_MFP376_monty() {
    spint a[Nlimbs_MFP376_ct], b[Nlimbs_MFP376_ct], c[2 * Nlimbs_MFP376_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmul_MFP376_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("MFP376, monty, modarith, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsqr_MFP376_monty() {
    spint a[Nlimbs_MFP376_ct], c[2 * Nlimbs_MFP376_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modsqr_MFP376_ct(a, c);
    DoNotOptimize(c);
    bm_end();

    printf("MFP376, monty, modarith, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modadd_MFP376_monty() {
    spint a[Nlimbs_MFP376_ct], b[Nlimbs_MFP376_ct], c[Nlimbs_MFP376_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modadd_MFP376_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("MFP376, monty, modarith, modadd, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsub_MFP376_monty() {
    spint a[Nlimbs_MFP376_ct], b[Nlimbs_MFP376_ct], c[Nlimbs_MFP376_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modsub_MFP376_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("MFP376, monty, modarith, modsub, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}



void bench_modarith_MFP376_monty() {
    bench_modarith_modmul_MFP376_monty();
    bench_modarith_modsqr_MFP376_monty();
    bench_modarith_modadd_MFP376_monty();
    bench_modarith_modsub_MFP376_monty();
    
    printf("\n");
}
