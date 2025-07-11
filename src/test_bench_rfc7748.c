#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include "hal.h"

#if defined (RFC7748_C25519) || defined(RFC7748_C25519_CUSTOM)

#ifdef RFC7748_MODARITH
#define RFC7748_NAME modarith_rfc7748_C25519
#elif defined(RFC7748_M4)
#ifdef RFC7748_C25519
#define RFC7748_NAME m4_rfc7748_C25519
#elif defined(RFC7748_C25519_CUSTOM)
#define RFC7748_NAME m4_rfc7748_C25519_custom
#else
#error A generator must be selected for M4 RFC7748. Please #define either RFC7748_C25519 or RFC7748_C25519_CUSTOM.
#endif

#define C25519
#else
#error A generator must be selected for RFC7748. Please #define either RFC7748_MODARITH or RFC7748_M4.
#endif

#define Nbytes 32

#elif defined(RFC7748_C448) || defined(RFC7748_C448_CUSTOM)

#ifdef RFC7748_MODARITH
#define RFC7748_NAME modarith_rfc7748_C448
#elif defined(RFC7748_M4)
#ifdef RFC7748_C448
#define RFC7748_NAME m4_rfc7748_C448
#elif defined(RFC7748_C448_CUSTOM)
#define RFC7748_NAME m4_rfc7748_C448_custom
#else
#error A generator must be selected for M4 RFC7748. Please #define either RFC7748_C448 or RFC7748_C448_CUSTOM.
#endif

#define C448
#else
#error A generator must be selected for RFC7748. Please #define either RFC7748_MODARITH or RFC7748_M4.
#endif

#define Nbytes 56

#else
#error A curve must be selected for RFC7748. Please #define either RFC7748_C25519 or RFC7748_C448.
#endif

#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#endif

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

#define PASTE2(a, b) a##b
#define BENCH_NAME(N) PASTE2(bench_, N)
#define TEST_NAME(N, VARIANT) PASTE2(N, VARIANT)
#define FN_NAME(N) N

void FN_NAME(RFC7748_NAME)(const char *bk, const char *bu, char *bv);

#ifdef M4_MODARITH_TEST
#include "unity.h"

