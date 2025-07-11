
// Automatically generated modular arithmetic C code
// Python Script by Mike Scott (Technology Innovation Institute, UAE, 2025)

#include <stdint.h>
#include <stdio.h>

#define sspint int32_t
#define spint uint32_t
#define udpint uint64_t
#define dpint uint64_t

#define Wordlength_NIST521_ct 32
#define Nlimbs_NIST521_ct 19
#define Radix_NIST521_ct 28
#define Nbits_NIST521_ct 521
#define Nbytes_NIST521_ct 66

#define MONTGOMERY
#define NIST521

// propagate carries
static spint inline prop(spint *n) {
    int i;
    spint mask = ((spint)1 << 28u) - (spint)1;
    sspint carry = (sspint)n[0];
    carry >>= 28u;
    n[0] &= mask;
    for (i = 1; i < 18; i++) {
        carry += (sspint)n[i];
        n[i] = (spint)carry & mask;
        carry >>= 28u;
    }
    n[18] += (spint)carry;
    return -((n[18] >> 1) >> 30u);
}

// propagate carries and add p if negative, propagate carries again
static int inline flatten(spint *n) {
    spint carry = prop(n);
    n[0] -= (spint)1u & carry;
    n[18] += ((spint)0x20000u) & carry;
    (void)prop(n);
    return (int)(carry & 1);
}

// Montgomery final subtract
static int modfsb_NIST521_ct(spint *n) {
    n[0] += (spint)1u;
    n[18] -= (spint)0x20000u;
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
    n[18] = a[18] + b[18];
    n[0] += (spint)2u;
    n[18] -= (spint)0x40000u;
    carry = prop(n);
    n[0] -= (spint)2u & carry;
    n[18] += ((spint)0x40000u) & carry;
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
    n[18] = a[18] - b[18];
    carry = prop(n);
    n[0] -= (spint)2u & carry;
    n[18] += ((spint)0x40000u) & carry;
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
    n[18] = (spint)0 - b[18];
    carry = prop(n);
    n[0] -= (spint)2u & carry;
    n[18] += ((spint)0x40000u) & carry;
    (void)prop(n);
}

