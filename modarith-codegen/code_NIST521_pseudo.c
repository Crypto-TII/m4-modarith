
// Automatically generated modular arithmetic C code for pseudo-Mersenne primes
// Python Script by Mike Scott (Technology Innovation Institute, UAE, 2025)

#include <stdint.h>
#include <stdio.h>

#define sspint int32_t
#define spint uint32_t
#define udpint uint64_t
#define dpint uint64_t

#define Wordlength_NIST521_ct 32
#define Nlimbs_NIST521_ct 18
#define Radix_NIST521_ct 29
#define Nbits_NIST521_ct 521
#define Nbytes_NIST521_ct 66

#define MERSENNE
#define MULBYINT
#define NIST521

// propagate carries
static spint inline prop(spint *n) {
    int i;
    spint mask = ((spint)1 << 29u) - (spint)1;
    sspint carry = (sspint)n[0];
    carry >>= 29u;
    n[0] &= mask;
    for (i = 1; i < 17; i++) {
        carry += (sspint)n[i];
        n[i] = (spint)carry & mask;
        carry >>= 29u;
    }
    n[17] += (spint)carry;
    return -((n[17] >> 1) >> 30u);
}

// propagate carries and add p if negative, propagate carries again
static int inline flatten(spint *n) {
    spint carry = prop(n);
    n[0] -= ((spint)1u) & carry;
    n[17] += ((spint)0x10000000u) & carry;
    (void)prop(n);
    return (int)(carry & 1);
}

// Montgomery final subtract
static int modfsb_NIST521_ct(spint *n) {
    n[0] += (spint)1u;
    n[17] -= (spint)0x10000000u;
    return flatten(n);
}

// Modular addition - reduce less than 2p
static void modadd_NIST521_ct(const spint *a, const spint *b, spint *n) {
    spint carry;
    n[0] = a[0] + b[0];
    n[1] = a[1] + b[1];
    n[2] = a[2] + b[2];
    n[3] = a[3] + b[3];
    n[4] = a[4] + b[4];
    n[5] = a[5] + b[5];
    n[6] = a[6] + b[6];
    n[7] = a[7] + b[7];
    n[8] = a[8] + b[8];
    n[9] = a[9] + b[9];
    n[10] = a[10] + b[10];
    n[11] = a[11] + b[11];
    n[12] = a[12] + b[12];
    n[13] = a[13] + b[13];
    n[14] = a[14] + b[14];
    n[15] = a[15] + b[15];
    n[16] = a[16] + b[16];
    n[17] = a[17] + b[17];
    n[0] += (spint)2u;
    n[17] -= (spint)0x20000000u;
    carry = prop(n);
    n[0] -= ((spint)2u) & carry;
    n[17] += ((spint)0x20000000u) & carry;
    (void)prop(n);
}

// Modular subtraction - reduce less than 2p
static void modsub_NIST521_ct(const spint *a, const spint *b, spint *n) {
    spint carry;
    n[0] = a[0] - b[0];
    n[1] = a[1] - b[1];
    n[2] = a[2] - b[2];
    n[3] = a[3] - b[3];
    n[4] = a[4] - b[4];
    n[5] = a[5] - b[5];
    n[6] = a[6] - b[6];
    n[7] = a[7] - b[7];
    n[8] = a[8] - b[8];
    n[9] = a[9] - b[9];
    n[10] = a[10] - b[10];
    n[11] = a[11] - b[11];
    n[12] = a[12] - b[12];
    n[13] = a[13] - b[13];
    n[14] = a[14] - b[14];
    n[15] = a[15] - b[15];
    n[16] = a[16] - b[16];
    n[17] = a[17] - b[17];
    carry = prop(n);
    n[0] -= ((spint)2u) & carry;
    n[17] += ((spint)0x20000000u) & carry;
    (void)prop(n);
}

// Modular negation
static void modneg_NIST521_ct(const spint *b, spint *n) {
    spint carry;
    n[0] = (spint)0 - b[0];
    n[1] = (spint)0 - b[1];
    n[2] = (spint)0 - b[2];
    n[3] = (spint)0 - b[3];
    n[4] = (spint)0 - b[4];
    n[5] = (spint)0 - b[5];
    n[6] = (spint)0 - b[6];
    n[7] = (spint)0 - b[7];
    n[8] = (spint)0 - b[8];
    n[9] = (spint)0 - b[9];
    n[10] = (spint)0 - b[10];
    n[11] = (spint)0 - b[11];
    n[12] = (spint)0 - b[12];
    n[13] = (spint)0 - b[13];
    n[14] = (spint)0 - b[14];
    n[15] = (spint)0 - b[15];
    n[16] = (spint)0 - b[16];
    n[17] = (spint)0 - b[17];
    carry = prop(n);
    n[0] -= ((spint)2u) & carry;
    n[17] += ((spint)0x20000000u) & carry;
    (void)prop(n);
}

// Modular multiplication by an integer, c=a*b mod 2p
static void modmli_NIST521_ct(const spint *a, int b, spint *c) {
    udpint t = 0;
    spint carry;
    spint s;
    spint mask = ((spint)1 << 29u) - (spint)1;
    t += (udpint)a[0] * (udpint)b;
    spint v0 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[1] * (udpint)b;
    spint v1 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[2] * (udpint)b;
    spint v2 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[3] * (udpint)b;
    spint v3 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[4] * (udpint)b;
    spint v4 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[5] * (udpint)b;
    spint v5 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[6] * (udpint)b;
    spint v6 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[7] * (udpint)b;
    spint v7 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[8] * (udpint)b;
    spint v8 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[9] * (udpint)b;
    spint v9 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[10] * (udpint)b;
    spint v10 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[11] * (udpint)b;
    spint v11 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[12] * (udpint)b;
    spint v12 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[13] * (udpint)b;
    spint v13 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[14] * (udpint)b;
    spint v14 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[15] * (udpint)b;
    spint v15 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[16] * (udpint)b;
    spint v16 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[17] * (udpint)b;
    spint v17 = (spint)t & mask;
    t = t >> 29u;
    // second reduction pass

    udpint ut = (udpint)t;
    ut = (ut << 1) + (spint)(v17 >> 28u);
    v17 &= 0xfffffff;
    s = v0 + ((spint)ut & mask);
    c[0] = (spint)(s & mask);
    carry = (s >> 29) + (spint)(ut >> 29);
    c[1] = v1 + carry;
    c[2] = v2;
    c[3] = v3;
    c[4] = v4;
    c[5] = v5;
    c[6] = v6;
    c[7] = v7;
    c[8] = v8;
    c[9] = v9;
    c[10] = v10;
    c[11] = v11;
    c[12] = v12;
    c[13] = v13;
    c[14] = v14;
    c[15] = v15;
    c[16] = v16;
    c[17] = v17;
}

