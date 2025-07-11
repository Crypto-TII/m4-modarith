#include <stdio.h>

#include "unity.h"

void modarith_rfc7748_C25519_sect_5_2_first_sects_6_1_and_6_2(void);
void modarith_rfc7748_C25519_sect_5_2_second(void);
void modarith_rfc7748_C448_sect_5_2_first_sects_6_1_and_6_2(void);
void modarith_rfc7748_C448_sect_5_2_second(void);
void m4_rfc7748_C25519_sect_5_2_first_sects_6_1_and_6_2(void);
void m4_rfc7748_C25519_sect_5_2_second(void);
void m4_rfc7748_C25519_custom_sect_5_2_first_sects_6_1_and_6_2(void);
void m4_rfc7748_C25519_custom_sect_5_2_second(void);
void m4_rfc7748_C448_sect_5_2_first_sects_6_1_and_6_2(void);
void m4_rfc7748_C448_sect_5_2_second(void);
void m4_rfc7748_C448_custom_sect_5_2_first_sects_6_1_and_6_2(void);
void m4_rfc7748_C448_custom_sect_5_2_second(void);

void test_rfc7748(void) {
    RUN_TEST(modarith_rfc7748_C25519_sect_5_2_first_sects_6_1_and_6_2);
    RUN_TEST(modarith_rfc7748_C25519_sect_5_2_second);
    RUN_TEST(modarith_rfc7748_C448_sect_5_2_first_sects_6_1_and_6_2);
    RUN_TEST(modarith_rfc7748_C448_sect_5_2_second);
    RUN_TEST(m4_rfc7748_C25519_sect_5_2_first_sects_6_1_and_6_2);
    RUN_TEST(m4_rfc7748_C25519_sect_5_2_second);
    RUN_TEST(m4_rfc7748_C25519_custom_sect_5_2_first_sects_6_1_and_6_2);
    RUN_TEST(m4_rfc7748_C25519_custom_sect_5_2_second);
    RUN_TEST(m4_rfc7748_C448_sect_5_2_first_sects_6_1_and_6_2);
    RUN_TEST(m4_rfc7748_C448_sect_5_2_second);
    RUN_TEST(m4_rfc7748_C448_custom_sect_5_2_first_sects_6_1_and_6_2);
    RUN_TEST(m4_rfc7748_C448_custom_sect_5_2_second);
    printf("\n");
}
