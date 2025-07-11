#ifndef TEST_UTILITY_H
#define TEST_UTILITY_H

#include <stdint.h>

#include "mini-gmp.h"

void test_utility_init(void);
void test_utility_clear(void);

void convert_to_mpz_t(mpz_t res, uint32_t *input, size_t size);
void convert_to_array(uint32_t *res, mpz_t input, size_t size);
int compare_with_ref_mul(uint32_t *actual, uint32_t *a, uint32_t *b, const mpz_t a_mpz, const mpz_t b_mpz, size_t size);
int compare_with_ref_modadd(uint32_t *actual, const mpz_t a_mpz, const mpz_t b_mpz, size_t size, mpz_t m, int ispmp);
int compare_with_ref_modsub(uint32_t *actual, const mpz_t a_mpz, const mpz_t b_mpz, size_t size, mpz_t m, int ispmp);
int compare_with_ref_mod(uint32_t *actual, uint32_t *a, uint32_t *b, const mpz_t a_mpz, const mpz_t b_mpz, size_t size,
                         mpz_t m);
int compare_with_ref_modmul(uint32_t *actual, const mpz_t a_mpz, const mpz_t b_mpz, size_t size, mpz_t m);
int compare_with_ref_modred(uint32_t *actual, const mpz_t c_mpz, size_t size, mpz_t m);
int compare_with_ref_mont(uint32_t *actual, uint32_t *a, uint32_t *b, size_t size, mpz_t m);
int compare_with_ref_redc(uint32_t *actual, mpz_t a_mpz, size_t size, mpz_t m);
int compare_with_ref_nres(uint32_t *actual, mpz_t a_mpz, size_t size, mpz_t m);
int compare_with_ref_modcmp(int actual, mpz_t a_mpz, mpz_t b_mpz, size_t size, mpz_t m);
int compare_with_ref_modsign(int actual, mpz_t a_mpz, size_t size, mpz_t m);
int compare_with_ref_modsign_mont(int actual, mpz_t a_mpz, size_t size, mpz_t m);
int compare_with_ref_mod2r(uint32_t *actual, unsigned int r, size_t size, mpz_t m);
int compare_with_ref_mod2r_mont(uint32_t *actual, unsigned int r, size_t size, mpz_t m);
int compare_with_ref_modneg(uint32_t *actual, mpz_t a_mpz, size_t size, mpz_t m);
int compare_with_ref_modinv(uint32_t *actual, mpz_t a_mpz, size_t size, mpz_t m);
int compare_with_ref_modfsb(uint32_t *actual, int r, mpz_t a_mpz, size_t size, mpz_t m);
int compare_with_ref_modis1(int res, mpz_t a_mpz);
int compare_with_ref_modis0(int res, mpz_t a_mpz);
int compare_with_ref_modcsw(int move, uint32_t *amv, uint32_t *bmv, mpz_t a_mpz, mpz_t b_mpz, size_t size);
int compare_with_ref_modcmv(int move, uint32_t *bmv, mpz_t a_mpz, mpz_t b_mpz, size_t size);
int compare_with_ref_modsqrt(uint32_t *actual, mpz_t a_mpz, size_t size, mpz_t m);
int compare_with_ref_modshr(int shift, uint32_t *actual, mpz_t a_mpz, size_t size);
int compare_with_ref_modshl(int shift, uint32_t *actual, mpz_t a_mpz, size_t size, mpz_t m);
int compare_with_ref_modmul_mont(uint32_t *actual, const mpz_t a_mpz, const mpz_t b_mpz, size_t size, mpz_t m);
int compare_with_ref_modmul_mont_2p(uint32_t *actual, const mpz_t a_mpz, const mpz_t b_mpz, size_t size, mpz_t m);
int compare_with_ref_congruent(uint32_t *actual, uint32_t *a, uint32_t *b, const mpz_t a_mpz, const mpz_t b_mpz,
                               size_t size, mpz_t m);
