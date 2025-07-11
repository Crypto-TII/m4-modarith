#include <inttypes.h>

#include "hal.h"
#include "include/fe25519.h"

#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "r,m"(value) : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "m,r"(value) : "memory");
#endif

void bench_haase_c25519_mul() {
    fe25519 *out1;
    fe25519 *arg1, *arg2;
    bm_decls;

    bm_start();
    DoNotOptimize(arg1);
    DoNotOptimize(arg2);
    fe25519_mul_asm(out1, arg1, arg2);
    DoNotOptimize(out1);
    bm_end();

    printf("C25519, pmp, haase, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_haase_c25519_sqr() {
    fe25519 *out1;
    fe25519 *arg1;
    bm_decls;

    bm_start();
    DoNotOptimize(arg1);
    fe25519_square_asm(out1, arg1);
    DoNotOptimize(out1);
    bm_end();

    printf("C25519, pmp, haase, modsqr, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

void bench_haase_c25519() {
    bench_haase_c25519_mul();
    bench_haase_c25519_sqr();
    printf("\n");
}