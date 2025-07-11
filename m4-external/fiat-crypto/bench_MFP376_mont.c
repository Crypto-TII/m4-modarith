#include <inttypes.h>

#include "MFP376_mont.c"
#include "hal.h"

#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "r,m"(value) : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "m,r"(value) : "memory");
#endif

void bench_fiat_MFP376_add() {
    fiat_MFP376_montgomery_domain_field_element out1;
    fiat_MFP376_montgomery_domain_field_element arg1, arg2;
    bm_decls;

    bm_start();
    DoNotOptimize(arg1);
    DoNotOptimize(arg2);
    fiat_MFP376_add(out1, arg1, arg2);
    DoNotOptimize(out1);
    bm_end();

    printf("MFP376, mont, Fiat_crypto, modadd, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_fiat_MFP376_square() {
    fiat_MFP376_montgomery_domain_field_element out1;
    fiat_MFP376_montgomery_domain_field_element arg1;
    bm_decls;

    bm_start();
    DoNotOptimize(arg1);
    fiat_MFP376_square(out1, arg1);
    DoNotOptimize(out1);
    bm_end();

    printf("MFP376, mont, Fiat_crypto, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_fiat_MFP376_sub() {
    fiat_MFP376_montgomery_domain_field_element out1;
    fiat_MFP376_montgomery_domain_field_element arg1, arg2;
    bm_decls;

    bm_start();
    DoNotOptimize(arg1);
    DoNotOptimize(arg2);
    fiat_MFP376_sub(out1, arg1, arg2);
    DoNotOptimize(out1);
    bm_end();

    printf("MFP376, mont, Fiat_crypto, modsub, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_fiat_MFP376_mul() {
    fiat_MFP376_montgomery_domain_field_element out1;
    fiat_MFP376_montgomery_domain_field_element arg1, arg2;
    bm_decls;

    bm_start();
    DoNotOptimize(arg1);
    DoNotOptimize(arg2);
    fiat_MFP376_mul(out1, arg1, arg2);
    DoNotOptimize(out1);
    bm_end();

    printf("MFP376, mont, Fiat_crypto, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_fiat_MFP376_mont() {
    bench_fiat_MFP376_mul();
    bench_fiat_MFP376_square();
    bench_fiat_MFP376_add();
    bench_fiat_MFP376_sub();
    printf("\n");
}