void TEST_NAME(RFC7748_NAME, _sect_5_2_first_sects_6_1_and_6_2)(void) {
    const char *sk[] = {
#ifdef RFC7748_C25519
        "77076d0a7318a57d3c16c17251b26645df4c2f87ebc0992ab177fba51db92c2a",
        "5dab087e624a8a4b79e17f8b83800ee66f3bb1292618b6fd1c2f8b27ff88e0eb",
        "77076d0a7318a57d3c16c17251b26645df4c2f87ebc0992ab177fba51db92c2a",
        "5dab087e624a8a4b79e17f8b83800ee66f3bb1292618b6fd1c2f8b27ff88e0eb",
        "a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4",
        "4b66e9d4d1b4673c5ad22691957d6af5c11b6421e0ea01d42ca4169e7918ba0d",
#elif defined(RFC7748_C448) || defined(RFC7748_C448_CUSTOM)
        "9a8f4925d1519f5775cf46b04b5800d4ee9ee8bae8bc5565d498c28d"
        "d9c9baf574a9419744897391006382a6f127ab1d9ac2d8c0a598726b",
        "1c306a7ac2a0e2e0990b294470cba339e6453772b075811d8fad0d1d"
        "6927c120bb5ee8972b0d3e21374c9c921b09d1b0366f10b65173992d",
        "9a8f4925d1519f5775cf46b04b5800d4ee9ee8bae8bc5565d498c28d"
        "d9c9baf574a9419744897391006382a6f127ab1d9ac2d8c0a598726b",
        "1c306a7ac2a0e2e0990b294470cba339e6453772b075811d8fad0d1d"
        "6927c120bb5ee8972b0d3e21374c9c921b09d1b0366f10b65173992d",
        "3d262fddf9ec8e88495266fea19a34d28882acef045104d0d1aae121"
        "700a779c984c24f8cdd78fbff44943eba368f54b29259a4f1c600ad3",
        "203d494428b8399352665ddca42f9de8fef600908e0d461cb021f8c5"
        "38345dd77c3e4806e25f46d3315c44e0a5b4371282dd2c8d5be3095f",
#endif
    };

    const char *su[] = {
#ifdef RFC7748_C25519
        "0900000000000000000000000000000000000000000000000000000000000000",
        "0900000000000000000000000000000000000000000000000000000000000000",
        "de9edb7d7b7dc1b4d35b61c2ece435373f8343c85b78674dadfc7e146f882b4f",
        "8520f0098930a754748b7ddcb43ef75a0dbf3a0d26381af4eba4a98eaa9b4e6a",
        "e6db6867583030db3594c1a424b15f7c726624ec26b3353b10a903a6d0ab1c4c",
        "e5210f12786811d3f4b7959d0538ae2c31dbe7106fc03c3efc4cd549c715a493",
#elif defined(RFC7748_C448) || defined(RFC7748_C448_CUSTOM)
        "05000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000",
        "05000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000",
        "3eb7a829b0cd20f5bcfc0b599b6feccf6da4627107bdb0d4f345b430"
        "27d8b972fc3e34fb4232a13ca706dcb57aec3dae07bdc1c67bf33609",
        "9b08f7cc31b7e3e67d22d5aea121074a273bd2b83de09c63faa73d2c"
        "22c5d9bbc836647241d953d40c5b12da88120d53177f80e532c41fa0",
        "06fce640fa3487bfda5f6cf2d5263f8aad88334cbd07437f020f08f9"
        "814dc031ddbdc38c19c6da2583fa5429db94ada18aa7a7fb4ef8a086",
        "0fbcc2f993cd56d3305b0b7d9e55d4c1a8fb5dbb52f8e9a1e9b6201b"
        "165d015894e56c4d3570bee52fe205e28a78b91cdfbde71ce8d157db",
#endif
    };

    const char *sv[] = {
#ifdef RFC7748_C25519
        "8520f0098930a754748b7ddcb43ef75a0dbf3a0d26381af4eba4a98eaa9b4e6a",
        "de9edb7d7b7dc1b4d35b61c2ece435373f8343c85b78674dadfc7e146f882b4f",
        "4a5d9d5ba4ce2de1728e3bf480350f25e07e21c947d19e3376f09b3c1e161742",
        "4a5d9d5ba4ce2de1728e3bf480350f25e07e21c947d19e3376f09b3c1e161742",
        "c3da55379de9c6908e94ea4df28d084f32eccf03491c71f754b4075577a28552",
        "95cbde9476e8907d7aade45cb4b873f88b595a68799fa152e6f8f7647aac7957",
#elif defined(RFC7748_C448) || defined(RFC7748_C448_CUSTOM)
        "9b08f7cc31b7e3e67d22d5aea121074a273bd2b83de09c63faa73d2c"
        "22c5d9bbc836647241d953d40c5b12da88120d53177f80e532c41fa0",
        "3eb7a829b0cd20f5bcfc0b599b6feccf6da4627107bdb0d4f345b430"
        "27d8b972fc3e34fb4232a13ca706dcb57aec3dae07bdc1c67bf33609",
        "07fff4181ac6cc95ec1c16a94a0f74d12da232ce40a77552281d282b"
        "b60c0b56fd2464c335543936521c24403085d59a449a5037514a879d",
        "07fff4181ac6cc95ec1c16a94a0f74d12da232ce40a77552281d282b"
        "b60c0b56fd2464c335543936521c24403085d59a449a5037514a879d",
        "ce3e4ff95a60dc6697da1db1d85e6afbdf79b50a2412d7546d5f239f"
        "e14fbaadeb445fc66a01b0779d98223961111e21766282f73dd96b6f",
        "884a02576239ff7a2f2f63b2db6a9ff37047ac13568e1e30fe63c4a7"
        "ad1b3ee3a5700df34321d62077e63633c575c1c954514e99da7c179d",
#endif
    };

    char sv_actual[2 * Nbytes + 1];

    char bk[Nbytes];
    char bu[Nbytes];
    char bv[Nbytes];

    for (int i = 0; i < sizeof(sk) / sizeof(sk[0]); i++) {
        fromHex(su[i], bu);
        fromHex(sk[i], bk);

        FN_NAME(RFC7748_NAME)(bk, bu, bv);

        toHex(bv, sv_actual);

        TEST_ASSERT_EQUAL_CHAR_ARRAY(sv[i], sv_actual, 2 * Nbytes);
    }
}

