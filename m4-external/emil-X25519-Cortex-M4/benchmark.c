#include <inttypes.h>
#include <stdio.h>

#include "hal.h"
#include "x25519-cortex-m4.h"

#define Nbytes 32
#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "r,m"(value) : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "m,r"(value) : "memory");
#endif

#if !defined(EXTERNAL_EMIL_X25519_M4) && !defined(EXTERNAL_EMIL_X25519_M4F)
#error Please #define either EXTERNAL_EMIL_X25519_M4 or EXTERNAL_EMIL_X25519_M4F.
#endif

#ifdef EXTERNAL_EMIL_X25519_M4
void bench_external_emil_x25519_m4_rfc7748_C25519(void) {
#elif defined EXTERNAL_EMIL_X25519_M4F
void bench_external_emil_x25519_m4f_rfc7748_C25519(void) {
#endif
    char bk[Nbytes], bu[Nbytes], bv[Nbytes];
    bm_decls;

    bm_start();
    DoNotOptimize(bk);
    DoNotOptimize(bu);
#ifdef EXTERNAL_EMIL_X25519_M4
    curve25519_scalarmult_m4((unsigned char *)bv, (unsigned char *)bk, (unsigned char *)bu);
#elif defined EXTERNAL_EMIL_X25519_M4F
    curve25519_scalarmult_m4f((unsigned char *)bv, (unsigned char *)bk, (unsigned char *)bu);
#endif
    DoNotOptimize(bv);
    bm_end();

#ifdef EXTERNAL_EMIL_X25519_M4
    printf("C25519, pseudo, emil-m4, RFC7748, cycles, %" PRIu32 "\n\n", bm_result());
#elif defined EXTERNAL_EMIL_X25519_M4F
    printf("C25519, pseudo, emil-m4f, RFC7748, cycles, %" PRIu32 "\n\n", bm_result());
#endif

    usleep(10000);  // To avoid SWO buffer overflows
}
