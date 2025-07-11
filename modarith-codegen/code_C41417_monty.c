
// Automatically generated modular arithmetic C code
// Python Script by Mike Scott (Technology Innovation Institute, UAE, 2025)

#include <stdint.h>
#include <stdio.h>

#define sspint int32_t
#define spint uint32_t
#define udpint uint64_t
#define dpint uint64_t

#define Wordlength_C41417_ct 32
#define Nlimbs_C41417_ct 15
#define Radix_C41417_ct 28
#define Nbits_C41417_ct 414
#define Nbytes_C41417_ct 52

#define MONTGOMERY
#define C41417

// propagate carries
static spint inline prop(spint *n) {
    int i;
    spint mask = ((spint)1 << 28u) - (spint)1;
    sspint carry = (sspint)n[0];
    carry >>= 28u;
    n[0] &= mask;
    for (i = 1; i < 14; i++) {
        carry += (sspint)n[i];
        n[i] = (spint)carry & mask;
        carry >>= 28u;
    }
    n[14] += (spint)carry;
    return -((n[14] >> 1) >> 30u);
}

// propagate carries and add p if negative, propagate carries again
static int inline flatten(spint *n) {
    spint carry = prop(n);
    n[0] += ((spint)0xfffffefu) & carry;
    n[1] -= (spint)1u & carry;
    n[14] += ((spint)0x400000u) & carry;
    (void)prop(n);
    return (int)(carry & 1);
}

// Montgomery final subtract
static int modfsb_C41417_ct(spint *n) {
    n[0] -= (spint)0xfffffefu;
    n[1] += (spint)1u;
    n[14] -= (spint)0x400000u;
    return flatten(n);
}

// Modular addition - reduce less than 2p
static void modadd_C41417_ct(const spint *a, const spint *b, spint *n) {
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
    n[0] -= (spint)0x1fffffdeu;
    n[1] += (spint)2u;
    n[14] -= (spint)0x800000u;
    carry = prop(n);
    n[0] += ((spint)0x1fffffdeu) & carry;
    n[1] -= (spint)2u & carry;
    n[14] += ((spint)0x800000u) & carry;
    (void)prop(n);
}

// Modular subtraction - reduce less than 2p
static void modsub_C41417_ct(const spint *a, const spint *b, spint *n) {
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
    carry = prop(n);
    n[0] += ((spint)0x1fffffdeu) & carry;
    n[1] -= (spint)2u & carry;
    n[14] += ((spint)0x800000u) & carry;
    (void)prop(n);
}

// Modular negation
static void modneg_C41417_ct(const spint *b, spint *n) {
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
    carry = prop(n);
    n[0] += ((spint)0x1fffffdeu) & carry;
    n[1] -= (spint)2u & carry;
    n[14] += ((spint)0x800000u) & carry;
    (void)prop(n);
}

