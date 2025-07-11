
// Automatically generated modular arithmetic C code for pseudo-Mersenne primes
// Python Script by Mike Scott (Technology Innovation Institute, UAE, 2025)

#include <stdint.h>
#include <stdio.h>

#define sspint int32_t
#define spint uint32_t
#define udpint uint64_t
#define dpint uint64_t

#define Wordlength_C25519_ct 32
#define Nlimbs_C25519_ct 9
#define Radix_C25519_ct 29
#define Nbits_C25519_ct 255
#define Nbytes_C25519_ct 32

#define MERSENNE
#define MULBYINT
#define C25519

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
    n[0] -= ((spint)19u) & carry;
    n[8] += ((spint)0x800000u) & carry;
    (void)prop(n);
    return (int)(carry & 1);
}

// Montgomery final subtract
static int modfsb_C25519_ct(spint *n) {
    n[0] += (spint)19u;
    n[8] -= (spint)0x800000u;
    return flatten(n);
}

// Modular addition - reduce less than 2p
static void modadd_C25519_ct(const spint *a, const spint *b, spint *n) {
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
    n[0] += (spint)38u;
    n[8] -= (spint)0x1000000u;
    carry = prop(n);
    n[0] -= ((spint)38u) & carry;
    n[8] += ((spint)0x1000000u) & carry;
    (void)prop(n);
}

// Modular subtraction - reduce less than 2p
static void modsub_C25519_ct(const spint *a, const spint *b, spint *n) {
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
    n[0] -= ((spint)38u) & carry;
    n[8] += ((spint)0x1000000u) & carry;
    (void)prop(n);
}

// Modular negation
static void modneg_C25519_ct(const spint *b, spint *n) {
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
    n[0] -= ((spint)38u) & carry;
    n[8] += ((spint)0x1000000u) & carry;
    (void)prop(n);
}

// Modular multiplication by an integer, c=a*b mod 2p
static void modmli_C25519_ct(const spint *a, int b, spint *c) {
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
    // second reduction pass

    udpint ut = (udpint)t;
    ut = (ut << 6) + (spint)(v8 >> 23u);
    v8 &= 0x7fffff;
    ut *= 0x13;
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
}

