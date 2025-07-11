#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "mini-gmp.h"
#include "unity.h"
#include "test_utility.h"

#define ITERATIONS 256
#define ALWAYS_INLINE __attribute__((noinline))

#include "m4-custom/code_MFP248_mont.c"

extern gmp_randstate_t state;
extern mpz_t a_mpz, b_mpz, c_mpz, r_mpz, rinv_mpz, w_mpz, lim_mpz, zero_mpz, usedprime, realprime, maxbound;

static void mul_fixed(void) {
    test_mul_fixed(8, mul_MFP248_ct);
}

static void mul_random(void) {
    test_mul_random(8, mul_MFP248_ct);
}

static void sqr_fixed(void) {
    test_sqr_fixed(8, sqr_MFP248_ct);
}

static void sqr_random(void) {
    test_sqr_random(8, sqr_MFP248_ct);
}

static void modmul_fixed(void) {
    test_modmul_fixed(8, 0, modmul_MFP248_ct, compare_with_ref_modmul_mont_2p);
}

static void modmul_random(void) {
    test_modmul_random(8, modmul_MFP248_ct, compare_with_ref_modmul_mont_2p);
}

static void modsqr_fixed(void) {
    test_modsqr_fixed(8, 0, modsqr_MFP248_ct, compare_with_ref_modmul_mont_2p);
}

static void modsqr_random(void) {
    test_modsqr_random(8, modsqr_MFP248_ct, compare_with_ref_modmul_mont_2p);
}

static void modmli_fixed(void) {
    test_modmli_fixed(8, modmli_MFP248_ct);
}

static void modmli_random(void) {
    test_modmli_random(8, modmli_MFP248_ct);
}

static void modadd_fixed(void) {
    test_op2inputs_fixed(8, 0, 0, modadd_MFP248_ct, compare_with_ref_modadd);
}

static void modadd_random(void) {
    test_op2inputs_random(8, 0, 0, modadd_MFP248_ct, compare_with_ref_modadd);
}

static void modsub_fixed(void) {
    test_op2inputs_fixed(8, 0, 1, modsub_MFP248_ct, compare_with_ref_modsub);
}

static void modsub_random(void) {
    test_op2inputs_random(8, 0, 0, modsub_MFP248_ct, compare_with_ref_modsub);
}

static void modsub_negate_fixed(void) {
    test_op2inputs_fixed(8, 0, 1, modsub_MFP248_ct, compare_with_ref_modsub);
}

static void modsub_negate_random(void) {
    test_op2inputs_random(8, 0, 1, modsub_MFP248_ct, compare_with_ref_modsub);
}

static void modcpy_fixed(void) {
    test_modcpy_fixed(8, modcpy_MFP248_ct);
}

static void modcpy_random(void) {
    test_modcpy_random(8, modcpy_MFP248_ct);
}

static void nres_fixed(void) {
    test_nres_fixed(8, 0, nres_MFP248_ct);
}

static void nres_random(void) {
    test_nres_random(8, 0, nres_MFP248_ct);
}

static void redc_fixed(void) {
    test_redc_fixed(8, 0, redc_MFP248_ct, modfsb_MFP248_ct);
}

static void redc_random(void) {
    test_redc_random(8, 0, redc_MFP248_ct, modfsb_MFP248_ct);
}

static void modneg_fixed(void) {
    test_modneg_fixed(8, 0, modneg_MFP248_ct);
}

static void modneg_random(void) {
    test_modneg_random(8, 0, modneg_MFP248_ct);
}

static void modinv_fixed(void) {
    test_modinv_fixed(8, nres_MFP248_ct, modinv_MFP248_ct, redc_MFP248_ct);
}

static void modinv_random(void) {
    test_modinv_random(8, nres_MFP248_ct, modinv_MFP248_ct, redc_MFP248_ct);
}

static void modfsb_fixed(void) {
    test_modfsb_fixed(8, modfsb_MFP248_ct);
}

static void modfsb_random(void) {
    test_modfsb_random(8, modfsb_MFP248_ct);
}

static void modis1_fixed(void) {
    test_modis1_fixed(8, nres_MFP248_ct, modis1_MFP248_ct);
}

static void modis1_random(void) {
    test_modis1_random(8, nres_MFP248_ct, modis1_MFP248_ct);
}

static void modis0_fixed(void) {
    test_modis0_fixed(8, nres_MFP248_ct, modis0_MFP248_ct);
}

static void modis0_random(void) {
    test_modis0_random(8, modis0_MFP248_ct);
}

static void modzer_random(void) {
    test_modzer_random(8, modzer_MFP248_ct);
}

static void modone_random(void) {
    test_modone_random(8, modone_MFP248_ct, redc_MFP248_ct);
}

static void modint_random(void) {
    test_modint_random(8, modint_MFP248_ct, redc_MFP248_ct);
}

static void modcmv_random(void) {
    test_modcmv_random(8, modcmv_MFP248_ct);
}

