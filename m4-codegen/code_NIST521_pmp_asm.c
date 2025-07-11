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

static int modfsb_NIST521_ct(spint *a) {
    const spint p0 = 4294967295;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 4294967295;
    const spint p4 = 4294967295;
    const spint p5 = 4294967295;
    const spint p6 = 4294967295;
    const spint p7 = 4294967295;
    const spint p8 = 4294967295;
    const spint p9 = 4294967295;
    const spint p10 = 4294967295;
    const spint p11 = 4294967295;
    const spint p12 = 4294967295;
    const spint p13 = 4294967295;
    const spint p14 = 4294967295;
    const spint p15 = 4294967295;
    const spint p16 = 511;
    spint t0, t1;
    spint tmpvec[17];
    int r = 0;
    asm volatile(
        "ldr    %[t0], [%[a], #0]\n"
        "subs   %[t0], %[t0], %[p0]\n"
        "ldr    %[t1], [%[a], #4]\n"
        "str    %[t0], [%[tmpvec], #0]\n"
        "sbcs   %[t1], %[t1], %[p1]\n"
        "ldr    %[t0], [%[a], #8]\n"
        "str    %[t1], [%[tmpvec], #4]\n"
        "sbcs   %[t0], %[t0], %[p2]\n"
        "ldr    %[t1], [%[a], #12]\n"
        "str    %[t0], [%[tmpvec], #8]\n"
        "sbcs   %[t1], %[t1], %[p3]\n"
        "ldr    %[t0], [%[a], #16]\n"
        "str    %[t1], [%[tmpvec], #12]\n"
        "sbcs   %[t0], %[t0], %[p4]\n"
        "ldr    %[t1], [%[a], #20]\n"
        "str    %[t0], [%[tmpvec], #16]\n"
        "sbcs   %[t1], %[t1], %[p5]\n"
        "ldr    %[t0], [%[a], #24]\n"
        "str    %[t1], [%[tmpvec], #20]\n"
        "sbcs   %[t0], %[t0], %[p6]\n"
        "ldr    %[t1], [%[a], #28]\n"
        "str    %[t0], [%[tmpvec], #24]\n"
        "sbcs   %[t1], %[t1], %[p7]\n"
        "ldr    %[t0], [%[a], #32]\n"
        "str    %[t1], [%[tmpvec], #28]\n"
        "sbcs   %[t0], %[t0], %[p8]\n"
        "ldr    %[t1], [%[a], #36]\n"
        "str    %[t0], [%[tmpvec], #32]\n"
        "sbcs   %[t1], %[t1], %[p9]\n"
        "ldr    %[t0], [%[a], #40]\n"
        "str    %[t1], [%[tmpvec], #36]\n"
        "sbcs   %[t0], %[t0], %[p10]\n"
        "ldr    %[t1], [%[a], #44]\n"
        "str    %[t0], [%[tmpvec], #40]\n"
        "sbcs   %[t1], %[t1], %[p11]\n"
        "ldr    %[t0], [%[a], #48]\n"
        "str    %[t1], [%[tmpvec], #44]\n"
        "sbcs   %[t0], %[t0], %[p12]\n"
        "ldr    %[t1], [%[a], #52]\n"
        "str    %[t0], [%[tmpvec], #48]\n"
        "sbcs   %[t1], %[t1], %[p13]\n"
        "ldr    %[t0], [%[a], #56]\n"
        "str    %[t1], [%[tmpvec], #52]\n"
        "sbcs   %[t0], %[t0], %[p14]\n"
        "ldr    %[t1], [%[a], #60]\n"
        "str    %[t0], [%[tmpvec], #56]\n"
        "sbcs   %[t1], %[t1], %[p15]\n"
        "ldr    %[t0], [%[a], #64]\n"
        "str    %[t1], [%[tmpvec], #60]\n"
        "sbcs   %[t0], %[t0], %[p16]\n"
        "str    %[t0], [%[tmpvec], #64]\n"
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
        "itttt cs\n"
        "ldrcs %[t0], [%[tmpvec], #56]\n"
        "ldrcs %[t1], [%[tmpvec], #60]\n"
        "strcs %[t0], [%[a], #56]\n"
        "strcs %[t1], [%[a], #60]\n"
        "itt cs\n"
        "ldrcs %[t0], [%[tmpvec], #64]\n"
        "strcs %[t0], [%[a], #64]\n"
        "adc    %[r], %[r], %[r]\n"
        : [t0] "=&r" (t0), [t1] "=&r" (t1), [r] "+&r" (r)
        : [a] "r" (a), [p0] "rI" (p0), [p1] "rI" (p1), [p2] "rI" (p2), [p3] "rI" (p3), [p4] "rI" (p4), [p5] "rI" (p5), [p6] "rI" (p6), [p7] "rI" (p7), [p8] "rI" (p8), [p9] "rI" (p9), [p10] "rI" (p10), [p11] "rI" (p11), [p12] "rI" (p12), [p13] "rI" (p13), [p14] "rI" (p14), [p15] "rI" (p15), [p16] "rI" (p16), [tmpvec] "r" (tmpvec)
        : "cc", "memory");

    return 1 - r;
}

