#include "test_utility.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "mini-gmp.h"
#include "unity.h"

#ifndef ITERATIONS
#define ITERATIONS 256
#endif

// These static variables are namespaced to avoid any clashes with the
// *_mpz variables from the generated tests
static mpz_t tu_t, tu_in;
static mpz_t tu_actual_mpz, tu_actual2_mpz, tu_expected_mpz, tu_partialexpected_mpz;
static mpz_t tu_a_mpz, tu_b_mpz, tu_c_mpz, tu_t_mpz;
static mpz_t tu_factor_mpz, tu_lim_mpz;

extern gmp_randstate_t state;
extern mpz_t a_mpz, b_mpz, c_mpz, r_mpz, rinv_mpz, w_mpz, lim_mpz, zero_mpz, usedprime, realprime, maxbound;

void test_utility_init(void) {
    mpz_init(tu_t);
    mpz_init(tu_in);
    mpz_init(tu_actual_mpz);
    mpz_init(tu_actual2_mpz);
    mpz_init(tu_expected_mpz);
    mpz_init(tu_partialexpected_mpz);
    mpz_init(tu_a_mpz);
    mpz_init(tu_b_mpz);
    mpz_init(tu_c_mpz);
    mpz_init(tu_t_mpz);
    mpz_init(tu_factor_mpz);
    mpz_init(tu_lim_mpz);
}

void test_utility_clear(void) {
    mpz_clear(tu_t);
    mpz_clear(tu_in);
    mpz_clear(tu_actual_mpz);
    mpz_clear(tu_actual2_mpz);
    mpz_clear(tu_expected_mpz);
    mpz_clear(tu_partialexpected_mpz);
    mpz_clear(tu_a_mpz);
    mpz_clear(tu_b_mpz);
    mpz_clear(tu_c_mpz);
    mpz_clear(tu_t_mpz);
    mpz_clear(tu_factor_mpz);
    mpz_clear(tu_lim_mpz);
}

void convert_to_mpz_t(mpz_t res, uint32_t *input, size_t size) {
    mpz_set_ui(res, input[size - 1]);
    for (int i = size - 2; i >= 0; i--) {
        mpz_mul_2exp(res, res, 32);
        mpz_add_ui(res, res, input[i]);
    }
}

void convert_to_array(uint32_t *res, mpz_t input, size_t size) {
    mpz_set(tu_in, input);
    for (int i = 0; i < size; i++) {
        mpz_fdiv_r_2exp(tu_t, tu_in, 32);
        res[i] = mpz_get_ui(tu_t);
        mpz_fdiv_q_2exp(tu_in, tu_in, 32);
    }
}

int compare_with_ref_mul(uint32_t *actual, uint32_t *a, uint32_t *b, const mpz_t a_mpz, const mpz_t b_mpz,
                         size_t size) {
    int ret;

    mpz_mul(tu_expected_mpz, a_mpz, b_mpz);
    convert_to_mpz_t(tu_actual_mpz, actual, 2 * size);

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz);

    if (ret != 0) {
        char expected_str[1024], actual_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        printf("Expected: 0x%128s\n", expected_str);
        printf("Actual:   0x%128s\n", actual_str);
    }

    return ret;
}

int compare_with_ref_modadd(uint32_t *actual, const mpz_t a_mpz, const mpz_t b_mpz, size_t size, mpz_t m, int ispmp) {
    int ret;

    convert_to_mpz_t(tu_actual_mpz, actual, size);

    mpz_add(tu_c_mpz, a_mpz, b_mpz);
    mpz_mod(tu_expected_mpz, tu_c_mpz, m);
    mpz_add(tu_partialexpected_mpz, tu_expected_mpz, m);

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz);
    if (ispmp || (!ispmp && size * 32 >= mpz_sizeinbase(m, 2) + 2)) {
        ret = ret && mpz_cmp(tu_partialexpected_mpz, tu_actual_mpz);
    }

    if (ret != 0) {
        char m_str[1024], a_str[1024], b_str[1024], c_str[1024];
        char expected_str[1024], actual_str[1024], partialexp_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        mpz_get_str(m_str, 16, m);
        mpz_get_str(a_str, 16, a_mpz);
        mpz_get_str(b_str, 16, b_mpz);
        mpz_get_str(c_str, 16, tu_c_mpz);
        mpz_get_str(partialexp_str, 16, tu_partialexpected_mpz);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
        if (ispmp) {
            printf("Partial Red: 0x%64s\n", partialexp_str);
        }

        printf("M:        0x%64s\n", m_str);
        printf("a:        0x%64s\n", a_str);
        printf("b:        0x%64s\n", b_str);
        printf("c:        0x%64s\n", c_str);
    }

    return ret;
}

int compare_with_ref_modsub(uint32_t *actual, const mpz_t a_mpz, const mpz_t b_mpz, size_t size, mpz_t m, int ispmp) {
    int ret;

    convert_to_mpz_t(tu_actual_mpz, actual, size);

    mpz_sub(tu_c_mpz, a_mpz, b_mpz);
    mpz_mod(tu_expected_mpz, tu_c_mpz, m);
    mpz_add(tu_partialexpected_mpz, tu_expected_mpz, m);

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz);
    if (ispmp || (!ispmp && size * 32 >= mpz_sizeinbase(m, 2) + 2)) {
        ret = ret && mpz_cmp(tu_partialexpected_mpz, tu_actual_mpz);
    }

    if (ret != 0) {
        char m_str[1024], a_str[1024], b_str[1024], c_str[1024];
        char expected_str[1024], actual_str[1024], partialexp_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        mpz_get_str(m_str, 16, m);
        mpz_get_str(a_str, 16, a_mpz);
        mpz_get_str(b_str, 16, b_mpz);
        mpz_get_str(c_str, 16, tu_c_mpz);
        mpz_get_str(partialexp_str, 16, tu_partialexpected_mpz);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
        if (ispmp) {
            printf("Partial Red: 0x%64s\n", partialexp_str);
        }

        printf("M:        0x%64s\n", m_str);
        printf("a:        0x%64s\n", a_str);
        printf("b:        0x%64s\n", b_str);
        printf("c:        0x%64s\n", c_str);
    }

    return ret;
}

int compare_with_ref_mod(uint32_t *actual, uint32_t *a, uint32_t *b, const mpz_t a_mpz, const mpz_t b_mpz, size_t size,
                         mpz_t m) {
    int ret;

    convert_to_mpz_t(tu_actual_mpz, actual, size);
    mpz_mul(tu_expected_mpz, a_mpz, b_mpz);
    mpz_mod(tu_expected_mpz, tu_expected_mpz, m);

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz);

    if (ret != 0) {
        char expected_str[1024], actual_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
    }

    mpz_clear(tu_actual_mpz);
    mpz_clear(tu_expected_mpz);

    return ret;
}

int compare_with_ref_modmul(uint32_t *actual, const mpz_t a_mpz, const mpz_t b_mpz, size_t size, mpz_t m) {
    int ret;

    convert_to_mpz_t(tu_actual_mpz, actual, size);

    mpz_mul(tu_c_mpz, a_mpz, b_mpz);
    mpz_mod(tu_expected_mpz, tu_c_mpz, m);
    mpz_add(tu_partialexpected_mpz, tu_expected_mpz, m);

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz) && mpz_cmp(tu_partialexpected_mpz, tu_actual_mpz);

    if (ret != 0) {
        char expected_str[1024], actual_str[1024], a_str[1024], b_str[1024], c_str[1024], realm_str[1024],
            partialexp_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        mpz_get_str(partialexp_str, 16, tu_partialexpected_mpz);
        mpz_get_str(a_str, 16, a_mpz);
        mpz_get_str(b_str, 16, b_mpz);
        mpz_get_str(c_str, 16, tu_c_mpz);
        mpz_get_str(realm_str, 16, m);
        printf("Expected:    0x%64s\n", expected_str);
        printf("Actual:      0x%64s\n", actual_str);
        printf("Partial Red: 0x%64s\n", partialexp_str);
        printf("M:           0x%64s\n", realm_str);
        printf("a:           0x%64s\n", a_str);
        printf("b:           0x%64s\n", b_str);
        printf("c:           0x%128s\n", c_str);
    }

    return ret;
}

int compare_with_ref_modred(uint32_t *actual, const mpz_t c_mpz, size_t size, mpz_t m) {
    int ret;

    convert_to_mpz_t(tu_actual_mpz, actual, size);
    mpz_mod(tu_expected_mpz, c_mpz, m);
    mpz_add(tu_partialexpected_mpz, tu_expected_mpz, m);

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz) && mpz_cmp(tu_partialexpected_mpz, tu_actual_mpz);

    if (ret != 0) {
        char expected_str[1024], actual_str[1024], c_str[1024], partialexp_str[1024], m_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        mpz_get_str(c_str, 16, c_mpz);
        mpz_get_str(m_str, 16, m);
        mpz_get_str(partialexp_str, 16, tu_partialexpected_mpz);
        printf("Expected:    0x%64s\n", expected_str);
        printf("Actual:      0x%64s\n", actual_str);
        printf("Partial Red: 0x%64s\n", partialexp_str);
        printf("M:           0x%64s\n", m_str);
        printf("Original:    0x%128s\n", c_str);
    }

    return ret;
}

