
#include <inttypes.h>
#include "hal.h"
               
#include "code_NIST521_monty.c"
               
#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#endif

void bench_modarith_modmul_NIST521_monty() {
    spint a[Nlimbs_NIST521_ct], b[Nlimbs_NIST521_ct], c[2 * Nlimbs_NIST521_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmul_NIST521_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("NIST521, monty, modarith, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsqr_NIST521_monty() {
    spint a[Nlimbs_NIST521_ct], c[2 * Nlimbs_NIST521_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modsqr_NIST521_ct(a, c);
    DoNotOptimize(c);
    bm_end();

    printf("NIST521, monty, modarith, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modadd_NIST521_monty() {
    spint a[Nlimbs_NIST521_ct], b[Nlimbs_NIST521_ct], c[Nlimbs_NIST521_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modadd_NIST521_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("NIST521, monty, modarith, modadd, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsub_NIST521_monty() {
    spint a[Nlimbs_NIST521_ct], b[Nlimbs_NIST521_ct], c[Nlimbs_NIST521_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modsub_NIST521_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("NIST521, monty, modarith, modsub, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}



void bench_modarith_NIST521_monty() {
    bench_modarith_modmul_NIST521_monty();
    bench_modarith_modsqr_NIST521_monty();
    bench_modarith_modadd_NIST521_monty();
    bench_modarith_modsub_NIST521_monty();
    
    printf("\n");
}
