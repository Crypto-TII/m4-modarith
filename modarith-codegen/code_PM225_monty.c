
// Automatically generated modular arithmetic C code
// Python Script by Mike Scott (Technology Innovation Institute, UAE, 2025)

#include <stdint.h>
#include <stdio.h>

#define sspint int32_t
#define spint uint32_t
#define udpint uint64_t
#define dpint uint64_t

#define Wordlength_PM225_ct 32
#define Nlimbs_PM225_ct 8
#define Radix_PM225_ct 29
#define Nbits_PM225_ct 225
#define Nbytes_PM225_ct 29

#define MONTGOMERY
#define PM225

// propagate carries
static spint inline prop(spint *n) {
    int i;
    spint mask = ((spint)1 << 29u) - (spint)1;
    sspint carry = (sspint)n[0];
    carry >>= 29u;
    n[0] &= mask;
    for (i = 1; i < 7; i++) {
        carry += (sspint)n[i];
        n[i] = (spint)carry & mask;
        carry >>= 29u;
    }
    n[7] += (spint)carry;
    return -((n[7] >> 1) >> 30u);
}

// propagate carries and add p if negative, propagate carries again
static int inline flatten(spint *n) {
    spint carry = prop(n);
    n[0] += ((spint)0x1fffffcfu) & carry;
    n[1] -= (spint)1u & carry;
    n[7] += ((spint)0x400000u) & carry;
    (void)prop(n);
    return (int)(carry & 1);
}

// Montgomery final subtract
static int modfsb_PM225_ct(spint *n) {
    n[0] -= (spint)0x1fffffcfu;
    n[1] += (spint)1u;
    n[7] -= (spint)0x400000u;
    return flatten(n);
}

// Modular addition - reduce less than 2p
static void modadd_PM225_ct(const spint *a, const spint *b, spint *n) {
    spint carry;
    n[0] = a[0] + b[0];
    n[1] = a[1] + b[1];
    n[2] = a[2] + b[2];
    n[3] = a[3] + b[3];
    n[4] = a[4] + b[4];
    n[5] = a[5] + b[5];
    n[6] = a[6] + b[6];
    n[7] = a[7] + b[7];
    n[0] -= (spint)0x3fffff9eu;
    n[1] += (spint)2u;
    n[7] -= (spint)0x800000u;
    carry = prop(n);
    n[0] += ((spint)0x3fffff9eu) & carry;
    n[1] -= (spint)2u & carry;
    n[7] += ((spint)0x800000u) & carry;
    (void)prop(n);
}

// Modular subtraction - reduce less than 2p
static void modsub_PM225_ct(const spint *a, const spint *b, spint *n) {
    spint carry;
    n[0] = a[0] - b[0];
    n[1] = a[1] - b[1];
    n[2] = a[2] - b[2];
    n[3] = a[3] - b[3];
    n[4] = a[4] - b[4];
    n[5] = a[5] - b[5];
    n[6] = a[6] - b[6];
    n[7] = a[7] - b[7];
    carry = prop(n);
    n[0] += ((spint)0x3fffff9eu) & carry;
    n[1] -= (spint)2u & carry;
    n[7] += ((spint)0x800000u) & carry;
    (void)prop(n);
}

// Modular negation
static void modneg_PM225_ct(const spint *b, spint *n) {
    spint carry;
    n[0] = (spint)0 - b[0];
    n[1] = (spint)0 - b[1];
    n[2] = (spint)0 - b[2];
    n[3] = (spint)0 - b[3];
    n[4] = (spint)0 - b[4];
    n[5] = (spint)0 - b[5];
    n[6] = (spint)0 - b[6];
    n[7] = (spint)0 - b[7];
    carry = prop(n);
    n[0] += ((spint)0x3fffff9eu) & carry;
    n[1] -= (spint)2u & carry;
    n[7] += ((spint)0x800000u) & carry;
    (void)prop(n);
}

