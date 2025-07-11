#include "hal.h"
#include "unity.h"
#include "mini-gmp.h"
#include "test_utility.h"

gmp_randstate_t state;
mpz_t a_mpz, b_mpz, c_mpz, r_mpz, rinv_mpz, w_mpz, lim_mpz, zero_mpz, usedprime, realprime, maxbound;

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_C25519_pmp_asm_ct(void);
void test_C25519_mont_ct(void);
void test_PM266_pmp_asm_ct(void);
void test_PM266_mont_ct(void);
void test_PM512_pmp_asm_ct(void);
void test_PM512_mont_ct(void);
void test_NIST521_pmp_asm_ct(void);
void test_NIST521_mont_ct(void);
void test_PM383_pmp_asm_ct(void);
void test_PM383_mont_ct(void);
void test_C41417_pmp_asm_ct(void);
void test_C41417_mont_ct(void);
void test_PM336_pmp_asm_ct(void);
void test_PM336_mont_ct(void);
void test_PM225_pmp_asm_ct(void);
void test_PM225_mont_ct(void);
void test_NIST256_mont_ct(void);
void test_C448_mont_ct(void);
void test_MFP47441_mont_ct(void);
void test_MFP248_mont_ct(void);
void test_MFP376_mont_ct(void);
void test_MFP500_mont_ct(void);
void test_SECP256K1_mont_ct(void);
void test_MFP248_mont_ct_custom(void);
void test_C25519_pmp_asm_ct_custom(void);
void test_C448_pmp_c_ct_custom(void);
void test_rfc7748(void);
void test_external(void);

int main(void) {
    hal_setup(CLOCK_FAST);

    gmp_randinit_default(state);
    mpz_init(a_mpz);
    mpz_init(b_mpz);
    mpz_init(c_mpz);
    mpz_init(r_mpz);
    mpz_init(rinv_mpz);
    mpz_init(w_mpz);
    mpz_init(lim_mpz);
    mpz_init_set_ui(zero_mpz, 0);
    mpz_init(usedprime);
    mpz_init(realprime);
    mpz_init(maxbound);

    test_utility_init();

    UNITY_BEGIN();

    test_C25519_pmp_asm_ct();
    test_C25519_mont_ct();
    test_PM266_pmp_asm_ct();
    test_PM266_mont_ct();
    test_PM512_pmp_asm_ct();
    test_PM512_mont_ct();
    test_NIST521_pmp_asm_ct();
    test_NIST521_mont_ct();
    test_PM383_pmp_asm_ct();
    test_PM383_mont_ct();
    test_C41417_pmp_asm_ct();
    test_C41417_mont_ct();
    test_PM336_pmp_asm_ct();
    test_PM336_mont_ct();
    test_PM225_pmp_asm_ct();
    test_PM225_mont_ct();
    test_NIST256_mont_ct();
    test_C448_mont_ct();
    test_MFP47441_mont_ct();
    test_MFP248_mont_ct();
    test_MFP376_mont_ct();
    test_MFP500_mont_ct();
    test_SECP256K1_mont_ct();
    test_MFP248_mont_ct_custom();
    test_C25519_pmp_asm_ct_custom();
    test_C448_pmp_c_ct_custom();
    test_rfc7748();
    test_external();

    gmp_randclear(state);
    mpz_clear(a_mpz);
    mpz_clear(b_mpz);
    mpz_clear(c_mpz);
    mpz_clear(w_mpz);
    mpz_clear(lim_mpz);
    mpz_clear(zero_mpz);
    mpz_clear(usedprime);
    mpz_clear(realprime);
    mpz_clear(maxbound);

    test_utility_clear();

    hal_exit_(UNITY_END());

    // Unreachable
    return 0;
}
