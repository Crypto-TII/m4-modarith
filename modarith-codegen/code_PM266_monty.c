
// Automatically generated modular arithmetic C code
// Python Script by Mike Scott (Technology Innovation Institute, UAE, 2025)

#include <stdint.h>
#include <stdio.h>

#define sspint int32_t
#define spint uint32_t
#define udpint uint64_t
#define dpint uint64_t

#define Wordlength_PM266_ct 32
#define Nlimbs_PM266_ct 10
#define Radix_PM266_ct 27
#define Nbits_PM266_ct 266
#define Nbytes_PM266_ct 34

#define MONTGOMERY
#define PM266

// propagate carries
static spint inline prop(spint *n) {
    int i;
    spint mask = ((spint)1 << 27u) - (spint)1;
    sspint carry = (sspint)n[0];
    carry >>= 27u;
    n[0] &= mask;
    for (i = 1; i < 9; i++) {
        carry += (sspint)n[i];
        n[i] = (spint)carry & mask;
        carry >>= 27u;
    }
    n[9] += (spint)carry;
    return -((n[9] >> 1) >> 30u);
}

// propagate carries and add p if negative, propagate carries again
static int inline flatten(spint *n) {
    spint carry = prop(n);
    n[0] -= ((spint)0x3u) & carry;
    n[9] += ((spint)0x800000u) & carry;
    (void)prop(n);
    return (int)(carry & 1);
}

// Montgomery final subtract
static int modfsb_PM266_ct(spint *n) {
    n[0] += (spint)0x3u;
    n[9] -= (spint)0x800000u;
    return flatten(n);
}

// Modular addition - reduce less than 2p
static void modadd_PM266_ct(const spint *a, const spint *b, spint *n) {
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
    n[0] += (spint)0x6u;
    n[9] -= (spint)0x1000000u;
    carry = prop(n);
    n[0] -= ((spint)0x6u) & carry;
    n[9] += ((spint)0x1000000u) & carry;
    (void)prop(n);
}

// Modular subtraction - reduce less than 2p
static void modsub_PM266_ct(const spint *a, const spint *b, spint *n) {
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
    carry = prop(n);
    n[0] -= ((spint)0x6u) & carry;
    n[9] += ((spint)0x1000000u) & carry;
    (void)prop(n);
}

// Modular negation
static void modneg_PM266_ct(const spint *b, spint *n) {
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
    carry = prop(n);
    n[0] -= ((spint)0x6u) & carry;
    n[9] += ((spint)0x1000000u) & carry;
    (void)prop(n);
}

