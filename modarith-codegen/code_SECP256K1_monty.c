
// Automatically generated modular arithmetic C code
// Python Script by Mike Scott (Technology Innovation Institute, UAE, 2025)

#include <stdint.h>
#include <stdio.h>

#define sspint int32_t
#define spint uint32_t
#define udpint uint64_t
#define dpint uint64_t

#define Wordlength_SECP256K1_ct 32
#define Nlimbs_SECP256K1_ct 9
#define Radix_SECP256K1_ct 29
#define Nbits_SECP256K1_ct 256
#define Nbytes_SECP256K1_ct 32

#define MONTGOMERY
#define SECP256K1

// propagate carries
static spint inline prop(spint *n) {
    int i;
    spint mask = ((spint)1 << 29u) - (spint)1;
    sspint carry = (sspint)n[0];
    carry >>= 29u;
    n[0] &= mask;
    for (i = 1; i < 8; i++) {
        carry += (sspint)n[i];
        n[i] = (spint)carry & mask;
        carry >>= 29u;
    }
    n[8] += (spint)carry;
    return -((n[8] >> 1) >> 30u);
}

// propagate carries and add p if negative, propagate carries again
static int inline flatten(spint *n) {
    spint carry = prop(n);
    n[0] += ((spint)0x1ffffc2fu) & carry;
    n[1] += ((spint)0x1ffffff7u) & carry;
    n[2] -= (spint)1u & carry;
    n[8] += ((spint)0x1000000u) & carry;
    (void)prop(n);
    return (int)(carry & 1);
}

// Montgomery final subtract
static int modfsb_SECP256K1_ct(spint *n) {
    n[0] -= (spint)0x1ffffc2fu;
    n[1] -= (spint)0x1ffffff7u;
    n[2] += (spint)1u;
    n[8] -= (spint)0x1000000u;
    return flatten(n);
}

// Modular addition - reduce less than 2p
static void modadd_SECP256K1_ct(const spint *a, const spint *b, spint *n) {
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
    n[0] -= (spint)0x3ffff85eu;
    n[1] -= (spint)0x3fffffeeu;
    n[2] += (spint)2u;
    n[8] -= (spint)0x2000000u;
    carry = prop(n);
    n[0] += ((spint)0x3ffff85eu) & carry;
    n[1] += ((spint)0x3fffffeeu) & carry;
    n[2] -= (spint)2u & carry;
    n[8] += ((spint)0x2000000u) & carry;
    (void)prop(n);
}

// Modular subtraction - reduce less than 2p
static void modsub_SECP256K1_ct(const spint *a, const spint *b, spint *n) {
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
    carry = prop(n);
    n[0] += ((spint)0x3ffff85eu) & carry;
    n[1] += ((spint)0x3fffffeeu) & carry;
    n[2] -= (spint)2u & carry;
    n[8] += ((spint)0x2000000u) & carry;
    (void)prop(n);
}

// Modular negation
static void modneg_SECP256K1_ct(const spint *b, spint *n) {
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
    carry = prop(n);
    n[0] += ((spint)0x3ffff85eu) & carry;
    n[1] += ((spint)0x3fffffeeu) & carry;
    n[2] -= (spint)2u & carry;
    n[8] += ((spint)0x2000000u) & carry;
    (void)prop(n);
}

