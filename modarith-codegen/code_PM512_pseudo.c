
// Automatically generated modular arithmetic C code for pseudo-Mersenne primes
// Python Script by Mike Scott (Technology Innovation Institute, UAE, 2025)

#include <stdint.h>
#include <stdio.h>

#define sspint int32_t
#define spint uint32_t
#define udpint uint64_t
#define dpint uint64_t

#define Wordlength_PM512_ct 32
#define Nlimbs_PM512_ct 18
#define Radix_PM512_ct 29
#define Nbits_PM512_ct 512
#define Nbytes_PM512_ct 64

#define MERSENNE
#define MULBYINT
#define PM512

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
    n[0] -= ((spint)569u) & carry;
    n[17] += ((spint)0x80000u) & carry;
    (void)prop(n);
    return (int)(carry & 1);
}

// Montgomery final subtract
static int modfsb_PM512_ct(spint *n) {
    n[0] += (spint)569u;
    n[17] -= (spint)0x80000u;
    return flatten(n);
}

// Modular addition - reduce less than 2p
static void modadd_PM512_ct(const spint *a, const spint *b, spint *n) {
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
    n[0] += (spint)1138u;
    n[17] -= (spint)0x100000u;
    carry = prop(n);
    n[0] -= ((spint)1138u) & carry;
    n[17] += ((spint)0x100000u) & carry;
    (void)prop(n);
}

// Modular subtraction - reduce less than 2p
static void modsub_PM512_ct(const spint *a, const spint *b, spint *n) {
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
    n[0] -= ((spint)1138u) & carry;
    n[17] += ((spint)0x100000u) & carry;
    (void)prop(n);
}

// Modular negation
static void modneg_PM512_ct(const spint *b, spint *n) {
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
    n[0] -= ((spint)1138u) & carry;
    n[17] += ((spint)0x100000u) & carry;
    (void)prop(n);
}