int compare_with_ref_mont(uint32_t *actual, uint32_t *a, uint32_t *b, size_t size, mpz_t m) {
    int ret;

    convert_to_mpz_t(tu_a_mpz, a, size);
    convert_to_mpz_t(tu_b_mpz, b, size);

    mpz_mul(tu_expected_mpz, tu_a_mpz, tu_b_mpz);
    mpz_mod(tu_expected_mpz, tu_expected_mpz, m);
    mpz_mul(tu_expected_mpz, tu_expected_mpz, rinv_mpz);
    mpz_mod(tu_expected_mpz, tu_expected_mpz, m);

    convert_to_mpz_t(tu_actual_mpz, actual, size);

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz);

    if (ret != 0) {
        char r_str[1024], m_str[1024], a_str[1024], b_str[1024];
        char expected_str[1024], actual_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
        mpz_get_str(r_str, 16, r_mpz);
        mpz_get_str(m_str, 16, m);
        mpz_get_str(a_str, 16, tu_a_mpz);
        mpz_get_str(b_str, 16, tu_b_mpz);
        printf("R:        0x%64s\n", r_str);
        printf("M:        0x%64s\n", m_str);
        printf("a:        0x%64s\n", a_str);
        printf("b:        0x%64s\n", b_str);
    }

    return ret;
}

int compare_with_ref_redc(uint32_t *actual, mpz_t a_mpz, size_t size, mpz_t m) {
    int ret;

    mpz_mul(tu_expected_mpz, a_mpz, rinv_mpz);
    mpz_mod(tu_expected_mpz, tu_expected_mpz, m);

    convert_to_mpz_t(tu_actual_mpz, actual, size);

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz);

    if (ret != 0) {
        char r_str[1024], m_str[1024], a_str[1024];
        char expected_str[1024], actual_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
        mpz_get_str(r_str, 16, rinv_mpz);
        mpz_get_str(m_str, 16, m);
        mpz_get_str(a_str, 16, a_mpz);
        printf("Rinv:     0x%64s\n", r_str);
        printf("M:        0x%64s\n", m_str);
        printf("a:        0x%64s\n", a_str);
    }

    return ret;
}

int compare_with_ref_nres(uint32_t *actual, mpz_t a_mpz, size_t size, mpz_t m) {
    int ret;

    mpz_mul(tu_expected_mpz, a_mpz, r_mpz);
    mpz_mod(tu_expected_mpz, tu_expected_mpz, m);

    convert_to_mpz_t(tu_actual_mpz, actual, size);
    mpz_mod(tu_actual_mpz, tu_actual_mpz, m);

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz);

    if (ret != 0) {
        char r_str[1024], m_str[1024], a_str[1024];
        char expected_str[1024], actual_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
        mpz_get_str(r_str, 16, r_mpz);
        mpz_get_str(m_str, 16, m);
        mpz_get_str(a_str, 16, a_mpz);
        printf("R:        0x%64s\n", r_str);
        printf("M:        0x%64s\n", m_str);
        printf("a:        0x%64s\n", a_str);
    }

    return ret;
}

int compare_with_ref_modcmp(int actual, mpz_t a_mpz, mpz_t b_mpz, size_t size, mpz_t m) {
    int ret;

    mpz_mod(tu_a_mpz, a_mpz, m);
    mpz_mod(tu_b_mpz, b_mpz, m);

    ret = !mpz_cmp(tu_a_mpz, tu_b_mpz);

    if (ret != actual) {
        char m_str[1024], a_str[1024], b_str[1024];
        printf("Expected: 0x%d\n", ret);
        printf("Actual:   0x%d\n", actual);
        mpz_get_str(m_str, 16, m);
        mpz_get_str(a_str, 16, a_mpz);
        mpz_get_str(b_str, 16, b_mpz);
        printf("M:        0x%64s\n", m_str);
        printf("a:        0x%64s\n", a_str);
        printf("b:        0x%64s\n", b_str);
    }

    return ret != actual;
}

int compare_with_ref_modsign(int actual, mpz_t a_mpz, size_t size, mpz_t m) {
    int ret;

    mpz_mod(tu_a_mpz, a_mpz, m);

    ret = mpz_odd_p(tu_a_mpz);

    if (ret != actual) {
        char m_str[1024], a_str[1024];
        printf("Expected: 0x%d\n", ret);
        printf("Actual:   0x%d\n", actual);
        mpz_get_str(m_str, 16, m);
        mpz_get_str(a_str, 16, a_mpz);
        printf("M:        0x%64s\n", m_str);
        printf("a:        0x%64s\n", a_str);
    }

    return !(ret == actual);
}

int compare_with_ref_modsign_mont(int actual, mpz_t a_mpz, size_t size, mpz_t m) {
    int ret;

    mpz_mul(tu_a_mpz, a_mpz, rinv_mpz);
    mpz_mod(tu_a_mpz, tu_a_mpz, m);

    ret = mpz_odd_p(tu_a_mpz);

    if (ret != actual) {
        char r_str[1024], m_str[1024], a_str[1024];
        printf("Expected: 0x%d\n", ret);
        printf("Actual:   0x%d\n", actual);
        mpz_get_str(r_str, 16, rinv_mpz);
        mpz_get_str(m_str, 16, m);
        mpz_get_str(a_str, 16, a_mpz);
        printf("Rinv:     0x%64s\n", r_str);
        printf("M:        0x%64s\n", m_str);
        printf("a:        0x%64s\n", a_str);
    }

    return !(ret == actual);
}
int compare_with_ref_mod2r(uint32_t *actual, unsigned int r, size_t size, mpz_t m) {
    int ret;

    mpz_set_ui(tu_a_mpz, 1);
    int mbits = mpz_sizeinbase(m, 2);
    if (mbits % 32 != 0) {
        mbits++;
    }
    mpz_set_ui(tu_expected_mpz, 0);
    if (r < mbits) {
        mpz_mul_2exp(tu_expected_mpz, tu_a_mpz, r);
    }

    convert_to_mpz_t(tu_actual_mpz, actual, size);
    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz);

    if (ret != 0) {
        char m_str[1024];
        char expected_str[1024], actual_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        mpz_get_str(m_str, 16, m);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
        printf("M:        0x%64s\n", m_str);
        printf("r:        0x%u\n", r);
        printf("mbits:    0x%u\n", mbits);
        printf("sizebase: 0x%u\n", mpz_sizeinbase(m, 2));
    }

    return ret;
}

int compare_with_ref_mod2r_mont(uint32_t *actual, unsigned int r, size_t size, mpz_t m) {
    int ret;

    mpz_set_ui(tu_a_mpz, 1);
    mpz_set_ui(tu_expected_mpz, 0);
    if (r < size * 32) {
        mpz_mul_2exp(tu_expected_mpz, tu_a_mpz, r);

        mpz_mul(tu_expected_mpz, tu_expected_mpz, r_mpz);
        mpz_mod(tu_expected_mpz, tu_expected_mpz, m);
    }

    convert_to_mpz_t(tu_actual_mpz, actual, size);
    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz);

    if (ret != 0) {
        char m_str[1024];
        char expected_str[1024], actual_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        mpz_get_str(m_str, 16, m);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
        printf("M:        0x%64s\n", m_str);
        printf("r:        0x%u\n", r);
    }

    return ret;
}

int compare_with_ref_modfsb(uint32_t *actual, int r, mpz_t a_mpz, size_t size, mpz_t m) {
    int ret, r_exp;

    mpz_mul_ui(tu_lim_mpz, m, 2);

    convert_to_mpz_t(tu_actual_mpz, actual, size);
    mpz_mod(tu_expected_mpz, a_mpz, m);
    r_exp = !(mpz_cmp(tu_expected_mpz, a_mpz));

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz);

    ret = ret != 0 || r_exp != r;

    if (ret != 0) {
        char m_str[1024], a_str[1024], lim_str[1024];
        char expected_str[1024], actual_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
        mpz_get_str(m_str, 16, m);
        mpz_get_str(a_str, 16, a_mpz);
        mpz_get_str(lim_str, 16, tu_lim_mpz);
        printf("M:        0x%64s\n", m_str);
        printf("Lim:      0x%64s\n", lim_str);
        printf("a:        0x%64s\n", a_str);
        printf("r:        0x%d\n", r);
        printf("r_exp:    0x%d\n", r_exp);
    }

    return ret;
}

// int compare_with_ref_modneg(uint32_t *actual, mpz_t a_mpz, size_t size, mpz_t m) {
//     int ret;

//     mpz_neg(expected_mpz, a_mpz);
//     mpz_mod(expected_mpz, expected_mpz, m);

//     convert_to_mpz_t(actual_mpz, actual, size);

//     ret = mpz_cmp(expected_mpz, actual_mpz);

//     if (ret != 0) {
//         char m_str[1024], a_str[1024];
//         char expected_str[1024], actual_str[1024];
//         mpz_get_str(expected_str, 16, expected_mpz);
//         mpz_get_str(actual_str, 16, actual_mpz);
//         printf("Expected: 0x%64s\n", expected_str);
//         printf("Actual:   0x%64s\n", actual_str);
//         mpz_get_str(m_str, 16, m);
//         mpz_get_str(a_str, 16, a_mpz);
//         printf("M:        0x%64s\n", m_str);
//         printf("a:        0x%64s\n", a_str);
//     }