// Modular multiplication, c=a*b mod 2p
static void modmul_C25519_ct(const spint *a, const spint *b, spint *c) {
    dpint t = 0;
    dpint tt;
    spint lo;
    spint hi;
    spint carry;
    spint s;
    spint mask = ((spint)1 << 29u) - (spint)1;
    tt = (dpint)a[1] * (dpint)b[8];
    tt += (dpint)a[2] * (dpint)b[7];
    tt += (dpint)a[3] * (dpint)b[6];
    tt += (dpint)a[4] * (dpint)b[5];
    tt += (dpint)a[5] * (dpint)b[4];
    tt += (dpint)a[6] * (dpint)b[3];
    tt += (dpint)a[7] * (dpint)b[2];
    tt += (dpint)a[8] * (dpint)b[1];
    lo = (spint)tt & mask;
    t += (dpint)lo * (dpint)0x4c0;
    hi = (spint)(tt >> 29u);
    t += (dpint)a[0] * (dpint)b[0];
    spint v0 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[2] * (dpint)b[8];
    tt += (dpint)a[3] * (dpint)b[7];
    tt += (dpint)a[4] * (dpint)b[6];
    tt += (dpint)a[5] * (dpint)b[5];
    tt += (dpint)a[6] * (dpint)b[4];
    tt += (dpint)a[7] * (dpint)b[3];
    tt += (dpint)a[8] * (dpint)b[2];
    lo = (spint)tt & mask;
    t += (dpint)(spint)(lo + hi) * (dpint)0x4c0;
    hi = (spint)(tt >> 29u);
    t += (dpint)a[0] * (dpint)b[1];
    t += (dpint)a[1] * (dpint)b[0];
    spint v1 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[3] * (dpint)b[8];
    tt += (dpint)a[4] * (dpint)b[7];
    tt += (dpint)a[5] * (dpint)b[6];
    tt += (dpint)a[6] * (dpint)b[5];
    tt += (dpint)a[7] * (dpint)b[4];
    tt += (dpint)a[8] * (dpint)b[3];
    lo = (spint)tt & mask;
    t += (dpint)(spint)(lo + hi) * (dpint)0x4c0;
    hi = (spint)(tt >> 29u);
    t += (dpint)a[0] * (dpint)b[2];
    t += (dpint)a[1] * (dpint)b[1];
    t += (dpint)a[2] * (dpint)b[0];
    spint v2 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[4] * (dpint)b[8];
    tt += (dpint)a[5] * (dpint)b[7];
    tt += (dpint)a[6] * (dpint)b[6];
    tt += (dpint)a[7] * (dpint)b[5];
    tt += (dpint)a[8] * (dpint)b[4];
    lo = (spint)tt & mask;
    t += (dpint)(spint)(lo + hi) * (dpint)0x4c0;
    hi = (spint)(tt >> 29u);
    t += (dpint)a[0] * (dpint)b[3];
    t += (dpint)a[1] * (dpint)b[2];
    t += (dpint)a[2] * (dpint)b[1];
    t += (dpint)a[3] * (dpint)b[0];
    spint v3 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[5] * (dpint)b[8];
    tt += (dpint)a[6] * (dpint)b[7];
    tt += (dpint)a[7] * (dpint)b[6];
    tt += (dpint)a[8] * (dpint)b[5];
    lo = (spint)tt & mask;
    t += (dpint)(spint)(lo + hi) * (dpint)0x4c0;
    hi = (spint)(tt >> 29u);
    t += (dpint)a[0] * (dpint)b[4];
    t += (dpint)a[1] * (dpint)b[3];
    t += (dpint)a[2] * (dpint)b[2];
    t += (dpint)a[3] * (dpint)b[1];
    t += (dpint)a[4] * (dpint)b[0];
    spint v4 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[6] * (dpint)b[8];
    tt += (dpint)a[7] * (dpint)b[7];
    tt += (dpint)a[8] * (dpint)b[6];
    lo = (spint)tt & mask;
    t += (dpint)(spint)(lo + hi) * (dpint)0x4c0;
    hi = (spint)(tt >> 29u);
    t += (dpint)a[0] * (dpint)b[5];
    t += (dpint)a[1] * (dpint)b[4];
    t += (dpint)a[2] * (dpint)b[3];
    t += (dpint)a[3] * (dpint)b[2];
    t += (dpint)a[4] * (dpint)b[1];
    t += (dpint)a[5] * (dpint)b[0];
    spint v5 = (spint)t & mask;
    t = t >> 29u;
    tt = (dpint)a[7] * (dpint)b[8];
    tt += (dpint)a[8] * (dpint)b[7];
    lo = (spint)tt & mask;
    t += (dpint)(spint)(lo + hi) * (dpint)0x4c0;
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
    tt = (dpint)a[8] * (dpint)b[8];
    lo = (spint)tt & mask;
    t += (dpint)(spint)(lo + hi) * (dpint)0x4c0;
    hi = (spint)(tt >> 29u);
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
    t += (dpint)a[0] * (dpint)b[8];
    t += (dpint)a[1] * (dpint)b[7];
    t += (dpint)a[2] * (dpint)b[6];
    t += (dpint)a[3] * (dpint)b[5];
    t += (dpint)a[4] * (dpint)b[4];
    t += (dpint)a[5] * (dpint)b[3];
    t += (dpint)a[6] * (dpint)b[2];
    t += (dpint)a[7] * (dpint)b[1];
    t += (dpint)a[8] * (dpint)b[0];
    t += (dpint)hi * (dpint)0x4c0;
    spint v8 = (spint)t & mask;
    t = t >> 29u;
    // second reduction pass

    udpint ut = (udpint)t;
    ut = (ut << 6) + (spint)(v8 >> 23u);
    v8 &= 0x7fffff;
    ut *= 0x13;
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
}