int compare_with_ref_modimp(uint32_t* actual, const mpz_t a_mpz, size_t size);
int compare_with_ref_modimp_mont(uint32_t* actual, const mpz_t a_mpz, size_t size);
int compare_with_ref_modexp(const char* actual, const mpz_t a_mpz, size_t size);
int compare_with_ref_modexp_mont(const char* actual, const mpz_t a_mpz, size_t size);
int compare_with_ref_acpt(uint32_t *actual, const mpz_t a_mpz, const mpz_t b_mpz, size_t size, mpz_t m);

void test_mul_fixed(int nlimbs, void (*mul)(const uint32_t *, const uint32_t *, uint32_t *));
void test_mul_random(int nlimbs, void (*mul)(const uint32_t *, const uint32_t *, uint32_t *));

void test_modmul_fixed(int nlimbs, int ispmp, void (*modmul)(const uint32_t *, const uint32_t *, uint32_t *),
                       int (*compare_with_ref_modmul)(uint32_t *, const mpz_t, const mpz_t, size_t, mpz_t));
void test_modmul_random(int nlimbs, void (*modmul)(const uint32_t *, const uint32_t *, uint32_t *),
                        int (*compare_with_ref_modmul)(uint32_t *, const mpz_t, const mpz_t, size_t, mpz_t));

void test_sqr_fixed(int nlimbs, void (*sqr)(const uint32_t *, uint32_t *));
void test_sqr_random(int nlimbs, void (*sqr)(const uint32_t *, uint32_t *));

void test_modsqr_fixed(int nlimbs, int ispmp, void (*modsqr)(const uint32_t *, uint32_t *),
                       int (*compare_with_ref_modmul)(uint32_t *, const mpz_t, const mpz_t, size_t, mpz_t));
void test_modsqr_random(int nlimbs, void (*modsqr)(const uint32_t *, uint32_t *),
                        int (*compare_with_ref_modmul)(uint32_t *, const mpz_t, const mpz_t, size_t, mpz_t));

void test_modred_fixed(int nlimbs, int n, void (*modred)(const uint32_t *, uint32_t *));
void test_modred_inplace_fixed(int nlimbs, int n, void (*modred)(uint32_t *));
void test_modred_random(int nlimbs, int n, void (*modred)(const uint32_t *, uint32_t *));
void test_modred_inplace_random(int nlimbs, int n, void (*modred)(uint32_t *));

void test_modneg_fixed(int nlimbs, int ispmp, void (*modneg)(const uint32_t *, uint32_t *));
void test_modneg_random(int nlimbs, int ispmp, void (*modneg)(const uint32_t *, uint32_t *));

void test_op2inputs_fixed(int nlimbs, int ispmp, int issub, void (*op)(const uint32_t *, const uint32_t *, uint32_t *),
                          int (*compare_with_ref)(uint32_t *, const mpz_t, const mpz_t, size_t, mpz_t, int));
void test_op2inputs_random(int nlimbs, int ispmp, int zero_a,
                           void (*op)(const uint32_t *, const uint32_t *, uint32_t *),
                           int (*compare_with_ref)(uint32_t *, const mpz_t, const mpz_t, size_t, mpz_t, int));

void test_modmli_fixed(int nlimbs, void (*modmli)(const uint32_t *, const uint32_t, uint32_t *s));
void test_modmli_random(int nlimbs, void (*modmli)(const uint32_t *, const uint32_t, uint32_t *));

void test_redc_fixed(int nlimbs, int ispmp, void (*redc)(const uint32_t *, uint32_t *), int (*modfsb)(uint32_t *));
void test_redc_random(int nlimbs, int ispmp, void (*redc)(const uint32_t *, uint32_t *), int (*modfsb)(uint32_t *));

void test_nres_fixed(int nlimbs, int ispmp, void (*nres)(const uint32_t *, uint32_t *));
void test_nres_random(int nlimbs, int ispmp, void (*nres)(const uint32_t *, uint32_t *));

void test_modcpy_fixed(int nlimbs, void (*modcpy)(const uint32_t *, uint32_t *));
void test_modcpy_random(int nlimbs, void (*modcpy)(const uint32_t *, uint32_t *));

void test_modinv_fixed(int nlimbs, void (*nres)(const uint32_t *, uint32_t *),
                       void (*modinv)(const uint32_t *, const uint32_t *, uint32_t *),
                       void (*redc)(const uint32_t *, uint32_t *));