// Overflow limit   = 18446744073709551616
// maximum possible = 3179540831711265762
// Modular multiplication, c=a*b mod 2p
static void modmul_SECP256K1_ct(const spint *a, const spint *b, spint *c) {
    dpint t = 0;
    spint p0 = 0x1ffffc2fu;
    spint p1 = 0x1ffffff7u;
    spint q = ((spint)1 << 29u);  // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    spint ndash = 0x12253531u;
    t += (dpint)a[0] * b[0];
    spint v0 = (((spint)t * ndash) & mask);
    t += (dpint)v0 * (dpint)p0;
    t >>= 29;
    t += (dpint)a[0] * b[1];
    t += (dpint)a[1] * b[0];
    t += (dpint)v0 * (dpint)p1;
    spint v1 = (((spint)t * ndash) & mask);
    t += (dpint)v1 * (dpint)p0;
    t >>= 29;
    t += (dpint)a[0] * b[2];
    t += (dpint)a[1] * b[1];
    t += (dpint)a[2] * b[0];
    t += (dpint)(spint)(q - v0);
    t += (dpint)v1 * (dpint)p1;
    spint v2 = (((spint)t * ndash) & mask);
    t += (dpint)v2 * (dpint)p0;
    t >>= 29;
    t += (dpint)a[0] * b[3];
    t += (dpint)a[1] * b[2];
    t += (dpint)a[2] * b[1];
    t += (dpint)a[3] * b[0];
    spint s = (spint)mask;
    s -= v1;
    t += (dpint)v2 * (dpint)p1;
    t += (dpint)s;
    spint v3 = (((spint)t * ndash) & mask);
    t += (dpint)v3 * (dpint)p0;
    t >>= 29;
    t += (dpint)a[0] * b[4];
    t += (dpint)a[1] * b[3];
    t += (dpint)a[2] * b[2];
    t += (dpint)a[3] * b[1];
    t += (dpint)a[4] * b[0];
    s = (spint)mask;
    s -= v2;
    t += (dpint)v3 * (dpint)p1;
    t += (dpint)s;
    spint v4 = (((spint)t * ndash) & mask);
    t += (dpint)v4 * (dpint)p0;
    t >>= 29;
    t += (dpint)a[0] * b[5];
    t += (dpint)a[1] * b[4];
    t += (dpint)a[2] * b[3];
    t += (dpint)a[3] * b[2];
    t += (dpint)a[4] * b[1];
    t += (dpint)a[5] * b[0];
    s = (spint)mask;
    s -= v3;
    t += (dpint)v4 * (dpint)p1;
    t += (dpint)s;
    spint v5 = (((spint)t * ndash) & mask);
    t += (dpint)v5 * (dpint)p0;
    t >>= 29;
    t += (dpint)a[0] * b[6];
    t += (dpint)a[1] * b[5];
    t += (dpint)a[2] * b[4];
    t += (dpint)a[3] * b[3];
    t += (dpint)a[4] * b[2];
    t += (dpint)a[5] * b[1];
    t += (dpint)a[6] * b[0];
    s = (spint)mask;
    s -= v4;
    t += (dpint)v5 * (dpint)p1;
    t += (dpint)s;
    spint v6 = (((spint)t * ndash) & mask);
    t += (dpint)v6 * (dpint)p0;
    t >>= 29;
    t += (dpint)a[0] * b[7];
    t += (dpint)a[1] * b[6];
    t += (dpint)a[2] * b[5];
    t += (dpint)a[3] * b[4];
    t += (dpint)a[4] * b[3];
    t += (dpint)a[5] * b[2];
    t += (dpint)a[6] * b[1];
    t += (dpint)a[7] * b[0];
    s = (spint)mask;
    s -= v5;
    t += (dpint)v6 * (dpint)p1;
    t += (dpint)s;
    spint v7 = (((spint)t * ndash) & mask);
    t += (dpint)v7 * (dpint)p0;
    t >>= 29;
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
    t += (dpint)(udpint)((udpint)v0 << 24u);
    s -= v6;
    t += (dpint)v7 * (dpint)p1;
    t += (dpint)s;
    spint v8 = (((spint)t * ndash) & mask);
    t += (dpint)v8 * (dpint)p0;
    t >>= 29;
    t += (dpint)a[1] * b[8];
    t += (dpint)a[2] * b[7];
    t += (dpint)a[3] * b[6];
    t += (dpint)a[4] * b[5];
    t += (dpint)a[5] * b[4];
    t += (dpint)a[6] * b[3];
    t += (dpint)a[7] * b[2];
    t += (dpint)a[8] * b[1];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v1 << 24u);
    s -= v7;
    t += (dpint)v8 * (dpint)p1;
    t += (dpint)s;
    c[0] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[2] * b[8];
    t += (dpint)a[3] * b[7];
    t += (dpint)a[4] * b[6];
    t += (dpint)a[5] * b[5];
    t += (dpint)a[6] * b[4];
    t += (dpint)a[7] * b[3];
    t += (dpint)a[8] * b[2];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v2 << 24u);
    s -= v8;
    t += (dpint)s;
    c[1] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[3] * b[8];
    t += (dpint)a[4] * b[7];
    t += (dpint)a[5] * b[6];
    t += (dpint)a[6] * b[5];
    t += (dpint)a[7] * b[4];
    t += (dpint)a[8] * b[3];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v3 << 24u);
    t += (dpint)s;
    c[2] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[4] * b[8];
    t += (dpint)a[5] * b[7];
    t += (dpint)a[6] * b[6];
    t += (dpint)a[7] * b[5];
    t += (dpint)a[8] * b[4];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v4 << 24u);
    t += (dpint)s;
    c[3] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[5] * b[8];
    t += (dpint)a[6] * b[7];
    t += (dpint)a[7] * b[6];
    t += (dpint)a[8] * b[5];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v5 << 24u);
    t += (dpint)s;
    c[4] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[6] * b[8];
    t += (dpint)a[7] * b[7];
    t += (dpint)a[8] * b[6];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v6 << 24u);
    t += (dpint)s;
    c[5] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[7] * b[8];
    t += (dpint)a[8] * b[7];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v7 << 24u);
    t += (dpint)s;
    c[6] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[8] * b[8];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v8 << 24u);
    t += (dpint)s;
    c[7] = ((spint)t & mask);
    t >>= 29;
    t -= (dpint)1u;
    c[8] = (spint)t;
}

