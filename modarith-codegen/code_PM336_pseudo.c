
// Automatically generated modular arithmetic C code for pseudo-Mersenne primes
// Python Script by Mike Scott (Technology Innovation Institute, UAE, 2025)

#include <stdint.h>
#include <stdio.h>

#define sspint int32_t
#define spint uint32_t
#define udpint uint64_t
#define dpint uint64_t

#define Wordlength_PM336_ct 32
#define Nlimbs_PM336_ct 12
#define Radix_PM336_ct 28
#define Nbits_PM336_ct 336
#define Nbytes_PM336_ct 42

#define MERSENNE
#define MULBYINT
#define PM336

// propagate carries
static spint inline prop(spint *n) {
    int i;
    spint mask = ((spint)1 << 28u) - (spint)1;
    sspint carry = (sspint)n[0];
    carry >>= 28u;
    n[0] &= mask;
    for (i = 1; i < 11; i++) {
        carry += (sspint)n[i];
        n[i] = (spint)carry & mask;
        carry >>= 28u;
    }
    n[11] += (spint)carry;
    return -((n[11] >> 1) >> 30u);
}

// propagate carries and add p if negative, propagate carries again
static int inline flatten(spint *n) {
    spint carry = prop(n);
    n[0] -= ((spint)3u) & carry;
    n[11] += ((spint)0x10000000u) & carry;
    (void)prop(n);
    return (int)(carry & 1);
}

// Montgomery final subtract
static int modfsb_PM336_ct(spint *n) {
    n[0] += (spint)3u;
    n[11] -= (spint)0x10000000u;
    return flatten(n);
}

// Modular addition - reduce less than 2p
static void modadd_PM336_ct(const spint *a, const spint *b, spint *n) {
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
    n[0] += (spint)6u;
    n[11] -= (spint)0x20000000u;
    carry = prop(n);
    n[0] -= ((spint)6u) & carry;
    n[11] += ((spint)0x20000000u) & carry;
    (void)prop(n);
}

// Modular subtraction - reduce less than 2p
static void modsub_PM336_ct(const spint *a, const spint *b, spint *n) {
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
    carry = prop(n);
    n[0] -= ((spint)6u) & carry;
    n[11] += ((spint)0x20000000u) & carry;
    (void)prop(n);
}

// Modular negation
static void modneg_PM336_ct(const spint *b, spint *n) {
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
    carry = prop(n);
    n[0] -= ((spint)6u) & carry;
    n[11] += ((spint)0x20000000u) & carry;
    (void)prop(n);
}

// Modular multiplication by an integer, c=a*b mod 2p
static void modmli_PM336_ct(const spint *a, int b, spint *c) {
    udpint t = 0;
    spint carry;
    spint s;
    spint mask = ((spint)1 << 28u) - (spint)1;
    t += (udpint)a[0] * (udpint)b;
    spint v0 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)a[1] * (udpint)b;
    spint v1 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)a[2] * (udpint)b;
    spint v2 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)a[3] * (udpint)b;
    spint v3 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)a[4] * (udpint)b;
    spint v4 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)a[5] * (udpint)b;
    spint v5 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)a[6] * (udpint)b;
    spint v6 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)a[7] * (udpint)b;
    spint v7 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)a[8] * (udpint)b;
    spint v8 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)a[9] * (udpint)b;
    spint v9 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)a[10] * (udpint)b;
    spint v10 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)a[11] * (udpint)b;
    spint v11 = (spint)t & mask;
    t = t >> 28u;
    // second reduction pass

    udpint ut = (udpint)t;
    ut *= 0x3;
    s = v0 + ((spint)ut & mask);
    c[0] = (spint)(s & mask);
    carry = (s >> 28) + (spint)(ut >> 28);
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
}