// Overflow limit   = 18446744073709551616
// maximum possible = 2596325184638025784
// Modular multiplication, c=a*b mod 2p
static void modmul_PM225_ct(const spint *a, const spint *b, spint *c) {
    dpint t = 0;
    spint p0 = 0x1fffffcfu;
    spint q = ((spint)1 << 29u);  // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    spint ndash = 0x1a1f58d1u;
    t += (dpint)a[0] * b[0];
    spint v0 = (((spint)t * ndash) & mask);
    t += (dpint)v0 * (dpint)p0;
    t >>= 29;
    t += (dpint)a[0] * b[1];
    t += (dpint)a[1] * b[0];
    t += (dpint)(spint)(q - v0);
    spint v1 = (((spint)t * ndash) & mask);
    t += (dpint)v1 * (dpint)p0;
    t >>= 29;
    t += (dpint)a[0] * b[2];
    t += (dpint)a[1] * b[1];
    t += (dpint)a[2] * b[0];
    spint s = (spint)mask;
    s -= v1;
    t += (dpint)s;
    spint v2 = (((spint)t * ndash) & mask);
    t += (dpint)v2 * (dpint)p0;
    t >>= 29;
    t += (dpint)a[0] * b[3];
    t += (dpint)a[1] * b[2];
    t += (dpint)a[2] * b[1];
    t += (dpint)a[3] * b[0];
    s = (spint)mask;
    s -= v2;
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
    s -= v3;
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
    s -= v4;
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
    s -= v5;
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
    t += (dpint)(udpint)((udpint)v0 << 22u);
    s -= v6;
    t += (dpint)s;
    spint v7 = (((spint)t * ndash) & mask);
    t += (dpint)v7 * (dpint)p0;
    t >>= 29;
    t += (dpint)a[1] * b[7];
    t += (dpint)a[2] * b[6];
    t += (dpint)a[3] * b[5];
    t += (dpint)a[4] * b[4];
    t += (dpint)a[5] * b[3];
    t += (dpint)a[6] * b[2];
    t += (dpint)a[7] * b[1];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v1 << 22u);
    s -= v7;
    t += (dpint)s;
    c[0] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[2] * b[7];
    t += (dpint)a[3] * b[6];
    t += (dpint)a[4] * b[5];
    t += (dpint)a[5] * b[4];
    t += (dpint)a[6] * b[3];
    t += (dpint)a[7] * b[2];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v2 << 22u);
    t += (dpint)s;
    c[1] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[3] * b[7];
    t += (dpint)a[4] * b[6];
    t += (dpint)a[5] * b[5];
    t += (dpint)a[6] * b[4];
    t += (dpint)a[7] * b[3];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v3 << 22u);
    t += (dpint)s;
    c[2] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[4] * b[7];
    t += (dpint)a[5] * b[6];
    t += (dpint)a[6] * b[5];
    t += (dpint)a[7] * b[4];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v4 << 22u);
    t += (dpint)s;
    c[3] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[5] * b[7];
    t += (dpint)a[6] * b[6];
    t += (dpint)a[7] * b[5];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v5 << 22u);
    t += (dpint)s;
    c[4] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[6] * b[7];
    t += (dpint)a[7] * b[6];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v6 << 22u);
    t += (dpint)s;
    c[5] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[7] * b[7];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v7 << 22u);
    t += (dpint)s;
    c[6] = ((spint)t & mask);
    t >>= 29;
    t -= (dpint)1u;
    c[7] = (spint)t;
}