// Modular multiplication, c=a*b mod 2p
static void modmul_NIST521_ct(const spint *a, const spint *b, spint *c) {
    dpint t = 0;
    spint ma1 = a[1] * (spint)0x2;
    spint ma2 = a[2] * (spint)0x2;
    spint ma3 = a[3] * (spint)0x2;
    spint ma4 = a[4] * (spint)0x2;
    spint ma5 = a[5] * (spint)0x2;
    spint ma6 = a[6] * (spint)0x2;
    spint ma7 = a[7] * (spint)0x2;
    spint ma8 = a[8] * (spint)0x2;
    spint ma9 = a[9] * (spint)0x2;
    spint ma10 = a[10] * (spint)0x2;
    spint ma11 = a[11] * (spint)0x2;
    spint ma12 = a[12] * (spint)0x2;
    spint ma13 = a[13] * (spint)0x2;
    spint ma14 = a[14] * (spint)0x2;
    spint ma15 = a[15] * (spint)0x2;
    spint ma16 = a[16] * (spint)0x2;
    spint ma17 = a[17] * (spint)0x2;
    spint carry;
    spint s;
    spint mask = ((spint)1 << 29u) - (spint)1;
    t += (dpint)ma1 * (dpint)b[17];
    t += (dpint)ma2 * (dpint)b[16];
    t += (dpint)ma3 * (dpint)b[15];
    t += (dpint)ma4 * (dpint)b[14];
    t += (dpint)ma5 * (dpint)b[13];
    t += (dpint)ma6 * (dpint)b[12];
    t += (dpint)ma7 * (dpint)b[11];
    t += (dpint)ma8 * (dpint)b[10];
    t += (dpint)ma9 * (dpint)b[9];
    t += (dpint)ma10 * (dpint)b[8];
    t += (dpint)ma11 * (dpint)b[7];
    t += (dpint)ma12 * (dpint)b[6];
    t += (dpint)ma13 * (dpint)b[5];
    t += (dpint)ma14 * (dpint)b[4];
    t += (dpint)ma15 * (dpint)b[3];
    t += (dpint)ma16 * (dpint)b[2];
    t += (dpint)ma17 * (dpint)b[1];
    t += (dpint)a[0] * (dpint)b[0];
    spint v0 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma2 * (dpint)b[17];
    t += (dpint)ma3 * (dpint)b[16];
    t += (dpint)ma4 * (dpint)b[15];
    t += (dpint)ma5 * (dpint)b[14];
    t += (dpint)ma6 * (dpint)b[13];
    t += (dpint)ma7 * (dpint)b[12];
    t += (dpint)ma8 * (dpint)b[11];
    t += (dpint)ma9 * (dpint)b[10];
    t += (dpint)ma10 * (dpint)b[9];
    t += (dpint)ma11 * (dpint)b[8];
    t += (dpint)ma12 * (dpint)b[7];
    t += (dpint)ma13 * (dpint)b[6];
    t += (dpint)ma14 * (dpint)b[5];
    t += (dpint)ma15 * (dpint)b[4];
    t += (dpint)ma16 * (dpint)b[3];
    t += (dpint)ma17 * (dpint)b[2];
    t += (dpint)a[0] * (dpint)b[1];
    t += (dpint)a[1] * (dpint)b[0];
    spint v1 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma3 * (dpint)b[17];
    t += (dpint)ma4 * (dpint)b[16];
    t += (dpint)ma5 * (dpint)b[15];
    t += (dpint)ma6 * (dpint)b[14];
    t += (dpint)ma7 * (dpint)b[13];
    t += (dpint)ma8 * (dpint)b[12];
    t += (dpint)ma9 * (dpint)b[11];
    t += (dpint)ma10 * (dpint)b[10];
    t += (dpint)ma11 * (dpint)b[9];
    t += (dpint)ma12 * (dpint)b[8];
    t += (dpint)ma13 * (dpint)b[7];
    t += (dpint)ma14 * (dpint)b[6];
    t += (dpint)ma15 * (dpint)b[5];
    t += (dpint)ma16 * (dpint)b[4];
    t += (dpint)ma17 * (dpint)b[3];
    t += (dpint)a[0] * (dpint)b[2];
    t += (dpint)a[1] * (dpint)b[1];
    t += (dpint)a[2] * (dpint)b[0];
    spint v2 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma4 * (dpint)b[17];
    t += (dpint)ma5 * (dpint)b[16];
    t += (dpint)ma6 * (dpint)b[15];
    t += (dpint)ma7 * (dpint)b[14];
    t += (dpint)ma8 * (dpint)b[13];
    t += (dpint)ma9 * (dpint)b[12];
    t += (dpint)ma10 * (dpint)b[11];
    t += (dpint)ma11 * (dpint)b[10];
    t += (dpint)ma12 * (dpint)b[9];
    t += (dpint)ma13 * (dpint)b[8];
    t += (dpint)ma14 * (dpint)b[7];
    t += (dpint)ma15 * (dpint)b[6];
    t += (dpint)ma16 * (dpint)b[5];
    t += (dpint)ma17 * (dpint)b[4];
    t += (dpint)a[0] * (dpint)b[3];
    t += (dpint)a[1] * (dpint)b[2];
    t += (dpint)a[2] * (dpint)b[1];
    t += (dpint)a[3] * (dpint)b[0];
    spint v3 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma5 * (dpint)b[17];
    t += (dpint)ma6 * (dpint)b[16];
    t += (dpint)ma7 * (dpint)b[15];
    t += (dpint)ma8 * (dpint)b[14];
    t += (dpint)ma9 * (dpint)b[13];
    t += (dpint)ma10 * (dpint)b[12];
    t += (dpint)ma11 * (dpint)b[11];
    t += (dpint)ma12 * (dpint)b[10];
    t += (dpint)ma13 * (dpint)b[9];
    t += (dpint)ma14 * (dpint)b[8];
    t += (dpint)ma15 * (dpint)b[7];
    t += (dpint)ma16 * (dpint)b[6];
    t += (dpint)ma17 * (dpint)b[5];
    t += (dpint)a[0] * (dpint)b[4];
    t += (dpint)a[1] * (dpint)b[3];
    t += (dpint)a[2] * (dpint)b[2];
    t += (dpint)a[3] * (dpint)b[1];
    t += (dpint)a[4] * (dpint)b[0];
    spint v4 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma6 * (dpint)b[17];
    t += (dpint)ma7 * (dpint)b[16];
    t += (dpint)ma8 * (dpint)b[15];
    t += (dpint)ma9 * (dpint)b[14];
    t += (dpint)ma10 * (dpint)b[13];
    t += (dpint)ma11 * (dpint)b[12];
    t += (dpint)ma12 * (dpint)b[11];
    t += (dpint)ma13 * (dpint)b[10];
    t += (dpint)ma14 * (dpint)b[9];
    t += (dpint)ma15 * (dpint)b[8];
    t += (dpint)ma16 * (dpint)b[7];
    t += (dpint)ma17 * (dpint)b[6];
    t += (dpint)a[0] * (dpint)b[5];
    t += (dpint)a[1] * (dpint)b[4];
    t += (dpint)a[2] * (dpint)b[3];
    t += (dpint)a[3] * (dpint)b[2];
    t += (dpint)a[4] * (dpint)b[1];
    t += (dpint)a[5] * (dpint)b[0];
    spint v5 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma7 * (dpint)b[17];
    t += (dpint)ma8 * (dpint)b[16];
    t += (dpint)ma9 * (dpint)b[15];
    t += (dpint)ma10 * (dpint)b[14];
    t += (dpint)ma11 * (dpint)b[13];
    t += (dpint)ma12 * (dpint)b[12];
    t += (dpint)ma13 * (dpint)b[11];
    t += (dpint)ma14 * (dpint)b[10];
    t += (dpint)ma15 * (dpint)b[9];
    t += (dpint)ma16 * (dpint)b[8];
    t += (dpint)ma17 * (dpint)b[7];
    t += (dpint)a[0] * (dpint)b[6];
    t += (dpint)a[1] * (dpint)b[5];
    t += (dpint)a[2] * (dpint)b[4];
    t += (dpint)a[3] * (dpint)b[3];
    t += (dpint)a[4] * (dpint)b[2];
    t += (dpint)a[5] * (dpint)b[1];
    t += (dpint)a[6] * (dpint)b[0];
    spint v6 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma8 * (dpint)b[17];
    t += (dpint)ma9 * (dpint)b[16];
    t += (dpint)ma10 * (dpint)b[15];
    t += (dpint)ma11 * (dpint)b[14];
    t += (dpint)ma12 * (dpint)b[13];
    t += (dpint)ma13 * (dpint)b[12];
    t += (dpint)ma14 * (dpint)b[11];
    t += (dpint)ma15 * (dpint)b[10];
    t += (dpint)ma16 * (dpint)b[9];
    t += (dpint)ma17 * (dpint)b[8];
    t += (dpint)a[0] * (dpint)b[7];
    t += (dpint)a[1] * (dpint)b[6];
    t += (dpint)a[2] * (dpint)b[5];
    t += (dpint)a[3] * (dpint)b[4];
    t += (dpint)a[4] * (dpint)b[3];
    t += (dpint)a[5] * (dpint)b[2];
    t += (dpint)a[6] * (dpint)b[1];
    t += (dpint)a[7] * (dpint)b[0];
    spint v7 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma9 * (dpint)b[17];
    t += (dpint)ma10 * (dpint)b[16];
    t += (dpint)ma11 * (dpint)b[15];
    t += (dpint)ma12 * (dpint)b[14];
    t += (dpint)ma13 * (dpint)b[13];
    t += (dpint)ma14 * (dpint)b[12];
    t += (dpint)ma15 * (dpint)b[11];
    t += (dpint)ma16 * (dpint)b[10];
    t += (dpint)ma17 * (dpint)b[9];
    t += (dpint)a[0] * (dpint)b[8];
    t += (dpint)a[1] * (dpint)b[7];
    t += (dpint)a[2] * (dpint)b[6];
    t += (dpint)a[3] * (dpint)b[5];
    t += (dpint)a[4] * (dpint)b[4];
    t += (dpint)a[5] * (dpint)b[3];
    t += (dpint)a[6] * (dpint)b[2];
    t += (dpint)a[7] * (dpint)b[1];
    t += (dpint)a[8] * (dpint)b[0];
    spint v8 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma10 * (dpint)b[17];
    t += (dpint)ma11 * (dpint)b[16];
    t += (dpint)ma12 * (dpint)b[15];
    t += (dpint)ma13 * (dpint)b[14];
    t += (dpint)ma14 * (dpint)b[13];
    t += (dpint)ma15 * (dpint)b[12];
    t += (dpint)ma16 * (dpint)b[11];
    t += (dpint)ma17 * (dpint)b[10];
    t += (dpint)a[0] * (dpint)b[9];
    t += (dpint)a[1] * (dpint)b[8];
    t += (dpint)a[2] * (dpint)b[7];
    t += (dpint)a[3] * (dpint)b[6];
    t += (dpint)a[4] * (dpint)b[5];
    t += (dpint)a[5] * (dpint)b[4];
    t += (dpint)a[6] * (dpint)b[3];
    t += (dpint)a[7] * (dpint)b[2];
    t += (dpint)a[8] * (dpint)b[1];
    t += (dpint)a[9] * (dpint)b[0];
    spint v9 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma11 * (dpint)b[17];
    t += (dpint)ma12 * (dpint)b[16];
    t += (dpint)ma13 * (dpint)b[15];
    t += (dpint)ma14 * (dpint)b[14];
    t += (dpint)ma15 * (dpint)b[13];
    t += (dpint)ma16 * (dpint)b[12];
    t += (dpint)ma17 * (dpint)b[11];
    t += (dpint)a[0] * (dpint)b[10];
    t += (dpint)a[1] * (dpint)b[9];
    t += (dpint)a[2] * (dpint)b[8];
    t += (dpint)a[3] * (dpint)b[7];
    t += (dpint)a[4] * (dpint)b[6];
    t += (dpint)a[5] * (dpint)b[5];
    t += (dpint)a[6] * (dpint)b[4];
    t += (dpint)a[7] * (dpint)b[3];
    t += (dpint)a[8] * (dpint)b[2];
    t += (dpint)a[9] * (dpint)b[1];
    t += (dpint)a[10] * (dpint)b[0];
    spint v10 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma12 * (dpint)b[17];
    t += (dpint)ma13 * (dpint)b[16];
    t += (dpint)ma14 * (dpint)b[15];
    t += (dpint)ma15 * (dpint)b[14];
    t += (dpint)ma16 * (dpint)b[13];
    t += (dpint)ma17 * (dpint)b[12];
    t += (dpint)a[0] * (dpint)b[11];
    t += (dpint)a[1] * (dpint)b[10];
    t += (dpint)a[2] * (dpint)b[9];
    t += (dpint)a[3] * (dpint)b[8];
    t += (dpint)a[4] * (dpint)b[7];
    t += (dpint)a[5] * (dpint)b[6];
    t += (dpint)a[6] * (dpint)b[5];
    t += (dpint)a[7] * (dpint)b[4];
    t += (dpint)a[8] * (dpint)b[3];
    t += (dpint)a[9] * (dpint)b[2];
    t += (dpint)a[10] * (dpint)b[1];
    t += (dpint)a[11] * (dpint)b[0];
    spint v11 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma13 * (dpint)b[17];
    t += (dpint)ma14 * (dpint)b[16];
    t += (dpint)ma15 * (dpint)b[15];
    t += (dpint)ma16 * (dpint)b[14];
    t += (dpint)ma17 * (dpint)b[13];
    t += (dpint)a[0] * (dpint)b[12];
    t += (dpint)a[1] * (dpint)b[11];
    t += (dpint)a[2] * (dpint)b[10];
    t += (dpint)a[3] * (dpint)b[9];
    t += (dpint)a[4] * (dpint)b[8];
    t += (dpint)a[5] * (dpint)b[7];
    t += (dpint)a[6] * (dpint)b[6];
    t += (dpint)a[7] * (dpint)b[5];
    t += (dpint)a[8] * (dpint)b[4];
    t += (dpint)a[9] * (dpint)b[3];
    t += (dpint)a[10] * (dpint)b[2];
    t += (dpint)a[11] * (dpint)b[1];
    t += (dpint)a[12] * (dpint)b[0];
    spint v12 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma14 * (dpint)b[17];
    t += (dpint)ma15 * (dpint)b[16];
    t += (dpint)ma16 * (dpint)b[15];
    t += (dpint)ma17 * (dpint)b[14];
    t += (dpint)a[0] * (dpint)b[13];
    t += (dpint)a[1] * (dpint)b[12];
    t += (dpint)a[2] * (dpint)b[11];
    t += (dpint)a[3] * (dpint)b[10];
    t += (dpint)a[4] * (dpint)b[9];
    t += (dpint)a[5] * (dpint)b[8];
    t += (dpint)a[6] * (dpint)b[7];
    t += (dpint)a[7] * (dpint)b[6];
    t += (dpint)a[8] * (dpint)b[5];
    t += (dpint)a[9] * (dpint)b[4];
    t += (dpint)a[10] * (dpint)b[3];
    t += (dpint)a[11] * (dpint)b[2];
    t += (dpint)a[12] * (dpint)b[1];
    t += (dpint)a[13] * (dpint)b[0];
    spint v13 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma15 * (dpint)b[17];
    t += (dpint)ma16 * (dpint)b[16];
    t += (dpint)ma17 * (dpint)b[15];
    t += (dpint)a[0] * (dpint)b[14];
    t += (dpint)a[1] * (dpint)b[13];
    t += (dpint)a[2] * (dpint)b[12];
    t += (dpint)a[3] * (dpint)b[11];
    t += (dpint)a[4] * (dpint)b[10];
    t += (dpint)a[5] * (dpint)b[9];
    t += (dpint)a[6] * (dpint)b[8];
    t += (dpint)a[7] * (dpint)b[7];
    t += (dpint)a[8] * (dpint)b[6];
    t += (dpint)a[9] * (dpint)b[5];
    t += (dpint)a[10] * (dpint)b[4];
    t += (dpint)a[11] * (dpint)b[3];
    t += (dpint)a[12] * (dpint)b[2];
    t += (dpint)a[13] * (dpint)b[1];
    t += (dpint)a[14] * (dpint)b[0];
    spint v14 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma16 * (dpint)b[17];
    t += (dpint)ma17 * (dpint)b[16];
    t += (dpint)a[0] * (dpint)b[15];
    t += (dpint)a[1] * (dpint)b[14];
    t += (dpint)a[2] * (dpint)b[13];
    t += (dpint)a[3] * (dpint)b[12];
    t += (dpint)a[4] * (dpint)b[11];
    t += (dpint)a[5] * (dpint)b[10];
    t += (dpint)a[6] * (dpint)b[9];
    t += (dpint)a[7] * (dpint)b[8];
    t += (dpint)a[8] * (dpint)b[7];
    t += (dpint)a[9] * (dpint)b[6];
    t += (dpint)a[10] * (dpint)b[5];
    t += (dpint)a[11] * (dpint)b[4];
    t += (dpint)a[12] * (dpint)b[3];
    t += (dpint)a[13] * (dpint)b[2];
    t += (dpint)a[14] * (dpint)b[1];
    t += (dpint)a[15] * (dpint)b[0];
    spint v15 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)ma17 * (dpint)b[17];
    t += (dpint)a[0] * (dpint)b[16];
    t += (dpint)a[1] * (dpint)b[15];
    t += (dpint)a[2] * (dpint)b[14];
    t += (dpint)a[3] * (dpint)b[13];
    t += (dpint)a[4] * (dpint)b[12];
    t += (dpint)a[5] * (dpint)b[11];
    t += (dpint)a[6] * (dpint)b[10];
    t += (dpint)a[7] * (dpint)b[9];
    t += (dpint)a[8] * (dpint)b[8];
    t += (dpint)a[9] * (dpint)b[7];
    t += (dpint)a[10] * (dpint)b[6];
    t += (dpint)a[11] * (dpint)b[5];
    t += (dpint)a[12] * (dpint)b[4];
    t += (dpint)a[13] * (dpint)b[3];
    t += (dpint)a[14] * (dpint)b[2];
    t += (dpint)a[15] * (dpint)b[1];
    t += (dpint)a[16] * (dpint)b[0];
    spint v16 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)a[0] * (dpint)b[17];
    t += (dpint)a[1] * (dpint)b[16];
    t += (dpint)a[2] * (dpint)b[15];
    t += (dpint)a[3] * (dpint)b[14];
    t += (dpint)a[4] * (dpint)b[13];
    t += (dpint)a[5] * (dpint)b[12];
    t += (dpint)a[6] * (dpint)b[11];
    t += (dpint)a[7] * (dpint)b[10];
    t += (dpint)a[8] * (dpint)b[9];
    t += (dpint)a[9] * (dpint)b[8];
    t += (dpint)a[10] * (dpint)b[7];
    t += (dpint)a[11] * (dpint)b[6];
    t += (dpint)a[12] * (dpint)b[5];
    t += (dpint)a[13] * (dpint)b[4];
    t += (dpint)a[14] * (dpint)b[3];
    t += (dpint)a[15] * (dpint)b[2];
    t += (dpint)a[16] * (dpint)b[1];
    t += (dpint)a[17] * (dpint)b[0];
    spint v17 = (spint)t & mask;
    t = t >> 29u;
    // second reduction pass

    udpint ut = (udpint)t;
    ut = (ut << 1) + (spint)(v17 >> 28u);
    v17 &= 0xfffffff;
    s = v0 + ((spint)ut & mask);
    c[0] = (spint)(s & mask);
    carry = (s >> 29) + (spint)(ut >> 29);
    c[1] = v1 + carry;
    c[2] = v2;
    c[3] = v3;
    c[4] = v4;
    c[5] = v5;
    c[6] = v6;
    c[7] = v7;
    c[8] = v8;
    c[9] = v9;
    c[10] = v10;
    c[11] = v11;
    c[12] = v12;
    c[13] = v13;
    c[14] = v14;
    c[15] = v15;
    c[16] = v16;
    c[17] = v17;
}