//     return ret;
// }

int compare_with_ref_modsqrt(uint32_t *actual, mpz_t a_mpz, size_t size, mpz_t m) {
    int ret;

    convert_to_mpz_t(tu_actual_mpz, actual, size);
    mpz_powm_ui(tu_actual2_mpz, tu_actual_mpz, 2, m);

    ret = mpz_cmp(a_mpz, tu_actual2_mpz);

    if (ret != 0) {
        char m_str[1024], a_str[1024];
        char actual_str[1024], actual2_str[1024];
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        mpz_get_str(actual2_str, 16, tu_actual2_mpz);
        printf("Actual:   0x%64s\n", actual_str);
        printf("Actual^2: 0x%64s\n", actual2_str);
        mpz_get_str(m_str, 16, m);
        mpz_get_str(a_str, 16, a_mpz);
        printf("M:        0x%64s\n", m_str);
        printf("a:        0x%64s\n", a_str);
    }

    return ret;
}

int compare_with_ref_modshr(int shift, uint32_t *actual, mpz_t a_mpz, size_t size) {
    int ret;

    mpz_set_ui(tu_factor_mpz, 1);
    mpz_mul_2exp(tu_factor_mpz, tu_factor_mpz, shift);
    mpz_fdiv_q(tu_expected_mpz, a_mpz, tu_factor_mpz);

    convert_to_mpz_t(tu_actual_mpz, actual, size);

    ret = mpz_cmp(tu_actual_mpz, tu_expected_mpz);

    if (ret != 0) {
        char a_str[1024];
        char expected_str[1024], actual_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
        mpz_get_str(a_str, 16, a_mpz);
        printf("a:        0x%64s\n", a_str);
        printf("Shift:    %d\n", shift);
    }

    return ret;
}

int compare_with_ref_modshl(int shift, uint32_t *actual, mpz_t a_mpz, size_t size, mpz_t m) {
    int ret;

    mpz_set_ui(tu_factor_mpz, 1);
    mpz_mul_2exp(tu_factor_mpz, tu_factor_mpz, shift);
    mpz_mul(tu_expected_mpz, a_mpz, tu_factor_mpz);
    mpz_mod(tu_expected_mpz, tu_expected_mpz, r_mpz);

    convert_to_mpz_t(tu_actual_mpz, actual, size);

    ret = mpz_cmp(tu_actual_mpz, tu_expected_mpz);

    if (ret != 0) {
        char a_str[1024];
        char expected_str[1024], actual_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
        mpz_get_str(a_str, 16, a_mpz);
        printf("a:        0x%64s\n", a_str);
        printf("Shift:    %d\n", shift);
    }

    return ret;
}

int compare_with_ref_modis1(int res, mpz_t a_mpz) {
    int ret;

    ret = mpz_cmp_ui(a_mpz, 1);

    if (ret == 0 && res == 1) return ret;

    if (res && !ret) {
        char a_str[1024];
        mpz_get_str(a_str, 16, a_mpz);
        printf("a:        0x%64s\n", a_str);
        printf("ret:      %d\n", ret);
    }

    return res && !ret;
}

int compare_with_ref_modis0(int res, mpz_t a_mpz) {
    int ret;

    ret = mpz_cmp_ui(a_mpz, 0);

    if (ret == 0 && res == 1) return ret;

    if (res && !ret) {
        char a_str[1024];
        mpz_get_str(a_str, 16, a_mpz);
        printf("a:        0x%64s\n", a_str);
        printf("ret:      %d\n", ret);
    }

    return res && !ret;
}

int compare_with_ref_modinv(uint32_t *actual, mpz_t a_mpz, size_t size, mpz_t m) {
    int ret;

    // if a_mpz is 0, then mpz_invert below silently fails, not setting
    // expected_mpz. By setting it to zero here, we ensure the test does
    // not fail, due to reusing whatever value was previously in expected_mpz.
    mpz_set_ui(tu_expected_mpz, 0);

    mpz_invert(tu_expected_mpz, a_mpz, m);

    convert_to_mpz_t(tu_actual_mpz, actual, size);

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz);

    if (ret != 0) {
        char m_str[1024], a_str[1024];
        char expected_str[1024], actual_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
        mpz_get_str(m_str, 16, m);
        mpz_get_str(a_str, 16, a_mpz);
        printf("M:        0x%64s\n", m_str);
        printf("a:        0x%64s\n", a_str);
    }

    return ret;
}

int compare_with_ref_modcsw(int move, uint32_t *amv, uint32_t *bmv, mpz_t a_mpz, mpz_t b_mpz, size_t size) {
    int ret;

    convert_to_mpz_t(tu_a_mpz, amv, size);
    convert_to_mpz_t(tu_b_mpz, bmv, size);

    if (move == 0)
        ret = mpz_cmp(tu_a_mpz, a_mpz) || mpz_cmp(tu_b_mpz, b_mpz);
    else
        ret = mpz_cmp(tu_a_mpz, b_mpz) || mpz_cmp(tu_b_mpz, a_mpz);

    if (ret != 0) {
        char amv_str[1024], bmv_str[1024];
        char ampz_str[1024], bmpz_str[1024];
        mpz_get_str(amv_str, 16, tu_a_mpz);
        mpz_get_str(bmv_str, 16, tu_b_mpz);
        printf("amv:      0x%64s\n", amv_str);
        printf("bmv:      0x%64s\n", bmv_str);
        printf("Move:     %d\n", move);
        mpz_get_str(ampz_str, 16, a_mpz);
        mpz_get_str(bmpz_str, 16, b_mpz);
        printf("a_mpz:    0x%64s\n", ampz_str);
        printf("b_mpz:    0x%64s\n", bmpz_str);
    }

    return ret;
}

int compare_with_ref_modcmv(int move, uint32_t *bmv, mpz_t a_mpz, mpz_t b_mpz, size_t size) {
    int ret;

    convert_to_mpz_t(tu_b_mpz, bmv, size);

    if (move == 0)
        ret = mpz_cmp(tu_b_mpz, b_mpz);
    else
        ret = mpz_cmp(tu_b_mpz, a_mpz);

    if (ret != 0) {
        char bmv_str[1024];
        char ampz_str[1024], bmpz_str[1024];
        mpz_get_str(bmv_str, 16, tu_b_mpz);
        printf("bmv:      0x%64s\n", bmv_str);
        printf("Move:     %d\n", move);
        mpz_get_str(ampz_str, 16, a_mpz);
        mpz_get_str(bmpz_str, 16, b_mpz);
        printf("a_mpz:    0x%64s\n", ampz_str);
        printf("b_mpz:    0x%64s\n", bmpz_str);
    }

    return ret;
}

int compare_with_ref_modmul_mont(uint32_t *actual, const mpz_t ampz, const mpz_t bmpz, size_t size, mpz_t m) {
    int ret;

    mpz_mul(tu_expected_mpz, ampz, bmpz);
    mpz_mod(tu_expected_mpz, tu_expected_mpz, m);
    mpz_mul(tu_expected_mpz, tu_expected_mpz, rinv_mpz);
    mpz_mod(tu_expected_mpz, tu_expected_mpz, m);

    convert_to_mpz_t(tu_actual_mpz, actual, size);

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz);

    if (ret != 0) {
        char r_str[1024], m_str[1024], a_str[1024], b_str[1024];
        char expected_str[1024], actual_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
        mpz_get_str(r_str, 16, r_mpz);
        mpz_get_str(m_str, 16, m);
        mpz_get_str(a_str, 16, ampz);
        mpz_get_str(b_str, 16, bmpz);
        printf("R:        0x%64s\n", r_str);
        printf("M:        0x%64s\n", m_str);
        printf("a:        0x%64s\n", a_str);
        printf("b:        0x%64s\n", b_str);
    }

    return ret;
}

int compare_with_ref_modmul_mont_2p(uint32_t *actual, const mpz_t ampz, const mpz_t bmpz, size_t size, mpz_t m) {
    int ret;

    mpz_mul(tu_expected_mpz, ampz, bmpz);
    mpz_mod(tu_expected_mpz, tu_expected_mpz, m);
    mpz_mul(tu_expected_mpz, tu_expected_mpz, rinv_mpz);
    mpz_mod(tu_expected_mpz, tu_expected_mpz, m);

    convert_to_mpz_t(tu_actual_mpz, actual, size);

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz);

    if (ret != 0) {
        mpz_sub(tu_actual2_mpz, tu_actual_mpz, m);
        ret = mpz_cmp(tu_expected_mpz, tu_actual2_mpz);
        if (ret != 0) {
            char r_str[1024], m_str[1024], a_str[1024], b_str[1024];
            char expected_str[1024], actual_str[1024], actual2_str[1024];
            mpz_get_str(expected_str, 16, tu_expected_mpz);
            mpz_get_str(actual_str, 16, tu_actual_mpz);
            mpz_get_str(actual2_str, 16, tu_actual2_mpz);
            printf("Expected: 0x%64s\n", expected_str);
            printf("Actual:   0x%64s\n", actual_str);
            printf("Actual2p: 0x%64s\n", actual2_str);
            mpz_get_str(r_str, 16, r_mpz);
            mpz_get_str(m_str, 16, m);
            mpz_get_str(a_str, 16, ampz);
            mpz_get_str(b_str, 16, bmpz);
            printf("R:        0x%64s\n", r_str);
            printf("M:        0x%64s\n", m_str);
            printf("a:        0x%64s\n", a_str);
            printf("b:        0x%64s\n", b_str);
        }
    }

    return ret;
}