// Overflow limit   = 18446744073709551616
// maximum possible = 1154047460612505631
// Modular multiplication, c=a*b mod 2p
static void modmul_C41417_ct(const spint *a, const spint *b, spint *c) {
    dpint t = 0;
    spint p0 = 0xfffffefu;
    spint q = ((spint)1 << 28u);  // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    spint ndash = 0xf0f0f1u;
    t += (dpint)a[0] * b[0];
    spint v0 = (((spint)t * ndash) & mask);
    t += (dpint)v0 * (dpint)p0;
    t >>= 28;
    t += (dpint)a[0] * b[1];
    t += (dpint)a[1] * b[0];
    t += (dpint)(spint)(q - v0);
    spint v1 = (((spint)t * ndash) & mask);
    t += (dpint)v1 * (dpint)p0;
    t >>= 28;
    t += (dpint)a[0] * b[2];
    t += (dpint)a[1] * b[1];
    t += (dpint)a[2] * b[0];
    spint s = (spint)mask;
    s -= v1;
    t += (dpint)s;
    spint v2 = (((spint)t * ndash) & mask);
    t += (dpint)v2 * (dpint)p0;
    t >>= 28;
    t += (dpint)a[0] * b[3];
    t += (dpint)a[1] * b[2];
    t += (dpint)a[2] * b[1];
    t += (dpint)a[3] * b[0];
    s = (spint)mask;
    s -= v2;
    t += (dpint)s;
    spint v3 = (((spint)t * ndash) & mask);
    t += (dpint)v3 * (dpint)p0;
    t >>= 28;
    t += (dpint)a[0] * b[4];
    t += (dpint)a[1] * b[3];
    t += (dpint)a[2] * b[2];
    t += (dpint)a[3] * b[1];
    t += (dpint)a[4] * b[0];
    s = (spint)mask;
    s -= v3;
    t += (dpint)s;
    spint v4 = (((spint)t * ndash) & mask);
    t += (dpint)v4 * (dpint)p0;
    t >>= 28;
    t += (dpint)a[0] * b[5];
    t += (dpint)a[1] * b[4];
    t += (dpint)a[2] * b[3];
    t += (dpint)a[3] * b[2];
    t += (dpint)a[4] * b[1];
    t += (dpint)a[5] * b[0];
    s = (spint)mask;
    s -= v4;
    t += (dpint)s;
    spint v5 = (((spint)t * ndash) & mask);
    t += (dpint)v5 * (dpint)p0;
    t >>= 28;
    t += (dpint)a[0] * b[6];
    t += (dpint)a[1] * b[5];
    t += (dpint)a[2] * b[4];
    t += (dpint)a[3] * b[3];
    t += (dpint)a[4] * b[2];
    t += (dpint)a[5] * b[1];
    t += (dpint)a[6] * b[0];
    s = (spint)mask;
    s -= v5;
    t += (dpint)s;
    spint v6 = (((spint)t * ndash) & mask);
    t += (dpint)v6 * (dpint)p0;
    t >>= 28;
    t += (dpint)a[0] * b[7];
    t += (dpint)a[1] * b[6];
    t += (dpint)a[2] * b[5];
    t += (dpint)a[3] * b[4];
    t += (dpint)a[4] * b[3];
    t += (dpint)a[5] * b[2];
    t += (dpint)a[6] * b[1];
    t += (dpint)a[7] * b[0];
    s = (spint)mask;
    s -= v6;
    t += (dpint)s;
    spint v7 = (((spint)t * ndash) & mask);
    t += (dpint)v7 * (dpint)p0;
    t >>= 28;
    t += (dpint)a[0] * b[8];
    t += (dpint)a[1] * b[7];
    t += (dpint)a[2] * b[6];
    t += (dpint)a[3] * b[5];
    t += (dpint)a[4] * b[4];
    t += (dpint)a[5] * b[3];
    t += (dpint)a[6] * b[2];
    t += (dpint)a[7] * b[1];
    t += (dpint)a[8] * b[0];
    s = (spint)mask;
    s -= v7;
    t += (dpint)s;
    spint v8 = (((spint)t * ndash) & mask);
    t += (dpint)v8 * (dpint)p0;
    t >>= 28;
    t += (dpint)a[0] * b[9];
    t += (dpint)a[1] * b[8];
    t += (dpint)a[2] * b[7];
    t += (dpint)a[3] * b[6];
    t += (dpint)a[4] * b[5];
    t += (dpint)a[5] * b[4];
    t += (dpint)a[6] * b[3];
    t += (dpint)a[7] * b[2];
    t += (dpint)a[8] * b[1];
    t += (dpint)a[9] * b[0];
    s = (spint)mask;
    s -= v8;
    t += (dpint)s;
    spint v9 = (((spint)t * ndash) & mask);
    t += (dpint)v9 * (dpint)p0;
    t >>= 28;
    t += (dpint)a[0] * b[10];
    t += (dpint)a[1] * b[9];
    t += (dpint)a[2] * b[8];
    t += (dpint)a[3] * b[7];
    t += (dpint)a[4] * b[6];
    t += (dpint)a[5] * b[5];
    t += (dpint)a[6] * b[4];
    t += (dpint)a[7] * b[3];
    t += (dpint)a[8] * b[2];
    t += (dpint)a[9] * b[1];
    t += (dpint)a[10] * b[0];
    s = (spint)mask;
    s -= v9;
    t += (dpint)s;
    spint v10 = (((spint)t * ndash) & mask);
    t += (dpint)v10 * (dpint)p0;
    t >>= 28;
    t += (dpint)a[0] * b[11];
    t += (dpint)a[1] * b[10];
    t += (dpint)a[2] * b[9];
    t += (dpint)a[3] * b[8];
    t += (dpint)a[4] * b[7];
    t += (dpint)a[5] * b[6];
    t += (dpint)a[6] * b[5];
    t += (dpint)a[7] * b[4];
    t += (dpint)a[8] * b[3];
    t += (dpint)a[9] * b[2];
    t += (dpint)a[10] * b[1];
    t += (dpint)a[11] * b[0];
    s = (spint)mask;
    s -= v10;
    t += (dpint)s;
    spint v11 = (((spint)t * ndash) & mask);
    t += (dpint)v11 * (dpint)p0;
    t >>= 28;
    t += (dpint)a[0] * b[12];
    t += (dpint)a[1] * b[11];
    t += (dpint)a[2] * b[10];
    t += (dpint)a[3] * b[9];
    t += (dpint)a[4] * b[8];
    t += (dpint)a[5] * b[7];
    t += (dpint)a[6] * b[6];
    t += (dpint)a[7] * b[5];
    t += (dpint)a[8] * b[4];
    t += (dpint)a[9] * b[3];
    t += (dpint)a[10] * b[2];
    t += (dpint)a[11] * b[1];
    t += (dpint)a[12] * b[0];
    s = (spint)mask;
    s -= v11;
    t += (dpint)s;
    spint v12 = (((spint)t * ndash) & mask);
    t += (dpint)v12 * (dpint)p0;
    t >>= 28;
    t += (dpint)a[0] * b[13];
    t += (dpint)a[1] * b[12];
    t += (dpint)a[2] * b[11];
    t += (dpint)a[3] * b[10];
    t += (dpint)a[4] * b[9];
    t += (dpint)a[5] * b[8];
    t += (dpint)a[6] * b[7];
    t += (dpint)a[7] * b[6];
    t += (dpint)a[8] * b[5];
    t += (dpint)a[9] * b[4];
    t += (dpint)a[10] * b[3];
    t += (dpint)a[11] * b[2];
    t += (dpint)a[12] * b[1];
    t += (dpint)a[13] * b[0];
    s = (spint)mask;
    s -= v12;
    t += (dpint)s;
    spint v13 = (((spint)t * ndash) & mask);
    t += (dpint)v13 * (dpint)p0;
    t >>= 28;
    t += (dpint)a[0] * b[14];
    t += (dpint)a[1] * b[13];
    t += (dpint)a[2] * b[12];
    t += (dpint)a[3] * b[11];
    t += (dpint)a[4] * b[10];
    t += (dpint)a[5] * b[9];
    t += (dpint)a[6] * b[8];
    t += (dpint)a[7] * b[7];
    t += (dpint)a[8] * b[6];
    t += (dpint)a[9] * b[5];
    t += (dpint)a[10] * b[4];
    t += (dpint)a[11] * b[3];
    t += (dpint)a[12] * b[2];
    t += (dpint)a[13] * b[1];
    t += (dpint)a[14] * b[0];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v0 << 22u);
    s -= v13;
    t += (dpint)s;
    spint v14 = (((spint)t * ndash) & mask);
    t += (dpint)v14 * (dpint)p0;
    t >>= 28;
    t += (dpint)a[1] * b[14];
    t += (dpint)a[2] * b[13];
    t += (dpint)a[3] * b[12];
    t += (dpint)a[4] * b[11];
    t += (dpint)a[5] * b[10];
    t += (dpint)a[6] * b[9];
    t += (dpint)a[7] * b[8];
    t += (dpint)a[8] * b[7];
    t += (dpint)a[9] * b[6];
    t += (dpint)a[10] * b[5];
    t += (dpint)a[11] * b[4];
    t += (dpint)a[12] * b[3];
    t += (dpint)a[13] * b[2];
    t += (dpint)a[14] * b[1];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v1 << 22u);
    s -= v14;
    t += (dpint)s;
    c[0] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[2] * b[14];
    t += (dpint)a[3] * b[13];
    t += (dpint)a[4] * b[12];
    t += (dpint)a[5] * b[11];
    t += (dpint)a[6] * b[10];
    t += (dpint)a[7] * b[9];
    t += (dpint)a[8] * b[8];
    t += (dpint)a[9] * b[7];
    t += (dpint)a[10] * b[6];
    t += (dpint)a[11] * b[5];
    t += (dpint)a[12] * b[4];
    t += (dpint)a[13] * b[3];
    t += (dpint)a[14] * b[2];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v2 << 22u);
    t += (dpint)s;
    c[1] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[3] * b[14];
    t += (dpint)a[4] * b[13];
    t += (dpint)a[5] * b[12];
    t += (dpint)a[6] * b[11];
    t += (dpint)a[7] * b[10];
    t += (dpint)a[8] * b[9];
    t += (dpint)a[9] * b[8];
    t += (dpint)a[10] * b[7];
    t += (dpint)a[11] * b[6];
    t += (dpint)a[12] * b[5];
    t += (dpint)a[13] * b[4];
    t += (dpint)a[14] * b[3];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v3 << 22u);
    t += (dpint)s;
    c[2] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[4] * b[14];
    t += (dpint)a[5] * b[13];
    t += (dpint)a[6] * b[12];
    t += (dpint)a[7] * b[11];
    t += (dpint)a[8] * b[10];
    t += (dpint)a[9] * b[9];
    t += (dpint)a[10] * b[8];
    t += (dpint)a[11] * b[7];
    t += (dpint)a[12] * b[6];
    t += (dpint)a[13] * b[5];
    t += (dpint)a[14] * b[4];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v4 << 22u);
    t += (dpint)s;
    c[3] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[5] * b[14];
    t += (dpint)a[6] * b[13];
    t += (dpint)a[7] * b[12];
    t += (dpint)a[8] * b[11];
    t += (dpint)a[9] * b[10];
    t += (dpint)a[10] * b[9];
    t += (dpint)a[11] * b[8];
    t += (dpint)a[12] * b[7];
    t += (dpint)a[13] * b[6];
    t += (dpint)a[14] * b[5];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v5 << 22u);
    t += (dpint)s;
    c[4] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[6] * b[14];
    t += (dpint)a[7] * b[13];
    t += (dpint)a[8] * b[12];
    t += (dpint)a[9] * b[11];
    t += (dpint)a[10] * b[10];
    t += (dpint)a[11] * b[9];
    t += (dpint)a[12] * b[8];
    t += (dpint)a[13] * b[7];
    t += (dpint)a[14] * b[6];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v6 << 22u);
    t += (dpint)s;
    c[5] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[7] * b[14];
    t += (dpint)a[8] * b[13];
    t += (dpint)a[9] * b[12];
    t += (dpint)a[10] * b[11];
    t += (dpint)a[11] * b[10];
    t += (dpint)a[12] * b[9];
    t += (dpint)a[13] * b[8];
    t += (dpint)a[14] * b[7];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v7 << 22u);
    t += (dpint)s;
    c[6] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[8] * b[14];
    t += (dpint)a[9] * b[13];
    t += (dpint)a[10] * b[12];
    t += (dpint)a[11] * b[11];
    t += (dpint)a[12] * b[10];
    t += (dpint)a[13] * b[9];
    t += (dpint)a[14] * b[8];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v8 << 22u);
    t += (dpint)s;
    c[7] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[9] * b[14];
    t += (dpint)a[10] * b[13];
    t += (dpint)a[11] * b[12];
    t += (dpint)a[12] * b[11];
    t += (dpint)a[13] * b[10];
    t += (dpint)a[14] * b[9];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v9 << 22u);
    t += (dpint)s;
    c[8] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[10] * b[14];
    t += (dpint)a[11] * b[13];
    t += (dpint)a[12] * b[12];
    t += (dpint)a[13] * b[11];
    t += (dpint)a[14] * b[10];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v10 << 22u);
    t += (dpint)s;
    c[9] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[11] * b[14];
    t += (dpint)a[12] * b[13];
    t += (dpint)a[13] * b[12];
    t += (dpint)a[14] * b[11];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v11 << 22u);
    t += (dpint)s;
    c[10] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[12] * b[14];
    t += (dpint)a[13] * b[13];
    t += (dpint)a[14] * b[12];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v12 << 22u);
    t += (dpint)s;
    c[11] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[13] * b[14];
    t += (dpint)a[14] * b[13];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v13 << 22u);
    t += (dpint)s;
    c[12] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[14] * b[14];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v14 << 22u);
    t += (dpint)s;
    c[13] = ((spint)t & mask);
    t >>= 28;
    t -= (dpint)1u;
    c[14] = (spint)t;
}