// Overflow limit   = 18446744073709551616
// maximum possible = 181270020150525959
// Modular multiplication, c=a*b mod 2p
static void modmul_PM266_ct(const spint *a, const spint *b, spint *c) {
    dpint t = 0;
    spint q = ((spint)1 << 27u);  // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    spint ndash = 0x2aaaaabu;
    t += (dpint)a[0] * b[0];
    spint v0 = (((spint)t * ndash) & mask);
    t += (dpint)(spint)((spint)3 * (q - v0));
    t >>= 27;
    t += (dpint)a[0] * b[1];
    t += (dpint)a[1] * b[0];
    t += (dpint)(spint)((spint)3 * mask);
    spint v1 = (((spint)t * ndash) & mask);
    t -= (dpint)(spint)((spint)3 * v1);
    t >>= 27;
    t += (dpint)a[0] * b[2];
    t += (dpint)a[1] * b[1];
    t += (dpint)a[2] * b[0];
    t += (dpint)(spint)((spint)3 * mask);
    spint v2 = (((spint)t * ndash) & mask);
    t -= (dpint)(spint)((spint)3 * v2);
    t >>= 27;
    t += (dpint)a[0] * b[3];
    t += (dpint)a[1] * b[2];
    t += (dpint)a[2] * b[1];
    t += (dpint)a[3] * b[0];
    t += (dpint)(spint)((spint)3 * mask);
    spint v3 = (((spint)t * ndash) & mask);
    t -= (dpint)(spint)((spint)3 * v3);
    t >>= 27;
    t += (dpint)a[0] * b[4];
    t += (dpint)a[1] * b[3];
    t += (dpint)a[2] * b[2];
    t += (dpint)a[3] * b[1];
    t += (dpint)a[4] * b[0];
    t += (dpint)(spint)((spint)3 * mask);
    spint v4 = (((spint)t * ndash) & mask);
    t -= (dpint)(spint)((spint)3 * v4);
    t >>= 27;
    t += (dpint)a[0] * b[5];
    t += (dpint)a[1] * b[4];
    t += (dpint)a[2] * b[3];
    t += (dpint)a[3] * b[2];
    t += (dpint)a[4] * b[1];
    t += (dpint)a[5] * b[0];
    t += (dpint)(spint)((spint)3 * mask);
    spint v5 = (((spint)t * ndash) & mask);
    t -= (dpint)(spint)((spint)3 * v5);
    t >>= 27;
    t += (dpint)a[0] * b[6];
    t += (dpint)a[1] * b[5];
    t += (dpint)a[2] * b[4];
    t += (dpint)a[3] * b[3];
    t += (dpint)a[4] * b[2];
    t += (dpint)a[5] * b[1];
    t += (dpint)a[6] * b[0];
    t += (dpint)(spint)((spint)3 * mask);
    spint v6 = (((spint)t * ndash) & mask);
    t -= (dpint)(spint)((spint)3 * v6);
    t >>= 27;
    t += (dpint)a[0] * b[7];
    t += (dpint)a[1] * b[6];
    t += (dpint)a[2] * b[5];
    t += (dpint)a[3] * b[4];
    t += (dpint)a[4] * b[3];
    t += (dpint)a[5] * b[2];
    t += (dpint)a[6] * b[1];
    t += (dpint)a[7] * b[0];
    t += (dpint)(spint)((spint)3 * mask);
    spint v7 = (((spint)t * ndash) & mask);
    t -= (dpint)(spint)((spint)3 * v7);
    t >>= 27;
    t += (dpint)a[0] * b[8];
    t += (dpint)a[1] * b[7];
    t += (dpint)a[2] * b[6];
    t += (dpint)a[3] * b[5];
    t += (dpint)a[4] * b[4];
    t += (dpint)a[5] * b[3];
    t += (dpint)a[6] * b[2];
    t += (dpint)a[7] * b[1];
    t += (dpint)a[8] * b[0];
    t += (dpint)(spint)((spint)3 * mask);
    spint v8 = (((spint)t * ndash) & mask);
    t -= (dpint)(spint)((spint)3 * v8);
    t >>= 27;
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
    t += (dpint)(spint)((spint)3 * mask);
    t += (dpint)(udpint)((udpint)v0 << 23u);
    spint v9 = (((spint)t * ndash) & mask);
    t -= (dpint)(spint)((spint)3 * v9);
    t >>= 27;
    t += (dpint)a[1] * b[9];
    t += (dpint)a[2] * b[8];
    t += (dpint)a[3] * b[7];
    t += (dpint)a[4] * b[6];
    t += (dpint)a[5] * b[5];
    t += (dpint)a[6] * b[4];
    t += (dpint)a[7] * b[3];
    t += (dpint)a[8] * b[2];
    t += (dpint)a[9] * b[1];
    t += (dpint)(spint)((spint)3 * mask);
    t += (dpint)(udpint)((udpint)v1 << 23u);
    c[0] = ((spint)t & mask);
    t >>= 27;
    t += (dpint)a[2] * b[9];
    t += (dpint)a[3] * b[8];
    t += (dpint)a[4] * b[7];
    t += (dpint)a[5] * b[6];
    t += (dpint)a[6] * b[5];
    t += (dpint)a[7] * b[4];
    t += (dpint)a[8] * b[3];
    t += (dpint)a[9] * b[2];
    t += (dpint)(spint)((spint)3 * mask);
    t += (dpint)(udpint)((udpint)v2 << 23u);
    c[1] = ((spint)t & mask);
    t >>= 27;
    t += (dpint)a[3] * b[9];
    t += (dpint)a[4] * b[8];
    t += (dpint)a[5] * b[7];
    t += (dpint)a[6] * b[6];
    t += (dpint)a[7] * b[5];
    t += (dpint)a[8] * b[4];
    t += (dpint)a[9] * b[3];
    t += (dpint)(spint)((spint)3 * mask);
    t += (dpint)(udpint)((udpint)v3 << 23u);
    c[2] = ((spint)t & mask);
    t >>= 27;
    t += (dpint)a[4] * b[9];
    t += (dpint)a[5] * b[8];
    t += (dpint)a[6] * b[7];
    t += (dpint)a[7] * b[6];
    t += (dpint)a[8] * b[5];
    t += (dpint)a[9] * b[4];
    t += (dpint)(spint)((spint)3 * mask);
    t += (dpint)(udpint)((udpint)v4 << 23u);
    c[3] = ((spint)t & mask);
    t >>= 27;
    t += (dpint)a[5] * b[9];
    t += (dpint)a[6] * b[8];
    t += (dpint)a[7] * b[7];
    t += (dpint)a[8] * b[6];
    t += (dpint)a[9] * b[5];
    t += (dpint)(spint)((spint)3 * mask);
    t += (dpint)(udpint)((udpint)v5 << 23u);
    c[4] = ((spint)t & mask);
    t >>= 27;
    t += (dpint)a[6] * b[9];
    t += (dpint)a[7] * b[8];
    t += (dpint)a[8] * b[7];
    t += (dpint)a[9] * b[6];
    t += (dpint)(spint)((spint)3 * mask);
    t += (dpint)(udpint)((udpint)v6 << 23u);
    c[5] = ((spint)t & mask);
    t >>= 27;
    t += (dpint)a[7] * b[9];
    t += (dpint)a[8] * b[8];
    t += (dpint)a[9] * b[7];
    t += (dpint)(spint)((spint)3 * mask);
    t += (dpint)(udpint)((udpint)v7 << 23u);
    c[6] = ((spint)t & mask);
    t >>= 27;
    t += (dpint)a[8] * b[9];
    t += (dpint)a[9] * b[8];
    t += (dpint)(spint)((spint)3 * mask);
    t += (dpint)(udpint)((udpint)v8 << 23u);
    c[7] = ((spint)t & mask);
    t >>= 27;
    t += (dpint)a[9] * b[9];
    t += (dpint)(spint)((spint)3 * mask);
    t += (dpint)(udpint)((udpint)v9 << 23u);
    c[8] = ((spint)t & mask);
    t >>= 27;
    t -= (dpint)3;
    c[9] = (spint)t;
}