// Modular squaring, c=a*a mod 2p
static void modsqr_NIST521_ct(const spint *a, spint *c) {
    udpint t = 0;
    spint ta1 = a[1] * (spint)2;
    spint ta2 = a[2] * (spint)2;
    spint ta3 = a[3] * (spint)2;
    spint ta4 = a[4] * (spint)2;
    spint ta5 = a[5] * (spint)2;
    spint ta6 = a[6] * (spint)2;
    spint ta7 = a[7] * (spint)2;
    spint ta8 = a[8] * (spint)2;
    spint ta9 = a[9] * (spint)2;
    spint ta10 = a[10] * (spint)2;
    spint ta11 = a[11] * (spint)2;
    spint ta12 = a[12] * (spint)2;
    spint ta13 = a[13] * (spint)2;
    spint ta14 = a[14] * (spint)2;
    spint ta15 = a[15] * (spint)2;
    spint ta16 = a[16] * (spint)2;
    spint ta17 = a[17] * (spint)2;
    spint ma1 = a[1] * (spint)0x2;
    spint ma2 = a[2] * (spint)0x2;
    spint ma3 = a[3] * (spint)0x2;
    spint ma4 = a[4] * (spint)0x2;
    spint ma5 = a[5] * (spint)0x2;
    spint ma6 = a[6] * (spint)0x2;
    spint ma7 = a[7] * (spint)0x2;
    spint ma8 = a[8] * (spint)0x2;
    spint ma9 = a[9] * (spint)0x2;
    spint ma10 = a[10] * (spint)0x2;
    spint ma11 = a[11] * (spint)0x2;
    spint ma12 = a[12] * (spint)0x2;
    spint ma13 = a[13] * (spint)0x2;
    spint ma14 = a[14] * (spint)0x2;
    spint ma15 = a[15] * (spint)0x2;
    spint ma16 = a[16] * (spint)0x2;
    spint ma17 = a[17] * (spint)0x2;
    spint carry;
    spint s;
    spint mask = ((spint)1 << 29u) - (spint)1;
    t += (udpint)ma1 * (udpint)ta17;
    t += (udpint)ma2 * (udpint)ta16;
    t += (udpint)ma3 * (udpint)ta15;
    t += (udpint)ma4 * (udpint)ta14;
    t += (udpint)ma5 * (udpint)ta13;
    t += (udpint)ma6 * (udpint)ta12;
    t += (udpint)ma7 * (udpint)ta11;
    t += (udpint)ma8 * (udpint)ta10;
    t += (udpint)ma9 * (udpint)a[9];
    t += (udpint)a[0] * (udpint)a[0];
    spint v0 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma2 * (udpint)ta17;
    t += (udpint)ma3 * (udpint)ta16;
    t += (udpint)ma4 * (udpint)ta15;
    t += (udpint)ma5 * (udpint)ta14;
    t += (udpint)ma6 * (udpint)ta13;
    t += (udpint)ma7 * (udpint)ta12;
    t += (udpint)ma8 * (udpint)ta11;
    t += (udpint)ma9 * (udpint)ta10;
    t += (udpint)a[0] * (udpint)ta1;
    spint v1 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma3 * (udpint)ta17;
    t += (udpint)ma4 * (udpint)ta16;
    t += (udpint)ma5 * (udpint)ta15;
    t += (udpint)ma6 * (udpint)ta14;
    t += (udpint)ma7 * (udpint)ta13;
    t += (udpint)ma8 * (udpint)ta12;
    t += (udpint)ma9 * (udpint)ta11;
    t += (udpint)ma10 * (udpint)a[10];
    t += (udpint)a[0] * (udpint)ta2;
    t += (udpint)a[1] * (udpint)a[1];
    spint v2 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma4 * (udpint)ta17;
    t += (udpint)ma5 * (udpint)ta16;
    t += (udpint)ma6 * (udpint)ta15;
    t += (udpint)ma7 * (udpint)ta14;
    t += (udpint)ma8 * (udpint)ta13;
    t += (udpint)ma9 * (udpint)ta12;
    t += (udpint)ma10 * (udpint)ta11;
    t += (udpint)a[0] * (udpint)ta3;
    t += (udpint)a[1] * (udpint)ta2;
    spint v3 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma5 * (udpint)ta17;
    t += (udpint)ma6 * (udpint)ta16;
    t += (udpint)ma7 * (udpint)ta15;
    t += (udpint)ma8 * (udpint)ta14;
    t += (udpint)ma9 * (udpint)ta13;
    t += (udpint)ma10 * (udpint)ta12;
    t += (udpint)ma11 * (udpint)a[11];
    t += (udpint)a[0] * (udpint)ta4;
    t += (udpint)a[1] * (udpint)ta3;
    t += (udpint)a[2] * (udpint)a[2];
    spint v4 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma6 * (udpint)ta17;
    t += (udpint)ma7 * (udpint)ta16;
    t += (udpint)ma8 * (udpint)ta15;
    t += (udpint)ma9 * (udpint)ta14;
    t += (udpint)ma10 * (udpint)ta13;
    t += (udpint)ma11 * (udpint)ta12;
    t += (udpint)a[0] * (udpint)ta5;
    t += (udpint)a[1] * (udpint)ta4;
    t += (udpint)a[2] * (udpint)ta3;
    spint v5 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma7 * (udpint)ta17;
    t += (udpint)ma8 * (udpint)ta16;
    t += (udpint)ma9 * (udpint)ta15;
    t += (udpint)ma10 * (udpint)ta14;
    t += (udpint)ma11 * (udpint)ta13;
    t += (udpint)ma12 * (udpint)a[12];
    t += (udpint)a[0] * (udpint)ta6;
    t += (udpint)a[1] * (udpint)ta5;
    t += (udpint)a[2] * (udpint)ta4;
    t += (udpint)a[3] * (udpint)a[3];
    spint v6 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma8 * (udpint)ta17;
    t += (udpint)ma9 * (udpint)ta16;
    t += (udpint)ma10 * (udpint)ta15;
    t += (udpint)ma11 * (udpint)ta14;
    t += (udpint)ma12 * (udpint)ta13;
    t += (udpint)a[0] * (udpint)ta7;
    t += (udpint)a[1] * (udpint)ta6;
    t += (udpint)a[2] * (udpint)ta5;
    t += (udpint)a[3] * (udpint)ta4;
    spint v7 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma9 * (udpint)ta17;
    t += (udpint)ma10 * (udpint)ta16;
    t += (udpint)ma11 * (udpint)ta15;
    t += (udpint)ma12 * (udpint)ta14;
    t += (udpint)ma13 * (udpint)a[13];
    t += (udpint)a[0] * (udpint)ta8;
    t += (udpint)a[1] * (udpint)ta7;
    t += (udpint)a[2] * (udpint)ta6;
    t += (udpint)a[3] * (udpint)ta5;
    t += (udpint)a[4] * (udpint)a[4];
    spint v8 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma10 * (udpint)ta17;
    t += (udpint)ma11 * (udpint)ta16;
    t += (udpint)ma12 * (udpint)ta15;
    t += (udpint)ma13 * (udpint)ta14;
    t += (udpint)a[0] * (udpint)ta9;
    t += (udpint)a[1] * (udpint)ta8;
    t += (udpint)a[2] * (udpint)ta7;
    t += (udpint)a[3] * (udpint)ta6;
    t += (udpint)a[4] * (udpint)ta5;
    spint v9 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma11 * (udpint)ta17;
    t += (udpint)ma12 * (udpint)ta16;
    t += (udpint)ma13 * (udpint)ta15;
    t += (udpint)ma14 * (udpint)a[14];
    t += (udpint)a[0] * (udpint)ta10;
    t += (udpint)a[1] * (udpint)ta9;
    t += (udpint)a[2] * (udpint)ta8;
    t += (udpint)a[3] * (udpint)ta7;
    t += (udpint)a[4] * (udpint)ta6;
    t += (udpint)a[5] * (udpint)a[5];
    spint v10 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma12 * (udpint)ta17;
    t += (udpint)ma13 * (udpint)ta16;
    t += (udpint)ma14 * (udpint)ta15;
    t += (udpint)a[0] * (udpint)ta11;
    t += (udpint)a[1] * (udpint)ta10;
    t += (udpint)a[2] * (udpint)ta9;
    t += (udpint)a[3] * (udpint)ta8;
    t += (udpint)a[4] * (udpint)ta7;
    t += (udpint)a[5] * (udpint)ta6;
    spint v11 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma13 * (udpint)ta17;
    t += (udpint)ma14 * (udpint)ta16;
    t += (udpint)ma15 * (udpint)a[15];
    t += (udpint)a[0] * (udpint)ta12;
    t += (udpint)a[1] * (udpint)ta11;
    t += (udpint)a[2] * (udpint)ta10;
    t += (udpint)a[3] * (udpint)ta9;
    t += (udpint)a[4] * (udpint)ta8;
    t += (udpint)a[5] * (udpint)ta7;
    t += (udpint)a[6] * (udpint)a[6];
    spint v12 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma14 * (udpint)ta17;
    t += (udpint)ma15 * (udpint)ta16;
    t += (udpint)a[0] * (udpint)ta13;
    t += (udpint)a[1] * (udpint)ta12;
    t += (udpint)a[2] * (udpint)ta11;
    t += (udpint)a[3] * (udpint)ta10;
    t += (udpint)a[4] * (udpint)ta9;
    t += (udpint)a[5] * (udpint)ta8;
    t += (udpint)a[6] * (udpint)ta7;
    spint v13 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma15 * (udpint)ta17;
    t += (udpint)ma16 * (udpint)a[16];
    t += (udpint)a[0] * (udpint)ta14;
    t += (udpint)a[1] * (udpint)ta13;
    t += (udpint)a[2] * (udpint)ta12;
    t += (udpint)a[3] * (udpint)ta11;
    t += (udpint)a[4] * (udpint)ta10;
    t += (udpint)a[5] * (udpint)ta9;
    t += (udpint)a[6] * (udpint)ta8;
    t += (udpint)a[7] * (udpint)a[7];
    spint v14 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma16 * (udpint)ta17;
    t += (udpint)a[0] * (udpint)ta15;
    t += (udpint)a[1] * (udpint)ta14;
    t += (udpint)a[2] * (udpint)ta13;
    t += (udpint)a[3] * (udpint)ta12;
    t += (udpint)a[4] * (udpint)ta11;
    t += (udpint)a[5] * (udpint)ta10;
    t += (udpint)a[6] * (udpint)ta9;
    t += (udpint)a[7] * (udpint)ta8;
    spint v15 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)ma17 * (udpint)a[17];
    t += (udpint)a[0] * (udpint)ta16;
    t += (udpint)a[1] * (udpint)ta15;
    t += (udpint)a[2] * (udpint)ta14;
    t += (udpint)a[3] * (udpint)ta13;
    t += (udpint)a[4] * (udpint)ta12;
    t += (udpint)a[5] * (udpint)ta11;
    t += (udpint)a[6] * (udpint)ta10;
    t += (udpint)a[7] * (udpint)ta9;
    t += (udpint)a[8] * (udpint)a[8];
    spint v16 = (spint)t & mask;
    t = t >> 29u;
    t += (udpint)a[0] * (udpint)ta17;
    t += (udpint)a[1] * (udpint)ta16;
    t += (udpint)a[2] * (udpint)ta15;
    t += (udpint)a[3] * (udpint)ta14;
    t += (udpint)a[4] * (udpint)ta13;
    t += (udpint)a[5] * (udpint)ta12;
    t += (udpint)a[6] * (udpint)ta11;
    t += (udpint)a[7] * (udpint)ta10;
    t += (udpint)a[8] * (udpint)ta9;
    spint v17 = (spint)t & mask;
    t = t >> 29u;
    // second reduction pass

    udpint ut = (udpint)t;
    ut = (ut << 1) + (spint)(v17 >> 28u);
    v17 &= 0xfffffff;
    s = v0 + ((spint)ut & mask);
    c[0] = (spint)(s & mask);
    carry = (s >> 29) + (spint)(ut >> 29);
    c[1] = v1 + carry;
    c[2] = v2;
    c[3] = v3;
    c[4] = v4;
    c[5] = v5;
    c[6] = v6;
    c[7] = v7;
    c[8] = v8;
    c[9] = v9;
    c[10] = v10;
    c[11] = v11;
    c[12] = v12;
    c[13] = v13;
    c[14] = v14;
    c[15] = v15;
    c[16] = v16;
    c[17] = v17;
}