ALWAYS_INLINE static void mul_NIST521_ct(const spint *p, const spint *q, spint *r) {
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
        "mov.w  %[t1], #0\n"
        "mov.w  %[t2], #0\n"
        "mov.w  %[t3], #0\n"
        "ldr.w  %[b0], [%[p], #32]\n"
        "ldr.w  %[b1], [%[p], #36]\n"
        "ldr.w  %[b2], [%[p], #40]\n"
        "ldr.w  %[b3], [%[p], #44]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "str.w  %[t0], [%[r], #32]\n"
        "str.w  %[t1], [%[r], #36]\n"
        "str.w  %[t2], [%[r], #40]\n"
        "str.w  %[t3], [%[r], #44]\n"
        "mov.w  %[t0], #0\n"
        "mov.w  %[t1], #0\n"
        "mov.w  %[t2], #0\n"
        "mov.w  %[t3], #0\n"
        "ldr.w  %[b0], [%[p], #48]\n"
        "ldr.w  %[b1], [%[p], #52]\n"
        "ldr.w  %[b2], [%[p], #56]\n"
        "ldr.w  %[b3], [%[p], #60]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "str.w  %[t0], [%[r], #48]\n"
        "str.w  %[t1], [%[r], #52]\n"
        "str.w  %[t2], [%[r], #56]\n"
        "str.w  %[t3], [%[r], #60]\n"
        "mov.w  %[t0], #0\n"
        "ldr.w  %[b0], [%[p], #64]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "str.w  %[t0], [%[r], #64]\n"
        "str.w  %[t4], [%[r], #68]\n"
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
        "ldr.w   %[a], [%[r], #40]\n"
        "str.w  %[t0], [%[r], #24]\n"
        "mov.w  %[t0], #0\n"
        "adcs.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #24]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #44]\n"
        "str.w  %[t1], [%[r], #28]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #28]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #48]\n"
        "str.w  %[t2], [%[r], #32]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #32]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #52]\n"
        "str.w  %[t3], [%[r], #36]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #36]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #56]\n"
        "str.w  %[t4], [%[r], #40]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #40]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #60]\n"
        "str.w  %[t0], [%[r], #44]\n"
        "mov.w  %[t0], #0\n"
        "adcs.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #44]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #64]\n"
        "str.w  %[t1], [%[r], #48]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #48]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #68]\n"
        "str.w  %[t2], [%[r], #52]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #52]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #56]\n"
        "str.w  %[t3], [%[r], #56]\n"
        "mov.w  %[t3], #0\n"
#ifdef __clang__
        "adcs   %[t2], %[t2], #0\n"
#else
        "adcs.w %[t2], %[t2], #0\n"
#endif
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #60]\n"
        "str.w  %[t4], [%[r], #60]\n"
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
        "ldr.w   %[a], [%[p], #64]\n"
        "str.w  %[t0], [%[r], #64]\n"
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
#ifdef __clang__
        "adcs   %[t0], %[t0], #0\n"
#else
        "adcs.w %[t0], %[t0], #0\n"
#endif
        "str.w  %[t1], [%[r], #68]\n"
        "str.w  %[t2], [%[r], #72]\n"
        "str.w  %[t3], [%[r], #76]\n"
        "str.w  %[t4], [%[r], #80]\n"
        "str.w  %[t0], [%[r], #84]\n"
        "mov.w  %[t1], #0\n"
#ifdef __clang__
        "adcs   %[t1], %[t1], #0\n"
#else
        "adcs.w %[t1], %[t1], #0\n"
#endif
        "str.w  %[t1], [%[r], #88]\n"
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
        "ldr.w   %[a], [%[r], #60]\n"
        "str.w  %[t1], [%[r], #44]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #28]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #64]\n"
        "str.w  %[t2], [%[r], #48]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #32]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #68]\n"
        "str.w  %[t3], [%[r], #52]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #36]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #72]\n"
        "str.w  %[t4], [%[r], #56]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #40]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #76]\n"
        "str.w  %[t0], [%[r], #60]\n"
        "mov.w  %[t0], #0\n"
        "adcs.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #44]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #80]\n"
        "str.w  %[t1], [%[r], #64]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #48]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #84]\n"
        "str.w  %[t2], [%[r], #68]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #52]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #88]\n"
        "str.w  %[t3], [%[r], #72]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #56]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #60]\n"
        "str.w  %[t4], [%[r], #76]\n"
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
        "ldr.w   %[a], [%[p], #64]\n"
        "str.w  %[t0], [%[r], #80]\n"
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
#ifdef __clang__
        "adcs   %[t0], %[t0], #0\n"
#else
        "adcs.w %[t0], %[t0], #0\n"
#endif
        "str.w  %[t1], [%[r], #84]\n"
        "str.w  %[t2], [%[r], #88]\n"
        "str.w  %[t3], [%[r], #92]\n"
        "str.w  %[t4], [%[r], #96]\n"
        "str.w  %[t0], [%[r], #100]\n"
        "mov.w  %[t1], #0\n"
#ifdef __clang__
        "adcs   %[t1], %[t1], #0\n"
#else
        "adcs.w %[t1], %[t1], #0\n"
#endif
        "str.w  %[t1], [%[r], #104]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = q[9];
    b1 = q[10];
    b2 = q[11];
    b3 = q[12];
    t0 = r[9];
    t1 = r[10];
    t2 = r[11];
    t3 = r[12];
    t4 = 0;
    asm volatile(
        ".p2align 2\n"
        "ldr.w   %[a], [%[p], #0]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #52]\n"
        "str.w  %[t0], [%[r], #36]\n"
        "mov.w  %[t0], #0\n"
        "adds.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #4]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #56]\n"
        "str.w  %[t1], [%[r], #40]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #8]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #60]\n"
        "str.w  %[t2], [%[r], #44]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #12]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #64]\n"
        "str.w  %[t3], [%[r], #48]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #16]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #68]\n"
        "str.w  %[t4], [%[r], #52]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #20]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #72]\n"
        "str.w  %[t0], [%[r], #56]\n"
        "mov.w  %[t0], #0\n"
        "adcs.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #24]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #76]\n"
        "str.w  %[t1], [%[r], #60]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #28]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #80]\n"
        "str.w  %[t2], [%[r], #64]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #32]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #84]\n"
        "str.w  %[t3], [%[r], #68]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #36]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #88]\n"
        "str.w  %[t4], [%[r], #72]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #40]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #92]\n"
        "str.w  %[t0], [%[r], #76]\n"
        "mov.w  %[t0], #0\n"
        "adcs.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #44]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #96]\n"
        "str.w  %[t1], [%[r], #80]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #48]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #100]\n"
        "str.w  %[t2], [%[r], #84]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #52]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #104]\n"
        "str.w  %[t3], [%[r], #88]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #56]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #60]\n"
        "str.w  %[t4], [%[r], #92]\n"
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
        "ldr.w   %[a], [%[p], #64]\n"
        "str.w  %[t0], [%[r], #96]\n"
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
#ifdef __clang__
        "adcs   %[t0], %[t0], #0\n"
#else
        "adcs.w %[t0], %[t0], #0\n"
#endif
        "str.w  %[t1], [%[r], #100]\n"
        "str.w  %[t2], [%[r], #104]\n"
        "str.w  %[t3], [%[r], #108]\n"
        "str.w  %[t4], [%[r], #112]\n"
        "str.w  %[t0], [%[r], #116]\n"
        "mov.w  %[t1], #0\n"
#ifdef __clang__
        "adcs   %[t1], %[t1], #0\n"
#else
        "adcs.w %[t1], %[t1], #0\n"
#endif
        "str.w  %[t1], [%[r], #120]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = q[13];
    b1 = q[14];
    b2 = q[15];
    b3 = q[16];
    t0 = r[13];
    t1 = r[14];
    t2 = r[15];
    t3 = r[16];
    t4 = 0;
    asm volatile(
        ".p2align 2\n"
        "ldr.w   %[a], [%[p], #0]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #68]\n"
        "str.w  %[t0], [%[r], #52]\n"
        "mov.w  %[t0], #0\n"
        "adds.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #4]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #72]\n"
        "str.w  %[t1], [%[r], #56]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #8]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #76]\n"
        "str.w  %[t2], [%[r], #60]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #12]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #80]\n"
        "str.w  %[t3], [%[r], #64]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #16]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #84]\n"
        "str.w  %[t4], [%[r], #68]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #20]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #88]\n"
        "str.w  %[t0], [%[r], #72]\n"
        "mov.w  %[t0], #0\n"
        "adcs.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #24]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #92]\n"
        "str.w  %[t1], [%[r], #76]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #28]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #96]\n"
        "str.w  %[t2], [%[r], #80]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #32]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #100]\n"
        "str.w  %[t3], [%[r], #84]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #36]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #104]\n"
        "str.w  %[t4], [%[r], #88]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #40]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #108]\n"
        "str.w  %[t0], [%[r], #92]\n"
        "mov.w  %[t0], #0\n"
        "adcs.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #44]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #112]\n"
        "str.w  %[t1], [%[r], #96]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #48]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #116]\n"
        "str.w  %[t2], [%[r], #100]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #52]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #120]\n"
        "str.w  %[t3], [%[r], #104]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #56]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #60]\n"
        "str.w  %[t4], [%[r], #108]\n"
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
        "ldr.w   %[a], [%[p], #64]\n"
        "str.w  %[t0], [%[r], #112]\n"
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
#ifdef __clang__
        "adcs   %[t0], %[t0], #0\n"
#else
        "adcs.w %[t0], %[t0], #0\n"
#endif
        "str.w  %[t1], [%[r], #116]\n"
        "str.w  %[t2], [%[r], #120]\n"
        "str.w  %[t3], [%[r], #124]\n"
        "str.w  %[t4], [%[r], #128]\n"
        "str.w  %[t0], [%[r], #132]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
}

ALWAYS_INLINE static void sqr_NIST521_ct(const spint *p, spint *r) {
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
        "ldr.w   %[a], [%[p], #56]\n"
        "str.w  %[t2], [%[r], #52]\n"
        "mov.w  %[t2], #0\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #60]\n"
        "str.w  %[t3], [%[r], #56]\n"
        "mov.w  %[t3], #0\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #64]\n"
        "str.w  %[t4], [%[r], #60]\n"
        "mov.w  %[t4], #0\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "str.w  %[t0], [%[r], #64]\n"
        "str.w  %[t1], [%[r], #68]\n"
        "str.w  %[t2], [%[r], #72]\n"
        "str.w  %[t3], [%[r], #76]\n"
        "str.w  %[t4], [%[r], #80]\n"
        : [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [a] "=&r"(a)
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
        "ldr.w   %[a], [%[r], #72]\n"
        "str.w  %[t0], [%[r], #56]\n"
        "mov.w  %[t0], #0\n"
#ifdef __clang__
        "adcs   %[t4], %[t4], %[a]\n"
#else
        "adcs.w %[t4], %[t4], %[a]\n"
#endif
        "ldr.w   %[a], [%[p], #44]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #76]\n"
        "str.w  %[t1], [%[r], #60]\n"
        "mov.w  %[t1], #0\n"
#ifdef __clang__
        "adcs   %[t0], %[t0], %[a]\n"
#else
        "adcs.w %[t0], %[t0], %[a]\n"
#endif
        "ldr.w   %[a], [%[p], #48]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #80]\n"
        "str.w  %[t2], [%[r], #64]\n"
        "mov.w  %[t2], #0\n"
#ifdef __clang__
        "adcs   %[t1], %[t1], %[a]\n"
#else
        "adcs.w %[t1], %[t1], %[a]\n"
#endif
        "ldr.w   %[a], [%[p], #52]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #56]\n"
        "str.w  %[t3], [%[r], #68]\n"
        "mov.w  %[t3], #0\n"
#ifdef __clang__
        "adcs   %[t2], %[t2], #0\n"
#else
        "adcs.w %[t2], %[t2], #0\n"
#endif
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #60]\n"
        "str.w  %[t4], [%[r], #72]\n"
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
        "ldr.w   %[a], [%[p], #64]\n"
        "str.w  %[t0], [%[r], #76]\n"
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
#ifdef __clang__
        "adcs   %[t0], %[t0], #0\n"
#else
        "adcs.w %[t0], %[t0], #0\n"
#endif
        "str.w  %[t1], [%[r], #80]\n"
        "str.w  %[t2], [%[r], #84]\n"
        "str.w  %[t3], [%[r], #88]\n"
        "str.w  %[t4], [%[r], #92]\n"
        "str.w  %[t0], [%[r], #96]\n"
        "mov.w  %[t1], #0\n"
#ifdef __clang__
        "adcs   %[t1], %[t1], #0\n"
#else
        "adcs.w %[t1], %[t1], #0\n"
#endif
        "str.w  %[t1], [%[r], #100]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = p[8];
    b1 = p[9];
    b2 = p[10];
    b3 = p[11];
    t0 = r[17];
    t1 = r[18];
    t2 = r[19];
    t3 = r[20];
    t4 = r[21];
    asm volatile(
        ".p2align 2\n"
        "mov.w  %[a], #0\n"
        "umaal  %[t0], %[a], %[b0], %[b1]\n"
        "str.w  %[t0], [%[r], #68]\n"
        "mov.w  %[t0], #0\n"
        "umaal  %[t1], %[a], %[b0], %[b2]\n"
        "umaal  %[t2], %[a], %[b1], %[b2]\n"
        "ldr.w  %[t0], [%[r], #88]\n"
        "str.w  %[t1], [%[r], #72]\n"
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
        "ldr.w  %[t1], [%[r], #92]\n"
        "str.w  %[t2], [%[r], #76]\n"
        "mov.w  %[t2], #0\n"
#ifdef __clang__
        "adcs   %[t0], %[t0], %[a]\n"
        "adcs   %[t1], %[t1], #0\n"
#else
        "adcs.w %[t0], %[t0], %[a]\n"
        "adcs.w %[t1], %[t1], #0\n"
#endif
        "ldr.w   %[a], [%[p], #48]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #96]\n"
        "str.w  %[t3], [%[r], #80]\n"
        "mov.w  %[t3], #0\n"
#ifdef __clang__
        "adcs   %[t2], %[t2], %[a]\n"
#else
        "adcs.w %[t2], %[t2], %[a]\n"
#endif
        "ldr.w   %[a], [%[p], #52]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #100]\n"
        "str.w  %[t4], [%[r], #84]\n"
        "mov.w  %[t4], #0\n"
#ifdef __clang__
        "adcs   %[t3], %[t3], %[a]\n"
#else
        "adcs.w %[t3], %[t3], %[a]\n"
#endif
        "ldr.w   %[a], [%[p], #56]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #60]\n"
        "str.w  %[t0], [%[r], #88]\n"
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
        "ldr.w   %[a], [%[p], #64]\n"
        "str.w  %[t1], [%[r], #92]\n"
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
        "str.w  %[t2], [%[r], #96]\n"
        "str.w  %[t3], [%[r], #100]\n"
        "str.w  %[t4], [%[r], #104]\n"
        "str.w  %[t0], [%[r], #108]\n"
        "str.w  %[t1], [%[r], #112]\n"
        "mov.w  %[t2], #0\n"
#ifdef __clang__
        "adcs   %[t2], %[t2], #0\n"
#else
        "adcs.w %[t2], %[t2], #0\n"
#endif
        "str.w  %[t2], [%[r], #116]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = p[12]; b1 = p[13]; b2 = p[14]; b3 = p[15];
    a = p[16];
    t0 = r[25]; t1 = r[26]; t2 = r[27]; t3 = r[28]; t4 = 0;
    asm volatile(
        ".p2align 2\n"
        "umaal  %[t4], %[t0], %[b0], %[b1]\n"
        "umaal  %[t0], %[t1], %[b0], %[b2]\n"
        "str.w  %[t4], [%[r], #100]\n"
        "str.w  %[t0], [%[r], #104]\n"
        "mov.w  %[t4], #0\n"
        "umaal  %[t1], %[t2], %[b0], %[b3]\n"
        "umaal  %[t1], %[t4], %[b1], %[b2]\n"
        "umaal  %[t2], %[t4], %[b0], %[a]\n"
        "umaal  %[t2], %[t3], %[b1], %[b3]\n"
        "ldr.w   %[t0], [%[r], #116]\n"
        "str.w  %[t1], [%[r], #108]\n"
        "str.w  %[t2], [%[r], #112]\n"
        "mov.w  %[t1], #0\n"
        "umaal  %[t3], %[t4], %[b1], %[a]\n"
        "umaal  %[t3], %[t0], %[b2], %[b3]\n"
        "umaal  %[t4], %[t0], %[b2], %[a]\n"
        "umaal  %[t0], %[t1], %[b3], %[a]\n"
        "str.w  %[t3], [%[r], #116]\n"
        "str.w  %[t4], [%[r], #120]\n"
        "str.w  %[t0], [%[r], #124]\n"
        "str.w  %[t1], [%[r], #128]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [a] "r"(a), [r] "r"(r)
        : "memory");
    r[0] = 0;
    r[33] = 0;
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
        "ldr.w   %[b1], [%[p], #36]\n"
        "umull  %[t0], %[t1], %[b0], %[b0]\n"
        "umull  %[t2], %[t3], %[b1], %[b1]\n"
        "ldr.w   %[b0], [%[r], #64]\n"
        "ldr.w   %[b1], [%[r], #68]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "ldr.w   %[b0], [%[r], #72]\n"
        "ldr.w   %[b1], [%[r], #76]\n"
        "str.w  %[t0], [%[r], #64]\n"
        "str.w  %[t1], [%[r], #68]\n"
        "umaal  %[t2], %[t4], %[a], %[b0]\n"
        "umaal  %[t3], %[t4], %[a], %[b1]\n"
        "str.w  %[t2], [%[r], #72]\n"
        "str.w  %[t3], [%[r], #76]\n"
        "ldr.w   %[b2], [%[p], #40]\n"
        "ldr.w   %[b3], [%[p], #44]\n"
        "umull  %[t0], %[t1], %[b2], %[b2]\n"
        "umull  %[t2], %[t3], %[b3], %[b3]\n"
        "ldr.w   %[b2], [%[r], #80]\n"
        "ldr.w   %[b3], [%[r], #84]\n"
        "umaal  %[t0], %[t4], %[a], %[b2]\n"
        "umaal  %[t1], %[t4], %[a], %[b3]\n"
        "ldr.w   %[b2], [%[r], #88]\n"
        "ldr.w   %[b3], [%[r], #92]\n"
        "str.w  %[t0], [%[r], #80]\n"
        "str.w  %[t1], [%[r], #84]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "str.w  %[t2], [%[r], #88]\n"
        "str.w  %[t3], [%[r], #92]\n"
        "ldr.w   %[b0], [%[p], #48]\n"
        "ldr.w   %[b1], [%[p], #52]\n"
        "umull  %[t0], %[t1], %[b0], %[b0]\n"
        "umull  %[t2], %[t3], %[b1], %[b1]\n"
        "ldr.w   %[b0], [%[r], #96]\n"
        "ldr.w   %[b1], [%[r], #100]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "ldr.w   %[b0], [%[r], #104]\n"
        "ldr.w   %[b1], [%[r], #108]\n"
        "str.w  %[t0], [%[r], #96]\n"
        "str.w  %[t1], [%[r], #100]\n"
        "umaal  %[t2], %[t4], %[a], %[b0]\n"
        "umaal  %[t3], %[t4], %[a], %[b1]\n"
        "str.w  %[t2], [%[r], #104]\n"
        "str.w  %[t3], [%[r], #108]\n"
        "ldr.w   %[b2], [%[p], #56]\n"
        "ldr.w   %[b3], [%[p], #60]\n"
        "umull  %[t0], %[t1], %[b2], %[b2]\n"
        "umull  %[t2], %[t3], %[b3], %[b3]\n"
        "ldr.w   %[b2], [%[r], #112]\n"
        "ldr.w   %[b3], [%[r], #116]\n"
        "umaal  %[t0], %[t4], %[a], %[b2]\n"
        "umaal  %[t1], %[t4], %[a], %[b3]\n"
        "ldr.w   %[b2], [%[r], #120]\n"
        "ldr.w   %[b3], [%[r], #124]\n"
        "str.w  %[t0], [%[r], #112]\n"
        "str.w  %[t1], [%[r], #116]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "str.w  %[t2], [%[r], #120]\n"
        "str.w  %[t3], [%[r], #124]\n"
        "ldr.w   %[b0], [%[p], #64]\n"
        "ldr.w   %[b1], [%[r], #128]\n"
        "umull  %[t0], %[t1], %[b0], %[b0]\n"
        "umaal  %[t0], %[t4], %[a], %[b1]\n"
        "add.w  %[t1], %[t1], %[t4]\n"
        "str.w  %[t0], [%[r], #128]\n"
        "str.w  %[t1], [%[r], #132]\n"
        : [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [a] "=&r"(a),
          [b0] "=&r"(b0), [b1] "=&r"(b1), [b2] "=&r"(b2), [b3] "=&r"(b3)
        : [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
}

static void modred_NIST521_ct(const spint *c, spint *r) {
    spint t, rH, rT, cc = 0;

    rH = c[15];
    UMAAL(rH, cc, c[32], 1 << 23);

    rT = c[16];
    UMAAL(rT, cc, c[33], 1 << 23);
    cc = 1 * ((cc << 23) | (rT >> 9));
    rT &= 0x000001ff;

    t = c[0];
    UMAAL(t, cc, c[17], 1 << 23);
    r[0] = t;

    t = c[1];
    UMAAL(t, cc, c[18], 1 << 23);
    r[1] = t;

    t = c[2];
    UMAAL(t, cc, c[19], 1 << 23);
    r[2] = t;

    t = c[3];
    UMAAL(t, cc, c[20], 1 << 23);
    r[3] = t;

    t = c[4];
    UMAAL(t, cc, c[21], 1 << 23);
    r[4] = t;

    t = c[5];
    UMAAL(t, cc, c[22], 1 << 23);
    r[5] = t;

    t = c[6];
    UMAAL(t, cc, c[23], 1 << 23);
    r[6] = t;

    t = c[7];
    UMAAL(t, cc, c[24], 1 << 23);
    r[7] = t;

    t = c[8];
    UMAAL(t, cc, c[25], 1 << 23);
    r[8] = t;

    t = c[9];
    UMAAL(t, cc, c[26], 1 << 23);
    r[9] = t;

    t = c[10];
    UMAAL(t, cc, c[27], 1 << 23);
    r[10] = t;

    t = c[11];
    UMAAL(t, cc, c[28], 1 << 23);
    r[11] = t;

    t = c[12];
    UMAAL(t, cc, c[29], 1 << 23);
    r[12] = t;

    t = c[13];
    UMAAL(t, cc, c[30], 1 << 23);
    r[13] = t;

    t = c[14];
    UMAAL(t, cc, c[31], 1 << 23);
    r[14] = t;

    UMAAL(rH, cc, 0, 0);
    r[15] = rH;

    r[16] = rT + cc;
}

static void modmul_NIST521_ct(const spint *a, const spint *b, spint *res) {
    spint z[34];
    mul_NIST521_ct(a, b, z);
    modred_NIST521_ct(z, res);
}

ALWAYS_INLINE static void inner_modsqr_NIST521_ct(const spint *a, spint *res) {
    spint z[34];
    sqr_NIST521_ct(a, z);
    modred_NIST521_ct(z, res);
}

static void modsqr_NIST521_ct(const spint *a, spint *res) {
    inner_modsqr_NIST521_ct(a, res);
}

static void nres_NIST521_ct(const spint *a, spint *b) {
    b[0] = a[0];
    b[1] = a[1];
    b[2] = a[2];
    b[3] = a[3];
    b[4] = a[4];
    b[5] = a[5];
    b[6] = a[6];
    b[7] = a[7];
    b[8] = a[8];
    b[9] = a[9];
    b[10] = a[10];
    b[11] = a[11];
    b[12] = a[12];
    b[13] = a[13];
    b[14] = a[14];
    b[15] = a[15];
    b[16] = a[16];
}

static void redc_NIST521_ct(const spint *a, spint *b) {
    b[0] = a[0];
    b[1] = a[1];
    b[2] = a[2];
    b[3] = a[3];
    b[4] = a[4];
    b[5] = a[5];
    b[6] = a[6];
    b[7] = a[7];
    b[8] = a[8];
    b[9] = a[9];
    b[10] = a[10];
    b[11] = a[11];
    b[12] = a[12];
    b[13] = a[13];
    b[14] = a[14];
    b[15] = a[15];
    b[16] = a[16];
    modfsb_NIST521_ct(b);
}

static void modcmv_NIST521_ct(int d, const spint *a, volatile spint *b) {
    spint c0, c1, s, t, aux;
    spint r = 0x5aa5a55a;
    c0 = (~d) & (r + 1);
    c1 = d + r;
    for (int i = 0; i < 17; i++) {
        s = a[i];
        t = b[i];
        b[i] = aux = c0 * t + c1 * s;
        b[i] = aux - r * (t + s);
    }
}

static void modcsw_NIST521_ct(int d, volatile spint *a, volatile spint *b) {
    spint c0, c1, s, t, w, aux;
    spint r = 0x5aa5a55a;
    c0 = (~d) & (r + 1);
    c1 = d + r;
    for (int i = 0; i < 17; i++) {
        s = a[i];
        t = b[i];
        w = r * (t + s);
        b[i] = aux = c0 * t + c1 * s;
        b[i] = aux - w;
        a[i] = aux = c0 * s + c1 * t;
        a[i] = aux - w;
    }
}

inline static void modadd_NIST521_ct(const spint *a, const spint *b, spint *res) {
    spint t = 0;
    spint a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16;
    spint b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15, b16;
    a16 = a[16];
    b16 = b[16];
    UMAAL(a16, t, 1, b16);
    t = 1 * ((a16 >> 9) + (t << 23));
    a16 = a16 & 0x1ff;
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
    a9 = a[9];
    b9 = b[9];
    UMAAL(a9, t, 1, b9);
    res[9] = a9;
    a10 = a[10];
    b10 = b[10];
    UMAAL(a10, t, 1, b10);
    res[10] = a10;
    a11 = a[11];
    b11 = b[11];
    UMAAL(a11, t, 1, b11);
    res[11] = a11;
    a12 = a[12];
    b12 = b[12];
    UMAAL(a12, t, 1, b12);
    res[12] = a12;
    a13 = a[13];
    b13 = b[13];
    UMAAL(a13, t, 1, b13);
    res[13] = a13;
    a14 = a[14];
    b14 = b[14];
    UMAAL(a14, t, 1, b14);
    res[14] = a14;
    a15 = a[15];
    b15 = b[15];
    UMAAL(a15, t, 1, b15);
    res[15] = a15;
    UMAAL(a16, t, 0, 0);
    res[16] = a16;
}

inline static void modsub_NIST521_ct(const spint *a, const spint *b, spint *res) {
    spint ae, ao;
    spint t, t1, t2;
    spint t3, t4;
    const spint p0 = 4294967295;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 4294967295;
    const spint p4 = 4294967295;
    const spint p5 = 4294967295;
    const spint p6 = 4294967295;
    const spint p7 = 4294967295;
    const spint p8 = 4294967295;
    const spint p9 = 4294967295;
    const spint p10 = 4294967295;
    const spint p11 = 4294967295;
    const spint p12 = 4294967295;
    const spint p13 = 4294967295;
    const spint p14 = 4294967295;
    const spint p15 = 4294967295;
    const spint p16 = 511;
    asm volatile(
        "ldr    %[t3], [%[a], #0]\n"
        "ldr    %[t4], [%[b], #0]\n"
        "subs   %[t3], %[t3], %[t4]\n"
        "ldr    %[t1], [%[a], #4]\n"
        "ldr    %[t4], [%[b], #4]\n"
        "str    %[t3], [%[res], #0]\n"
        "sbcs   %[t1], %[t1], %[t4]\n"
        "ldr    %[t3], [%[a], #8]\n"
        "ldr    %[t4], [%[b], #8]\n"
        "str    %[t1], [%[res], #4]\n"
        "sbcs   %[t3], %[t3], %[t4]\n"
        "ldr    %[t1], [%[a], #12]\n"
        "ldr    %[t4], [%[b], #12]\n"
        "str    %[t3], [%[res], #8]\n"
        "sbcs   %[t1], %[t1], %[t4]\n"
        "ldr    %[t3], [%[a], #16]\n"
        "ldr    %[t4], [%[b], #16]\n"
        "str    %[t1], [%[res], #12]\n"
        "sbcs   %[t3], %[t3], %[t4]\n"
        "ldr    %[t1], [%[a], #20]\n"
        "ldr    %[t4], [%[b], #20]\n"
        "str    %[t3], [%[res], #16]\n"
        "sbcs   %[t1], %[t1], %[t4]\n"
        "ldr    %[t3], [%[a], #24]\n"
        "ldr    %[t4], [%[b], #24]\n"
        "str    %[t1], [%[res], #20]\n"
        "sbcs   %[t3], %[t3], %[t4]\n"
        "ldr    %[t1], [%[a], #28]\n"
        "ldr    %[t4], [%[b], #28]\n"
        "str    %[t3], [%[res], #24]\n"
        "sbcs   %[t1], %[t1], %[t4]\n"
        "ldr    %[t3], [%[a], #32]\n"
        "ldr    %[t4], [%[b], #32]\n"
        "str    %[t1], [%[res], #28]\n"
        "sbcs   %[t3], %[t3], %[t4]\n"
        "ldr    %[t1], [%[a], #36]\n"
        "ldr    %[t4], [%[b], #36]\n"
        "str    %[t3], [%[res], #32]\n"
        "sbcs   %[t1], %[t1], %[t4]\n"
        "ldr    %[t3], [%[a], #40]\n"
        "ldr    %[t4], [%[b], #40]\n"
        "str    %[t1], [%[res], #36]\n"
        "sbcs   %[t3], %[t3], %[t4]\n"
        "ldr    %[t1], [%[a], #44]\n"
        "ldr    %[t4], [%[b], #44]\n"
        "str    %[t3], [%[res], #40]\n"
        "sbcs   %[t1], %[t1], %[t4]\n"
        "ldr    %[t3], [%[a], #48]\n"
        "ldr    %[t4], [%[b], #48]\n"
        "str    %[t1], [%[res], #44]\n"
        "sbcs   %[t3], %[t3], %[t4]\n"
        "ldr    %[t1], [%[a], #52]\n"
        "ldr    %[t4], [%[b], #52]\n"
        "str    %[t3], [%[res], #48]\n"
        "sbcs   %[t1], %[t1], %[t4]\n"
        "ldr    %[t3], [%[a], #56]\n"
        "ldr    %[t4], [%[b], #56]\n"
        "str    %[t1], [%[res], #52]\n"
        "sbcs   %[t3], %[t3], %[t4]\n"
        "ldr    %[t1], [%[a], #60]\n"
        "ldr    %[t4], [%[b], #60]\n"
        "str    %[t3], [%[res], #56]\n"
        "sbcs   %[t1], %[t1], %[t4]\n"
        "ldr    %[t3], [%[a], #64]\n"
        "ldr    %[t4], [%[b], #64]\n"
        "str    %[t1], [%[res], #60]\n"
        "sbcs   %[t3], %[t3], %[t4]\n"
        "str    %[t3], [%[res], #64]\n"
        "sbcs    %[t], %[t3], %[t3]\n"
        : [t] "=&r" (t), [t1] "=&r" (t1), [t2] "=&r" (t2), [t3] "=&r" (t3), [t4] "=&r" (t4)
        : [b] "r" (b), [a] "r" (a), [res] "r" (res)
        : "cc", "memory");
    t = -t | (t3 > p16);
    t2 = 0;
    ae = res[0];
    UMAAL(ae, t2, t, p0);
    ao = res[1];
    res[0] = ae;
    UMAAL(ao, t2, t, p1);
    ae = res[2];
    res[1] = ao;
    UMAAL(ae, t2, t, p2);
    ao = res[3];
    res[2] = ae;
    UMAAL(ao, t2, t, p3);
    ae = res[4];
    res[3] = ao;
    UMAAL(ae, t2, t, p4);
    ao = res[5];
    res[4] = ae;
    UMAAL(ao, t2, t, p5);
    ae = res[6];
    res[5] = ao;
    UMAAL(ae, t2, t, p6);
    ao = res[7];
    res[6] = ae;
    UMAAL(ao, t2, t, p7);
    ae = res[8];
    res[7] = ao;
    UMAAL(ae, t2, t, p8);
    ao = res[9];
    res[8] = ae;
    UMAAL(ao, t2, t, p9);
    ae = res[10];
    res[9] = ao;
    UMAAL(ae, t2, t, p10);
    ao = res[11];
    res[10] = ae;
    UMAAL(ao, t2, t, p11);
    ae = res[12];
    res[11] = ao;
    UMAAL(ae, t2, t, p12);
    ao = res[13];
    res[12] = ae;
    UMAAL(ao, t2, t, p13);
    ae = res[14];
    res[13] = ao;
    UMAAL(ae, t2, t, p14);
    ao = res[15];
    res[14] = ae;
    UMAAL(ao, t2, t, p15);
    ae = res[16];
    res[15] = ao;
    UMAAL(ae, t2, t, p16);
    res[16] = ae;
}

static void modneg_NIST521_ct(const spint *a, spint *r) {
    spint zero[17] = {0};
    modsub_NIST521_ct(zero, a, r);
}

static void modshl_NIST521_ct(int n, spint *a) {
#pragma GCC unroll 16
    for (int i = 16; i > 0; i--) {
        a[i] = (a[i] << n) + (a[i - 1] >> (32 - n));
    }
    a[0] = (a[0] << n);
}

// Only works for n <= 31
static spint modshr_NIST521_ct(int n, spint *a) {
    spint r = a[0] & ((1 << n) - 1);
#pragma GCC unroll 16
    for (int i = 0; i < 16; i++) {
        a[i] = (a[i] >> n) | (a[i + 1] << (32 - n));
    }
    a[16] = a[16] >> n;
    return r;
}

static void modcpy_NIST521_ct(const spint *a, spint *b) {
#pragma GCC unroll 17
    for (int i = 0; i < 17; i++) {
        b[i] = a[i];
    }
}

static int modis0_NIST521_ct(const spint *a) {
    spint c[17] = {0};
    spint d = 0;
    modcpy_NIST521_ct(a, c);
    modfsb_NIST521_ct(c);
    for (int i = 0; i < 17; i++) {
        d |= c[i];
    }
    return 1 - ((d | -d) >> 31);
}

static int modis1_NIST521_ct(const spint *a) {
    spint c[17] = {0};
    spint d = 0;
    redc_NIST521_ct(a, c);
    c[0] = c[0] - 1;
    for (int i = 0; i < 17; i++) {
        d |= c[i];
    }
    return 1 - ((d | -d) >> 31);
}

static int modcmp_NIST521_ct(const spint *a, const spint *b) {
    spint c[17], d[17];
    int neq = 0;
    redc_NIST521_ct(a, c);
    redc_NIST521_ct(b, d);
    for (int i = 0; i < 17; i++) {
        neq |= c[i] ^ d[i];
    }
    neq = (neq | -neq) >> 31;
    return 1 - (neq & 1);
}

static int modsign_NIST521_ct(const spint *a) {
    spint c[17];
    redc_NIST521_ct(a, c);
    return c[0] % 2;
}

NOINLINE static void modnsqr_NIST521_ct(spint *a, int n) {
    for (int i = 0; i < n; i++) {
        inner_modsqr_NIST521_ct(a, a);
    }
}

// Calculate progenitor
NOINLINE static void modpro_NIST521_ct(const spint *w, spint *z) {
    spint x[17];
    spint t0[17];
    modcpy_NIST521_ct(w, x);
    modsqr_NIST521_ct(x, z);
    modmul_NIST521_ct(x, z, z);
    modcpy_NIST521_ct(z, t0);
    modnsqr_NIST521_ct(t0, 2);
    modmul_NIST521_ct(z, t0, z);
    modcpy_NIST521_ct(z, t0);
    modnsqr_NIST521_ct(t0, 4);
    modmul_NIST521_ct(z, t0, z);
    modcpy_NIST521_ct(z, t0);
    modnsqr_NIST521_ct(t0, 8);
    modmul_NIST521_ct(z, t0, z);
    modcpy_NIST521_ct(z, t0);
    modnsqr_NIST521_ct(t0, 16);
    modmul_NIST521_ct(z, t0, z);
    modcpy_NIST521_ct(z, t0);
    modnsqr_NIST521_ct(t0, 32);
    modmul_NIST521_ct(z, t0, z);
    modsqr_NIST521_ct(z, t0);
    modmul_NIST521_ct(x, t0, t0);
    modnsqr_NIST521_ct(t0, 64);
    modmul_NIST521_ct(z, t0, z);
    modsqr_NIST521_ct(z, t0);
    modmul_NIST521_ct(x, t0, t0);
    modnsqr_NIST521_ct(t0, 129);
    modmul_NIST521_ct(z, t0, z);
    modsqr_NIST521_ct(z, t0);
    modmul_NIST521_ct(x, t0, t0);
    modnsqr_NIST521_ct(t0, 259);
    modmul_NIST521_ct(z, t0, z);
}

// Test for quadratic residue, provide progenitor h if available, NULL if not
static int modqr_NIST521_ct(const spint *h, const spint *x) {
    spint r[17];
    if (h == NULL) {
        modpro_NIST521_ct(x, r);
        modsqr_NIST521_ct(r, r);
    }
    else {
        modsqr_NIST521_ct(h, r);
    }
    modmul_NIST521_ct(r, x, r);
    return modis1_NIST521_ct(r);
}

// Modular square root, provide progenitor h if available, NULL if not
static void modsqrt_NIST521_ct(const spint *x, const spint *h, spint *r) {
    spint s[17];
    spint y[17];
    if (h == NULL) {
        modpro_NIST521_ct(x, y);
    }
    else {
        modcpy_NIST521_ct(h, y);
    }
    modmul_NIST521_ct(y, x, s);
    modcpy_NIST521_ct(s, r);
}

// Calculate inverse, provide progenitor h if available
static void modinv_NIST521_ct(const spint *x, const spint *h, spint *z) {
    spint s[17];
    spint t[17];
    if (h == NULL) {
        modpro_NIST521_ct(x, t);
    }
    else {
        modcpy_NIST521_ct(h, t);
    }
    modcpy_NIST521_ct(x, s);
    modnsqr_NIST521_ct(t, 2);
    modmul_NIST521_ct(s, t, z);
}

static void modzer_NIST521_ct(spint *a) {
#pragma GCC unroll 17
    for (int i = 0; i < 17; i++) {
        a[i] = 0;
    }
}

static void modone_NIST521_ct(spint *a) {
    a[0] = 1;
#pragma GCC unroll 16
    for (int i = 1; i < 17; i++) {
        a[i] = 0;
    }
}

static void modint_NIST521_ct(int x, spint *a) {
    a[0] = (spint)x;
#pragma GCC unroll 16
    for (int i = 1; i < 17; i++) {
        a[i] = 0;
    }
}

static void mod2r_NIST521_ct(unsigned int r, spint *a) {
    unsigned int n = r >> 5;
    unsigned int m = r & 31;
    modzer_NIST521_ct(a);
    if (r >= 522) {
        return;
    }
    a[n] = 1 << m;
    nres_NIST521_ct(a, a);
}

static void modmli_NIST521_ct(const spint *p, const spint q, spint *r) {
    spint t0, t1, t2, t3, t4, t5, t6, t7, t8, b;
    spint tmp[34] = {0};
    b = q - 1;
    t8 = 0;
    t0 = p[0];
    UMAAL(t0, t8, t0, b);
    tmp[0] = t0;
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
    tmp[1] = t0;
    tmp[2] = t1;
    tmp[3] = t2;
    tmp[4] = t3;
    tmp[5] = t4;
    tmp[6] = t5;
    tmp[7] = t6;
    tmp[8] = t7;
    t0 = p[9];
    t1 = p[10];
    t2 = p[11];
    t3 = p[12];
    t4 = p[13];
    t5 = p[14];
    t6 = p[15];
    t7 = p[16];
    UMAAL(t0, t8, t0, b);
    UMAAL(t1, t8, t1, b);
    UMAAL(t2, t8, t2, b);
    UMAAL(t3, t8, t3, b);
    UMAAL(t4, t8, t4, b);
    UMAAL(t5, t8, t5, b);
    UMAAL(t6, t8, t6, b);
    UMAAL(t7, t8, t7, b);
    tmp[9] = t0;
    tmp[10] = t1;
    tmp[11] = t2;
    tmp[12] = t3;
    tmp[13] = t4;
    tmp[14] = t5;
    tmp[15] = t6;
    tmp[16] = t7;
    tmp[17] = t8;
    modred_NIST521_ct(tmp, r);
}

static void modimp_NIST521_ct(const char *b, spint *a) {
    const spint *b32 = (const spint *)b;
#pragma GCC unroll 17
    for (int i = 0; i < 17; i++) {
        a[i] = __builtin_bswap32(b32[16 - i]);
    }
}

// Code for export, not exponentiation
static void modexp_NIST521_ct(const spint *a, char *b) {
    spint c[17], *b32 = (spint *)b;
    redc_NIST521_ct(a, c);
#pragma GCC unroll 17
    for (int i = 0; i < 17; i++) {
        b32[16 - i] = __builtin_bswap32(c[i]);
    }
}

#define Nlimbs_NIST521_ct 17
#define Nbits_NIST521_ct  521
#define Nbytes_NIST521_ct 68