// Modular squaring, c=a*a  mod 2p
static void modsqr_PM225_ct(const spint *a, spint *c) {
    udpint tot;
    udpint t = 0;
    spint p0 = 0x1fffffcfu;
    spint q = ((spint)1 << 29u);  // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    spint ndash = 0x1a1f58d1u;
    tot = (udpint)a[0] * a[0];
    t = tot;
    spint v0 = (((spint)t * ndash) & mask);
    t += (udpint)v0 * p0;
    t >>= 29;
    tot = (udpint)a[0] * a[1];
    tot *= 2;
    t += tot;
    t += (udpint)(spint)(q - v0);
    spint v1 = (((spint)t * ndash) & mask);
    t += (udpint)v1 * p0;
    t >>= 29;
    tot = (udpint)a[0] * a[2];
    tot *= 2;
    tot += (udpint)a[1] * a[1];
    t += tot;
    spint s = (spint)mask;
    s -= v1;
    t += (udpint)s;
    spint v2 = (((spint)t * ndash) & mask);
    t += (udpint)v2 * p0;
    t >>= 29;
    tot = (udpint)a[0] * a[3];
    tot += (udpint)a[1] * a[2];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    s -= v2;
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
    s -= v3;
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
    s -= v4;
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
    s -= v5;
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
    t += (udpint)v0 << 22u;
    s -= v6;
    t += (udpint)s;
    spint v7 = (((spint)t * ndash) & mask);
    t += (udpint)v7 * p0;
    t >>= 29;
    tot = (udpint)a[1] * a[7];
    tot += (udpint)a[2] * a[6];
    tot += (udpint)a[3] * a[5];
    tot *= 2;
    tot += (udpint)a[4] * a[4];
    t += tot;
    s = (spint)mask;
    t += (udpint)v1 << 22u;
    s -= v7;
    t += (udpint)s;
    c[0] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[2] * a[7];
    tot += (udpint)a[3] * a[6];
    tot += (udpint)a[4] * a[5];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v2 << 22u;
    t += (udpint)s;
    c[1] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[3] * a[7];
    tot += (udpint)a[4] * a[6];
    tot *= 2;
    tot += (udpint)a[5] * a[5];
    t += tot;
    s = (spint)mask;
    t += (udpint)v3 << 22u;
    t += (udpint)s;
    c[2] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[4] * a[7];
    tot += (udpint)a[5] * a[6];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v4 << 22u;
    t += (udpint)s;
    c[3] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[5] * a[7];
    tot *= 2;
    tot += (udpint)a[6] * a[6];
    t += tot;
    s = (spint)mask;
    t += (udpint)v5 << 22u;
    t += (udpint)s;
    c[4] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[6] * a[7];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v6 << 22u;
    t += (udpint)s;
    c[5] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[7] * a[7];
    t += tot;
    s = (spint)mask;
    t += (udpint)v7 << 22u;
    t += (udpint)s;
    c[6] = ((spint)t & mask);
    t >>= 29;
    t -= 1u;
    c[7] = (spint)t;
}

// copy
static void modcpy_PM225_ct(const spint *a, spint *c) {
    int i;
    for (i = 0; i < 8; i++) {
        c[i] = a[i];
    }
}

// square n times
static void modnsqr_PM225_ct(spint *a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        modsqr_PM225_ct(a, a);
    }
}

// Calculate progenitor
static void modpro_PM225_ct(const spint *w, spint *z) {
    spint x[8];
    spint t0[8];
    spint t1[8];
    spint t2[8];
    spint t3[8];
    modcpy_PM225_ct(w, x);
    modsqr_PM225_ct(x, z);
    modmul_PM225_ct(x, z, z);
    modsqr_PM225_ct(z, t0);
    modmul_PM225_ct(x, t0, t0);
    modcpy_PM225_ct(t0, t1);
    modnsqr_PM225_ct(t1, 3);
    modmul_PM225_ct(t0, t1, t1);
    modcpy_PM225_ct(t1, t2);
    modnsqr_PM225_ct(t2, 6);
    modmul_PM225_ct(t1, t2, t1);
    modcpy_PM225_ct(t1, t2);
    modnsqr_PM225_ct(t2, 12);
    modmul_PM225_ct(t1, t2, t2);
    modcpy_PM225_ct(t2, t1);
    modnsqr_PM225_ct(t1, 3);
    modcpy_PM225_ct(t1, t3);
    modnsqr_PM225_ct(t3, 21);
    modmul_PM225_ct(t2, t3, t2);
    modcpy_PM225_ct(t2, t3);
    modnsqr_PM225_ct(t3, 48);
    modmul_PM225_ct(t2, t3, t2);
    modcpy_PM225_ct(t2, t3);
    modnsqr_PM225_ct(t3, 96);
    modmul_PM225_ct(t2, t3, t2);
    modnsqr_PM225_ct(t2, 27);
    modmul_PM225_ct(t1, t2, t1);
    modmul_PM225_ct(t0, t1, t0);
    modnsqr_PM225_ct(t0, 4);
    modmul_PM225_ct(z, t0, z);
}

