
#include <inttypes.h>
#include "hal.h"
               
#include "code_PM266_pseudo.c"
               
#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#endif

void bench_modarith_modmul_PM266_pseudo() {
    spint a[Nlimbs_PM266_ct], b[Nlimbs_PM266_ct], c[2 * Nlimbs_PM266_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmul_PM266_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("PM266, pseudo, modarith, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsqr_PM266_pseudo() {
    spint a[Nlimbs_PM266_ct], c[2 * Nlimbs_PM266_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modsqr_PM266_ct(a, c);
    DoNotOptimize(c);
    bm_end();

    printf("PM266, pseudo, modarith, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modadd_PM266_pseudo() {
    spint a[Nlimbs_PM266_ct], b[Nlimbs_PM266_ct], c[Nlimbs_PM266_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modadd_PM266_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("PM266, pseudo, modarith, modadd, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}

void bench_modarith_modsub_PM266_pseudo() {
    spint a[Nlimbs_PM266_ct], b[Nlimbs_PM266_ct], c[Nlimbs_PM266_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modsub_PM266_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("PM266, pseudo, modarith, modsub, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}


void bench_modarith_modmli_PM266_pseudo() {
    spint a[Nlimbs_PM266_ct], b, c[Nlimbs_PM266_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmli_PM266_ct(a, b+2, c);
    DoNotOptimize(c);
    bm_end();

    printf("PM266, pseudo, modarith, modmli, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}


void bench_modarith_PM266_pseudo() {
    bench_modarith_modmul_PM266_pseudo();
    bench_modarith_modsqr_PM266_pseudo();
    bench_modarith_modadd_PM266_pseudo();
    bench_modarith_modsub_PM266_pseudo();
    bench_modarith_modmli_PM266_pseudo();
    printf("\n");
}
