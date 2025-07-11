
// Automatically generated modular arithmetic C code
// Python Script by Mike Scott (Technology Innovation Institute, UAE, 2025)

#include <stdint.h>
#include <stdio.h>

#define sspint int32_t
#define spint uint32_t
#define udpint uint64_t
#define dpint uint64_t

#define Wordlength_NIST256_ct 32
#define Nlimbs_NIST256_ct 9
#define Radix_NIST256_ct 29
#define Nbits_NIST256_ct 256
#define Nbytes_NIST256_ct 32

#define MONTGOMERY
#define NIST256

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
    n[0] -= (spint)1u & carry;
    n[3] += ((spint)0x200u) & carry;
    n[6] += ((spint)0x40000u) & carry;
    n[7] += ((spint)0x1fe00000u) & carry;
    n[8] += ((spint)0xffffffu) & carry;
    (void)prop(n);
    return (int)(carry & 1);
}

// Montgomery final subtract
static int modfsb_NIST256_ct(spint *n) {
    n[0] += (spint)1u;
    n[3] -= (spint)0x200u;
    n[6] -= (spint)0x40000u;
    n[7] -= (spint)0x1fe00000u;
    n[8] -= (spint)0xffffffu;
    return flatten(n);
}

// Modular addition - reduce less than 2p
static void modadd_NIST256_ct(const spint *a, const spint *b, spint *n) {
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
    n[0] += (spint)2u;
    n[3] -= (spint)0x400u;
    n[6] -= (spint)0x80000u;
    n[7] -= (spint)0x3fc00000u;
    n[8] -= (spint)0x1fffffeu;
    carry = prop(n);
    n[0] -= (spint)2u & carry;
    n[3] += ((spint)0x400u) & carry;
    n[6] += ((spint)0x80000u) & carry;
    n[7] += ((spint)0x3fc00000u) & carry;
    n[8] += ((spint)0x1fffffeu) & carry;
    (void)prop(n);
}

// Modular subtraction - reduce less than 2p
static void modsub_NIST256_ct(const spint *a, const spint *b, spint *n) {
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
    n[0] -= (spint)2u & carry;
    n[3] += ((spint)0x400u) & carry;
    n[6] += ((spint)0x80000u) & carry;
    n[7] += ((spint)0x3fc00000u) & carry;
    n[8] += ((spint)0x1fffffeu) & carry;
    (void)prop(n);
}

// Modular negation
static void modneg_NIST256_ct(const spint *b, spint *n) {
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
    n[0] -= (spint)2u & carry;
    n[3] += ((spint)0x400u) & carry;
    n[6] += ((spint)0x80000u) & carry;
    n[7] += ((spint)0x3fc00000u) & carry;
    n[8] += ((spint)0x1fffffeu) & carry;
    (void)prop(n);
}