// calculate inverse, provide progenitor h if available
static void modinv_PM225_ct(const spint *x, const spint *h, spint *z) {
    spint s[8];
    spint t[8];
    if (h == NULL) {
        modpro_PM225_ct(x, t);
    }
    else {
        modcpy_PM225_ct(h, t);
    }
    modcpy_PM225_ct(x, s);
    modnsqr_PM225_ct(t, 2);
    modmul_PM225_ct(s, t, z);
}

// Convert m to n-residue form, n=nres(m)
static void nres_PM225_ct(const spint *m, spint *n) {
    const spint c[8] = {0x2584000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u};
    modmul_PM225_ct(m, c, n);
}

// Convert n back to normal form, m=redc(n)
static void redc_PM225_ct(const spint *n, spint *m) {
    int i;
    spint c[8];
    c[0] = 1;
    for (i = 1; i < 8; i++) {
        c[i] = 0;
    }
    modmul_PM225_ct(n, c, m);
    (void)modfsb_PM225_ct(m);
}

// is unity?
static int modis1_PM225_ct(const spint *a) {
    int i;
    spint c[8];
    spint c0;
    spint d = 0;
    redc_PM225_ct(a, c);
    for (i = 1; i < 8; i++) {
        d |= c[i];
    }
    c0 = (spint)c[0];
    return ((spint)1 & ((d - (spint)1) >> 29u) & (((c0 ^ (spint)1) - (spint)1) >> 29u));
}

// is zero?
static int modis0_PM225_ct(const spint *a) {
    int i;
    spint c[8];
    spint d = 0;
    redc_PM225_ct(a, c);
    for (i = 0; i < 8; i++) {
        d |= c[i];
    }
    return ((spint)1 & ((d - (spint)1) >> 29u));
}

// set to zero
static void modzer_PM225_ct(spint *a) {
    int i;
    for (i = 0; i < 8; i++) {
        a[i] = 0;
    }
}

// set to one
static void modone_PM225_ct(spint *a) {
    int i;
    a[0] = 1;
    for (i = 1; i < 8; i++) {
        a[i] = 0;
    }
    nres_PM225_ct(a, a);
}

// set to integer
static void modint_PM225_ct(int x, spint *a) {
    int i;
    a[0] = (spint)x;
    for (i = 1; i < 8; i++) {
        a[i] = 0;
    }
    nres_PM225_ct(a, a);
}

// Modular multiplication by an integer, c=a*b mod 2p
static void modmli_PM225_ct(const spint *a, int b, spint *c) {
    spint t[8];
    modint_PM225_ct(b, t);
    modmul_PM225_ct(a, t, c);
}

// Test for quadratic residue
static int modqr_PM225_ct(const spint *h, const spint *x) {
    spint r[8];
    if (h == NULL) {
        modpro_PM225_ct(x, r);
        modsqr_PM225_ct(r, r);
    }
    else {
        modsqr_PM225_ct(h, r);
    }
    modmul_PM225_ct(r, x, r);
    return modis1_PM225_ct(r) | modis0_PM225_ct(x);
}

