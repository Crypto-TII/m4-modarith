#include <string.h>

#include "unity.h"
#include "x25519-cortex-m4.h"

#if !defined(EXTERNAL_EMIL_X25519_M4) && !defined(EXTERNAL_EMIL_X25519_M4F)
#error Please #define either EXTERNAL_EMIL_X25519_M4 or EXTERNAL_EMIL_X25519_M4F.
#endif

#define Nbytes 32

// Borrowed from Mike's rfc7748.c

static int char2int(char input) {
    if ((input >= '0') && (input <= '9')) return input - '0';
    if ((input >= 'A') && (input <= 'F')) return input - 'A' + 10;
    if ((input >= 'a') && (input <= 'f')) return input - 'a' + 10;
    return 0;
}

// Convert a byte array to a hex string
static void toHex(const char *src, char *dst) {
    for (int i = 0; i < Nbytes; i++) {
        unsigned char ch = src[i];
        sprintf(&dst[i * 2], "%02x", ch);
    }
    dst[2 * Nbytes] = '\0';
}

// Convert from a hex string to byte array
static int fromHex(const char *src, char *dst) {
    int i = 0;
    int j = 0;
    while (src[j] != 0) {
        dst[i] = (char2int(src[j]) * 16) + char2int(src[j + 1]);
        i += 1;
        j += 2;
    }
    return j;
}

#define Nbytes 32

#ifdef EXTERNAL_EMIL_X25519_M4
void external_emil_x25519_m4_rfc7748_C25519_sect_5_2_first_sects_6_1_and_6_2(void) {
#elif defined EXTERNAL_EMIL_X25519_M4F
void external_emil_x25519_m4f_rfc7748_C25519_sect_5_2_first_sects_6_1_and_6_2(void) {
#endif
    const char* sk[] = {
        "77076d0a7318a57d3c16c17251b26645df4c2f87ebc0992ab177fba51db92c2a",
        "5dab087e624a8a4b79e17f8b83800ee66f3bb1292618b6fd1c2f8b27ff88e0eb",
        "77076d0a7318a57d3c16c17251b26645df4c2f87ebc0992ab177fba51db92c2a",
        "5dab087e624a8a4b79e17f8b83800ee66f3bb1292618b6fd1c2f8b27ff88e0eb",
        "a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4",
        "4b66e9d4d1b4673c5ad22691957d6af5c11b6421e0ea01d42ca4169e7918ba0d",
    };

    const char* su[] = {
        "0900000000000000000000000000000000000000000000000000000000000000",
        "0900000000000000000000000000000000000000000000000000000000000000",
        "de9edb7d7b7dc1b4d35b61c2ece435373f8343c85b78674dadfc7e146f882b4f",
        "8520f0098930a754748b7ddcb43ef75a0dbf3a0d26381af4eba4a98eaa9b4e6a",
        "e6db6867583030db3594c1a424b15f7c726624ec26b3353b10a903a6d0ab1c4c",
        "e5210f12786811d3f4b7959d0538ae2c31dbe7106fc03c3efc4cd549c715a493",
    };

    const char* sv[] = {
        "8520f0098930a754748b7ddcb43ef75a0dbf3a0d26381af4eba4a98eaa9b4e6a",
        "de9edb7d7b7dc1b4d35b61c2ece435373f8343c85b78674dadfc7e146f882b4f",
        "4a5d9d5ba4ce2de1728e3bf480350f25e07e21c947d19e3376f09b3c1e161742",
        "4a5d9d5ba4ce2de1728e3bf480350f25e07e21c947d19e3376f09b3c1e161742",
        "c3da55379de9c6908e94ea4df28d084f32eccf03491c71f754b4075577a28552",
        "95cbde9476e8907d7aade45cb4b873f88b595a68799fa152e6f8f7647aac7957",
    };

    char sv_actual[2 * Nbytes + 1];

    char bk[Nbytes];
    char bu[Nbytes];
    char bv[Nbytes];

    for (int i = 0; i < sizeof(sk)/sizeof(const char*); i++) {
        fromHex(su[i], bu);
        fromHex(sk[i], bk);

#ifdef EXTERNAL_EMIL_X25519_M4
        curve25519_scalarmult_m4((unsigned char*)bv, (unsigned char*)bk, (unsigned char*)bu);
#elif defined EXTERNAL_EMIL_X25519_M4F
        curve25519_scalarmult_m4f((unsigned char*)bv, (unsigned char*)bk, (unsigned char*)bu);
#endif

        toHex(bv, sv_actual);

        TEST_ASSERT_EQUAL_CHAR_ARRAY(sv[i], sv_actual, 2 * Nbytes);
    }
}

#ifdef EXTERNAL_EMIL_X25519_M4
void external_emil_x25519_m4_rfc7748_C25519_sect_5_2_second(void) {
#elif defined EXTERNAL_EMIL_X25519_M4F
void external_emil_x25519_m4f_rfc7748_C25519_sect_5_2_second(void) {
#endif
    const char sk[] = "0900000000000000000000000000000000000000000000000000000000000000";

    int iters[] = {1, 1000, 1000000};

    const char* sv[] = {
        "422c8e7a6227d7bca1350b3e2bb7279f7897b87bb6854b783c60e80311ae3079",
        "684cf59ba83309552800ef566f2f4d3c1c3887c49360e3875f2eb94d99532c51",
        "7c3911e0ab2586fd864497297e575e6f3bc601c0883c30df5f4dd2d24f665424",
    };

    char sv_actual[2 * Nbytes + 1];

    char bk[Nbytes];
    char bu[Nbytes];
    char bv[Nbytes];

    // 1000000 iterations takes too long
    // for (int i = 0; i < sizeof(iters)/sizeof(iters[0]); i++) {
    for (int i = 0; i < sizeof(iters)/sizeof(iters[0]) - 1; i++) {
        fromHex(sk, bu);
        fromHex(sk, bk);

        for (int j = 0; j < iters[i]; j++) {
#ifdef EXTERNAL_EMIL_X25519_M4
        curve25519_scalarmult_m4((unsigned char*)bv, (unsigned char*)bk, (unsigned char*)bu);
#elif defined EXTERNAL_EMIL_X25519_M4F
        curve25519_scalarmult_m4f((unsigned char*)bv, (unsigned char*)bk, (unsigned char*)bu);
#endif
            memcpy(bu, bk, Nbytes);
            memcpy(bk, bv, Nbytes);
        }

        toHex(bv, sv_actual);

        TEST_ASSERT_EQUAL_CHAR_ARRAY(sv[i], sv_actual, 2 * Nbytes);
    }
}