// Overflow limit   = 18446744073709551616
// maximum possible = 2890326096838655498
// Modular multiplication, c=a*b mod 2p
static void modmul_NIST256_ct(const spint *a, const spint *b, spint *c) {
    dpint t = 0;
    spint p7 = 0x1fe00000u;
    spint p8 = 0xffffffu;
    spint q = ((spint)1 << 29u);  // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    t += (dpint)a[0] * b[0];
    spint v0 = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[0] * b[1];
    t += (dpint)a[1] * b[0];
    spint v1 = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[0] * b[2];
    t += (dpint)a[1] * b[1];
    t += (dpint)a[2] * b[0];
    spint v2 = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[0] * b[3];
    t += (dpint)a[1] * b[2];
    t += (dpint)a[2] * b[1];
    t += (dpint)a[3] * b[0];
    t += (dpint)(udpint)((udpint)v0 << 9u);
    spint v3 = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[0] * b[4];
    t += (dpint)a[1] * b[3];
    t += (dpint)a[2] * b[2];
    t += (dpint)a[3] * b[1];
    t += (dpint)a[4] * b[0];
    t += (dpint)(udpint)((udpint)v1 << 9u);
    spint v4 = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[0] * b[5];
    t += (dpint)a[1] * b[4];
    t += (dpint)a[2] * b[3];
    t += (dpint)a[3] * b[2];
    t += (dpint)a[4] * b[1];
    t += (dpint)a[5] * b[0];
    t += (dpint)(udpint)((udpint)v2 << 9u);
    spint v5 = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[0] * b[6];
    t += (dpint)a[1] * b[5];
    t += (dpint)a[2] * b[4];
    t += (dpint)a[3] * b[3];
    t += (dpint)a[4] * b[2];
    t += (dpint)a[5] * b[1];
    t += (dpint)a[6] * b[0];
    t += (dpint)(udpint)((udpint)v0 << 18u);
    t += (dpint)(udpint)((udpint)v3 << 9u);
    spint v6 = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[0] * b[7];
    t += (dpint)a[1] * b[6];
    t += (dpint)a[2] * b[5];
    t += (dpint)a[3] * b[4];
    t += (dpint)a[4] * b[3];
    t += (dpint)a[5] * b[2];
    t += (dpint)a[6] * b[1];
    t += (dpint)a[7] * b[0];
    t += (dpint)v0 * (dpint)p7;
    t += (dpint)(udpint)((udpint)v1 << 18u);
    t += (dpint)(udpint)((udpint)v4 << 9u);
    spint v7 = ((spint)t & mask);
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
    t += (dpint)v0 * (dpint)p8;
    t += (dpint)v1 * (dpint)p7;
    t += (dpint)(udpint)((udpint)v2 << 18u);
    t += (dpint)(udpint)((udpint)v5 << 9u);
    spint v8 = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[1] * b[8];
    t += (dpint)a[2] * b[7];
    t += (dpint)a[3] * b[6];
    t += (dpint)a[4] * b[5];
    t += (dpint)a[5] * b[4];
    t += (dpint)a[6] * b[3];
    t += (dpint)a[7] * b[2];
    t += (dpint)a[8] * b[1];
    t += (dpint)v1 * (dpint)p8;
    t += (dpint)v2 * (dpint)p7;
    t += (dpint)(udpint)((udpint)v3 << 18u);
    t += (dpint)(udpint)((udpint)v6 << 9u);
    c[0] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[2] * b[8];
    t += (dpint)a[3] * b[7];
    t += (dpint)a[4] * b[6];
    t += (dpint)a[5] * b[5];
    t += (dpint)a[6] * b[4];
    t += (dpint)a[7] * b[3];
    t += (dpint)a[8] * b[2];
    t += (dpint)v2 * (dpint)p8;
    t += (dpint)v3 * (dpint)p7;
    t += (dpint)(udpint)((udpint)v4 << 18u);
    t += (dpint)(udpint)((udpint)v7 << 9u);
    c[1] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[3] * b[8];
    t += (dpint)a[4] * b[7];
    t += (dpint)a[5] * b[6];
    t += (dpint)a[6] * b[5];
    t += (dpint)a[7] * b[4];
    t += (dpint)a[8] * b[3];
    t += (dpint)v3 * (dpint)p8;
    t += (dpint)v4 * (dpint)p7;
    t += (dpint)(udpint)((udpint)v5 << 18u);
    t += (dpint)(udpint)((udpint)v8 << 9u);
    c[2] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[4] * b[8];
    t += (dpint)a[5] * b[7];
    t += (dpint)a[6] * b[6];
    t += (dpint)a[7] * b[5];
    t += (dpint)a[8] * b[4];
    t += (dpint)v4 * (dpint)p8;
    t += (dpint)v5 * (dpint)p7;
    t += (dpint)(udpint)((udpint)v6 << 18u);
    c[3] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[5] * b[8];
    t += (dpint)a[6] * b[7];
    t += (dpint)a[7] * b[6];
    t += (dpint)a[8] * b[5];
    t += (dpint)v5 * (dpint)p8;
    t += (dpint)v6 * (dpint)p7;
    t += (dpint)(udpint)((udpint)v7 << 18u);
    c[4] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[6] * b[8];
    t += (dpint)a[7] * b[7];
    t += (dpint)a[8] * b[6];
    t += (dpint)v6 * (dpint)p8;
    t += (dpint)v7 * (dpint)p7;
    t += (dpint)(udpint)((udpint)v8 << 18u);
    c[5] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[7] * b[8];
    t += (dpint)a[8] * b[7];
    t += (dpint)v7 * (dpint)p8;
    t += (dpint)v8 * (dpint)p7;
    c[6] = ((spint)t & mask);
    t >>= 29;
    t += (dpint)a[8] * b[8];
    t += (dpint)v8 * (dpint)p8;
    c[7] = ((spint)t & mask);
    t >>= 29;
    c[8] = (spint)t;
}

