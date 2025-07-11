// Copyright 2025 Technology Innovation Institute

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

static int modfsb_NIST256_ct(spint *a) {
    const spint p0 = 4294967295;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 0;
    const spint p4 = 0;
    const spint p5 = 0;
    const spint p6 = 1;
    const spint p7 = 4294967295;
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
        "strcs %[a0], [%[a], #0]\n"
        "strcs %[a1], [%[a], #4]\n"
        "strcs %[a2], [%[a], #8]\n"
        "strcs %[a3], [%[a], #12]\n"
        "itttt cs\n"
        "strcs %[a4], [%[a], #16]\n"
        "strcs %[a5], [%[a], #20]\n"
        "strcs %[a6], [%[a], #24]\n"
        "strcs %[a7], [%[a], #28]\n"
        "adc    %[r], %[r], %[r]\n"
        : [a0] "+&r" (a0), [a1] "+&r" (a1), [a2] "+&r" (a2), [a3] "+&r" (a3), [a4] "+&r" (a4), [a5] "+&r" (a5), [a6] "+&r" (a6), [a7] "+&r" (a7), [r] "+&r" (r)
        : [a] "r" (a), [p0] "rI" (p0), [p1] "rI" (p1), [p2] "rI" (p2), [p3] "rI" (p3), [p4] "rI" (p4), [p5] "rI" (p5), [p6] "rI" (p6), [p7] "rI" (p7)
        : "cc", "memory");

    return 1 - r;
}

