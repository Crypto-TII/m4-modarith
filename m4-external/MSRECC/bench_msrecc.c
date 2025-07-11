#include <inttypes.h>

#include "fp.c"
#include "hal.h"

#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "r,m"(value) : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "m,r"(value) : "memory");
#endif


void bench_msrecc_256_mul() {
    dig256 a256, b256, c256;
    bm_decls;

    bm_start();
    DoNotOptimize(a256);
    DoNotOptimize(b256);
    fpmul256(a256, b256, c256);
    DoNotOptimize(c256);
    bm_end();

    printf("MSR256189, pmp, MSRECC, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_msrecc_256_sqr() {
    dig256 a256, c256;
    bm_decls;

    bm_start();
    DoNotOptimize(a256);
    fpsqr256(a256, c256);
    DoNotOptimize(c256);
    bm_end();

    printf("MSR256189, pmp, MSRECC, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_msrecc_384_mul() {
    dig384 a384, b384, c384;
    bm_decls;

    bm_start();
    DoNotOptimize(a384);
    DoNotOptimize(b384);
    fpmul384(a384, b384, c384);
    DoNotOptimize(c384);
    bm_end();

    printf("MSR384317, pmp, MSRECC, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_msrecc_384_sqr() {
    dig384 a384, c384;
    bm_decls;

    bm_start();
    DoNotOptimize(a384);
    fpsqr384(a384, c384);
    DoNotOptimize(c384);
    bm_end();

    printf("MSR384317, pmp, MSRECC, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_msrecc_512_mul() {
    dig512 a512, b512, c512;
    bm_decls;

    bm_start();
    DoNotOptimize(a512);
    DoNotOptimize(b512);
    fpmul512(a512, b512, c512);
    DoNotOptimize(c512);
    bm_end();

    printf("MSR512569, pmp, MSRECC, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_msrecc_512_sqr() {
    dig512 a512, c512;
    bm_decls;

    bm_start();
    DoNotOptimize(a512);
    fpsqr512(a512, c512);
    DoNotOptimize(c512);
    bm_end();

    printf("MSR512569, pmp, MSRECC, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_msrecc() {
    bench_msrecc_256_mul();
    bench_msrecc_256_sqr();
    printf("\n");
    bench_msrecc_384_mul();
    bench_msrecc_384_sqr();
    printf("\n");
    bench_msrecc_512_mul();
    bench_msrecc_512_sqr();
    printf("\n");
}