// copy
static void modcpy_NIST521_ct(const spint *a, spint *c) {
    int i;
    for (i = 0; i < 18; i++) {
        c[i] = a[i];
    }
}

// square n times
static void modnsqr_NIST521_ct(spint *a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        modsqr_NIST521_ct(a, a);
    }
}

// Calculate progenitor - use optimal addition chain
static void modpro_NIST521_ct(const spint *w, spint *z) {
    spint x[18];
    spint t0[18];
    modcpy_NIST521_ct(w, x);
    modsqr_NIST521_ct(x, z);
    modmul_NIST521_ct(x, z, z);
    modcpy_NIST521_ct(z, t0);
    modnsqr_NIST521_ct(t0, 2);
    modmul_NIST521_ct(z, t0, z);
    modcpy_NIST521_ct(z, t0);
    modnsqr_NIST521_ct(t0, 4);
    modmul_NIST521_ct(z, t0, z);
    modcpy_NIST521_ct(z, t0);
    modnsqr_NIST521_ct(t0, 8);
    modmul_NIST521_ct(z, t0, z);
    modcpy_NIST521_ct(z, t0);
    modnsqr_NIST521_ct(t0, 16);
    modmul_NIST521_ct(z, t0, z);
    modcpy_NIST521_ct(z, t0);
    modnsqr_NIST521_ct(t0, 32);
    modmul_NIST521_ct(z, t0, z);
    modsqr_NIST521_ct(z, t0);
    modmul_NIST521_ct(x, t0, t0);
    modnsqr_NIST521_ct(t0, 64);
    modmul_NIST521_ct(z, t0, z);
    modsqr_NIST521_ct(z, t0);
    modmul_NIST521_ct(x, t0, t0);
    modnsqr_NIST521_ct(t0, 129);
    modmul_NIST521_ct(z, t0, z);
    modsqr_NIST521_ct(z, t0);
    modmul_NIST521_ct(x, t0, t0);
    modnsqr_NIST521_ct(t0, 259);
    modmul_NIST521_ct(z, t0, z);
}

