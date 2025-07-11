#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "mini-gmp.h"
#include "unity.h"
#include "test_utility.h"

#define ITERATIONS 256
#define ALWAYS_INLINE __attribute__((noinline))

#include "m4-custom/code_C448_pmp_c.c"

extern gmp_randstate_t state;
extern mpz_t a_mpz, b_mpz, c_mpz, r_mpz, rinv_mpz, w_mpz, lim_mpz, zero_mpz, usedprime, realprime, maxbound;

static void mul_fixed(void) {
    test_mul_fixed(14, mul_C448_ct);
}

static void mul_random(void) {
    test_mul_random(14, mul_C448_ct);
}

static void sqr_fixed(void) {
    test_sqr_fixed(14, sqr_C448_ct);
}

static void sqr_random(void) {
    test_sqr_random(14, sqr_C448_ct);
}

static void modmul_fixed(void) {
    test_modmul_fixed(14, 1, modmul_C448_ct, compare_with_ref_modmul);
}

static void modmul_random(void) {
    test_modmul_random(14, modmul_C448_ct, compare_with_ref_modmul);
}

static void modsqr_fixed(void) {
    test_modsqr_fixed(14, 1, modsqr_C448_ct, compare_with_ref_modmul);
}

static void modsqr_random(void) {
    test_modsqr_random(14, modsqr_C448_ct, compare_with_ref_modmul);
}

static void modred_fixed(void) {
    test_modred_fixed(14, 448, modred_C448_ct);
}

static void modred_random(void) {
    test_modred_random(14, 448, modred_C448_ct);
}

static void modmli_fixed(void) {
    test_modmli_fixed(14, modmli_C448_ct);
}

static void modmli_random(void) {
    test_modmli_random(14, modmli_C448_ct);
}

static void modadd_fixed(void) {
    test_op2inputs_fixed(14, 1, 0, modadd_C448_ct, compare_with_ref_modadd);
}

static void modadd_random(void) {
    test_op2inputs_random(14, 1, 0, modadd_C448_ct, compare_with_ref_modadd);
}

static void modsub_fixed(void) {
    test_op2inputs_fixed(14, 1, 1, modsub_C448_ct, compare_with_ref_modsub);
}

static void modsub_random(void) {
    test_op2inputs_random(14, 1, 0, modsub_C448_ct, compare_with_ref_modsub);
}

static void modsub_negate_fixed(void) {
    test_op2inputs_fixed(14, 1, 1, modsub_C448_ct, compare_with_ref_modsub);
}

static void modsub_negate_random(void) {
    test_op2inputs_random(14, 1, 1, modsub_C448_ct, compare_with_ref_modsub);
}

static void modcpy_fixed(void) {
    test_modcpy_fixed(14, modcpy_C448_ct);
}

static void modcpy_random(void) {
    test_modcpy_random(14, modcpy_C448_ct);
}

static void nres_fixed(void) {
    test_nres_fixed(14, 1, nres_C448_ct);
}

static void nres_random(void) {
    test_nres_random(14, 1, nres_C448_ct);
}

static void redc_fixed(void) {
    test_redc_fixed(14, 1, redc_C448_ct, modfsb_C448_ct);
}

static void redc_random(void) {
    test_redc_random(14, 1, redc_C448_ct, modfsb_C448_ct);
}

static void modneg_fixed(void) {
    test_modneg_fixed(14, 1, modneg_C448_ct);
}

static void modneg_random(void) {
    test_modneg_random(14, 1, modneg_C448_ct);
}

static void modinv_fixed(void) {
    test_modinv_fixed(14, nres_C448_ct, modinv_C448_ct, redc_C448_ct);
}

static void modinv_random(void) {
    test_modinv_random(14, nres_C448_ct, modinv_C448_ct, redc_C448_ct);
}

static void modfsb_fixed(void) {
    test_modfsb_fixed(14, modfsb_C448_ct);
}

