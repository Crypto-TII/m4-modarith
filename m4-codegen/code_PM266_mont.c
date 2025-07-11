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

static int modfsb_PM266_ct(spint *a) {
    const spint p0 = 4294967293;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 4294967295;
    const spint p4 = 4294967295;
    const spint p5 = 4294967295;
    const spint p6 = 4294967295;
    const spint p7 = 4294967295;
    const spint p8 = 1023;
    spint a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4], a5 = a[5], a6 = a[6], a7 = a[7], a8 = a[8];
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
        "sbcs   %[a8], %[a8], %[p8]\n"
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
        "it cs\n"
        "strcs %[a8], [%[a], #32]\n"
        "adc    %[r], %[r], %[r]\n"
        : [a0] "+&r" (a0), [a1] "+&r" (a1), [a2] "+&r" (a2), [a3] "+&r" (a3), [a4] "+&r" (a4), [a5] "+&r" (a5), [a6] "+&r" (a6), [a7] "+&r" (a7), [a8] "+&r" (a8), [r] "+&r" (r)
        : [a] "r" (a), [p0] "rI" (p0), [p1] "rI" (p1), [p2] "rI" (p2), [p3] "rI" (p3), [p4] "rI" (p4), [p5] "rI" (p5), [p6] "rI" (p6), [p7] "rI" (p7), [p8] "rI" (p8)
        : "cc", "memory");

    return 1 - r;
}