// Modular squaring, c=a*a mod 2p
static void modsqr_C25519_ct(const spint *a, spint *c) {
    udpint t = 0;
    udpint tt;
    udpint t2;
    spint carry;
    spint s;
    spint mask = ((spint)1 << 29u) - (spint)1;
    spint lo;
    spint hi;
    tt = (udpint)a[1] * (udpint)a[8];
    tt += (udpint)a[2] * (udpint)a[7];
    tt += (udpint)a[3] * (udpint)a[6];
    tt += (udpint)a[4] * (udpint)a[5];
    tt *= 2;
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[0];
    t2 += (udpint)lo * (udpint)0x4c0;
    hi = (spint)(tt >> 29u);
    t += t2;
    spint v0 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[2] * (udpint)a[8];
    tt += (udpint)a[3] * (udpint)a[7];
    tt += (udpint)a[4] * (udpint)a[6];
    tt *= 2;
    tt += (udpint)a[5] * (udpint)a[5];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[1];
    t2 *= 2;
    t2 += (udpint)(spint)(lo + hi) * (udpint)0x4c0;
    hi = (spint)(tt >> 29u);
    t += t2;
    spint v1 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[3] * (udpint)a[8];
    tt += (udpint)a[4] * (udpint)a[7];
    tt += (udpint)a[5] * (udpint)a[6];
    tt *= 2;
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[2];
    t2 *= 2;
    t2 += (udpint)a[1] * (udpint)a[1];
    t2 += (udpint)(spint)(lo + hi) * (udpint)0x4c0;
    hi = (spint)(tt >> 29u);
    t += t2;
    spint v2 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[4] * (udpint)a[8];
    tt += (udpint)a[5] * (udpint)a[7];
    tt *= 2;
    tt += (udpint)a[6] * (udpint)a[6];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[3];
    t2 += (udpint)a[1] * (udpint)a[2];
    t2 *= 2;
    t2 += (udpint)(spint)(lo + hi) * (udpint)0x4c0;
    hi = (spint)(tt >> 29u);
    t += t2;
    spint v3 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[5] * (udpint)a[8];
    tt += (udpint)a[6] * (udpint)a[7];
    tt *= 2;
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[4];
    t2 += (udpint)a[1] * (udpint)a[3];
    t2 *= 2;
    t2 += (udpint)a[2] * (udpint)a[2];
    t2 += (udpint)(spint)(lo + hi) * (udpint)0x4c0;
    hi = (spint)(tt >> 29u);
    t += t2;
    spint v4 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[6] * (udpint)a[8];
    tt *= 2;
    tt += (udpint)a[7] * (udpint)a[7];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[5];
    t2 += (udpint)a[1] * (udpint)a[4];
    t2 += (udpint)a[2] * (udpint)a[3];
    t2 *= 2;
    t2 += (udpint)(spint)(lo + hi) * (udpint)0x4c0;
    hi = (spint)(tt >> 29u);
    t += t2;
    spint v5 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[7] * (udpint)a[8];
    tt *= 2;
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[6];
    t2 += (udpint)a[1] * (udpint)a[5];
    t2 += (udpint)a[2] * (udpint)a[4];
    t2 *= 2;
    t2 += (udpint)a[3] * (udpint)a[3];
    t2 += (udpint)(spint)(lo + hi) * (udpint)0x4c0;
    hi = (spint)(tt >> 29u);
    t += t2;
    spint v6 = (spint)t & mask;
    t = t >> 29u;
    tt = (udpint)a[8] * (udpint)a[8];
    lo = (spint)tt & mask;
    t2 = (udpint)a[0] * (udpint)a[7];
    t2 += (udpint)a[1] * (udpint)a[6];
    t2 += (udpint)a[2] * (udpint)a[5];
    t2 += (udpint)a[3] * (udpint)a[4];
    t2 *= 2;
    t2 += (udpint)(spint)(lo + hi) * (udpint)0x4c0;
    hi = (spint)(tt >> 29u);
    t += t2;
    spint v7 = (spint)t & mask;
    t = t >> 29u;
    t2 = (udpint)a[0] * (udpint)a[8];
    t2 += (udpint)a[1] * (udpint)a[7];
    t2 += (udpint)a[2] * (udpint)a[6];
    t2 += (udpint)a[3] * (udpint)a[5];
    t2 *= 2;
    t2 += (udpint)a[4] * (udpint)a[4];
    t += (udpint)hi * (udpint)0x4c0;
    t += t2;
    spint v8 = (spint)t & mask;
    t = t >> 29u;
    // second reduction pass

    udpint ut = (udpint)t;
    ut = (ut << 6) + (spint)(v8 >> 23u);
    v8 &= 0x7fffff;
    ut *= 0x13;
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
}

// copy
static void modcpy_C25519_ct(const spint *a, spint *c) {
    int i;
    for (i = 0; i < 9; i++) {
        c[i] = a[i];
    }
}

// square n times
static void modnsqr_C25519_ct(spint *a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        modsqr_C25519_ct(a, a);
    }
}