// Overflow limit   = 18446744073709551616
// maximum possible = 1369129529611517971
// Modular multiplication, c=a*b mod 2p
static void modmul_NIST521_ct(const spint *a, const spint *b, spint *c) {
    dpint t = 0;
    spint q = ((spint)1 << 28u);  // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    t += (dpint)a[0] * b[0];
    spint v0 = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[0] * b[1];
    t += (dpint)a[1] * b[0];
    spint v1 = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[0] * b[2];
    t += (dpint)a[1] * b[1];
    t += (dpint)a[2] * b[0];
    spint v2 = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[0] * b[3];
    t += (dpint)a[1] * b[2];
    t += (dpint)a[2] * b[1];
    t += (dpint)a[3] * b[0];
    spint v3 = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[0] * b[4];
    t += (dpint)a[1] * b[3];
    t += (dpint)a[2] * b[2];
    t += (dpint)a[3] * b[1];
    t += (dpint)a[4] * b[0];
    spint v4 = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[0] * b[5];
    t += (dpint)a[1] * b[4];
    t += (dpint)a[2] * b[3];
    t += (dpint)a[3] * b[2];
    t += (dpint)a[4] * b[1];
    t += (dpint)a[5] * b[0];
    spint v5 = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[0] * b[6];
    t += (dpint)a[1] * b[5];
    t += (dpint)a[2] * b[4];
    t += (dpint)a[3] * b[3];
    t += (dpint)a[4] * b[2];
    t += (dpint)a[5] * b[1];
    t += (dpint)a[6] * b[0];
    spint v6 = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[0] * b[7];
    t += (dpint)a[1] * b[6];
    t += (dpint)a[2] * b[5];
    t += (dpint)a[3] * b[4];
    t += (dpint)a[4] * b[3];
    t += (dpint)a[5] * b[2];
    t += (dpint)a[6] * b[1];
    t += (dpint)a[7] * b[0];
    spint v7 = ((spint)t & mask);
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
    spint v8 = ((spint)t & mask);
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
    spint v9 = ((spint)t & mask);
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
    spint v10 = ((spint)t & mask);
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
    spint v11 = ((spint)t & mask);
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
    spint v12 = ((spint)t & mask);
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
    spint v13 = ((spint)t & mask);
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
    spint v14 = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[0] * b[15];
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
    t += (dpint)a[15] * b[0];
    spint v15 = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[0] * b[16];
    t += (dpint)a[1] * b[15];
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
    t += (dpint)a[15] * b[1];
    t += (dpint)a[16] * b[0];
    spint v16 = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[0] * b[17];
    t += (dpint)a[1] * b[16];
    t += (dpint)a[2] * b[15];
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
    t += (dpint)a[15] * b[2];
    t += (dpint)a[16] * b[1];
    t += (dpint)a[17] * b[0];
    spint v17 = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[0] * b[18];
    t += (dpint)a[1] * b[17];
    t += (dpint)a[2] * b[16];
    t += (dpint)a[3] * b[15];
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
    t += (dpint)a[15] * b[3];
    t += (dpint)a[16] * b[2];
    t += (dpint)a[17] * b[1];
    t += (dpint)a[18] * b[0];
    t += (dpint)(udpint)((udpint)v0 << 17u);
    spint v18 = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[1] * b[18];
    t += (dpint)a[2] * b[17];
    t += (dpint)a[3] * b[16];
    t += (dpint)a[4] * b[15];
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
    t += (dpint)a[15] * b[4];
    t += (dpint)a[16] * b[3];
    t += (dpint)a[17] * b[2];
    t += (dpint)a[18] * b[1];
    t += (dpint)(udpint)((udpint)v1 << 17u);
    c[0] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[2] * b[18];
    t += (dpint)a[3] * b[17];
    t += (dpint)a[4] * b[16];
    t += (dpint)a[5] * b[15];
    t += (dpint)a[6] * b[14];
    t += (dpint)a[7] * b[13];
    t += (dpint)a[8] * b[12];
    t += (dpint)a[9] * b[11];
    t += (dpint)a[10] * b[10];
    t += (dpint)a[11] * b[9];
    t += (dpint)a[12] * b[8];
    t += (dpint)a[13] * b[7];
    t += (dpint)a[14] * b[6];
    t += (dpint)a[15] * b[5];
    t += (dpint)a[16] * b[4];
    t += (dpint)a[17] * b[3];
    t += (dpint)a[18] * b[2];
    t += (dpint)(udpint)((udpint)v2 << 17u);
    c[1] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[3] * b[18];
    t += (dpint)a[4] * b[17];
    t += (dpint)a[5] * b[16];
    t += (dpint)a[6] * b[15];
    t += (dpint)a[7] * b[14];
    t += (dpint)a[8] * b[13];
    t += (dpint)a[9] * b[12];
    t += (dpint)a[10] * b[11];
    t += (dpint)a[11] * b[10];
    t += (dpint)a[12] * b[9];
    t += (dpint)a[13] * b[8];
    t += (dpint)a[14] * b[7];
    t += (dpint)a[15] * b[6];
    t += (dpint)a[16] * b[5];
    t += (dpint)a[17] * b[4];
    t += (dpint)a[18] * b[3];
    t += (dpint)(udpint)((udpint)v3 << 17u);
    c[2] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[4] * b[18];
    t += (dpint)a[5] * b[17];
    t += (dpint)a[6] * b[16];
    t += (dpint)a[7] * b[15];
    t += (dpint)a[8] * b[14];
    t += (dpint)a[9] * b[13];
    t += (dpint)a[10] * b[12];
    t += (dpint)a[11] * b[11];
    t += (dpint)a[12] * b[10];
    t += (dpint)a[13] * b[9];
    t += (dpint)a[14] * b[8];
    t += (dpint)a[15] * b[7];
    t += (dpint)a[16] * b[6];
    t += (dpint)a[17] * b[5];
    t += (dpint)a[18] * b[4];
    t += (dpint)(udpint)((udpint)v4 << 17u);
    c[3] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[5] * b[18];
    t += (dpint)a[6] * b[17];
    t += (dpint)a[7] * b[16];
    t += (dpint)a[8] * b[15];
    t += (dpint)a[9] * b[14];
    t += (dpint)a[10] * b[13];
    t += (dpint)a[11] * b[12];
    t += (dpint)a[12] * b[11];
    t += (dpint)a[13] * b[10];
    t += (dpint)a[14] * b[9];
    t += (dpint)a[15] * b[8];
    t += (dpint)a[16] * b[7];
    t += (dpint)a[17] * b[6];
    t += (dpint)a[18] * b[5];
    t += (dpint)(udpint)((udpint)v5 << 17u);
    c[4] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[6] * b[18];
    t += (dpint)a[7] * b[17];
    t += (dpint)a[8] * b[16];
    t += (dpint)a[9] * b[15];
    t += (dpint)a[10] * b[14];
    t += (dpint)a[11] * b[13];
    t += (dpint)a[12] * b[12];
    t += (dpint)a[13] * b[11];
    t += (dpint)a[14] * b[10];
    t += (dpint)a[15] * b[9];
    t += (dpint)a[16] * b[8];
    t += (dpint)a[17] * b[7];
    t += (dpint)a[18] * b[6];
    t += (dpint)(udpint)((udpint)v6 << 17u);
    c[5] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[7] * b[18];
    t += (dpint)a[8] * b[17];
    t += (dpint)a[9] * b[16];
    t += (dpint)a[10] * b[15];
    t += (dpint)a[11] * b[14];
    t += (dpint)a[12] * b[13];
    t += (dpint)a[13] * b[12];
    t += (dpint)a[14] * b[11];
    t += (dpint)a[15] * b[10];
    t += (dpint)a[16] * b[9];
    t += (dpint)a[17] * b[8];
    t += (dpint)a[18] * b[7];
    t += (dpint)(udpint)((udpint)v7 << 17u);
    c[6] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[8] * b[18];
    t += (dpint)a[9] * b[17];
    t += (dpint)a[10] * b[16];
    t += (dpint)a[11] * b[15];
    t += (dpint)a[12] * b[14];
    t += (dpint)a[13] * b[13];
    t += (dpint)a[14] * b[12];
    t += (dpint)a[15] * b[11];
    t += (dpint)a[16] * b[10];
    t += (dpint)a[17] * b[9];
    t += (dpint)a[18] * b[8];
    t += (dpint)(udpint)((udpint)v8 << 17u);
    c[7] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[9] * b[18];
    t += (dpint)a[10] * b[17];
    t += (dpint)a[11] * b[16];
    t += (dpint)a[12] * b[15];
    t += (dpint)a[13] * b[14];
    t += (dpint)a[14] * b[13];
    t += (dpint)a[15] * b[12];
    t += (dpint)a[16] * b[11];
    t += (dpint)a[17] * b[10];
    t += (dpint)a[18] * b[9];
    t += (dpint)(udpint)((udpint)v9 << 17u);
    c[8] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[10] * b[18];
    t += (dpint)a[11] * b[17];
    t += (dpint)a[12] * b[16];
    t += (dpint)a[13] * b[15];
    t += (dpint)a[14] * b[14];
    t += (dpint)a[15] * b[13];
    t += (dpint)a[16] * b[12];
    t += (dpint)a[17] * b[11];
    t += (dpint)a[18] * b[10];
    t += (dpint)(udpint)((udpint)v10 << 17u);
    c[9] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[11] * b[18];
    t += (dpint)a[12] * b[17];
    t += (dpint)a[13] * b[16];
    t += (dpint)a[14] * b[15];
    t += (dpint)a[15] * b[14];
    t += (dpint)a[16] * b[13];
    t += (dpint)a[17] * b[12];
    t += (dpint)a[18] * b[11];
    t += (dpint)(udpint)((udpint)v11 << 17u);
    c[10] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[12] * b[18];
    t += (dpint)a[13] * b[17];
    t += (dpint)a[14] * b[16];
    t += (dpint)a[15] * b[15];
    t += (dpint)a[16] * b[14];
    t += (dpint)a[17] * b[13];
    t += (dpint)a[18] * b[12];
    t += (dpint)(udpint)((udpint)v12 << 17u);
    c[11] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[13] * b[18];
    t += (dpint)a[14] * b[17];
    t += (dpint)a[15] * b[16];
    t += (dpint)a[16] * b[15];
    t += (dpint)a[17] * b[14];
    t += (dpint)a[18] * b[13];
    t += (dpint)(udpint)((udpint)v13 << 17u);
    c[12] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[14] * b[18];
    t += (dpint)a[15] * b[17];
    t += (dpint)a[16] * b[16];
    t += (dpint)a[17] * b[15];
    t += (dpint)a[18] * b[14];
    t += (dpint)(udpint)((udpint)v14 << 17u);
    c[13] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[15] * b[18];
    t += (dpint)a[16] * b[17];
    t += (dpint)a[17] * b[16];
    t += (dpint)a[18] * b[15];
    t += (dpint)(udpint)((udpint)v15 << 17u);
    c[14] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[16] * b[18];
    t += (dpint)a[17] * b[17];
    t += (dpint)a[18] * b[16];
    t += (dpint)(udpint)((udpint)v16 << 17u);
    c[15] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[17] * b[18];
    t += (dpint)a[18] * b[17];
    t += (dpint)(udpint)((udpint)v17 << 17u);
    c[16] = ((spint)t & mask);
    t >>= 28;
    t += (dpint)a[18] * b[18];
    t += (dpint)(udpint)((udpint)v18 << 17u);
    c[17] = ((spint)t & mask);
    t >>= 28;
    c[18] = (spint)t;
}

