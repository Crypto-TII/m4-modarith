#include "mini-gmp-rand.h"

#include "xoshiro128plusplus.h"

// To select the method for generating random numbers modulo n, either #define REJECTION_SAMPLING_RANDOM or leave it
// undefined.
// Rejection sampling ensures unbiased results, but it may be a little slower.
// The alternative method introduces a small bias.
#define REJECTION_SAMPLING_RANDOM

void gmp_randinit_default(gmp_randstate_t state) {
    // The xoroshiro128++ generator cannot be seeded with zero, or it will only generate zeros as its output. Thus,
    // we seed it with **something**.
    const uint32_t seed[4] = {0xB85497A9, 0x68E100A5, 0xD00B0638, 0x5C068A34};
    xoshiro128plusplus_seed(state, seed);
}

void gmp_randclear(gmp_randstate_t state) {
    (void)state;
}

void gmp_randseed(gmp_randstate_t state, const mpz_t seed) {
    // Use only the least significant 128 bits of the seed
    mpz_t seed_copy;
    uint32_t seed_array[4];
    mpz_init_set(seed_copy, seed);

    for (int i = 0; i < 4; i++) {
        seed_array[i] = mpz_get_ui(seed_copy);
        mpz_fdiv_q_2exp(seed_copy, seed_copy, 32);
    }

    xoshiro128plusplus_seed(state, seed_array);

    mpz_clear(seed_copy);
}

void gmp_randseed_ui(gmp_randstate_t state, unsigned long int seed) {
    uint32_t seed_array[4] = {seed, seed, seed, seed};
    xoshiro128plusplus_seed(state, seed_array);
}

void mpz_urandomb(mpz_t rop, gmp_randstate_t state, mp_bitcnt_t n) {
    mpz_set_ui(rop, 0);

    while (n > 32) {
        mpz_mul_2exp(rop, rop, 32);
        mpz_add_ui(rop, rop, xoshiro128plusplus_rand32(state));
        n -= 32;
    }

    mpz_mul_2exp(rop, rop, n);
    mpz_add_ui(rop, rop, xoshiro128plusplus_rand32(state) & ((1 << n) - 1));
}

void mpz_urandomm(mpz_t rop, gmp_randstate_t state, const mpz_t n) {
#ifdef REJECTION_SAMPLING_RANDOM
    do {
        mpz_urandomb(rop, state, mpz_sizeinbase(n, 2));
    }
    while (mpz_cmp(rop, n) >= 0);
#else
    mpz_urandomb(rop, state, mpz_sizeinbase(n, 2));
    if (mpz_cmp(rop, n) >= 0) {
        mpz_sub(rop, rop, n);
    }
#endif
}

unsigned long gmp_urandomb_ui(gmp_randstate_t state, unsigned long n) {
    unsigned long res = xoshiro128plusplus_rand32(state);
    return res & ((1 << n) - 1);
}

unsigned long gmp_urandomm_ui(gmp_randstate_t state, unsigned long n) {
    unsigned long res = xoshiro128plusplus_rand32(state);
    return res % n;
}