static void modcsw_random(void) {
    test_modcsw_random(8, modcsw_MFP248_ct);
}

static void modsqrt_fixed(void) {
    test_modsqrt_fixed(8, nres_MFP248_ct, modsqrt_MFP248_ct, redc_MFP248_ct);
}

static void modsqrt_random(void) {
    test_modsqrt_random(8, nres_MFP248_ct, modsqrt_MFP248_ct, redc_MFP248_ct);
}

static void modshr_fixed(void) {
    test_modshr_fixed(8, modshr_MFP248_ct);
}

static void modshr_random(void) {
    test_modshr_random(8, modshr_MFP248_ct);
}

static void modshl_fixed(void) {
    test_modshl_fixed(8, modshl_MFP248_ct);
}

static void modshl_random(void) {
    test_modshl_random(8, modshl_MFP248_ct);
}

static void mod2r_random(void) {
    test_mod2r_random(8, 0, mod2r_MFP248_ct);
}

static void mod2r_fixed(void) {
    test_mod2r_fixed(8, 0, mod2r_MFP248_ct);
}

static void modsign_fixed(void) {
    test_modsign_fixed(8, 0, modsign_MFP248_ct);
}

static void modsign_random(void) {
    test_modsign_random(8, 0, modsign_MFP248_ct);
}

static void modcmp_random(void) {
    test_modcmp_random(8, 0, modcmp_MFP248_ct);
}

static void modimp_fixed(void) {
    test_modimp_fixed(8, 0, modimp_MFP248_ct);
}

static void modimp_random(void) {
    test_modimp_random(8, 0, modimp_MFP248_ct);
}

static void modexp_random(void) {
    test_modexp_random(8, 0, modexp_MFP248_ct);
}

static void acceptance_random(void) {
    test_acceptance_random(8, 0, nres_MFP248_ct, modadd_MFP248_ct, modsub_MFP248_ct, modmul_MFP248_ct, modsqr_MFP248_ct, modinv_MFP248_ct, modsqrt_MFP248_ct, redc_MFP248_ct, modfsb_MFP248_ct);
}

void test_MFP248_mont_ct_custom(void) {
    printf("Testing MFP248_mont_custom\n");
    mpz_set_str(realprime, "0x4ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff", 0);
    mpz_add(usedprime, realprime, realprime);
    mpz_set_ui(maxbound, 1);
    mpz_mul_2exp(maxbound, maxbound, 252);
    mpz_sub_ui(maxbound, maxbound, 1);
    mpz_set_ui(r_mpz, 1);
    mpz_mul_2exp(r_mpz, r_mpz, 256);
    mpz_invert(rinv_mpz, r_mpz, realprime);
    RUN_TEST(mul_random);
    RUN_TEST(mul_fixed);
    RUN_TEST(sqr_random);
    RUN_TEST(sqr_fixed);
    RUN_TEST(modmul_random);
    RUN_TEST(modmul_fixed);
    RUN_TEST(modsqr_random);
    RUN_TEST(modsqr_fixed);
    RUN_TEST(modmli_random);
    RUN_TEST(modmli_fixed);
    RUN_TEST(modadd_random);
    RUN_TEST(modadd_fixed);
    RUN_TEST(modsub_random);
    RUN_TEST(modsub_fixed);
    RUN_TEST(modsub_negate_random);
    RUN_TEST(modsub_negate_fixed);
    RUN_TEST(modcpy_random);
    RUN_TEST(modcpy_fixed);
    RUN_TEST(nres_random);
    RUN_TEST(nres_fixed);
    RUN_TEST(redc_random);
    RUN_TEST(redc_fixed);
    RUN_TEST(modneg_random);
    RUN_TEST(modneg_fixed);
    RUN_TEST(modinv_random);
    RUN_TEST(modinv_fixed);
    RUN_TEST(modfsb_random);
    RUN_TEST(modfsb_fixed);
    RUN_TEST(modis1_random);
    RUN_TEST(modis1_fixed);
    RUN_TEST(modis0_random);
    RUN_TEST(modis0_fixed);
    RUN_TEST(modzer_random);
    RUN_TEST(modone_random);
    RUN_TEST(modint_random);
    RUN_TEST(modcmv_random);
    RUN_TEST(modcsw_random);
    RUN_TEST(modsqrt_random);
    RUN_TEST(modsqrt_fixed);
    RUN_TEST(modshr_random);
    RUN_TEST(modshr_fixed);
    RUN_TEST(modshl_random);
    RUN_TEST(modshl_fixed);
    RUN_TEST(mod2r_random);
    RUN_TEST(mod2r_fixed);
    RUN_TEST(modsign_random);
    RUN_TEST(modsign_fixed);
    RUN_TEST(modcmp_random);
    RUN_TEST(modimp_random);
    RUN_TEST(modimp_fixed);
    RUN_TEST(modexp_random);
    RUN_TEST(acceptance_random);
    printf("\n");
}
