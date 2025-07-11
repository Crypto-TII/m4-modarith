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

inline static int modfsb_C448_ct(spint *a) {
    const spint p0 = 4294967295;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 4294967295;
    const spint p4 = 4294967295;
    const spint p5 = 4294967295;
    const spint p6 = 4294967295;
    const spint p7 = 4294967294;
    const spint p8 = 4294967295;
    const spint p9 = 4294967295;
    const spint p10 = 4294967295;
    const spint p11 = 4294967295;
    const spint p12 = 4294967295;
    const spint p13 = 4294967295;
    spint t0, t1;
    spint tmpvec[14];
    int r = 0;
    asm volatile(
        "ldr   %[t0], [%[a], #0]\n"
        "subs  %[t0], %[t0], %[p0]\n"

        "ldr   %[t1], [%[a], #4]\n"
        "str   %[t0], [%[tmpvec], #0]\n"
        "sbcs  %[t1], %[t1], %[p1]\n"

        "ldr   %[t0], [%[a], #8]\n"
        "str   %[t1], [%[tmpvec], #4]\n"
        "sbcs  %[t0], %[t0], %[p2]\n"

        "ldr   %[t1], [%[a], #12]\n"
        "str   %[t0], [%[tmpvec], #8]\n"
        "sbcs  %[t1], %[t1], %[p3]\n"

        "ldr   %[t0], [%[a], #16]\n"
        "str   %[t1], [%[tmpvec], #12]\n"
        "sbcs  %[t0], %[t0], %[p4]\n"

        "ldr   %[t1], [%[a], #20]\n"
        "str   %[t0], [%[tmpvec], #16]\n"
        "sbcs  %[t1], %[t1], %[p5]\n"

        "ldr   %[t0], [%[a], #24]\n"
        "str   %[t1], [%[tmpvec], #20]\n"
        "sbcs  %[t0], %[t0], %[p6]\n"

        "ldr   %[t1], [%[a], #28]\n"
        "str   %[t0], [%[tmpvec], #24]\n"
        "sbcs  %[t1], %[t1], %[p7]\n"

        "ldr   %[t0], [%[a], #32]\n"
        "str   %[t1], [%[tmpvec], #28]\n"
        "sbcs  %[t0], %[t0], %[p8]\n"

        "ldr   %[t1], [%[a], #36]\n"
        "str   %[t0], [%[tmpvec], #32]\n"
        "sbcs  %[t1], %[t1], %[p9]\n"

        "ldr   %[t0], [%[a], #40]\n"
        "str   %[t1], [%[tmpvec], #36]\n"
        "sbcs  %[t0], %[t0], %[p10]\n"

        "ldr   %[t1], [%[a], #44]\n"
        "str   %[t0], [%[tmpvec], #40]\n"
        "sbcs  %[t1], %[t1], %[p11]\n"

        "ldr   %[t0], [%[a], #48]\n"
        "str   %[t1], [%[tmpvec], #44]\n"
        "sbcs  %[t0], %[t0], %[p12]\n"

        "ldr   %[t1], [%[a], #52]\n"
        "str   %[t0], [%[tmpvec], #48]\n"
        "sbcs  %[t1], %[t1], %[p13]\n"

        "str   %[t1], [%[tmpvec], #52]\n"

        "itttt cs\n"
        "ldrcs %[t0], [%[tmpvec], #0]\n"
        "ldrcs %[t1], [%[tmpvec], #4]\n"
        "strcs %[t0], [%[a], #0]\n"
        "strcs %[t1], [%[a], #4]\n"
        "itttt cs\n"
        "ldrcs %[t0], [%[tmpvec], #8]\n"
        "ldrcs %[t1], [%[tmpvec], #12]\n"
        "strcs %[t0], [%[a], #8]\n"
        "strcs %[t1], [%[a], #12]\n"
        "itttt cs\n"
        "ldrcs %[t0], [%[tmpvec], #16]\n"
        "ldrcs %[t1], [%[tmpvec], #20]\n"
        "strcs %[t0], [%[a], #16]\n"
        "strcs %[t1], [%[a], #20]\n"
        "itttt cs\n"
        "ldrcs %[t0], [%[tmpvec], #24]\n"
        "ldrcs %[t1], [%[tmpvec], #28]\n"
        "strcs %[t0], [%[a], #24]\n"
        "strcs %[t1], [%[a], #28]\n"
        "itttt cs\n"
        "ldrcs %[t0], [%[tmpvec], #32]\n"
        "ldrcs %[t1], [%[tmpvec], #36]\n"
        "strcs %[t0], [%[a], #32]\n"
        "strcs %[t1], [%[a], #36]\n"
        "itttt cs\n"
        "ldrcs %[t0], [%[tmpvec], #40]\n"
        "ldrcs %[t1], [%[tmpvec], #44]\n"
        "strcs %[t0], [%[a], #40]\n"
        "strcs %[t1], [%[a], #44]\n"
        "itttt cs\n"
        "ldrcs %[t0], [%[tmpvec], #48]\n"
        "ldrcs %[t1], [%[tmpvec], #52]\n"
        "strcs %[t0], [%[a], #48]\n"
        "strcs %[t1], [%[a], #52]\n"
        "adc   %[r], %[r], %[r]\n"
        : [t0] "=&r" (t0), [t1] "=&r" (t1), [r] "+&r" (r)
        : [a] "r" (a), [p0] "rI" (p0), [p1] "rI" (p1), [p2] "rI" (p2), [p3] "rI" (p3), [p4] "rI" (p4), [p5] "rI" (p5), [p6] "rI" (p6), [p7] "rI" (p7), [p8] "rI" (p8), [p9] "rI" (p9), [p10] "rI" (p10), [p11] "rI" (p11), [p12] "rI" (p12), [p13] "rI" (p13), [tmpvec] "r" (tmpvec)
        : "cc", "memory");

    return 1 - r;
}