// Modular squaring, c=a*a  mod 2p
static void modsqr_NIST256_ct(const spint *a, spint *c) {
    udpint tot;
    udpint t = 0;
    spint p7 = 0x1fe00000u;
    spint p8 = 0xffffffu;
    spint q = ((spint)1 << 29u);  // q is unsaturated radix
    spint mask = (spint)(q - (spint)1);
    tot = (udpint)a[0] * a[0];
    t = tot;
    spint v0 = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[0] * a[1];
    tot *= 2;
    t += tot;
    spint v1 = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[0] * a[2];
    tot *= 2;
    tot += (udpint)a[1] * a[1];
    t += tot;
    spint v2 = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[0] * a[3];
    tot += (udpint)a[1] * a[2];
    tot *= 2;
    t += tot;
    t += (udpint)v0 << 9u;
    spint v3 = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[0] * a[4];
    tot += (udpint)a[1] * a[3];
    tot *= 2;
    tot += (udpint)a[2] * a[2];
    t += tot;
    t += (udpint)v1 << 9u;
    spint v4 = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[0] * a[5];
    tot += (udpint)a[1] * a[4];
    tot += (udpint)a[2] * a[3];
    tot *= 2;
    t += tot;
    t += (udpint)v2 << 9u;
    spint v5 = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[0] * a[6];
    tot += (udpint)a[1] * a[5];
    tot += (udpint)a[2] * a[4];
    tot *= 2;
    tot += (udpint)a[3] * a[3];
    t += tot;
    t += (udpint)v0 << 18u;
    t += (udpint)v3 << 9u;
    spint v6 = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[0] * a[7];
    tot += (udpint)a[1] * a[6];
    tot += (udpint)a[2] * a[5];
    tot += (udpint)a[3] * a[4];
    tot *= 2;
    t += tot;
    t += (udpint)v0 * p7;
    t += (udpint)v1 << 18u;
    t += (udpint)v4 << 9u;
    spint v7 = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[0] * a[8];
    tot += (udpint)a[1] * a[7];
    tot += (udpint)a[2] * a[6];
    tot += (udpint)a[3] * a[5];
    tot *= 2;
    tot += (udpint)a[4] * a[4];
    t += tot;
    t += (udpint)v0 * p8;
    t += (udpint)v1 * p7;
    t += (udpint)v2 << 18u;
    t += (udpint)v5 << 9u;
    spint v8 = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[1] * a[8];
    tot += (udpint)a[2] * a[7];
    tot += (udpint)a[3] * a[6];
    tot += (udpint)a[4] * a[5];
    tot *= 2;
    t += tot;
    t += (udpint)v1 * p8;
    t += (udpint)v2 * p7;
    t += (udpint)v3 << 18u;
    t += (udpint)v6 << 9u;
    c[0] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[2] * a[8];
    tot += (udpint)a[3] * a[7];
    tot += (udpint)a[4] * a[6];
    tot *= 2;
    tot += (udpint)a[5] * a[5];
    t += tot;
    t += (udpint)v2 * p8;
    t += (udpint)v3 * p7;
    t += (udpint)v4 << 18u;
    t += (udpint)v7 << 9u;
    c[1] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[3] * a[8];
    tot += (udpint)a[4] * a[7];
    tot += (udpint)a[5] * a[6];
    tot *= 2;
    t += tot;
    t += (udpint)v3 * p8;
    t += (udpint)v4 * p7;
    t += (udpint)v5 << 18u;
    t += (udpint)v8 << 9u;
    c[2] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[4] * a[8];
    tot += (udpint)a[5] * a[7];
    tot *= 2;
    tot += (udpint)a[6] * a[6];
    t += tot;
    t += (udpint)v4 * p8;
    t += (udpint)v5 * p7;
    t += (udpint)v6 << 18u;
    c[3] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[5] * a[8];
    tot += (udpint)a[6] * a[7];
    tot *= 2;
    t += tot;
    t += (udpint)v5 * p8;
    t += (udpint)v6 * p7;
    t += (udpint)v7 << 18u;
    c[4] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[6] * a[8];
    tot *= 2;
    tot += (udpint)a[7] * a[7];
    t += tot;
    t += (udpint)v6 * p8;
    t += (udpint)v7 * p7;
    t += (udpint)v8 << 18u;
    c[5] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[7] * a[8];
    tot *= 2;
    t += tot;
    t += (udpint)v7 * p8;
    t += (udpint)v8 * p7;
    c[6] = ((spint)t & mask);
    t >>= 29;
    tot = (udpint)a[8] * a[8];
    t += tot;
    t += (udpint)v8 * p8;
    c[7] = ((spint)t & mask);
    t >>= 29;
    c[8] = (spint)t;
}