// Modular multiplication, c=a*b mod 2p
static void modmul_PM336_ct(const spint *a, const spint *b, spint *c) {
    dpint t = 0;
    spint ma1 = a[1] * (spint)0x3;
    spint ma2 = a[2] * (spint)0x3;
    spint ma3 = a[3] * (spint)0x3;
    spint ma4 = a[4] * (spint)0x3;
    spint ma5 = a[5] * (spint)0x3;
    spint ma6 = a[6] * (spint)0x3;
    spint ma7 = a[7] * (spint)0x3;
    spint ma8 = a[8] * (spint)0x3;
    spint ma9 = a[9] * (spint)0x3;
    spint ma10 = a[10] * (spint)0x3;
    spint ma11 = a[11] * (spint)0x3;
    spint carry;
    spint s;
    spint mask = ((spint)1 << 28u) - (spint)1;
    t += (dpint)ma1 * (dpint)b[11];
    t += (dpint)ma2 * (dpint)b[10];
    t += (dpint)ma3 * (dpint)b[9];
    t += (dpint)ma4 * (dpint)b[8];
    t += (dpint)ma5 * (dpint)b[7];
    t += (dpint)ma6 * (dpint)b[6];
    t += (dpint)ma7 * (dpint)b[5];
    t += (dpint)ma8 * (dpint)b[4];
    t += (dpint)ma9 * (dpint)b[3];
    t += (dpint)ma10 * (dpint)b[2];
    t += (dpint)ma11 * (dpint)b[1];
    t += (dpint)a[0] * (dpint)b[0];
    spint v0 = (spint)t & mask;
    t = t >> 28u;
    t += (dpint)ma2 * (dpint)b[11];
    t += (dpint)ma3 * (dpint)b[10];
    t += (dpint)ma4 * (dpint)b[9];
    t += (dpint)ma5 * (dpint)b[8];
    t += (dpint)ma6 * (dpint)b[7];
    t += (dpint)ma7 * (dpint)b[6];
    t += (dpint)ma8 * (dpint)b[5];
    t += (dpint)ma9 * (dpint)b[4];
    t += (dpint)ma10 * (dpint)b[3];
    t += (dpint)ma11 * (dpint)b[2];
    t += (dpint)a[0] * (dpint)b[1];
    t += (dpint)a[1] * (dpint)b[0];
    spint v1 = (spint)t & mask;
    t = t >> 28u;
    t += (dpint)ma3 * (dpint)b[11];
    t += (dpint)ma4 * (dpint)b[10];
    t += (dpint)ma5 * (dpint)b[9];
    t += (dpint)ma6 * (dpint)b[8];
    t += (dpint)ma7 * (dpint)b[7];
    t += (dpint)ma8 * (dpint)b[6];
    t += (dpint)ma9 * (dpint)b[5];
    t += (dpint)ma10 * (dpint)b[4];
    t += (dpint)ma11 * (dpint)b[3];
    t += (dpint)a[0] * (dpint)b[2];
    t += (dpint)a[1] * (dpint)b[1];
    t += (dpint)a[2] * (dpint)b[0];
    spint v2 = (spint)t & mask;
    t = t >> 28u;
    t += (dpint)ma4 * (dpint)b[11];
    t += (dpint)ma5 * (dpint)b[10];
    t += (dpint)ma6 * (dpint)b[9];
    t += (dpint)ma7 * (dpint)b[8];
    t += (dpint)ma8 * (dpint)b[7];
    t += (dpint)ma9 * (dpint)b[6];
    t += (dpint)ma10 * (dpint)b[5];
    t += (dpint)ma11 * (dpint)b[4];
    t += (dpint)a[0] * (dpint)b[3];
    t += (dpint)a[1] * (dpint)b[2];
    t += (dpint)a[2] * (dpint)b[1];
    t += (dpint)a[3] * (dpint)b[0];
    spint v3 = (spint)t & mask;
    t = t >> 28u;
    t += (dpint)ma5 * (dpint)b[11];
    t += (dpint)ma6 * (dpint)b[10];
    t += (dpint)ma7 * (dpint)b[9];
    t += (dpint)ma8 * (dpint)b[8];
    t += (dpint)ma9 * (dpint)b[7];
    t += (dpint)ma10 * (dpint)b[6];
    t += (dpint)ma11 * (dpint)b[5];
    t += (dpint)a[0] * (dpint)b[4];
    t += (dpint)a[1] * (dpint)b[3];
    t += (dpint)a[2] * (dpint)b[2];
    t += (dpint)a[3] * (dpint)b[1];
    t += (dpint)a[4] * (dpint)b[0];
    spint v4 = (spint)t & mask;
    t = t >> 28u;
    t += (dpint)ma6 * (dpint)b[11];
    t += (dpint)ma7 * (dpint)b[10];
    t += (dpint)ma8 * (dpint)b[9];
    t += (dpint)ma9 * (dpint)b[8];
    t += (dpint)ma10 * (dpint)b[7];
    t += (dpint)ma11 * (dpint)b[6];
    t += (dpint)a[0] * (dpint)b[5];
    t += (dpint)a[1] * (dpint)b[4];
    t += (dpint)a[2] * (dpint)b[3];
    t += (dpint)a[3] * (dpint)b[2];
    t += (dpint)a[4] * (dpint)b[1];
    t += (dpint)a[5] * (dpint)b[0];
    spint v5 = (spint)t & mask;
    t = t >> 28u;
    t += (dpint)ma7 * (dpint)b[11];
    t += (dpint)ma8 * (dpint)b[10];
    t += (dpint)ma9 * (dpint)b[9];
    t += (dpint)ma10 * (dpint)b[8];
    t += (dpint)ma11 * (dpint)b[7];
    t += (dpint)a[0] * (dpint)b[6];
    t += (dpint)a[1] * (dpint)b[5];
    t += (dpint)a[2] * (dpint)b[4];
    t += (dpint)a[3] * (dpint)b[3];
    t += (dpint)a[4] * (dpint)b[2];
    t += (dpint)a[5] * (dpint)b[1];
    t += (dpint)a[6] * (dpint)b[0];
    spint v6 = (spint)t & mask;
    t = t >> 28u;
    t += (dpint)ma8 * (dpint)b[11];
    t += (dpint)ma9 * (dpint)b[10];
    t += (dpint)ma10 * (dpint)b[9];
    t += (dpint)ma11 * (dpint)b[8];
    t += (dpint)a[0] * (dpint)b[7];
    t += (dpint)a[1] * (dpint)b[6];
    t += (dpint)a[2] * (dpint)b[5];
    t += (dpint)a[3] * (dpint)b[4];
    t += (dpint)a[4] * (dpint)b[3];
    t += (dpint)a[5] * (dpint)b[2];
    t += (dpint)a[6] * (dpint)b[1];
    t += (dpint)a[7] * (dpint)b[0];
    spint v7 = (spint)t & mask;
    t = t >> 28u;
    t += (dpint)ma9 * (dpint)b[11];
    t += (dpint)ma10 * (dpint)b[10];
    t += (dpint)ma11 * (dpint)b[9];
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
    t = t >> 28u;
    t += (dpint)ma10 * (dpint)b[11];
    t += (dpint)ma11 * (dpint)b[10];
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
    t = t >> 28u;
    t += (dpint)ma11 * (dpint)b[11];
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
    t = t >> 28u;
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
    t = t >> 28u;
    // second reduction pass

    udpint ut = (udpint)t;
    ut *= 0x3;
    s = v0 + ((spint)ut & mask);
    c[0] = (spint)(s & mask);
    carry = (s >> 28) + (spint)(ut >> 28);
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
}