// Modular squaring, c=a*a  mod 2p
static void modsqr_SECP256K1_ct(const spint *a, spint *c) {
    udpint tot;
    udpint t = 0;
    spint p0 = 0x1ffffc2fu;
    spint p1 = 0x1ffffff7u;
    spint q = ((spint)1 << 29u);  // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    spint ndash = 0x12253531u;
    tot = (udpint)a[0] * a[0];
    t = tot;
    spint v0 = (((spint)t * ndash) & mask);
    t += (udpint)v0 * p0;
    t >>= 29;
    tot = (udpint)a[0] * a[1];
    tot *= 2;
    t += tot;
    t += (udpint)v0 * p1;
    spint v1 = (((spint)t * ndash) & mask);
    t += (udpint)v1 * p0;
    t >>= 29;
    tot = (udpint)a[0] * a[2];
    tot *= 2;
    tot += (udpint)a[1] * a[1];
    t += tot;
    t += (udpint)(spint)(q - v0);
    t += (udpint)v1 * p1;
    spint v2 = (((spint)t * ndash) & mask);
    t += (udpint)v2 * p0;
    t >>= 29;
    tot = (udpint)a[0] * a[3];
    tot += (udpint)a[1] * a[2];
    tot *= 2;
    t += tot;
    spint s = (spint)mask;
    s -= v1;
    t += (udpint)v2 * p1;
    t += (udpint)s;
    spint v3 = (((spint)t * ndash) & mask);
    t += (udpint)v3 * p0;
    t >>= 29;
    tot = (udpint)a[0] * a[4];
    tot += (udpint)a[1] * a[3];
    tot *= 2;
    tot += (udpint)a[2] * a[2];
    t += tot;
    s = (spint)mask;
    s -= v2;
    t += (udpint)v3 * p1;
    t += (udpint)s;
    spint v4 = (((spint)t * ndash) & mask);
    t += (udpint)v4 * p0;
    t >>= 29;
    tot = (udpint)a[0] * a[5];
    tot += (udpint)a[1] * a[4];
    tot += (udpint)a[2] * a[3];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    s -= v3;
    t += (udpint)v4 * p1;
    t += (udpint)s;
    spint v5 = (((spint)t * ndash) & mask);
    t += (udpint)v5 * p0;
    t >>= 29;
    tot = (udpint)a[0] * a[6];
    tot += (udpint)a[1] * a[5];
    tot += (udpint)a[2] * a[4];
    tot *= 2;
    tot += (udpint)a[3] * a[3];
    t += tot;
    s = (spint)mask;
    s -= v4;
    t += (udpint)v5 * p1;
    t += (udpint)s;
    spint v6 = (((spint)t * ndash) & mask);
    t += (udpint)v6 * p0;
    t >>= 29;
    tot = (udpint)a[0] * a[7];
    tot += (udpint)a[1] * a[6];
    tot += (udpint)a[2] * a[5];
    tot += (udpint)a[3] * a[4];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    s -= v5;
    t += (udpint)v6 * p1;
    t += (udpint)s;
    spint v7 = (((spint)t * ndash) & mask);
    t += (udpint)v7 * p0;
    t >>= 29;
    tot = (udpint)a[0] * a[8];
    tot += (udpint)a[1] * a[7];
    tot += (udpint)a[2] * a[6];
    tot += (udpint)a[3] * a[5];
    tot *= 2;
    tot += (udpint)a[4] * a[4];
    t += tot;
    s = (spint)mask;
    t += (udpint)v0 << 24u;
    s -= v6;
    t += (udpint)v7 * p1;
    t += (udpint)s;
    spint v8 = (((spint)t * ndash) & mask);
    t += (udpint)v8 * p0;
    t >>= 29;
    tot = (udpint)a[1] * a[8];
    tot += (udpint)a[2] * a[7];
    tot += (udpint)a[3] * a[6];
    tot += (udpint)a[4] * a[5];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v1 << 24u;
    s -= v7;
    t += (udpint)v8 * p1;
    t += (udpint)s;
    c[0] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[2] * a[8];
    tot += (udpint)a[3] * a[7];
    tot += (udpint)a[4] * a[6];
    tot *= 2;
    tot += (udpint)a[5] * a[5];
    t += tot;
    s = (spint)mask;
    t += (udpint)v2 << 24u;
    s -= v8;
    t += (udpint)s;
    c[1] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[3] * a[8];
    tot += (udpint)a[4] * a[7];
    tot += (udpint)a[5] * a[6];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v3 << 24u;
    t += (udpint)s;
    c[2] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[4] * a[8];
    tot += (udpint)a[5] * a[7];
    tot *= 2;
    tot += (udpint)a[6] * a[6];
    t += tot;
    s = (spint)mask;
    t += (udpint)v4 << 24u;
    t += (udpint)s;
    c[3] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[5] * a[8];
    tot += (udpint)a[6] * a[7];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v5 << 24u;
    t += (udpint)s;
    c[4] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[6] * a[8];
    tot *= 2;
    tot += (udpint)a[7] * a[7];
    t += tot;
    s = (spint)mask;
    t += (udpint)v6 << 24u;
    t += (udpint)s;
    c[5] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[7] * a[8];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v7 << 24u;
    t += (udpint)s;
    c[6] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[8] * a[8];
    t += tot;
    s = (spint)mask;
    t += (udpint)v8 << 24u;
    t += (udpint)s;
    c[7] = ((spint)t & mask);
    t >>= 29;
    t -= 1u;
    c[8] = (spint)t;
}