// copy
static void modcpy_NIST256_ct(const spint *a, spint *c) {
    int i;
    for (i = 0; i < 9; i++) {
        c[i] = a[i];
    }
}

// square n times
static void modnsqr_NIST256_ct(spint *a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        modsqr_NIST256_ct(a, a);
    }
}

// Calculate progenitor
static void modpro_NIST256_ct(const spint *w, spint *z) {
    spint x[9];
    spint t0[9];
    spint t1[9];
    modcpy_NIST256_ct(w, x);
    modsqr_NIST256_ct(x, z);
    modmul_NIST256_ct(x, z, z);
    modsqr_NIST256_ct(z, z);
    modmul_NIST256_ct(x, z, z);
    modcpy_NIST256_ct(z, t0);
    modnsqr_NIST256_ct(t0, 3);
    modmul_NIST256_ct(z, t0, t0);
    modcpy_NIST256_ct(t0, t1);
    modnsqr_NIST256_ct(t1, 6);
    modmul_NIST256_ct(t0, t1, t0);
    modnsqr_NIST256_ct(t0, 3);
    modmul_NIST256_ct(z, t0, z);
    modsqr_NIST256_ct(z, t0);
    modmul_NIST256_ct(x, t0, t0);
    modcpy_NIST256_ct(t0, t1);
    modnsqr_NIST256_ct(t1, 16);
    modmul_NIST256_ct(t0, t1, t0);
    modnsqr_NIST256_ct(t0, 15);
    modmul_NIST256_ct(z, t0, z);
    modnsqr_NIST256_ct(t0, 17);
    modmul_NIST256_ct(x, t0, t0);
    modnsqr_NIST256_ct(t0, 143);
    modmul_NIST256_ct(z, t0, t0);
    modnsqr_NIST256_ct(t0, 47);
    modmul_NIST256_ct(z, t0, z);
}

// calculate inverse, provide progenitor h if available
static void modinv_NIST256_ct(const spint *x, const spint *h, spint *z) {
    spint s[9];
    spint t[9];
    if (h == NULL) {
        modpro_NIST256_ct(x, t);
    }
    else {
        modcpy_NIST256_ct(h, t);
    }
    modcpy_NIST256_ct(x, s);
    modnsqr_NIST256_ct(t, 2);
    modmul_NIST256_ct(s, t, z);
}

// Convert m to n-residue form, n=nres(m)
static void nres_NIST256_ct(const spint *m, spint *n) {
    const spint c[9] = {0xc00u,      0x0u,        0x1fff0000u, 0x1fdfffffu, 0x1fbfffffu,
                        0x1fffffffu, 0x1fffffffu, 0x1ffffffeu, 0x13u};
    modmul_NIST256_ct(m, c, n);
}

// Convert n back to normal form, m=redc(n)
static void redc_NIST256_ct(const spint *n, spint *m) {
    int i;
    spint c[9];
    c[0] = 1;
    for (i = 1; i < 9; i++) {
        c[i] = 0;
    }
    modmul_NIST256_ct(n, c, m);
    (void)modfsb_NIST256_ct(m);
}

// is unity?
static int modis1_NIST256_ct(const spint *a) {
    int i;
    spint c[9];
    spint c0;
    spint d = 0;
    redc_NIST256_ct(a, c);
    for (i = 1; i < 9; i++) {
        d |= c[i];
    }
    c0 = (spint)c[0];
    return ((spint)1 & ((d - (spint)1) >> 29u) & (((c0 ^ (spint)1) - (spint)1) >> 29u));
}

// is zero?
static int modis0_NIST256_ct(const spint *a) {
    int i;
    spint c[9];
    spint d = 0;
    redc_NIST256_ct(a, c);
    for (i = 0; i < 9; i++) {
        d |= c[i];
    }
    return ((spint)1 & ((d - (spint)1) >> 29u));
}

// set to zero
static void modzer_NIST256_ct(spint *a) {
    int i;
    for (i = 0; i < 9; i++) {
        a[i] = 0;
    }
}

