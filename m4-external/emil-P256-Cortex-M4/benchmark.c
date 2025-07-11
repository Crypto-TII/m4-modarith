#include <inttypes.h>
#include <stdio.h>

#include "hal.h"
#include "p256-cortex-m4.h"

#define Nbytes 32
#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "r,m"(value) : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "m,r"(value) : "memory");
#endif

#if !defined(EXTERNAL_EMIL_P256_M4) && !defined(EXTERNAL_EMIL_P256_M4F)
#error Please #define either EXTERNAL_EMIL_X25519_M4 or EXTERNAL_EMIL_X25519_M4F.
#endif

#ifdef EXTERNAL_EMIL_P256_M4
void bench_external_emil_p256_m4(void) {
#elif defined EXTERNAL_EMIL_P256_M4F
void bench_external_emil_p256_m4f(void) {
#endif
    uint32_t public_key_x1[8], public_key_y1[8], private_key1[8] = {0};
    uint32_t public_key_x2[8], public_key_y2[8], private_key2[8] = {0};
    uint8_t shared_secret[32];
    bool ret;
    bm_decls;

    for (int i = 0; i < 32; i++) {
        private_key1[i / 4] |= ((uint32_t)rand() & 0xFF) << (8 * (i % 4));
        private_key2[i / 4] |= ((uint32_t)rand() & 0xFF) << (8 * (i % 4));
    }

    private_key1[7] &= 0x7FFFFFFF;  // Ensure the private key is in the range [1, n-1]
    private_key2[7] &= 0x7FFFFFFF;  // Ensure the private key is in the range [1, n-1]

    ret = p256_keygen(public_key_x1, public_key_y1, private_key1);
    ret = p256_keygen(public_key_x2, public_key_y2, private_key2);

    bm_start();
    DoNotOptimize(public_key_x1);
    DoNotOptimize(public_key_y1);
    DoNotOptimize(private_key2);
    ret = p256_ecdh_calc_shared_secret(shared_secret, private_key2, public_key_x1, public_key_y1);
    DoNotOptimize(shared_secret);
    bm_end();

    if (!ret) {
        printf("P256, mont, emil-m4, ECDH failed\n");
        return;
    }
#ifdef EXTERNAL_EMIL_P256_M4
    printf("P256, mont, emil-m4, ECDH, cycles, %" PRIu32 "\n\n", bm_result());
#elif defined EXTERNAL_EMIL_P256_M4F
    printf("P256, mont, emil-m4f, ECDH, cycles, %" PRIu32 "\n\n", bm_result());
#endif

    usleep(10000);  // To avoid SWO buffer overflows
}