ALWAYS_INLINE static void mul_NIST256_ct(const spint *p, const spint *q, spint *r) {
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

ALWAYS_INLINE static void sqr_NIST256_ct(const spint *p, spint *r) {
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

static void modmul_NIST256_ct(const spint *a, const spint *b, spint *res) {
    spint A[16];
    spint A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15;
    const spint p0 = 4294967295;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 0;
    const spint p4 = 0;
    const spint p5 = 0;
    const spint p6 = 1;
    const spint p7 = 4294967295;
    spint q, t, t2 = 0;

    mul_NIST256_ct(a, b, A);

    A0 = A[0];
    A1 = A[1];
    A2 = A[2];
    A3 = A[3];
    A4 = A[4];
    A5 = A[5];
    A6 = A[6];
    A7 = A[7];
    A8 = A[8];
    A9 = A[9];
    A10 = A[10];
    A11 = A[11];
    A12 = A[12];
    A13 = A[13];
    A14 = A[14];
    A15 = A[15];

    q = A0;
    t = 0;
    UMAAL(A3, t, q, p3 + 1);
    UMAAL(A4, t, q, p4);
    UMAAL(A5, t, q, p5);
    UMAAL(A6, t, q, p6);
    UMAAL(A7, t, q, p7);
    UMAAL(A8, t2, 1, t);

    q = A1;
    t = 0;
    UMAAL(A4, t, q, p3 + 1);
    UMAAL(A5, t, q, p4);
    UMAAL(A6, t, q, p5);
    UMAAL(A7, t, q, p6);
    UMAAL(A8, t, q, p7);
    UMAAL(A9, t2, 1, t);

    q = A2;
    t = 0;
    UMAAL(A5, t, q, p3 + 1);
    UMAAL(A6, t, q, p4);
    UMAAL(A7, t, q, p5);
    UMAAL(A8, t, q, p6);
    UMAAL(A9, t, q, p7);
    UMAAL(A10, t2, 1, t);

    q = A3;
    t = 0;
    UMAAL(A6, t, q, p3 + 1);
    UMAAL(A7, t, q, p4);
    UMAAL(A8, t, q, p5);
    UMAAL(A9, t, q, p6);
    UMAAL(A10, t, q, p7);
    UMAAL(A11, t2, 1, t);

    q = A4;
    t = 0;
    UMAAL(A7, t, q, p3 + 1);
    UMAAL(A8, t, q, p4);
    UMAAL(A9, t, q, p5);
    UMAAL(A10, t, q, p6);
    UMAAL(A11, t, q, p7);
    UMAAL(A12, t2, 1, t);

    q = A5;
    t = 0;
    UMAAL(A8, t, q, p3 + 1);
    UMAAL(A9, t, q, p4);
    UMAAL(A10, t, q, p5);
    UMAAL(A11, t, q, p6);
    UMAAL(A12, t, q, p7);
    UMAAL(A13, t2, 1, t);

    q = A6;
    t = 0;
    UMAAL(A9, t, q, p3 + 1);
    UMAAL(A10, t, q, p4);
    UMAAL(A11, t, q, p5);
    UMAAL(A12, t, q, p6);
    UMAAL(A13, t, q, p7);
    UMAAL(A14, t2, 1, t);

    q = A7;
    t = 0;
    UMAAL(A10, t, q, p3 + 1);
    UMAAL(A11, t, q, p4);
    UMAAL(A12, t, q, p5);
    UMAAL(A13, t, q, p6);
    UMAAL(A14, t, q, p7);
    UMAAL(A15, t2, 1, t);

    res[0] = A8;
    res[1] = A9;
    res[2] = A10;
    res[3] = A11;
    res[4] = A12;
    res[5] = A13;
    res[6] = A14;
    res[7] = A15;
    asm volatile(
        "subs %[A8], %[A8], %[p0]\n"
        "sbcs %[A9], %[A9], %[p1]\n"
        "sbcs %[A10], %[A10], %[p2]\n"
        "sbcs %[A11], %[A11], %[p3]\n"
        "sbcs %[A12], %[A12], %[p4]\n"
        "sbcs %[A13], %[A13], %[p5]\n"
        "sbcs %[A14], %[A14], %[p6]\n"
        "sbcs %[A15], %[A15], %[p7]\n"
        "subs %[t2], %[t2], #1\n"
        "itttt cs\n"
        "strcs %[A8], [%[res], #0]\n"
        "strcs %[A9], [%[res], #4]\n"
        "strcs %[A10], [%[res], #8]\n"
        "strcs %[A11], [%[res], #12]\n"
        "itttt cs\n"
        "strcs %[A12], [%[res], #16]\n"
        "strcs %[A13], [%[res], #20]\n"
        "strcs %[A14], [%[res], #24]\n"
        "strcs %[A15], [%[res], #28]\n"
        : [A8] "+&r" (A8), [A9] "+&r" (A9), [A10] "+&r" (A10), [A11] "+&r" (A11), [A12] "+&r" (A12), [A13] "+&r" (A13), [A14] "+&r" (A14), [A15] "+&r" (A15), [t2] "+&r" (t2)
        : [res] "r" (res), [p0] "rI" (p0), [p1] "rI" (p1), [p2] "rI" (p2), [p3] "rI" (p3), [p4] "rI" (p4), [p5] "rI" (p5), [p6] "rI" (p6), [p7] "rI" (p7)
        : "cc", "memory");

    modfsb_NIST256_ct(res);
}

ALWAYS_INLINE static void inner_modsqr_NIST256_ct(const spint *a, spint *res) {
    spint A[16];
    spint A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15;
    const spint p0 = 4294967295;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 0;
    const spint p4 = 0;
    const spint p5 = 0;
    const spint p6 = 1;
    const spint p7 = 4294967295;
    spint q, t, t2 = 0;

    sqr_NIST256_ct(a, A);

    A0 = A[0];
    A1 = A[1];
    A2 = A[2];
    A3 = A[3];
    A4 = A[4];
    A5 = A[5];
    A6 = A[6];
    A7 = A[7];
    A8 = A[8];
    A9 = A[9];
    A10 = A[10];
    A11 = A[11];
    A12 = A[12];
    A13 = A[13];
    A14 = A[14];
    A15 = A[15];

    q = A0;
    t = 0;
    UMAAL(A3, t, q, p3 + 1);
    UMAAL(A4, t, q, p4);
    UMAAL(A5, t, q, p5);
    UMAAL(A6, t, q, p6);
    UMAAL(A7, t, q, p7);
    UMAAL(A8, t2, 1, t);

    q = A1;
    t = 0;
    UMAAL(A4, t, q, p3 + 1);
    UMAAL(A5, t, q, p4);
    UMAAL(A6, t, q, p5);
    UMAAL(A7, t, q, p6);
    UMAAL(A8, t, q, p7);
    UMAAL(A9, t2, 1, t);

    q = A2;
    t = 0;
    UMAAL(A5, t, q, p3 + 1);
    UMAAL(A6, t, q, p4);
    UMAAL(A7, t, q, p5);
    UMAAL(A8, t, q, p6);
    UMAAL(A9, t, q, p7);
    UMAAL(A10, t2, 1, t);

    q = A3;
    t = 0;
    UMAAL(A6, t, q, p3 + 1);
    UMAAL(A7, t, q, p4);
    UMAAL(A8, t, q, p5);
    UMAAL(A9, t, q, p6);
    UMAAL(A10, t, q, p7);
    UMAAL(A11, t2, 1, t);

    q = A4;
    t = 0;
    UMAAL(A7, t, q, p3 + 1);
    UMAAL(A8, t, q, p4);
    UMAAL(A9, t, q, p5);
    UMAAL(A10, t, q, p6);
    UMAAL(A11, t, q, p7);
    UMAAL(A12, t2, 1, t);

    q = A5;
    t = 0;
    UMAAL(A8, t, q, p3 + 1);
    UMAAL(A9, t, q, p4);
    UMAAL(A10, t, q, p5);
    UMAAL(A11, t, q, p6);
    UMAAL(A12, t, q, p7);
    UMAAL(A13, t2, 1, t);

    q = A6;
    t = 0;
    UMAAL(A9, t, q, p3 + 1);
    UMAAL(A10, t, q, p4);
    UMAAL(A11, t, q, p5);
    UMAAL(A12, t, q, p6);
    UMAAL(A13, t, q, p7);
    UMAAL(A14, t2, 1, t);

    q = A7;
    t = 0;
    UMAAL(A10, t, q, p3 + 1);
    UMAAL(A11, t, q, p4);
    UMAAL(A12, t, q, p5);
    UMAAL(A13, t, q, p6);
    UMAAL(A14, t, q, p7);
    UMAAL(A15, t2, 1, t);

    res[0] = A8;
    res[1] = A9;
    res[2] = A10;
    res[3] = A11;
    res[4] = A12;
    res[5] = A13;
    res[6] = A14;
    res[7] = A15;
    asm volatile(
        "subs %[A8], %[A8], %[p0]\n"
        "sbcs %[A9], %[A9], %[p1]\n"
        "sbcs %[A10], %[A10], %[p2]\n"
        "sbcs %[A11], %[A11], %[p3]\n"
        "sbcs %[A12], %[A12], %[p4]\n"
        "sbcs %[A13], %[A13], %[p5]\n"
        "sbcs %[A14], %[A14], %[p6]\n"
        "sbcs %[A15], %[A15], %[p7]\n"
        "subs %[t2], %[t2], #1\n"
        "itttt cs\n"
        "strcs %[A8], [%[res], #0]\n"
        "strcs %[A9], [%[res], #4]\n"
        "strcs %[A10], [%[res], #8]\n"
        "strcs %[A11], [%[res], #12]\n"
        "itttt cs\n"
        "strcs %[A12], [%[res], #16]\n"
        "strcs %[A13], [%[res], #20]\n"
        "strcs %[A14], [%[res], #24]\n"
        "strcs %[A15], [%[res], #28]\n"
        : [A8] "+&r" (A8), [A9] "+&r" (A9), [A10] "+&r" (A10), [A11] "+&r" (A11), [A12] "+&r" (A12), [A13] "+&r" (A13), [A14] "+&r" (A14), [A15] "+&r" (A15), [t2] "+&r" (t2)
        : [res] "r" (res), [p0] "rI" (p0), [p1] "rI" (p1), [p2] "rI" (p2), [p3] "rI" (p3), [p4] "rI" (p4), [p5] "rI" (p5), [p6] "rI" (p6), [p7] "rI" (p7)
        : "cc", "memory");

    modfsb_NIST256_ct(res);
}

static void modsqr_NIST256_ct(const spint *a, spint *res) {
    inner_modsqr_NIST256_ct(a, res);
}

static void nres_NIST256_ct(const spint *a, spint *b) {
    spint nresfactor[] = {3, 0, 4294967295, 4294967291, 4294967294, 4294967295, 4294967293, 4};
    modmul_NIST256_ct(a, nresfactor, b);
}

static void redc_NIST256_ct(const spint *a, spint *b) {
    spint rinv[] = {1, 0, 0, 0, 0, 0, 0, 0};
    modmul_NIST256_ct(a, rinv, b);
}

static void modcmv_NIST256_ct(int d, const spint *a, volatile spint *b) {
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

static void modcsw_NIST256_ct(int d, volatile spint *a, volatile spint *b) {
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

inline static void modadd_NIST256_ct(const spint *a, const spint *b, spint *res) {
    spint a0, a1, a2, a3, a4, a5, a6, a7;
    spint b0, b1, b2, b3, b4, b5, b6, b7;
    spint t = 0;
    const spint p0 = 4294967295;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 0;
    const spint p4 = 0;
    const spint p5 = 0;
    const spint p6 = 1;
    const spint p7 = 4294967295;
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
        "subs %[a0], %[a0], %[p0]\n"
        "sbcs %[a1], %[a1], %[p1]\n"
        "sbcs %[a2], %[a2], %[p2]\n"
        "sbcs %[a3], %[a3], %[p3]\n"
        "sbcs %[a4], %[a4], %[p4]\n"
        "sbcs %[a5], %[a5], %[p5]\n"
        "sbcs %[a6], %[a6], %[p6]\n"
        "sbcs %[a7], %[a7], %[p7]\n"
        "itttt cs\n"
        "strcs %[a0], [%[res], #0]\n"
        "strcs %[a1], [%[res], #4]\n"
        "strcs %[a2], [%[res], #8]\n"
        "strcs %[a3], [%[res], #12]\n"
        "itttt cs\n"
        "strcs %[a4], [%[res], #16]\n"
        "strcs %[a5], [%[res], #20]\n"
        "strcs %[a6], [%[res], #24]\n"
        "strcs %[a7], [%[res], #28]\n"
        : [a0] "+&r" (a0), [a1] "+&r" (a1), [a2] "+&r" (a2), [a3] "+&r" (a3), [a4] "+&r" (a4), [a5] "+&r" (a5), [a6] "+&r" (a6), [a7] "+&r" (a7)
        : [res] "r" (res), [p0] "rI" (p0), [p1] "rI" (p1), [p2] "rI" (p2), [p3] "rI" (p3), [p4] "rI" (p4), [p5] "rI" (p5), [p6] "rI" (p6), [p7] "rI" (p7)
        : "cc", "memory");
    res[0] = a0*t - res[0]*(t-1);
    res[1] = a1*t - res[1]*(t-1);
    res[2] = a2*t - res[2]*(t-1);
    res[3] = a3*t - res[3]*(t-1);
    res[4] = a4*t - res[4]*(t-1);
    res[5] = a5*t - res[5]*(t-1);
    res[6] = a6*t - res[6]*(t-1);
    res[7] = a7*t - res[7]*(t-1);
}

inline static void modsub_NIST256_ct(const spint *a, const spint *b, spint *res) {
    spint a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4], a5 = a[5], a6 = a[6], a7 = a[7];
    spint t, t1, t2;
    const spint p0 = 4294967295;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 0;
    const spint p4 = 0;
    const spint p5 = 0;
    const spint p6 = 1;
    const spint p7 = 4294967295;
    asm volatile(
        "ldrd %[t1], %[t2], [%[b]]\n"
        "subs %[a0], %[a0], %[t1]\n"
        "sbcs %[a1], %[a1], %[t2]\n"
        "ldrd %[t1], %[t2], [%[b], #8]\n"
        "sbcs %[a2], %[a2], %[t1]\n"
        "sbcs %[a3], %[a3], %[t2]\n"
        "ldrd %[t1], %[t2], [%[b], #16]\n"
        "sbcs %[a4], %[a4], %[t1]\n"
        "sbcs %[a5], %[a5], %[t2]\n"
        "ldrd %[t1], %[t2], [%[b], #24]\n"
        "sbcs %[a6], %[a6], %[t1]\n"
        "sbcs %[a7], %[a7], %[t2]\n"
        "sbcs  %[t], %[t1], %[t1]\n"
        : [a0] "+&r" (a0), [a1] "+&r" (a1), [a2] "+&r" (a2), [a3] "+&r" (a3), [a4] "+&r" (a4), [a5] "+&r" (a5), [a6] "+&r" (a6), [a7] "+&r" (a7), [t] "=&r" (t), [t1] "=&r" (t1), [t2] "=&r" (t2)
        : [b] "r" (b)
        : "cc", "memory");
    t = -t;
    t2 = 0;
    UMAAL(a0, t2, t, p0);
    UMAAL(a1, t2, t, p1);
    UMAAL(a2, t2, t, p2);
    UMAAL(a3, t2, t, p3);
    UMAAL(a4, t2, t, p4);
    UMAAL(a5, t2, t, p5);
    UMAAL(a6, t2, t, p6);
    UMAAL(a7, t2, t, p7);
    res[0] = a0;
    res[1] = a1;
    res[2] = a2;
    res[3] = a3;
    res[4] = a4;
    res[5] = a5;
    res[6] = a6;
    res[7] = a7;
}

static void modneg_NIST256_ct(const spint *a, spint *r) {
    spint zero[8] = {0};
    modsub_NIST256_ct(zero, a, r);
}

static void modshl_NIST256_ct(int n, spint *a) {
#pragma GCC unroll 7
    for (int i = 7; i > 0; i--) {
        a[i] = (a[i] << n) + (a[i - 1] >> (32 - n));
    }
    a[0] = (a[0] << n);
}

// Only works for n <= 31
static spint modshr_NIST256_ct(int n, spint *a) {
    spint r = a[0] & ((1 << n) - 1);
#pragma GCC unroll 7
    for (int i = 0; i < 7; i++) {
        a[i] = (a[i] >> n) | (a[i + 1] << (32 - n));
    }
    a[7] = a[7] >> n;
    return r;
}

static void modcpy_NIST256_ct(const spint *a, spint *b) {
#pragma GCC unroll 8
    for (int i = 0; i < 8; i++) {
        b[i] = a[i];
    }
}

static int modis0_NIST256_ct(const spint *a) {
    spint c[8] = {0};
    spint d = 0;
    modcpy_NIST256_ct(a, c);
    modfsb_NIST256_ct(c);
    for (int i = 0; i < 8; i++) {
        d |= c[i];
    }
    return 1 - ((d | -d) >> 31);
}

static int modis1_NIST256_ct(const spint *a) {
    spint c[8] = {0};
    spint d = 0;
    redc_NIST256_ct(a, c);
    c[0] = c[0] - 1;
    for (int i = 0; i < 8; i++) {
        d |= c[i];
    }
    return 1 - ((d | -d) >> 31);
}

static int modcmp_NIST256_ct(const spint *a, const spint *b) {
    spint c[8], d[8];
    int neq = 0;
    redc_NIST256_ct(a, c);
    redc_NIST256_ct(b, d);
    for (int i = 0; i < 8; i++) {
        neq |= c[i] ^ d[i];
    }
    neq = (neq | -neq) >> 31;
    return 1 - (neq & 1);
}

static int modsign_NIST256_ct(const spint *a) {
    spint c[8];
    redc_NIST256_ct(a, c);
    return c[0] % 2;
}

NOINLINE static void modnsqr_NIST256_ct(spint *a, int n) {
    for (int i = 0; i < n; i++) {
        inner_modsqr_NIST256_ct(a, a);
    }
}

// Calculate progenitor
NOINLINE static void modpro_NIST256_ct(const spint *w, spint *z) {
    spint x[8];
    spint t0[8];
    spint t1[8];
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

// Test for quadratic residue, provide progenitor h if available, NULL if not
static int modqr_NIST256_ct(const spint *h, const spint *x) {
    spint r[8];
    if (h == NULL) {
        modpro_NIST256_ct(x, r);
        modsqr_NIST256_ct(r, r);
    }
    else {
        modsqr_NIST256_ct(h, r);
    }
    modmul_NIST256_ct(r, x, r);
    return modis1_NIST256_ct(r);
}

// Modular square root, provide progenitor h if available, NULL if not
static void modsqrt_NIST256_ct(const spint *x, const spint *h, spint *r) {
    spint s[8];
    spint y[8];
    if (h == NULL) {
        modpro_NIST256_ct(x, y);
    }
    else {
        modcpy_NIST256_ct(h, y);
    }
    modmul_NIST256_ct(y, x, s);
    modcpy_NIST256_ct(s, r);
}

// Calculate inverse, provide progenitor h if available
static void modinv_NIST256_ct(const spint *x, const spint *h, spint *z) {
    spint s[8];
    spint t[8];
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

static void modzer_NIST256_ct(spint *a) {
#pragma GCC unroll 8
    for (int i = 0; i < 8; i++) {
        a[i] = 0;
    }
}

static void modone_NIST256_ct(spint *a) {
    a[0] = 1;
    a[1] = 0;
    a[2] = 0;
    a[3] = 4294967295;
    a[4] = 4294967295;
    a[5] = 4294967295;
    a[6] = 4294967294;
    a[7] = 0;
}

static void modint_NIST256_ct(int x, spint *a) {
    a[0] = (spint)x;
#pragma GCC unroll 7
    for (int i = 1; i < 8; i++) {
        a[i] = 0;
    }
    nres_NIST256_ct(a, a);
}

static void mod2r_NIST256_ct(unsigned int r, spint *a) {
    unsigned int n = r >> 5;
    unsigned int m = r & 31;
    modzer_NIST256_ct(a);
    if (r >= 256) {
        return;
    }
    a[n] = 1 << m;
    nres_NIST256_ct(a, a);
}

static void modmli_NIST256_ct(const spint *p, const spint q, spint *r) {
    spint t[8];
    modint_NIST256_ct(q, t);
    modmul_NIST256_ct(p, t, r);
}

static void modimp_NIST256_ct(const char *b, spint *a) {
    const spint *b32 = (const spint *)b;
#pragma GCC unroll 8
    for (int i = 0; i < 8; i++) {
        a[i] = __builtin_bswap32(b32[7 - i]);
    }
    nres_NIST256_ct(a, a);
}

// Code for export, not exponentiation
static void modexp_NIST256_ct(const spint *a, char *b) {
    spint c[8], *b32 = (spint *)b;
    redc_NIST256_ct(a, c);
#pragma GCC unroll 8
    for (int i = 0; i < 8; i++) {
        b32[7 - i] = __builtin_bswap32(c[i]);
    }
}

#define Nlimbs_NIST256_ct 8
#define Nbits_NIST256_ct  256
#define Nbytes_NIST256_ct 32
