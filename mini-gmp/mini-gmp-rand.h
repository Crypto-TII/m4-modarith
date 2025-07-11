#ifndef MINI_GMP_RAND_H
#define MINI_GMP_RAND_H

#include "mini-gmp.h"
#include "xoshiro128plusplus.h"

typedef xoshiro128plusplus_state gmp_randstate_t;

void gmp_randinit_default(gmp_randstate_t state);
void gmp_randclear(gmp_randstate_t state);

void gmp_randseed(gmp_randstate_t state, const mpz_t seed);
void gmp_randseed_ui(gmp_randstate_t state, unsigned long int seed);

void mpz_urandomb(mpz_t rop, gmp_randstate_t state, mp_bitcnt_t n);
void mpz_urandomm(mpz_t rop, gmp_randstate_t state, const mpz_t n);

unsigned long gmp_urandomb_ui(gmp_randstate_t state, unsigned long n);
unsigned long gmp_urandomm_ui(gmp_randstate_t state, unsigned long n);

#endif  // MINI_GMP_RAND_H
