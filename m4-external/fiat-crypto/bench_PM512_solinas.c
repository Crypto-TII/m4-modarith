#include <inttypes.h>

#include "hal.h"
#include "PM512_solinas.c"

#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "r,m"(value) : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "m,r"(value) : "memory");
#endif

void bench_fiat_solinas_PM512_add() {
    fiat_PM512_loose_field_element out1;
    fiat_PM512_tight_field_element arg1, arg2;
    bm_decls;

    bm_start();
    DoNotOptimize(arg1);
    DoNotOptimize(arg2);
    fiat_PM512_add(out1, arg1, arg2);
    DoNotOptimize(out1);
    bm_end();

    printf("PM512, unsaturated-solinas, Fiat_crypto, modadd, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_fiat_PM512_carry_square() {
    fiat_PM512_loose_field_element arg1;
    fiat_PM512_tight_field_element out1;
    bm_decls;

    bm_start();
    DoNotOptimize(arg1);
    fiat_PM512_carry_square(out1, arg1);
    DoNotOptimize(out1);
    bm_end();

    printf("PM512, unsaturated-solinas, Fiat_crypto, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_fiat_solinas_PM512_sub() {
    fiat_PM512_loose_field_element out1;
    fiat_PM512_tight_field_element arg1, arg2;
    bm_decls;

    bm_start();
    DoNotOptimize(arg1);
    DoNotOptimize(arg2);
    fiat_PM512_sub(out1, arg1, arg2);
    DoNotOptimize(out1);
    bm_end();

    printf("PM512, unsaturated-solinas, Fiat_crypto, modsub, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_fiat_PM512_carry_mul() {
    fiat_PM512_loose_field_element arg1, arg2;
    fiat_PM512_tight_field_element out1;
    bm_decls;

    bm_start();
    DoNotOptimize(arg1);
    DoNotOptimize(arg2);
    fiat_PM512_carry_mul(out1, arg1, arg2);
    DoNotOptimize(out1);
    bm_end();

    printf("PM512, unsaturated-solinas, Fiat_crypto, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_fiat_PM512_solinas() {
    bench_fiat_PM512_carry_mul();
    bench_fiat_PM512_carry_square();
    bench_fiat_solinas_PM512_add();
    bench_fiat_solinas_PM512_sub();
    printf("\n");
}