ALWAYS_INLINE static void mul_C448_ct(const spint *p, const spint *q, spint *r) {
    spint t0, t1, t2, t3, t4, a, b0, b1, b2, b3;
    b0 = q[0];
    b1 = q[1];
    asm volatile(
        ".p2align 2\n"
        "mov.w  %[t1], #0\n"
        "ldr.w   %[a], [%[p], #0]\n"
        "umull  %[t0], %[t2], %[a], %[b0]\n"
        "umaal  %[t1], %[t2], %[a], %[b1]\n"
        "ldr.w   %[a], [%[p], #4]\n"
        "str.w  %[t0], [%[r], #0]\n"
        "mov.w  %[t0], #0\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "ldr.w   %[a], [%[p], #8]\n"
        "str.w  %[t1], [%[r], #4]\n"
        "mov.w  %[t1], #0\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t0], %[t1], %[a], %[b1]\n"
        "ldr.w   %[a], [%[p], #12]\n"
        "str.w  %[t2], [%[r], #8]\n"
        "mov.w  %[t2], #0\n"
        "umaal  %[t0], %[t2], %[a], %[b0]\n"
        "umaal  %[t1], %[t2], %[a], %[b1]\n"
        "ldr.w   %[a], [%[p], #16]\n"
        "str.w  %[t0], [%[r], #12]\n"
        "mov.w  %[t0], #0\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "ldr.w   %[a], [%[p], #20]\n"
        "str.w  %[t1], [%[r], #16]\n"
        "mov.w  %[t1], #0\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t0], %[t1], %[a], %[b1]\n"
        "ldr.w   %[a], [%[p], #24]\n"
        "str.w  %[t2], [%[r], #20]\n"
        "mov.w  %[t2], #0\n"
        "umaal  %[t0], %[t2], %[a], %[b0]\n"
        "umaal  %[t1], %[t2], %[a], %[b1]\n"
        "ldr.w   %[a], [%[p], #28]\n"
        "str.w  %[t0], [%[r], #24]\n"
        "mov.w  %[t0], #0\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "ldr.w   %[a], [%[p], #32]\n"
        "str.w  %[t1], [%[r], #28]\n"
        "mov.w  %[t1], #0\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t0], %[t1], %[a], %[b1]\n"
        "ldr.w   %[a], [%[p], #36]\n"
        "str.w  %[t2], [%[r], #32]\n"
        "mov.w  %[t2], #0\n"
        "umaal  %[t0], %[t2], %[a], %[b0]\n"
        "umaal  %[t1], %[t2], %[a], %[b1]\n"
        "ldr.w   %[a], [%[p], #40]\n"
        "str.w  %[t0], [%[r], #36]\n"
        "mov.w  %[t0], #0\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "ldr.w   %[a], [%[p], #44]\n"
        "str.w  %[t1], [%[r], #40]\n"
        "mov.w  %[t1], #0\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t0], %[t1], %[a], %[b1]\n"
        "ldr.w   %[a], [%[p], #48]\n"
        "str.w  %[t2], [%[r], #44]\n"
        "mov.w  %[t2], #0\n"
        "umaal  %[t0], %[t2], %[a], %[b0]\n"
        "umaal  %[t1], %[t2], %[a], %[b1]\n"
        "ldr.w   %[a], [%[p], #52]\n"
        "str.w  %[t0], [%[r], #48]\n"
        "mov.w  %[t0], #0\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "str.w  %[t1], [%[r], #52]\n"
        "str.w  %[t2], [%[r], #56]\n"
        "str.w  %[t0], [%[r], #60]\n"
        : [t1] "=&r"(t1), [t2] "=&r"(t2), [t0] "=&r"(t0), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = q[2];
    b1 = q[3];
    b2 = q[4];
    b3 = q[5];
    t0 = r[2];
    t1 = r[3];
    t2 = r[4];
    t3 = r[5];
    t4 = 0;
    asm volatile(
        ".p2align 2\n"
        "ldr.w   %[a], [%[p], #0]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #24]\n"
        "str.w  %[t0], [%[r], #8]\n"
        "mov.w  %[t0], #0\n"
        "adds.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #4]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #28]\n"
        "str.w  %[t1], [%[r], #12]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #8]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #32]\n"
        "str.w  %[t2], [%[r], #16]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #12]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #36]\n"
        "str.w  %[t3], [%[r], #20]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #16]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #40]\n"
        "str.w  %[t4], [%[r], #24]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #20]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #44]\n"
        "str.w  %[t0], [%[r], #28]\n"
        "mov.w  %[t0], #0\n"
        "adcs.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #24]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #48]\n"
        "str.w  %[t1], [%[r], #32]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #28]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #52]\n"
        "str.w  %[t2], [%[r], #36]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #32]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #56]\n"
        "str.w  %[t3], [%[r], #40]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #36]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #60]\n"
        "str.w  %[t4], [%[r], #44]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #40]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #44]\n"
        "str.w  %[t0], [%[r], #48]\n"
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
        "ldr.w   %[a], [%[p], #48]\n"
        "str.w  %[t1], [%[r], #52]\n"
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
        "ldr.w   %[a], [%[p], #52]\n"
        "str.w  %[t2], [%[r], #56]\n"
        "mov.w  %[t2], #0\n"
#ifdef __clang__
        "adcs   %[t1], %[t1], #0\n"
#else
        "adcs.w %[t1], %[t1], #0\n"
#endif
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
#ifdef __clang__
        "adcs   %[t2], %[t2], #0\n"
#else
        "adcs.w %[t2], %[t2], #0\n"
#endif
        "str.w  %[t3], [%[r], #60]\n"
        "str.w  %[t4], [%[r], #64]\n"
        "str.w  %[t0], [%[r], #68]\n"
        "str.w  %[t1], [%[r], #72]\n"
        "str.w  %[t2], [%[r], #76]\n"
        "mov.w  %[t3], #0\n"
#ifdef __clang__
        "adcs   %[t3], %[t3], #0\n"
#else
        "adcs.w %[t3], %[t3], #0\n"
#endif
        "str.w  %[t3], [%[r], #80]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = q[6];
    b1 = q[7];
    b2 = q[8];
    b3 = q[9];
    t0 = r[6];
    t1 = r[7];
    t2 = r[8];
    t3 = r[9];
    t4 = 0;
    asm volatile(
        ".p2align 2\n"
        "ldr.w   %[a], [%[p], #0]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #40]\n"
        "str.w  %[t0], [%[r], #24]\n"
        "mov.w  %[t0], #0\n"
        "adds.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #4]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #44]\n"
        "str.w  %[t1], [%[r], #28]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #8]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #48]\n"
        "str.w  %[t2], [%[r], #32]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #12]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #52]\n"
        "str.w  %[t3], [%[r], #36]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #16]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #56]\n"
        "str.w  %[t4], [%[r], #40]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #20]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #60]\n"
        "str.w  %[t0], [%[r], #44]\n"
        "mov.w  %[t0], #0\n"
        "adcs.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #24]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #64]\n"
        "str.w  %[t1], [%[r], #48]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #28]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #68]\n"
        "str.w  %[t2], [%[r], #52]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #32]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #72]\n"
        "str.w  %[t3], [%[r], #56]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #36]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #76]\n"
        "str.w  %[t4], [%[r], #60]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #40]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #80]\n"
        "str.w  %[t0], [%[r], #64]\n"
        "mov.w  %[t0], #0\n"
        "adcs.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #44]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #48]\n"
        "str.w  %[t1], [%[r], #68]\n"
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
        "ldr.w   %[a], [%[p], #52]\n"
        "str.w  %[t2], [%[r], #72]\n"
        "mov.w  %[t2], #0\n"
#ifdef __clang__
        "adcs   %[t1], %[t1], #0\n"
#else
        "adcs.w %[t1], %[t1], #0\n"
#endif
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
#ifdef __clang__
        "adcs   %[t2], %[t2], #0\n"
#else
        "adcs.w %[t2], %[t2], #0\n"
#endif
        "str.w  %[t3], [%[r], #76]\n"
        "str.w  %[t4], [%[r], #80]\n"
        "str.w  %[t0], [%[r], #84]\n"
        "str.w  %[t1], [%[r], #88]\n"
        "str.w  %[t2], [%[r], #92]\n"
        "mov.w  %[t3], #0\n"
#ifdef __clang__
        "adcs   %[t3], %[t3], #0\n"
#else
        "adcs.w %[t3], %[t3], #0\n"
#endif
        "str.w  %[t3], [%[r], #96]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = q[10];
    b1 = q[11];
    b2 = q[12];
    b3 = q[13];
    t0 = r[10];
    t1 = r[11];
    t2 = r[12];
    t3 = r[13];
    t4 = 0;
    asm volatile(
        ".p2align 2\n"
        "ldr.w   %[a], [%[p], #0]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #56]\n"
        "str.w  %[t0], [%[r], #40]\n"
        "mov.w  %[t0], #0\n"
        "adds.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #4]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #60]\n"
        "str.w  %[t1], [%[r], #44]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #8]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #64]\n"
        "str.w  %[t2], [%[r], #48]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #12]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #68]\n"
        "str.w  %[t3], [%[r], #52]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #16]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #72]\n"
        "str.w  %[t4], [%[r], #56]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #20]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #76]\n"
        "str.w  %[t0], [%[r], #60]\n"
        "mov.w  %[t0], #0\n"
        "adcs.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #24]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #80]\n"
        "str.w  %[t1], [%[r], #64]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #28]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #84]\n"
        "str.w  %[t2], [%[r], #68]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #32]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #88]\n"
        "str.w  %[t3], [%[r], #72]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #36]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #92]\n"
        "str.w  %[t4], [%[r], #76]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #40]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #96]\n"
        "str.w  %[t0], [%[r], #80]\n"
        "mov.w  %[t0], #0\n"
        "adcs.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #44]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #48]\n"
        "str.w  %[t1], [%[r], #84]\n"
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
        "ldr.w   %[a], [%[p], #52]\n"
        "str.w  %[t2], [%[r], #88]\n"
        "mov.w  %[t2], #0\n"
#ifdef __clang__
        "adcs   %[t1], %[t1], #0\n"
#else
        "adcs.w %[t1], %[t1], #0\n"
#endif
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
#ifdef __clang__
        "adcs   %[t2], %[t2], #0\n"
#else
        "adcs.w %[t2], %[t2], #0\n"
#endif
        "str.w  %[t3], [%[r], #92]\n"
        "str.w  %[t4], [%[r], #96]\n"
        "str.w  %[t0], [%[r], #100]\n"
        "str.w  %[t1], [%[r], #104]\n"
        "str.w  %[t2], [%[r], #108]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
}

ALWAYS_INLINE static void sqr_C448_ct(const spint *p, spint *r) {
    spint t0, t1, t2, t3, t4, a, b0, b1, b2, b3;
    b0 = p[0];
    b1 = p[1];
    b2 = p[2];
    b3 = p[3];
    asm volatile(
        ".p2align 2\n"
        "mov.w  %[t2], #0\n"
        "mov.w  %[t3], #0\n"
        "mov.w  %[t4], #0\n"
        "umull  %[t0], %[t1], %[b0], %[b1]\n"
        "str.w  %[t0], [%[r], #4]\n"
        "mov.w  %[t0], #0\n"
        "umaal  %[t1], %[t3], %[b0], %[b2]\n"
        "umaal  %[t2], %[t3], %[b1], %[b2]\n"
        "str.w  %[t1], [%[r], #8]\n"
        "mov.w  %[t1], #0\n"
        "umaal  %[t2], %[t0], %[b0], %[b3]\n"
        "umaal  %[t3], %[t0], %[b1], %[b3]\n"
        "umaal  %[t4], %[t0], %[b2], %[b3]\n"
        "str.w  %[t2], [%[r], #12]\n"
        "mov.w  %[t2], #0\n"
        "ldr.w   %[a], [%[p], #16]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #20]\n"
        "str.w  %[t3], [%[r], #16]\n"
        "mov.w  %[t3], #0\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #24]\n"
        "str.w  %[t4], [%[r], #20]\n"
        "mov.w  %[t4], #0\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #28]\n"
        "str.w  %[t0], [%[r], #24]\n"
        "mov.w  %[t0], #0\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #32]\n"
        "str.w  %[t1], [%[r], #28]\n"
        "mov.w  %[t1], #0\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #36]\n"
        "str.w  %[t2], [%[r], #32]\n"
        "mov.w  %[t2], #0\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #40]\n"
        "str.w  %[t3], [%[r], #36]\n"
        "mov.w  %[t3], #0\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #44]\n"
        "str.w  %[t4], [%[r], #40]\n"
        "mov.w  %[t4], #0\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #48]\n"
        "str.w  %[t0], [%[r], #44]\n"
        "mov.w  %[t0], #0\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #52]\n"
        "str.w  %[t1], [%[r], #48]\n"
        "mov.w  %[t1], #0\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "str.w  %[t2], [%[r], #52]\n"
        "str.w  %[t3], [%[r], #56]\n"
        "str.w  %[t4], [%[r], #60]\n"
        "str.w  %[t0], [%[r], #64]\n"
        "str.w  %[t1], [%[r], #68]\n"
        : [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [t0] "=&r"(t0), [t1] "=&r"(t1), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = p[4];
    b1 = p[5];
    b2 = p[6];
    b3 = p[7];
    t0 = r[9];
    t1 = r[10];
    t2 = r[11];
    t3 = r[12];
    t4 = r[13];
    asm volatile(
        ".p2align 2\n"
        "mov.w  %[a], #0\n"
        "umaal  %[t0], %[a], %[b0], %[b1]\n"
        "str.w  %[t0], [%[r], #36]\n"
        "mov.w  %[t0], #0\n"
        "umaal  %[t1], %[a], %[b0], %[b2]\n"
        "umaal  %[t2], %[a], %[b1], %[b2]\n"
        "ldr.w  %[t0], [%[r], #56]\n"
        "str.w  %[t1], [%[r], #40]\n"
        "mov.w  %[t1], #0\n"
        "adds.w %[t3], %[t3], %[a]\n"
        "mov.w  %[a], #0\n"
#ifdef __clang__
        "adcs   %[t4], %[t4], #0\n"
#else
        "adcs.w %[t4], %[t4], #0\n"
#endif
        "umaal  %[t2], %[a], %[b0], %[b3]\n"
        "umaal  %[t3], %[a], %[b1], %[b3]\n"
        "umaal  %[t4], %[a], %[b2], %[b3]\n"
        "ldr.w  %[t1], [%[r], #60]\n"
        "str.w  %[t2], [%[r], #44]\n"
        "mov.w  %[t2], #0\n"
#ifdef __clang__
        "adcs   %[t0], %[t0], %[a]\n"
        "adcs   %[t1], %[t1], #0\n"
#else
        "adcs.w %[t0], %[t0], %[a]\n"
        "adcs.w %[t1], %[t1], #0\n"
#endif
        "ldr.w   %[a], [%[p], #32]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #64]\n"
        "str.w  %[t3], [%[r], #48]\n"
        "mov.w  %[t3], #0\n"
#ifdef __clang__
        "adcs   %[t2], %[t2], %[a]\n"
#else
        "adcs.w %[t2], %[t2], %[a]\n"
#endif
        "ldr.w   %[a], [%[p], #36]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #68]\n"
        "str.w  %[t4], [%[r], #52]\n"
        "mov.w  %[t4], #0\n"
#ifdef __clang__
        "adcs   %[t3], %[t3], %[a]\n"
#else
        "adcs.w %[t3], %[t3], %[a]\n"
#endif
        "ldr.w   %[a], [%[p], #40]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #44]\n"
        "str.w  %[t0], [%[r], #56]\n"
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
        "ldr.w   %[a], [%[p], #48]\n"
        "str.w  %[t1], [%[r], #60]\n"
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
        "ldr.w   %[a], [%[p], #52]\n"
        "str.w  %[t2], [%[r], #64]\n"
        "mov.w  %[t2], #0\n"
#ifdef __clang__
        "adcs   %[t1], %[t1], #0\n"
#else
        "adcs.w %[t1], %[t1], #0\n"
#endif
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
#ifdef __clang__
        "adcs   %[t2], %[t2], #0\n"
#else
        "adcs.w %[t2], %[t2], #0\n"
#endif
        "str.w  %[t3], [%[r], #68]\n"
        "str.w  %[t4], [%[r], #72]\n"
        "str.w  %[t0], [%[r], #76]\n"
        "str.w  %[t1], [%[r], #80]\n"
        "str.w  %[t2], [%[r], #84]\n"
        "mov.w  %[t3], #0\n"
#ifdef __clang__
        "adcs   %[t3], %[t3], #0\n"
#else
        "adcs.w %[t3], %[t3], #0\n"
#endif
        "str.w  %[t3], [%[r], #88]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    spint a0 = p[8], a1 = p[9], a2 = p[10], a3 = p[11], a4 = p[12], a5 = p[13], c0, c1;
    asm volatile(
        ".p2align 2\n"
        "ldr.w   %[c0], [%[r], #68]\n"
        "mov.w   %[t0], #0\n"
        "mov.w   %[t1], #0\n"
        "umaal   %[c0], %[t0], %[a1], %[a0]\n"
        "ldr.w   %[c1], [%[r], #72]\n"
        "str.w   %[c0], [%[r], #68]\n"
        "umaal   %[c1], %[t0], %[a2], %[a0]\n"
        "ldr.w   %[c0], [%[r], #76]\n"
        "str.w   %[c1], [%[r], #72]\n"
        "umaal   %[c0], %[t0], %[a3], %[a0]\n"
        "umaal   %[c0], %[t1], %[a2], %[a1]\n"
        "ldr.w   %[c1], [%[r], #80]\n"
        "str.w   %[c0], [%[r], #76]\n"
        "umaal   %[c1], %[t0], %[a4], %[a0]\n"
        "umaal   %[c1], %[t1], %[a3], %[a1]\n"
        "ldr.w   %[c0], [%[r], #84]\n"
        "str.w   %[c1], [%[r], #80]\n"
        "umaal   %[c0], %[t0], %[a5], %[a0]\n"
        "mov.w   %[a0], #0\n"
        "umaal   %[c0], %[t1], %[a4], %[a1]\n"
        "umaal   %[c0], %[a0], %[a3], %[a2]\n"
        "mov.w  %[c1], #0\n"
        "str.w   %[c0], [%[r], #84]\n"
        "umaal   %[c1], %[t0], %[a5], %[a1]\n"
        "mov.w   %[a1], #0\n"
        "umaal   %[c1], %[t1], %[a4], %[a2]\n"
        "umaal   %[c1], %[a0], %[a1], %[a1]\n"
        "str.w   %[c1], [%[r], #88]\n"
        "umaal   %[t0], %[t1], %[a5], %[a2]\n"
        "umaal   %[t0], %[a0], %[a4], %[a3]\n"
        "str.w   %[t0], [%[r], #92]\n"
        "umaal   %[t1], %[a0], %[a5], %[a3]\n"
        "str.w   %[t1], [%[r], #96]\n"
        "umaal   %[a0], %[a1], %[a5], %[a4]\n"
        "str.w   %[a0], [%[r], #100]\n"
        "str.w   %[a1], [%[r], #104]\n"
        : [a0] "+&r"(a0), [a1] "+&r"(a1), [c0] "=&r"(c0), [c1] "=&r"(c1), [t0] "=&r"(t0), [t1] "=&r"(t1)
        : [a2] "r"(a2), [a3] "r"(a3), [a4] "r"(a4), [a5] "r"(a5), [r] "r"(r)
        : "memory");
    r[0] = 0;
    r[27] = 0;
    asm volatile(
        ".p2align 2\n"
        "mov.w  %[a], #2\n"
        "mov.w  %[t2], #0\n"
        "ldr.w   %[b0], [%[p], #0]\n"
        "ldr.w   %[b1], [%[p], #4]\n"
        "umull  %[t3], %[t4], %[b0], %[b0]\n"
        "umull  %[t0], %[t1], %[b1], %[b1]\n"
        "ldr.w   %[b0], [%[r], #0]\n"
        "ldr.w   %[b1], [%[r], #4]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "ldr.w   %[b0], [%[r], #8]\n"
        "ldr.w   %[b1], [%[r], #12]\n"
        "str.w  %[t3], [%[r], #0]\n"
        "str.w  %[t4], [%[r], #4]\n"
        "umaal  %[t0], %[t2], %[a], %[b0]\n"
        "umaal  %[t1], %[t2], %[a], %[b1]\n"
        "str.w  %[t0], [%[r], #8]\n"
        "str.w  %[t1], [%[r], #12]\n"
        "ldr.w   %[b2], [%[p], #8]\n"
        "ldr.w   %[b3], [%[p], #12]\n"
        "umull  %[t3], %[t4], %[b2], %[b2]\n"
        "umull  %[t0], %[t1], %[b3], %[b3]\n"
        "ldr.w   %[b2], [%[r], #16]\n"
        "ldr.w   %[b3], [%[r], #20]\n"
        "umaal  %[t3], %[t2], %[a], %[b2]\n"
        "umaal  %[t4], %[t2], %[a], %[b3]\n"
        "ldr.w   %[b2], [%[r], #24]\n"
        "ldr.w   %[b3], [%[r], #28]\n"
        "str.w  %[t3], [%[r], #16]\n"
        "str.w  %[t4], [%[r], #20]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "str.w  %[t0], [%[r], #24]\n"
        "str.w  %[t1], [%[r], #28]\n"
        "ldr.w   %[b0], [%[p], #16]\n"
        "ldr.w   %[b1], [%[p], #20]\n"
        "umull  %[t3], %[t4], %[b0], %[b0]\n"
        "umull  %[t0], %[t1], %[b1], %[b1]\n"
        "ldr.w   %[b0], [%[r], #32]\n"
        "ldr.w   %[b1], [%[r], #36]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "ldr.w   %[b0], [%[r], #40]\n"
        "ldr.w   %[b1], [%[r], #44]\n"
        "str.w  %[t3], [%[r], #32]\n"
        "str.w  %[t4], [%[r], #36]\n"
        "umaal  %[t0], %[t2], %[a], %[b0]\n"
        "umaal  %[t1], %[t2], %[a], %[b1]\n"
        "str.w  %[t0], [%[r], #40]\n"
        "str.w  %[t1], [%[r], #44]\n"
        "ldr.w   %[b2], [%[p], #24]\n"
        "ldr.w   %[b3], [%[p], #28]\n"
        "umull  %[t3], %[t4], %[b2], %[b2]\n"
        "umull  %[t0], %[t1], %[b3], %[b3]\n"
        "ldr.w   %[b2], [%[r], #48]\n"
        "ldr.w   %[b3], [%[r], #52]\n"
        "umaal  %[t3], %[t2], %[a], %[b2]\n"
        "umaal  %[t4], %[t2], %[a], %[b3]\n"
        "ldr.w   %[b2], [%[r], #56]\n"
        "ldr.w   %[b3], [%[r], #60]\n"
        "str.w  %[t3], [%[r], #48]\n"
        "str.w  %[t4], [%[r], #52]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "str.w  %[t0], [%[r], #56]\n"
        "str.w  %[t1], [%[r], #60]\n"
        "ldr.w   %[b0], [%[p], #32]\n"
        "ldr.w   %[b1], [%[p], #36]\n"
        "umull  %[t3], %[t4], %[b0], %[b0]\n"
        "umull  %[t0], %[t1], %[b1], %[b1]\n"
        "ldr.w   %[b0], [%[r], #64]\n"
        "ldr.w   %[b1], [%[r], #68]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "ldr.w   %[b0], [%[r], #72]\n"
        "ldr.w   %[b1], [%[r], #76]\n"
        "str.w  %[t3], [%[r], #64]\n"
        "str.w  %[t4], [%[r], #68]\n"
        "umaal  %[t0], %[t2], %[a], %[b0]\n"
        "umaal  %[t1], %[t2], %[a], %[b1]\n"
        "str.w  %[t0], [%[r], #72]\n"
        "str.w  %[t1], [%[r], #76]\n"
        "ldr.w   %[b2], [%[p], #40]\n"
        "ldr.w   %[b3], [%[p], #44]\n"
        "umull  %[t3], %[t4], %[b2], %[b2]\n"
        "umull  %[t0], %[t1], %[b3], %[b3]\n"
        "ldr.w   %[b2], [%[r], #80]\n"
        "ldr.w   %[b3], [%[r], #84]\n"
        "umaal  %[t3], %[t2], %[a], %[b2]\n"
        "umaal  %[t4], %[t2], %[a], %[b3]\n"
        "ldr.w   %[b2], [%[r], #88]\n"
        "ldr.w   %[b3], [%[r], #92]\n"
        "str.w  %[t3], [%[r], #80]\n"
        "str.w  %[t4], [%[r], #84]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "str.w  %[t0], [%[r], #88]\n"
        "str.w  %[t1], [%[r], #92]\n"
        "ldr.w   %[b0], [%[p], #48]\n"
        "ldr.w   %[b1], [%[p], #52]\n"
        "umull  %[t3], %[t4], %[b0], %[b0]\n"
        "umull  %[t0], %[t1], %[b1], %[b1]\n"
        "ldr.w   %[b0], [%[r], #96]\n"
        "ldr.w   %[b1], [%[r], #100]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "ldr.w   %[b0], [%[r], #104]\n"
        "ldr.w   %[b1], [%[r], #108]\n"
        "str.w  %[t3], [%[r], #96]\n"
        "str.w  %[t4], [%[r], #100]\n"
        "umaal  %[t0], %[t2], %[a], %[b0]\n"
        "umaal  %[t1], %[t2], %[a], %[b1]\n"
        "str.w  %[t0], [%[r], #104]\n"
        "str.w  %[t1], [%[r], #108]\n"
        : [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [a] "=&r"(a),
          [b0] "=&r"(b0), [b1] "=&r"(b1), [b2] "=&r"(b2), [b3] "=&r"(b3)
        : [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
}

ALWAYS_INLINE static void modred_C448_ct(const spint *c, spint *r) {
    spint tt0, tt1;

    // r = { c[0], c[1], ..., c[13] }
    spint r0 = c[0], r6 = c[6], r7 = c[7], r13 = c[13];
    spint t0, t6, t7, t13;
    t0 = t7 = c[14];
    t6 = t13 = c[20];
    tt0 = c[21];
    tt1 = c[27];
    UMAAL(r0, t0, tt0, 1);
    UMAAL(r6, t6, tt1, 1);
    UMAAL(r7, t7, tt0, 2);
    UMAAL(r13, t13, tt1, 2);

    spint carry = 0;
    UMAAL(r0, carry, t13, 1);

    spint r1 = c[1], r2 = c[2], r8 = c[8], r9 = c[9];
    spint t1, t2, t8, t9;
    t1 = t8 = c[15];
    t2 = t9 = c[16];
    tt0 = c[22];
    tt1 = c[23];
    UMAAL(r1, t1, tt0, 1);
    UMAAL(r2, t2, tt1, 1);
    UMAAL(r8, t8, tt0, 2);
    UMAAL(r9, t9, tt1, 2);

    UMAAL(r1, carry, t0, 1);
    UMAAL(r2, carry, t1, 1);

    spint r3 = c[3], r4 = c[4], r10 = c[10], r11 = c[11];
    spint t3, t4, t10, t11;
    t3 = t10 = c[17];
    t4 = t11 = c[18];
    tt0 = c[24];
    tt1 = c[25];
    UMAAL(r3, t3, tt0, 1);
    UMAAL(r4, t4, tt1, 1);
    UMAAL(r10, t10, tt0, 2);
    UMAAL(r11, t11, tt1, 2);

    UMAAL(r3, carry, t2, 1);
    UMAAL(r4, carry, t3, 1);

    spint r5 = c[5], r12 = c[12];
    spint t5, t12;
    t5 = t12 = c[19];
    tt0 = c[26];
    UMAAL(r5, t5, tt0, 1);
    UMAAL(r12, t12, tt0, 2);

    UMAAL(r5, carry, t4, 1);

    // t = { c[14], ..., c[20], c[14], ..., c[20] }

    // tt = { c[21], ..., c[27], c[21], ..., c[27] }

    // Propagate carries { t[13], t[0], ..., t[5], t[6] + t[13], t[7], ..., t[12] }
    UMAAL(r6, carry, t5, 1);
    carry += t13;
    UMAAL(r7, carry, t6, 1);
    UMAAL(r8, carry, t7, 1);
    UMAAL(r9, carry, t8, 1);
    UMAAL(r10, carry, t9, 1);
    UMAAL(r11, carry, t10, 1);
    UMAAL(r12, carry, t11, 1);
    UMAAL(r13, carry, t12, 1);

    // If there is a carry, add 2^224 + 1
    spint carry2 = 0;
    UMAAL(r0, carry2, carry, 1);
    r[0] = r0;

    UMAAL(r1, carry2, 0, 0);
    r[1] = r1;

    UMAAL(r2, carry2, 0, 0);
    r[2] = r2;

    UMAAL(r3, carry2, 0, 0);
    r[3] = r3;

    UMAAL(r4, carry2, 0, 0);
    r[4] = r4;

    UMAAL(r5, carry2, 0, 0);
    r[5] = r5;

    UMAAL(r6, carry2, 0, 0);
    r[6] = r6;

    UMAAL(r7, carry2, carry, 1);
    r[7] = r7;

    UMAAL(r8, carry2, 0, 0);
    r[8] = r8;

    UMAAL(r9, carry2, 0, 0);
    r[9] = r9;

    UMAAL(r10, carry2, 0, 0);
    r[10] = r10;

    UMAAL(r11, carry2, 0, 0);
    r[11] = r11;

    UMAAL(r12, carry2, 0, 0);
    r[12] = r12;

    UMAAL(r13, carry2, 0, 0);
    r[13] = r13;

    // If any errors crop up during tests in the future, first try to uncomment below
    // r[0] += carry;
    // r[7] += carry;
}

inline static void modmul_C448_ct(const spint *a, const spint *b, spint *res) {
    spint z[28];
    mul_C448_ct(a, b, z);
    modred_C448_ct(z, res);
}

ALWAYS_INLINE static void inner_modsqr_C448_ct(const spint *a, spint *res) {
    spint z[28];
    sqr_C448_ct(a, z);
    modred_C448_ct(z, res);
}

inline static void modsqr_C448_ct(const spint *a, spint *res) {
    inner_modsqr_C448_ct(a, res);
}

ALWAYS_INLINE static void mli_C448_ct(const spint *p, const spint q, spint *r) {
    spint b, c;
    b = q - 1;
    spint te, to;

    c = 0;

    te = p[0];
    UMAAL(te, c, te, b);

    to = p[1];
    r[0] = te;
    UMAAL(to, c, to, b);

    te = p[2];
    r[1] = to;
    UMAAL(te, c, te, b);

    to = p[3];
    r[2] = te;
    UMAAL(to, c, to, b);

    te = p[4];
    r[3] = to;
    UMAAL(te, c, te, b);

    to = p[5];
    r[4] = te;
    UMAAL(to, c, to, b);

    te = p[6];
    r[5] = to;
    UMAAL(te, c, te, b);

    to = p[7];
    r[6] = te;
    UMAAL(to, c, to, b);

    te = p[8];
    r[7] = to;
    UMAAL(te, c, te, b);

    to = p[9];
    r[8] = te;
    UMAAL(to, c, to, b);

    te = p[10];
    r[9] = to;
    UMAAL(te, c, te, b);

    to = p[11];
    r[10] = te;
    UMAAL(to, c, to, b);

    te = p[12];
    r[11] = to;
    UMAAL(te, c, te, b);

    to = p[13];
    r[12] = te;
    UMAAL(to, c, to, b);

    r[13] = to;
    r[14] = c;
}

inline static void modmli_C448_ct(const spint *a, const spint b, spint *res) {
    spint z[15], carry = 0;

    mli_C448_ct(a, b, z);

    spint z14 = z[14], r0, r7, t1, t2;
    r0 = z[0];
    t2 = z[1];
    UMAAL(r0, carry, z14, 1);
    UMAAL(t2, carry, 0, 1);

    t1 = z[2];
    res[1] = t2;
    UMAAL(t1, carry, 0, 1);

    t2 = z[3];
    res[2] = t1;
    UMAAL(t2, carry, 0, 1);

    t1 = z[4];
    res[3] = t2;
    UMAAL(t1, carry, 0, 1);

    t2 = z[5];
    res[4] = t1;
    UMAAL(t2, carry, 0, 1);

    t1 = z[6];
    res[5] = t2;
    UMAAL(t1, carry, 0, 1);

    r7 = z[7];
    t2 = z[8];
    res[6] = t1;
    UMAAL(r7, carry, z14, 1);
    UMAAL(t2, carry, 0, 1);

    t1 = z[9];
    res[8] = t2;
    UMAAL(t1, carry, 0, 1);

    t2 = z[10];
    res[9] = t1;
    UMAAL(t2, carry, 0, 1);

    t1 = z[11];
    res[10] = t2;
    UMAAL(t1, carry, 0, 1);

    t2 = z[12];
    res[11] = t1;
    UMAAL(t2, carry, 0, 1);

    t1 = z[13];
    res[12] = t2;
    UMAAL(t1, carry, 0, 1);

    res[13] = t1;

    r0 += carry;
    r7 += carry;

    res[0] = r0;
    res[7] = r7;

    // If any errors crop up during tests in the future, first try to replace the
    // two additions above with the commented code below

    // spint t = carry;
    // UMAAL(res[0], carry, 0, 0);
    // UMAAL(res[1], carry, 0, 0);
    // UMAAL(res[2], carry, 0, 0);
    // UMAAL(res[3], carry, 0, 0);
    // UMAAL(res[4], carry, 0, 0);
    // UMAAL(res[5], carry, 0, 0);
    // UMAAL(res[6], carry, 0, 0);
    // UMAAL(res[7], carry, t, 1);
    // UMAAL(res[8], carry, 0, 0);
    // UMAAL(res[9], carry, 0, 0);
    // UMAAL(res[10], carry, 0, 0);
    // UMAAL(res[11], carry, 0, 0);
    // UMAAL(res[12], carry, 0, 0);
    // UMAAL(res[13], carry, 0, 0);
}

ALWAYS_INLINE static void nres_C448_ct(const spint *a, spint *b) {
#pragma GCC unroll 14
    for (int i = 0; i < 14; i++) {
        b[i] = a[i];
    }
}

ALWAYS_INLINE static void redc_C448_ct(const spint *a, spint *b) {
#pragma GCC unroll 14
    for (int i = 0; i < 14; i++) {
        b[i] = a[i];
    }
    modfsb_C448_ct(b);
}

NOINLINE static void modcmv_C448_ct(int d, const spint *a, volatile spint *b) {
    spint c0, c1, s, t, aux;
    spint r = 0x5aa5a55a;
    c0 = (~d) & (r + 1);
    c1 = d + r;
    for (int i = 0; i < 14; i++) {
        s = a[i];
        t = b[i];
        b[i] = aux = c0 * t + c1 * s;
        b[i] = aux - r * (t + s);
    }
}

NOINLINE static void modcsw_C448_ct(int d, volatile spint *a, volatile spint *b) {
    spint c0, c1, s, t, w, aux;
    spint r = 0x5aa5a55a;
    c0 = (~d) & (r + 1);
    c1 = d + r;
    for (int i = 0; i < 14; i++) {
        s = a[i];
        t = b[i];
        w = r * (t + s);
        b[i] = aux = c0 * t + c1 * s;
        b[i] = aux - w;
        a[i] = aux = c0 * s + c1 * t;
        a[i] = aux - w;
    }
}

inline static void modadd_C448_ct(const spint *a, const spint *b, spint *res) {
    spint tmpres[14];
    spint t = 0, tt, aa, bb;

    asm volatile(
        "ldr   %[aa], [%[a]]\n"
        "ldr   %[bb], [%[b]]\n"
        "umaal %[aa], %[t], %[one], %[bb]\n"
        "str   %[aa], [%[res]]\n"
        "subs  %[tt], %[aa], %[m1]\n"
        
        "ldr   %[aa], [%[a], #4]\n"
        "ldr   %[bb], [%[b], #4]\n"
        "str   %[tt], [%[tmpres]]\n"
        "umaal %[aa], %[t], %[one], %[bb]\n"
        "str   %[aa], [%[res], #4]\n"
        "sbcs  %[tt], %[aa], %[m1]\n"
        
        "ldr   %[aa], [%[a], #8]\n"
        "ldr   %[bb], [%[b], #8]\n"
        "str   %[tt], [%[tmpres], #4]\n"
        "umaal %[aa], %[t], %[one], %[bb]\n"
        "str   %[aa], [%[res], #8]\n"
        "sbcs  %[tt], %[aa], %[m1]\n"
        
        "ldr   %[aa], [%[a], #12]\n"
        "ldr   %[bb], [%[b], #12]\n"
        "str   %[tt], [%[tmpres], #8]\n"
        "umaal %[aa], %[t], %[one], %[bb]\n"
        "str   %[aa], [%[res], #12]\n"
        "sbcs  %[tt], %[aa], %[m1]\n"
        
        "ldr   %[aa], [%[a], #16]\n"
        "ldr   %[bb], [%[b], #16]\n"
        "str   %[tt], [%[tmpres], #12]\n"
        "umaal %[aa], %[t], %[one], %[bb]\n"
        "str   %[aa], [%[res], #16]\n"
        "sbcs  %[tt], %[aa], %[m1]\n"
        
        "ldr   %[aa], [%[a], #20]\n"
        "ldr   %[bb], [%[b], #20]\n"
        "str   %[tt], [%[tmpres], #16]\n"
        "umaal %[aa], %[t], %[one], %[bb]\n"
        "str   %[aa], [%[res], #20]\n"
        "sbcs  %[tt], %[aa], %[m1]\n"
        
        "ldr   %[aa], [%[a], #24]\n"
        "ldr   %[bb], [%[b], #24]\n"
        "str   %[tt], [%[tmpres], #20]\n"
        "umaal %[aa], %[t], %[one], %[bb]\n"
        "str   %[aa], [%[res], #24]\n"
        "sbcs  %[tt], %[aa], %[m1]\n"
        
        "ldr   %[aa], [%[a], #28]\n"
        "ldr   %[bb], [%[b], #28]\n"
        "str   %[tt], [%[tmpres], #24]\n"
        "umaal %[aa], %[t], %[one], %[bb]\n"
        "str   %[aa], [%[res], #28]\n"
        "sbcs  %[tt], %[aa], %[m2]\n"
        
        "ldr   %[aa], [%[a], #32]\n"
        "ldr   %[bb], [%[b], #32]\n"
        "str   %[tt], [%[tmpres], #28]\n"
        "umaal %[aa], %[t], %[one], %[bb]\n"
        "str   %[aa], [%[res], #32]\n"
        "sbcs  %[tt], %[aa], %[m1]\n"
        
        "ldr   %[aa], [%[a], #36]\n"
        "ldr   %[bb], [%[b], #36]\n"
        "str   %[tt], [%[tmpres], #32]\n"
        "umaal %[aa], %[t], %[one], %[bb]\n"
        "str   %[aa], [%[res], #36]\n"
        "sbcs  %[tt], %[aa], %[m1]\n"
        
        "ldr   %[aa], [%[a], #40]\n"
        "ldr   %[bb], [%[b], #40]\n"
        "str   %[tt], [%[tmpres], #36]\n"
        "umaal %[aa], %[t], %[one], %[bb]\n"
        "str   %[aa], [%[res], #40]\n"
        "sbcs  %[tt], %[aa], %[m1]\n"
        
        "ldr   %[aa], [%[a], #44]\n"
        "ldr   %[bb], [%[b], #44]\n"
        "str   %[tt], [%[tmpres], #40]\n"
        "umaal %[aa], %[t], %[one], %[bb]\n"
        "str   %[aa], [%[res], #44]\n"
        "sbcs  %[tt], %[aa], %[m1]\n"
        
        "ldr   %[aa], [%[a], #48]\n"
        "ldr   %[bb], [%[b], #48]\n"
        "str   %[tt], [%[tmpres], #44]\n"
        "umaal %[aa], %[t], %[one], %[bb]\n"
        "str   %[aa], [%[res], #48]\n"
        "sbcs  %[tt], %[aa], %[m1]\n"
        
        "ldr   %[aa], [%[a], #52]\n"
        "ldr   %[bb], [%[b], #52]\n"
        "str   %[tt], [%[tmpres], #48]\n"
        "umaal %[aa], %[t], %[one], %[bb]\n"
        "str   %[aa], [%[res], #52]\n"
        "sbcs  %[tt], %[aa], %[m1]\n"
        "str   %[tt], [%[tmpres], #52]\n"

        "adcs  %[t],  %[t], %[t]\n"
        "itttt ne\n"
        "ldrne %[t], [%[tmpres], #0]\n"
        "ldrne %[tt], [%[tmpres], #4]\n"
        "strne %[t], [%[res], #0]\n"
        "strne %[tt], [%[res], #4]\n"
        "itttt ne\n"
        "ldrne %[t], [%[tmpres], #8]\n"
        "ldrne %[tt], [%[tmpres], #12]\n"
        "strne %[t], [%[res], #8]\n"
        "strne %[tt], [%[res], #12]\n"
        "itttt ne\n"
        "ldrne %[t], [%[tmpres], #16]\n"
        "ldrne %[tt], [%[tmpres], #20]\n"
        "strne %[t], [%[res], #16]\n"
        "strne %[tt], [%[res], #20]\n"
        "itttt ne\n"
        "ldrne %[t], [%[tmpres], #24]\n"
        "ldrne %[tt], [%[tmpres], #28]\n"
        "strne %[t], [%[res], #24]\n"
        "strne %[tt], [%[res], #28]\n"
        "itttt ne\n"
        "ldrne %[t], [%[tmpres], #32]\n"
        "ldrne %[tt], [%[tmpres], #36]\n"
        "strne %[t], [%[res], #32]\n"
        "strne %[tt], [%[res], #36]\n"
        "itttt ne\n"
        "ldrne %[t], [%[tmpres], #40]\n"
        "ldrne %[tt], [%[tmpres], #44]\n"
        "strne %[t], [%[res], #40]\n"
        "strne %[tt], [%[res], #44]\n"
        "itttt ne\n"
        "ldrne %[t], [%[tmpres], #48]\n"
        "ldrne %[tt], [%[tmpres], #52]\n"
        "strne %[t], [%[res], #48]\n"
        "strne %[tt], [%[res], #52]\n"
        : [t] "+&r" (t), [tt] "=&r" (tt), [aa] "=&r" (aa), [bb] "=&r" (bb)
        : [res] "r" (res), [tmpres] "r" (tmpres), [a] "r" (a), [b] "r" (b), [one] "r" (1), [m1] "r" (-1), [m2] "r" (-2)
        : "cc", "memory");
}

inline static void modsub_C448_ct(const spint *a, const spint *b, spint *res) {
    spint t, bb;
    spint t3, t4;
    const spint p0 = 4294967295;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 4294967295;
    const spint p4 = 4294967295;
    const spint p5 = 4294967295;
    const spint p6 = 4294967295;
    const spint p7 = 4294967294;
    const spint p8 = 4294967295;
    const spint p9 = 4294967295;
    const spint p10 = 4294967295;
    const spint p11 = 4294967295;
    const spint p12 = 4294967295;
    const spint p13 = 4294967295;
    asm volatile(
        "ldr  %[t3], [%[a], #0]\n"
        "ldr  %[bb], [%[b], #0]\n"
        "subs %[t3], %[t3], %[bb]\n"

        "ldr  %[t4], [%[a], #4]\n"
        "ldr  %[bb], [%[b], #4]\n"
        "str  %[t3], [%[res], #0]\n"
        "sbcs %[t4], %[t4], %[bb]\n"

        "ldr  %[t3], [%[a], #8]\n"
        "ldr  %[bb], [%[b], #8]\n"
        "str  %[t4], [%[res], #4]\n"
        "sbcs %[t3], %[t3], %[bb]\n"

        "ldr  %[t4], [%[a], #12]\n"
        "ldr  %[bb], [%[b], #12]\n"
        "str  %[t3], [%[res], #8]\n"
        "sbcs %[t4], %[t4], %[bb]\n"

        "ldr  %[t3], [%[a], #16]\n"
        "ldr  %[bb], [%[b], #16]\n"
        "str  %[t4], [%[res], #12]\n"
        "sbcs %[t3], %[t3], %[bb]\n"

        "ldr  %[t4], [%[a], #20]\n"
        "ldr  %[bb], [%[b], #20]\n"
        "str  %[t3], [%[res], #16]\n"
        "sbcs %[t4], %[t4], %[bb]\n"

        "ldr  %[t3], [%[a], #24]\n"
        "ldr  %[bb], [%[b], #24]\n"
        "str  %[t4], [%[res], #20]\n"
        "sbcs %[t3], %[t3], %[bb]\n"

        "ldr  %[t4], [%[a], #28]\n"
        "ldr  %[bb], [%[b], #28]\n"
        "str  %[t3], [%[res], #24]\n"
        "sbcs %[t4], %[t4], %[bb]\n"

        "ldr  %[t3], [%[a], #32]\n"
        "ldr  %[bb], [%[b], #32]\n"
        "str  %[t4], [%[res], #28]\n"
        "sbcs %[t3], %[t3], %[bb]\n"

        "ldr  %[t4], [%[a], #36]\n"
        "ldr  %[bb], [%[b], #36]\n"
        "str  %[t3], [%[res], #32]\n"
        "sbcs %[t4], %[t4], %[bb]\n"

        "ldr  %[t3], [%[a], #40]\n"
        "ldr  %[bb], [%[b], #40]\n"
        "str  %[t4], [%[res], #36]\n"
        "sbcs %[t3], %[t3], %[bb]\n"

        "ldr  %[t4], [%[a], #44]\n"
        "ldr  %[bb], [%[b], #44]\n"
        "str  %[t3], [%[res], #40]\n"
        "sbcs %[t4], %[t4], %[bb]\n"

        "ldr  %[t3], [%[a], #48]\n"
        "ldr  %[bb], [%[b], #48]\n"
        "str  %[t4], [%[res], #44]\n"
        "sbcs %[t3], %[t3], %[bb]\n"

        "ldr  %[t4], [%[a], #52]\n"
        "ldr  %[bb], [%[b], #52]\n"
        "str  %[t3], [%[res], #48]\n"
        "sbcs %[t4], %[t4], %[bb]\n"

        "str  %[t4], [%[res], #52]\n"
        "sbcs %[t], %[t4], %[t4]\n"
        : [t] "=&r" (t), [bb] "=&r" (bb), [t3] "=&r" (t3), [t4] "=&r" (t4)
        : [b] "r" (b), [a] "r" (a), [res] "r" (res)
        : "cc", "memory");
    t = -t | (t4 > p13);
    bb = 0;

    t3 = res[0];
    UMAAL(t3, bb, t, p0);

    t4 = res[1];
    res[0] = t3;
    UMAAL(t4, bb, t, p1);

    t3 = res[2];
    res[1] = t4;
    UMAAL(t3, bb, t, p2);

    t4 = res[3];
    res[2] = t3;
    UMAAL(t4, bb, t, p3);

    t3 = res[4];
    res[3] = t4;
    UMAAL(t3, bb, t, p4);

    t4 = res[5];
    res[4] = t3;
    UMAAL(t4, bb, t, p5);

    t3 = res[6];
    res[5] = t4;
    UMAAL(t3, bb, t, p6);

    t4 = res[7];
    res[6] = t3;
    UMAAL(t4, bb, t, p7);

    t3 = res[8];
    res[7] = t4;
    UMAAL(t3, bb, t, p8);

    t4 = res[9];
    res[8] = t3;
    UMAAL(t4, bb, t, p9);

    t3 = res[10];
    res[9] = t4;
    UMAAL(t3, bb, t, p10);

    t4 = res[11];
    res[10] = t3;
    UMAAL(t4, bb, t, p11);

    t3 = res[12];
    res[11] = t4;
    UMAAL(t3, bb, t, p12);

    t4 = res[13];
    res[12] = t3;
    UMAAL(t4, bb, t, p13);

    res[13] = t4;
}

inline static void modneg_C448_ct(const spint *a, spint *r) {
    spint zero[14] = {0};
    modsub_C448_ct(zero, a, r);
}

static void modshl_C448_ct(int n, spint *a) {
#pragma GCC unroll 13
    for (int i = 13; i > 0; i--) {
        a[i] = (a[i] << n) + (a[i - 1] >> (32 - n));
    }
    a[0] = (a[0] << n);
}

// Only works for n <= 31
static spint modshr_C448_ct(int n, spint *a) {
    spint r = a[0] & ((1 << n) - 1);
#pragma GCC unroll 13
    for (int i = 0; i < 13; i++) {
        a[i] = (a[i] >> n) | (a[i + 1] << (32 - n));
    }
    a[13] = a[13] >> n;
    return r;
}

inline static void modcpy_C448_ct(const spint *a, spint *b) {
#pragma GCC unroll 14
    for (int i = 0; i < 14; i++) {
        b[i] = a[i];
    }
}

ALWAYS_INLINE static int modis0_C448_ct(const spint *a) {
    spint c[14] = {0};
    spint d = 0;
    modcpy_C448_ct(a, c);
    modfsb_C448_ct(c);
    for (int i = 0; i < 14; i++) {
        d |= c[i];
    }
    return 1 - ((d | -d) >> 31);
}

ALWAYS_INLINE static int modis1_C448_ct(const spint *a) {
    spint c[14] = {0};
    spint d = 0;
    redc_C448_ct(a, c);
    c[0] = c[0] - 1;
    for (int i = 0; i < 14; i++) {
        d |= c[i];
    }
    return 1 - ((d | -d) >> 31);
}

ALWAYS_INLINE static int modcmp_C448_ct(const spint *a, const spint *b) {
    spint c[14], d[14];
    int neq = 0;
    redc_C448_ct(a, c);
    redc_C448_ct(b, d);
    for (int i = 0; i < 14; i++) {
        neq |= c[i] ^ d[i];
    }
    neq = (neq | -neq) >> 31;
    return 1 - (neq & 1);
}

ALWAYS_INLINE static int modsign_C448_ct(const spint *a) {
    spint c[14];
    redc_C448_ct(a, c);
    return c[0] % 2;
}

static void modnsqr_C448_ct(spint *a, int n) {
    for (int i = 0; i < n; i++) {
        inner_modsqr_C448_ct(a, a);
    }
}

// Calculate progenitor
NOINLINE static void modpro_C448_ct(const spint *w, spint *z) {
    spint x[14];
    spint t0[14];
    spint t1[14];
    modcpy_C448_ct(w, x);
    modsqr_C448_ct(x, z);
    modmul_C448_ct(x, z, z);
    modsqr_C448_ct(z, z);
    modmul_C448_ct(x, z, z);
    modcpy_C448_ct(z, t0);
    modnsqr_C448_ct(t0, 3);
    modmul_C448_ct(z, t0, z);
    modcpy_C448_ct(z, t0);
    modnsqr_C448_ct(t0, 6);
    modmul_C448_ct(z, t0, t0);
    modcpy_C448_ct(t0, t1);
    modnsqr_C448_ct(t1, 12);
    modmul_C448_ct(t0, t1, t0);
    modcpy_C448_ct(t0, t1);
    modnsqr_C448_ct(t1, 6);
    modmul_C448_ct(z, t1, z);
    modnsqr_C448_ct(t1, 18);
    modmul_C448_ct(t0, t1, t0);
    modcpy_C448_ct(t0, t1);
    modnsqr_C448_ct(t1, 48);
    modmul_C448_ct(t0, t1, t0);
    modcpy_C448_ct(t0, t1);
    modnsqr_C448_ct(t1, 96);
    modmul_C448_ct(t0, t1, t0);
    modnsqr_C448_ct(t0, 30);
    modmul_C448_ct(z, t0, z);
    modsqr_C448_ct(z, t0);
    modmul_C448_ct(x, t0, t0);
    modnsqr_C448_ct(t0, 223);
    modmul_C448_ct(z, t0, z);
}

// Test for quadratic residue, provide progenitor h if available, NULL if not
inline static int modqr_C448_ct(const spint *h, const spint *x) {
    spint r[14];
    if (h == NULL) {
        modpro_C448_ct(x, r);
        modsqr_C448_ct(r, r);
    }
    else {
        modsqr_C448_ct(h, r);
    }
    modmul_C448_ct(r, x, r);
    return modis1_C448_ct(r);
}

// Modular square root, provide progenitor h if available, NULL if not
inline static void modsqrt_C448_ct(const spint *x, const spint *h, spint *r) {
    spint s[14];
    spint y[14];
    if (h == NULL) {
        modpro_C448_ct(x, y);
    }
    else {
        modcpy_C448_ct(h, y);
    }
    modmul_C448_ct(y, x, s);
    modcpy_C448_ct(s, r);
}

// Calculate inverse, provide progenitor h if available
inline static void modinv_C448_ct(const spint *x, const spint *h, spint *z) {
    spint s[14];
    spint t[14];
    if (h == NULL) {
        modpro_C448_ct(x, t);
    }
    else {
        modcpy_C448_ct(h, t);
    }
    modcpy_C448_ct(x, s);
    modnsqr_C448_ct(t, 2);
    modmul_C448_ct(s, t, z);
}

inline static void modzer_C448_ct(spint *a) {
#pragma GCC unroll 14
    for (int i = 0; i < 14; i++) {
        a[i] = 0;
    }
}

inline static void modone_C448_ct(spint *a) {
    a[0] = 1;
#pragma GCC unroll 13
    for (int i = 1; i < 14; i++) {
        a[i] = 0;
    }
}

inline static void modint_C448_ct(int x, spint *a) {
    a[0] = (spint)x;
#pragma GCC unroll 13
    for (int i = 1; i < 14; i++) {
        a[i] = 0;
    }
}

ALWAYS_INLINE static void mod2r_C448_ct(unsigned int r, spint *a) {
    unsigned int n = r >> 5;
    unsigned int m = r & 31;
    modzer_C448_ct(a);
    if (r >= 448) {
        return;
    }
    a[n] = 1 << m;
    nres_C448_ct(a, a);
}

inline static void modimp_C448_ct(const char *b, spint *a) {
    const spint *b32 = (const spint *)b;
#pragma GCC unroll 14
    for (int i = 0; i < 14; i++) {
        a[i] = __builtin_bswap32(b32[13 - i]);
    }
    nres_C448_ct(a, a);
}

// Code for export, not exponentiation
inline static void modexp_C448_ct(const spint *a, char *b) {
    spint c[14], *b32 = (spint *)b;
    redc_C448_ct(a, c);
#pragma GCC unroll 14
    for (int i = 0; i < 14; i++) {
        b32[13 - i] = __builtin_bswap32(c[i]);
    }
}

#define Nlimbs_C448_ct 14
#define Nbits_C448_ct  448
#define Nbytes_C448_ct 56