int compare_with_ref_congruent(uint32_t *actual, uint32_t *a, uint32_t *b, const mpz_t a_mpz, const mpz_t b_mpz,
                               size_t size, mpz_t m) {
    int ret;

    convert_to_mpz_t(tu_actual_mpz, actual, size);
    mpz_mul(tu_expected_mpz, a_mpz, b_mpz);

    ret = mpz_congruent_p(tu_expected_mpz, tu_actual_mpz, m);

    if (ret == 0) {
        char expected_str[1024], actual_str[1024];
        mpz_mod(tu_expected_mpz, tu_expected_mpz, m);
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
    }

    return ret;
}

int compare_with_ref_modimp(uint32_t* actual, const mpz_t a_mpz, size_t size) {
    int ret;

    mpz_set(tu_expected_mpz, a_mpz);
    convert_to_mpz_t(tu_actual_mpz, actual, size);

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz);

    if (ret != 0) {
        char r_str[1024], m_str[1024], a_str[1024];
        char expected_str[1024], actual_str[1024];

        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
        mpz_get_str(r_str, 16, r_mpz);
        mpz_get_str(m_str, 16, usedprime);
        mpz_get_str(a_str, 16, a_mpz);
        printf("R:        0x%64s\n", r_str);
        printf("M:        0x%64s\n", m_str);
        printf("a:        0x%64s\n", a_str);
        printf("Buffer:   0x");
        for (int i = size - 1; i >= 0; i--) {
            printf("%08x", actual[i]);
        }
        printf("\n");
    }

    return ret;
}

int compare_with_ref_modimp_mont(uint32_t* actual, const mpz_t a_mpz, size_t size) {
    int ret;

    mpz_mul(tu_expected_mpz, a_mpz, r_mpz);
    mpz_mod(tu_expected_mpz, tu_expected_mpz, realprime);
    if (size * 32 >= mpz_sizeinbase(realprime, 2) + 2) {
        mpz_add(tu_partialexpected_mpz, tu_expected_mpz, realprime);
    }

    convert_to_mpz_t(tu_actual_mpz, actual, size);

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz) && mpz_cmp(tu_partialexpected_mpz, tu_actual_mpz);

    if (ret != 0) {
        char r_str[1024], m_str[1024], a_str[1024];
        char expected_str[1024], actual_str[1024];

        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
        mpz_get_str(r_str, 16, r_mpz);
        mpz_get_str(m_str, 16, realprime);
        mpz_get_str(a_str, 16, a_mpz);
        printf("R:        0x%64s\n", r_str);
        printf("M:        0x%64s\n", m_str);
        printf("a:        0x%64s\n", a_str);
        printf("Buffer:   0x");
        for (int i = size - 1; i >= 0; i--) {
            printf("%08x", actual[i]);
        }
        printf("\n");
    }

    return ret;
}

int compare_with_ref_modexp(const char* actual, const mpz_t a_mpz, size_t size) {
    char a[size * 4];
    int ret;
    size_t sz, bytes;

    mpz_mod(tu_a_mpz, a_mpz, realprime);
    bytes = (mpz_sizeinbase(tu_a_mpz, 2) + 7) / 8;

    memset(a, 0, size * 4);

    mpz_export(&a[size * 4 - bytes], &sz, 1, 1, 0, 0, tu_a_mpz);

    ret = memcmp(a, actual, size * 4);

    if (ret != 0) {
        char r_str[1024], m_str[1024], a_str[1024];

        printf("Expected: 0x");
        for (int i = 0; i < size * 4; i++) {
            printf("%02x", a[i]);
        }
        printf("\n");
        printf("Actual:   0x");
        for (int i = 0; i < size * 4; i++) {
            printf("%02x", actual[i]);
        }
        printf("\n");
        mpz_get_str(r_str, 16, r_mpz);
        mpz_get_str(m_str, 16, usedprime);
        mpz_get_str(a_str, 16, a_mpz);
        printf("R:        0x%64s\n", r_str);
        printf("M:        0x%64s\n", m_str);
        printf("a:        0x%64s\n", a_str);
    }

    return ret;
}

int compare_with_ref_modexp_mont(const char* actual, const mpz_t a_mpz, size_t size) {
    char a[size * 4];
    int ret;
    size_t sz, bytes;

    mpz_mul(tu_a_mpz, a_mpz, rinv_mpz);
    mpz_mod(tu_a_mpz, tu_a_mpz, realprime);
    bytes = (mpz_sizeinbase(tu_a_mpz, 2) + 7) / 8;

    memset(a, 0, size * 4);

    mpz_export(&a[size * 4 - bytes], &sz, 1, 1, 0, 0, tu_a_mpz);

    ret = memcmp(a, actual, size * 4);

    if (ret != 0) {
        char rinv_str[1024], m_str[1024], a_str[1024];

        printf("Expected: 0x");
        for (int i = 0; i < size * 4; i++) {
            printf("%02x", a[i]);
        }
        printf("%\n");
        printf("Actual:   0x");
        for (int i = 0; i < size * 4; i++) {
            printf("%02x", actual[i]);
        }
        printf("%\n");
        mpz_get_str(rinv_str, 16, rinv_mpz);
        mpz_get_str(m_str, 16, usedprime);
        mpz_get_str(a_str, 16, a_mpz);
        printf("Rinv:     0x%64s\n", rinv_str);
        printf("M:        0x%64s\n", m_str);
        printf("a:        0x%64s\n", a_str);
    }

    return ret;
}

int compare_with_ref_acpt(uint32_t *actual, const mpz_t a_mpz, const mpz_t b_mpz, size_t size, mpz_t m) {
    int ret;

    convert_to_mpz_t(tu_actual_mpz, actual, size);
    mpz_add(tu_t_mpz, a_mpz, b_mpz);
    mpz_mod(tu_t_mpz, tu_t_mpz, m);
    mpz_sub(tu_c_mpz, a_mpz, b_mpz);
    mpz_mod(tu_c_mpz, tu_c_mpz, m);
    mpz_mul(tu_a_mpz, tu_t_mpz, tu_c_mpz);
    mpz_mod(tu_a_mpz, tu_a_mpz, m);
    mpz_mul(tu_c_mpz, tu_a_mpz, tu_a_mpz);
    mpz_mod(tu_c_mpz, tu_c_mpz, m);
    mpz_invert(tu_c_mpz, tu_c_mpz, m);

    // mpz_mod(expected_mpz, c_mpz, m);
    mpz_mod(tu_expected_mpz, tu_c_mpz, m);

    ret = mpz_cmp(tu_expected_mpz, tu_actual_mpz);

    if (ret != 0) {
        char expected_str[1024], actual_str[1024], a_str[1024], b_str[1024], c_str[1024];
        mpz_get_str(expected_str, 16, tu_expected_mpz);
        mpz_get_str(actual_str, 16, tu_actual_mpz);
        mpz_get_str(a_str, 16, a_mpz);
        mpz_get_str(b_str, 16, b_mpz);
        // mpz_get_str(c_str, 16, c_mpz);
        mpz_get_str(c_str, 16, tu_c_mpz);
        printf("Expected: 0x%64s\n", expected_str);
        printf("Actual:   0x%64s\n", actual_str);
        printf("a:        0x%64s\n", a_str);
        printf("b:        0x%64s\n", b_str);
        printf("c:        0x%64s\n", c_str);
    }

    return ret;
}

static void callback_fixed_tests(int nlimbs, int test_number, uint32_t *man_tests) {
    memset(man_tests, 0, nlimbs * sizeof(uint32_t));

    switch (test_number) {
        case 0:
            man_tests[0] = 1;
            break;
        case 1:
            break;
        case 2:
            for (int i = 0; i < nlimbs; i++) {
                man_tests[i] = -1;
            }
            break;
        case 3:
            man_tests[nlimbs - 1] = 0x8000000;
            break;
        case 4:
            man_tests[0] = -1;
            break;
        case 5:
            man_tests[nlimbs - 1] = -1;
            break;
        case 6:
            mpz_sub_ui(a_mpz, usedprime, 1);
            convert_to_array(man_tests, a_mpz, nlimbs);
            break;
        case 7:
            mpz_sub_ui(a_mpz, realprime, 1);
            convert_to_array(man_tests, a_mpz, nlimbs);
            break;
        case 8:
            mpz_set_ui(a_mpz, 1);
            mpz_mul_2exp(a_mpz, a_mpz, nlimbs * 32 - 1);
            mpz_add_ui(a_mpz, a_mpz, 1);
            convert_to_array(man_tests, a_mpz, nlimbs);
            break;
        case 9:
            mpz_set_ui(a_mpz, 1);
            mpz_mul_2exp(a_mpz, a_mpz, nlimbs * 32);
            mpz_sub_ui(a_mpz, a_mpz, 1);
            convert_to_array(man_tests, a_mpz, nlimbs);
            break;
        case 10:
            mpz_sub_ui(a_mpz, a_mpz, 1);
            convert_to_array(man_tests, a_mpz, nlimbs);
            break;
        default:
            mpz_set_ui(a_mpz, 1);
            mpz_mul_2exp(a_mpz, a_mpz, (test_number - 10) * 16);
            mpz_sub(a_mpz, realprime, a_mpz);
            convert_to_array(man_tests, a_mpz, nlimbs);
            break;
    }
}