// Modular squaring, c=a*a  mod 2p
static void modsqr_PM266_ct(const spint *a, spint *c) {
    udpint tot;
    udpint t = 0;
    spint q = ((spint)1 << 27u);  // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    spint ndash = 0x2aaaaabu;
    tot = (udpint)a[0] * a[0];
    t = tot;
    spint v0 = (((spint)t * ndash) & mask);
    t += (udpint)(spint)((spint)3 * (q - v0));
    t >>= 27;
    tot = (udpint)a[0] * a[1];
    tot *= 2;
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    spint v1 = (((spint)t * ndash) & mask);
    t -= (udpint)(spint)((spint)3 * v1);
    t >>= 27;
    tot = (udpint)a[0] * a[2];
    tot *= 2;
    tot += (udpint)a[1] * a[1];
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    spint v2 = (((spint)t * ndash) & mask);
    t -= (udpint)(spint)((spint)3 * v2);
    t >>= 27;
    tot = (udpint)a[0] * a[3];
    tot += (udpint)a[1] * a[2];
    tot *= 2;
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    spint v3 = (((spint)t * ndash) & mask);
    t -= (udpint)(spint)((spint)3 * v3);
    t >>= 27;
    tot = (udpint)a[0] * a[4];
    tot += (udpint)a[1] * a[3];
    tot *= 2;
    tot += (udpint)a[2] * a[2];
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    spint v4 = (((spint)t * ndash) & mask);
    t -= (udpint)(spint)((spint)3 * v4);
    t >>= 27;
    tot = (udpint)a[0] * a[5];
    tot += (udpint)a[1] * a[4];
    tot += (udpint)a[2] * a[3];
    tot *= 2;
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    spint v5 = (((spint)t * ndash) & mask);
    t -= (udpint)(spint)((spint)3 * v5);
    t >>= 27;
    tot = (udpint)a[0] * a[6];
    tot += (udpint)a[1] * a[5];
    tot += (udpint)a[2] * a[4];
    tot *= 2;
    tot += (udpint)a[3] * a[3];
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    spint v6 = (((spint)t * ndash) & mask);
    t -= (udpint)(spint)((spint)3 * v6);
    t >>= 27;
    tot = (udpint)a[0] * a[7];
    tot += (udpint)a[1] * a[6];
    tot += (udpint)a[2] * a[5];
    tot += (udpint)a[3] * a[4];
    tot *= 2;
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    spint v7 = (((spint)t * ndash) & mask);
    t -= (udpint)(spint)((spint)3 * v7);
    t >>= 27;
    tot = (udpint)a[0] * a[8];
    tot += (udpint)a[1] * a[7];
    tot += (udpint)a[2] * a[6];
    tot += (udpint)a[3] * a[5];
    tot *= 2;
    tot += (udpint)a[4] * a[4];
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    spint v8 = (((spint)t * ndash) & mask);
    t -= (udpint)(spint)((spint)3 * v8);
    t >>= 27;
    tot = (udpint)a[0] * a[9];
    tot += (udpint)a[1] * a[8];
    tot += (udpint)a[2] * a[7];
    tot += (udpint)a[3] * a[6];
    tot += (udpint)a[4] * a[5];
    tot *= 2;
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    t += (udpint)v0 << 23u;
    spint v9 = (((spint)t * ndash) & mask);
    t -= (udpint)(spint)((spint)3 * v9);
    t >>= 27;
    tot = (udpint)a[1] * a[9];
    tot += (udpint)a[2] * a[8];
    tot += (udpint)a[3] * a[7];
    tot += (udpint)a[4] * a[6];
    tot *= 2;
    tot += (udpint)a[5] * a[5];
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    t += (udpint)v1 << 23u;
    c[0] = ((spint)t & mask);
    t >>= 27;
    tot = (udpint)a[2] * a[9];
    tot += (udpint)a[3] * a[8];
    tot += (udpint)a[4] * a[7];
    tot += (udpint)a[5] * a[6];
    tot *= 2;
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    t += (udpint)v2 << 23u;
    c[1] = ((spint)t & mask);
    t >>= 27;
    tot = (udpint)a[3] * a[9];
    tot += (udpint)a[4] * a[8];
    tot += (udpint)a[5] * a[7];
    tot *= 2;
    tot += (udpint)a[6] * a[6];
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    t += (udpint)v3 << 23u;
    c[2] = ((spint)t & mask);
    t >>= 27;
    tot = (udpint)a[4] * a[9];
    tot += (udpint)a[5] * a[8];
    tot += (udpint)a[6] * a[7];
    tot *= 2;
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    t += (udpint)v4 << 23u;
    c[3] = ((spint)t & mask);
    t >>= 27;
    tot = (udpint)a[5] * a[9];
    tot += (udpint)a[6] * a[8];
    tot *= 2;
    tot += (udpint)a[7] * a[7];
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    t += (udpint)v5 << 23u;
    c[4] = ((spint)t & mask);
    t >>= 27;
    tot = (udpint)a[6] * a[9];
    tot += (udpint)a[7] * a[8];
    tot *= 2;
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    t += (udpint)v6 << 23u;
    c[5] = ((spint)t & mask);
    t >>= 27;
    tot = (udpint)a[7] * a[9];
    tot *= 2;
    tot += (udpint)a[8] * a[8];
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    t += (udpint)v7 << 23u;
    c[6] = ((spint)t & mask);
    t >>= 27;
    tot = (udpint)a[8] * a[9];
    tot *= 2;
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    t += (udpint)v8 << 23u;
    c[7] = ((spint)t & mask);
    t >>= 27;
    tot = (udpint)a[9] * a[9];
    t += tot;
    t += (udpint)(spint)((spint)3 * mask);
    t += (udpint)v9 << 23u;
    c[8] = ((spint)t & mask);
    t >>= 27;
    t -= (udpint)3;
    c[9] = (spint)t;
}

