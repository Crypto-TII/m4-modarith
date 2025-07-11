
#include <inttypes.h>
#include "hal.h"
               
#include "code_SECP256K1_monty.c"
               
#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#endif

void bench_modarith_modmul_SECP256K1_monty() {
    spint a[Nlimbs_SECP256K1_ct], b[Nlimbs_SECP256K1_ct], c[2 * Nlimbs_SECP256K1_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmul_SECP256K1_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("SECP256K1, monty, modarith, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsqr_SECP256K1_monty() {
    spint a[Nlimbs_SECP256K1_ct], c[2 * Nlimbs_SECP256K1_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modsqr_SECP256K1_ct(a, c);
    DoNotOptimize(c);
    bm_end();

    printf("SECP256K1, monty, modarith, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modadd_SECP256K1_monty() {
    spint a[Nlimbs_SECP256K1_ct], b[Nlimbs_SECP256K1_ct], c[Nlimbs_SECP256K1_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modadd_SECP256K1_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("SECP256K1, monty, modarith, modadd, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsub_SECP256K1_monty() {
    spint a[Nlimbs_SECP256K1_ct], b[Nlimbs_SECP256K1_ct], c[Nlimbs_SECP256K1_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modsub_SECP256K1_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("SECP256K1, monty, modarith, modsub, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}



void bench_modarith_SECP256K1_monty() {
    bench_modarith_modmul_SECP256K1_monty();
    bench_modarith_modsqr_SECP256K1_monty();
    bench_modarith_modadd_SECP256K1_monty();
    bench_modarith_modsub_SECP256K1_monty();
    
    printf("\n");
}