// set to one
static void modone_NIST256_ct(spint *a) {
    int i;
    a[0] = 1;
    for (i = 1; i < 9; i++) {
        a[i] = 0;
    }
    nres_NIST256_ct(a, a);
}

// set to integer
static void modint_NIST256_ct(int x, spint *a) {
    int i;
    a[0] = (spint)x;
    for (i = 1; i < 9; i++) {
        a[i] = 0;
    }
    nres_NIST256_ct(a, a);
}

// Modular multiplication by an integer, c=a*b mod 2p
static void modmli_NIST256_ct(const spint *a, int b, spint *c) {
    spint t[9];
    modint_NIST256_ct(b, t);
    modmul_NIST256_ct(a, t, c);
}

// Test for quadratic residue
static int modqr_NIST256_ct(const spint *h, const spint *x) {
    spint r[9];
    if (h == NULL) {
        modpro_NIST256_ct(x, r);
        modsqr_NIST256_ct(r, r);
    }
    else {
        modsqr_NIST256_ct(h, r);
    }
    modmul_NIST256_ct(r, x, r);
    return modis1_NIST256_ct(r) | modis0_NIST256_ct(x);
}

// conditional move g to f if d=1
// strongly recommend inlining be disabled using compiler specific syntax
static void modcmv_NIST256_ct(int b, const spint *g, volatile spint *f) {
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
static void modcsw_NIST256_ct(int b, volatile spint *g, volatile spint *f) {
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
static void modsqrt_NIST256_ct(const spint *x, const spint *h, spint *r) {
    spint s[9];
    spint y[9];
    if (h == NULL) {
        modpro_NIST256_ct(x, y);
    }
    else {
        modcpy_NIST256_ct(h, y);
    }
    modmul_NIST256_ct(y, x, s);
    modcpy_NIST256_ct(s, r);
}

// shift left by less than a word
static void modshl_NIST256_ct(unsigned int n, spint *a) {
    int i;
    a[8] = ((a[8] << n)) | (a[7] >> (29u - n));
    for (i = 7; i > 0; i--) {
        a[i] = ((a[i] << n) & (spint)0x1fffffff) | (a[i - 1] >> (29u - n));
    }
    a[0] = (a[0] << n) & (spint)0x1fffffff;
}

// shift right by less than a word. Return shifted out part
static int modshr_NIST256_ct(unsigned int n, spint *a) {
    int i;
    spint r = a[0] & (((spint)1 << n) - (spint)1);
    for (i = 0; i < 8; i++) {
        a[i] = (a[i] >> n) | ((a[i + 1] << (29u - n)) & (spint)0x1fffffff);
    }
    a[8] = a[8] >> n;
    return r;
}

// set a= 2^r
static void mod2r_NIST256_ct(unsigned int r, spint *a) {
    unsigned int n = r / 29u;
    unsigned int m = r % 29u;
    modzer_NIST256_ct(a);
    if (r >= 32 * 8) return;
    a[n] = 1;
    a[n] <<= m;
    nres_NIST256_ct(a, a);
}

// export to byte array
static void modexp_NIST256_ct(const spint *a, char *b) {
    int i;
    spint c[9];
    redc_NIST256_ct(a, c);
    for (i = 31; i >= 0; i--) {
        b[i] = c[0] & (spint)0xff;
        (void)modshr_NIST256_ct(8, c);
    }
}

// import from byte array
// returns 1 if in range, else 0
static int modimp_NIST256_ct(const char *b, spint *a) {
    int i, res;
    for (i = 0; i < 9; i++) {
        a[i] = 0;
    }
    for (i = 0; i < 32; i++) {
        modshl_NIST256_ct(8, a);
        a[0] += (spint)(unsigned char)b[i];
    }
    res = modfsb_NIST256_ct(a);
    nres_NIST256_ct(a, a);
    return res;
}

// determine sign
static int modsign_NIST256_ct(const spint *a) {
    spint c[9];
    redc_NIST256_ct(a, c);
    return c[0] % 2;
}

// return true if equal
static int modcmp_NIST256_ct(const spint *a, const spint *b) {
    spint c[9], d[9];
    int i, eq = 1;
    redc_NIST256_ct(a, c);
    redc_NIST256_ct(b, d);
    for (i = 0; i < 9; i++) {
        eq &= (((c[i] ^ d[i]) - 1) >> 29) & 1;
    }
    return eq;
}
