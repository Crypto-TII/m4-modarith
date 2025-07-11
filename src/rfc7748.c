// Program to implement RFC7748 - https://datatracker.ietf.org/doc/html/rfc7748
// Montgomery curve key exchange code, as used by TLS
// Use associated python scripts to generate code for C25519 or C448, but easily modified for other Montgomery curves
//
// A good Montgomery curve can be found by running the sagemath script bowe.sage
//
// Mike Scott 23rd November 2023
// TII
//
// code for 32/64-bit processor for C25519 curve can be generated  by
//
// python pseudo.py 32/64 C25519
// or
// python monty.py 32/64 C25519
//
// code for 32/64-bit processor for X448 curve can be generated  by
//
// python monty.py 32/64 C448

// make sure decoration and generic are both set to False
// Seems to prefer clang compiler and karatsuba set to False for C25519 and True for C448
// clang -O3 -march=native -mtune=native rfc7748.c -lcpucycles -o rfc7748

/*** Insert automatically generated code for modulus code.c here ***/

/*** End of automatically generated code ***/

#if defined (RFC7748_C25519) || defined(RFC7748_C25519_CUSTOM)

#ifdef RFC7748_MODARITH
#include "modarith-codegen/code_C25519_pseudo.c"
#define RFC7748_NAME modarith_rfc7748_C25519
#elif defined(RFC7748_M4)
#ifdef RFC7748_C25519
#include "m4-codegen/code_C25519_pmp_asm.c"
#define RFC7748_NAME m4_rfc7748_C25519
#elif defined(RFC7748_C25519_CUSTOM)
#include "m4-custom/code_C25519_pmp_asm.c"
#define RFC7748_NAME m4_rfc7748_C25519_custom
#else
#error A generator must be selected for M4 RFC7748. Please #define either RFC7748_C25519 or RFC7748_C25519_CUSTOM.
#endif

#define C25519
#else
#error A generator must be selected for RFC7748. Please #define either RFC7748_MODARITH or RFC7748_M4.
#endif

#define Nlimbs Nlimbs_C25519_ct
#define Nbits Nbits_C25519_ct
#define Nbytes Nbytes_C25519_ct
#define modimp modimp_C25519_ct
#define modcpy modcpy_C25519_ct
#define modone modone_C25519_ct
#define modzer modzer_C25519_ct
#define modcsw modcsw_C25519_ct
#define modadd modadd_C25519_ct
#define modsqr modsqr_C25519_ct
#define modsub modsub_C25519_ct
#define modmul modmul_C25519_ct
#define modmli modmli_C25519_ct
#define modpro modpro_C25519_ct
#define modinv modinv_C25519_ct
#define modfsb modfsb_C25519_ct
#define modshr modshr_C25519_ct
#define modexp modexp_C25519_ct

#elif defined(RFC7748_C448) || defined(RFC7748_C448_CUSTOM)

#ifdef RFC7748_MODARITH
#include "modarith-codegen/code_C448_monty.c"
#define RFC7748_NAME modarith_rfc7748_C448
#elif defined(RFC7748_M4)
#ifdef RFC7748_C448
#include "m4-codegen/code_C448_mont.c"
#define RFC7748_NAME m4_rfc7748_C448
#elif defined(RFC7748_C448_CUSTOM)
#include "m4-custom/code_C448_pmp_c.c"
#define RFC7748_NAME m4_rfc7748_C448_custom
#else
#error A generator must be selected for M4 RFC7748. Please #define either RFC7748_C448 or RFC7748_C448_CUSTOM.
#endif

#define C448
#else
#error A generator must be selected for RFC7748. Please #define either RFC7748_MODARITH or RFC7748_M4.
#endif

#define Nlimbs Nlimbs_C448_ct
#define Nbits Nbits_C448_ct
#define Nbytes Nbytes_C448_ct
#define modimp modimp_C448_ct
#define modcpy modcpy_C448_ct
#define modone modone_C448_ct
#define modzer modzer_C448_ct
#define modcsw modcsw_C448_ct
#define modadd modadd_C448_ct
#define modsqr modsqr_C448_ct
#define modsub modsub_C448_ct
#define modmul modmul_C448_ct
#define modmli modmli_C448_ct
#define modpro modpro_C448_ct
#define modinv modinv_C448_ct
#define modfsb modfsb_C448_ct
#define modshr modshr_C448_ct
#define modexp modexp_C448_ct

#else
#error A curve must be selected for RFC7748. Please #define either RFC7748_C25519 or RFC7748_C448.
#endif

// reverse bytes. Useful when dealing with little-endian formats
static void reverse(char *w) {
    for (int i = 0; i < (Nbytes / 2); i++) {
        unsigned char ch = w[i];
        w[i] = w[Nbytes - i - 1];
        w[Nbytes - i - 1] = ch;
    }
}
// Describe Montgomery Curve parameters

