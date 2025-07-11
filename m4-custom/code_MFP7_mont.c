#include <stdint.h>

#define UMULL(rdlo, rdhi, rn, rm) asm volatile("umull %0, %1, %2, %3" : "=r"(rdlo), "=r"(rdhi) : "r"(rn), "r"(rm))

#define UMAAL(rdlo, rdhi, rn, rm) asm volatile("umaal %0, %1, %2, %3" : "+r"(rdlo), "+r"(rdhi) : "r"(rn), "r"(rm))

#define ADDS(rt, r1, r2) asm volatile("adds %0, %1, %2" : "+r"(rt) : "r"(r1), "r"(r2))

#define ADCS(rt, r1, r2) asm volatile("adcs %0, %1, %2" : "+r"(rt) : "r"(r1), "r"(r2))

#define spint uint32_t

static void mul_MFP7_ct(const spint *p, const spint *q, spint *r) {
    spint t0, t1, t2, t3, t4, a, b0, b1, b2, b3;
    b0 = q[0];
    b1 = q[1];
    b2 = q[2];
    b3 = q[3];
    asm volatile(
        ".p2align 2\n"
        "mov.w  %[t1], #0 \n"
        "mov.w  %[t2], #0 \n"
        "mov.w  %[t3], #0 \n"
        "ldr.w   %[a], [%[p], #0] \n"
        "umull  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#4] \n"
        "str.w  %[t0], [%[r],#0] \n"
        "mov.w  %[t0], #0 \n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#8] \n"
        "str.w  %[t1], [%[r],#4] \n"
        "mov.w  %[t1], #0 \n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#12] \n"
        "str.w  %[t2], [%[r],#8] \n"
        "mov.w  %[t2], #0 \n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#16] \n"
        "str.w  %[t3], [%[r],#12] \n"
        "mov.w  %[t3], #0 \n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#20] \n"
        "str.w  %[t4], [%[r],#16] \n"
        "mov.w  %[t4], #0 \n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#24] \n"
        "str.w  %[t0], [%[r],#20] \n"
        "mov.w  %[t0], #0 \n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#28] \n"
        "str.w  %[t1], [%[r],#24] \n"
        "mov.w  %[t1], #0 \n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "str.w  %[t2], [%[r],#28] \n"
        "str.w  %[t3], [%[r],#32] \n"
        "str.w  %[t4], [%[r],#36] \n"
        "str.w  %[t0], [%[r],#40] \n"
        "str.w  %[t1], [%[r],#44] \n"
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
        "ldr.w   %[a], [%[p],#0] \n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#32] \n"
        "str.w  %[t0], [%[r],#16] \n"
        "mov.w  %[t0], #0 \n"
        "adds.w %[t4], %[a] \n"
        "ldr.w   %[a], [%[p],#4] \n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#36] \n"
        "str.w  %[t1], [%[r],#20] \n"
        "mov.w  %[t1], #0 \n"
        "adcs.w %[t0], %[a] \n"
        "ldr.w   %[a], [%[p],#8] \n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#40] \n"
        "str.w  %[t2], [%[r],#24] \n"
        "mov.w  %[t2], #0 \n"
        "adcs.w %[t1], %[a] \n"
        "ldr.w   %[a], [%[p],#12] \n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r],#44] \n"
        "str.w  %[t3], [%[r],#28] \n"
        "mov.w  %[t3], #0 \n"
        "adcs.w %[t2], %[a] \n"
        "ldr.w   %[a], [%[p],#16] \n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#20] \n"
        "str.w  %[t4], [%[r],#32] \n"
        "mov.w  %[t4], #0 \n"
        "adcs.w %[t3], #0\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#24] \n"
        "str.w  %[t0], [%[r],#36] \n"
        "mov.w  %[t0], #0 \n"
        "adcs.w %[t4], #0\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p],#28] \n"
        "str.w  %[t1], [%[r],#40] \n"
        "mov.w  %[t1], #0 \n"
        "adcs.w %[t0], #0\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "adcs.w %[t1], #0 \n"
        "str.w  %[t2], [%[r],#44] \n"
        "str.w  %[t3], [%[r],#48] \n"
        "str.w  %[t4], [%[r],#52] \n"
        "str.w  %[t0], [%[r],#56] \n"
        "str.w  %[t1], [%[r],#60] \n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
}

static void sqr_MFP7_ct(const spint *a, spint *res) {
    spint t5, t6, t7, t8, t9, t10, t11, t12, t13, t14;
    spint T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15;
    spint T;

    spint t, a0, a1, a2, a3, a4;

    T = 0;

    asm volatile(
        "ldr   %[a0], [%[a]]               \n"
        "ldr   %[a1], [%[a], #4]           \n"
        "ldr   %[a2], [%[a], #8]           \n"
        "ldr   %[a3], [%[a], #12]          \n"
        "ldr   %[a4], [%[a], #16]          \n"
        "umull %[t],  %[t8],  %[a0],  %[a1]\n"
        "umull %[T0], %[T1],  %[a0],  %[a0]\n"
        "umaal %[T1], %[T],   %[two], %[t] \n"
        "str   %[T0], [%[res]]             \n"
        "str   %[T1], [%[res], #4]         \n"
        "mov   %[t], #0                    \n"
        "umaal %[t],  %[t8],  %[a0],  %[a2]\n"
        "umull %[T0], %[T1],  %[a1],  %[a1]\n"
        "umaal %[T0], %[T],   %[two], %[t] \n"
        "umull %[t],  %[t10], %[a0],  %[a3]\n"
        "umaal %[t],  %[t8],  %[a1],  %[a2]\n"
        "umaal %[T1], %[T],   %[two], %[t] \n"
        "str   %[T0], [%[res], #8]         \n"
        "str   %[T1], [%[res], #12]        \n"
        "mov   %[t], #0                    \n"
        "umaal %[t],  %[t10], %[a0],  %[a4]\n"
        "umaal %[t],  %[t8],  %[a1],  %[a3]\n"
        "umull %[T0], %[T1],  %[a2],  %[a2]\n"
        "umaal %[T0], %[T],   %[two], %[t] \n"
        "str   %[T0], [%[res], #16]        \n"
        : [a0] "=&r"(a0), [a1] "=&r"(a1), [a2] "=&r"(a2), [a3] "=&r"(a3), [a4] "=&r"(a4), [t] "=&r"(t), [t8] "=&r"(t8),
          [t10] "=&r"(t10), [T0] "=&r"(T4), [T1] "=&r"(T5), [T] "+&r"(T)
        : [a] "r"(a), [res] "r"(res), [two] "r"(2));

    uint32_t a5 = a[5];
    UMULL(t5, t12, a0, a5);
    UMAAL(t5, t10, a1, a4);
    UMAAL(t5, t8, a2, a3);
    UMAAL(T5, T, 2, t5);
    res[5] = T5;

    t6 = 0;
    uint32_t a6 = a[6];
    UMAAL(t6, t12, a0, a6);
    UMAAL(t6, t10, a1, a5);
    UMAAL(t6, t8, a2, a4);
    UMULL(T6, T7, a3, a3);
    UMAAL(T6, T, 2, t6);
    res[6] = T6;

    uint32_t a7 = a[7];
    UMULL(t7, t14, a0, a7);
    UMAAL(t7, t12, a1, a6);
    UMAAL(t7, t10, a2, a5);
    UMAAL(t7, t8, a3, a4);
    UMAAL(T7, T, 2, t7);
    res[7] = T7;

    UMAAL(t8, t14, a1, a7);
    UMAAL(t8, t12, a2, a6);
    UMAAL(t8, t10, a3, a5);
    UMULL(T8, T9, a4, a4);
    UMAAL(T8, T, 2, t8);
    res[8] = T8;

    t9 = 0;
    UMAAL(t9, t14, a2, a7);
    UMAAL(t9, t12, a3, a6);
    UMAAL(t9, t10, a4, a5);
    UMAAL(T9, T, 2, t9);
    res[9] = T9;

    UMAAL(t10, t14, a3, a7);
    UMAAL(t10, t12, a4, a6);
    UMULL(T10, T11, a5, a5);
    UMAAL(T10, T, 2, t10);
    res[10] = T10;

    t11 = 0;
    UMAAL(t11, t14, a4, a7);
    UMAAL(t11, t12, a5, a6);
    UMAAL(T11, T, 2, t11);
    res[11] = T11;

    UMAAL(t12, t14, a5, a7);
    UMULL(T12, T13, a6, a6);
    UMAAL(T12, T, 2, t12);
    res[12] = T12;

    t13 = 0;
    UMAAL(t13, t14, a6, a7);
    UMAAL(T13, T, 2, t13);
    res[13] = T13;

    UMULL(T14, T15, a7, a7);
    UMAAL(T14, T, 2, t14);
    res[14] = T14;

    T15 += T;
    res[15] = T15;
}

static void modmul_MFP7_ct(const spint *a, const spint *b, spint *res) {
    spint A[16];
    spint A8, A9, A10, A11, A12, A13, A14, A15;
    const spint p4 = 3829006335, p5 = 1288340339, p6 = 2933633043, p7 = 815531196;
    spint t;

    mul_MFP7_ct(a, b, A);
    asm volatile(
        "ldr   %[A0_8],  [%[A], #0]\n"
        "ldr   %[A1_9],  [%[A], #4]\n"
        "ldr   %[A2_10], [%[A], #8]\n"
        "ldr   %[A3_11], [%[A], #12]\n"
        "ldr   %[A4_12], [%[A], #16]\n"
        "ldr   %[A5_13], [%[A], #20]\n"
        "ldr   %[A6_14], [%[A], #24]\n"
        "ldr   %[A7_15], [%[A], #28]\n"
        "mov   %[t],     #0\n"
        "umaal %[A4_12], %[t],     %[A0_8], %[p41]\n"
        "umaal %[A5_13], %[t],     %[A0_8], %[p5]\n"
        "umaal %[A6_14], %[t],     %[A0_8], %[p6]\n"
        "umaal %[A7_15], %[t],     %[A0_8], %[p7]\n"
        "ldr   %[A0_8],  [%[A], #32]\n"
        "adds  %[A0_8],  %[A0_8],  %[t]\n"
        "mov   %[t],     #0\n"
        "umaal %[A5_13], %[t],     %[A1_9], %[p41]\n"
        "umaal %[A6_14], %[t],     %[A1_9], %[p5]\n"
        "umaal %[A7_15], %[t],     %[A1_9], %[p6]\n"
        "umaal %[A0_8],  %[t],     %[A1_9], %[p7]\n"
        "ldr   %[A1_9],  [%[A], #36]\n"
        "adcs  %[A1_9],  %[A1_9],  %[t]\n"
        "mov   %[t],     #0\n"
        "umaal %[A6_14], %[t],     %[A2_10], %[p41]\n"
        "umaal %[A7_15], %[t],     %[A2_10], %[p5]\n"
        "umaal %[A0_8],  %[t],     %[A2_10], %[p6]\n"
        "umaal %[A1_9],  %[t],     %[A2_10], %[p7]\n"
        "ldr   %[A2_10], [%[A], #40]\n"
        "adcs  %[A2_10], %[A2_10], %[t]\n"
        "mov   %[t],     #0\n"
        "umaal %[A7_15], %[t],     %[A3_11], %[p41]\n"
        "umaal %[A0_8],  %[t],     %[A3_11], %[p5]\n"
        "umaal %[A1_9],  %[t],     %[A3_11], %[p6]\n"
        "umaal %[A2_10], %[t],     %[A3_11], %[p7]\n"
        "ldr   %[A3_11], [%[A], #44]\n"
        "adcs  %[A3_11], %[A3_11], %[t]\n"
        "mov   %[t],     #0\n"
        "umaal %[A0_8],  %[t],     %[A4_12], %[p41]\n"
        "umaal %[A1_9],  %[t],     %[A4_12], %[p5]\n"
        "umaal %[A2_10], %[t],     %[A4_12], %[p6]\n"
        "umaal %[A3_11], %[t],     %[A4_12], %[p7]\n"
        "ldr   %[A4_12], [%[A], #48]\n"
        "adcs  %[A4_12], %[A4_12], %[t]\n"
        "mov   %[t],     #0\n"
        "umaal %[A1_9],  %[t],     %[A5_13], %[p41]\n"
        "umaal %[A2_10], %[t],     %[A5_13], %[p5]\n"
        "umaal %[A3_11], %[t],     %[A5_13], %[p6]\n"
        "umaal %[A4_12], %[t],     %[A5_13], %[p7]\n"
        "ldr   %[A5_13], [%[A], #52]\n"
        "adcs  %[A5_13], %[A5_13], %[t]\n"
        "mov   %[t],     #0\n"
        "umaal %[A2_10], %[t],     %[A6_14], %[p41]\n"
        "umaal %[A3_11], %[t],     %[A6_14], %[p5]\n"
        "umaal %[A4_12], %[t],     %[A6_14], %[p6]\n"
        "umaal %[A5_13], %[t],     %[A6_14], %[p7]\n"
        "ldr   %[A6_14], [%[A], #56]\n"
        "adcs  %[A6_14], %[A6_14], %[t]\n"
        "mov   %[t],     #0\n"
        "umaal %[A3_11], %[t],     %[A7_15], %[p41]\n"
        "umaal %[A4_12], %[t],     %[A7_15], %[p5]\n"
        "umaal %[A5_13], %[t],     %[A7_15], %[p6]\n"
        "umaal %[A6_14], %[t],     %[A7_15], %[p7]\n"
        "ldr   %[A7_15], [%[A], #60]\n"
        "adcs  %[A7_15], %[A7_15], %[t]\n"
        : [A0_8] "=&r"(A8), [A1_9] "=&r"(A9), [A2_10] "=&r"(A10), [A3_11] "=&r"(A11), [A4_12] "=&r"(A12),
          [A5_13] "=&r"(A13), [A6_14] "=&r"(A14), [A7_15] "=&r"(A15), [t] "=&r"(t)
        : [A] "r"(A), [p41] "r"(p4 + 1), [p5] "r"(p5), [p6] "r"(p6), [p7] "r"(p7));

// Conditional subtraction (not needed for primes with 2bit slack from representation)
#if 0
    asm volatile(
        "str  %[res0], [%[res], #0]\n"
        "str  %[res1], [%[res], #4]\n"
        "str  %[res2], [%[res], #8]\n"
        "str  %[res3], [%[res], #12]\n"
        "str  %[res4], [%[res], #16]\n"
        "str  %[res5], [%[res], #20]\n"
        "str  %[res6], [%[res], #24]\n"
        "str  %[res7], [%[res], #28]\n"
        "subs %[res0], %[res0], #-1\n"
        "sbcs %[res1], %[res1], #-1\n"
        "sbcs %[res2], %[res2], #-1\n"
        "sbcs %[res3], %[res3], #-1\n"
        "sbcs %[res4], %[res4], %[p4]\n"
        "sbcs %[res5], %[res5], %[p5]\n"
        "sbcs %[res6], %[res6], %[p6]\n"
        "sbcs %[res7], %[res7], %[p7]\n"
        "itttt cs\n"
        "strdcs %[res0], %[res1], [%[res]]\n"
        "strdcs %[res2], %[res3], [%[res], #8]\n"
        "strdcs %[res4], %[res5], [%[res], #16]\n"
        "strdcs %[res6], %[res7], [%[res], #24]\n"
        : [res0] "+&r"(A8), [res1] "+&r"(A9), [res2] "+&r"(A10), [res3] "+&r"(A11), [res4] "+&r"(A12),
          [res5] "+&r"(A13), [res6] "+&r"(A14), [res7] "+&r"(A15)
        : [res] "r"(res), [p4] "r"(p4), [p5] "r"(p5), [p6] "r"(p6), [p7] "r"(p7));
#else
    asm volatile(
        "str  %[res0], [%[res], #0]\n"
        "str  %[res1], [%[res], #4]\n"
        "str  %[res2], [%[res], #8]\n"
        "str  %[res3], [%[res], #12]\n"
        "str  %[res4], [%[res], #16]\n"
        "str  %[res5], [%[res], #20]\n"
        "str  %[res6], [%[res], #24]\n"
        "str  %[res7], [%[res], #28]\n"
        :
        : [res0] "r"(A8), [res1] "r"(A9), [res2] "r"(A10), [res3] "r"(A11), [res4] "r"(A12), [res5] "r"(A13),
          [res6] "r"(A14), [res7] "r"(A15), [res] "r"(res));
#endif
}

static void modsqr_MFP7_ct(const spint *a, spint *res) {
    spint A[16];
    spint A8, A9, A10, A11, A12, A13, A14, A15;
    const spint p4 = 3829006335, p5 = 1288340339, p6 = 2933633043, p7 = 815531196;
    spint t;

    sqr_MFP7_ct(a, A);
    asm volatile(
        "ldr   %[A0_8],  [%[A], #0]\n"
        "ldr   %[A1_9],  [%[A], #4]\n"
        "ldr   %[A2_10], [%[A], #8]\n"
        "ldr   %[A3_11], [%[A], #12]\n"
        "ldr   %[A4_12], [%[A], #16]\n"
        "ldr   %[A5_13], [%[A], #20]\n"
        "ldr   %[A6_14], [%[A], #24]\n"
        "ldr   %[A7_15], [%[A], #28]\n"
        "mov   %[t],     #0\n"
        "umaal %[A4_12], %[t],     %[A0_8], %[p41]\n"
        "umaal %[A5_13], %[t],     %[A0_8], %[p5]\n"
        "umaal %[A6_14], %[t],     %[A0_8], %[p6]\n"
        "umaal %[A7_15], %[t],     %[A0_8], %[p7]\n"
        "ldr   %[A0_8],  [%[A], #32]\n"
        "adds  %[A0_8],  %[A0_8],  %[t]\n"
        "mov   %[t],     #0\n"
        "umaal %[A5_13], %[t],     %[A1_9], %[p41]\n"
        "umaal %[A6_14], %[t],     %[A1_9], %[p5]\n"
        "umaal %[A7_15], %[t],     %[A1_9], %[p6]\n"
        "umaal %[A0_8],  %[t],     %[A1_9], %[p7]\n"
        "ldr   %[A1_9],  [%[A], #36]\n"
        "adcs  %[A1_9],  %[A1_9],  %[t]\n"
        "mov   %[t],     #0\n"
        "umaal %[A6_14], %[t],     %[A2_10], %[p41]\n"
        "umaal %[A7_15], %[t],     %[A2_10], %[p5]\n"
        "umaal %[A0_8],  %[t],     %[A2_10], %[p6]\n"
        "umaal %[A1_9],  %[t],     %[A2_10], %[p7]\n"
        "ldr   %[A2_10], [%[A], #40]\n"
        "adcs  %[A2_10], %[A2_10], %[t]\n"
        "mov   %[t],     #0\n"
        "umaal %[A7_15], %[t],     %[A3_11], %[p41]\n"
        "umaal %[A0_8],  %[t],     %[A3_11], %[p5]\n"
        "umaal %[A1_9],  %[t],     %[A3_11], %[p6]\n"
        "umaal %[A2_10], %[t],     %[A3_11], %[p7]\n"
        "ldr   %[A3_11], [%[A], #44]\n"
        "adcs  %[A3_11], %[A3_11], %[t]\n"
        "mov   %[t],     #0\n"
        "umaal %[A0_8],  %[t],     %[A4_12], %[p41]\n"
        "umaal %[A1_9],  %[t],     %[A4_12], %[p5]\n"
        "umaal %[A2_10], %[t],     %[A4_12], %[p6]\n"
        "umaal %[A3_11], %[t],     %[A4_12], %[p7]\n"
        "ldr   %[A4_12], [%[A], #48]\n"
        "adcs  %[A4_12], %[A4_12], %[t]\n"
        "mov   %[t],     #0\n"
        "umaal %[A1_9],  %[t],     %[A5_13], %[p41]\n"
        "umaal %[A2_10], %[t],     %[A5_13], %[p5]\n"
        "umaal %[A3_11], %[t],     %[A5_13], %[p6]\n"
        "umaal %[A4_12], %[t],     %[A5_13], %[p7]\n"
        "ldr   %[A5_13], [%[A], #52]\n"
        "adcs  %[A5_13], %[A5_13], %[t]\n"
        "mov   %[t],     #0\n"
        "umaal %[A2_10], %[t],     %[A6_14], %[p41]\n"
        "umaal %[A3_11], %[t],     %[A6_14], %[p5]\n"
        "umaal %[A4_12], %[t],     %[A6_14], %[p6]\n"
        "umaal %[A5_13], %[t],     %[A6_14], %[p7]\n"
        "ldr   %[A6_14], [%[A], #56]\n"
        "adcs  %[A6_14], %[A6_14], %[t]\n"
        "mov   %[t],     #0\n"
        "umaal %[A3_11], %[t],     %[A7_15], %[p41]\n"
        "umaal %[A4_12], %[t],     %[A7_15], %[p5]\n"
        "umaal %[A5_13], %[t],     %[A7_15], %[p6]\n"
        "umaal %[A6_14], %[t],     %[A7_15], %[p7]\n"
        "ldr   %[A7_15], [%[A], #60]\n"
        "adcs  %[A7_15], %[A7_15], %[t]\n"
        : [A0_8] "=&r"(A8), [A1_9] "=&r"(A9), [A2_10] "=&r"(A10), [A3_11] "=&r"(A11), [A4_12] "=&r"(A12),
          [A5_13] "=&r"(A13), [A6_14] "=&r"(A14), [A7_15] "=&r"(A15), [t] "=&r"(t)
        : [A] "r"(A), [p41] "r"(p4 + 1), [p5] "r"(p5), [p6] "r"(p6), [p7] "r"(p7));

// Conditional subtraction (not needed for primes with 2bit slack from representation)
#if 0
    asm volatile(
        "str  %[res0], [%[res], #0]\n"
        "str  %[res1], [%[res], #4]\n"
        "str  %[res2], [%[res], #8]\n"
        "str  %[res3], [%[res], #12]\n"
        "str  %[res4], [%[res], #16]\n"
        "str  %[res5], [%[res], #20]\n"
        "str  %[res6], [%[res], #24]\n"
        "str  %[res7], [%[res], #28]\n"
        "subs %[res0], %[res0], #-1\n"
        "sbcs %[res1], %[res1], #-1\n"
        "sbcs %[res2], %[res2], #-1\n"
        "sbcs %[res3], %[res3], #-1\n"
        "sbcs %[res4], %[res4], %[p4]\n"
        "sbcs %[res5], %[res5], %[p5]\n"
        "sbcs %[res6], %[res6], %[p6]\n"
        "sbcs %[res7], %[res7], %[p7]\n"
        "itttt cs\n"
        "strdcs %[res0], %[res1], [%[res]]\n"
        "strdcs %[res2], %[res3], [%[res], #8]\n"
        "strdcs %[res4], %[res5], [%[res], #16]\n"
        "strdcs %[res6], %[res7], [%[res], #24]\n"
        : [res0] "+&r"(A8), [res1] "+&r"(A9), [res2] "+&r"(A10), [res3] "+&r"(A11), [res4] "+&r"(A12),
          [res5] "+&r"(A13), [res6] "+&r"(A14), [res7] "+&r"(A15)
        : [res] "r"(res), [p4] "r"(p4), [p5] "r"(p5), [p6] "r"(p6), [p7] "r"(p7));
#else
    asm volatile(
        "str  %[res0], [%[res], #0]\n"
        "str  %[res1], [%[res], #4]\n"
        "str  %[res2], [%[res], #8]\n"
        "str  %[res3], [%[res], #12]\n"
        "str  %[res4], [%[res], #16]\n"
        "str  %[res5], [%[res], #20]\n"
        "str  %[res6], [%[res], #24]\n"
        "str  %[res7], [%[res], #28]\n"
        :
        : [res0] "r"(A8), [res1] "r"(A9), [res2] "r"(A10), [res3] "r"(A11), [res4] "r"(A12), [res5] "r"(A13),
          [res6] "r"(A14), [res7] "r"(A15), [res] "r"(res));
#endif
}

static void modadd_MFP7_ct(const spint *a, const spint *b, spint *res) {
    // No longer passes tests, using generated code for now
    // spint a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4], a5 = a[5], a6 = a[6], a7 = a[7];
    // spint b0 = b[0], b1 = b[1], b2 = b[2], b3 = b[3], b4 = b[4], b5 = b[5], b6 = b[6], b7 = b[7];
    // spint res0, res1, res2, res3, res4, res5, res6, res7;
    // spint t = 0;
    // const spint p0 = 4294967295;
    // const spint p1 = 4294967295;
    // const spint p2 = 4294967295;
    // const spint p3 = 4294967295;
    // const spint p4 = 3829006335;
    // const spint p5 = 1288340339;
    // const spint p6 = 2933633043;
    // const spint p7 = 815531196;
    // UMAAL(a0, t, 1, b0);
    // UMAAL(a1, t, 1, b1);
    // UMAAL(a2, t, 1, b2);
    // UMAAL(a3, t, 1, b3);
    // UMAAL(a4, t, 1, b4);
    // UMAAL(a5, t, 1, b5);
    // UMAAL(a6, t, 1, b6);
    // UMAAL(a7, t, 1, b7);
    // res[0] = a0;
    // res0 = a0;
    // res[1] = a1;
    // res1 = a1;
    // res[2] = a2;
    // res2 = a2;
    // res[3] = a3;
    // res3 = a3;
    // res[4] = a4;
    // res4 = a4;
    // res[5] = a5;
    // res5 = a5;
    // res[6] = a6;
    // res6 = a6;
    // res[7] = a7;
    // res7 = a7;
    // asm volatile(
    //     "subs %[res0], %[res0], %[p0]\n"
    //     "sbcs %[res1], %[res1], %[p1]\n"
    //     "sbcs %[res2], %[res2], %[p2]\n"
    //     "sbcs %[res3], %[res3], %[p3]\n"
    //     "sbcs %[res4], %[res4], %[p4]\n"
    //     "sbcs %[res5], %[res5], %[p5]\n"
    //     "sbcs %[res6], %[res6], %[p6]\n"
    //     "sbcs %[res7], %[res7], %[p7]\n"
    //     "itttt cs\n"
    //     "strdcs %[res0], %[res1], [%[res]]\n"
    //     "strdcs %[res2], %[res3], [%[res], #8]\n"
    //     "strdcs %[res4], %[res5], [%[res], #16]\n"
    //     "strdcs %[res6], %[res7], [%[res], #24]\n"
    //     : [res0] "+&r"(res0), [res1] "+&r"(res1), [res2] "+&r"(res2), [res3] "+&r"(res3), [res4] "+&r"(res4),
    //       [res5] "+&r"(res5), [res6] "+&r"(res6), [res7] "+&r"(res7)
    //     : [res] "r"(res), [p0] "r"(p0), [p1] "r"(p1), [p2] "r"(p2), [p3] "r"(p3), [p4] "r"(p4), [p5] "r"(p5),
    //       [p6] "r"(p6), [p7] "r"(p7));

    spint a0, a1, a2, a3, a4, a5, a6, a7;
    spint b0, b1, b2, b3, b4, b5, b6, b7;
    spint t0, t1, t2, t3;
    spint tmpres[8];
    spint t = 0;
    const spint p[8] = {4294967294, 4294967295, 4294967295, 4294967295, 3363045375, 2576680679, 1572298790, 1631062393};
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
    a7 = a[7];
    b7 = b[7];
    UMAAL(a7, t, 1, b7);
    res[7] = a7;
    asm volatile(
        "ldr    %[t0], [%[res]]\n"
        "ldr    %[t1], [%[res], #4]\n"
        "ldr    %[t2], [%[p]]\n"
        "ldr    %[t3], [%[p], #4]\n"
        "subs   %[t0], %[t0], %[t2]\n"
        "sbcs   %[t1], %[t1], %[t3]\n"
        "str    %[t0], [%[tmpres]]\n"
        "str    %[t1], [%[tmpres], #4]\n"
        "ldr    %[t0], [%[res], #8]\n"
        "ldr    %[t1], [%[res], #12]\n"
        "ldr    %[t2], [%[p], #8]\n"
        "ldr    %[t3], [%[p], #12]\n"
        "sbcs   %[t0], %[t0], %[t2]\n"
        "sbcs   %[t1], %[t1], %[t3]\n"
        "str    %[t0], [%[tmpres], #8]\n"
        "str    %[t1], [%[tmpres], #12]\n"
        "ldr    %[t0], [%[res], #16]\n"
        "ldr    %[t1], [%[res], #20]\n"
        "ldr    %[t2], [%[p], #16]\n"
        "ldr    %[t3], [%[p], #20]\n"
        "sbcs   %[t0], %[t0], %[t2]\n"
        "sbcs   %[t1], %[t1], %[t3]\n"
        "str    %[t0], [%[tmpres], #16]\n"
        "str    %[t1], [%[tmpres], #20]\n"
        "ldr    %[t0], [%[res], #24]\n"
        "ldr    %[t1], [%[res], #28]\n"
        "ldr    %[t2], [%[p], #24]\n"
        "ldr    %[t3], [%[p], #28]\n"
        "sbcs   %[t0], %[t0], %[t2]\n"
        "sbcs   %[t1], %[t1], %[t3]\n"
        "str    %[t0], [%[tmpres], #24]\n"
        "str    %[t1], [%[tmpres], #28]\n"
        "itttt  cs\n"
        "ldrdcs %[t0], %[t1], [%[tmpres], #0]\n"
        "ldrdcs %[t2], %[t3], [%[tmpres], #8]\n"
        "strdcs %[t0], %[t1], [%[res], #0]\n"
        "strdcs %[t2], %[t3], [%[res], #8]\n"
        "itttt  cs\n"
        "ldrdcs %[t0], %[t1], [%[tmpres], #16]\n"
        "ldrdcs %[t2], %[t3], [%[tmpres], #24]\n"
        "strdcs %[t0], %[t1], [%[res], #16]\n"
        "strdcs %[t2], %[t3], [%[res], #24]\n"
        : [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3)
        : [res] "r"(res), [tmpres] "r"(tmpres), [p] "r"(p)
        : "cc", "memory");
}

static void modsub_MFP7_ct(const spint *a, const spint *b, spint *res) {
    // No longer passes tests, using generated code for now
    // spint a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4], a5 = a[5], a6 = a[6], a7 = a[7];
    // spint t = 0, t1, t2;
    // const spint p0 = 4294967295;
    // const spint p1 = 4294967295;
    // const spint p2 = 4294967295;
    // const spint p3 = 4294967295;
    // const spint p4 = 3829006335;
    // const spint p5 = 1288340339;
    // const spint p6 = 2933633043;
    // const spint p7 = 815531196;
    // asm volatile(
    //     "ldrd %[t1], %[t2], [%[b]]\n"
    //     "subs %[a0], %[a0], %[t1]\n"
    //     "sbcs %[a1], %[a1], %[t2]\n"
    //     "ldrd %[t1], %[t2], [%[b], #8]\n"
    //     "sbcs %[a2], %[a2], %[t1]\n"
    //     "sbcs %[a3], %[a3], %[t2]\n"
    //     "ldrd %[t1], %[t2], [%[b], #16]\n"
    //     "sbcs %[a4], %[a4], %[t1]\n"
    //     "sbcs %[a5], %[a5], %[t2]\n"
    //     "ldrd %[t1], %[t2], [%[b], #24]\n"
    //     "sbcs %[a6], %[a6], %[t1]\n"
    //     "sbcs %[a7], %[a7], %[t2]\n"
    //     "sbcs %[t], %[t], %[t]\n"
    //     : [a0] "+&r"(a0), [a1] "+&r"(a1), [a2] "+&r"(a2), [a3] "+&r"(a3), [a4] "+&r"(a4), [a5] "+&r"(a5),
    //       [a6] "+&r"(a6), [a7] "+&r"(a7), [t] "+&r"(t), [t1] "+r"(t1), [t2] "+r"(t2)
    //     : [b] "r"(b));
    // t = -t;
    // t2 = 0;
    // UMAAL(a0, t2, t, p0);
    // UMAAL(a1, t2, t, p1);
    // UMAAL(a2, t2, t, p2);
    // UMAAL(a3, t2, t, p3);
    // UMAAL(a4, t2, t, p4);
    // UMAAL(a5, t2, t, p5);
    // UMAAL(a6, t2, t, p6);
    // UMAAL(a7, t2, t, p7);
    // res[0] = a0;
    // res[1] = a1;
    // res[2] = a2;
    // res[3] = a3;
    // res[4] = a4;
    // res[5] = a5;
    // res[6] = a6;
    // res[7] = a7;
    spint a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4], a5 = a[5], a6 = a[6], a7 = a[7];
    spint t, t1, t2;
    spint t3, t4;
    const spint p0 = 4294967294;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 4294967295;
    const spint p4 = 3363045375;
    const spint p5 = 2576680679;
    const spint p6 = 1572298790;
    const spint p7 = 1631062393;
    asm volatile(
        "mov %[t], #0\n"
        "ldrd %[t1], %[t2], [%[b]]\n"
        "ldrd %[t3], %[t4], [%[a]]\n"
        "subs %[t3], %[t3], %[t1]\n"
        "sbcs %[t4], %[t4], %[t2]\n"
        "strd %[t3], %[t4], [%[res]]\n"
        "ldrd %[t1], %[t2], [%[b], #8]\n"
        "ldrd %[t3], %[t4], [%[a], #8]\n"
        "sbcs %[t3], %[t3], %[t1]\n"
        "sbcs %[t4], %[t4], %[t2]\n"
        "strd %[t3], %[t4], [%[res], #8]\n"
        "ldrd %[t1], %[t2], [%[b], #16]\n"
        "ldrd %[t3], %[t4], [%[a], #16]\n"
        "sbcs %[t3], %[t3], %[t1]\n"
        "sbcs %[t4], %[t4], %[t2]\n"
        "strd %[t3], %[t4], [%[res], #16]\n"
        "ldrd %[t1], %[t2], [%[b], #24]\n"
        "ldrd %[t3], %[t4], [%[a], #24]\n"
        "sbcs %[t3], %[t3], %[t1]\n"
        "sbcs %[t4], %[t4], %[t2]\n"
        "strd %[t3], %[t4], [%[res], #24]\n"
        "sbcs %[t], %[t], %[t]\n"
        : [t] "=&r"(t), [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4)
        : [b] "r"(b), [a] "r"(a), [res] "r"(res)
        : "cc", "memory");
    t = -t | (res[7] > p7);
    t2 = 0;
    a0 = res[0];
    UMAAL(a0, t2, t, p0);
    res[0] = a0;
    a1 = res[1];
    UMAAL(a1, t2, t, p1);
    res[1] = a1;
    a2 = res[2];
    UMAAL(a2, t2, t, p2);
    res[2] = a2;
    a3 = res[3];
    UMAAL(a3, t2, t, p3);
    res[3] = a3;
    a4 = res[4];
    UMAAL(a4, t2, t, p4);
    res[4] = a4;
    a5 = res[5];
    UMAAL(a5, t2, t, p5);
    res[5] = a5;
    a6 = res[6];
    UMAAL(a6, t2, t, p6);
    res[6] = a6;
    a7 = res[7];
    UMAAL(a7, t2, t, p7);
    res[7] = a7;
}
#define Nlimbs_MFP7_ct 8
#define Nbits_MFP7_ct 254
#define Nbytes_MFP7_ct 32
