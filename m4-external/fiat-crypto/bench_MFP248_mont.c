#include <inttypes.h>

#include "MFP248_mont.c"
#include "hal.h"

#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "r,m"(value) : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "m,r"(value) : "memory");
#endif

void bench_fiat_MFP248_add() {
    fiat_MFP248_montgomery_domain_field_element out1;
    fiat_MFP248_montgomery_domain_field_element arg1, arg2;
    bm_decls;

    bm_start();
    DoNotOptimize(arg1);
    DoNotOptimize(arg2);
    fiat_MFP248_add(out1, arg1, arg2);
    DoNotOptimize(out1);
    bm_end();

    printf("MFP248, mont, Fiat_crypto, modadd, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_fiat_MFP248_square() {
    fiat_MFP248_montgomery_domain_field_element out1;
    fiat_MFP248_montgomery_domain_field_element arg1;
    bm_decls;

    bm_start();
    DoNotOptimize(arg1);
    fiat_MFP248_square(out1, arg1);
    DoNotOptimize(out1);
    bm_end();

    printf("MFP248, mont, Fiat_crypto, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_fiat_MFP248_sub() {
    fiat_MFP248_montgomery_domain_field_element out1;
    fiat_MFP248_montgomery_domain_field_element arg1, arg2;
    bm_decls;

    bm_start();
    DoNotOptimize(arg1);
    DoNotOptimize(arg2);
    fiat_MFP248_sub(out1, arg1, arg2);
    DoNotOptimize(out1);
    bm_end();

    printf("MFP248, mont, Fiat_crypto, modsub, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_fiat_MFP248_mul() {
    fiat_MFP248_montgomery_domain_field_element out1;
    fiat_MFP248_montgomery_domain_field_element arg1, arg2;
    bm_decls;

    bm_start();
    DoNotOptimize(arg1);
    DoNotOptimize(arg2);
    fiat_MFP248_mul(out1, arg1, arg2);
    DoNotOptimize(out1);
    bm_end();

    printf("MFP248, mont, Fiat_crypto, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_fiat_MFP248_mont() {
    bench_fiat_MFP248_mul();
    bench_fiat_MFP248_square();
    bench_fiat_MFP248_add();
    bench_fiat_MFP248_sub();
    printf("\n");
}