// copy
static void modcpy_SECP256K1_ct(const spint *a, spint *c) {
    int i;
    for (i = 0; i < 9; i++) {
        c[i] = a[i];
    }
}

// square n times
static void modnsqr_SECP256K1_ct(spint *a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        modsqr_SECP256K1_ct(a, a);
    }
}

// Calculate progenitor
static void modpro_SECP256K1_ct(const spint *w, spint *z) {
    spint x[9];
    spint t0[9];
    spint t1[9];
    spint t2[9];
    spint t3[9];
    modcpy_SECP256K1_ct(w, x);
    modsqr_SECP256K1_ct(x, z);
    modmul_SECP256K1_ct(x, z, z);
    modcpy_SECP256K1_ct(z, t0);
    modnsqr_SECP256K1_ct(t0, 2);
    modmul_SECP256K1_ct(z, t0, t0);
    modsqr_SECP256K1_ct(t0, t1);
    modmul_SECP256K1_ct(x, t1, t2);
    modcpy_SECP256K1_ct(t2, t1);
    modnsqr_SECP256K1_ct(t1, 2);
    modmul_SECP256K1_ct(z, t1, t1);
    modcpy_SECP256K1_ct(t1, t3);
    modnsqr_SECP256K1_ct(t3, 4);
    modmul_SECP256K1_ct(t0, t3, t0);
    modcpy_SECP256K1_ct(t0, t3);
    modnsqr_SECP256K1_ct(t3, 11);
    modmul_SECP256K1_ct(t0, t3, t0);
    modcpy_SECP256K1_ct(t0, t3);
    modnsqr_SECP256K1_ct(t3, 5);
    modmul_SECP256K1_ct(t2, t3, t2);
    modcpy_SECP256K1_ct(t2, t3);
    modnsqr_SECP256K1_ct(t3, 27);
    modmul_SECP256K1_ct(t2, t3, t2);
    modcpy_SECP256K1_ct(t2, t3);
    modnsqr_SECP256K1_ct(t3, 54);
    modmul_SECP256K1_ct(t2, t3, t2);
    modcpy_SECP256K1_ct(t2, t3);
    modnsqr_SECP256K1_ct(t3, 108);
    modmul_SECP256K1_ct(t2, t3, t2);
    modnsqr_SECP256K1_ct(t2, 7);
    modmul_SECP256K1_ct(t1, t2, t1);
    modnsqr_SECP256K1_ct(t1, 23);
    modmul_SECP256K1_ct(t0, t1, t0);
    modnsqr_SECP256K1_ct(t0, 5);
    modmul_SECP256K1_ct(x, t0, t0);
    modnsqr_SECP256K1_ct(t0, 3);
    modmul_SECP256K1_ct(z, t0, z);
}

