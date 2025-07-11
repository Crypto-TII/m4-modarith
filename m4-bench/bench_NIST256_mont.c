
#include <inttypes.h>
#include "hal.h"

#include "m4-codegen/code_NIST256_mont.c"

#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "r,m"(value) : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "m,r"(value) : "memory");
#endif

static void bench_m4_modmul_NIST256_mont() {
    uint32_t a[Nlimbs_NIST256_ct], b[Nlimbs_NIST256_ct], c[2 * Nlimbs_NIST256_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmul_NIST256_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("NIST256, mont, M4, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}

static void bench_m4_modsqr_NIST256_mont() {
    uint32_t a[Nlimbs_NIST256_ct], c[2 * Nlimbs_NIST256_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modsqr_NIST256_ct(a, c);
    DoNotOptimize(c);
    bm_end();

    printf("NIST256, mont, M4, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}

static void bench_m4_modadd_NIST256_mont() {
    uint32_t a[Nlimbs_NIST256_ct], b[Nlimbs_NIST256_ct], c[Nlimbs_NIST256_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modadd_NIST256_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("NIST256, mont, M4, modadd, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}

static void bench_m4_modsub_NIST256_mont() {
    uint32_t a[Nlimbs_NIST256_ct], b[Nlimbs_NIST256_ct], c[Nlimbs_NIST256_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modsub_NIST256_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("NIST256, mont, M4, modsub, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}

static void bench_m4_modmli_NIST256_mont() {
    spint a[Nlimbs_NIST256_ct], b, c[Nlimbs_NIST256_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmli_NIST256_ct(a, b+2, c);
    DoNotOptimize(c);
    bm_end();

    printf("NIST256, mont, M4, modmli, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}


void bench_m4_NIST256_mont() {
    bench_m4_modmul_NIST256_mont();
    bench_m4_modsqr_NIST256_mont();
    bench_m4_modadd_NIST256_mont();
    bench_m4_modsub_NIST256_mont();
    bench_m4_modmli_NIST256_mont();
    
    printf("\n");
}
