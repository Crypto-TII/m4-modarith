
// Automatically generated modular arithmetic C code for pseudo-Mersenne primes
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

#define MERSENNE
#define MULBYINT
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
    n[0] -= ((spint)49u) & carry;
    n[7] += ((spint)0x400000u) & carry;
    (void)prop(n);
    return (int)(carry & 1);
}

// Montgomery final subtract
static int modfsb_PM225_ct(spint *n) {
    n[0] += (spint)49u;
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
    n[0] += (spint)98u;
    n[7] -= (spint)0x800000u;
    carry = prop(n);
    n[0] -= ((spint)98u) & carry;
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
    n[0] -= ((spint)98u) & carry;
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
    n[0] -= ((spint)98u) & carry;
    n[7] += ((spint)0x800000u) & carry;
    (void)prop(n);
}

// Modular multiplication by an integer, c=a*b mod 2p
static void modmli_PM225_ct(const spint *a, int b, spint *c) {
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
    // second reduction pass

    udpint ut = (udpint)t;
    ut = (ut << 7) + (spint)(v7 >> 22u);
    v7 &= 0x3fffff;
    ut *= 0x31;
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
}

// Modular multiplication, c=a*b mod 2p
static void modmul_PM225_ct(const spint *a, const spint *b, spint *c) {
    dpint t = 0;
    dpint tt;
    spint lo;
    spint hi;
    spint carry;
    spint s;
    spint mask = ((spint)1 << 29u) - (spint)1;
    tt = (dpint)a[1] * (dpint)b[7];
    tt += (dpint)a[2] * (dpint)b[6];
    tt += (dpint)a[3] * (dpint)b[5];
    tt += (dpint)a[4] * (dpint)b[4];
    tt += (dpint)a[5] * (dpint)b[3];
    tt += (dpint)a[6] * (dpint)b[2];
    tt += (dpint)a[7] * (dpint)b[1];
    lo = (spint)tt & mask;
    t += (dpint)lo * (dpint)0x1880;
    hi = (spint)(tt >> 29u);
    t += (dpint)a[0] * (dpint)b[0];
    spint v0 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[2] * (dpint)b[7];
    tt += (dpint)a[3] * (dpint)b[6];
    tt += (dpint)a[4] * (dpint)b[5];
    tt += (dpint)a[5] * (dpint)b[4];
    tt += (dpint)a[6] * (dpint)b[3];
    tt += (dpint)a[7] * (dpint)b[2];
    lo = (spint)tt & mask;
    t += (dpint)(spint)(lo + hi) * (dpint)0x1880;
    hi = (spint)(tt >> 29u);
    t += (dpint)a[0] * (dpint)b[1];
    t += (dpint)a[1] * (dpint)b[0];
    spint v1 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[3] * (dpint)b[7];
    tt += (dpint)a[4] * (dpint)b[6];
    tt += (dpint)a[5] * (dpint)b[5];
    tt += (dpint)a[6] * (dpint)b[4];
    tt += (dpint)a[7] * (dpint)b[3];
    lo = (spint)tt & mask;
    t += (dpint)(spint)(lo + hi) * (dpint)0x1880;
    hi = (spint)(tt >> 29u);
    t += (dpint)a[0] * (dpint)b[2];
    t += (dpint)a[1] * (dpint)b[1];
    t += (dpint)a[2] * (dpint)b[0];
    spint v2 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[4] * (dpint)b[7];
    tt += (dpint)a[5] * (dpint)b[6];
    tt += (dpint)a[6] * (dpint)b[5];
    tt += (dpint)a[7] * (dpint)b[4];
    lo = (spint)tt & mask;
    t += (dpint)(spint)(lo + hi) * (dpint)0x1880;
    hi = (spint)(tt >> 29u);
    t += (dpint)a[0] * (dpint)b[3];
    t += (dpint)a[1] * (dpint)b[2];
    t += (dpint)a[2] * (dpint)b[1];
    t += (dpint)a[3] * (dpint)b[0];
    spint v3 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[5] * (dpint)b[7];
    tt += (dpint)a[6] * (dpint)b[6];
    tt += (dpint)a[7] * (dpint)b[5];
    lo = (spint)tt & mask;
    t += (dpint)(spint)(lo + hi) * (dpint)0x1880;
    hi = (spint)(tt >> 29u);
    t += (dpint)a[0] * (dpint)b[4];
    t += (dpint)a[1] * (dpint)b[3];
    t += (dpint)a[2] * (dpint)b[2];
    t += (dpint)a[3] * (dpint)b[1];
    t += (dpint)a[4] * (dpint)b[0];
    spint v4 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[6] * (dpint)b[7];
    tt += (dpint)a[7] * (dpint)b[6];
    lo = (spint)tt & mask;
    t += (dpint)(spint)(lo + hi) * (dpint)0x1880;
    hi = (spint)(tt >> 29u);
    t += (dpint)a[0] * (dpint)b[5];
    t += (dpint)a[1] * (dpint)b[4];
    t += (dpint)a[2] * (dpint)b[3];
    t += (dpint)a[3] * (dpint)b[2];
    t += (dpint)a[4] * (dpint)b[1];
    t += (dpint)a[5] * (dpint)b[0];
    spint v5 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[7] * (dpint)b[7];
    lo = (spint)tt & mask;
    t += (dpint)(spint)(lo + hi) * (dpint)0x1880;
    hi = (spint)(tt >> 29u);
    t += (dpint)a[0] * (dpint)b[6];
    t += (dpint)a[1] * (dpint)b[5];
    t += (dpint)a[2] * (dpint)b[4];
    t += (dpint)a[3] * (dpint)b[3];
    t += (dpint)a[4] * (dpint)b[2];
    t += (dpint)a[5] * (dpint)b[1];
    t += (dpint)a[6] * (dpint)b[0];
    spint v6 = (spint)t & mask;
    t = t >> 29u;
    t += (dpint)a[0] * (dpint)b[7];
    t += (dpint)a[1] * (dpint)b[6];
    t += (dpint)a[2] * (dpint)b[5];
    t += (dpint)a[3] * (dpint)b[4];
    t += (dpint)a[4] * (dpint)b[3];
    t += (dpint)a[5] * (dpint)b[2];
    t += (dpint)a[6] * (dpint)b[1];
    t += (dpint)a[7] * (dpint)b[0];
    t += (dpint)hi * (dpint)0x1880;
    spint v7 = (spint)t & mask;
    t = t >> 29u;
    // second reduction pass

    udpint ut = (udpint)t;
    ut = (ut << 7) + (spint)(v7 >> 22u);
    v7 &= 0x3fffff;
    ut *= 0x31;
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
}