// calculate inverse, provide progenitor h if available, NULL if not
static void modinv_NIST521_ct(const spint *x, const spint *h, spint *z) {
    spint s[18];
    spint t[18];
    if (h == NULL) {
        modpro_NIST521_ct(x, t);
    }
    else {
        modcpy_NIST521_ct(h, t);
    }
    modcpy_NIST521_ct(x, s);
    modnsqr_NIST521_ct(t, 2);
    modmul_NIST521_ct(s, t, z);
}

// Convert m to internal form, n=nres(m)
static void nres_NIST521_ct(const spint *m, spint *n) {
    int i;
    for (i = 0; i < 18; i++) {
        n[i] = m[i];
    }
}

// Convert n back to normal form, m=redc(n)
static void redc_NIST521_ct(const spint *n, spint *m) {
    int i;
    for (i = 0; i < 18; i++) {
        m[i] = n[i];
    }
    (void)modfsb_NIST521_ct(m);
}

// is unity?
static int modis1_NIST521_ct(const spint *a) {
    int i;
    spint c[18];
    spint c0;
    spint d = 0;
    redc_NIST521_ct(a, c);
    for (i = 1; i < 18; i++) {
        d |= c[i];
    }
    c0 = (spint)c[0];
    return ((spint)1 & ((d - (spint)1) >> 29u) & (((c0 ^ (spint)1) - (spint)1) >> 29u));
}