// copy
static void modcpy_PM266_ct(const spint *a, spint *c) {
    int i;
    for (i = 0; i < 10; i++) {
        c[i] = a[i];
    }
}

// square n times
static void modnsqr_PM266_ct(spint *a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        modsqr_PM266_ct(a, a);
    }
}

// Calculate progenitor
static void modpro_PM266_ct(const spint *w, spint *z) {
    spint x[10];
    spint t0[10];
    modcpy_PM266_ct(w, x);
    modsqr_PM266_ct(x, z);
    modmul_PM266_ct(x, z, z);
    modcpy_PM266_ct(z, t0);
    modnsqr_PM266_ct(t0, 2);
    modmul_PM266_ct(z, t0, z);
    modcpy_PM266_ct(z, t0);
    modnsqr_PM266_ct(t0, 4);
    modmul_PM266_ct(z, t0, z);
    modcpy_PM266_ct(z, t0);
    modnsqr_PM266_ct(t0, 8);
    modmul_PM266_ct(z, t0, z);
    modcpy_PM266_ct(z, t0);
    modnsqr_PM266_ct(t0, 16);
    modmul_PM266_ct(z, t0, z);
    modsqr_PM266_ct(z, t0);
    modmul_PM266_ct(x, t0, t0);
    modnsqr_PM266_ct(t0, 32);
    modmul_PM266_ct(z, t0, z);
    modsqr_PM266_ct(z, t0);
    modmul_PM266_ct(x, t0, t0);
    modnsqr_PM266_ct(t0, 65);
    modmul_PM266_ct(z, t0, z);
    modsqr_PM266_ct(z, t0);
    modmul_PM266_ct(x, t0, t0);
    modnsqr_PM266_ct(t0, 131);
    modmul_PM266_ct(z, t0, z);
}

