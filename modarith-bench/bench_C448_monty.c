
#include <inttypes.h>
#include "hal.h"
               
#include "code_C448_monty.c"
               
#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#endif

void bench_modarith_modmul_C448_monty() {
    spint a[Nlimbs_C448_ct], b[Nlimbs_C448_ct], c[2 * Nlimbs_C448_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmul_C448_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("C448, monty, modarith, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsqr_C448_monty() {
    spint a[Nlimbs_C448_ct], c[2 * Nlimbs_C448_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modsqr_C448_ct(a, c);
    DoNotOptimize(c);
    bm_end();

    printf("C448, monty, modarith, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modadd_C448_monty() {
    spint a[Nlimbs_C448_ct], b[Nlimbs_C448_ct], c[Nlimbs_C448_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modadd_C448_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("C448, monty, modarith, modadd, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsub_C448_monty() {
    spint a[Nlimbs_C448_ct], b[Nlimbs_C448_ct], c[Nlimbs_C448_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modsub_C448_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("C448, monty, modarith, modsub, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}



void bench_modarith_C448_monty() {
    bench_modarith_modmul_C448_monty();
    bench_modarith_modsqr_C448_monty();
    bench_modarith_modadd_C448_monty();
    bench_modarith_modsub_C448_monty();
    
    printf("\n");
}