void test_mul_fixed(int nlimbs, void (*mul)(const uint32_t *, const uint32_t *, uint32_t *)) {
    uint32_t c[2 * nlimbs], man_tests_i[nlimbs], man_tests_j[nlimbs];

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests_i);
        for (int j = 0; j < 11 + (nlimbs * 2 - 1); j++) {
            callback_fixed_tests(nlimbs, j, man_tests_j);

            mul(man_tests_i, man_tests_j, c);

            convert_to_mpz_t(a_mpz, man_tests_i, nlimbs);
            convert_to_mpz_t(b_mpz, man_tests_j, nlimbs);

            TEST_ASSERT(compare_with_ref_mul(c, man_tests_i, man_tests_j, a_mpz, b_mpz, nlimbs) == 0);
        }
    }
}

void test_mul_random(int nlimbs, void (*mul)(const uint32_t *, const uint32_t *, uint32_t *)) {
    uint32_t a[nlimbs], b[nlimbs], c[2 * nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);
        mpz_urandomm(b_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);
        convert_to_array(b, b_mpz, nlimbs);

        mul(a, b, c);

        TEST_ASSERT(compare_with_ref_mul(c, a, b, a_mpz, b_mpz, nlimbs) == 0);
    }
}

void test_modmul_fixed(int nlimbs, int ispmp, void (*modmul)(const uint32_t *, const uint32_t *, uint32_t *),
                       int (*compare_with_ref_modmul)(uint32_t *, const mpz_t, const mpz_t, size_t, mpz_t)) {
    uint32_t c[2 * nlimbs], man_tests_i[nlimbs], man_tests_j[nlimbs];

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests_i);
        for (int j = 0; j < 11 + (nlimbs * 2 - 1); j++) {
            callback_fixed_tests(nlimbs, j, man_tests_j);

            convert_to_mpz_t(a_mpz, man_tests_i, nlimbs);
            convert_to_mpz_t(b_mpz, man_tests_j, nlimbs);
            mpz_mod(a_mpz, a_mpz, ispmp ? maxbound : usedprime);
            mpz_mod(b_mpz, b_mpz, ispmp ? maxbound : usedprime);
            convert_to_array(man_tests_i, a_mpz, nlimbs);
            convert_to_array(man_tests_j, b_mpz, nlimbs);

            modmul(man_tests_i, man_tests_j, c);

            TEST_ASSERT(compare_with_ref_modmul(c, a_mpz, b_mpz, nlimbs, realprime) == 0);
        }
    }
}

void test_modmul_random(int nlimbs, void (*modmul)(const uint32_t *, const uint32_t *, uint32_t *),
                        int (*compare_with_ref_modmul)(uint32_t *, const mpz_t, const mpz_t, size_t, mpz_t)) {
    uint32_t a[nlimbs], b[nlimbs], c[2 * nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);
        mpz_urandomm(b_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);
        convert_to_array(b, b_mpz, nlimbs);

        modmul(a, b, c);

        TEST_ASSERT(compare_with_ref_modmul(c, a_mpz, b_mpz, nlimbs, realprime) == 0);
    }
}

void test_sqr_fixed(int nlimbs, void (*sqr)(const uint32_t *, uint32_t *)) {
    uint32_t c[2 * nlimbs], man_tests[nlimbs];

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests);

        sqr(man_tests, c);

        convert_to_mpz_t(a_mpz, man_tests, nlimbs);

        TEST_ASSERT(compare_with_ref_mul(c, man_tests, man_tests, a_mpz, a_mpz, nlimbs) == 0);
    }
}

void test_sqr_random(int nlimbs, void (*sqr)(const uint32_t *, uint32_t *)) {
    uint32_t a[nlimbs], c[2 * nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);

        sqr(a, c);

        TEST_ASSERT(compare_with_ref_mul(c, a, a, a_mpz, a_mpz, nlimbs) == 0);
    }
}

void test_modsqr_fixed(int nlimbs, int ispmp, void (*modsqr)(const uint32_t *, uint32_t *),
                       int (*compare_with_ref_modmul)(uint32_t *, const mpz_t, const mpz_t, size_t, mpz_t)) {
    uint32_t c[2 * nlimbs], man_tests[nlimbs];

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests);

        convert_to_mpz_t(a_mpz, man_tests, nlimbs);
        mpz_mod(a_mpz, a_mpz, ispmp ? maxbound : usedprime);
        convert_to_array(man_tests, a_mpz, nlimbs);

        modsqr(man_tests, c);

        TEST_ASSERT(compare_with_ref_modmul(c, a_mpz, a_mpz, nlimbs, realprime) == 0);
    }
}

void test_modsqr_random(int nlimbs, void (*modsqr)(const uint32_t *, uint32_t *),
                        int (*compare_with_ref_modmul)(uint32_t *, const mpz_t, const mpz_t, size_t, mpz_t)) {
    uint32_t a[nlimbs], c[2 * nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);

        modsqr(a, c);

        TEST_ASSERT(compare_with_ref_modmul(c, a_mpz, a_mpz, nlimbs, realprime) == 0);
    }
}

void test_modred_fixed(int nlimbs, int n, void (*modred)(const uint32_t *, uint32_t *)) {
    uint32_t c[2 * nlimbs], r[nlimbs], man_tests_i[nlimbs], man_tests_j[nlimbs];

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests_i);
        for (int j = 0; j < 11 + (nlimbs * 2 - 1); j++) {
            callback_fixed_tests(nlimbs, j, man_tests_j);

            convert_to_mpz_t(a_mpz, man_tests_i, nlimbs);
            convert_to_mpz_t(b_mpz, man_tests_j, nlimbs);
            mpz_mod(a_mpz, a_mpz, maxbound);
            mpz_mod(b_mpz, b_mpz, maxbound);
            mpz_mul(c_mpz, a_mpz, b_mpz);
            convert_to_array(man_tests_i, a_mpz, nlimbs);
            convert_to_array(man_tests_j, b_mpz, nlimbs);
            convert_to_array(c, c_mpz, 2 * nlimbs);

            modred(c, r);

            TEST_ASSERT(compare_with_ref_modred(r, c_mpz, nlimbs, realprime) == 0);
        }
    }
}

void test_modred_inplace_fixed(int nlimbs, int n, void (*modred)(uint32_t *)) {
    uint32_t c[2 * nlimbs], man_tests_i[nlimbs], man_tests_j[nlimbs];

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests_i);
        for (int j = 0; j < 11 + (nlimbs * 2 - 1); j++) {
            callback_fixed_tests(nlimbs, j, man_tests_j);

            convert_to_mpz_t(a_mpz, man_tests_i, nlimbs);
            convert_to_mpz_t(b_mpz, man_tests_j, nlimbs);
            mpz_mod(a_mpz, a_mpz, maxbound);
            mpz_mod(b_mpz, b_mpz, maxbound);
            mpz_mul(c_mpz, a_mpz, b_mpz);
            convert_to_array(man_tests_i, a_mpz, nlimbs);
            convert_to_array(man_tests_j, b_mpz, nlimbs);
            convert_to_array(c, c_mpz, 2 * nlimbs);

            modred(c);

            TEST_ASSERT(compare_with_ref_modred(c, c_mpz, nlimbs, realprime) == 0);
        }
    }
}

void test_modred_random(int nlimbs, int n, void (*modred)(const uint32_t *, uint32_t *)) {
    uint32_t c[2 * nlimbs], r[nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomb(c_mpz, state, 2 * n);

        convert_to_array(c, c_mpz, 2 * nlimbs);

        modred(c, r);

        TEST_ASSERT(compare_with_ref_modred(r, c_mpz, nlimbs, realprime) == 0);
    }
}

void test_modred_inplace_random(int nlimbs, int n, void (*modred)(uint32_t *)) {
    uint32_t c[2 * nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomb(c_mpz, state, 2 * n);

        convert_to_array(c, c_mpz, 2 * nlimbs);

        modred(c);

        TEST_ASSERT(compare_with_ref_modred(c, c_mpz, nlimbs, realprime) == 0);
    }
}

void test_modneg_fixed(int nlimbs, int ispmp, void (*modneg)(const uint32_t *, uint32_t *)) {
    uint32_t c[nlimbs], man_tests[nlimbs];

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests);

        convert_to_mpz_t(a_mpz, man_tests, nlimbs);
        mpz_mod(a_mpz, a_mpz, usedprime);
        convert_to_array(man_tests, a_mpz, nlimbs);

        modneg(man_tests, c);

        TEST_ASSERT(compare_with_ref_modsub(c, zero_mpz, a_mpz, nlimbs, usedprime, ispmp) == 0);
    }
}

void test_modneg_random(int nlimbs, int ispmp, void (*modneg)(const uint32_t *, uint32_t *)) {
    uint32_t a[nlimbs], c[nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);

        modneg(a, c);

        TEST_ASSERT(compare_with_ref_modsub(c, zero_mpz, a_mpz, nlimbs, usedprime, ispmp) == 0);
    }
}

