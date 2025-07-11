
#include <inttypes.h>

#include "hal.h"
#include "p256-m.h"
#include "p256-m-internal.h"

#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "r,m"(value) : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "m,r"(value) : "memory");
#endif

void bench_p256_m_mul_p256r1() {
    uint32_t res[8], l[8], r[8];
    bm_decls;

    bm_start();
    DoNotOptimize(l);
    DoNotOptimize(r);
    m256_mul(res, l, r, &p256_p);
    DoNotOptimize(res);
    bm_end();

    printf("SECP256R1, -, p256-m, modmul, cycles, %" PRIu32 "\n", bm_result());
    usleep(10000);  // To avoid SWO buffer overflows
}

int p256_generate_random(uint8_t *output, unsigned output_size) {
    for (int i = 0; i < output_size; i++) {
        output[i] = rand() % 256;  // Simple random generation for demonstration
    }
    return 0;
}

void bench_256_m_ecdh_shared_secret() {
    uint8_t priv1[32], pub1[64], priv2[32], pub2[64], secret[32];
    int res;

    bm_decls;

    p256_gen_keypair(priv1, pub1);
    p256_gen_keypair(priv2, pub2);

    bm_start();
    DoNotOptimize(priv1);
    DoNotOptimize(pub2);
    res = p256_ecdh_shared_secret(secret, priv1, pub2);
    DoNotOptimize(secret);
    DoNotOptimize(res);
    bm_end();

    if (res != P256_SUCCESS) {
        printf("SECP256R1, -, p256-m, ECDH, error, %d\n", res);
        return;
    }
    else {
        printf("SECP256R1, -, p256-m, ECDH, cycles, %" PRIu32 "\n", bm_result());
    }
}

void bench_p256_m() {
    bench_p256_m_mul_p256r1();
    bench_256_m_ecdh_shared_secret();
    printf("\n");
}