// Modular squaring, c=a*a mod 2p
static void modsqr_PM225_ct(const spint *a, spint *c) {
    udpint t = 0;
    udpint tt;
    udpint t2;
    spint carry;
    spint s;
    spint mask = ((spint)1 << 29u) - (spint)1;
    spint lo;
    spint hi;
    tt = (udpint)a[1] * (udpint)a[7];
    tt += (udpint)a[2] * (udpint)a[6];
    tt += (udpint)a[3] * (udpint)a[5];
    tt *= 2;
    tt += (udpint)a[4] * (udpint)a[4];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[0];
    t2 += (udpint)lo * (udpint)0x1880;
    hi = (spint)(tt >> 29u);
    t += t2;
    spint v0 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[2] * (udpint)a[7];
    tt += (udpint)a[3] * (udpint)a[6];
    tt += (udpint)a[4] * (udpint)a[5];
    tt *= 2;
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[1];
    t2 *= 2;
    t2 += (udpint)(spint)(lo + hi) * (udpint)0x1880;
    hi = (spint)(tt >> 29u);
    t += t2;
    spint v1 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[3] * (udpint)a[7];
    tt += (udpint)a[4] * (udpint)a[6];
    tt *= 2;
    tt += (udpint)a[5] * (udpint)a[5];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[2];
    t2 *= 2;
    t2 += (udpint)a[1] * (udpint)a[1];
    t2 += (udpint)(spint)(lo + hi) * (udpint)0x1880;
    hi = (spint)(tt >> 29u);
    t += t2;
    spint v2 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[4] * (udpint)a[7];
    tt += (udpint)a[5] * (udpint)a[6];
    tt *= 2;
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[3];
    t2 += (udpint)a[1] * (udpint)a[2];
    t2 *= 2;
    t2 += (udpint)(spint)(lo + hi) * (udpint)0x1880;
    hi = (spint)(tt >> 29u);
    t += t2;
    spint v3 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[5] * (udpint)a[7];
    tt *= 2;
    tt += (udpint)a[6] * (udpint)a[6];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[4];
    t2 += (udpint)a[1] * (udpint)a[3];
    t2 *= 2;
    t2 += (udpint)a[2] * (udpint)a[2];
    t2 += (udpint)(spint)(lo + hi) * (udpint)0x1880;
    hi = (spint)(tt >> 29u);
    t += t2;
    spint v4 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[6] * (udpint)a[7];
    tt *= 2;
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[5];
    t2 += (udpint)a[1] * (udpint)a[4];
    t2 += (udpint)a[2] * (udpint)a[3];
    t2 *= 2;
    t2 += (udpint)(spint)(lo + hi) * (udpint)0x1880;
    hi = (spint)(tt >> 29u);
    t += t2;
    spint v5 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[7] * (udpint)a[7];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[6];
    t2 += (udpint)a[1] * (udpint)a[5];
    t2 += (udpint)a[2] * (udpint)a[4];
    t2 *= 2;
    t2 += (udpint)a[3] * (udpint)a[3];
    t2 += (udpint)(spint)(lo + hi) * (udpint)0x1880;
    hi = (spint)(tt >> 29u);
    t += t2;
    spint v6 = (spint)t & mask;
    t = t >> 29u;
    t2 = (udpint)a[0] * (udpint)a[7];
    t2 += (udpint)a[1] * (udpint)a[6];
    t2 += (udpint)a[2] * (udpint)a[5];
    t2 += (udpint)a[3] * (udpint)a[4];
    t2 *= 2;
    t += (udpint)hi * (udpint)0x1880;
    t += t2;
    spint v7 = (spint)t & mask;
    t = t >> 29u;
    // second reduction pass

    udpint ut = (udpint)t;
    ut = (ut << 7) + (spint)(v7 >> 22u);
    v7 &= 0x3fffff;
    ut *= 0x31;
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

// Calculate progenitor - use optimal addition chain
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

// calculate inverse, provide progenitor h if available, NULL if not
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

// Convert m to internal form, n=nres(m)
static void nres_PM225_ct(const spint *m, spint *n) {
    int i;
    for (i = 0; i < 8; i++) {
        n[i] = m[i];
    }
}

// Convert n back to normal form, m=redc(n)
static void redc_PM225_ct(const spint *n, spint *m) {
    int i;
    for (i = 0; i < 8; i++) {
        m[i] = n[i];
    }
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

// Test for quadratic residue, provide progenitor h if available, NULL if not
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
