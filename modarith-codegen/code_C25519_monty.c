
// Automatically generated modular arithmetic C code
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

#define MONTGOMERY
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
    n[0] += ((spint)0x1fffffedu) & carry;
    n[1] -= (spint)1u & carry;
    n[8] += ((spint)0x800000u) & carry;
    (void)prop(n);
    return (int)(carry & 1);
}

// Montgomery final subtract
static int modfsb_C25519_ct(spint *n) {
    n[0] -= (spint)0x1fffffedu;
    n[1] += (spint)1u;
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
    n[0] -= (spint)0x3fffffdau;
    n[1] += (spint)2u;
    n[8] -= (spint)0x1000000u;
    carry = prop(n);
    n[0] += ((spint)0x3fffffdau) & carry;
    n[1] -= (spint)2u & carry;
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
    n[0] += ((spint)0x3fffffdau) & carry;
    n[1] -= (spint)2u & carry;
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
    n[0] += ((spint)0x3fffffdau) & carry;
    n[1] -= (spint)2u & carry;
    n[8] += ((spint)0x1000000u) & carry;
    (void)prop(n);
}

// Overflow limit   = 18446744073709551616
// maximum possible = 2886807375631613979
// Modular multiplication, c=a*b mod 2p
static void modmul_C25519_ct(const spint *a, const spint *b, spint *c) {
    dpint t = 0;
    spint p0 = 0x1fffffedu;
    spint q = ((spint)1 << 29u);  // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    spint ndash = 0x86bca1bu;
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
    s -= v6;
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
    t += (dpint)(udpint)((udpint)v0 << 23u);
    s -= v7;
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
    t += (dpint)(udpint)((udpint)v1 << 23u);
    s -= v8;
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
    t += (dpint)(udpint)((udpint)v2 << 23u);
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
    t += (dpint)(udpint)((udpint)v3 << 23u);
    t += (dpint)s;
    c[2] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[4] * b[8];
    t += (dpint)a[5] * b[7];
    t += (dpint)a[6] * b[6];
    t += (dpint)a[7] * b[5];
    t += (dpint)a[8] * b[4];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v4 << 23u);
    t += (dpint)s;
    c[3] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[5] * b[8];
    t += (dpint)a[6] * b[7];
    t += (dpint)a[7] * b[6];
    t += (dpint)a[8] * b[5];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v5 << 23u);
    t += (dpint)s;
    c[4] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[6] * b[8];
    t += (dpint)a[7] * b[7];
    t += (dpint)a[8] * b[6];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v6 << 23u);
    t += (dpint)s;
    c[5] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[7] * b[8];
    t += (dpint)a[8] * b[7];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v7 << 23u);
    t += (dpint)s;
    c[6] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[8] * b[8];
    s = (spint)mask;
    t += (dpint)(udpint)((udpint)v8 << 23u);
    t += (dpint)s;
    c[7] = ((spint)t & mask);
    t >>= 29;
    t -= (dpint)1u;
    c[8] = (spint)t;
}

// Modular squaring, c=a*a  mod 2p
static void modsqr_C25519_ct(const spint *a, spint *c) {
    udpint tot;
    udpint t = 0;
    spint p0 = 0x1fffffedu;
    spint q = ((spint)1 << 29u);  // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    spint ndash = 0x86bca1bu;
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
    s -= v6;
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
    t += (udpint)v0 << 23u;
    s -= v7;
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
    t += (udpint)v1 << 23u;
    s -= v8;
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
    t += (udpint)v2 << 23u;
    t += (udpint)s;
    c[1] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[3] * a[8];
    tot += (udpint)a[4] * a[7];
    tot += (udpint)a[5] * a[6];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v3 << 23u;
    t += (udpint)s;
    c[2] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[4] * a[8];
    tot += (udpint)a[5] * a[7];
    tot *= 2;
    tot += (udpint)a[6] * a[6];
    t += tot;
    s = (spint)mask;
    t += (udpint)v4 << 23u;
    t += (udpint)s;
    c[3] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[5] * a[8];
    tot += (udpint)a[6] * a[7];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v5 << 23u;
    t += (udpint)s;
    c[4] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[6] * a[8];
    tot *= 2;
    tot += (udpint)a[7] * a[7];
    t += tot;
    s = (spint)mask;
    t += (udpint)v6 << 23u;
    t += (udpint)s;
    c[5] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[7] * a[8];
    tot *= 2;
    t += tot;
    s = (spint)mask;
    t += (udpint)v7 << 23u;
    t += (udpint)s;
    c[6] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[8] * a[8];
    t += tot;
    s = (spint)mask;
    t += (udpint)v8 << 23u;
    t += (udpint)s;
    c[7] = ((spint)t & mask);
    t >>= 29;
    t -= 1u;
    c[8] = (spint)t;
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

// Calculate progenitor
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

// calculate inverse, provide progenitor h if available
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
    for (i = 0; i < (2 - 1); i++) {
        modsqr_C25519_ct(s, s);
        modmul_C25519_ct(s, x, s);
    }
    modnsqr_C25519_ct(t, 3);
    modmul_C25519_ct(s, t, z);
}

// Convert m to n-residue form, n=nres(m)
static void nres_C25519_ct(const spint *m, spint *n) {
    const spint c[9] = {0x169000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u};
    modmul_C25519_ct(m, c, n);
}

// Convert n back to normal form, m=redc(n)
static void redc_C25519_ct(const spint *n, spint *m) {
    int i;
    spint c[9];
    c[0] = 1;
    for (i = 1; i < 9; i++) {
        c[i] = 0;
    }
    modmul_C25519_ct(n, c, m);
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

// Modular multiplication by an integer, c=a*b mod 2p
static void modmli_C25519_ct(const spint *a, int b, spint *c) {
    spint t[9];
    modint_C25519_ct(b, t);
    modmul_C25519_ct(a, t, c);
}

// Test for quadratic residue
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
    spint z[9] = {0xa0ea0b0u, 0x770d93au,  0xbf91e31u,  0x6300d5au, 0x1d7a72f4u,
                  0x4c9efdu,  0x1c2cad34u, 0x1009f83bu, 0x2b8324u};
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
    nres_C25519_ct(a, a);
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