// Modular squaring, c=a*a  mod 2p
static void modsqr_NIST521_ct(const spint *a, spint *c) {
    udpint tot;
    udpint t = 0;
    spint q = ((spint)1 << 28u);  // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    tot = (udpint)a[0] * a[0];
    t = tot;
    spint v0 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[0] * a[1];
    tot *= 2;
    t += tot;
    spint v1 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[0] * a[2];
    tot *= 2;
    tot += (udpint)a[1] * a[1];
    t += tot;
    spint v2 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[0] * a[3];
    tot += (udpint)a[1] * a[2];
    tot *= 2;
    t += tot;
    spint v3 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[0] * a[4];
    tot += (udpint)a[1] * a[3];
    tot *= 2;
    tot += (udpint)a[2] * a[2];
    t += tot;
    spint v4 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[0] * a[5];
    tot += (udpint)a[1] * a[4];
    tot += (udpint)a[2] * a[3];
    tot *= 2;
    t += tot;
    spint v5 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[0] * a[6];
    tot += (udpint)a[1] * a[5];
    tot += (udpint)a[2] * a[4];
    tot *= 2;
    tot += (udpint)a[3] * a[3];
    t += tot;
    spint v6 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[0] * a[7];
    tot += (udpint)a[1] * a[6];
    tot += (udpint)a[2] * a[5];
    tot += (udpint)a[3] * a[4];
    tot *= 2;
    t += tot;
    spint v7 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[0] * a[8];
    tot += (udpint)a[1] * a[7];
    tot += (udpint)a[2] * a[6];
    tot += (udpint)a[3] * a[5];
    tot *= 2;
    tot += (udpint)a[4] * a[4];
    t += tot;
    spint v8 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[0] * a[9];
    tot += (udpint)a[1] * a[8];
    tot += (udpint)a[2] * a[7];
    tot += (udpint)a[3] * a[6];
    tot += (udpint)a[4] * a[5];
    tot *= 2;
    t += tot;
    spint v9 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[0] * a[10];
    tot += (udpint)a[1] * a[9];
    tot += (udpint)a[2] * a[8];
    tot += (udpint)a[3] * a[7];
    tot += (udpint)a[4] * a[6];
    tot *= 2;
    tot += (udpint)a[5] * a[5];
    t += tot;
    spint v10 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[0] * a[11];
    tot += (udpint)a[1] * a[10];
    tot += (udpint)a[2] * a[9];
    tot += (udpint)a[3] * a[8];
    tot += (udpint)a[4] * a[7];
    tot += (udpint)a[5] * a[6];
    tot *= 2;
    t += tot;
    spint v11 = ((spint)t & mask);
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
    spint v12 = ((spint)t & mask);
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
    spint v13 = ((spint)t & mask);
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
    spint v14 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[0] * a[15];
    tot += (udpint)a[1] * a[14];
    tot += (udpint)a[2] * a[13];
    tot += (udpint)a[3] * a[12];
    tot += (udpint)a[4] * a[11];
    tot += (udpint)a[5] * a[10];
    tot += (udpint)a[6] * a[9];
    tot += (udpint)a[7] * a[8];
    tot *= 2;
    t += tot;
    spint v15 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[0] * a[16];
    tot += (udpint)a[1] * a[15];
    tot += (udpint)a[2] * a[14];
    tot += (udpint)a[3] * a[13];
    tot += (udpint)a[4] * a[12];
    tot += (udpint)a[5] * a[11];
    tot += (udpint)a[6] * a[10];
    tot += (udpint)a[7] * a[9];
    tot *= 2;
    tot += (udpint)a[8] * a[8];
    t += tot;
    spint v16 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[0] * a[17];
    tot += (udpint)a[1] * a[16];
    tot += (udpint)a[2] * a[15];
    tot += (udpint)a[3] * a[14];
    tot += (udpint)a[4] * a[13];
    tot += (udpint)a[5] * a[12];
    tot += (udpint)a[6] * a[11];
    tot += (udpint)a[7] * a[10];
    tot += (udpint)a[8] * a[9];
    tot *= 2;
    t += tot;
    spint v17 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[0] * a[18];
    tot += (udpint)a[1] * a[17];
    tot += (udpint)a[2] * a[16];
    tot += (udpint)a[3] * a[15];
    tot += (udpint)a[4] * a[14];
    tot += (udpint)a[5] * a[13];
    tot += (udpint)a[6] * a[12];
    tot += (udpint)a[7] * a[11];
    tot += (udpint)a[8] * a[10];
    tot *= 2;
    tot += (udpint)a[9] * a[9];
    t += tot;
    t += (udpint)v0 << 17u;
    spint v18 = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[1] * a[18];
    tot += (udpint)a[2] * a[17];
    tot += (udpint)a[3] * a[16];
    tot += (udpint)a[4] * a[15];
    tot += (udpint)a[5] * a[14];
    tot += (udpint)a[6] * a[13];
    tot += (udpint)a[7] * a[12];
    tot += (udpint)a[8] * a[11];
    tot += (udpint)a[9] * a[10];
    tot *= 2;
    t += tot;
    t += (udpint)v1 << 17u;
    c[0] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[2] * a[18];
    tot += (udpint)a[3] * a[17];
    tot += (udpint)a[4] * a[16];
    tot += (udpint)a[5] * a[15];
    tot += (udpint)a[6] * a[14];
    tot += (udpint)a[7] * a[13];
    tot += (udpint)a[8] * a[12];
    tot += (udpint)a[9] * a[11];
    tot *= 2;
    tot += (udpint)a[10] * a[10];
    t += tot;
    t += (udpint)v2 << 17u;
    c[1] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[3] * a[18];
    tot += (udpint)a[4] * a[17];
    tot += (udpint)a[5] * a[16];
    tot += (udpint)a[6] * a[15];
    tot += (udpint)a[7] * a[14];
    tot += (udpint)a[8] * a[13];
    tot += (udpint)a[9] * a[12];
    tot += (udpint)a[10] * a[11];
    tot *= 2;
    t += tot;
    t += (udpint)v3 << 17u;
    c[2] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[4] * a[18];
    tot += (udpint)a[5] * a[17];
    tot += (udpint)a[6] * a[16];
    tot += (udpint)a[7] * a[15];
    tot += (udpint)a[8] * a[14];
    tot += (udpint)a[9] * a[13];
    tot += (udpint)a[10] * a[12];
    tot *= 2;
    tot += (udpint)a[11] * a[11];
    t += tot;
    t += (udpint)v4 << 17u;
    c[3] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[5] * a[18];
    tot += (udpint)a[6] * a[17];
    tot += (udpint)a[7] * a[16];
    tot += (udpint)a[8] * a[15];
    tot += (udpint)a[9] * a[14];
    tot += (udpint)a[10] * a[13];
    tot += (udpint)a[11] * a[12];
    tot *= 2;
    t += tot;
    t += (udpint)v5 << 17u;
    c[4] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[6] * a[18];
    tot += (udpint)a[7] * a[17];
    tot += (udpint)a[8] * a[16];
    tot += (udpint)a[9] * a[15];
    tot += (udpint)a[10] * a[14];
    tot += (udpint)a[11] * a[13];
    tot *= 2;
    tot += (udpint)a[12] * a[12];
    t += tot;
    t += (udpint)v6 << 17u;
    c[5] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[7] * a[18];
    tot += (udpint)a[8] * a[17];
    tot += (udpint)a[9] * a[16];
    tot += (udpint)a[10] * a[15];
    tot += (udpint)a[11] * a[14];
    tot += (udpint)a[12] * a[13];
    tot *= 2;
    t += tot;
    t += (udpint)v7 << 17u;
    c[6] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[8] * a[18];
    tot += (udpint)a[9] * a[17];
    tot += (udpint)a[10] * a[16];
    tot += (udpint)a[11] * a[15];
    tot += (udpint)a[12] * a[14];
    tot *= 2;
    tot += (udpint)a[13] * a[13];
    t += tot;
    t += (udpint)v8 << 17u;
    c[7] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[9] * a[18];
    tot += (udpint)a[10] * a[17];
    tot += (udpint)a[11] * a[16];
    tot += (udpint)a[12] * a[15];
    tot += (udpint)a[13] * a[14];
    tot *= 2;
    t += tot;
    t += (udpint)v9 << 17u;
    c[8] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[10] * a[18];
    tot += (udpint)a[11] * a[17];
    tot += (udpint)a[12] * a[16];
    tot += (udpint)a[13] * a[15];
    tot *= 2;
    tot += (udpint)a[14] * a[14];
    t += tot;
    t += (udpint)v10 << 17u;
    c[9] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[11] * a[18];
    tot += (udpint)a[12] * a[17];
    tot += (udpint)a[13] * a[16];
    tot += (udpint)a[14] * a[15];
    tot *= 2;
    t += tot;
    t += (udpint)v11 << 17u;
    c[10] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[12] * a[18];
    tot += (udpint)a[13] * a[17];
    tot += (udpint)a[14] * a[16];
    tot *= 2;
    tot += (udpint)a[15] * a[15];
    t += tot;
    t += (udpint)v12 << 17u;
    c[11] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[13] * a[18];
    tot += (udpint)a[14] * a[17];
    tot += (udpint)a[15] * a[16];
    tot *= 2;
    t += tot;
    t += (udpint)v13 << 17u;
    c[12] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[14] * a[18];
    tot += (udpint)a[15] * a[17];
    tot *= 2;
    tot += (udpint)a[16] * a[16];
    t += tot;
    t += (udpint)v14 << 17u;
    c[13] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[15] * a[18];
    tot += (udpint)a[16] * a[17];
    tot *= 2;
    t += tot;
    t += (udpint)v15 << 17u;
    c[14] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[16] * a[18];
    tot *= 2;
    tot += (udpint)a[17] * a[17];
    t += tot;
    t += (udpint)v16 << 17u;
    c[15] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[17] * a[18];
    tot *= 2;
    t += tot;
    t += (udpint)v17 << 17u;
    c[16] = ((spint)t & mask);
    t >>= 28;
    tot = (udpint)a[18] * a[18];
    t += tot;
    t += (udpint)v18 << 17u;
    c[17] = ((spint)t & mask);
    t >>= 28;
    c[18] = (spint)t;
}