// is zero?
static int modis0_NIST521_ct(const spint *a) {
    int i;
    spint c[18];
    spint d = 0;
    redc_NIST521_ct(a, c);
    for (i = 0; i < 18; i++) {
        d |= c[i];
    }
    return ((spint)1 & ((d - (spint)1) >> 29u));
}

// set to zero
static void modzer_NIST521_ct(spint *a) {
    int i;
    for (i = 0; i < 18; i++) {
        a[i] = 0;
    }
}

// set to one
static void modone_NIST521_ct(spint *a) {
    int i;
    a[0] = 1;
    for (i = 1; i < 18; i++) {
        a[i] = 0;
    }
    nres_NIST521_ct(a, a);
}

// set to integer
static void modint_NIST521_ct(int x, spint *a) {
    int i;
    a[0] = (spint)x;
    for (i = 1; i < 18; i++) {
        a[i] = 0;
    }
    nres_NIST521_ct(a, a);
}

// Test for quadratic residue, provide progenitor h if available, NULL if not
static int modqr_NIST521_ct(const spint *h, const spint *x) {
    spint r[18];
    if (h == NULL) {
        modpro_NIST521_ct(x, r);
        modsqr_NIST521_ct(r, r);
    }
    else {
        modsqr_NIST521_ct(h, r);
    }
    modmul_NIST521_ct(r, x, r);
    return modis1_NIST521_ct(r) | modis0_NIST521_ct(x);
}