// calculate inverse, provide progenitor h if available
static void modinv_SECP256K1_ct(const spint *x, const spint *h, spint *z) {
    spint s[9];
    spint t[9];
    if (h == NULL) {
        modpro_SECP256K1_ct(x, t);
    }
    else {
        modcpy_SECP256K1_ct(h, t);
    }
    modcpy_SECP256K1_ct(x, s);
    modnsqr_SECP256K1_ct(t, 2);
    modmul_SECP256K1_ct(s, t, z);
}

// Convert m to n-residue form, n=nres(m)
static void nres_SECP256K1_ct(const spint *m, spint *n) {
    const spint c[9] = {0x1a428400u, 0xf44001u, 0x10000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u};
    modmul_SECP256K1_ct(m, c, n);
}

// Convert n back to normal form, m=redc(n)
static void redc_SECP256K1_ct(const spint *n, spint *m) {
    int i;
    spint c[9];
    c[0] = 1;
    for (i = 1; i < 9; i++) {
        c[i] = 0;
    }
    modmul_SECP256K1_ct(n, c, m);
    (void)modfsb_SECP256K1_ct(m);
}

// is unity?
static int modis1_SECP256K1_ct(const spint *a) {
    int i;
    spint c[9];
    spint c0;
    spint d = 0;
    redc_SECP256K1_ct(a, c);
    for (i = 1; i < 9; i++) {
        d |= c[i];
    }
    c0 = (spint)c[0];
    return ((spint)1 & ((d - (spint)1) >> 29u) & (((c0 ^ (spint)1) - (spint)1) >> 29u));
}

// is zero?
static int modis0_SECP256K1_ct(const spint *a) {
    int i;
    spint c[9];
    spint d = 0;
    redc_SECP256K1_ct(a, c);
    for (i = 0; i < 9; i++) {
        d |= c[i];
    }
    return ((spint)1 & ((d - (spint)1) >> 29u));
}

// set to zero
static void modzer_SECP256K1_ct(spint *a) {
    int i;
    for (i = 0; i < 9; i++) {
        a[i] = 0;
    }
}

// set to one
static void modone_SECP256K1_ct(spint *a) {
    int i;
    a[0] = 1;
    for (i = 1; i < 9; i++) {
        a[i] = 0;
    }
    nres_SECP256K1_ct(a, a);
}

// set to integer
static void modint_SECP256K1_ct(int x, spint *a) {
    int i;
    a[0] = (spint)x;
    for (i = 1; i < 9; i++) {
        a[i] = 0;
    }
    nres_SECP256K1_ct(a, a);
}

// Modular multiplication by an integer, c=a*b mod 2p
static void modmli_SECP256K1_ct(const spint *a, int b, spint *c) {
    spint t[9];
    modint_SECP256K1_ct(b, t);
    modmul_SECP256K1_ct(a, t, c);
}

// Test for quadratic residue
static int modqr_SECP256K1_ct(const spint *h, const spint *x) {
    spint r[9];
    if (h == NULL) {
        modpro_SECP256K1_ct(x, r);
        modsqr_SECP256K1_ct(r, r);
    }
    else {
        modsqr_SECP256K1_ct(h, r);
    }
    modmul_SECP256K1_ct(r, x, r);
    return modis1_SECP256K1_ct(r) | modis0_SECP256K1_ct(x);
}

