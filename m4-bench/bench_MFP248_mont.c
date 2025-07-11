
#include <inttypes.h>
#include "hal.h"

#include "m4-codegen/code_MFP248_mont.c"

#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "r,m"(value) : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "m,r"(value) : "memory");
#endif

static void bench_m4_modmul_MFP248_mont() {
    uint32_t a[Nlimbs_MFP248_ct], b[Nlimbs_MFP248_ct], c[2 * Nlimbs_MFP248_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmul_MFP248_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("MFP248, mont, M4, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}

static void bench_m4_modsqr_MFP248_mont() {
    uint32_t a[Nlimbs_MFP248_ct], c[2 * Nlimbs_MFP248_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modsqr_MFP248_ct(a, c);
    DoNotOptimize(c);
    bm_end();

    printf("MFP248, mont, M4, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}

static void bench_m4_modadd_MFP248_mont() {
    uint32_t a[Nlimbs_MFP248_ct], b[Nlimbs_MFP248_ct], c[Nlimbs_MFP248_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modadd_MFP248_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("MFP248, mont, M4, modadd, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}

static void bench_m4_modsub_MFP248_mont() {
    uint32_t a[Nlimbs_MFP248_ct], b[Nlimbs_MFP248_ct], c[Nlimbs_MFP248_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modsub_MFP248_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("MFP248, mont, M4, modsub, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}

static void bench_m4_modmli_MFP248_mont() {
    spint a[Nlimbs_MFP248_ct], b, c[Nlimbs_MFP248_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmli_MFP248_ct(a, b+2, c);
    DoNotOptimize(c);
    bm_end();

    printf("MFP248, mont, M4, modmli, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}


void bench_m4_MFP248_mont() {
    bench_m4_modmul_MFP248_mont();
    bench_m4_modsqr_MFP248_mont();
    bench_m4_modadd_MFP248_mont();
    bench_m4_modsub_MFP248_mont();
    bench_m4_modmli_MFP248_mont();
    
    printf("\n");
}
