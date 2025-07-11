
#include <inttypes.h>
#include "hal.h"
               
#include "code_PM383_monty.c"
               
#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#endif

void bench_modarith_modmul_PM383_monty() {
    spint a[Nlimbs_PM383_ct], b[Nlimbs_PM383_ct], c[2 * Nlimbs_PM383_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmul_PM383_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("PM383, monty, modarith, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsqr_PM383_monty() {
    spint a[Nlimbs_PM383_ct], c[2 * Nlimbs_PM383_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modsqr_PM383_ct(a, c);
    DoNotOptimize(c);
    bm_end();

    printf("PM383, monty, modarith, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modadd_PM383_monty() {
    spint a[Nlimbs_PM383_ct], b[Nlimbs_PM383_ct], c[Nlimbs_PM383_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modadd_PM383_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("PM383, monty, modarith, modadd, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsub_PM383_monty() {
    spint a[Nlimbs_PM383_ct], b[Nlimbs_PM383_ct], c[Nlimbs_PM383_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modsub_PM383_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("PM383, monty, modarith, modsub, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}



void bench_modarith_PM383_monty() {
    bench_modarith_modmul_PM383_monty();
    bench_modarith_modsqr_PM383_monty();
    bench_modarith_modadd_PM383_monty();
    bench_modarith_modsub_PM383_monty();
    
    printf("\n");
}