// conditional move g to f if d=1
// strongly recommend inlining be disabled using compiler specific syntax
static void modcmv_NIST521_ct(int b, const spint *g, volatile spint *f) {
    int i;
    spint c0, c1, s, t, aux;
    spint r = 0x5aa5a55au;
    c0 = (~b) & (r + 1);
    c1 = b + r;
    for (i = 0; i < 18; i++) {
        s = g[i];
        t = f[i];
        f[i] = aux = c0 * t + c1 * s;
        f[i] = aux - r * (t + s);
    }
}

// conditional swap g and f if d=1
// strongly recommend inlining be disabled using compiler specific syntax
static void modcsw_NIST521_ct(int b, volatile spint *g, volatile spint *f) {
    int i;
    spint c0, c1, s, t, w, aux;
    spint r = 0x5aa5a55au;
    c0 = (~b) & (r + 1);
    c1 = b + r;
    for (i = 0; i < 18; i++) {
        s = g[i];
        t = f[i];
        w = r * (t + s);
        f[i] = aux = c0 * t + c1 * s;
        f[i] = aux - w;
        g[i] = aux = c0 * s + c1 * t;
        g[i] = aux - w;
    }
}

// Modular square root, provide progenitor h if available, NULL if not
static void modsqrt_NIST521_ct(const spint *x, const spint *h, spint *r) {
    spint s[18];
    spint y[18];
    if (h == NULL) {
        modpro_NIST521_ct(x, y);
    }
    else {
        modcpy_NIST521_ct(h, y);
    }
    modmul_NIST521_ct(y, x, s);
    modcpy_NIST521_ct(s, r);
}