// Calculate progenitor - use optimal addition chain
static void modpro_C25519_ct(const spint *w, spint *z) {
    spint x[9];
    spint t0[9];
    spint t1[9];
    modcpy_C25519_ct(w, x);
    modsqr_C25519_ct(x, z);
    modmul_C25519_ct(x, z, z);
    modcpy_C25519_ct(z, t0);
    modnsqr_C25519_ct(t0, 2);
    modmul_C25519_ct(z, t0, z);
    modsqr_C25519_ct(z, z);
    modmul_C25519_ct(x, z, t0);
    modcpy_C25519_ct(t0, z);
    modnsqr_C25519_ct(z, 5);
    modmul_C25519_ct(t0, z, z);
    modcpy_C25519_ct(z, t1);
    modnsqr_C25519_ct(t1, 5);
    modmul_C25519_ct(t0, t1, t0);
    modcpy_C25519_ct(t0, t1);
    modnsqr_C25519_ct(t1, 15);
    modmul_C25519_ct(t0, t1, t0);
    modcpy_C25519_ct(t0, t1);
    modnsqr_C25519_ct(t1, 30);
    modmul_C25519_ct(t0, t1, t0);
    modcpy_C25519_ct(t0, t1);
    modnsqr_C25519_ct(t1, 60);
    modmul_C25519_ct(t0, t1, t0);
    modcpy_C25519_ct(t0, t1);
    modnsqr_C25519_ct(t1, 120);
    modmul_C25519_ct(t0, t1, t0);
    modnsqr_C25519_ct(t0, 10);
    modmul_C25519_ct(z, t0, z);
    modnsqr_C25519_ct(z, 2);
    modmul_C25519_ct(x, z, z);
}

// calculate inverse, provide progenitor h if available, NULL if not
static void modinv_C25519_ct(const spint *x, const spint *h, spint *z) {
    int i;
    spint s[9];
    spint t[9];
    if (h == NULL) {
        modpro_C25519_ct(x, t);
    }
    else {
        modcpy_C25519_ct(h, t);
    }
    modcpy_C25519_ct(x, s);
    for (i = 0; i < 1; i++) {
        modsqr_C25519_ct(s, s);
        modmul_C25519_ct(s, x, s);
    }
    modnsqr_C25519_ct(t, 3);
    modmul_C25519_ct(s, t, z);
}

// Convert m to internal form, n=nres(m)
static void nres_C25519_ct(const spint *m, spint *n) {
    int i;
    for (i = 0; i < 9; i++) {
        n[i] = m[i];
    }
}

// Convert n back to normal form, m=redc(n)
static void redc_C25519_ct(const spint *n, spint *m) {
    int i;
    for (i = 0; i < 9; i++) {
        m[i] = n[i];
    }
    (void)modfsb_C25519_ct(m);
}

// is unity?
static int modis1_C25519_ct(const spint *a) {
    int i;
    spint c[9];
    spint c0;
    spint d = 0;
    redc_C25519_ct(a, c);
    for (i = 1; i < 9; i++) {
        d |= c[i];
    }
    c0 = (spint)c[0];
    return ((spint)1 & ((d - (spint)1) >> 29u) & (((c0 ^ (spint)1) - (spint)1) >> 29u));
}

// is zero?
static int modis0_C25519_ct(const spint *a) {
    int i;
    spint c[9];
    spint d = 0;
    redc_C25519_ct(a, c);
    for (i = 0; i < 9; i++) {
        d |= c[i];
    }
    return ((spint)1 & ((d - (spint)1) >> 29u));
}

// set to zero
static void modzer_C25519_ct(spint *a) {
    int i;
    for (i = 0; i < 9; i++) {
        a[i] = 0;
    }
}

// set to one
static void modone_C25519_ct(spint *a) {
    int i;
    a[0] = 1;
    for (i = 1; i < 9; i++) {
        a[i] = 0;
    }
    nres_C25519_ct(a, a);
}

// set to integer
static void modint_C25519_ct(int x, spint *a) {
    int i;
    a[0] = (spint)x;
    for (i = 1; i < 9; i++) {
        a[i] = 0;
    }
    nres_C25519_ct(a, a);
}