void test_modinv_random(int nlimbs, void (*nres)(const uint32_t *, uint32_t *),
                        void (*modinv)(const uint32_t *, const uint32_t *, uint32_t *),
                        void (*redc)(const uint32_t *, uint32_t *));

void test_modfsb_fixed(int nlimbs, int (*modfsb)(uint32_t *));
void test_modfsb_random(int nlimbs, int (*modfsb)(uint32_t *));

void test_modis1_fixed(int nlimbs, void (*nres)(const uint32_t *, uint32_t *), int (*modis1)(const uint32_t *));
void test_modis1_random(int nlimbs, void (*nres)(const uint32_t *, uint32_t *), int (*modis1)(const uint32_t *));

void test_modis0_fixed(int nlimbs, void (*nres)(const uint32_t *, uint32_t *), int (*modis0)(const uint32_t *));
void test_modis0_random(int nlimbs, int (*modis0)(const uint32_t *));

void test_modzer_random(int nlimbs, void (*modzer)(uint32_t *));

void test_modone_random(int nlimbs, void (*modone)(uint32_t *), void (*redc)(const uint32_t *, uint32_t *));

void test_modint_random(int nlimbs, void (*modint)(int, uint32_t *), void (*redc)(const uint32_t *, uint32_t *));

void test_modshr_fixed(int nlimbs, uint32_t (*modshr)(int, uint32_t *));
void test_modshr_random(int nlimbs, uint32_t (*modshr)(int, uint32_t *));

void test_modshl_fixed(int nlimbs, void (*modshl)(int, uint32_t *));
void test_modshl_random(int nlimbs, void (*modshl)(int, uint32_t *));

void test_modcmv_random(int nlimbs, void (*modcmv)(int, const uint32_t *, volatile uint32_t *));

void test_modcsw_random(int nlimbs, void (*modcsw)(int, volatile uint32_t *, volatile uint32_t *));

void test_modsqrt_fixed(int nlimbs, void (*nres)(const uint32_t *, uint32_t *),
                        void (*modsqrt)(const uint32_t *, const uint32_t *, uint32_t *),
                        void (*redc)(const uint32_t *, uint32_t *));
void test_modsqrt_random(int nlimbs, void (*nres)(const uint32_t *, uint32_t *),
                         void (*modsqrt)(const uint32_t *, const uint32_t *, uint32_t *),
                         void (*redc)(const uint32_t *, uint32_t *));

void test_modcmp_fixed(int nlimbs, int ispmp, int (*modcmp)(const uint32_t *, const uint32_t *));
void test_modcmp_random(int nlimbs, int ispmp, int (*modcmp)(const uint32_t *, const uint32_t *));

void test_modsign_fixed(int nlimbs, int ispmp, int (*modsign)(const uint32_t *));
void test_modsign_random(int nlimbs, int ispmp, int (*modsign)(const uint32_t *));

void test_mod2r_fixed(int nlimbs, int ispmp, void (*mod2r)(unsigned int, uint32_t *));
void test_mod2r_random(int nlimbs, int ispmp, void (*mod2r)(unsigned int, uint32_t *));

void test_modimp_fixed(int nlimbs, int ispmp, void (*modimp)(const char *, uint32_t *));
void test_modimp_random(int nlimbs, int ispmp, void (*modimp)(const char *, uint32_t *));

void test_modexp_random(int nlimbs, int ispmp, void (*modexp)(const uint32_t *a, char *b));

void test_acceptance_random(int nlimbs, int ispmp, void (*nres)(const uint32_t *, uint32_t *),
                            void (*modadd)(const uint32_t *, const uint32_t *, uint32_t *),
                            void (*modsub)(const uint32_t *, const uint32_t *, uint32_t *),
                            void (*modmul)(const uint32_t *, const uint32_t *, uint32_t *),
                            void (*modsqr)(const uint32_t *, uint32_t *),
                            void (*modinv)(const uint32_t *, const uint32_t *, uint32_t *),
                            void (*modsqrt)(const uint32_t *, const uint32_t *, uint32_t *),
                            void (*redc)(const uint32_t *, uint32_t *), int (*modfsb)(uint32_t *));

#endif  // TEST_UTILITY_H