// Modular squaring, c=a*a  mod 2p
static void modsqr_C41417_ct(const spint *a, spint *c) {
    udpint tot;
    udpint t = 0;
    spint p0 = 0xfffffefu;
    spint q = ((spint)1 << 28u);  // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    spint ndash = 0xf0f0f1u;
    tot = (udpint)a[0] * a[0];
    t = tot;
    spint v0 = (((spint)t * ndash) & mask);
    t += (udpint)v0 * p0;
    t >>= 28;
    tot = (udpint)a[0] * a[1];
    tot *= 2;
    t += tot;
    t += (udpint)(spint)(q - v0);
    spint v1 = (((spint)t * ndash) & mask);
    t += (udpint)v1 * p0;
    t >>= 28;
    tot = (udpint)a[0] * a[2];
    tot *= 2;
    tot += (udpint)a[1] * a[1];
    t += tot;
    spint s = (spint)mask;
    s -= v1;
    t += (udpint)s;
    spint v2 = (((spint)t * ndash) & mask);
    t += (udpint)v2 * p0;
    t >>= 28;
    tot = (udpint)a[0] * a[3];
    tot += (udpint)a[1] * a[2];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    s -= v2;
    t += (udpint)s;
    spint v3 = (((spint)t * ndash) & mask);
    t += (udpint)v3 * p0;
    t >>= 28;
    tot = (udpint)a[0] * a[4];
    tot += (udpint)a[1] * a[3];
    tot *= 2;
    tot += (udpint)a[2] * a[2];
    t += tot;
    s = (spint)mask;
    s -= v3;
    t += (udpint)s;
    spint v4 = (((spint)t * ndash) & mask);
    t += (udpint)v4 * p0;
    t >>= 28;
    tot = (udpint)a[0] * a[5];
    tot += (udpint)a[1] * a[4];
    tot += (udpint)a[2] * a[3];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    s -= v4;
    t += (udpint)s;
    spint v5 = (((spint)t * ndash) & mask);
    t += (udpint)v5 * p0;
    t >>= 28;
    tot = (udpint)a[0] * a[6];
    tot += (udpint)a[1] * a[5];
    tot += (udpint)a[2] * a[4];
    tot *= 2;
    tot += (udpint)a[3] * a[3];
    t += tot;
    s = (spint)mask;
    s -= v5;
    t += (udpint)s;
    spint v6 = (((spint)t * ndash) & mask);
    t += (udpint)v6 * p0;
    t >>= 28;
    tot = (udpint)a[0] * a[7];
    tot += (udpint)a[1] * a[6];
    tot += (udpint)a[2] * a[5];
    tot += (udpint)a[3] * a[4];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    s -= v6;
    t += (udpint)s;
    spint v7 = (((spint)t * ndash) & mask);
    t += (udpint)v7 * p0;
    t >>= 28;
    tot = (udpint)a[0] * a[8];
    tot += (udpint)a[1] * a[7];
    tot += (udpint)a[2] * a[6];
    tot += (udpint)a[3] * a[5];
    tot *= 2;
    tot += (udpint)a[4] * a[4];
    t += tot;
    s = (spint)mask;
    s -= v7;
    t += (udpint)s;
    spint v8 = (((spint)t * ndash) & mask);
    t += (udpint)v8 * p0;
    t >>= 28;
    tot = (udpint)a[0] * a[9];
    tot += (udpint)a[1] * a[8];
    tot += (udpint)a[2] * a[7];
    tot += (udpint)a[3] * a[6];
    tot += (udpint)a[4] * a[5];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    s -= v8;
    t += (udpint)s;
    spint v9 = (((spint)t * ndash) & mask);
    t += (udpint)v9 * p0;
    t >>= 28;
    tot = (udpint)a[0] * a[10];
    tot += (udpint)a[1] * a[9];
    tot += (udpint)a[2] * a[8];
    tot += (udpint)a[3] * a[7];
    tot += (udpint)a[4] * a[6];
    tot *= 2;
    tot += (udpint)a[5] * a[5];
    t += tot;
    s = (spint)mask;
    s -= v9;
    t += (udpint)s;
    spint v10 = (((spint)t * ndash) & mask);
    t += (udpint)v10 * p0;
    t >>= 28;
    tot = (udpint)a[0] * a[11];
    tot += (udpint)a[1] * a[10];
    tot += (udpint)a[2] * a[9];
    tot += (udpint)a[3] * a[8];
    tot += (udpint)a[4] * a[7];
    tot += (udpint)a[5] * a[6];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    s -= v10;
    t += (udpint)s;
    spint v11 = (((spint)t * ndash) & mask);
    t += (udpint)v11 * p0;
    t >>= 28;
    tot = (udpint)a[0] * a[12];
    tot += (udpint)a[1] * a[11];
    tot += (udpint)a[2] * a[10];
    tot += (udpint)a[3] * a[9];
    tot += (udpint)a[4] * a[8];
    tot += (udpint)a[5] * a[7];
    tot *= 2;
    tot += (udpint)a[6] * a[6];
    t += tot;
    s = (spint)mask;
    s -= v11;
    t += (udpint)s;
    spint v12 = (((spint)t * ndash) & mask);
    t += (udpint)v12 * p0;
    t >>= 28;
    tot = (udpint)a[0] * a[13];
    tot += (udpint)a[1] * a[12];
    tot += (udpint)a[2] * a[11];
    tot += (udpint)a[3] * a[10];
    tot += (udpint)a[4] * a[9];
    tot += (udpint)a[5] * a[8];
    tot += (udpint)a[6] * a[7];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    s -= v12;
    t += (udpint)s;
    spint v13 = (((spint)t * ndash) & mask);
    t += (udpint)v13 * p0;
    t >>= 28;
    tot = (udpint)a[0] * a[14];
    tot += (udpint)a[1] * a[13];
    tot += (udpint)a[2] * a[12];
    tot += (udpint)a[3] * a[11];
    tot += (udpint)a[4] * a[10];
    tot += (udpint)a[5] * a[9];
    tot += (udpint)a[6] * a[8];
    tot *= 2;
    tot += (udpint)a[7] * a[7];
    t += tot;
    s = (spint)mask;
    t += (udpint)v0 << 22u;
    s -= v13;
    t += (udpint)s;
    spint v14 = (((spint)t * ndash) & mask);
    t += (udpint)v14 * p0;
    t >>= 28;
    tot = (udpint)a[1] * a[14];
    tot += (udpint)a[2] * a[13];
    tot += (udpint)a[3] * a[12];
    tot += (udpint)a[4] * a[11];
    tot += (udpint)a[5] * a[10];
    tot += (udpint)a[6] * a[9];
    tot += (udpint)a[7] * a[8];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v1 << 22u;
    s -= v14;
    t += (udpint)s;
    c[0] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[2] * a[14];
    tot += (udpint)a[3] * a[13];
    tot += (udpint)a[4] * a[12];
    tot += (udpint)a[5] * a[11];
    tot += (udpint)a[6] * a[10];
    tot += (udpint)a[7] * a[9];
    tot *= 2;
    tot += (udpint)a[8] * a[8];
    t += tot;
    s = (spint)mask;
    t += (udpint)v2 << 22u;
    t += (udpint)s;
    c[1] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[3] * a[14];
    tot += (udpint)a[4] * a[13];
    tot += (udpint)a[5] * a[12];
    tot += (udpint)a[6] * a[11];
    tot += (udpint)a[7] * a[10];
    tot += (udpint)a[8] * a[9];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v3 << 22u;
    t += (udpint)s;
    c[2] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[4] * a[14];
    tot += (udpint)a[5] * a[13];
    tot += (udpint)a[6] * a[12];
    tot += (udpint)a[7] * a[11];
    tot += (udpint)a[8] * a[10];
    tot *= 2;
    tot += (udpint)a[9] * a[9];
    t += tot;
    s = (spint)mask;
    t += (udpint)v4 << 22u;
    t += (udpint)s;
    c[3] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[5] * a[14];
    tot += (udpint)a[6] * a[13];
    tot += (udpint)a[7] * a[12];
    tot += (udpint)a[8] * a[11];
    tot += (udpint)a[9] * a[10];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v5 << 22u;
    t += (udpint)s;
    c[4] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[6] * a[14];
    tot += (udpint)a[7] * a[13];
    tot += (udpint)a[8] * a[12];
    tot += (udpint)a[9] * a[11];
    tot *= 2;
    tot += (udpint)a[10] * a[10];
    t += tot;
    s = (spint)mask;
    t += (udpint)v6 << 22u;
    t += (udpint)s;
    c[5] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[7] * a[14];
    tot += (udpint)a[8] * a[13];
    tot += (udpint)a[9] * a[12];
    tot += (udpint)a[10] * a[11];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v7 << 22u;
    t += (udpint)s;
    c[6] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[8] * a[14];
    tot += (udpint)a[9] * a[13];
    tot += (udpint)a[10] * a[12];
    tot *= 2;
    tot += (udpint)a[11] * a[11];
    t += tot;
    s = (spint)mask;
    t += (udpint)v8 << 22u;
    t += (udpint)s;
    c[7] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[9] * a[14];
    tot += (udpint)a[10] * a[13];
    tot += (udpint)a[11] * a[12];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v9 << 22u;
    t += (udpint)s;
    c[8] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[10] * a[14];
    tot += (udpint)a[11] * a[13];
    tot *= 2;
    tot += (udpint)a[12] * a[12];
    t += tot;
    s = (spint)mask;
    t += (udpint)v10 << 22u;
    t += (udpint)s;
    c[9] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[11] * a[14];
    tot += (udpint)a[12] * a[13];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v11 << 22u;
    t += (udpint)s;
    c[10] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[12] * a[14];
    tot *= 2;
    tot += (udpint)a[13] * a[13];
    t += tot;
    s = (spint)mask;
    t += (udpint)v12 << 22u;
    t += (udpint)s;
    c[11] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[13] * a[14];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v13 << 22u;
    t += (udpint)s;
    c[12] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[14] * a[14];
    t += tot;
    s = (spint)mask;
    t += (udpint)v14 << 22u;
    t += (udpint)s;
    c[13] = ((spint)t & mask);
    t >>= 28;
    t -= 1u;
    c[14] = (spint)t;
}

