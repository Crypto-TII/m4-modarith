
#include <inttypes.h>
#include "hal.h"
               
#include "code_NIST256_monty.c"
               
#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#endif

void bench_modarith_modmul_NIST256_monty() {
    spint a[Nlimbs_NIST256_ct], b[Nlimbs_NIST256_ct], c[2 * Nlimbs_NIST256_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmul_NIST256_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("NIST256, monty, modarith, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsqr_NIST256_monty() {
    spint a[Nlimbs_NIST256_ct], c[2 * Nlimbs_NIST256_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modsqr_NIST256_ct(a, c);
    DoNotOptimize(c);
    bm_end();

    printf("NIST256, monty, modarith, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modadd_NIST256_monty() {
    spint a[Nlimbs_NIST256_ct], b[Nlimbs_NIST256_ct], c[Nlimbs_NIST256_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modadd_NIST256_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("NIST256, monty, modarith, modadd, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsub_NIST256_monty() {
    spint a[Nlimbs_NIST256_ct], b[Nlimbs_NIST256_ct], c[Nlimbs_NIST256_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modsub_NIST256_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("NIST256, monty, modarith, modsub, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}



void bench_modarith_NIST256_monty() {
    bench_modarith_modmul_NIST256_monty();
    bench_modarith_modsqr_NIST256_monty();
    bench_modarith_modadd_NIST256_monty();
    bench_modarith_modsub_NIST256_monty();
    
    printf("\n");
}