// Modular squaring, c=a*a mod 2p
static void modsqr_PM336_ct(const spint *a, spint *c) {
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
    spint ma1 = a[1] * (spint)0x3;
    spint ma2 = a[2] * (spint)0x3;
    spint ma3 = a[3] * (spint)0x3;
    spint ma4 = a[4] * (spint)0x3;
    spint ma5 = a[5] * (spint)0x3;
    spint ma6 = a[6] * (spint)0x3;
    spint ma7 = a[7] * (spint)0x3;
    spint ma8 = a[8] * (spint)0x3;
    spint ma9 = a[9] * (spint)0x3;
    spint ma10 = a[10] * (spint)0x3;
    spint ma11 = a[11] * (spint)0x3;
    spint carry;
    spint s;
    spint mask = ((spint)1 << 28u) - (spint)1;
    t += (udpint)ma1 * (udpint)ta11;
    t += (udpint)ma2 * (udpint)ta10;
    t += (udpint)ma3 * (udpint)ta9;
    t += (udpint)ma4 * (udpint)ta8;
    t += (udpint)ma5 * (udpint)ta7;
    t += (udpint)ma6 * (udpint)a[6];
    t += (udpint)a[0] * (udpint)a[0];
    spint v0 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)ma2 * (udpint)ta11;
    t += (udpint)ma3 * (udpint)ta10;
    t += (udpint)ma4 * (udpint)ta9;
    t += (udpint)ma5 * (udpint)ta8;
    t += (udpint)ma6 * (udpint)ta7;
    t += (udpint)a[0] * (udpint)ta1;
    spint v1 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)ma3 * (udpint)ta11;
    t += (udpint)ma4 * (udpint)ta10;
    t += (udpint)ma5 * (udpint)ta9;
    t += (udpint)ma6 * (udpint)ta8;
    t += (udpint)ma7 * (udpint)a[7];
    t += (udpint)a[0] * (udpint)ta2;
    t += (udpint)a[1] * (udpint)a[1];
    spint v2 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)ma4 * (udpint)ta11;
    t += (udpint)ma5 * (udpint)ta10;
    t += (udpint)ma6 * (udpint)ta9;
    t += (udpint)ma7 * (udpint)ta8;
    t += (udpint)a[0] * (udpint)ta3;
    t += (udpint)a[1] * (udpint)ta2;
    spint v3 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)ma5 * (udpint)ta11;
    t += (udpint)ma6 * (udpint)ta10;
    t += (udpint)ma7 * (udpint)ta9;
    t += (udpint)ma8 * (udpint)a[8];
    t += (udpint)a[0] * (udpint)ta4;
    t += (udpint)a[1] * (udpint)ta3;
    t += (udpint)a[2] * (udpint)a[2];
    spint v4 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)ma6 * (udpint)ta11;
    t += (udpint)ma7 * (udpint)ta10;
    t += (udpint)ma8 * (udpint)ta9;
    t += (udpint)a[0] * (udpint)ta5;
    t += (udpint)a[1] * (udpint)ta4;
    t += (udpint)a[2] * (udpint)ta3;
    spint v5 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)ma7 * (udpint)ta11;
    t += (udpint)ma8 * (udpint)ta10;
    t += (udpint)ma9 * (udpint)a[9];
    t += (udpint)a[0] * (udpint)ta6;
    t += (udpint)a[1] * (udpint)ta5;
    t += (udpint)a[2] * (udpint)ta4;
    t += (udpint)a[3] * (udpint)a[3];
    spint v6 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)ma8 * (udpint)ta11;
    t += (udpint)ma9 * (udpint)ta10;
    t += (udpint)a[0] * (udpint)ta7;
    t += (udpint)a[1] * (udpint)ta6;
    t += (udpint)a[2] * (udpint)ta5;
    t += (udpint)a[3] * (udpint)ta4;
    spint v7 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)ma9 * (udpint)ta11;
    t += (udpint)ma10 * (udpint)a[10];
    t += (udpint)a[0] * (udpint)ta8;
    t += (udpint)a[1] * (udpint)ta7;
    t += (udpint)a[2] * (udpint)ta6;
    t += (udpint)a[3] * (udpint)ta5;
    t += (udpint)a[4] * (udpint)a[4];
    spint v8 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)ma10 * (udpint)ta11;
    t += (udpint)a[0] * (udpint)ta9;
    t += (udpint)a[1] * (udpint)ta8;
    t += (udpint)a[2] * (udpint)ta7;
    t += (udpint)a[3] * (udpint)ta6;
    t += (udpint)a[4] * (udpint)ta5;
    spint v9 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)ma11 * (udpint)a[11];
    t += (udpint)a[0] * (udpint)ta10;
    t += (udpint)a[1] * (udpint)ta9;
    t += (udpint)a[2] * (udpint)ta8;
    t += (udpint)a[3] * (udpint)ta7;
    t += (udpint)a[4] * (udpint)ta6;
    t += (udpint)a[5] * (udpint)a[5];
    spint v10 = (spint)t & mask;
    t = t >> 28u;
    t += (udpint)a[0] * (udpint)ta11;
    t += (udpint)a[1] * (udpint)ta10;
    t += (udpint)a[2] * (udpint)ta9;
    t += (udpint)a[3] * (udpint)ta8;
    t += (udpint)a[4] * (udpint)ta7;
    t += (udpint)a[5] * (udpint)ta6;
    spint v11 = (spint)t & mask;
    t = t >> 28u;
    // second reduction pass

    udpint ut = (udpint)t;
    ut *= 0x3;
    s = v0 + ((spint)ut & mask);
    c[0] = (spint)(s & mask);
    carry = (s >> 28) + (spint)(ut >> 28);
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
}