void test_op2inputs_fixed(int nlimbs, int ispmp, int issub, void (*op)(const uint32_t *, const uint32_t *, uint32_t *),
                          int (*compare_with_ref)(uint32_t *, const mpz_t, const mpz_t, size_t, mpz_t, int)) {
    uint32_t c[2 * nlimbs], man_tests_i[nlimbs], man_tests_j[nlimbs];

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests_i);
        for (int j = 0; j < 11 + (nlimbs * 2 - 1); j++) {
            callback_fixed_tests(nlimbs, j, man_tests_j);

            convert_to_mpz_t(a_mpz, man_tests_i, nlimbs);
            convert_to_mpz_t(b_mpz, man_tests_j, nlimbs);
            mpz_mod(a_mpz, a_mpz, (ispmp && !issub) ? maxbound : usedprime);
            mpz_mod(b_mpz, b_mpz, (ispmp && !issub) ? maxbound : usedprime);
            convert_to_array(man_tests_i, a_mpz, nlimbs);
            convert_to_array(man_tests_j, b_mpz, nlimbs);

            op(man_tests_i, man_tests_j, c);

            TEST_ASSERT(compare_with_ref(c, a_mpz, b_mpz, nlimbs, realprime, ispmp) == 0);
        }
    }
}

void test_op2inputs_random(int nlimbs, int ispmp, int zero_a,
                           void (*op)(const uint32_t *, const uint32_t *, uint32_t *),
                           int (*compare_with_ref)(uint32_t *, const mpz_t, const mpz_t, size_t, mpz_t, int)) {
    uint32_t a[nlimbs], b[nlimbs], c[2 * nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        if (zero_a) {
            mpz_set_ui(a_mpz, 0);
        }
        else {
            mpz_urandomm(a_mpz, state, usedprime);
        }
        mpz_urandomm(b_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);
        convert_to_array(b, b_mpz, nlimbs);

        op(a, b, c);

        TEST_ASSERT(compare_with_ref(c, a_mpz, b_mpz, nlimbs, realprime, ispmp) == 0);
    }
}

void test_modmli_fixed(int nlimbs, void (*modmli)(const uint32_t *, const uint32_t, uint32_t *s)) {
    uint32_t b, c[nlimbs], man_tests[nlimbs];

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests);
        mpz_urandomb(b_mpz, state, 31);
        mpz_add_ui(b_mpz, b_mpz, 1);
        b = mpz_get_ui(b_mpz);

        convert_to_mpz_t(a_mpz, man_tests, nlimbs);
        mpz_mod(a_mpz, a_mpz, usedprime);
        convert_to_array(man_tests, a_mpz, nlimbs);

        modmli(man_tests, b, c);

        TEST_ASSERT(compare_with_ref_modmul(c, a_mpz, b_mpz, nlimbs, realprime) == 0);
    }
}

void test_modmli_random(int nlimbs, void (*modmli)(const uint32_t *, const uint32_t, uint32_t *s)) {
    uint32_t a[nlimbs], b, c[nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);
        mpz_urandomb(b_mpz, state, 31);
        mpz_add_ui(b_mpz, b_mpz, 1);

        convert_to_array(a, a_mpz, nlimbs);
        b = mpz_get_ui(b_mpz);

        modmli(a, b, c);

        TEST_ASSERT(compare_with_ref_modmul(c, a_mpz, b_mpz, nlimbs, realprime) == 0);
    }
}

void test_redc_fixed(int nlimbs, int ispmp, void (*redc)(const uint32_t *, uint32_t *), int (*modfsb)(uint32_t *)) {
    uint32_t b[nlimbs], man_tests[nlimbs];
    char testv;

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests);

        convert_to_mpz_t(a_mpz, man_tests, nlimbs);
        mpz_mod(a_mpz, a_mpz, usedprime);
        convert_to_array(man_tests, a_mpz, nlimbs);

        redc(man_tests, b);

        if (ispmp) {
            modfsb(man_tests);

            testv = 0;

            for (int j = 0; j < nlimbs; j++) {
                if (man_tests[j] != b[j]) {
                    testv = 1;
                }
            }

            TEST_ASSERT(testv == 0);
        }
        else {
            TEST_ASSERT(compare_with_ref_redc(b, a_mpz, nlimbs, realprime) == 0);
        }
    }
}

void test_redc_random(int nlimbs, int ispmp, void (*redc)(const uint32_t *, uint32_t *), int (*modfsb)(uint32_t *)) {
    uint32_t a[nlimbs], b[nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);

        redc(a, b);

        if (ispmp) {
            modfsb(a);
            char testv = 0;
            for (int j = 0; j < nlimbs; j++) {
                if (a[j] != b[j]) {
                    testv = 1;
                }
            }

            TEST_ASSERT(testv == 0);
        }
        else {
            TEST_ASSERT(compare_with_ref_redc(b, a_mpz, nlimbs, realprime) == 0);
        }
    }
}

void test_modcmp_random(int nlimbs, int ispmp, int (*modcmp)(const uint32_t *, const uint32_t *)) {
    uint32_t a[nlimbs], b[nlimbs];
    int eq;

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, ispmp ? maxbound : usedprime);
        mpz_urandomm(b_mpz, state, ispmp ? maxbound : usedprime);

        convert_to_array(a, a_mpz, nlimbs);
        convert_to_array(b, b_mpz, nlimbs);

        eq = modcmp(a, b);

        TEST_ASSERT(compare_with_ref_modcmp(eq, a_mpz, b_mpz, nlimbs, realprime) == 0);
    }

    for (int i = 0; i < mpz_sizeinbase(usedprime, 2); i++) {
        mpz_urandomm(a_mpz, state, ispmp ? maxbound : usedprime);
        mpz_set(b_mpz, a_mpz);
        mpz_combit(b_mpz, i);

        convert_to_array(a, a_mpz, nlimbs);
        convert_to_array(b, b_mpz, nlimbs);

        eq = modcmp(a, b);

        TEST_ASSERT(compare_with_ref_modcmp(eq, a_mpz, b_mpz, nlimbs, realprime) == 0);
    }

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, ispmp ? maxbound : usedprime);
        mpz_set(b_mpz, a_mpz);

        convert_to_array(a, a_mpz, nlimbs);
        memcpy(b, a, nlimbs * sizeof(uint32_t));

        eq = modcmp(a, b);

        TEST_ASSERT(compare_with_ref_modcmp(eq, a_mpz, b_mpz, nlimbs, realprime) == 0);
    }

    if (mpz_sizeinbase(usedprime, 2) % 32 != 0) {
        for (int i = 0; i < ITERATIONS; i++) {
            mpz_urandomm(a_mpz, state, usedprime);
            mpz_add(b_mpz, a_mpz, usedprime);

            convert_to_array(a, a_mpz, nlimbs);
            convert_to_array(b, b_mpz, nlimbs);

            eq = modcmp(a, b);

            TEST_ASSERT(compare_with_ref_modcmp(eq, a_mpz, b_mpz, nlimbs, realprime) == 0);
        }
    }
}

void test_modsign_fixed(int nlimbs, int ispmp, int (*modsign)(const uint32_t *)) {
    uint32_t man_tests[nlimbs];
    int sign;

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests);

        convert_to_mpz_t(a_mpz, man_tests, nlimbs);
        mpz_mod(a_mpz, a_mpz, ispmp ? maxbound : usedprime);
        convert_to_array(man_tests, a_mpz, nlimbs);

        sign = modsign(man_tests);

        if (ispmp) {
            TEST_ASSERT(compare_with_ref_modsign(sign, a_mpz, nlimbs, realprime) == 0);
        }
        else {
            TEST_ASSERT(compare_with_ref_modsign_mont(sign, a_mpz, nlimbs, realprime) == 0);
        }
    }
}

void test_modsign_random(int nlimbs, int ispmp, int (*modsign)(const uint32_t *)) {
    uint32_t a[nlimbs];
    int sign;
    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, ispmp ? maxbound : usedprime);

        convert_to_array(a, a_mpz, nlimbs);

        sign = modsign(a);

        if (ispmp) {
            TEST_ASSERT(compare_with_ref_modsign(sign, a_mpz, nlimbs, realprime) == 0);
        }
        else {
            TEST_ASSERT(compare_with_ref_modsign_mont(sign, a_mpz, nlimbs, realprime) == 0);
        }
    }
}

void test_mod2r_fixed(int nlimbs, int ispmp, void (*mod2r)(unsigned int, uint32_t *)) {
    uint32_t a[nlimbs];
    for (unsigned int i = 0; i < (nlimbs + 1) * 32; i++) {
        mod2r(i, a);

        if (ispmp) {
            TEST_ASSERT(compare_with_ref_mod2r(a, i, nlimbs, realprime) == 0);
        }
        else {
            TEST_ASSERT(compare_with_ref_mod2r_mont(a, i, nlimbs, realprime) == 0);
        }
    }
}

