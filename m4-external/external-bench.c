#include <stdio.h>

#ifdef EXTERNAL_EMIL_P256_M4
void bench_external_emil_p256_m4();
#endif

#ifdef EXTERNAL_EMIL_P256_M4F
void bench_external_emil_p256_m4f();
#endif

#ifdef EXTERNAL_EMIL_X25519_M4
void bench_external_emil_x25519_m4_rfc7748_C25519();
#endif

#ifdef EXTERNAL_EMIL_X25519_M4F
void bench_external_emil_x25519_m4f_rfc7748_C25519();
#endif

#ifdef EXTERNAL_FIAT
void bench_fiat_25519_solinas();
void bench_fiat_p448_solinas();
void bench_fiat_p448_mont();
void bench_fiat_MFP248_mont();
void bench_fiat_MFP376_mont();
void bench_fiat_MFP500_mont();
void bench_fiat_PM266_mont();
void bench_fiat_PM512_mont();
void bench_fiat_PM266_solinas();
void bench_fiat_PM512_solinas();
void bench_fiat_NIST521_solinas();
void bench_fiat_NIST256_mont();
void bench_fiat_SECP256K1_mont();
#endif

#ifdef EXTERNAL_HAYATO
void bench_hayato_c25519();
#endif

#ifdef EXTERNAL_P256_M
void bench_p256_m();
#endif

#ifdef EXTERNAL_HAASE
void bench_haase_c25519();
#endif

#ifdef EXTERNAL_AZARDERAKHSH
void bench_azarderakhsh_ed448();
#endif

#ifdef EXTERNAL_MSRECC
void bench_msrecc();
#endif

#ifdef EXTERNAL_UECC
void bench_uecc();
#endif

void bench_external() {
#ifdef EXTERNAL_EMIL_P256_M4
    bench_external_emil_p256_m4();
#endif

#ifdef EXTERNAL_EMIL_P256_M4F
    bench_external_emil_p256_m4f();
#endif

#ifdef EXTERNAL_EMIL_X25519_M4
    bench_external_emil_x25519_m4_rfc7748_C25519();
#endif

#ifdef EXTERNAL_EMIL_X25519_M4F
    bench_external_emil_x25519_m4f_rfc7748_C25519();
#endif

#ifdef EXTERNAL_FIAT
    bench_fiat_25519_solinas();
    bench_fiat_p448_solinas();
    bench_fiat_p448_mont();
    bench_fiat_MFP248_mont();
    bench_fiat_MFP376_mont();
    bench_fiat_MFP500_mont();
    bench_fiat_PM266_solinas();
    bench_fiat_PM512_mont();
    bench_fiat_PM512_solinas();
    bench_fiat_NIST521_solinas();
    bench_fiat_NIST256_mont();
    bench_fiat_SECP256K1_mont();
#endif

#ifdef EXTERNAL_HAYATO
    bench_hayato_c25519();
#endif

#ifdef EXTERNAL_HAYATO
    bench_p256_m();
#endif

#ifdef EXTERNAL_HAASE
    bench_haase_c25519();
#endif

#ifdef EXTERNAL_AZARDERAKHSH
    bench_azarderakhsh_ed448();
#endif

#ifdef EXTERNAL_MSRECC
    bench_msrecc();
#endif

#ifdef EXTERNAL_UECC
    bench_uecc();
#endif
    printf("\n");
}