// copy
static void modcpy_PM336_ct(const spint *a, spint *c) {
    int i;
    for (i = 0; i < 12; i++) {
        c[i] = a[i];
    }
}

// square n times
static void modnsqr_PM336_ct(spint *a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        modsqr_PM336_ct(a, a);
    }
}

// Calculate progenitor - use optimal addition chain
static void modpro_PM336_ct(const spint *w, spint *z) {
    spint x[12];
    spint t0[12];
    spint t1[12];
    modcpy_PM336_ct(w, x);
    modsqr_PM336_ct(x, z);
    modmul_PM336_ct(x, z, z);
    modsqr_PM336_ct(z, z);
    modmul_PM336_ct(x, z, z);
    modcpy_PM336_ct(z, t0);
    modnsqr_PM336_ct(t0, 3);
    modmul_PM336_ct(z, t0, z);
    modsqr_PM336_ct(z, t0);
    modmul_PM336_ct(x, t0, t0);
    modcpy_PM336_ct(t0, t1);
    modnsqr_PM336_ct(t1, 6);
    modmul_PM336_ct(z, t1, z);
    modcpy_PM336_ct(z, t1);
    modnsqr_PM336_ct(t1, 7);
    modmul_PM336_ct(t0, t1, t0);
    modcpy_PM336_ct(t0, t1);
    modnsqr_PM336_ct(t1, 20);
    modmul_PM336_ct(t0, t1, t0);
    modcpy_PM336_ct(t0, t1);
    modnsqr_PM336_ct(t1, 40);
    modmul_PM336_ct(t0, t1, t0);
    modcpy_PM336_ct(t0, t1);
    modnsqr_PM336_ct(t1, 80);
    modmul_PM336_ct(t0, t1, t0);
    modcpy_PM336_ct(t0, t1);
    modnsqr_PM336_ct(t1, 160);
    modmul_PM336_ct(t0, t1, t0);
    modnsqr_PM336_ct(t0, 13);
    modmul_PM336_ct(z, t0, z);
}