// calculate inverse, provide progenitor h if available
static void modinv_PM266_ct(const spint *x, const spint *h, spint *z) {
    int i;
    spint s[10];
    spint t[10];
    if (h == NULL) {
        modpro_PM266_ct(x, t);
    }
    else {
        modcpy_PM266_ct(h, t);
    }
    modcpy_PM266_ct(x, s);
    for (i = 0; i < (2 - 1); i++) {
        modsqr_PM266_ct(s, s);
        modmul_PM266_ct(s, x, s);
    }
    modnsqr_PM266_ct(t, 3);
    modmul_PM266_ct(s, t, z);
}

// Convert m to n-residue form, n=nres(m)
static void nres_PM266_ct(const spint *m, spint *n) {
    const spint c[10] = {0x900u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u};
    modmul_PM266_ct(m, c, n);
}

// Convert n back to normal form, m=redc(n)
static void redc_PM266_ct(const spint *n, spint *m) {
    int i;
    spint c[10];
    c[0] = 1;
    for (i = 1; i < 10; i++) {
        c[i] = 0;
    }
    modmul_PM266_ct(n, c, m);
    (void)modfsb_PM266_ct(m);
}

// is unity?
static int modis1_PM266_ct(const spint *a) {
    int i;
    spint c[10];
    spint c0;
    spint d = 0;
    redc_PM266_ct(a, c);
    for (i = 1; i < 10; i++) {
        d |= c[i];
    }
    c0 = (spint)c[0];
    return ((spint)1 & ((d - (spint)1) >> 27u) & (((c0 ^ (spint)1) - (spint)1) >> 27u));
}

// is zero?
static int modis0_PM266_ct(const spint *a) {
    int i;
    spint c[10];
    spint d = 0;
    redc_PM266_ct(a, c);
    for (i = 0; i < 10; i++) {
        d |= c[i];
    }
    return ((spint)1 & ((d - (spint)1) >> 27u));
}

// set to zero
static void modzer_PM266_ct(spint *a) {
    int i;
    for (i = 0; i < 10; i++) {
        a[i] = 0;
    }
}

// set to one
static void modone_PM266_ct(spint *a) {
    int i;
    a[0] = 1;
    for (i = 1; i < 10; i++) {
        a[i] = 0;
    }
    nres_PM266_ct(a, a);
}

// set to integer
static void modint_PM266_ct(int x, spint *a) {
    int i;
    a[0] = (spint)x;
    for (i = 1; i < 10; i++) {
        a[i] = 0;
    }
    nres_PM266_ct(a, a);
}

// Modular multiplication by an integer, c=a*b mod 2p
static void modmli_PM266_ct(const spint *a, int b, spint *c) {
    spint t[10];
    modint_PM266_ct(b, t);
    modmul_PM266_ct(a, t, c);
}

// Test for quadratic residue
static int modqr_PM266_ct(const spint *h, const spint *x) {
    spint r[10];
    if (h == NULL) {
        modpro_PM266_ct(x, r);
        modsqr_PM266_ct(r, r);
    }
    else {
        modsqr_PM266_ct(h, r);
    }
    modmul_PM266_ct(r, x, r);
    modnsqr_PM266_ct(r, 1);
    return modis1_PM266_ct(r) | modis0_PM266_ct(x);
}

// conditional move g to f if d=1
// strongly recommend inlining be disabled using compiler specific syntax
static void modcmv_PM266_ct(int b, const spint *g, volatile spint *f) {
    int i;
    spint c0, c1, s, t, aux;
    spint r = 0x5aa5a55au;
    c0 = (~b) & (r + 1);
    c1 = b + r;
    for (i = 0; i < 10; i++) {
        s = g[i];
        t = f[i];
        f[i] = aux = c0 * t + c1 * s;
        f[i] = aux - r * (t + s);
    }
}