// shift left by less than a word
static void modshl_NIST521_ct(unsigned int n, spint *a) {
    int i;
    a[17] = ((a[17] << n)) | (a[16] >> (29u - n));
    for (i = 16; i > 0; i--) {
        a[i] = ((a[i] << n) & (spint)0x1fffffff) | (a[i - 1] >> (29u - n));
    }
    a[0] = (a[0] << n) & (spint)0x1fffffff;
}

// shift right by less than a word. Return shifted out part
static int modshr_NIST521_ct(unsigned int n, spint *a) {
    int i;
    spint r = a[0] & (((spint)1 << n) - (spint)1);
    for (i = 0; i < 17; i++) {
        a[i] = (a[i] >> n) | ((a[i + 1] << (29u - n)) & (spint)0x1fffffff);
    }
    a[17] = a[17] >> n;
    return r;
}

// set a= 2^r
static void mod2r_NIST521_ct(unsigned int r, spint *a) {
    unsigned int n = r / 29u;
    unsigned int m = r % 29u;
    modzer_NIST521_ct(a);
    if (r >= 66 * 8) return;
    a[n] = 1;
    a[n] <<= m;
}

// export to byte array
static void modexp_NIST521_ct(const spint *a, char *b) {
    int i;
    spint c[18];
    redc_NIST521_ct(a, c);
    for (i = 65; i >= 0; i--) {
        b[i] = c[0] & (spint)0xff;
        (void)modshr_NIST521_ct(8, c);
    }
}

// import from byte array
// returns 1 if in range, else 0
static int modimp_NIST521_ct(const char *b, spint *a) {
    int i, res;
    for (i = 0; i < 18; i++) {
        a[i] = 0;
    }
    for (i = 0; i < 66; i++) {
        modshl_NIST521_ct(8, a);
        a[0] += (spint)(unsigned char)b[i];
    }
    res = modfsb_NIST521_ct(a);
    nres_NIST521_ct(a, a);
    return res;
}

// determine sign
static int modsign_NIST521_ct(const spint *a) {
    spint c[18];
    redc_NIST521_ct(a, c);
    return c[0] % 2;
}

// return true if equal
static int modcmp_NIST521_ct(const spint *a, const spint *b) {
    spint c[18], d[18];
    int i, eq = 1;
    redc_NIST521_ct(a, c);
    redc_NIST521_ct(b, d);
    for (i = 0; i < 18; i++) {
        eq &= (((c[i] ^ d[i]) - 1) >> 29) & 1;
    }
    return eq;
}