// calculate inverse, provide progenitor h if available, NULL if not
static void modinv_PM336_ct(const spint *x, const spint *h, spint *z) {
    int i;
    spint s[12];
    spint t[12];
    if (h == NULL) {
        modpro_PM336_ct(x, t);
    }
    else {
        modcpy_PM336_ct(h, t);
    }
    modcpy_PM336_ct(x, s);
    for (i = 0; i < 1; i++) {
        modsqr_PM336_ct(s, s);
        modmul_PM336_ct(s, x, s);
    }
    modnsqr_PM336_ct(t, 3);
    modmul_PM336_ct(s, t, z);
}

// Convert m to internal form, n=nres(m)
static void nres_PM336_ct(const spint *m, spint *n) {
    int i;
    for (i = 0; i < 12; i++) {
        n[i] = m[i];
    }
}

// Convert n back to normal form, m=redc(n)
static void redc_PM336_ct(const spint *n, spint *m) {
    int i;
    for (i = 0; i < 12; i++) {
        m[i] = n[i];
    }
    (void)modfsb_PM336_ct(m);
}

// is unity?
static int modis1_PM336_ct(const spint *a) {
    int i;
    spint c[12];
    spint c0;
    spint d = 0;
    redc_PM336_ct(a, c);
    for (i = 1; i < 12; i++) {
        d |= c[i];
    }
    c0 = (spint)c[0];
    return ((spint)1 & ((d - (spint)1) >> 28u) & (((c0 ^ (spint)1) - (spint)1) >> 28u));
}

// is zero?
static int modis0_PM336_ct(const spint *a) {
    int i;
    spint c[12];
    spint d = 0;
    redc_PM336_ct(a, c);
    for (i = 0; i < 12; i++) {
        d |= c[i];
    }
    return ((spint)1 & ((d - (spint)1) >> 28u));
}

// set to zero
static void modzer_PM336_ct(spint *a) {
    int i;
    for (i = 0; i < 12; i++) {
        a[i] = 0;
    }
}

// set to one
static void modone_PM336_ct(spint *a) {
    int i;
    a[0] = 1;
    for (i = 1; i < 12; i++) {
        a[i] = 0;
    }
    nres_PM336_ct(a, a);
}

// set to integer
static void modint_PM336_ct(int x, spint *a) {
    int i;
    a[0] = (spint)x;
    for (i = 1; i < 12; i++) {
        a[i] = 0;
    }
    nres_PM336_ct(a, a);
}

// Test for quadratic residue, provide progenitor h if available, NULL if not
static int modqr_PM336_ct(const spint *h, const spint *x) {
    spint r[12];
    if (h == NULL) {
        modpro_PM336_ct(x, r);
        modsqr_PM336_ct(r, r);
    }
    else {
        modsqr_PM336_ct(h, r);
    }
    modmul_PM336_ct(r, x, r);
    modnsqr_PM336_ct(r, 1);
    return modis1_PM336_ct(r) | modis0_PM336_ct(x);
}