static void modfsb_random(void) {
    test_modfsb_random(14, modfsb_C448_ct);
}

static void modis1_fixed(void) {
    test_modis1_fixed(14, nres_C448_ct, modis1_C448_ct);
}

static void modis1_random(void) {
    test_modis1_random(14, nres_C448_ct, modis1_C448_ct);
}

static void modis0_fixed(void) {
    test_modis0_fixed(14, nres_C448_ct, modis0_C448_ct);
}

static void modis0_random(void) {
    test_modis0_random(14, modis0_C448_ct);
}

static void modzer_random(void) {
    test_modzer_random(14, modzer_C448_ct);
}

static void modone_random(void) {
    test_modone_random(14, modone_C448_ct, redc_C448_ct);
}

static void modint_random(void) {
    test_modint_random(14, modint_C448_ct, redc_C448_ct);
}

static void modcmv_random(void) {
    test_modcmv_random(14, modcmv_C448_ct);
}

static void modcsw_random(void) {
    test_modcsw_random(14, modcsw_C448_ct);
}

static void modsqrt_fixed(void) {
    test_modsqrt_fixed(14, nres_C448_ct, modsqrt_C448_ct, redc_C448_ct);
}

static void modsqrt_random(void) {
    test_modsqrt_random(14, nres_C448_ct, modsqrt_C448_ct, redc_C448_ct);
}

static void modshr_fixed(void) {
    test_modshr_fixed(14, modshr_C448_ct);
}

static void modshr_random(void) {
    test_modshr_random(14, modshr_C448_ct);
}

static void modshl_fixed(void) {
    test_modshl_fixed(14, modshl_C448_ct);
}

static void modshl_random(void) {
    test_modshl_random(14, modshl_C448_ct);
}

static void mod2r_random(void) {
    test_mod2r_random(14, 1, mod2r_C448_ct);
}

static void mod2r_fixed(void) {
    test_mod2r_fixed(14, 1, mod2r_C448_ct);
}

static void modsign_fixed(void) {
    test_modsign_fixed(14, 1, modsign_C448_ct);
}

static void modsign_random(void) {
    test_modsign_random(14, 1, modsign_C448_ct);
}

static void modcmp_random(void) {
    test_modcmp_random(14, 1, modcmp_C448_ct);
}

static void modimp_fixed(void) {
    test_modimp_fixed(14, 1, modimp_C448_ct);
}

static void modimp_random(void) {
    test_modimp_random(14, 1, modimp_C448_ct);
}

static void modexp_random(void) {
    test_modexp_random(14, 1, modexp_C448_ct);
}

static void acceptance_random(void) {
    test_acceptance_random(14, 1, nres_C448_ct, modadd_C448_ct, modsub_C448_ct, modmul_C448_ct, modsqr_C448_ct, modinv_C448_ct, modsqrt_C448_ct, redc_C448_ct, modfsb_C448_ct);
}

void test_C448_pmp_c_ct_custom(void) {
    printf("Testing C448_pmp_c_custom\n");
    mpz_set_str(realprime, "0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffeffffffffffffffffffffffffffffffffffffffffffffffffffffffff", 0);
    mpz_set(usedprime, realprime);
    mpz_set_ui(maxbound, 1);
    mpz_mul_2exp(maxbound, maxbound, 448);
    mpz_sub_ui(maxbound, maxbound, 1);
    mpz_set_ui(r_mpz, 1);
    mpz_mul_2exp(r_mpz, r_mpz, 448);
    mpz_invert(rinv_mpz, r_mpz, realprime);
    RUN_TEST(mul_random);
    RUN_TEST(mul_fixed);
    RUN_TEST(sqr_random);
    RUN_TEST(sqr_fixed);
    RUN_TEST(modmul_random);
    RUN_TEST(modmul_fixed);
    RUN_TEST(modsqr_random);
    RUN_TEST(modsqr_fixed);
    RUN_TEST(modred_random);
    RUN_TEST(modred_fixed);
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
