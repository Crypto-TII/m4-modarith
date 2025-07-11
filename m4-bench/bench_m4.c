void setUp(void) { // needed for Unity, which we had to link due to RFC7748
    // set stuff up here
}

void tearDown(void) { // needed for Unity, which we had to link due to RFC7748
    // clean stuff up here
}

void bench_m4_C25519_pmp_asm(void);
void bench_m4_C25519_mont(void);
void bench_m4_PM266_pmp_asm(void);
void bench_m4_PM266_mont(void);
void bench_m4_PM512_pmp_asm(void);
void bench_m4_PM512_mont(void);
void bench_m4_NIST521_pmp_asm(void);
void bench_m4_NIST521_mont(void);
void bench_m4_PM383_pmp_asm(void);
void bench_m4_PM383_mont(void);
void bench_m4_C41417_pmp_asm(void);
void bench_m4_C41417_mont(void);
void bench_m4_PM336_pmp_asm(void);
void bench_m4_PM336_mont(void);
void bench_m4_PM225_pmp_asm(void);
void bench_m4_PM225_mont(void);
void bench_m4_NIST256_mont(void);
void bench_m4_C448_mont(void);
void bench_m4_MFP47441_mont(void);
void bench_m4_MFP248_mont(void);
void bench_m4_MFP376_mont(void);
void bench_m4_MFP500_mont(void);
void bench_m4_SECP256K1_mont(void);
void bench_m4_MFP248_mont_custom(void);
void bench_m4_C25519_pmp_asm_custom(void);
void bench_m4_C448_pmp_c_custom(void);
void bench_m4_rfc7748_C25519(void);
void bench_m4_rfc7748_C25519_custom(void);
void bench_m4_rfc7748_C448(void);
void bench_m4_rfc7748_C448_custom(void);
void bench_external(void);

void bench_m4(void) {
    bench_m4_C25519_pmp_asm();
    bench_m4_C25519_mont();
    bench_m4_PM266_pmp_asm();
    bench_m4_PM266_mont();
    bench_m4_PM512_pmp_asm();
    bench_m4_PM512_mont();
    bench_m4_NIST521_pmp_asm();
    bench_m4_NIST521_mont();
    bench_m4_PM383_pmp_asm();
    bench_m4_PM383_mont();
    bench_m4_C41417_pmp_asm();
    bench_m4_C41417_mont();
    bench_m4_PM336_pmp_asm();
    bench_m4_PM336_mont();
    bench_m4_PM225_pmp_asm();
    bench_m4_PM225_mont();
    bench_m4_NIST256_mont();
    bench_m4_C448_mont();
    bench_m4_MFP47441_mont();
    bench_m4_MFP248_mont();
    bench_m4_MFP376_mont();
    bench_m4_MFP500_mont();
    bench_m4_SECP256K1_mont();
    bench_m4_MFP248_mont_custom();
    bench_m4_C25519_pmp_asm_custom();
    bench_m4_C448_pmp_c_custom();

    bench_m4_rfc7748_C25519();
    bench_m4_rfc7748_C25519_custom();
    bench_m4_rfc7748_C448();
    bench_m4_rfc7748_C448_custom();
    bench_external();
}
