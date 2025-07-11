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

ALWAYS_INLINE static int modfsb_2611_ct(spint *a) {
    const spint p0 = 4294967295;
    const spint p1 = 536870911;
    spint a0 = a[0], a1 = a[1];
    int r = 0;
    asm volatile(
        "subs   %[a0], %[a0], %[p0]\n"
        "sbcs   %[a1], %[a1], %[p1]\n"
        "it cs\n"
        "strdcs %[a0], %[a1], [%[a], #0]\n"
        "adc    %[r], %[r], %[r]\n"
        : [a0] "+&r" (a0), [a1] "+&r" (a1), [r] "+&r" (r)
        : [a] "r" (a), [p0] "rI" (p0), [p1] "rI" (p1)
        : "cc", "memory");

    return 1 - r;
}

ALWAYS_INLINE static void mul_2611_ct(const spint *p, const spint *q, spint *r) {
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
        "str.w  %[t1], [%[r], #4]\n"
        "str.w  %[t2], [%[r], #8]\n"
        "str.w  %[t0], [%[r], #12]\n"
        : [t1] "=&r"(t1), [t2] "=&r"(t2), [t0] "=&r"(t0), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
}