// copy
static void modcpy_C41417_ct(const spint *a, spint *c) {
    int i;
    for (i = 0; i < 15; i++) {
        c[i] = a[i];
    }
}

// square n times
static void modnsqr_C41417_ct(spint *a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        modsqr_C41417_ct(a, a);
    }
}

// Calculate progenitor
static void modpro_C41417_ct(const spint *w, spint *z) {
    spint x[15];
    spint t0[15];
    spint t1[15];
    spint t2[15];
    modcpy_C41417_ct(w, x);
    modsqr_C41417_ct(x, z);
    modmul_C41417_ct(x, z, z);
    modsqr_C41417_ct(z, t0);
    modmul_C41417_ct(x, t0, t0);
    modcpy_C41417_ct(t0, t1);
    modnsqr_C41417_ct(t1, 3);
    modmul_C41417_ct(t0, t1, t0);
    modcpy_C41417_ct(t0, t1);
    modnsqr_C41417_ct(t1, 6);
    modmul_C41417_ct(t0, t1, t0);
    modcpy_C41417_ct(t0, t1);
    modnsqr_C41417_ct(t1, 12);
    modmul_C41417_ct(t0, t1, t1);
    modsqr_C41417_ct(t1, t0);
    modcpy_C41417_ct(t0, t2);
    modnsqr_C41417_ct(t2, 23);
    modmul_C41417_ct(t1, t2, t1);
    modcpy_C41417_ct(t1, t2);
    modnsqr_C41417_ct(t2, 48);
    modmul_C41417_ct(t1, t2, t1);
    modcpy_C41417_ct(t1, t2);
    modnsqr_C41417_ct(t2, 96);
    modmul_C41417_ct(t1, t2, t1);
    modcpy_C41417_ct(t1, t2);
    modnsqr_C41417_ct(t2, 192);
    modmul_C41417_ct(t1, t2, t1);
    modnsqr_C41417_ct(t1, 25);
    modmul_C41417_ct(t0, t1, t0);
    modmul_C41417_ct(x, t0, t0);
    modnsqr_C41417_ct(t0, 3);
    modmul_C41417_ct(z, t0, z);
}