// conditional move g to f if d=1
// strongly recommend inlining be disabled using compiler specific syntax
static void modcmv_SECP256K1_ct(int b, const spint *g, volatile spint *f) {
    int i;
    spint c0, c1, s, t, aux;
    spint r = 0x5aa5a55au;
    c0 = (~b) & (r + 1);
    c1 = b + r;
    for (i = 0; i < 9; i++) {
        s = g[i];
        t = f[i];
        f[i] = aux = c0 * t + c1 * s;
        f[i] = aux - r * (t + s);
    }
}

// conditional swap g and f if d=1
// strongly recommend inlining be disabled using compiler specific syntax
static void modcsw_SECP256K1_ct(int b, volatile spint *g, volatile spint *f) {
    int i;
    spint c0, c1, s, t, w, aux;
    spint r = 0x5aa5a55au;
    c0 = (~b) & (r + 1);
    c1 = b + r;
    for (i = 0; i < 9; i++) {
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
static void modsqrt_SECP256K1_ct(const spint *x, const spint *h, spint *r) {
    spint s[9];
    spint y[9];
    if (h == NULL) {
        modpro_SECP256K1_ct(x, y);
    }
    else {
        modcpy_SECP256K1_ct(h, y);
    }
    modmul_SECP256K1_ct(y, x, s);
    modcpy_SECP256K1_ct(s, r);
}

// shift left by less than a word
static void modshl_SECP256K1_ct(unsigned int n, spint *a) {
    int i;
    a[8] = ((a[8] << n)) | (a[7] >> (29u - n));
    for (i = 7; i > 0; i--) {
        a[i] = ((a[i] << n) & (spint)0x1fffffff) | (a[i - 1] >> (29u - n));
    }
    a[0] = (a[0] << n) & (spint)0x1fffffff;
}

// shift right by less than a word. Return shifted out part
static int modshr_SECP256K1_ct(unsigned int n, spint *a) {
    int i;
    spint r = a[0] & (((spint)1 << n) - (spint)1);
    for (i = 0; i < 8; i++) {
        a[i] = (a[i] >> n) | ((a[i + 1] << (29u - n)) & (spint)0x1fffffff);
    }
    a[8] = a[8] >> n;
    return r;
}

// set a= 2^r
static void mod2r_SECP256K1_ct(unsigned int r, spint *a) {
    unsigned int n = r / 29u;
    unsigned int m = r % 29u;
    modzer_SECP256K1_ct(a);
    if (r >= 32 * 8) return;
    a[n] = 1;
    a[n] <<= m;
    nres_SECP256K1_ct(a, a);
}

// export to byte array
static void modexp_SECP256K1_ct(const spint *a, char *b) {
    int i;
    spint c[9];
    redc_SECP256K1_ct(a, c);
    for (i = 31; i >= 0; i--) {
        b[i] = c[0] & (spint)0xff;
        (void)modshr_SECP256K1_ct(8, c);
    }
}

// import from byte array
// returns 1 if in range, else 0
static int modimp_SECP256K1_ct(const char *b, spint *a) {
    int i, res;
    for (i = 0; i < 9; i++) {
        a[i] = 0;
    }
    for (i = 0; i < 32; i++) {
        modshl_SECP256K1_ct(8, a);
        a[0] += (spint)(unsigned char)b[i];
    }
    res = modfsb_SECP256K1_ct(a);
    nres_SECP256K1_ct(a, a);
    return res;
}

// determine sign
static int modsign_SECP256K1_ct(const spint *a) {
    spint c[9];
    redc_SECP256K1_ct(a, c);
    return c[0] % 2;
}

// return true if equal
static int modcmp_SECP256K1_ct(const spint *a, const spint *b) {
    spint c[9], d[9];
    int i, eq = 1;
    redc_SECP256K1_ct(a, c);
    redc_SECP256K1_ct(b, d);
    for (i = 0; i < 9; i++) {
        eq &= (((c[i] ^ d[i]) - 1) >> 29) & 1;
    }
    return eq;
}