#ifdef C25519
#define A24 121665    // Montgomery curve constant (A-2)/4
#define COF 3         // Montgomery curve cofactor = 2^cof (2 or 3)
#define TWIST_SECURE  // If it is a twist secure curve
#endif

#ifdef C448
#define A24 39081     // Montgomery curve constant (A-2)/4
#define COF 2         // Montgomery curve cofactor = 2^cof (2 or 3)
#define TWIST_SECURE  // If it is a twist secure curve
#endif

// clamp input - see RFC7748
static void clamp(char *bk) {
    int s = (8 - (Nbits % 8)) % 8;
    bk[0] &= -(1 << COF);
    char mask = (unsigned char)(0xffu >> s);
    bk[Nbytes - 1] &= mask;
    bk[Nbytes - 1] |= (unsigned char)(0x80u >> s);
}

// return nth bit of byte array
static int bit(int n, const char *a) {
    return (int)((a[n / 8u] & ((unsigned char)1u << (n % 8u))) >> (n % 8u));
}

// RFC7748 - Montgomery curve
// bv=bk*bu, bu,bv are x coordinates on elliptic curve
#define FN_NAME(N) N
void FN_NAME(RFC7748_NAME)(const char *bk, const char *bu, char *bv) {
    int i;
    int kt;
    int swap = 0;
    char ck[Nbytes];
    char cu[Nbytes];
    spint u[Nlimbs];
    spint x1[Nlimbs];
    spint x2[Nlimbs];
    spint x3[Nlimbs];
    spint z2[Nlimbs];
    spint z3[Nlimbs];
    spint A[Nlimbs];
    spint B[Nlimbs];
    spint AA[Nlimbs];
    spint BB[Nlimbs];
    spint C[Nlimbs];
    spint D[Nlimbs];
    spint E[Nlimbs];

    for (i = 0; i < Nbytes; i++) {
        ck[i] = bk[i];
        cu[i] = bu[i];
    }
    reverse(cu);
#ifdef C25519
    cu[0] &= 0x7f;
#endif
    // clamp input
    clamp(ck);

    // import into internal representation
    modimp(cu, u);

    modcpy(u, x1);  // x_1=u
    modone(x2);     // x_2=1
    modzer(z2);     // z_2=0
    modcpy(u, x3);  // x_3=u
    modone(z3);     // z_3=1

    for (i = Nbits - 1; i >= 0; i--) {
        kt = bit(i, ck);
        swap ^= kt;
        modcsw(swap, x2, x3);
        modcsw(swap, z2, z3);
        swap = kt;

        modadd(x2, z2, A);  // A = x_2 + z_2
        modsqr(A, AA);      // AA = A^2
        modsub(x2, z2, B);  // B = x_2 - z_2
        modsqr(B, BB);      // BB = B^2

        modsub(AA, BB, E);  // E = AA - BB
        modadd(x3, z3, C);  // C = x_3 + z_3

        modsub(x3, z3, D);  // D = x_3 - z_3
        modmul(D, A, D);    // DA = D * A
        modmul(C, B, C);    // CB = C * B

        modadd(D, C, x3);
        modsqr(x3, x3);  // x_3 = (DA + CB)^2

        modsub(D, C, z3);
        modsqr(z3, z3);
        modmul(z3, x1, z3);  // z_3 = x_1 * (DA - CB)^2
        modmul(AA, BB, x2);  // x_2 = AA * BB
        modmli(E, A24, z2);
        modadd(z2, AA, z2);
        modmul(z2, E, z2);  // z_2 = E * (AA + a24 * E)
    }
    modcsw(swap, x2, x3);
    modcsw(swap, z2, z3);

#ifdef TWIST_SECURE
    modpro(z2, A);
    modinv(z2, A, z2);  // sufficient for twist secure curves like C25519 and C448
#else
    // Do cheap point validation here - see https://eprint.iacr.org/2020/1497
    modmul(u, z2, B);  // wZ
    modmul(B, z2, A);  // wZ^2
    modpro(A, E);      // y
    modcpy(A, C);
    modmul(E, z2, D);  // y.Z2
    modsqr(D, D);
    modmul(D, u, D);                   // w.(y.z2)^2
    for (i = 0; i < (COF - 2); i++) {  // COF is 2 or 3
        modsqr(C, C);
        modmul(C, A, C);
    }
    for (i = 0; i < COF; i++) {
        modsqr(E, E);
    }
    modmul(C, E, C);
    modmul(C, B, z2);
    for (i = 0; i < (COF - 2); i++) {
        modsqr(D, D);
    }
    modone(A);
    modadd(D, A, D);
    modfsb(D);
    modshr(1, D);       // 1 for QR, else 0
    modmul(x2, D, x2);  // set to zero for bad input point
#endif
    modmul(x2, z2, x2);

    modexp(x2, bv);
    reverse(bv);  // little endian
}