// Test for quadratic residue, provide progenitor h if available, NULL if not
static int modqr_C25519_ct(const spint *h, const spint *x) {
    spint r[9];
    if (h == NULL) {
        modpro_C25519_ct(x, r);
        modsqr_C25519_ct(r, r);
    }
    else {
        modsqr_C25519_ct(h, r);
    }
    modmul_C25519_ct(r, x, r);
    modnsqr_C25519_ct(r, 1);
    return modis1_C25519_ct(r) | modis0_C25519_ct(x);
}

// conditional move g to f if d=1
// strongly recommend inlining be disabled using compiler specific syntax
static void modcmv_C25519_ct(int b, const spint *g, volatile spint *f) {
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
static void modcsw_C25519_ct(int b, volatile spint *g, volatile spint *f) {
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
static void modsqrt_C25519_ct(const spint *x, const spint *h, spint *r) {
    int k;
    spint t[9];
    spint b[9];
    spint v[9];
    spint z[9] = {0xa0ea0b0, 0x770d93a, 0xbf91e31, 0x6300d5a, 0x1d7a72f4, 0x4c9efd, 0x1c2cad34, 0x1009f83b, 0x2b8324};
    spint s[9];
    spint y[9];
    if (h == NULL) {
        modpro_C25519_ct(x, y);
    }
    else {
        modcpy_C25519_ct(h, y);
    }
    modmul_C25519_ct(y, x, s);
    modmul_C25519_ct(s, y, t);
    nres_C25519_ct(z, z);
    for (k = 2; k > 1; k--) {
        modcpy_C25519_ct(t, b);
        modnsqr_C25519_ct(b, k - 2);
        int d = 1 - modis1_C25519_ct(b);
        modmul_C25519_ct(s, z, v);
        modcmv_C25519_ct(d, v, s);
        modsqr_C25519_ct(z, z);
        modmul_C25519_ct(t, z, v);
        modcmv_C25519_ct(d, v, t);
    }
    modcpy_C25519_ct(s, r);
}

// shift left by less than a word
static void modshl_C25519_ct(unsigned int n, spint *a) {
    int i;
    a[8] = ((a[8] << n)) | (a[7] >> (29u - n));
    for (i = 7; i > 0; i--) {
        a[i] = ((a[i] << n) & (spint)0x1fffffff) | (a[i - 1] >> (29u - n));
    }
    a[0] = (a[0] << n) & (spint)0x1fffffff;
}

// shift right by less than a word. Return shifted out part
static int modshr_C25519_ct(unsigned int n, spint *a) {
    int i;
    spint r = a[0] & (((spint)1 << n) - (spint)1);
    for (i = 0; i < 8; i++) {
        a[i] = (a[i] >> n) | ((a[i + 1] << (29u - n)) & (spint)0x1fffffff);
    }
    a[8] = a[8] >> n;
    return r;
}

// set a= 2^r
static void mod2r_C25519_ct(unsigned int r, spint *a) {
    unsigned int n = r / 29u;
    unsigned int m = r % 29u;
    modzer_C25519_ct(a);
    if (r >= 32 * 8) return;
    a[n] = 1;
    a[n] <<= m;
}

// export to byte array
static void modexp_C25519_ct(const spint *a, char *b) {
    int i;
    spint c[9];
    redc_C25519_ct(a, c);
    for (i = 31; i >= 0; i--) {
        b[i] = c[0] & (spint)0xff;
        (void)modshr_C25519_ct(8, c);
    }
}

// import from byte array
// returns 1 if in range, else 0
static int modimp_C25519_ct(const char *b, spint *a) {
    int i, res;
    for (i = 0; i < 9; i++) {
        a[i] = 0;
    }
    for (i = 0; i < 32; i++) {
        modshl_C25519_ct(8, a);
        a[0] += (spint)(unsigned char)b[i];
    }
    res = modfsb_C25519_ct(a);
    nres_C25519_ct(a, a);
    return res;
}

// determine sign
static int modsign_C25519_ct(const spint *a) {
    spint c[9];
    redc_C25519_ct(a, c);
    return c[0] % 2;
}

// return true if equal
static int modcmp_C25519_ct(const spint *a, const spint *b) {
    spint c[9], d[9];
    int i, eq = 1;
    redc_C25519_ct(a, c);
    redc_C25519_ct(b, d);
    for (i = 0; i < 9; i++) {
        eq &= (((c[i] ^ d[i]) - 1) >> 29) & 1;
    }
    return eq;
}