// calculate inverse, provide progenitor h if available
static void modinv_C41417_ct(const spint *x, const spint *h, spint *z) {
    spint s[15];
    spint t[15];
    if (h == NULL) {
        modpro_C41417_ct(x, t);
    }
    else {
        modcpy_C41417_ct(h, t);
    }
    modcpy_C41417_ct(x, s);
    modnsqr_C41417_ct(t, 2);
    modmul_C41417_ct(s, t, z);
}

// Convert m to n-residue form, n=nres(m)
static void nres_C41417_ct(const spint *m, spint *n) {
    const spint c[15] = {0x121000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u};
    modmul_C41417_ct(m, c, n);
}

// Convert n back to normal form, m=redc(n)
static void redc_C41417_ct(const spint *n, spint *m) {
    int i;
    spint c[15];
    c[0] = 1;
    for (i = 1; i < 15; i++) {
        c[i] = 0;
    }
    modmul_C41417_ct(n, c, m);
    (void)modfsb_C41417_ct(m);
}

// is unity?
static int modis1_C41417_ct(const spint *a) {
    int i;
    spint c[15];
    spint c0;
    spint d = 0;
    redc_C41417_ct(a, c);
    for (i = 1; i < 15; i++) {
        d |= c[i];
    }
    c0 = (spint)c[0];
    return ((spint)1 & ((d - (spint)1) >> 28u) & (((c0 ^ (spint)1) - (spint)1) >> 28u));
}