// conditional swap g and f if d=1
// strongly recommend inlining be disabled using compiler specific syntax
static void modcsw_PM266_ct(int b, volatile spint *g, volatile spint *f) {
    int i;
    spint c0, c1, s, t, w, aux;
    spint r = 0x5aa5a55au;
    c0 = (~b) & (r + 1);
    c1 = b + r;
    for (i = 0; i < 10; i++) {
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
static void modsqrt_PM266_ct(const spint *x, const spint *h, spint *r) {
    int k;
    spint t[10];
    spint b[10];
    spint v[10];
    spint z[10] = {0x1d89b35u, 0x4b7561fu, 0x74db88du, 0x540cef3u, 0x39587a9u,
                   0x13ec72cu, 0xd16a3eu,  0x74162d7u, 0x2e254efu, 0x1c4d32u};
    spint s[10];
    spint y[10];
    if (h == NULL) {
        modpro_PM266_ct(x, y);
    }
    else {
        modcpy_PM266_ct(h, y);
    }
    modmul_PM266_ct(y, x, s);
    modmul_PM266_ct(s, y, t);
    nres_PM266_ct(z, z);
    for (k = 2; k > 1; k--) {
        modcpy_PM266_ct(t, b);
        modnsqr_PM266_ct(b, k - 2);
        int d = 1 - modis1_PM266_ct(b);
        modmul_PM266_ct(s, z, v);
        modcmv_PM266_ct(d, v, s);
        modsqr_PM266_ct(z, z);
        modmul_PM266_ct(t, z, v);
        modcmv_PM266_ct(d, v, t);
    }
    modcpy_PM266_ct(s, r);
}

// shift left by less than a word
static void modshl_PM266_ct(unsigned int n, spint *a) {
    int i;
    a[9] = ((a[9] << n)) | (a[8] >> (27u - n));
    for (i = 8; i > 0; i--) {
        a[i] = ((a[i] << n) & (spint)0x7ffffff) | (a[i - 1] >> (27u - n));
    }
    a[0] = (a[0] << n) & (spint)0x7ffffff;
}

// shift right by less than a word. Return shifted out part
static int modshr_PM266_ct(unsigned int n, spint *a) {
    int i;
    spint r = a[0] & (((spint)1 << n) - (spint)1);
    for (i = 0; i < 9; i++) {
        a[i] = (a[i] >> n) | ((a[i + 1] << (27u - n)) & (spint)0x7ffffff);
    }
    a[9] = a[9] >> n;
    return r;
}

// set a= 2^r
static void mod2r_PM266_ct(unsigned int r, spint *a) {
    unsigned int n = r / 27u;
    unsigned int m = r % 27u;
    modzer_PM266_ct(a);
    if (r >= 34 * 8) return;
    a[n] = 1;
    a[n] <<= m;
    nres_PM266_ct(a, a);
}

// export to byte array
static void modexp_PM266_ct(const spint *a, char *b) {
    int i;
    spint c[10];
    redc_PM266_ct(a, c);
    for (i = 33; i >= 0; i--) {
        b[i] = c[0] & (spint)0xff;
        (void)modshr_PM266_ct(8, c);
    }
}

// import from byte array
// returns 1 if in range, else 0
static int modimp_PM266_ct(const char *b, spint *a) {
    int i, res;
    for (i = 0; i < 10; i++) {
        a[i] = 0;
    }
    for (i = 0; i < 34; i++) {
        modshl_PM266_ct(8, a);
        a[0] += (spint)(unsigned char)b[i];
    }
    res = modfsb_PM266_ct(a);
    nres_PM266_ct(a, a);
    return res;
}

// determine sign
static int modsign_PM266_ct(const spint *a) {
    spint c[10];
    redc_PM266_ct(a, c);
    return c[0] % 2;
}

// return true if equal
static int modcmp_PM266_ct(const spint *a, const spint *b) {
    spint c[10], d[10];
    int i, eq = 1;
    redc_PM266_ct(a, c);
    redc_PM266_ct(b, d);
    for (i = 0; i < 10; i++) {
        eq &= (((c[i] ^ d[i]) - 1) >> 27) & 1;
    }
    return eq;
}