void test_mod2r_random(int nlimbs, int ispmp, void (*mod2r)(unsigned int, uint32_t *)) {
    uint32_t a[nlimbs];
    for (unsigned int i = 0; i < (nlimbs + 1) * 32; i++) {
        mod2r(i, a);

        if (ispmp) {
            TEST_ASSERT(compare_with_ref_mod2r(a, i, nlimbs, realprime) == 0);
        }
        else {
            TEST_ASSERT(compare_with_ref_mod2r_mont(a, i, nlimbs, realprime) == 0);
        }
    }
}

void test_nres_fixed(int nlimbs, int ispmp, void (*nres)(const uint32_t *, uint32_t *)) {
    uint32_t b[nlimbs], man_tests[nlimbs];

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests);

        convert_to_mpz_t(a_mpz, man_tests, nlimbs);

        nres(man_tests, b);

        if (ispmp) {
            char testv = 0;

            for (int j = 0; j < nlimbs; j++) {
                if (man_tests[j] != b[j]) {
                    testv = 1;
                }
            }

            TEST_ASSERT(testv == 0);
        }
        else {
            TEST_ASSERT(compare_with_ref_nres(b, a_mpz, nlimbs, realprime) == 0);
        }
    }
}

void test_nres_random(int nlimbs, int ispmp, void (*nres)(const uint32_t *, uint32_t *)) {
    uint32_t a[nlimbs], b[nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);

        nres(a, b);

        if (ispmp) {
            char testv = 0;
            for (int j = 0; j < nlimbs; j++) {
                if (a[j] != b[j]) {
                    testv = 1;
                }
            }

            TEST_ASSERT(testv == 0);
        }
        else {
            TEST_ASSERT(compare_with_ref_nres(b, a_mpz, nlimbs, realprime) == 0);
        }
    }
}

void test_modcpy_fixed(int nlimbs, void (*modcpy)(const uint32_t *, uint32_t *)) {
    uint32_t b[nlimbs], man_tests[nlimbs];
    char testv;

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        convert_to_mpz_t(a_mpz, man_tests, nlimbs);

        modcpy(man_tests, b);

        testv = 0;
        for (int j = 0; j < nlimbs; j++) {
            if (man_tests[j] != b[j]) {
                testv = 1;
            }
        }

        TEST_ASSERT(testv == 0);
    }
}

void test_modcpy_random(int nlimbs, void (*modcpy)(const uint32_t *, uint32_t *)) {
    uint32_t a[nlimbs], b[nlimbs];
    char testv;

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);

        modcpy(a, b);
        testv = 0;
        for (int j = 0; j < nlimbs; j++) {
            if (a[j] != b[j]) {
                testv = 1;
            }
        }
        TEST_ASSERT(testv == 0);
    }
}

void test_modinv_fixed(int nlimbs, void (*nres)(const uint32_t *, uint32_t *),
                       void (*modinv)(const uint32_t *, const uint32_t *, uint32_t *),
                       void (*redc)(const uint32_t *, uint32_t *)) {
    uint32_t b[nlimbs], man_tests[nlimbs];

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests);

        convert_to_mpz_t(a_mpz, man_tests, nlimbs);
        mpz_mod(a_mpz, a_mpz, usedprime);
        convert_to_array(man_tests, a_mpz, nlimbs);

        nres(man_tests, man_tests);
        modinv(man_tests, NULL, b);
        redc(b, b);

        TEST_ASSERT(compare_with_ref_modinv(b, a_mpz, nlimbs, realprime) == 0);
    }
}

void test_modinv_random(int nlimbs, void (*nres)(const uint32_t *, uint32_t *),
                        void (*modinv)(const uint32_t *, const uint32_t *, uint32_t *),
                        void (*redc)(const uint32_t *, uint32_t *)) {
    uint32_t a[nlimbs], b[nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);

        nres(a, a);
        modinv(a, NULL, b);
        redc(b, b);

        TEST_ASSERT(compare_with_ref_modinv(b, a_mpz, nlimbs, realprime) == 0);
    }
}

void test_modfsb_fixed(int nlimbs, int (*modfsb)(uint32_t *)) {
    uint32_t man_tests[nlimbs];

    mpz_set_ui(a_mpz, 1);
    mpz_mul_2exp(a_mpz, a_mpz, nlimbs * 32);
    mpz_sub_ui(a_mpz, a_mpz, 1);
    mpz_mul_ui(lim_mpz, realprime, 2);
    if (mpz_cmp(lim_mpz, a_mpz) > 0) {
        mpz_set_ui(lim_mpz, 1);
        mpz_mul_2exp(lim_mpz, lim_mpz, nlimbs * 32);
        mpz_sub_ui(lim_mpz, lim_mpz, 1);
    }

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests);

        convert_to_mpz_t(a_mpz, man_tests, nlimbs);
        mpz_mod(a_mpz, a_mpz, lim_mpz);
        convert_to_array(man_tests, a_mpz, nlimbs);

        int r = modfsb(man_tests);

        TEST_ASSERT(compare_with_ref_modfsb(man_tests, r, a_mpz, nlimbs, realprime) == 0);
    }
}

void test_modfsb_random(int nlimbs, int (*modfsb)(uint32_t *)) {
    uint32_t a[nlimbs];

    mpz_set_ui(a_mpz, 1);
    mpz_mul_2exp(a_mpz, a_mpz, nlimbs * 32);
    mpz_sub_ui(a_mpz, a_mpz, 1);
    mpz_mul_ui(lim_mpz, realprime, 2);
    if (mpz_cmp(lim_mpz, a_mpz) > 0) {
        mpz_set_ui(lim_mpz, 1);
        mpz_mul_2exp(lim_mpz, lim_mpz, nlimbs * 32);
        mpz_sub_ui(lim_mpz, lim_mpz, 1);
    }

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, lim_mpz);

        convert_to_array(a, a_mpz, nlimbs);

        int r = modfsb(a);

        TEST_ASSERT(compare_with_ref_modfsb(a, r, a_mpz, nlimbs, realprime) == 0);
    }
}

void test_modis1_fixed(int nlimbs, void (*nres)(const uint32_t *, uint32_t *), int (*modis1)(const uint32_t *)) {
    uint32_t b[nlimbs];
    uint32_t man_tests[6][nlimbs];

    memset(man_tests, 0, 6 * nlimbs * sizeof(uint32_t));

    man_tests[0][0] = 1;
    for (int i = 0; i < nlimbs; i++) {
        man_tests[2][i] = -1;
    }
    man_tests[3][nlimbs - 1] = 0x8000000;
    man_tests[4][0] = -1;
    man_tests[5][nlimbs - 1] = -1;

    nres(man_tests[0], b);
    TEST_ASSERT(modis1(b) == 1);
    for (int i = 1; i < 6; i++) {
        nres(man_tests[i], b);
        TEST_ASSERT(modis1(b) == 0);
    }
}

void test_modis1_random(int nlimbs, void (*nres)(const uint32_t *, uint32_t *), int (*modis1)(const uint32_t *)) {
    uint32_t a[nlimbs], b[nlimbs];
    int res;

    for (int i = 0; i < ITERATIONS; i++) {
        if (i == 0) {
            mpz_set_ui(a_mpz, 1);
        }
        else {
            mpz_urandomm(a_mpz, state, usedprime);
        }

        convert_to_array(a, a_mpz, nlimbs);

        nres(a, b);
        res = modis1(b);
        TEST_ASSERT(compare_with_ref_modis1(res, a_mpz) == 0);
    }
}

void test_modis0_fixed(int nlimbs, void (*nres)(const uint32_t *, uint32_t *), int (*modis0)(const uint32_t *)) {
    uint32_t b[nlimbs];
    uint32_t man_tests[6][nlimbs];

    memset(man_tests, 0, 6 * nlimbs * sizeof(uint32_t));

    man_tests[1][0] = 1;
    for (int i = 0; i < nlimbs; i++) {
        man_tests[2][i] = -1;
    }
    man_tests[3][nlimbs - 1] = 0x8000000;
    man_tests[4][0] = -1;
    man_tests[5][nlimbs - 1] = -1;

    nres(man_tests[0], b);
    TEST_ASSERT(modis0(b) == 1);
    for (int i = 1; i < 6; i++) {
        nres(man_tests[i], b);
        TEST_ASSERT(modis0(b) == 0);
    }
}

void test_modis0_random(int nlimbs, int (*modis0)(const uint32_t *)) {
    uint32_t a[nlimbs], b[nlimbs];
    int res;

    for (int i = 0; i < ITERATIONS; i++) {
        if (i == 0) {
            mpz_set_ui(a_mpz, 0);
        }
        else {
            mpz_urandomm(a_mpz, state, usedprime);
        }

        convert_to_array(a, a_mpz, nlimbs);

        res = modis0(b);
        TEST_ASSERT(compare_with_ref_modis0(res, a_mpz) == 0);
    }
}

void test_modzer_random(int nlimbs, void (*modzer)(uint32_t *)) {
    uint32_t a[nlimbs];
    char res;

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);

        modzer(a);
        res = 0;
        for (int j = 0; j < nlimbs; j++) {
            if (a[j] != 0) {
                res = 1;
            }
        }

        TEST_ASSERT(res == 0);
    }
}