// is zero?
static int modis0_C41417_ct(const spint *a) {
    int i;
    spint c[15];
    spint d = 0;
    redc_C41417_ct(a, c);
    for (i = 0; i < 15; i++) {
        d |= c[i];
    }
    return ((spint)1 & ((d - (spint)1) >> 28u));
}

// set to zero
static void modzer_C41417_ct(spint *a) {
    int i;
    for (i = 0; i < 15; i++) {
        a[i] = 0;
    }
}

// set to one
static void modone_C41417_ct(spint *a) {
    int i;
    a[0] = 1;
    for (i = 1; i < 15; i++) {
        a[i] = 0;
    }
    nres_C41417_ct(a, a);
}

// set to integer
static void modint_C41417_ct(int x, spint *a) {
    int i;
    a[0] = (spint)x;
    for (i = 1; i < 15; i++) {
        a[i] = 0;
    }
    nres_C41417_ct(a, a);
}

// Modular multiplication by an integer, c=a*b mod 2p
static void modmli_C41417_ct(const spint *a, int b, spint *c) {
    spint t[15];
    modint_C41417_ct(b, t);
    modmul_C41417_ct(a, t, c);
}

// Test for quadratic residue
static int modqr_C41417_ct(const spint *h, const spint *x) {
    spint r[15];
    if (h == NULL) {
        modpro_C41417_ct(x, r);
        modsqr_C41417_ct(r, r);
    }
    else {
        modsqr_C41417_ct(h, r);
    }
    modmul_C41417_ct(r, x, r);
    return modis1_C41417_ct(r) | modis0_C41417_ct(x);
}

