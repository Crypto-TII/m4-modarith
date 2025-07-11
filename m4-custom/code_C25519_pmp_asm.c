#include <stdint.h>
#include <stddef.h>

#define UMULL(rdlo, rdhi, rn, rm) asm volatile("umull %0, %1, %2, %3" : "=r"(rdlo), "=r"(rdhi) : "r"(rn), "r"(rm))
#define UMAAL(rdlo, rdhi, rn, rm) asm volatile("umaal %0, %1, %2, %3" : "+r"(rdlo), "+r"(rdhi) : "r"(rn), "r"(rm))
#define ADDS(rt, r1, r2) asm volatile("adds %0, %1, %2" : "+r"(rt) : "r"(r1), "r" (r2))
#define ADCS(rt, r1, r2) asm volatile("adcs %0, %1, %2" : "+r"(rt) : "r"(r1), "r" (r2))

#define spint uint32_t

#ifndef NOINLINE
#define NOINLINE __attribute__((noinline))
#endif

#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE __attribute__((always_inline))
#endif

ALWAYS_INLINE static int modfsb_C25519_ct(spint *a) {
    const spint p0 = 4294967277;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 4294967295;
    const spint p4 = 4294967295;
    const spint p5 = 4294967295;
    const spint p6 = 4294967295;
    const spint p7 = 2147483647;
    spint a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4], a5 = a[5], a6 = a[6], a7 = a[7];
    int r = 0;
    asm volatile(
        "subs   %[a0], %[a0], %[p0]\n"
        "sbcs   %[a1], %[a1], %[p1]\n"
        "sbcs   %[a2], %[a2], %[p2]\n"
        "sbcs   %[a3], %[a3], %[p3]\n"
        "sbcs   %[a4], %[a4], %[p4]\n"
        "sbcs   %[a5], %[a5], %[p5]\n"
        "sbcs   %[a6], %[a6], %[p6]\n"
        "sbcs   %[a7], %[a7], %[p7]\n"
        "itttt cs\n"
        "strdcs %[a0], %[a1], [%[a], #0]\n"
        "strdcs %[a2], %[a3], [%[a], #8]\n"
        "strdcs %[a4], %[a5], [%[a], #16]\n"
        "strdcs %[a6], %[a7], [%[a], #24]\n"
        "adc    %[r], %[r], %[r]\n"
        : [a0] "+&r" (a0), [a1] "+&r" (a1), [a2] "+&r" (a2), [a3] "+&r" (a3), [a4] "+&r" (a4), [a5] "+&r" (a5), [a6] "+&r" (a6), [a7] "+&r" (a7), [r] "+&r" (r)
        : [a] "r" (a), [p0] "rI" (p0), [p1] "rI" (p1), [p2] "rI" (p2), [p3] "rI" (p3), [p4] "rI" (p4), [p5] "rI" (p5), [p6] "rI" (p6), [p7] "rI" (p7)
        : "cc", "memory");

    return 1 - r;
}