// conditional move g to f if d=1
// strongly recommend inlining be disabled using compiler specific syntax
static void modcmv_PM336_ct(int b, const spint *g, volatile spint *f) {
    int i;
    spint c0, c1, s, t, aux;
    spint r = 0x5aa5a55au;
    c0 = (~b) & (r + 1);
    c1 = b + r;
    for (i = 0; i < 12; i++) {
        s = g[i];
        t = f[i];
        f[i] = aux = c0 * t + c1 * s;
        f[i] = aux - r * (t + s);
    }
}

// conditional swap g and f if d=1
// strongly recommend inlining be disabled using compiler specific syntax
static void modcsw_PM336_ct(int b, volatile spint *g, volatile spint *f) {
    int i;
    spint c0, c1, s, t, w, aux;
    spint r = 0x5aa5a55au;
    c0 = (~b) & (r + 1);
    c1 = b + r;
    for (i = 0; i < 12; i++) {
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
static void modsqrt_PM336_ct(const spint *x, const spint *h, spint *r) {
    int k;
    spint t[12];
    spint b[12];
    spint v[12];
    spint z[12] = {0x559d3b8, 0x804827f, 0xeac636b, 0x4538b93, 0x95da4c9, 0xa9fca8b,
                   0x41f61ed, 0x3df798c, 0x8b2b455, 0x7811fc3, 0x31ef52,  0xf93fc3e};
    spint s[12];
    spint y[12];
    if (h == NULL) {
        modpro_PM336_ct(x, y);
    }
    else {
        modcpy_PM336_ct(h, y);
    }
    modmul_PM336_ct(y, x, s);
    modmul_PM336_ct(s, y, t);
    nres_PM336_ct(z, z);
    for (k = 2; k > 1; k--) {
        modcpy_PM336_ct(t, b);
        modnsqr_PM336_ct(b, k - 2);
        int d = 1 - modis1_PM336_ct(b);
        modmul_PM336_ct(s, z, v);
        modcmv_PM336_ct(d, v, s);
        modsqr_PM336_ct(z, z);
        modmul_PM336_ct(t, z, v);
        modcmv_PM336_ct(d, v, t);
    }
    modcpy_PM336_ct(s, r);
}

// shift left by less than a word
static void modshl_PM336_ct(unsigned int n, spint *a) {
    int i;
    a[11] = ((a[11] << n)) | (a[10] >> (28u - n));
    for (i = 10; i > 0; i--) {
        a[i] = ((a[i] << n) & (spint)0xfffffff) | (a[i - 1] >> (28u - n));
    }
    a[0] = (a[0] << n) & (spint)0xfffffff;
}

// shift right by less than a word. Return shifted out part
static int modshr_PM336_ct(unsigned int n, spint *a) {
    int i;
    spint r = a[0] & (((spint)1 << n) - (spint)1);
    for (i = 0; i < 11; i++) {
        a[i] = (a[i] >> n) | ((a[i + 1] << (28u - n)) & (spint)0xfffffff);
    }
    a[11] = a[11] >> n;
    return r;
}

// set a= 2^r
static void mod2r_PM336_ct(unsigned int r, spint *a) {
    unsigned int n = r / 28u;
    unsigned int m = r % 28u;
    modzer_PM336_ct(a);
    if (r >= 42 * 8) return;
    a[n] = 1;
    a[n] <<= m;
}

// export to byte array
static void modexp_PM336_ct(const spint *a, char *b) {
    int i;
    spint c[12];
    redc_PM336_ct(a, c);
    for (i = 41; i >= 0; i--) {
        b[i] = c[0] & (spint)0xff;
        (void)modshr_PM336_ct(8, c);
    }
}

// import from byte array
// returns 1 if in range, else 0
static int modimp_PM336_ct(const char *b, spint *a) {
    int i, res;
    for (i = 0; i < 12; i++) {
        a[i] = 0;
    }
    for (i = 0; i < 42; i++) {
        modshl_PM336_ct(8, a);
        a[0] += (spint)(unsigned char)b[i];
    }
    res = modfsb_PM336_ct(a);
    nres_PM336_ct(a, a);
    return res;
}

// determine sign
static int modsign_PM336_ct(const spint *a) {
    spint c[12];
    redc_PM336_ct(a, c);
    return c[0] % 2;
}

// return true if equal
static int modcmp_PM336_ct(const spint *a, const spint *b) {
    spint c[12], d[12];
    int i, eq = 1;
    redc_PM336_ct(a, c);
    redc_PM336_ct(b, d);
    for (i = 0; i < 12; i++) {
        eq &= (((c[i] ^ d[i]) - 1) >> 28) & 1;
    }
    return eq;
}