void test_modone_random(int nlimbs, void (*modone)(uint32_t *), void (*redc)(const uint32_t *, uint32_t *)) {
    uint32_t a[nlimbs];
    char res;

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);

        modone(a);
        redc(a, a);
        res = 0;
        if (a[0] != 1) {
            res = 1;
        }
        for (int j = 1; j < nlimbs; j++) {
            if (a[j] != 0) {
                res = 1;
            }
        }

        TEST_ASSERT(res == 0);
    }
}

void test_modint_random(int nlimbs, void (*modint)(int, uint32_t *), void (*redc)(const uint32_t *, uint32_t *)) {
    uint32_t a[nlimbs], b[nlimbs];
    char res;

    mpz_set_ui(w_mpz, 1);
    mpz_mul_2exp(w_mpz, w_mpz, 32);

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);

        mpz_mod(a_mpz, a_mpz, w_mpz);
        convert_to_array(a, a_mpz, nlimbs);

        modint(a[0], b);
        redc(b, b);
        res = 0;
        if (b[0] != a[0]) {
            res = 1;
        }
        for (int j = 1; j < nlimbs; j++) {
            if (b[j] != a[j]) {
                res = 1;
            }
        }

        TEST_ASSERT(res == 0);
    }
}

void test_modshr_fixed(int nlimbs, uint32_t (*modshr)(int, uint32_t *)) {
    uint32_t man_tests[nlimbs];

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        for (int j = 0; j < 32; j++) {
            callback_fixed_tests(nlimbs, i, man_tests);

            convert_to_mpz_t(a_mpz, man_tests, nlimbs);

            modshr(j, man_tests);

            TEST_ASSERT(compare_with_ref_modshr(j, man_tests, a_mpz, nlimbs) == 0);
        }
    }
}

void test_modshr_random(int nlimbs, uint32_t (*modshr)(int, uint32_t *)) {
    uint32_t a[nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);

        modshr(i % 32, a);

        TEST_ASSERT(compare_with_ref_modshr(i % 32, a, a_mpz, nlimbs) == 0);
    }
}

void test_modshl_fixed(int nlimbs, void (*modshl)(int, uint32_t *)) {
    uint32_t man_tests[nlimbs];

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        for (int j = 0; j < 32; j++) {
            callback_fixed_tests(nlimbs, i, man_tests);

            convert_to_mpz_t(a_mpz, man_tests, nlimbs);

            modshl(j, man_tests);

            TEST_ASSERT(compare_with_ref_modshl(j, man_tests, a_mpz, nlimbs, realprime) == 0);
        }
    }
}

void test_modshl_random(int nlimbs, void (*modshl)(int, uint32_t *)) {
    uint32_t a[nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);

        modshl(i % 32, a);

        TEST_ASSERT(compare_with_ref_modshl(i % 32, a, a_mpz, nlimbs, realprime) == 0);
    }
}

void test_modcmv_random(int nlimbs, void (*modcmv)(int, const uint32_t *, volatile uint32_t *)) {
    uint32_t a[nlimbs], b[nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);
        mpz_urandomm(b_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);
        convert_to_array(b, b_mpz, nlimbs);

        modcmv(i % 2, a, b);

        TEST_ASSERT(compare_with_ref_modcmv(i % 2, b, a_mpz, b_mpz, nlimbs) == 0);
    }
}

void test_modcsw_random(int nlimbs, void (*modcsw)(int, volatile uint32_t *, volatile uint32_t *)) {
    uint32_t a[nlimbs], b[nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);
        mpz_urandomm(b_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);
        convert_to_array(b, b_mpz, nlimbs);

        modcsw(i % 2, a, b);

        TEST_ASSERT(compare_with_ref_modcsw(i % 2, a, b, a_mpz, b_mpz, nlimbs) == 0);
    }
}

void test_modsqrt_fixed(int nlimbs, void (*nres)(const uint32_t *, uint32_t *),
                        void (*modsqrt)(const uint32_t *, const uint32_t *, uint32_t *),
                        void (*redc)(const uint32_t *, uint32_t *)) {
    uint32_t b[nlimbs], man_tests[nlimbs];

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests);

        convert_to_mpz_t(a_mpz, man_tests, nlimbs);
        mpz_powm_ui(a_mpz, a_mpz, 2, realprime);
        convert_to_array(man_tests, a_mpz, nlimbs);

        nres(man_tests, man_tests);
        modsqrt(man_tests, NULL, b);
        redc(b, b);

        TEST_ASSERT(compare_with_ref_modsqrt(b, a_mpz, nlimbs, realprime) == 0);
    }
}

void test_modsqrt_random(int nlimbs, void (*nres)(const uint32_t *, uint32_t *),
                         void (*modsqrt)(const uint32_t *, const uint32_t *, uint32_t *),
                         void (*redc)(const uint32_t *, uint32_t *)) {
    uint32_t a[nlimbs], b[nlimbs];

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);

        mpz_powm_ui(a_mpz, a_mpz, 2, realprime);
        convert_to_array(a, a_mpz, nlimbs);

        nres(a, a);
        modsqrt(a, NULL, b);
        redc(b, b);

        TEST_ASSERT(compare_with_ref_modsqrt(b, a_mpz, nlimbs, realprime) == 0);
    }
}

void test_modimp_fixed(int nlimbs, int ispmp, void (*modimp)(const char *, uint32_t *)) {
    uint32_t a[nlimbs], man_tests[nlimbs];
    char b[nlimbs * 4];
    size_t sz, bytes;

    for (int i = 0; i < 11 + (nlimbs * 2 - 1); i++) {
        callback_fixed_tests(nlimbs, i, man_tests);

        convert_to_mpz_t(a_mpz, man_tests, nlimbs);
        bytes = (mpz_sizeinbase(a_mpz, 2) + 7) / 8;

        memset(b, 0, nlimbs * 4);

        mpz_export(&b[nlimbs * 4 - bytes], &sz, 1, 1, 0, 0, a_mpz);

        modimp(b, a);

        if (ispmp) {
            TEST_ASSERT(compare_with_ref_modimp(a, a_mpz, nlimbs) == 0);
        }
        else {
            TEST_ASSERT(compare_with_ref_modimp_mont(a, a_mpz, nlimbs) == 0);
        }
    }
}

void test_modimp_random(int nlimbs, int ispmp, void (*modimp)(const char *, uint32_t *)) {
    uint32_t a[nlimbs];
    char b[nlimbs * 4];
    size_t sz, bytes;

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);
        bytes = (mpz_sizeinbase(a_mpz, 2) + 7) / 8;

        memset(b, 0, nlimbs * 4);

        mpz_export(&b[nlimbs * 4 - bytes], &sz, 1, 1, 0, 0, a_mpz);

        modimp(b, a);

        if (ispmp) {
            TEST_ASSERT(compare_with_ref_modimp(a, a_mpz, nlimbs) == 0);
        }
        else {
            TEST_ASSERT(compare_with_ref_modimp_mont(a, a_mpz, nlimbs) == 0);
        }
    }
}

void test_modexp_random(int nlimbs, int ispmp, void (*modexp)(const uint32_t *a, char *b)) {
    uint32_t a[nlimbs];
    char b[nlimbs * 4];
    // size_t sz, bytes;

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, ispmp ? maxbound : usedprime);

        convert_to_array(a, a_mpz, nlimbs);

        modexp(a, b);

        if (ispmp) {
            TEST_ASSERT(compare_with_ref_modexp(b, a_mpz, nlimbs) == 0);
        }
        else {
            TEST_ASSERT(compare_with_ref_modexp_mont(b, a_mpz, nlimbs) == 0);
        }
    }
}

void test_acceptance_random(int nlimbs, int ispmp, void (*nres)(const uint32_t *, uint32_t *),
                            void (*modadd)(const uint32_t *, const uint32_t *, uint32_t *),
                            void (*modsub)(const uint32_t *, const uint32_t *, uint32_t *),
                            void (*modmul)(const uint32_t *, const uint32_t *, uint32_t *),
                            void (*modsqr)(const uint32_t *, uint32_t *),
                            void (*modinv)(const uint32_t *, const uint32_t *, uint32_t *),
                            void (*modsqrt)(const uint32_t *, const uint32_t *, uint32_t *),
                            void (*redc)(const uint32_t *, uint32_t *), int (*modfsb)(uint32_t *)) {
    uint32_t a[nlimbs], b[nlimbs], t[nlimbs], c[nlimbs];

    memset(a, 0, nlimbs * sizeof(uint32_t));
    memset(b, 0, nlimbs * sizeof(uint32_t));
    memset(t, 0, nlimbs * sizeof(uint32_t));
    memset(c, 0, nlimbs * sizeof(uint32_t));

    for (int i = 0; i < ITERATIONS; i++) {
        mpz_urandomm(a_mpz, state, usedprime);
        mpz_urandomm(b_mpz, state, usedprime);

        convert_to_array(a, a_mpz, nlimbs);
        convert_to_array(b, b_mpz, nlimbs);

        nres(a, a);
        nres(b, b);
        modadd(a, b, t);
        modsub(a, b, c);
        modmul(t, c, a);
        modsqr(a, c);
        modinv(c, NULL, c);
        modsqrt(c, NULL, c);
        modsqr(c, c);
        if (ispmp) {
            modfsb(c);
        }
        else {
            redc(c, c);
        }

        TEST_ASSERT(compare_with_ref_acpt(c, a_mpz, b_mpz, nlimbs, realprime) == 0);
    }
}