ALWAYS_INLINE static void mul_C25519_ct(const spint *p, const spint *q, spint *r) {
    spint t0, t1, t2, t3, t4, a, b0, b1, b2, b3;
    b0 = q[0];
    b1 = q[1];
    b2 = q[2];
    b3 = q[3];
    asm volatile(
        ".p2align 2\n"
        "mov.w  %[t1], #0\n"
        "mov.w  %[t2], #0\n"
        "mov.w  %[t3], #0\n"
        "ldr.w   %[a], [%[p], #0]\n"
        "umull  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #4]\n"
        "str.w  %[t0], [%[r], #0]\n"
        "mov.w  %[t0], #0\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #8]\n"
        "str.w  %[t1], [%[r], #4]\n"
        "mov.w  %[t1], #0\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #12]\n"
        "str.w  %[t2], [%[r], #8]\n"
        "mov.w  %[t2], #0\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #16]\n"
        "str.w  %[t3], [%[r], #12]\n"
        "mov.w  %[t3], #0\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #20]\n"
        "str.w  %[t4], [%[r], #16]\n"
        "mov.w  %[t4], #0\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #24]\n"
        "str.w  %[t0], [%[r], #20]\n"
        "mov.w  %[t0], #0\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #28]\n"
        "str.w  %[t1], [%[r], #24]\n"
        "mov.w  %[t1], #0\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "str.w  %[t2], [%[r], #28]\n"
        "str.w  %[t3], [%[r], #32]\n"
        "str.w  %[t4], [%[r], #36]\n"
        "str.w  %[t0], [%[r], #40]\n"
        "str.w  %[t1], [%[r], #44]\n"
        : [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [t0] "=&r"(t0), [t1] "=&r"(t1), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = q[4];
    b1 = q[5];
    b2 = q[6];
    b3 = q[7];
    t0 = r[4];
    t1 = r[5];
    t2 = r[6];
    t3 = r[7];
    t4 = 0;
    asm volatile(
        ".p2align 2\n"
        "ldr.w   %[a], [%[p], #0]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #32]\n"
        "str.w  %[t0], [%[r], #16]\n"
        "mov.w  %[t0], #0\n"
        "adds.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #4]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #36]\n"
        "str.w  %[t1], [%[r], #20]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #8]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #40]\n"
        "str.w  %[t2], [%[r], #24]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #12]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #44]\n"
        "str.w  %[t3], [%[r], #28]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #16]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #20]\n"
        "str.w  %[t4], [%[r], #32]\n"
        "mov.w  %[t4], #0\n"
#ifdef __clang__
        "adcs   %[t3], %[t3], #0\n"
#else
        "adcs.w %[t3], %[t3], #0\n"
#endif
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #24]\n"
        "str.w  %[t0], [%[r], #36]\n"
        "mov.w  %[t0], #0\n"
#ifdef __clang__
        "adcs   %[t4], %[t4], #0\n"
#else
        "adcs.w %[t4], %[t4], #0\n"
#endif
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #28]\n"
        "str.w  %[t1], [%[r], #40]\n"
        "mov.w  %[t1], #0\n"
#ifdef __clang__
        "adcs   %[t0], %[t0], #0\n"
#else
        "adcs.w %[t0], %[t0], #0\n"
#endif
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
#ifdef __clang__
        "adcs   %[t1], %[t1], #0\n"
#else
        "adcs.w %[t1], %[t1], #0\n"
#endif
        "str.w  %[t2], [%[r], #44]\n"
        "str.w  %[t3], [%[r], #48]\n"
        "str.w  %[t4], [%[r], #52]\n"
        "str.w  %[t0], [%[r], #56]\n"
        "str.w  %[t1], [%[r], #60]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
}

ALWAYS_INLINE static void sqr_C25519_ct(const spint *p, spint *r) {
    spint t5, t6, t7, t8, t9, t10, t11, t12, t13, t14;
    spint T, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15;

    spint t, a0, a1, a2, a3, a4;

    T = 0;

    asm volatile(
        ".p2align 2\n"
        "ldr.w %[a0], [%[a]]\n"
        "ldr.w %[a1], [%[a], #4]\n"
        "umull  %[t], %[t8],  %[a0],  %[a1]\n"
        "umull %[T0], %[T1],  %[a0],  %[a0]\n"
        "umaal %[T1], %[T],   %[two], %[t]\n"
        "ldr.w %[a2], [%[a], #8]\n"
        "str.w %[T0], [%[res]]\n"
        "ldr.w %[a3], [%[a], #12]\n"
        "str.w %[T1], [%[res], #4]\n"
        "mov.w  %[t], #0\n"
        "umaal  %[t], %[t8],  %[a0],  %[a2]\n"
        "umull %[T0], %[T1],  %[a1],  %[a1]\n"
        "umaal %[T0], %[T],   %[two], %[t]\n"
        "umull  %[t], %[t10], %[a0],  %[a3]\n"
        "umaal  %[t], %[t8],  %[a1],  %[a2]\n"
        "umaal %[T1], %[T],   %[two], %[t]\n"
        "ldr.w %[a4], [%[a], #16]\n"
        "str.w %[T0], [%[res], #8]\n"
        "str.w %[T1], [%[res], #12]\n"
        "mov.w  %[t], #0\n"
        "umaal  %[t], %[t10], %[a0],  %[a4]\n"
        "umaal  %[t], %[t8],  %[a1],  %[a3]\n"
        "umull %[T0], %[T1],  %[a2],  %[a2]\n"
        "umaal %[T0], %[T],   %[two], %[t]\n"
        "str.w %[T0], [%[res], #16]\n"
        : [a0] "=&r"(a0), [a1] "=&r"(a1), [a2] "=&r"(a2), [a3] "=&r"(a3), [a4] "=&r"(a4), [t] "=&r"(t), [t8] "=&r"(t8),
          [t10] "=&r"(t10), [T0] "=&r"(T4), [T1] "=&r"(T5), [T] "+&r"(T)
        : [a] "r"(p), [res] "r"(r), [two] "r"(2)
        : "memory");


    spint a5 = p[5];
    UMULL(t5, t12, a0, a5);
    UMAAL(t5, t10, a1, a4);
    UMAAL(t5, t8,  a2, a3);
    UMAAL(T5, T,   2,  t5);
    r[5] = T5;

    t6 = 0;
    spint a6 = p[6];
    UMAAL(t6, t12, a0, a6);
    UMAAL(t6, t10, a1, a5);
    UMAAL(t6, t8,  a2, a4);
    UMULL(T6, T7,  a3, a3);
    UMAAL(T6, T,   2,  t6);
    r[6] = T6;

    spint a7 = p[7];
    UMULL(t7, t14, a0, a7);
    UMAAL(t7, t12, a1, a6);
    UMAAL(t7, t10, a2, a5);
    UMAAL(t7, t8,  a3, a4);
    UMAAL(T7, T,   2,  t7);
    r[7] = T7;

    UMAAL(t8, t14, a1, a7);
    UMAAL(t8, t12, a2, a6);
    UMAAL(t8, t10, a3, a5);
    UMULL(T8, T9,  a4, a4);
    UMAAL(T8, T,   2,  t8);
    r[8] = T8;

    t9 = 0;
    UMAAL(t9, t14, a2, a7);
    UMAAL(t9, t12, a3, a6);
    UMAAL(t9, t10, a4, a5);
    UMAAL(T9, T,   2,  t9);
    r[9] = T9;


    UMAAL(t10, t14, a3, a7);
    UMAAL(t10, t12, a4, a6);
    UMULL(T10, T11, a5, a5);
    UMAAL(T10, T,   2,  t10);
    r[10] = T10;

    t11 = 0;
    UMAAL(t11, t14, a4, a7);
    UMAAL(t11, t12, a5, a6);
    UMAAL(T11, T,   2,  t11);
    r[11] = T11;

    UMAAL(t12, t14, a5, a7);
    UMULL(T12, T13, a6, a6);
    UMAAL(T12, T,   2,  t12);
    r[12] = T12;

    t13 = 0;
    UMAAL(t13, t14, a6, a7);
    UMAAL(T13, T,   2,  t13);
    r[13] = T13;

    UMULL(T14, T15, a7, a7);
    UMAAL(T14, T,   2,  t14);
    r[14] = T14;

    T15 += T;
    r[15] = T15;
}

ALWAYS_INLINE static void modred_C25519_ct(const spint *c, spint *r) {
    spint t, t2, q, rH, cc = 0;

    rH = c[7];
    UMAAL(rH, cc, c[15], 19 << 1);

    cc = 19 * ((cc << 1) | (rH >> 31));
    rH &= 0x7fffffff;

    t = c[0];
    q = c[8];
    UMAAL(t, cc, q, 19 << 1);

    t2 = c[1];
    q = c[9];
    r[0] = t;
    UMAAL(t2, cc, q, 19 << 1);

    t = c[2];
    q = c[10];
    r[1] = t2;
    UMAAL(t, cc, q, 19 << 1);

    t2 = c[3];
    q = c[11];
    r[2] = t;
    UMAAL(t2, cc, q, 19 << 1);

    t = c[4];
    q = c[12];
    r[3] = t2;
    UMAAL(t, cc, q, 19 << 1);

    t2 = c[5];
    q = c[13];
    r[4] = t;
    UMAAL(t2, cc, q, 19 << 1);

    t = c[6];
    q = c[14];
    r[5] = t2;
    UMAAL(t, cc, q, 19 << 1);
    r[6] = t;

    r[7] = rH + cc;
}

inline static void modmul_C25519_ct(const spint *a, const spint *b, spint *res) {
    spint z[16];
    mul_C25519_ct(a, b, z);
    modred_C25519_ct(z, res);
}

ALWAYS_INLINE static void inner_modsqr_C25519_ct(const spint *a, spint *res) {
    spint z[16];
    sqr_C25519_ct(a, z);
    modred_C25519_ct(z, res);
}

inline static void modsqr_C25519_ct(const spint *a, spint *res) {
    inner_modsqr_C25519_ct(a, res);
}

inline static void modmli_C25519_ct(const spint *p, const spint q, spint *r) {
    spint t0, t1, t2, t3, t4, t5, t6, t7, t8, b;
    b = q - 1;
    t8 = 0;
    t0 = p[0];
    UMAAL(t0, t8, t0, b);

    t1 = p[1];
    r[0] = t0;
    UMAAL(t1, t8, t1, b);

    t2 = p[2];
    r[1] = t1;
    UMAAL(t2, t8, t2, b);

    t3 = p[3];
    r[2] = t2;
    UMAAL(t3, t8, t3, b);

    t4 = p[4];
    r[3] = t3;
    UMAAL(t4, t8, t4, b);

    t5 = p[5];
    r[4] = t4;
    UMAAL(t5, t8, t5, b);

    t6 = p[6];
    r[5] = t5;
    UMAAL(t6, t8, t6, b);

    t7 = p[7];
    r[6] = t6;
    UMAAL(t7, t8, t7, b);

    r[7] = t7;

    b = 0;
    spint c = 38;
    UMAAL(t0, b, t8, c);
    t8 = 0;
    asm volatile(
        ".p2align 2\n"
        "adds.w %[t1], %[t1], %[b]\n"
#ifdef __clang__
        "adcs   %[t2], %[t2], #0\n"
#else
        "adcs.w %[t2], %[t2], #0\n"
#endif
#ifdef __clang__
        "adcs   %[t3], %[t3], #0\n"
#else
        "adcs.w %[t3], %[t3], #0\n"
#endif
#ifdef __clang__
        "adcs   %[t4], %[t4], #0\n"
#else
        "adcs.w %[t4], %[t4], #0\n"
#endif
#ifdef __clang__
        "adcs   %[t5], %[t5], #0\n"
#else
        "adcs.w %[t5], %[t5], #0\n"
#endif
#ifdef __clang__
        "adcs   %[t6], %[t6], #0\n"
#else
        "adcs.w %[t6], %[t6], #0\n"
#endif
#ifdef __clang__
        "adcs   %[t7], %[t7], #0\n"
#else
        "adcs.w %[t7], %[t7], #0\n"
#endif
        "str.w  %[t1], [%[r], #4]\n"
        "str.w  %[t2], [%[r], #8]\n"
        "str.w  %[t3], [%[r], #12]\n"
        "str.w  %[t4], [%[r], #16]\n"
        "str.w  %[t5], [%[r], #20]\n"
        "str.w  %[t6], [%[r], #24]\n"
        "str.w  %[t7], [%[r], #28]\n"
#ifdef __clang__
        "adcs   %[t8], %[t8], #0\n"
#else
        "adcs.w %[t8], %[t8], #0\n"
#endif
        : [t1] "+&r" (t1), [t2] "+&r" (t2), [t3] "+&r" (t3),
          [t4] "+&r" (t4), [t5] "+&r" (t5), [t6] "+&r" (t6), [t7] "+&r" (t7), [t8] "+&r" (t8)
        : [b] "r" (b), [r] "r"(r)
        : "cc", "memory");
    b = 0;
    UMAAL(t0, b, t8, c);
    r[0] = t0;
}

ALWAYS_INLINE static void nres_C25519_ct(const spint *a, spint *b) {
    b[0] = a[0];
    b[1] = a[1];
    b[2] = a[2];
    b[3] = a[3];
    b[4] = a[4];
    b[5] = a[5];
    b[6] = a[6];
    b[7] = a[7];
}

ALWAYS_INLINE static void redc_C25519_ct(const spint *a, spint *b) {
    b[0] = a[0];
    b[1] = a[1];
    b[2] = a[2];
    b[3] = a[3];
    b[4] = a[4];
    b[5] = a[5];
    b[6] = a[6];
    b[7] = a[7];
    modfsb_C25519_ct(b);
    modfsb_C25519_ct(b);
}

inline static void modcmv_C25519_ct(int d, const spint *a, volatile spint *b) {
    spint c0, c1, s, t, aux;
    spint r = 0x5aa5a55a;
    c0 = (~d) & (r + 1);
    c1 = d + r;
    for (int i = 0; i < 8; i++) {
        s = a[i];
        t = b[i];
        b[i] = aux = c0 * t + c1 * s;
        b[i] = aux - r * (t + s);
    }
}

inline static void modcsw_C25519_ct(int d, volatile spint *a, volatile spint *b) {
    spint c0, c1, s, t, w, aux;
    spint r = 0x5aa5a55a;
    c0 = (~d) & (r + 1);
    c1 = d + r;
    for (int i = 0; i < 8; i++) {
        s = a[i];
        t = b[i];
        w = r * (t + s);
        b[i] = aux = c0 * t + c1 * s;
        b[i] = aux - w;
        a[i] = aux = c0 * s + c1 * t;
        a[i] = aux - w;
    }
}

inline static void modadd_C25519_ct(const spint *a, const spint *b, spint *res) {
    spint t = 0;
    spint a0, a1, a2, a3, a4, a5, a6, a7;
    spint b0, b1, b2, b3, b4, b5, b6, b7;
    a7 = a[7];
    b7 = b[7];
    UMAAL(a7, t, 1, b7);
    t = 19 * ((a7 >> 31) + (t << 1));
    a7 = a7 & 0x7fffffff;
    a0 = a[0];
    b0 = b[0];
    UMAAL(a0, t, 1, b0);
    res[0] = a0;
    a1 = a[1];
    b1 = b[1];
    UMAAL(a1, t, 1, b1);
    res[1] = a1;
    a2 = a[2];
    b2 = b[2];
    UMAAL(a2, t, 1, b2);
    res[2] = a2;
    a3 = a[3];
    b3 = b[3];
    UMAAL(a3, t, 1, b3);
    res[3] = a3;
    a4 = a[4];
    b4 = b[4];
    UMAAL(a4, t, 1, b4);
    res[4] = a4;
    a5 = a[5];
    b5 = b[5];
    UMAAL(a5, t, 1, b5);
    res[5] = a5;
    a6 = a[6];
    b6 = b[6];
    UMAAL(a6, t, 1, b6);
    res[6] = a6;
    UMAAL(a7, t, 0, 0);
    res[7] = a7;
}

ALWAYS_INLINE static void modsub_C25519_ct(const spint *a, const spint *b, spint *res) {
    spint a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4], a5 = a[5], a6 = a[6], a7 = a[7];
    spint t1, b_t = (spint)b, t2;
    asm volatile(
        ".p2align 2\n"
        "ldrd.w  %[t1], %[t2], [%[b_t], #0]\n"
        "subs.w  %[a0], %[a0], %[t1]\n"
        "sbcs.w  %[a1], %[a1], %[t2]\n"
        "ldrd.w  %[t1], %[t2], [%[b_t], #8]\n"
        "sbcs.w  %[a2], %[a2], %[t1]\n"
        "sbcs.w  %[a3], %[a3], %[t2]\n"
        "ldrd.w  %[t1], %[t2], [%[b_t], #16]\n"
        "sbcs.w  %[a4], %[a4], %[t1]\n"
        "sbcs.w  %[a5], %[a5], %[t2]\n"
        "ldrd.w  %[t1], %[t2], [%[b_t], #24]\n"
        "sbcs.w  %[a6], %[a6], %[t1]\n"
        "sbcs.w  %[a7], %[a7], %[t2]\n"
        "sbcs.w %[b_t], %[a7], %[a7]\n"
        "negs.w %[b_t], %[b_t]\n"
        "mvn.w   %[t1], #4294967295-4294967258\n"
        "mov.w   %[t2], #0\n"
        "umaal   %[a0], %[t2], %[b_t], %[t1]\n"
        "mov.w   %[t1], #-1\n"
        "umaal   %[a1], %[t2], %[b_t], %[t1]\n"
        "umaal   %[a2], %[t2], %[b_t], %[t1]\n"
        "umaal   %[a3], %[t2], %[b_t], %[t1]\n"
        "umaal   %[a4], %[t2], %[b_t], %[t1]\n"
        "umaal   %[a5], %[t2], %[b_t], %[t1]\n"
        "umaal   %[a6], %[t2], %[b_t], %[t1]\n"
        "umaal   %[a7], %[t2], %[b_t], %[t1]\n"
        : [a0] "+&r" (a0), [a1] "+&r" (a1), [a2] "+&r" (a2), [a3] "+&r" (a3), [a4] "+&r" (a4), [a5] "+&r" (a5), [a6] "+&r" (a6), [a7] "+&r" (a7),
          [t1] "=&r" (t1), [b_t] "+&r" (b_t), [t2] "=&r" (t2)
        :
        : "cc");

    res[0] = a0;
    res[1] = a1;
    res[2] = a2;
    res[3] = a3;
    res[4] = a4;
    res[5] = a5;
    res[6] = a6;
    res[7] = a7;
}

inline static void modneg_C25519_ct(const spint *a, spint *r) {
    spint zero[8] = {0};
    modsub_C25519_ct(zero, a, r);
}

ALWAYS_INLINE static void modshl_C25519_ct(int n, spint *a) {
#if 1
#pragma GCC unroll 7
    for (int i = 7; i > 0; i--) {
        a[i] = (a[i] << n) + (a[i - 1] >> (32 - n));
    }
#else
    a[7] = (a[7] << n) + (a[6] >> (32 - n));
    a[6] = (a[6] << n) + (a[5] >> (32 - n));
    a[5] = (a[5] << n) + (a[4] >> (32 - n));
    a[4] = (a[4] << n) + (a[3] >> (32 - n));
    a[3] = (a[3] << n) + (a[2] >> (32 - n));
    a[2] = (a[2] << n) + (a[1] >> (32 - n));
    a[1] = (a[1] << n) + (a[0] >> (32 - n));
#endif
    a[0] = (a[0] << n);
}

// Only works for n <= 31
ALWAYS_INLINE static spint modshr_C25519_ct(int n, spint *a) {
    spint r = a[0] & ((1 << n) - 1);
#pragma GCC unroll 7
    for (int i = 0; i < 7; i++) {
        a[i] = (a[i] >> n) | (a[i + 1] << (32 - n));
    }
    a[7] = a[7] >> n;
    return r;
}

inline static void modcpy_C25519_ct(const spint *a, spint *b) {
#pragma GCC unroll 8
    for (int i = 0; i < 8; i++) {
        b[i] = a[i];
    }
}

ALWAYS_INLINE static int modis0_C25519_ct(const spint *a) {
    spint c[8] = {0};
    spint d = 0;
    modcpy_C25519_ct(a, c);
    modfsb_C25519_ct(c);
    for (int i = 0; i < 8; i++) {
        d |= c[i];
    }
    return 1 - ((d | -d) >> 31);
}

ALWAYS_INLINE static int modis1_C25519_ct(const spint *a) {
    spint c[8] = {0};
    spint d = 0;
    redc_C25519_ct(a, c);
    c[0] = c[0] - 1;
    for (int i = 0; i < 8; i++) {
        d |= c[i];
    }
    return 1 - ((d | -d) >> 31);
}

ALWAYS_INLINE static int modcmp_C25519_ct(const spint *a, const spint *b) {
    spint c[8], d[8];
    int neq = 0;
    redc_C25519_ct(a, c);
    redc_C25519_ct(b, d);
    for (int i = 0; i < 8; i++) {
        neq |= c[i] ^ d[i];
    }
    neq = (neq | -neq) >> 31;
    return 1 - (neq & 1);
}

ALWAYS_INLINE static int modsign_C25519_ct(const spint *a) {
    spint c[8];
    redc_C25519_ct(a, c);
    return c[0] % 2;
}

static void modnsqr_C25519_ct(spint *a, int n) {
    for (int i = 0; i < n; i++) {
        inner_modsqr_C25519_ct(a, a);
    }
}

// Calculate progenitor
NOINLINE static void modpro_C25519_ct(const spint *w, spint *z) {
    spint x[8];
    spint t0[8];
    spint t1[8];
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

// Test for quadratic residue, provide progenitor h if available, NULL if not
inline static int modqr_C25519_ct(const spint *h, const spint *x) {
    spint r[8];
    if (h == NULL) {
        modpro_C25519_ct(x, r);
        modsqr_C25519_ct(r, r);
    }
    else {
        modsqr_C25519_ct(h, r);
    }
    modmul_C25519_ct(r, x, r);
    modnsqr_C25519_ct(r, 1);
    return modis1_C25519_ct(r);
}

// Modular square root, provide progenitor h if available, NULL if not
inline static void modsqrt_C25519_ct(const spint *x, const spint *h, spint *r) {
    spint t[8];
    spint b[8];
    spint v[8];
    spint z[8] = {0x4a0ea0b0u, 0xc4ee1b27u, 0xad2fe478u, 0x2f431806u, 0x3dfbd7a7u, 0x2b4d0099u, 0x4fc1df0bu, 0x2b832480u};
    spint s[8];
    spint y[8];
    if (h == NULL) {
        modpro_C25519_ct(x, y);
    }
    else {
        modcpy_C25519_ct(h, y);
    }
    modmul_C25519_ct(y, x, s);
    modmul_C25519_ct(s, y, t);
    nres_C25519_ct(z, z);
    for (int k = 2; k > 1; k--) {
        modcpy_C25519_ct(t, b);
        modnsqr_C25519_ct(b, k-2);
        int d = 1 - modis1_C25519_ct(b);
        modmul_C25519_ct(s, z, v);
        (void)modcmv_C25519_ct(d, v, s);
        modsqr_C25519_ct(z, z);
        modmul_C25519_ct(t, z, v);
        (void)modcmv_C25519_ct(d, v, t);
    }
    modcpy_C25519_ct(s, r);
}

// Calculate inverse, provide progenitor h if available
inline static void modinv_C25519_ct(const spint *x, const spint *h, spint *z) {
    spint s[8];
    spint t[8];
    if (h == NULL) {
        modpro_C25519_ct(x, t);
    }
    else {
        modcpy_C25519_ct(h, t);
    }
    modcpy_C25519_ct(x, s);
    for (int i = 0; i < (1); i++) {
        modsqr_C25519_ct(s, s);
        modmul_C25519_ct(s, x, s);
    }
    modnsqr_C25519_ct(t, 3);
    modmul_C25519_ct(s, t, z);
}

inline static void modzer_C25519_ct(spint *a) {
#pragma GCC unroll 8
    for (int i = 0; i < 8; i++) {
        a[i] = 0;
    }
}

inline static void modone_C25519_ct(spint *a) {
    a[0] = 1;
#pragma GCC unroll 7
    for (int i = 1; i < 8; i++) {
        a[i] = 0;
    }
}

inline static void modint_C25519_ct(int x, spint *a) {
    a[0] = (spint)x;
#pragma GCC unroll 7
    for (int i = 1; i < 8; i++) {
        a[i] = 0;
    }
}

ALWAYS_INLINE static void mod2r_C25519_ct(unsigned int r, spint *a) {
    unsigned int n = r >> 5;
    unsigned int m = r & 31;
    modzer_C25519_ct(a);
    if (r >= 256) {
        return;
    }
    a[n] = 1 << m;
    nres_C25519_ct(a, a);
}

inline static void modimp_C25519_ct(const char *b, spint *a) {
    const spint *b32 = (const spint *)b;
#pragma GCC unroll 8
    for (int i = 0; i < 8; i++) {
        a[i] = __builtin_bswap32(b32[7 - i]);
    }
}

// Code for export, not exponentiation
inline static void modexp_C25519_ct(const spint *a, char *b) {
    spint c[8], *b32 = (spint *)b;
    redc_C25519_ct(a, c);
#pragma GCC unroll 8
    for (int i = 0; i < 8; i++) {
        b32[7 - i] = __builtin_bswap32(c[i]);
    }
}

#define Nlimbs_C25519_ct 8
#define Nbits_C25519_ct  255
#define Nbytes_C25519_ct 32
