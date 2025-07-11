#include <stdio.h>

#include "unity.h"

#ifdef EXTERNAL_EMIL_X25519_M4
void external_emil_x25519_m4_rfc7748_C25519_sect_5_2_first_sects_6_1_and_6_2(void);
void external_emil_x25519_m4_rfc7748_C25519_sect_5_2_second(void);
#endif

#ifdef EXTERNAL_EMIL_X25519_M4F
void external_emil_x25519_m4f_rfc7748_C25519_sect_5_2_first_sects_6_1_and_6_2(void);
void external_emil_x25519_m4f_rfc7748_C25519_sect_5_2_second(void);
#endif

void test_external(void) {
#ifdef EXTERNAL_EMIL_X25519_M4
    RUN_TEST(external_emil_x25519_m4_rfc7748_C25519_sect_5_2_first_sects_6_1_and_6_2);
    RUN_TEST(external_emil_x25519_m4_rfc7748_C25519_sect_5_2_second);
#endif
#ifdef EXTERNAL_EMIL_X25519_M4F
    RUN_TEST(external_emil_x25519_m4f_rfc7748_C25519_sect_5_2_first_sects_6_1_and_6_2);
    RUN_TEST(external_emil_x25519_m4f_rfc7748_C25519_sect_5_2_second);
#endif
    printf("\n");
}
