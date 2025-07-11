
#include <inttypes.h>
#include "hal.h"

#include "m4-codegen/code_C25519_pmp_asm.c"

#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "r,m"(value) : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "m,r"(value) : "memory");
#endif

static void bench_m4_modmul_C25519_pmp_asm() {
    uint32_t a[Nlimbs_C25519_ct], b[Nlimbs_C25519_ct], c[2 * Nlimbs_C25519_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmul_C25519_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("C25519, pmp_asm, M4, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}

static void bench_m4_modsqr_C25519_pmp_asm() {
    uint32_t a[Nlimbs_C25519_ct], c[2 * Nlimbs_C25519_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modsqr_C25519_ct(a, c);
    DoNotOptimize(c);
    bm_end();

    printf("C25519, pmp_asm, M4, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}

static void bench_m4_modadd_C25519_pmp_asm() {
    uint32_t a[Nlimbs_C25519_ct], b[Nlimbs_C25519_ct], c[Nlimbs_C25519_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modadd_C25519_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("C25519, pmp_asm, M4, modadd, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}

static void bench_m4_modsub_C25519_pmp_asm() {
    uint32_t a[Nlimbs_C25519_ct], b[Nlimbs_C25519_ct], c[Nlimbs_C25519_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modsub_C25519_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("C25519, pmp_asm, M4, modsub, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}

static void bench_m4_modmli_C25519_pmp_asm() {
    spint a[Nlimbs_C25519_ct], b, c[Nlimbs_C25519_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmli_C25519_ct(a, b+2, c);
    DoNotOptimize(c);
    bm_end();

    printf("C25519, pmp_asm, M4, modmli, cycles, %" PRIu32 "\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}


void bench_m4_C25519_pmp_asm() {
    bench_m4_modmul_C25519_pmp_asm();
    bench_m4_modsqr_C25519_pmp_asm();
    bench_m4_modadd_C25519_pmp_asm();
    bench_m4_modsub_C25519_pmp_asm();
    bench_m4_modmli_C25519_pmp_asm();
    
    printf("\n");
}