// conditional move g to f if d=1
// strongly recommend inlining be disabled using compiler specific syntax
static void modcmv_C41417_ct(int b, const spint *g, volatile spint *f) {
    int i;
    spint c0, c1, s, t, aux;
    spint r = 0x5aa5a55au;
    c0 = (~b) & (r + 1);
    c1 = b + r;
    for (i = 0; i < 15; i++) {
        s = g[i];
        t = f[i];
        f[i] = aux = c0 * t + c1 * s;
        f[i] = aux - r * (t + s);
    }
}

// conditional swap g and f if d=1
// strongly recommend inlining be disabled using compiler specific syntax
static void modcsw_C41417_ct(int b, volatile spint *g, volatile spint *f) {
    int i;
    spint c0, c1, s, t, w, aux;
    spint r = 0x5aa5a55au;
    c0 = (~b) & (r + 1);
    c1 = b + r;
    for (i = 0; i < 15; i++) {
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
static void modsqrt_C41417_ct(const spint *x, const spint *h, spint *r) {
    spint s[15];
    spint y[15];
    if (h == NULL) {
        modpro_C41417_ct(x, y);
    }
    else {
        modcpy_C41417_ct(h, y);
    }
    modmul_C41417_ct(y, x, s);
    modcpy_C41417_ct(s, r);
}

// shift left by less than a word
static void modshl_C41417_ct(unsigned int n, spint *a) {
    int i;
    a[14] = ((a[14] << n)) | (a[13] >> (28u - n));
    for (i = 13; i > 0; i--) {
        a[i] = ((a[i] << n) & (spint)0xfffffff) | (a[i - 1] >> (28u - n));
    }
    a[0] = (a[0] << n) & (spint)0xfffffff;
}

// shift right by less than a word. Return shifted out part
static int modshr_C41417_ct(unsigned int n, spint *a) {
    int i;
    spint r = a[0] & (((spint)1 << n) - (spint)1);
    for (i = 0; i < 14; i++) {
        a[i] = (a[i] >> n) | ((a[i + 1] << (28u - n)) & (spint)0xfffffff);
    }
    a[14] = a[14] >> n;
    return r;
}

// set a= 2^r
static void mod2r_C41417_ct(unsigned int r, spint *a) {
    unsigned int n = r / 28u;
    unsigned int m = r % 28u;
    modzer_C41417_ct(a);
    if (r >= 52 * 8) return;
    a[n] = 1;
    a[n] <<= m;
    nres_C41417_ct(a, a);
}

// export to byte array
static void modexp_C41417_ct(const spint *a, char *b) {
    int i;
    spint c[15];
    redc_C41417_ct(a, c);
    for (i = 51; i >= 0; i--) {
        b[i] = c[0] & (spint)0xff;
        (void)modshr_C41417_ct(8, c);
    }
}

// import from byte array
// returns 1 if in range, else 0
static int modimp_C41417_ct(const char *b, spint *a) {
    int i, res;
    for (i = 0; i < 15; i++) {
        a[i] = 0;
    }
    for (i = 0; i < 52; i++) {
        modshl_C41417_ct(8, a);
        a[0] += (spint)(unsigned char)b[i];
    }
    res = modfsb_C41417_ct(a);
    nres_C41417_ct(a, a);
    return res;
}

// determine sign
static int modsign_C41417_ct(const spint *a) {
    spint c[15];
    redc_C41417_ct(a, c);
    return c[0] % 2;
}

// return true if equal
static int modcmp_C41417_ct(const spint *a, const spint *b) {
    spint c[15], d[15];
    int i, eq = 1;
    redc_C41417_ct(a, c);
    redc_C41417_ct(b, d);
    for (i = 0; i < 15; i++) {
        eq &= (((c[i] ^ d[i]) - 1) >> 28) & 1;
    }
    return eq;
}