// conditional move g to f if d=1
// strongly recommend inlining be disabled using compiler specific syntax
static void modcmv_PM225_ct(int b, const spint *g, volatile spint *f) {
    int i;
    spint c0, c1, s, t, aux;
    spint r = 0x5aa5a55au;
    c0 = (~b) & (r + 1);
    c1 = b + r;
    for (i = 0; i < 8; i++) {
        s = g[i];
        t = f[i];
        f[i] = aux = c0 * t + c1 * s;
        f[i] = aux - r * (t + s);
    }
}

// conditional swap g and f if d=1
// strongly recommend inlining be disabled using compiler specific syntax
static void modcsw_PM225_ct(int b, volatile spint *g, volatile spint *f) {
    int i;
    spint c0, c1, s, t, w, aux;
    spint r = 0x5aa5a55au;
    c0 = (~b) & (r + 1);
    c1 = b + r;
    for (i = 0; i < 8; i++) {
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
static void modsqrt_PM225_ct(const spint *x, const spint *h, spint *r) {
    spint s[8];
    spint y[8];
    if (h == NULL) {
        modpro_PM225_ct(x, y);
    }
    else {
        modcpy_PM225_ct(h, y);
    }
    modmul_PM225_ct(y, x, s);
    modcpy_PM225_ct(s, r);
}

// shift left by less than a word
static void modshl_PM225_ct(unsigned int n, spint *a) {
    int i;
    a[7] = ((a[7] << n)) | (a[6] >> (29u - n));
    for (i = 6; i > 0; i--) {
        a[i] = ((a[i] << n) & (spint)0x1fffffff) | (a[i - 1] >> (29u - n));
    }
    a[0] = (a[0] << n) & (spint)0x1fffffff;
}

// shift right by less than a word. Return shifted out part
static int modshr_PM225_ct(unsigned int n, spint *a) {
    int i;
    spint r = a[0] & (((spint)1 << n) - (spint)1);
    for (i = 0; i < 7; i++) {
        a[i] = (a[i] >> n) | ((a[i + 1] << (29u - n)) & (spint)0x1fffffff);
    }
    a[7] = a[7] >> n;
    return r;
}

// set a= 2^r
static void mod2r_PM225_ct(unsigned int r, spint *a) {
    unsigned int n = r / 29u;
    unsigned int m = r % 29u;
    modzer_PM225_ct(a);
    if (r >= 29 * 8) return;
    a[n] = 1;
    a[n] <<= m;
    nres_PM225_ct(a, a);
}

// export to byte array
static void modexp_PM225_ct(const spint *a, char *b) {
    int i;
    spint c[8];
    redc_PM225_ct(a, c);
    for (i = 28; i >= 0; i--) {
        b[i] = c[0] & (spint)0xff;
        (void)modshr_PM225_ct(8, c);
    }
}

// import from byte array
// returns 1 if in range, else 0
static int modimp_PM225_ct(const char *b, spint *a) {
    int i, res;
    for (i = 0; i < 8; i++) {
        a[i] = 0;
    }
    for (i = 0; i < 29; i++) {
        modshl_PM225_ct(8, a);
        a[0] += (spint)(unsigned char)b[i];
    }
    res = modfsb_PM225_ct(a);
    nres_PM225_ct(a, a);
    return res;
}

// determine sign
static int modsign_PM225_ct(const spint *a) {
    spint c[8];
    redc_PM225_ct(a, c);
    return c[0] % 2;
}

// return true if equal
static int modcmp_PM225_ct(const spint *a, const spint *b) {
    spint c[8], d[8];
    int i, eq = 1;
    redc_PM225_ct(a, c);
    redc_PM225_ct(b, d);
    for (i = 0; i < 8; i++) {
        eq &= (((c[i] ^ d[i]) - 1) >> 29) & 1;
    }
    return eq;
}