void TEST_NAME(RFC7748_NAME, _sect_5_2_second)(void) {
#if defined(RFC7748_C25519) || defined(RFC7748_C25519_CUSTOM)
    const char sk[] = "0900000000000000000000000000000000000000000000000000000000000000";
#elif defined(RFC7748_C448) || defined(RFC7748_C448_CUSTOM)
    const char sk[] =
        "05000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000";
#endif
    ;

    int iters[] = {1, 1000, 1000000};

    const char *sv[] = {
#if defined(RFC7748_C25519) || defined(RFC7748_C25519_CUSTOM)
        "422c8e7a6227d7bca1350b3e2bb7279f7897b87bb6854b783c60e80311ae3079",
        "684cf59ba83309552800ef566f2f4d3c1c3887c49360e3875f2eb94d99532c51",
        "7c3911e0ab2586fd864497297e575e6f3bc601c0883c30df5f4dd2d24f665424",
#elif defined(RFC7748_C448) || defined(RFC7748_C448_CUSTOM)
        "3f482c8a9f19b01e6c46ee9711d9dc14fd4bf67af30765c2ae2b846a"
        "4d23a8cd0db897086239492caf350b51f833868b9bc2b3bca9cf4113",
        "aa3b4749d55b9daf1e5b00288826c467274ce3ebbdd5c17b975e09d4"
        "af6c67cf10d087202db88286e2b79fceea3ec353ef54faa26e219f38",
        "077f453681caca3693198420bbe515cae0002472519b3e67661a7e89"
        "cab94695c8f4bcd66e61b9b9c946da8d524de3d69bd9d9d66b997e37",
#endif
    };

    char sv_actual[2 * Nbytes + 1];

    char bk[Nbytes];
    char bu[Nbytes];
    char bv[Nbytes];

    // 1000000 iterations takes too long
    // for (int i = 0; i < sizeof(iters)/sizeof(iters[0]); i++) {
    for (int i = 0; i < sizeof(iters) / sizeof(iters[0]) - 1; i++) {
        fromHex(sk, bu);
        fromHex(sk, bk);

        for (int j = 0; j < iters[i]; j++) {
            FN_NAME(RFC7748_NAME)(bk, bu, bv);
            memcpy(bu, bk, Nbytes);
            memcpy(bk, bv, Nbytes);
        }

        toHex(bv, sv_actual);

        TEST_ASSERT_EQUAL_CHAR_ARRAY(sv[i], sv_actual, 2 * Nbytes);
    }
}
#endif

#ifdef M4_MODARITH_BENCH
void BENCH_NAME(RFC7748_NAME)() {
    char bk[Nbytes], bu[Nbytes], bv[Nbytes];
    bm_decls;

    bm_start();
    DoNotOptimize(bk);
    DoNotOptimize(bu);
    FN_NAME(RFC7748_NAME)(bk, bu, bv);
    DoNotOptimize(bv);
    bm_end();

#ifdef RFC7748_MODARITH

#ifdef RFC7748_C25519
    printf("C25519, pseudo, modarith, RFC7748, cycles, %" PRIu32 "\n\n", bm_result());
#elif defined(RFC7748_C448)
    printf("C448, mont, modarith, RFC7748, cycles, %" PRIu32 "\n\n", bm_result());
#endif

#elif defined(RFC7748_M4)

#ifdef RFC7748_C25519
    printf("C25519, pseudo, M4, RFC7748, cycles, %" PRIu32 "\n\n", bm_result());
#elif defined(RFC7748_C25519_CUSTOM)
    printf("C25519, custom, M4, RFC7748, cycles, %" PRIu32 "\n\n", bm_result());
#elif defined(RFC7748_C448)
    printf("C448, mont, M4, RFC7748, cycles, %" PRIu32 "\n\n", bm_result());
#elif defined(RFC7748_C448_CUSTOM)
    printf("C448, custom, M4, RFC7748, cycles, %" PRIu32 "\n\n", bm_result());
#endif

#endif
    usleep(10000);  // To avoid SWO buffer overflows
}
#endif