// Modular multiplication by an integer, c=a*b mod 2p
static void modmli_PM512_ct(const spint *a, int b, spint *c) {
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
    ut = (ut << 10) + (spint)(v17 >> 19u);
    v17 &= 0x7ffff;
    ut *= 0x239;
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
static void modmul_PM512_ct(const spint *a, const spint *b, spint *c) {
    dpint t = 0;
    dpint tt;
    spint lo;
    dpint hi;
    spint carry;
    spint s;
    spint mask = ((spint)1 << 29u) - (spint)1;
    tt = (dpint)a[1] * (dpint)b[17];
    tt += (dpint)a[2] * (dpint)b[16];
    tt += (dpint)a[3] * (dpint)b[15];
    tt += (dpint)a[4] * (dpint)b[14];
    tt += (dpint)a[5] * (dpint)b[13];
    tt += (dpint)a[6] * (dpint)b[12];
    tt += (dpint)a[7] * (dpint)b[11];
    tt += (dpint)a[8] * (dpint)b[10];
    tt += (dpint)a[9] * (dpint)b[9];
    tt += (dpint)a[10] * (dpint)b[8];
    tt += (dpint)a[11] * (dpint)b[7];
    tt += (dpint)a[12] * (dpint)b[6];
    tt += (dpint)a[13] * (dpint)b[5];
    tt += (dpint)a[14] * (dpint)b[4];
    tt += (dpint)a[15] * (dpint)b[3];
    tt += (dpint)a[16] * (dpint)b[2];
    tt += (dpint)a[17] * (dpint)b[1];
    lo = (spint)tt & mask;
    t += (dpint)lo * (dpint)0x8e400;
    hi = tt >> 29u;
    t += (dpint)a[0] * (dpint)b[0];
    spint v0 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[2] * (dpint)b[17];
    tt += (dpint)a[3] * (dpint)b[16];
    tt += (dpint)a[4] * (dpint)b[15];
    tt += (dpint)a[5] * (dpint)b[14];
    tt += (dpint)a[6] * (dpint)b[13];
    tt += (dpint)a[7] * (dpint)b[12];
    tt += (dpint)a[8] * (dpint)b[11];
    tt += (dpint)a[9] * (dpint)b[10];
    tt += (dpint)a[10] * (dpint)b[9];
    tt += (dpint)a[11] * (dpint)b[8];
    tt += (dpint)a[12] * (dpint)b[7];
    tt += (dpint)a[13] * (dpint)b[6];
    tt += (dpint)a[14] * (dpint)b[5];
    tt += (dpint)a[15] * (dpint)b[4];
    tt += (dpint)a[16] * (dpint)b[3];
    tt += (dpint)a[17] * (dpint)b[2];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
    t += (dpint)a[0] * (dpint)b[1];
    t += (dpint)a[1] * (dpint)b[0];
    spint v1 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[3] * (dpint)b[17];
    tt += (dpint)a[4] * (dpint)b[16];
    tt += (dpint)a[5] * (dpint)b[15];
    tt += (dpint)a[6] * (dpint)b[14];
    tt += (dpint)a[7] * (dpint)b[13];
    tt += (dpint)a[8] * (dpint)b[12];
    tt += (dpint)a[9] * (dpint)b[11];
    tt += (dpint)a[10] * (dpint)b[10];
    tt += (dpint)a[11] * (dpint)b[9];
    tt += (dpint)a[12] * (dpint)b[8];
    tt += (dpint)a[13] * (dpint)b[7];
    tt += (dpint)a[14] * (dpint)b[6];
    tt += (dpint)a[15] * (dpint)b[5];
    tt += (dpint)a[16] * (dpint)b[4];
    tt += (dpint)a[17] * (dpint)b[3];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
    t += (dpint)a[0] * (dpint)b[2];
    t += (dpint)a[1] * (dpint)b[1];
    t += (dpint)a[2] * (dpint)b[0];
    spint v2 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[4] * (dpint)b[17];
    tt += (dpint)a[5] * (dpint)b[16];
    tt += (dpint)a[6] * (dpint)b[15];
    tt += (dpint)a[7] * (dpint)b[14];
    tt += (dpint)a[8] * (dpint)b[13];
    tt += (dpint)a[9] * (dpint)b[12];
    tt += (dpint)a[10] * (dpint)b[11];
    tt += (dpint)a[11] * (dpint)b[10];
    tt += (dpint)a[12] * (dpint)b[9];
    tt += (dpint)a[13] * (dpint)b[8];
    tt += (dpint)a[14] * (dpint)b[7];
    tt += (dpint)a[15] * (dpint)b[6];
    tt += (dpint)a[16] * (dpint)b[5];
    tt += (dpint)a[17] * (dpint)b[4];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
    t += (dpint)a[0] * (dpint)b[3];
    t += (dpint)a[1] * (dpint)b[2];
    t += (dpint)a[2] * (dpint)b[1];
    t += (dpint)a[3] * (dpint)b[0];
    spint v3 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[5] * (dpint)b[17];
    tt += (dpint)a[6] * (dpint)b[16];
    tt += (dpint)a[7] * (dpint)b[15];
    tt += (dpint)a[8] * (dpint)b[14];
    tt += (dpint)a[9] * (dpint)b[13];
    tt += (dpint)a[10] * (dpint)b[12];
    tt += (dpint)a[11] * (dpint)b[11];
    tt += (dpint)a[12] * (dpint)b[10];
    tt += (dpint)a[13] * (dpint)b[9];
    tt += (dpint)a[14] * (dpint)b[8];
    tt += (dpint)a[15] * (dpint)b[7];
    tt += (dpint)a[16] * (dpint)b[6];
    tt += (dpint)a[17] * (dpint)b[5];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
    t += (dpint)a[0] * (dpint)b[4];
    t += (dpint)a[1] * (dpint)b[3];
    t += (dpint)a[2] * (dpint)b[2];
    t += (dpint)a[3] * (dpint)b[1];
    t += (dpint)a[4] * (dpint)b[0];
    spint v4 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[6] * (dpint)b[17];
    tt += (dpint)a[7] * (dpint)b[16];
    tt += (dpint)a[8] * (dpint)b[15];
    tt += (dpint)a[9] * (dpint)b[14];
    tt += (dpint)a[10] * (dpint)b[13];
    tt += (dpint)a[11] * (dpint)b[12];
    tt += (dpint)a[12] * (dpint)b[11];
    tt += (dpint)a[13] * (dpint)b[10];
    tt += (dpint)a[14] * (dpint)b[9];
    tt += (dpint)a[15] * (dpint)b[8];
    tt += (dpint)a[16] * (dpint)b[7];
    tt += (dpint)a[17] * (dpint)b[6];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
    t += (dpint)a[0] * (dpint)b[5];
    t += (dpint)a[1] * (dpint)b[4];
    t += (dpint)a[2] * (dpint)b[3];
    t += (dpint)a[3] * (dpint)b[2];
    t += (dpint)a[4] * (dpint)b[1];
    t += (dpint)a[5] * (dpint)b[0];
    spint v5 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[7] * (dpint)b[17];
    tt += (dpint)a[8] * (dpint)b[16];
    tt += (dpint)a[9] * (dpint)b[15];
    tt += (dpint)a[10] * (dpint)b[14];
    tt += (dpint)a[11] * (dpint)b[13];
    tt += (dpint)a[12] * (dpint)b[12];
    tt += (dpint)a[13] * (dpint)b[11];
    tt += (dpint)a[14] * (dpint)b[10];
    tt += (dpint)a[15] * (dpint)b[9];
    tt += (dpint)a[16] * (dpint)b[8];
    tt += (dpint)a[17] * (dpint)b[7];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
    t += (dpint)a[0] * (dpint)b[6];
    t += (dpint)a[1] * (dpint)b[5];
    t += (dpint)a[2] * (dpint)b[4];
    t += (dpint)a[3] * (dpint)b[3];
    t += (dpint)a[4] * (dpint)b[2];
    t += (dpint)a[5] * (dpint)b[1];
    t += (dpint)a[6] * (dpint)b[0];
    spint v6 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[8] * (dpint)b[17];
    tt += (dpint)a[9] * (dpint)b[16];
    tt += (dpint)a[10] * (dpint)b[15];
    tt += (dpint)a[11] * (dpint)b[14];
    tt += (dpint)a[12] * (dpint)b[13];
    tt += (dpint)a[13] * (dpint)b[12];
    tt += (dpint)a[14] * (dpint)b[11];
    tt += (dpint)a[15] * (dpint)b[10];
    tt += (dpint)a[16] * (dpint)b[9];
    tt += (dpint)a[17] * (dpint)b[8];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
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
    tt = (dpint)a[9] * (dpint)b[17];
    tt += (dpint)a[10] * (dpint)b[16];
    tt += (dpint)a[11] * (dpint)b[15];
    tt += (dpint)a[12] * (dpint)b[14];
    tt += (dpint)a[13] * (dpint)b[13];
    tt += (dpint)a[14] * (dpint)b[12];
    tt += (dpint)a[15] * (dpint)b[11];
    tt += (dpint)a[16] * (dpint)b[10];
    tt += (dpint)a[17] * (dpint)b[9];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
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
    tt = (dpint)a[10] * (dpint)b[17];
    tt += (dpint)a[11] * (dpint)b[16];
    tt += (dpint)a[12] * (dpint)b[15];
    tt += (dpint)a[13] * (dpint)b[14];
    tt += (dpint)a[14] * (dpint)b[13];
    tt += (dpint)a[15] * (dpint)b[12];
    tt += (dpint)a[16] * (dpint)b[11];
    tt += (dpint)a[17] * (dpint)b[10];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
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
    tt = (dpint)a[11] * (dpint)b[17];
    tt += (dpint)a[12] * (dpint)b[16];
    tt += (dpint)a[13] * (dpint)b[15];
    tt += (dpint)a[14] * (dpint)b[14];
    tt += (dpint)a[15] * (dpint)b[13];
    tt += (dpint)a[16] * (dpint)b[12];
    tt += (dpint)a[17] * (dpint)b[11];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
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
    tt = (dpint)a[12] * (dpint)b[17];
    tt += (dpint)a[13] * (dpint)b[16];
    tt += (dpint)a[14] * (dpint)b[15];
    tt += (dpint)a[15] * (dpint)b[14];
    tt += (dpint)a[16] * (dpint)b[13];
    tt += (dpint)a[17] * (dpint)b[12];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
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
    tt = (dpint)a[13] * (dpint)b[17];
    tt += (dpint)a[14] * (dpint)b[16];
    tt += (dpint)a[15] * (dpint)b[15];
    tt += (dpint)a[16] * (dpint)b[14];
    tt += (dpint)a[17] * (dpint)b[13];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
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
    tt = (dpint)a[14] * (dpint)b[17];
    tt += (dpint)a[15] * (dpint)b[16];
    tt += (dpint)a[16] * (dpint)b[15];
    tt += (dpint)a[17] * (dpint)b[14];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
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
    tt = (dpint)a[15] * (dpint)b[17];
    tt += (dpint)a[16] * (dpint)b[16];
    tt += (dpint)a[17] * (dpint)b[15];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
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
    tt = (dpint)a[16] * (dpint)b[17];
    tt += (dpint)a[17] * (dpint)b[16];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
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
    tt = (dpint)a[17] * (dpint)b[17];
    lo = (spint)tt & mask;
    t += (hi + (dpint)lo) * (dpint)0x8e400;
    hi = tt >> 29u;
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
    t += (dpint)hi * (dpint)0x8e400;
    spint v17 = (spint)t & mask;
    t = t >> 29u;
    // second reduction pass

    udpint ut = (udpint)t;
    ut = (ut << 10) + (spint)(v17 >> 19u);
    v17 &= 0x7ffff;
    ut *= 0x239;
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
static void modsqr_PM512_ct(const spint *a, spint *c) {
    udpint t = 0;
    udpint tt;
    udpint t2;
    spint carry;
    spint s;
    spint mask = ((spint)1 << 29u) - (spint)1;
    spint lo;
    udpint hi;
    tt = (udpint)a[1] * (udpint)a[17];
    tt += (udpint)a[2] * (udpint)a[16];
    tt += (udpint)a[3] * (udpint)a[15];
    tt += (udpint)a[4] * (udpint)a[14];
    tt += (udpint)a[5] * (udpint)a[13];
    tt += (udpint)a[6] * (udpint)a[12];
    tt += (udpint)a[7] * (udpint)a[11];
    tt += (udpint)a[8] * (udpint)a[10];
    tt *= 2;
    tt += (udpint)a[9] * (udpint)a[9];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[0];
    t2 += (udpint)lo * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v0 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[2] * (udpint)a[17];
    tt += (udpint)a[3] * (udpint)a[16];
    tt += (udpint)a[4] * (udpint)a[15];
    tt += (udpint)a[5] * (udpint)a[14];
    tt += (udpint)a[6] * (udpint)a[13];
    tt += (udpint)a[7] * (udpint)a[12];
    tt += (udpint)a[8] * (udpint)a[11];
    tt += (udpint)a[9] * (udpint)a[10];
    tt *= 2;
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[1];
    t2 *= 2;
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v1 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[3] * (udpint)a[17];
    tt += (udpint)a[4] * (udpint)a[16];
    tt += (udpint)a[5] * (udpint)a[15];
    tt += (udpint)a[6] * (udpint)a[14];
    tt += (udpint)a[7] * (udpint)a[13];
    tt += (udpint)a[8] * (udpint)a[12];
    tt += (udpint)a[9] * (udpint)a[11];
    tt *= 2;
    tt += (udpint)a[10] * (udpint)a[10];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[2];
    t2 *= 2;
    t2 += (udpint)a[1] * (udpint)a[1];
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v2 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[4] * (udpint)a[17];
    tt += (udpint)a[5] * (udpint)a[16];
    tt += (udpint)a[6] * (udpint)a[15];
    tt += (udpint)a[7] * (udpint)a[14];
    tt += (udpint)a[8] * (udpint)a[13];
    tt += (udpint)a[9] * (udpint)a[12];
    tt += (udpint)a[10] * (udpint)a[11];
    tt *= 2;
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[3];
    t2 += (udpint)a[1] * (udpint)a[2];
    t2 *= 2;
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v3 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[5] * (udpint)a[17];
    tt += (udpint)a[6] * (udpint)a[16];
    tt += (udpint)a[7] * (udpint)a[15];
    tt += (udpint)a[8] * (udpint)a[14];
    tt += (udpint)a[9] * (udpint)a[13];
    tt += (udpint)a[10] * (udpint)a[12];
    tt *= 2;
    tt += (udpint)a[11] * (udpint)a[11];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[4];
    t2 += (udpint)a[1] * (udpint)a[3];
    t2 *= 2;
    t2 += (udpint)a[2] * (udpint)a[2];
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v4 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[6] * (udpint)a[17];
    tt += (udpint)a[7] * (udpint)a[16];
    tt += (udpint)a[8] * (udpint)a[15];
    tt += (udpint)a[9] * (udpint)a[14];
    tt += (udpint)a[10] * (udpint)a[13];
    tt += (udpint)a[11] * (udpint)a[12];
    tt *= 2;
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[5];
    t2 += (udpint)a[1] * (udpint)a[4];
    t2 += (udpint)a[2] * (udpint)a[3];
    t2 *= 2;
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v5 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[7] * (udpint)a[17];
    tt += (udpint)a[8] * (udpint)a[16];
    tt += (udpint)a[9] * (udpint)a[15];
    tt += (udpint)a[10] * (udpint)a[14];
    tt += (udpint)a[11] * (udpint)a[13];
    tt *= 2;
    tt += (udpint)a[12] * (udpint)a[12];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[6];
    t2 += (udpint)a[1] * (udpint)a[5];
    t2 += (udpint)a[2] * (udpint)a[4];
    t2 *= 2;
    t2 += (udpint)a[3] * (udpint)a[3];
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v6 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[8] * (udpint)a[17];
    tt += (udpint)a[9] * (udpint)a[16];
    tt += (udpint)a[10] * (udpint)a[15];
    tt += (udpint)a[11] * (udpint)a[14];
    tt += (udpint)a[12] * (udpint)a[13];
    tt *= 2;
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[7];
    t2 += (udpint)a[1] * (udpint)a[6];
    t2 += (udpint)a[2] * (udpint)a[5];
    t2 += (udpint)a[3] * (udpint)a[4];
    t2 *= 2;
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v7 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[9] * (udpint)a[17];
    tt += (udpint)a[10] * (udpint)a[16];
    tt += (udpint)a[11] * (udpint)a[15];
    tt += (udpint)a[12] * (udpint)a[14];
    tt *= 2;
    tt += (udpint)a[13] * (udpint)a[13];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[8];
    t2 += (udpint)a[1] * (udpint)a[7];
    t2 += (udpint)a[2] * (udpint)a[6];
    t2 += (udpint)a[3] * (udpint)a[5];
    t2 *= 2;
    t2 += (udpint)a[4] * (udpint)a[4];
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v8 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[10] * (udpint)a[17];
    tt += (udpint)a[11] * (udpint)a[16];
    tt += (udpint)a[12] * (udpint)a[15];
    tt += (udpint)a[13] * (udpint)a[14];
    tt *= 2;
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[9];
    t2 += (udpint)a[1] * (udpint)a[8];
    t2 += (udpint)a[2] * (udpint)a[7];
    t2 += (udpint)a[3] * (udpint)a[6];
    t2 += (udpint)a[4] * (udpint)a[5];
    t2 *= 2;
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v9 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[11] * (udpint)a[17];
    tt += (udpint)a[12] * (udpint)a[16];
    tt += (udpint)a[13] * (udpint)a[15];
    tt *= 2;
    tt += (udpint)a[14] * (udpint)a[14];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[10];
    t2 += (udpint)a[1] * (udpint)a[9];
    t2 += (udpint)a[2] * (udpint)a[8];
    t2 += (udpint)a[3] * (udpint)a[7];
    t2 += (udpint)a[4] * (udpint)a[6];
    t2 *= 2;
    t2 += (udpint)a[5] * (udpint)a[5];
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v10 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[12] * (udpint)a[17];
    tt += (udpint)a[13] * (udpint)a[16];
    tt += (udpint)a[14] * (udpint)a[15];
    tt *= 2;
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[11];
    t2 += (udpint)a[1] * (udpint)a[10];
    t2 += (udpint)a[2] * (udpint)a[9];
    t2 += (udpint)a[3] * (udpint)a[8];
    t2 += (udpint)a[4] * (udpint)a[7];
    t2 += (udpint)a[5] * (udpint)a[6];
    t2 *= 2;
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v11 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[13] * (udpint)a[17];
    tt += (udpint)a[14] * (udpint)a[16];
    tt *= 2;
    tt += (udpint)a[15] * (udpint)a[15];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[12];
    t2 += (udpint)a[1] * (udpint)a[11];
    t2 += (udpint)a[2] * (udpint)a[10];
    t2 += (udpint)a[3] * (udpint)a[9];
    t2 += (udpint)a[4] * (udpint)a[8];
    t2 += (udpint)a[5] * (udpint)a[7];
    t2 *= 2;
    t2 += (udpint)a[6] * (udpint)a[6];
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v12 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[14] * (udpint)a[17];
    tt += (udpint)a[15] * (udpint)a[16];
    tt *= 2;
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[13];
    t2 += (udpint)a[1] * (udpint)a[12];
    t2 += (udpint)a[2] * (udpint)a[11];
    t2 += (udpint)a[3] * (udpint)a[10];
    t2 += (udpint)a[4] * (udpint)a[9];
    t2 += (udpint)a[5] * (udpint)a[8];
    t2 += (udpint)a[6] * (udpint)a[7];
    t2 *= 2;
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v13 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[15] * (udpint)a[17];
    tt *= 2;
    tt += (udpint)a[16] * (udpint)a[16];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[14];
    t2 += (udpint)a[1] * (udpint)a[13];
    t2 += (udpint)a[2] * (udpint)a[12];
    t2 += (udpint)a[3] * (udpint)a[11];
    t2 += (udpint)a[4] * (udpint)a[10];
    t2 += (udpint)a[5] * (udpint)a[9];
    t2 += (udpint)a[6] * (udpint)a[8];
    t2 *= 2;
    t2 += (udpint)a[7] * (udpint)a[7];
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v14 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[16] * (udpint)a[17];
    tt *= 2;
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[15];
    t2 += (udpint)a[1] * (udpint)a[14];
    t2 += (udpint)a[2] * (udpint)a[13];
    t2 += (udpint)a[3] * (udpint)a[12];
    t2 += (udpint)a[4] * (udpint)a[11];
    t2 += (udpint)a[5] * (udpint)a[10];
    t2 += (udpint)a[6] * (udpint)a[9];
    t2 += (udpint)a[7] * (udpint)a[8];
    t2 *= 2;
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v15 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[17] * (udpint)a[17];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[16];
    t2 += (udpint)a[1] * (udpint)a[15];
    t2 += (udpint)a[2] * (udpint)a[14];
    t2 += (udpint)a[3] * (udpint)a[13];
    t2 += (udpint)a[4] * (udpint)a[12];
    t2 += (udpint)a[5] * (udpint)a[11];
    t2 += (udpint)a[6] * (udpint)a[10];
    t2 += (udpint)a[7] * (udpint)a[9];
    t2 *= 2;
    t2 += (udpint)a[8] * (udpint)a[8];
    t2 += (hi + (udpint)lo) * (udpint)0x8e400;
    hi = tt >> 29u;
    t += t2;
    spint v16 = (spint)t & mask;
    t = t >> 29u;
    t2 = (udpint)a[0] * (udpint)a[17];
    t2 += (udpint)a[1] * (udpint)a[16];
    t2 += (udpint)a[2] * (udpint)a[15];
    t2 += (udpint)a[3] * (udpint)a[14];
    t2 += (udpint)a[4] * (udpint)a[13];
    t2 += (udpint)a[5] * (udpint)a[12];
    t2 += (udpint)a[6] * (udpint)a[11];
    t2 += (udpint)a[7] * (udpint)a[10];
    t2 += (udpint)a[8] * (udpint)a[9];
    t2 *= 2;
    t += (udpint)hi * (udpint)0x8e400;
    t += t2;
    spint v17 = (spint)t & mask;
    t = t >> 29u;
    // second reduction pass

    udpint ut = (udpint)t;
    ut = (ut << 10) + (spint)(v17 >> 19u);
    v17 &= 0x7ffff;
    ut *= 0x239;
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
static void modcpy_PM512_ct(const spint *a, spint *c) {
    int i;
    for (i = 0; i < 18; i++) {
        c[i] = a[i];
    }
}

// square n times
static void modnsqr_PM512_ct(spint *a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        modsqr_PM512_ct(a, a);
    }
}

// Calculate progenitor - use optimal addition chain
static void modpro_PM512_ct(const spint *w, spint *z) {
    spint x[18];
    spint t0[18];
    spint t1[18];
    spint t2[18];
    modcpy_PM512_ct(w, x);
    modsqr_PM512_ct(x, z);
    modmul_PM512_ct(x, z, z);
    modsqr_PM512_ct(z, z);
    modmul_PM512_ct(x, z, z);
    modcpy_PM512_ct(z, t0);
    modnsqr_PM512_ct(t0, 3);
    modmul_PM512_ct(z, t0, t0);
    modnsqr_PM512_ct(t0, 3);
    modmul_PM512_ct(z, t0, t1);
    modcpy_PM512_ct(t1, t0);
    modnsqr_PM512_ct(t0, 9);
    modmul_PM512_ct(t1, t0, t0);
    modnsqr_PM512_ct(t0, 3);
    modmul_PM512_ct(z, t0, t0);
    modcpy_PM512_ct(t0, t2);
    modnsqr_PM512_ct(t2, 9);
    modmul_PM512_ct(t1, t2, t1);
    modcpy_PM512_ct(t1, t2);
    modnsqr_PM512_ct(t2, 30);
    modmul_PM512_ct(t1, t2, t1);
    modcpy_PM512_ct(t1, t2);
    modnsqr_PM512_ct(t2, 60);
    modmul_PM512_ct(t1, t2, t1);
    modcpy_PM512_ct(t1, t2);
    modnsqr_PM512_ct(t2, 120);
    modmul_PM512_ct(t1, t2, t1);
    modcpy_PM512_ct(t1, t2);
    modnsqr_PM512_ct(t2, 240);
    modmul_PM512_ct(t1, t2, t1);
    modnsqr_PM512_ct(t1, 21);
    modmul_PM512_ct(t0, t1, t0);
    modsqr_PM512_ct(t0, t0);
    modmul_PM512_ct(x, t0, t0);
    modnsqr_PM512_ct(t0, 4);
    modmul_PM512_ct(z, t0, z);
    modnsqr_PM512_ct(z, 4);
    modmul_PM512_ct(x, z, z);
}

// calculate inverse, provide progenitor h if available, NULL if not
static void modinv_PM512_ct(const spint *x, const spint *h, spint *z) {
    spint s[18];
    spint t[18];
    if (h == NULL) {
        modpro_PM512_ct(x, t);
    }
    else {
        modcpy_PM512_ct(h, t);
    }
    modcpy_PM512_ct(x, s);
    modnsqr_PM512_ct(t, 2);
    modmul_PM512_ct(s, t, z);
}

// Convert m to internal form, n=nres(m)
static void nres_PM512_ct(const spint *m, spint *n) {
    int i;
    for (i = 0; i < 18; i++) {
        n[i] = m[i];
    }
}

// Convert n back to normal form, m=redc(n)
static void redc_PM512_ct(const spint *n, spint *m) {
    int i;
    for (i = 0; i < 18; i++) {
        m[i] = n[i];
    }
    (void)modfsb_PM512_ct(m);
}

// is unity?
static int modis1_PM512_ct(const spint *a) {
    int i;
    spint c[18];
    spint c0;
    spint d = 0;
    redc_PM512_ct(a, c);
    for (i = 1; i < 18; i++) {
        d |= c[i];
    }
    c0 = (spint)c[0];
    return ((spint)1 & ((d - (spint)1) >> 29u) & (((c0 ^ (spint)1) - (spint)1) >> 29u));
}

// is zero?
static int modis0_PM512_ct(const spint *a) {
    int i;
    spint c[18];
    spint d = 0;
    redc_PM512_ct(a, c);
    for (i = 0; i < 18; i++) {
        d |= c[i];
    }
    return ((spint)1 & ((d - (spint)1) >> 29u));
}

// set to zero
static void modzer_PM512_ct(spint *a) {
    int i;
    for (i = 0; i < 18; i++) {
        a[i] = 0;
    }
}

// set to one
static void modone_PM512_ct(spint *a) {
    int i;
    a[0] = 1;
    for (i = 1; i < 18; i++) {
        a[i] = 0;
    }
    nres_PM512_ct(a, a);
}

// set to integer
static void modint_PM512_ct(int x, spint *a) {
    int i;
    a[0] = (spint)x;
    for (i = 1; i < 18; i++) {
        a[i] = 0;
    }
    nres_PM512_ct(a, a);
}

// Test for quadratic residue, provide progenitor h if available, NULL if not
static int modqr_PM512_ct(const spint *h, const spint *x) {
    spint r[18];
    if (h == NULL) {
        modpro_PM512_ct(x, r);
        modsqr_PM512_ct(r, r);
    }
    else {
        modsqr_PM512_ct(h, r);
    }
    modmul_PM512_ct(r, x, r);
    return modis1_PM512_ct(r) | modis0_PM512_ct(x);
}

// conditional move g to f if d=1
// strongly recommend inlining be disabled using compiler specific syntax
static void modcmv_PM512_ct(int b, const spint *g, volatile spint *f) {
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
static void modcsw_PM512_ct(int b, volatile spint *g, volatile spint *f) {
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
static void modsqrt_PM512_ct(const spint *x, const spint *h, spint *r) {
    spint s[18];
    spint y[18];
    if (h == NULL) {
        modpro_PM512_ct(x, y);
    }
    else {
        modcpy_PM512_ct(h, y);
    }
    modmul_PM512_ct(y, x, s);
    modcpy_PM512_ct(s, r);
}

// shift left by less than a word
static void modshl_PM512_ct(unsigned int n, spint *a) {
    int i;
    a[17] = ((a[17] << n)) | (a[16] >> (29u - n));
    for (i = 16; i > 0; i--) {
        a[i] = ((a[i] << n) & (spint)0x1fffffff) | (a[i - 1] >> (29u - n));
    }
    a[0] = (a[0] << n) & (spint)0x1fffffff;
}

// shift right by less than a word. Return shifted out part
static int modshr_PM512_ct(unsigned int n, spint *a) {
    int i;
    spint r = a[0] & (((spint)1 << n) - (spint)1);
    for (i = 0; i < 17; i++) {
        a[i] = (a[i] >> n) | ((a[i + 1] << (29u - n)) & (spint)0x1fffffff);
    }
    a[17] = a[17] >> n;
    return r;
}

// set a= 2^r
static void mod2r_PM512_ct(unsigned int r, spint *a) {
    unsigned int n = r / 29u;
    unsigned int m = r % 29u;
    modzer_PM512_ct(a);
    if (r >= 64 * 8) return;
    a[n] = 1;
    a[n] <<= m;
}

// export to byte array
static void modexp_PM512_ct(const spint *a, char *b) {
    int i;
    spint c[18];
    redc_PM512_ct(a, c);
    for (i = 63; i >= 0; i--) {
        b[i] = c[0] & (spint)0xff;
        (void)modshr_PM512_ct(8, c);
    }
}

// import from byte array
// returns 1 if in range, else 0
static int modimp_PM512_ct(const char *b, spint *a) {
    int i, res;
    for (i = 0; i < 18; i++) {
        a[i] = 0;
    }
    for (i = 0; i < 64; i++) {
        modshl_PM512_ct(8, a);
        a[0] += (spint)(unsigned char)b[i];
    }
    res = modfsb_PM512_ct(a);
    nres_PM512_ct(a, a);
    return res;
}

// determine sign
static int modsign_PM512_ct(const spint *a) {
    spint c[18];
    redc_PM512_ct(a, c);
    return c[0] % 2;
}

// return true if equal
static int modcmp_PM512_ct(const spint *a, const spint *b) {
    spint c[18], d[18];
    int i, eq = 1;
    redc_PM512_ct(a, c);
    redc_PM512_ct(b, d);
    for (i = 0; i < 18; i++) {
        eq &= (((c[i] ^ d[i]) - 1) >> 29) & 1;
    }
    return eq;
}