// copy
static void modcpy_NIST521_ct(const spint *a, spint *c) {
    int i;
    for (i = 0; i < 19; i++) {
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

// Calculate progenitor
static void modpro_NIST521_ct(const spint *w, spint *z) {
    spint x[19];
    spint t0[19];
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

// calculate inverse, provide progenitor h if available
static void modinv_NIST521_ct(const spint *x, const spint *h, spint *z) {
    spint s[19];
    spint t[19];
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

// Convert m to n-residue form, n=nres(m)
static void nres_NIST521_ct(const spint *m, spint *n) {
    const spint c[19] = {0x400000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
                         0x0u,      0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u};
    modmul_NIST521_ct(m, c, n);
}

// Convert n back to normal form, m=redc(n)
static void redc_NIST521_ct(const spint *n, spint *m) {
    int i;
    spint c[19];
    c[0] = 1;
    for (i = 1; i < 19; i++) {
        c[i] = 0;
    }
    modmul_NIST521_ct(n, c, m);
    (void)modfsb_NIST521_ct(m);
}

// is unity?
static int modis1_NIST521_ct(const spint *a) {
    int i;
    spint c[19];
    spint c0;
    spint d = 0;
    redc_NIST521_ct(a, c);
    for (i = 1; i < 19; i++) {
        d |= c[i];
    }
    c0 = (spint)c[0];
    return ((spint)1 & ((d - (spint)1) >> 28u) & (((c0 ^ (spint)1) - (spint)1) >> 28u));
}

// is zero?
static int modis0_NIST521_ct(const spint *a) {
    int i;
    spint c[19];
    spint d = 0;
    redc_NIST521_ct(a, c);
    for (i = 0; i < 19; i++) {
        d |= c[i];
    }
    return ((spint)1 & ((d - (spint)1) >> 28u));
}

// set to zero
static void modzer_NIST521_ct(spint *a) {
    int i;
    for (i = 0; i < 19; i++) {
        a[i] = 0;
    }
}

// set to one
static void modone_NIST521_ct(spint *a) {
    int i;
    a[0] = 1;
    for (i = 1; i < 19; i++) {
        a[i] = 0;
    }
    nres_NIST521_ct(a, a);
}

// set to integer
static void modint_NIST521_ct(int x, spint *a) {
    int i;
    a[0] = (spint)x;
    for (i = 1; i < 19; i++) {
        a[i] = 0;
    }
    nres_NIST521_ct(a, a);
}

// Modular multiplication by an integer, c=a*b mod 2p
static void modmli_NIST521_ct(const spint *a, int b, spint *c) {
    spint t[19];
    modint_NIST521_ct(b, t);
    modmul_NIST521_ct(a, t, c);
}

// Test for quadratic residue
static int modqr_NIST521_ct(const spint *h, const spint *x) {
    spint r[19];
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
    for (i = 0; i < 19; i++) {
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
    for (i = 0; i < 19; i++) {
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
    spint s[19];
    spint y[19];
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
    a[18] = ((a[18] << n)) | (a[17] >> (28u - n));
    for (i = 17; i > 0; i--) {
        a[i] = ((a[i] << n) & (spint)0xfffffff) | (a[i - 1] >> (28u - n));
    }
    a[0] = (a[0] << n) & (spint)0xfffffff;
}

// shift right by less than a word. Return shifted out part
static int modshr_NIST521_ct(unsigned int n, spint *a) {
    int i;
    spint r = a[0] & (((spint)1 << n) - (spint)1);
    for (i = 0; i < 18; i++) {
        a[i] = (a[i] >> n) | ((a[i + 1] << (28u - n)) & (spint)0xfffffff);
    }
    a[18] = a[18] >> n;
    return r;
}

// set a= 2^r
static void mod2r_NIST521_ct(unsigned int r, spint *a) {
    unsigned int n = r / 28u;
    unsigned int m = r % 28u;
    modzer_NIST521_ct(a);
    if (r >= 66 * 8) return;
    a[n] = 1;
    a[n] <<= m;
    nres_NIST521_ct(a, a);
}

// export to byte array
static void modexp_NIST521_ct(const spint *a, char *b) {
    int i;
    spint c[19];
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
    for (i = 0; i < 19; i++) {
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
    spint c[19];
    redc_NIST521_ct(a, c);
    return c[0] % 2;
}

// return true if equal
static int modcmp_NIST521_ct(const spint *a, const spint *b) {
    spint c[19], d[19];
    int i, eq = 1;
    redc_NIST521_ct(a, c);
    redc_NIST521_ct(b, d);
    for (i = 0; i < 19; i++) {
        eq &= (((c[i] ^ d[i]) - 1) >> 28) & 1;
    }
    return eq;
}