ALWAYS_INLINE static void mul_PM266_ct(const spint *p, const spint *q, spint *r) {
    spint t0, t1, t2, t3, t4, a, b0, b1, b2, b3;
    a = q[0];
    asm volatile(
        ".p2align 2\n"
        "mov.w  %[t1], #0\n"
        "mov.w  %[t2], #0\n"
        "mov.w  %[t3], #0\n"
        "ldr.w  %[b0], [%[p], #0]\n"
        "ldr.w  %[b1], [%[p], #4]\n"
        "ldr.w  %[b2], [%[p], #8]\n"
        "ldr.w  %[b3], [%[p], #12]\n"
        "umull  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "str.w  %[t0], [%[r], #0]\n"
        "str.w  %[t1], [%[r], #4]\n"
        "str.w  %[t2], [%[r], #8]\n"
        "str.w  %[t3], [%[r], #12]\n"
        "mov.w  %[t0], #0\n"
        "mov.w  %[t1], #0\n"
        "mov.w  %[t2], #0\n"
        "mov.w  %[t3], #0\n"
        "ldr.w  %[b0], [%[p], #16]\n"
        "ldr.w  %[b1], [%[p], #20]\n"
        "ldr.w  %[b2], [%[p], #24]\n"
        "ldr.w  %[b3], [%[p], #28]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "str.w  %[t0], [%[r], #16]\n"
        "str.w  %[t1], [%[r], #20]\n"
        "str.w  %[t2], [%[r], #24]\n"
        "str.w  %[t3], [%[r], #28]\n"
        "mov.w  %[t0], #0\n"
        "ldr.w  %[b0], [%[p], #32]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "str.w  %[t0], [%[r], #32]\n"
        "str.w  %[t4], [%[r], #36]\n"
        : [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [b0] "=&r"(b0),
          [b1] "=&r"(b1), [b2] "=&r"(b2), [b3] "=&r"(b3)
        : [a] "r"(a), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = q[1];
    b1 = q[2];
    b2 = q[3];
    b3 = q[4];
    t0 = r[1];
    t1 = r[2];
    t2 = r[3];
    t3 = r[4];
    t4 = 0;
    asm volatile(
        ".p2align 2\n"
        "ldr.w   %[a], [%[p], #0]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #20]\n"
        "str.w  %[t0], [%[r], #4]\n"
        "mov.w  %[t0], #0\n"
        "adds.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #4]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #24]\n"
        "str.w  %[t1], [%[r], #8]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #8]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #28]\n"
        "str.w  %[t2], [%[r], #12]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #12]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #32]\n"
        "str.w  %[t3], [%[r], #16]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #16]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #36]\n"
        "str.w  %[t4], [%[r], #20]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #20]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #24]\n"
        "str.w  %[t0], [%[r], #24]\n"
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
        "str.w  %[t1], [%[r], #28]\n"
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
        "ldr.w   %[a], [%[p], #32]\n"
        "str.w  %[t2], [%[r], #32]\n"
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
        "str.w  %[t3], [%[r], #36]\n"
        "str.w  %[t4], [%[r], #40]\n"
        "str.w  %[t0], [%[r], #44]\n"
        "str.w  %[t1], [%[r], #48]\n"
        "str.w  %[t2], [%[r], #52]\n"
        "mov.w  %[t3], #0\n"
#ifdef __clang__
        "adcs   %[t3], %[t3], #0\n"
#else
        "adcs.w %[t3], %[t3], #0\n"
#endif
        "str.w  %[t3], [%[r], #56]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = q[5];
    b1 = q[6];
    b2 = q[7];
    b3 = q[8];
    t0 = r[5];
    t1 = r[6];
    t2 = r[7];
    t3 = r[8];
    t4 = 0;
    asm volatile(
        ".p2align 2\n"
        "ldr.w   %[a], [%[p], #0]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #36]\n"
        "str.w  %[t0], [%[r], #20]\n"
        "mov.w  %[t0], #0\n"
        "adds.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #4]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #40]\n"
        "str.w  %[t1], [%[r], #24]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #8]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #44]\n"
        "str.w  %[t2], [%[r], #28]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #12]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #48]\n"
        "str.w  %[t3], [%[r], #32]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #16]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #52]\n"
        "str.w  %[t4], [%[r], #36]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #20]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #56]\n"
        "str.w  %[t0], [%[r], #40]\n"
        "mov.w  %[t0], #0\n"
        "adcs.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #24]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #28]\n"
        "str.w  %[t1], [%[r], #44]\n"
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
        "ldr.w   %[a], [%[p], #32]\n"
        "str.w  %[t2], [%[r], #48]\n"
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
        "str.w  %[t3], [%[r], #52]\n"
        "str.w  %[t4], [%[r], #56]\n"
        "str.w  %[t0], [%[r], #60]\n"
        "str.w  %[t1], [%[r], #64]\n"
        "str.w  %[t2], [%[r], #68]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
}

ALWAYS_INLINE static void sqr_PM266_ct(const spint *p, spint *r) {
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
        "str.w  %[t2], [%[r], #32]\n"
        "str.w  %[t3], [%[r], #36]\n"
        "str.w  %[t4], [%[r], #40]\n"
        "str.w  %[t0], [%[r], #44]\n"
        "str.w  %[t1], [%[r], #48]\n"
        : [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [t0] "=&r"(t0), [t1] "=&r"(t1), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = p[4]; b1 = p[5]; b2 = p[6]; b3 = p[7];
    a = p[8];
    t0 = r[9]; t1 = r[10]; t2 = r[11]; t3 = r[12]; t4 = 0;
    asm volatile(
        ".p2align 2\n"
        "umaal  %[t4], %[t0], %[b0], %[b1]\n"
        "umaal  %[t0], %[t1], %[b0], %[b2]\n"
        "str.w  %[t4], [%[r], #36]\n"
        "str.w  %[t0], [%[r], #40]\n"
        "mov.w  %[t4], #0\n"
        "umaal  %[t1], %[t2], %[b0], %[b3]\n"
        "umaal  %[t1], %[t4], %[b1], %[b2]\n"
        "umaal  %[t2], %[t4], %[b0], %[a]\n"
        "umaal  %[t2], %[t3], %[b1], %[b3]\n"
        "mov.w  %[t0], #0\n"
        "str.w  %[t1], [%[r], #44]\n"
        "str.w  %[t2], [%[r], #48]\n"
        "mov.w  %[t1], #0\n"
        "umaal  %[t3], %[t4], %[b1], %[a]\n"
        "umaal  %[t3], %[t0], %[b2], %[b3]\n"
        "umaal  %[t4], %[t0], %[b2], %[a]\n"
        "umaal  %[t0], %[t1], %[b3], %[a]\n"
        "str.w  %[t3], [%[r], #52]\n"
        "str.w  %[t4], [%[r], #56]\n"
        "str.w  %[t0], [%[r], #60]\n"
        "str.w  %[t1], [%[r], #64]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [a] "r"(a), [r] "r"(r)
        : "memory");
    r[0] = 0;
    r[17] = 0;
    asm volatile(
        ".p2align 2\n"
        "mov.w  %[a], #2\n"
        "mov.w  %[t4], #0\n"
        "ldr.w   %[b0], [%[p], #0]\n"
        "ldr.w   %[b1], [%[p], #4]\n"
        "umull  %[t0], %[t1], %[b0], %[b0]\n"
        "umull  %[t2], %[t3], %[b1], %[b1]\n"
        "ldr.w   %[b0], [%[r], #0]\n"
        "ldr.w   %[b1], [%[r], #4]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "ldr.w   %[b0], [%[r], #8]\n"
        "ldr.w   %[b1], [%[r], #12]\n"
        "str.w  %[t0], [%[r], #0]\n"
        "str.w  %[t1], [%[r], #4]\n"
        "umaal  %[t2], %[t4], %[a], %[b0]\n"
        "umaal  %[t3], %[t4], %[a], %[b1]\n"
        "str.w  %[t2], [%[r], #8]\n"
        "str.w  %[t3], [%[r], #12]\n"
        "ldr.w   %[b2], [%[p], #8]\n"
        "ldr.w   %[b3], [%[p], #12]\n"
        "umull  %[t0], %[t1], %[b2], %[b2]\n"
        "umull  %[t2], %[t3], %[b3], %[b3]\n"
        "ldr.w   %[b2], [%[r], #16]\n"
        "ldr.w   %[b3], [%[r], #20]\n"
        "umaal  %[t0], %[t4], %[a], %[b2]\n"
        "umaal  %[t1], %[t4], %[a], %[b3]\n"
        "ldr.w   %[b2], [%[r], #24]\n"
        "ldr.w   %[b3], [%[r], #28]\n"
        "str.w  %[t0], [%[r], #16]\n"
        "str.w  %[t1], [%[r], #20]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "str.w  %[t2], [%[r], #24]\n"
        "str.w  %[t3], [%[r], #28]\n"
        "ldr.w   %[b0], [%[p], #16]\n"
        "ldr.w   %[b1], [%[p], #20]\n"
        "umull  %[t0], %[t1], %[b0], %[b0]\n"
        "umull  %[t2], %[t3], %[b1], %[b1]\n"
        "ldr.w   %[b0], [%[r], #32]\n"
        "ldr.w   %[b1], [%[r], #36]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "ldr.w   %[b0], [%[r], #40]\n"
        "ldr.w   %[b1], [%[r], #44]\n"
        "str.w  %[t0], [%[r], #32]\n"
        "str.w  %[t1], [%[r], #36]\n"
        "umaal  %[t2], %[t4], %[a], %[b0]\n"
        "umaal  %[t3], %[t4], %[a], %[b1]\n"
        "str.w  %[t2], [%[r], #40]\n"
        "str.w  %[t3], [%[r], #44]\n"
        "ldr.w   %[b2], [%[p], #24]\n"
        "ldr.w   %[b3], [%[p], #28]\n"
        "umull  %[t0], %[t1], %[b2], %[b2]\n"
        "umull  %[t2], %[t3], %[b3], %[b3]\n"
        "ldr.w   %[b2], [%[r], #48]\n"
        "ldr.w   %[b3], [%[r], #52]\n"
        "umaal  %[t0], %[t4], %[a], %[b2]\n"
        "umaal  %[t1], %[t4], %[a], %[b3]\n"
        "ldr.w   %[b2], [%[r], #56]\n"
        "ldr.w   %[b3], [%[r], #60]\n"
        "str.w  %[t0], [%[r], #48]\n"
        "str.w  %[t1], [%[r], #52]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "str.w  %[t2], [%[r], #56]\n"
        "str.w  %[t3], [%[r], #60]\n"
        "ldr.w   %[b0], [%[p], #32]\n"
        "ldr.w   %[b1], [%[r], #64]\n"
        "umull  %[t0], %[t1], %[b0], %[b0]\n"
        "umaal  %[t0], %[t4], %[a], %[b1]\n"
        "add.w  %[t1], %[t1], %[t4]\n"
        "str.w  %[t0], [%[r], #64]\n"
        "str.w  %[t1], [%[r], #68]\n"
        : [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [a] "=&r"(a),
          [b0] "=&r"(b0), [b1] "=&r"(b1), [b2] "=&r"(b2), [b3] "=&r"(b3)
        : [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
}

static void modmul_PM266_ct(const spint *a, const spint *b, spint *res) {
    const spint mu = 2863311531;
    spint A[18];
    spint A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17;
    const spint p0 = 4294967293;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 4294967295;
    const spint p4 = 4294967295;
    const spint p5 = 4294967295;
    const spint p6 = 4294967295;
    const spint p7 = 4294967295;
    const spint p8 = 1023;
    spint q, t, t2 = 0;

    mul_PM266_ct(a, b, A);

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
    A16 = A[16];
    A17 = A[17];

    q = mu * A0;
    t = 0;
    UMAAL(A0, t, q, p0);
    UMAAL(A1, t, q, p1);
    UMAAL(A2, t, q, p2);
    UMAAL(A3, t, q, p3);
    UMAAL(A4, t, q, p4);
    UMAAL(A5, t, q, p5);
    UMAAL(A6, t, q, p6);
    UMAAL(A7, t, q, p7);
    UMAAL(A8, t, q, p8);
    UMAAL(A9, t2, 1, t);

    q = mu * A1;
    t = 0;
    UMAAL(A1, t, q, p0);
    UMAAL(A2, t, q, p1);
    UMAAL(A3, t, q, p2);
    UMAAL(A4, t, q, p3);
    UMAAL(A5, t, q, p4);
    UMAAL(A6, t, q, p5);
    UMAAL(A7, t, q, p6);
    UMAAL(A8, t, q, p7);
    UMAAL(A9, t, q, p8);
    UMAAL(A10, t2, 1, t);

    q = mu * A2;
    t = 0;
    UMAAL(A2, t, q, p0);
    UMAAL(A3, t, q, p1);
    UMAAL(A4, t, q, p2);
    UMAAL(A5, t, q, p3);
    UMAAL(A6, t, q, p4);
    UMAAL(A7, t, q, p5);
    UMAAL(A8, t, q, p6);
    UMAAL(A9, t, q, p7);
    UMAAL(A10, t, q, p8);
    UMAAL(A11, t2, 1, t);

    q = mu * A3;
    t = 0;
    UMAAL(A3, t, q, p0);
    UMAAL(A4, t, q, p1);
    UMAAL(A5, t, q, p2);
    UMAAL(A6, t, q, p3);
    UMAAL(A7, t, q, p4);
    UMAAL(A8, t, q, p5);
    UMAAL(A9, t, q, p6);
    UMAAL(A10, t, q, p7);
    UMAAL(A11, t, q, p8);
    UMAAL(A12, t2, 1, t);

    q = mu * A4;
    t = 0;
    UMAAL(A4, t, q, p0);
    UMAAL(A5, t, q, p1);
    UMAAL(A6, t, q, p2);
    UMAAL(A7, t, q, p3);
    UMAAL(A8, t, q, p4);
    UMAAL(A9, t, q, p5);
    UMAAL(A10, t, q, p6);
    UMAAL(A11, t, q, p7);
    UMAAL(A12, t, q, p8);
    UMAAL(A13, t2, 1, t);

    q = mu * A5;
    t = 0;
    UMAAL(A5, t, q, p0);
    UMAAL(A6, t, q, p1);
    UMAAL(A7, t, q, p2);
    UMAAL(A8, t, q, p3);
    UMAAL(A9, t, q, p4);
    UMAAL(A10, t, q, p5);
    UMAAL(A11, t, q, p6);
    UMAAL(A12, t, q, p7);
    UMAAL(A13, t, q, p8);
    UMAAL(A14, t2, 1, t);

    q = mu * A6;
    t = 0;
    UMAAL(A6, t, q, p0);
    UMAAL(A7, t, q, p1);
    UMAAL(A8, t, q, p2);
    UMAAL(A9, t, q, p3);
    UMAAL(A10, t, q, p4);
    UMAAL(A11, t, q, p5);
    UMAAL(A12, t, q, p6);
    UMAAL(A13, t, q, p7);
    UMAAL(A14, t, q, p8);
    UMAAL(A15, t2, 1, t);

    q = mu * A7;
    t = 0;
    UMAAL(A7, t, q, p0);
    UMAAL(A8, t, q, p1);
    UMAAL(A9, t, q, p2);
    UMAAL(A10, t, q, p3);
    UMAAL(A11, t, q, p4);
    UMAAL(A12, t, q, p5);
    UMAAL(A13, t, q, p6);
    UMAAL(A14, t, q, p7);
    UMAAL(A15, t, q, p8);
    UMAAL(A16, t2, 1, t);

    q = mu * A8;
    t = 0;
    UMAAL(A8, t, q, p0);
    UMAAL(A9, t, q, p1);
    UMAAL(A10, t, q, p2);
    UMAAL(A11, t, q, p3);
    UMAAL(A12, t, q, p4);
    UMAAL(A13, t, q, p5);
    UMAAL(A14, t, q, p6);
    UMAAL(A15, t, q, p7);
    UMAAL(A16, t, q, p8);
    UMAAL(A17, t2, 1, t);

    res[0] = A9;
    res[1] = A10;
    res[2] = A11;
    res[3] = A12;
    res[4] = A13;
    res[5] = A14;
    res[6] = A15;
    res[7] = A16;
    res[8] = A17;
}

ALWAYS_INLINE static void inner_modsqr_PM266_ct(const spint *a, spint *res) {
    const spint mu = 2863311531;
    spint A[18];
    spint A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17;
    const spint p0 = 4294967293;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 4294967295;
    const spint p4 = 4294967295;
    const spint p5 = 4294967295;
    const spint p6 = 4294967295;
    const spint p7 = 4294967295;
    const spint p8 = 1023;
    spint q, t, t2 = 0;

    sqr_PM266_ct(a, A);

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
    A16 = A[16];
    A17 = A[17];

    q = mu * A0;
    t = 0;
    UMAAL(A0, t, q, p0);
    UMAAL(A1, t, q, p1);
    UMAAL(A2, t, q, p2);
    UMAAL(A3, t, q, p3);
    UMAAL(A4, t, q, p4);
    UMAAL(A5, t, q, p5);
    UMAAL(A6, t, q, p6);
    UMAAL(A7, t, q, p7);
    UMAAL(A8, t, q, p8);
    UMAAL(A9, t2, 1, t);

    q = mu * A1;
    t = 0;
    UMAAL(A1, t, q, p0);
    UMAAL(A2, t, q, p1);
    UMAAL(A3, t, q, p2);
    UMAAL(A4, t, q, p3);
    UMAAL(A5, t, q, p4);
    UMAAL(A6, t, q, p5);
    UMAAL(A7, t, q, p6);
    UMAAL(A8, t, q, p7);
    UMAAL(A9, t, q, p8);
    UMAAL(A10, t2, 1, t);

    q = mu * A2;
    t = 0;
    UMAAL(A2, t, q, p0);
    UMAAL(A3, t, q, p1);
    UMAAL(A4, t, q, p2);
    UMAAL(A5, t, q, p3);
    UMAAL(A6, t, q, p4);
    UMAAL(A7, t, q, p5);
    UMAAL(A8, t, q, p6);
    UMAAL(A9, t, q, p7);
    UMAAL(A10, t, q, p8);
    UMAAL(A11, t2, 1, t);

    q = mu * A3;
    t = 0;
    UMAAL(A3, t, q, p0);
    UMAAL(A4, t, q, p1);
    UMAAL(A5, t, q, p2);
    UMAAL(A6, t, q, p3);
    UMAAL(A7, t, q, p4);
    UMAAL(A8, t, q, p5);
    UMAAL(A9, t, q, p6);
    UMAAL(A10, t, q, p7);
    UMAAL(A11, t, q, p8);
    UMAAL(A12, t2, 1, t);

    q = mu * A4;
    t = 0;
    UMAAL(A4, t, q, p0);
    UMAAL(A5, t, q, p1);
    UMAAL(A6, t, q, p2);
    UMAAL(A7, t, q, p3);
    UMAAL(A8, t, q, p4);
    UMAAL(A9, t, q, p5);
    UMAAL(A10, t, q, p6);
    UMAAL(A11, t, q, p7);
    UMAAL(A12, t, q, p8);
    UMAAL(A13, t2, 1, t);

    q = mu * A5;
    t = 0;
    UMAAL(A5, t, q, p0);
    UMAAL(A6, t, q, p1);
    UMAAL(A7, t, q, p2);
    UMAAL(A8, t, q, p3);
    UMAAL(A9, t, q, p4);
    UMAAL(A10, t, q, p5);
    UMAAL(A11, t, q, p6);
    UMAAL(A12, t, q, p7);
    UMAAL(A13, t, q, p8);
    UMAAL(A14, t2, 1, t);

    q = mu * A6;
    t = 0;
    UMAAL(A6, t, q, p0);
    UMAAL(A7, t, q, p1);
    UMAAL(A8, t, q, p2);
    UMAAL(A9, t, q, p3);
    UMAAL(A10, t, q, p4);
    UMAAL(A11, t, q, p5);
    UMAAL(A12, t, q, p6);
    UMAAL(A13, t, q, p7);
    UMAAL(A14, t, q, p8);
    UMAAL(A15, t2, 1, t);

    q = mu * A7;
    t = 0;
    UMAAL(A7, t, q, p0);
    UMAAL(A8, t, q, p1);
    UMAAL(A9, t, q, p2);
    UMAAL(A10, t, q, p3);
    UMAAL(A11, t, q, p4);
    UMAAL(A12, t, q, p5);
    UMAAL(A13, t, q, p6);
    UMAAL(A14, t, q, p7);
    UMAAL(A15, t, q, p8);
    UMAAL(A16, t2, 1, t);

    q = mu * A8;
    t = 0;
    UMAAL(A8, t, q, p0);
    UMAAL(A9, t, q, p1);
    UMAAL(A10, t, q, p2);
    UMAAL(A11, t, q, p3);
    UMAAL(A12, t, q, p4);
    UMAAL(A13, t, q, p5);
    UMAAL(A14, t, q, p6);
    UMAAL(A15, t, q, p7);
    UMAAL(A16, t, q, p8);
    UMAAL(A17, t2, 1, t);

    res[0] = A9;
    res[1] = A10;
    res[2] = A11;
    res[3] = A12;
    res[4] = A13;
    res[5] = A14;
    res[6] = A15;
    res[7] = A16;
    res[8] = A17;
}

static void modsqr_PM266_ct(const spint *a, spint *res) {
    inner_modsqr_PM266_ct(a, res);
}

static void nres_PM266_ct(const spint *a, spint *b) {
    spint nresfactor[] = {0, 36864, 0, 0, 0, 0, 0, 0, 0};
    modmul_PM266_ct(a, nresfactor, b);
}

static void redc_PM266_ct(const spint *a, spint *b) {
    spint rinv[] = {1, 0, 0, 0, 0, 0, 0, 0, 0};
    modmul_PM266_ct(a, rinv, b);
    modfsb_PM266_ct(b);
}

static void modcmv_PM266_ct(int d, const spint *a, volatile spint *b) {
    spint c0, c1, s, t, aux;
    spint r = 0x5aa5a55a;
    c0 = (~d) & (r + 1);
    c1 = d + r;
    for (int i = 0; i < 9; i++) {
        s = a[i];
        t = b[i];
        b[i] = aux = c0 * t + c1 * s;
        b[i] = aux - r * (t + s);
    }
}

static void modcsw_PM266_ct(int d, volatile spint *a, volatile spint *b) {
    spint c0, c1, s, t, w, aux;
    spint r = 0x5aa5a55a;
    c0 = (~d) & (r + 1);
    c1 = d + r;
    for (int i = 0; i < 9; i++) {
        s = a[i];
        t = b[i];
        w = r * (t + s);
        b[i] = aux = c0 * t + c1 * s;
        b[i] = aux - w;
        a[i] = aux = c0 * s + c1 * t;
        a[i] = aux - w;
    }
}

inline static void modadd_PM266_ct(const spint *a, const spint *b, spint *res) {
    spint a0, a1, a2, a3, a4, a5, a6, a7, a8;
    spint b0, b1, b2, b3, b4, b5, b6, b7, b8;
    spint t = 0;
    const spint p0 = 4294967290;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 4294967295;
    const spint p4 = 4294967295;
    const spint p5 = 4294967295;
    const spint p6 = 4294967295;
    const spint p7 = 4294967295;
    const spint p8 = 2047;
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
    a8 = a[8];
    b8 = b[8];
    UMAAL(a8, t, 1, b8);
    res[8] = a8;
    asm volatile(
        "subs %[a0], %[a0], %[p0]\n"
        "sbcs %[a1], %[a1], %[p1]\n"
        "sbcs %[a2], %[a2], %[p2]\n"
        "sbcs %[a3], %[a3], %[p3]\n"
        "sbcs %[a4], %[a4], %[p4]\n"
        "sbcs %[a5], %[a5], %[p5]\n"
        "sbcs %[a6], %[a6], %[p6]\n"
        "sbcs %[a7], %[a7], %[p7]\n"
        "sbcs %[a8], %[a8], %[p8]\n"
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
        "it cs\n"
        "strcs %[a8], [%[res], #32]\n"
        : [a0] "+&r" (a0), [a1] "+&r" (a1), [a2] "+&r" (a2), [a3] "+&r" (a3), [a4] "+&r" (a4), [a5] "+&r" (a5), [a6] "+&r" (a6), [a7] "+&r" (a7), [a8] "+&r" (a8)
        : [res] "r" (res), [p0] "rI" (p0), [p1] "rI" (p1), [p2] "rI" (p2), [p3] "rI" (p3), [p4] "rI" (p4), [p5] "rI" (p5), [p6] "rI" (p6), [p7] "rI" (p7), [p8] "rI" (p8)
        : "cc", "memory");
}

inline static void modsub_PM266_ct(const spint *a, const spint *b, spint *res) {
    spint a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3], a4 = a[4], a5 = a[5], a6 = a[6], a7 = a[7], a8 = a[8];
    spint t, t1, t2;
    const spint p0 = 4294967290;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 4294967295;
    const spint p4 = 4294967295;
    const spint p5 = 4294967295;
    const spint p6 = 4294967295;
    const spint p7 = 4294967295;
    const spint p8 = 2047;
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
        "ldr %[t1], [%[b], #32]\n"
        "sbcs %[a8], %[a8], %[t1]\n"
        "sbcs  %[t], %[t1], %[t1]\n"
        : [a0] "+&r" (a0), [a1] "+&r" (a1), [a2] "+&r" (a2), [a3] "+&r" (a3), [a4] "+&r" (a4), [a5] "+&r" (a5), [a6] "+&r" (a6), [a7] "+&r" (a7), [a8] "+&r" (a8), [t] "=&r" (t), [t1] "=&r" (t1), [t2] "=&r" (t2)
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
    UMAAL(a8, t2, t, p8);
    res[0] = a0;
    res[1] = a1;
    res[2] = a2;
    res[3] = a3;
    res[4] = a4;
    res[5] = a5;
    res[6] = a6;
    res[7] = a7;
    res[8] = a8;
}

static void modneg_PM266_ct(const spint *a, spint *r) {
    spint zero[9] = {0};
    modsub_PM266_ct(zero, a, r);
}

static void modshl_PM266_ct(int n, spint *a) {
#pragma GCC unroll 8
    for (int i = 8; i > 0; i--) {
        a[i] = (a[i] << n) + (a[i - 1] >> (32 - n));
    }
    a[0] = (a[0] << n);
}

// Only works for n <= 31
static spint modshr_PM266_ct(int n, spint *a) {
    spint r = a[0] & ((1 << n) - 1);
#pragma GCC unroll 8
    for (int i = 0; i < 8; i++) {
        a[i] = (a[i] >> n) | (a[i + 1] << (32 - n));
    }
    a[8] = a[8] >> n;
    return r;
}

static void modcpy_PM266_ct(const spint *a, spint *b) {
#pragma GCC unroll 9
    for (int i = 0; i < 9; i++) {
        b[i] = a[i];
    }
}

static int modis0_PM266_ct(const spint *a) {
    spint c[9] = {0};
    spint d = 0;
    modcpy_PM266_ct(a, c);
    modfsb_PM266_ct(c);
    for (int i = 0; i < 9; i++) {
        d |= c[i];
    }
    return 1 - ((d | -d) >> 31);
}

static int modis1_PM266_ct(const spint *a) {
    spint c[9] = {0};
    spint d = 0;
    redc_PM266_ct(a, c);
    c[0] = c[0] - 1;
    for (int i = 0; i < 9; i++) {
        d |= c[i];
    }
    return 1 - ((d | -d) >> 31);
}

static int modcmp_PM266_ct(const spint *a, const spint *b) {
    spint c[9], d[9];
    int neq = 0;
    redc_PM266_ct(a, c);
    redc_PM266_ct(b, d);
    for (int i = 0; i < 9; i++) {
        neq |= c[i] ^ d[i];
    }
    neq = (neq | -neq) >> 31;
    return 1 - (neq & 1);
}

static int modsign_PM266_ct(const spint *a) {
    spint c[9];
    redc_PM266_ct(a, c);
    return c[0] % 2;
}

NOINLINE static void modnsqr_PM266_ct(spint *a, int n) {
    for (int i = 0; i < n; i++) {
        inner_modsqr_PM266_ct(a, a);
    }
}

// Calculate progenitor
NOINLINE static void modpro_PM266_ct(const spint *w, spint *z) {
    spint x[9];
    spint t0[9];
    modcpy_PM266_ct(w, x);
    modsqr_PM266_ct(x, z);
    modmul_PM266_ct(x, z, z);
    modcpy_PM266_ct(z, t0);
    modnsqr_PM266_ct(t0, 2);
    modmul_PM266_ct(z, t0, z);
    modcpy_PM266_ct(z, t0);
    modnsqr_PM266_ct(t0, 4);
    modmul_PM266_ct(z, t0, z);
    modcpy_PM266_ct(z, t0);
    modnsqr_PM266_ct(t0, 8);
    modmul_PM266_ct(z, t0, z);
    modcpy_PM266_ct(z, t0);
    modnsqr_PM266_ct(t0, 16);
    modmul_PM266_ct(z, t0, z);
    modsqr_PM266_ct(z, t0);
    modmul_PM266_ct(x, t0, t0);
    modnsqr_PM266_ct(t0, 32);
    modmul_PM266_ct(z, t0, z);
    modsqr_PM266_ct(z, t0);
    modmul_PM266_ct(x, t0, t0);
    modnsqr_PM266_ct(t0, 65);
    modmul_PM266_ct(z, t0, z);
    modsqr_PM266_ct(z, t0);
    modmul_PM266_ct(x, t0, t0);
    modnsqr_PM266_ct(t0, 131);
    modmul_PM266_ct(z, t0, z);
}

// Test for quadratic residue, provide progenitor h if available, NULL if not
static int modqr_PM266_ct(const spint *h, const spint *x) {
    spint r[9];
    if (h == NULL) {
        modpro_PM266_ct(x, r);
        modsqr_PM266_ct(r, r);
    }
    else {
        modsqr_PM266_ct(h, r);
    }
    modmul_PM266_ct(r, x, r);
    modnsqr_PM266_ct(r, 1);
    return modis1_PM266_ct(r);
}

// Modular square root, provide progenitor h if available, NULL if not
static void modsqrt_PM266_ct(const spint *x, const spint *h, spint *r) {
    spint t[9];
    spint b[9];
    spint v[9];
    spint z[9] = {0xf9d89b35u, 0x2365bab0u, 0x9de7d36eu, 0x587a9a81u, 0x9f639639u, 0xe345a8f8u, 0xefe82c5au, 0x6992e254u, 0xe2u};
    spint s[9];
    spint y[9];
    if (h == NULL) {
        modpro_PM266_ct(x, y);
    }
    else {
        modcpy_PM266_ct(h, y);
    }
    modmul_PM266_ct(y, x, s);
    modmul_PM266_ct(s, y, t);
    nres_PM266_ct(z, z);
    for (int k = 2; k > 1; k--) {
        modcpy_PM266_ct(t, b);
        modnsqr_PM266_ct(b, k-2);
        int d = 1 - modis1_PM266_ct(b);
        modmul_PM266_ct(s, z, v);
        (void)modcmv_PM266_ct(d, v, s);
        modsqr_PM266_ct(z, z);
        modmul_PM266_ct(t, z, v);
        (void)modcmv_PM266_ct(d, v, t);
    }
    modcpy_PM266_ct(s, r);
}

// Calculate inverse, provide progenitor h if available
static void modinv_PM266_ct(const spint *x, const spint *h, spint *z) {
    spint s[9];
    spint t[9];
    if (h == NULL) {
        modpro_PM266_ct(x, t);
    }
    else {
        modcpy_PM266_ct(h, t);
    }
    modcpy_PM266_ct(x, s);
    for (int i = 0; i < (1); i++) {
        modsqr_PM266_ct(s, s);
        modmul_PM266_ct(s, x, s);
    }
    modnsqr_PM266_ct(t, 3);
    modmul_PM266_ct(s, t, z);
}

static void modzer_PM266_ct(spint *a) {
#pragma GCC unroll 9
    for (int i = 0; i < 9; i++) {
        a[i] = 0;
    }
}

static void modone_PM266_ct(spint *a) {
    a[0] = 12582912;
    a[1] = 0;
    a[2] = 0;
    a[3] = 0;
    a[4] = 0;
    a[5] = 0;
    a[6] = 0;
    a[7] = 0;
    a[8] = 0;
}

static void modint_PM266_ct(int x, spint *a) {
    a[0] = (spint)x;
#pragma GCC unroll 8
    for (int i = 1; i < 9; i++) {
        a[i] = 0;
    }
    nres_PM266_ct(a, a);
}

static void mod2r_PM266_ct(unsigned int r, spint *a) {
    unsigned int n = r >> 5;
    unsigned int m = r & 31;
    modzer_PM266_ct(a);
    if (r >= 288) {
        return;
    }
    a[n] = 1 << m;
    nres_PM266_ct(a, a);
}

ALWAYS_INLINE static void mli_PM266_ct(const spint *p, const spint q, spint *r) {
    spint b, t0, t1, t2, t3, t4, t5, t6, t7, t8;
    b = q - 1;
    t8 = 0;
    t0 = p[0];
    UMAAL(t0, t8, t0, b);
    r[0] = t0;
    t0 = p[1];
    t1 = p[2];
    t2 = p[3];
    t3 = p[4];
    t4 = p[5];
    t5 = p[6];
    t6 = p[7];
    t7 = p[8];
    UMAAL(t0, t8, t0, b);
    UMAAL(t1, t8, t1, b);
    UMAAL(t2, t8, t2, b);
    UMAAL(t3, t8, t3, b);
    UMAAL(t4, t8, t4, b);
    UMAAL(t5, t8, t5, b);
    UMAAL(t6, t8, t6, b);
    UMAAL(t7, t8, t7, b);
    r[1] = t0;
    r[2] = t1;
    r[3] = t2;
    r[4] = t3;
    r[5] = t4;
    r[6] = t5;
    r[7] = t6;
    r[8] = t7;
    r[9] = t8;
}

static void modmli_PM266_ct(const spint *p, const spint q, spint *r) {
    spint A[10];
    spint pq0, pq1, pq2, pq3, pq4, pq5, pq6, pq7, pq8;
    mli_PM266_ct(p, q, A);
    spint t = 0, t2 = 0;
    spint sum = A[9] << 22 | A[8] >> 10;
    A[8] = A[8] & 0x3ff;
    pq0 = A[0];
    UMAAL(pq0, t, sum, 3);
    pq1 = A[1];
    UMAAL(pq1, t, sum, 0);
    pq2 = A[2];
    UMAAL(pq2, t, sum, 0);
    pq3 = A[3];
    UMAAL(pq3, t, sum, 0);
    pq4 = A[4];
    UMAAL(pq4, t, sum, 0);
    pq5 = A[5];
    UMAAL(pq5, t, sum, 0);
    pq6 = A[6];
    UMAAL(pq6, t, sum, 0);
    pq7 = A[7];
    UMAAL(pq7, t, sum, 0);
    pq8 = A[8];
    UMAAL(pq8, t, sum, 0);
    t = t << 22 | pq8 >> 10;
    pq8 = pq8 & 0x3ff;
    UMAAL(pq0, t2, t, 3);
    UMAAL(pq1, t2, t, 0);
    UMAAL(pq2, t2, t, 0);
    UMAAL(pq3, t2, t, 0);
    UMAAL(pq4, t2, t, 0);
    UMAAL(pq5, t2, t, 0);
    UMAAL(pq6, t2, t, 0);
    UMAAL(pq7, t2, t, 0);
    UMAAL(pq8, t2, t, 0);
    r[0] = pq0;
    r[1] = pq1;
    r[2] = pq2;
    r[3] = pq3;
    r[4] = pq4;
    r[5] = pq5;
    r[6] = pq6;
    r[7] = pq7;
    r[8] = pq8;
}

static void modimp_PM266_ct(const char *b, spint *a) {
    const spint *b32 = (const spint *)b;
#pragma GCC unroll 9
    for (int i = 0; i < 9; i++) {
        a[i] = __builtin_bswap32(b32[8 - i]);
    }
    nres_PM266_ct(a, a);
}

// Code for export, not exponentiation
static void modexp_PM266_ct(const spint *a, char *b) {
    spint c[9], *b32 = (spint *)b;
    redc_PM266_ct(a, c);
#pragma GCC unroll 9
    for (int i = 0; i < 9; i++) {
        b32[8 - i] = __builtin_bswap32(c[i]);
    }
}

#define Nlimbs_PM266_ct 9
#define Nbits_PM266_ct  266
#define Nbytes_PM266_ct 36
