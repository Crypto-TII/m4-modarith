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

static int modfsb_C41417_ct(spint *a) {
    const spint p0 = 4294967279;
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
    const spint p12 = 1073741823;
    spint t0, t1;
    spint tmpvec[13];
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
        "str    %[t0], [%[tmpvec], #48]\n"
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
        "itt cs\n"
        "ldrcs %[t0], [%[tmpvec], #48]\n"
        "strcs %[t0], [%[a], #48]\n"
        "adc    %[r], %[r], %[r]\n"
        : [t0] "=&r" (t0), [t1] "=&r" (t1), [r] "+&r" (r)
        : [a] "r" (a), [p0] "rI" (p0), [p1] "rI" (p1), [p2] "rI" (p2), [p3] "rI" (p3), [p4] "rI" (p4), [p5] "rI" (p5), [p6] "rI" (p6), [p7] "rI" (p7), [p8] "rI" (p8), [p9] "rI" (p9), [p10] "rI" (p10), [p11] "rI" (p11), [p12] "rI" (p12), [tmpvec] "r" (tmpvec)
        : "cc", "memory");

    return 1 - r;
}

ALWAYS_INLINE static void mul_C41417_ct(const spint *p, const spint *q, spint *r) {
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
        "ldr.w  %[b0], [%[p], #48]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "str.w  %[t0], [%[r], #48]\n"
        "str.w  %[t4], [%[r], #52]\n"
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
        "ldr.w   %[a], [%[p], #40]\n"
        "str.w  %[t4], [%[r], #40]\n"
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
        "ldr.w   %[a], [%[p], #44]\n"
        "str.w  %[t0], [%[r], #44]\n"
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
        "str.w  %[t1], [%[r], #48]\n"
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
        "str.w  %[t2], [%[r], #52]\n"
        "str.w  %[t3], [%[r], #56]\n"
        "str.w  %[t4], [%[r], #60]\n"
        "str.w  %[t0], [%[r], #64]\n"
        "str.w  %[t1], [%[r], #68]\n"
        "mov.w  %[t2], #0\n"
#ifdef __clang__
        "adcs   %[t2], %[t2], #0\n"
#else
        "adcs.w %[t2], %[t2], #0\n"
#endif
        "str.w  %[t2], [%[r], #72]\n"
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
        "ldr.w   %[a], [%[p], #44]\n"
        "str.w  %[t0], [%[r], #60]\n"
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
        "str.w  %[t1], [%[r], #64]\n"
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
        "str.w  %[t2], [%[r], #68]\n"
        "str.w  %[t3], [%[r], #72]\n"
        "str.w  %[t4], [%[r], #76]\n"
        "str.w  %[t0], [%[r], #80]\n"
        "str.w  %[t1], [%[r], #84]\n"
        "mov.w  %[t2], #0\n"
#ifdef __clang__
        "adcs   %[t2], %[t2], #0\n"
#else
        "adcs.w %[t2], %[t2], #0\n"
#endif
        "str.w  %[t2], [%[r], #88]\n"
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
        "ldr.w   %[a], [%[p], #44]\n"
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
        "ldr.w   %[a], [%[p], #48]\n"
        "str.w  %[t1], [%[r], #80]\n"
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
        "str.w  %[t2], [%[r], #84]\n"
        "str.w  %[t3], [%[r], #88]\n"
        "str.w  %[t4], [%[r], #92]\n"
        "str.w  %[t0], [%[r], #96]\n"
        "str.w  %[t1], [%[r], #100]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
}

ALWAYS_INLINE static void sqr_C41417_ct(const spint *p, spint *r) {
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
        "str.w  %[t1], [%[r], #48]\n"
        "str.w  %[t2], [%[r], #52]\n"
        "str.w  %[t3], [%[r], #56]\n"
        "str.w  %[t4], [%[r], #60]\n"
        "str.w  %[t0], [%[r], #64]\n"
        : [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [t0] "=&r"(t0), [a] "=&r"(a)
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
        "ldr.w   %[a], [%[p], #40]\n"
        "str.w  %[t4], [%[r], #52]\n"
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
#ifdef __clang__
        "adcs   %[t1], %[t1], #0\n"
#else
        "adcs.w %[t1], %[t1], #0\n"
#endif
        "str.w  %[t2], [%[r], #64]\n"
        "str.w  %[t3], [%[r], #68]\n"
        "str.w  %[t4], [%[r], #72]\n"
        "str.w  %[t0], [%[r], #76]\n"
        "str.w  %[t1], [%[r], #80]\n"
        "mov.w  %[t2], #0\n"
#ifdef __clang__
        "adcs   %[t2], %[t2], #0\n"
#else
        "adcs.w %[t2], %[t2], #0\n"
#endif
        "str.w  %[t2], [%[r], #84]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = p[8]; b1 = p[9]; b2 = p[10]; b3 = p[11];
    a = p[12];
    t0 = r[17]; t1 = r[18]; t2 = r[19]; t3 = r[20]; t4 = 0;
    asm volatile(
        ".p2align 2\n"
        "umaal  %[t4], %[t0], %[b0], %[b1]\n"
        "umaal  %[t0], %[t1], %[b0], %[b2]\n"
        "str.w  %[t4], [%[r], #68]\n"
        "str.w  %[t0], [%[r], #72]\n"
        "mov.w  %[t4], #0\n"
        "umaal  %[t1], %[t2], %[b0], %[b3]\n"
        "umaal  %[t1], %[t4], %[b1], %[b2]\n"
        "umaal  %[t2], %[t4], %[b0], %[a]\n"
        "umaal  %[t2], %[t3], %[b1], %[b3]\n"
        "mov.w  %[t0], #0\n"
        "str.w  %[t1], [%[r], #76]\n"
        "str.w  %[t2], [%[r], #80]\n"
        "mov.w  %[t1], #0\n"
        "umaal  %[t3], %[t4], %[b1], %[a]\n"
        "umaal  %[t3], %[t0], %[b2], %[b3]\n"
        "umaal  %[t4], %[t0], %[b2], %[a]\n"
        "umaal  %[t0], %[t1], %[b3], %[a]\n"
        "str.w  %[t3], [%[r], #84]\n"
        "str.w  %[t4], [%[r], #88]\n"
        "str.w  %[t0], [%[r], #92]\n"
        "str.w  %[t1], [%[r], #96]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [a] "r"(a), [r] "r"(r)
        : "memory");
    r[0] = 0;
    r[25] = 0;
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
        "ldr.w   %[b1], [%[r], #96]\n"
        "umull  %[t0], %[t1], %[b0], %[b0]\n"
        "umaal  %[t0], %[t4], %[a], %[b1]\n"
        "add.w  %[t1], %[t1], %[t4]\n"
        "str.w  %[t0], [%[r], #96]\n"
        "str.w  %[t1], [%[r], #100]\n"
        : [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [a] "=&r"(a),
          [b0] "=&r"(b0), [b1] "=&r"(b1), [b2] "=&r"(b2), [b3] "=&r"(b3)
        : [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
}

static void modmul_C41417_ct(const spint *a, const spint *b, spint *res) {
    const spint mu = 4042322161;
    spint A[26];
    spint A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25;
    const spint p0 = 4294967279;
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
    const spint p12 = 1073741823;
    spint q, t, t2 = 0;

    mul_C41417_ct(a, b, A);

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
    A18 = A[18];
    A19 = A[19];
    A20 = A[20];
    A21 = A[21];
    A22 = A[22];
    A23 = A[23];
    A24 = A[24];
    A25 = A[25];

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
    UMAAL(A9, t, q, p9);
    UMAAL(A10, t, q, p10);
    UMAAL(A11, t, q, p11);
    UMAAL(A12, t, q, p12);
    UMAAL(A13, t2, 1, t);

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
    UMAAL(A10, t, q, p9);
    UMAAL(A11, t, q, p10);
    UMAAL(A12, t, q, p11);
    UMAAL(A13, t, q, p12);
    UMAAL(A14, t2, 1, t);

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
    UMAAL(A11, t, q, p9);
    UMAAL(A12, t, q, p10);
    UMAAL(A13, t, q, p11);
    UMAAL(A14, t, q, p12);
    UMAAL(A15, t2, 1, t);

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
    UMAAL(A12, t, q, p9);
    UMAAL(A13, t, q, p10);
    UMAAL(A14, t, q, p11);
    UMAAL(A15, t, q, p12);
    UMAAL(A16, t2, 1, t);

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
    UMAAL(A13, t, q, p9);
    UMAAL(A14, t, q, p10);
    UMAAL(A15, t, q, p11);
    UMAAL(A16, t, q, p12);
    UMAAL(A17, t2, 1, t);

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
    UMAAL(A14, t, q, p9);
    UMAAL(A15, t, q, p10);
    UMAAL(A16, t, q, p11);
    UMAAL(A17, t, q, p12);
    UMAAL(A18, t2, 1, t);

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
    UMAAL(A15, t, q, p9);
    UMAAL(A16, t, q, p10);
    UMAAL(A17, t, q, p11);
    UMAAL(A18, t, q, p12);
    UMAAL(A19, t2, 1, t);

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
    UMAAL(A16, t, q, p9);
    UMAAL(A17, t, q, p10);
    UMAAL(A18, t, q, p11);
    UMAAL(A19, t, q, p12);
    UMAAL(A20, t2, 1, t);

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
    UMAAL(A17, t, q, p9);
    UMAAL(A18, t, q, p10);
    UMAAL(A19, t, q, p11);
    UMAAL(A20, t, q, p12);
    UMAAL(A21, t2, 1, t);

    q = mu * A9;
    t = 0;
    UMAAL(A9, t, q, p0);
    UMAAL(A10, t, q, p1);
    UMAAL(A11, t, q, p2);
    UMAAL(A12, t, q, p3);
    UMAAL(A13, t, q, p4);
    UMAAL(A14, t, q, p5);
    UMAAL(A15, t, q, p6);
    UMAAL(A16, t, q, p7);
    UMAAL(A17, t, q, p8);
    UMAAL(A18, t, q, p9);
    UMAAL(A19, t, q, p10);
    UMAAL(A20, t, q, p11);
    UMAAL(A21, t, q, p12);
    UMAAL(A22, t2, 1, t);

    q = mu * A10;
    t = 0;
    UMAAL(A10, t, q, p0);
    UMAAL(A11, t, q, p1);
    UMAAL(A12, t, q, p2);
    UMAAL(A13, t, q, p3);
    UMAAL(A14, t, q, p4);
    UMAAL(A15, t, q, p5);
    UMAAL(A16, t, q, p6);
    UMAAL(A17, t, q, p7);
    UMAAL(A18, t, q, p8);
    UMAAL(A19, t, q, p9);
    UMAAL(A20, t, q, p10);
    UMAAL(A21, t, q, p11);
    UMAAL(A22, t, q, p12);
    UMAAL(A23, t2, 1, t);

    q = mu * A11;
    t = 0;
    UMAAL(A11, t, q, p0);
    UMAAL(A12, t, q, p1);
    UMAAL(A13, t, q, p2);
    UMAAL(A14, t, q, p3);
    UMAAL(A15, t, q, p4);
    UMAAL(A16, t, q, p5);
    UMAAL(A17, t, q, p6);
    UMAAL(A18, t, q, p7);
    UMAAL(A19, t, q, p8);
    UMAAL(A20, t, q, p9);
    UMAAL(A21, t, q, p10);
    UMAAL(A22, t, q, p11);
    UMAAL(A23, t, q, p12);
    UMAAL(A24, t2, 1, t);

    q = mu * A12;
    t = 0;
    UMAAL(A12, t, q, p0);
    UMAAL(A13, t, q, p1);
    UMAAL(A14, t, q, p2);
    UMAAL(A15, t, q, p3);
    UMAAL(A16, t, q, p4);
    UMAAL(A17, t, q, p5);
    UMAAL(A18, t, q, p6);
    UMAAL(A19, t, q, p7);
    UMAAL(A20, t, q, p8);
    UMAAL(A21, t, q, p9);
    UMAAL(A22, t, q, p10);
    UMAAL(A23, t, q, p11);
    UMAAL(A24, t, q, p12);
    UMAAL(A25, t2, 1, t);

    res[0] = A13;
    res[1] = A14;
    res[2] = A15;
    res[3] = A16;
    res[4] = A17;
    res[5] = A18;
    res[6] = A19;
    res[7] = A20;
    res[8] = A21;
    res[9] = A22;
    res[10] = A23;
    res[11] = A24;
    res[12] = A25;
}

ALWAYS_INLINE static void inner_modsqr_C41417_ct(const spint *a, spint *res) {
    const spint mu = 4042322161;
    spint A[26];
    spint A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25;
    const spint p0 = 4294967279;
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
    const spint p12 = 1073741823;
    spint q, t, t2 = 0;

    sqr_C41417_ct(a, A);

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
    A18 = A[18];
    A19 = A[19];
    A20 = A[20];
    A21 = A[21];
    A22 = A[22];
    A23 = A[23];
    A24 = A[24];
    A25 = A[25];

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
    UMAAL(A9, t, q, p9);
    UMAAL(A10, t, q, p10);
    UMAAL(A11, t, q, p11);
    UMAAL(A12, t, q, p12);
    UMAAL(A13, t2, 1, t);

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
    UMAAL(A10, t, q, p9);
    UMAAL(A11, t, q, p10);
    UMAAL(A12, t, q, p11);
    UMAAL(A13, t, q, p12);
    UMAAL(A14, t2, 1, t);

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
    UMAAL(A11, t, q, p9);
    UMAAL(A12, t, q, p10);
    UMAAL(A13, t, q, p11);
    UMAAL(A14, t, q, p12);
    UMAAL(A15, t2, 1, t);

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
    UMAAL(A12, t, q, p9);
    UMAAL(A13, t, q, p10);
    UMAAL(A14, t, q, p11);
    UMAAL(A15, t, q, p12);
    UMAAL(A16, t2, 1, t);

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
    UMAAL(A13, t, q, p9);
    UMAAL(A14, t, q, p10);
    UMAAL(A15, t, q, p11);
    UMAAL(A16, t, q, p12);
    UMAAL(A17, t2, 1, t);

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
    UMAAL(A14, t, q, p9);
    UMAAL(A15, t, q, p10);
    UMAAL(A16, t, q, p11);
    UMAAL(A17, t, q, p12);
    UMAAL(A18, t2, 1, t);

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
    UMAAL(A15, t, q, p9);
    UMAAL(A16, t, q, p10);
    UMAAL(A17, t, q, p11);
    UMAAL(A18, t, q, p12);
    UMAAL(A19, t2, 1, t);

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
    UMAAL(A16, t, q, p9);
    UMAAL(A17, t, q, p10);
    UMAAL(A18, t, q, p11);
    UMAAL(A19, t, q, p12);
    UMAAL(A20, t2, 1, t);

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
    UMAAL(A17, t, q, p9);
    UMAAL(A18, t, q, p10);
    UMAAL(A19, t, q, p11);
    UMAAL(A20, t, q, p12);
    UMAAL(A21, t2, 1, t);

    q = mu * A9;
    t = 0;
    UMAAL(A9, t, q, p0);
    UMAAL(A10, t, q, p1);
    UMAAL(A11, t, q, p2);
    UMAAL(A12, t, q, p3);
    UMAAL(A13, t, q, p4);
    UMAAL(A14, t, q, p5);
    UMAAL(A15, t, q, p6);
    UMAAL(A16, t, q, p7);
    UMAAL(A17, t, q, p8);
    UMAAL(A18, t, q, p9);
    UMAAL(A19, t, q, p10);
    UMAAL(A20, t, q, p11);
    UMAAL(A21, t, q, p12);
    UMAAL(A22, t2, 1, t);

    q = mu * A10;
    t = 0;
    UMAAL(A10, t, q, p0);
    UMAAL(A11, t, q, p1);
    UMAAL(A12, t, q, p2);
    UMAAL(A13, t, q, p3);
    UMAAL(A14, t, q, p4);
    UMAAL(A15, t, q, p5);
    UMAAL(A16, t, q, p6);
    UMAAL(A17, t, q, p7);
    UMAAL(A18, t, q, p8);
    UMAAL(A19, t, q, p9);
    UMAAL(A20, t, q, p10);
    UMAAL(A21, t, q, p11);
    UMAAL(A22, t, q, p12);
    UMAAL(A23, t2, 1, t);

    q = mu * A11;
    t = 0;
    UMAAL(A11, t, q, p0);
    UMAAL(A12, t, q, p1);
    UMAAL(A13, t, q, p2);
    UMAAL(A14, t, q, p3);
    UMAAL(A15, t, q, p4);
    UMAAL(A16, t, q, p5);
    UMAAL(A17, t, q, p6);
    UMAAL(A18, t, q, p7);
    UMAAL(A19, t, q, p8);
    UMAAL(A20, t, q, p9);
    UMAAL(A21, t, q, p10);
    UMAAL(A22, t, q, p11);
    UMAAL(A23, t, q, p12);
    UMAAL(A24, t2, 1, t);

    q = mu * A12;
    t = 0;
    UMAAL(A12, t, q, p0);
    UMAAL(A13, t, q, p1);
    UMAAL(A14, t, q, p2);
    UMAAL(A15, t, q, p3);
    UMAAL(A16, t, q, p4);
    UMAAL(A17, t, q, p5);
    UMAAL(A18, t, q, p6);
    UMAAL(A19, t, q, p7);
    UMAAL(A20, t, q, p8);
    UMAAL(A21, t, q, p9);
    UMAAL(A22, t, q, p10);
    UMAAL(A23, t, q, p11);
    UMAAL(A24, t, q, p12);
    UMAAL(A25, t2, 1, t);

    res[0] = A13;
    res[1] = A14;
    res[2] = A15;
    res[3] = A16;
    res[4] = A17;
    res[5] = A18;
    res[6] = A19;
    res[7] = A20;
    res[8] = A21;
    res[9] = A22;
    res[10] = A23;
    res[11] = A24;
    res[12] = A25;
}

static void modsqr_C41417_ct(const spint *a, spint *res) {
    inner_modsqr_C41417_ct(a, res);
}

static void nres_C41417_ct(const spint *a, spint *b) {
    spint nresfactor[] = {4624, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    modmul_C41417_ct(a, nresfactor, b);
}

static void redc_C41417_ct(const spint *a, spint *b) {
    spint rinv[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    modmul_C41417_ct(a, rinv, b);
    modfsb_C41417_ct(b);
}

static void modcmv_C41417_ct(int d, const spint *a, volatile spint *b) {
    spint c0, c1, s, t, aux;
    spint r = 0x5aa5a55a;
    c0 = (~d) & (r + 1);
    c1 = d + r;
    for (int i = 0; i < 13; i++) {
        s = a[i];
        t = b[i];
        b[i] = aux = c0 * t + c1 * s;
        b[i] = aux - r * (t + s);
    }
}

static void modcsw_C41417_ct(int d, volatile spint *a, volatile spint *b) {
    spint c0, c1, s, t, w, aux;
    spint r = 0x5aa5a55a;
    c0 = (~d) & (r + 1);
    c1 = d + r;
    for (int i = 0; i < 13; i++) {
        s = a[i];
        t = b[i];
        w = r * (t + s);
        b[i] = aux = c0 * t + c1 * s;
        b[i] = aux - w;
        a[i] = aux = c0 * s + c1 * t;
        a[i] = aux - w;
    }
}

inline static void modadd_C41417_ct(const spint *a, const spint *b, spint *res) {
    const spint p[13] = {4294967262, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 4294967295, 2147483647};
    spint tmpres[13];
    spint t = 0, pp, tt, aa, bb;

    asm volatile(
        "ldr    %[aa], [%[a]]\n"
        "ldr    %[bb], [%[b]]\n"
        "ldr    %[pp], [%[p]]\n"
        "umaal  %[aa], %[t], %[one], %[bb]\n"
        "str    %[aa], [%[res]]\n"
        "subs   %[tt], %[aa], %[pp]\n"
        "ldr    %[aa], [%[a], #4]\n"
        "ldr    %[bb], [%[b], #4]\n"
        "ldr    %[pp], [%[p], #4]\n"
        "str    %[tt], [%[tmpres], #0]\n"
        "umaal  %[aa], %[t], %[one], %[bb]\n"
        "str    %[aa], [%[res], #4]\n"
        "sbcs   %[tt], %[aa], %[pp]\n"
        "ldr    %[aa], [%[a], #8]\n"
        "ldr    %[bb], [%[b], #8]\n"
        "ldr    %[pp], [%[p], #8]\n"
        "str    %[tt], [%[tmpres], #4]\n"
        "umaal  %[aa], %[t], %[one], %[bb]\n"
        "str    %[aa], [%[res], #8]\n"
        "sbcs   %[tt], %[aa], %[pp]\n"
        "ldr    %[aa], [%[a], #12]\n"
        "ldr    %[bb], [%[b], #12]\n"
        "ldr    %[pp], [%[p], #12]\n"
        "str    %[tt], [%[tmpres], #8]\n"
        "umaal  %[aa], %[t], %[one], %[bb]\n"
        "str    %[aa], [%[res], #12]\n"
        "sbcs   %[tt], %[aa], %[pp]\n"
        "ldr    %[aa], [%[a], #16]\n"
        "ldr    %[bb], [%[b], #16]\n"
        "ldr    %[pp], [%[p], #16]\n"
        "str    %[tt], [%[tmpres], #12]\n"
        "umaal  %[aa], %[t], %[one], %[bb]\n"
        "str    %[aa], [%[res], #16]\n"
        "sbcs   %[tt], %[aa], %[pp]\n"
        "ldr    %[aa], [%[a], #20]\n"
        "ldr    %[bb], [%[b], #20]\n"
        "ldr    %[pp], [%[p], #20]\n"
        "str    %[tt], [%[tmpres], #16]\n"
        "umaal  %[aa], %[t], %[one], %[bb]\n"
        "str    %[aa], [%[res], #20]\n"
        "sbcs   %[tt], %[aa], %[pp]\n"
        "ldr    %[aa], [%[a], #24]\n"
        "ldr    %[bb], [%[b], #24]\n"
        "ldr    %[pp], [%[p], #24]\n"
        "str    %[tt], [%[tmpres], #20]\n"
        "umaal  %[aa], %[t], %[one], %[bb]\n"
        "str    %[aa], [%[res], #24]\n"
        "sbcs   %[tt], %[aa], %[pp]\n"
        "ldr    %[aa], [%[a], #28]\n"
        "ldr    %[bb], [%[b], #28]\n"
        "ldr    %[pp], [%[p], #28]\n"
        "str    %[tt], [%[tmpres], #24]\n"
        "umaal  %[aa], %[t], %[one], %[bb]\n"
        "str    %[aa], [%[res], #28]\n"
        "sbcs   %[tt], %[aa], %[pp]\n"
        "ldr    %[aa], [%[a], #32]\n"
        "ldr    %[bb], [%[b], #32]\n"
        "ldr    %[pp], [%[p], #32]\n"
        "str    %[tt], [%[tmpres], #28]\n"
        "umaal  %[aa], %[t], %[one], %[bb]\n"
        "str    %[aa], [%[res], #32]\n"
        "sbcs   %[tt], %[aa], %[pp]\n"
        "ldr    %[aa], [%[a], #36]\n"
        "ldr    %[bb], [%[b], #36]\n"
        "ldr    %[pp], [%[p], #36]\n"
        "str    %[tt], [%[tmpres], #32]\n"
        "umaal  %[aa], %[t], %[one], %[bb]\n"
        "str    %[aa], [%[res], #36]\n"
        "sbcs   %[tt], %[aa], %[pp]\n"
        "ldr    %[aa], [%[a], #40]\n"
        "ldr    %[bb], [%[b], #40]\n"
        "ldr    %[pp], [%[p], #40]\n"
        "str    %[tt], [%[tmpres], #36]\n"
        "umaal  %[aa], %[t], %[one], %[bb]\n"
        "str    %[aa], [%[res], #40]\n"
        "sbcs   %[tt], %[aa], %[pp]\n"
        "ldr    %[aa], [%[a], #44]\n"
        "ldr    %[bb], [%[b], #44]\n"
        "ldr    %[pp], [%[p], #44]\n"
        "str    %[tt], [%[tmpres], #40]\n"
        "umaal  %[aa], %[t], %[one], %[bb]\n"
        "str    %[aa], [%[res], #44]\n"
        "sbcs   %[tt], %[aa], %[pp]\n"
        "ldr    %[aa], [%[a], #48]\n"
        "ldr    %[bb], [%[b], #48]\n"
        "ldr    %[pp], [%[p], #48]\n"
        "str    %[tt], [%[tmpres], #44]\n"
        "umaal  %[aa], %[t], %[one], %[bb]\n"
        "str    %[aa], [%[res], #48]\n"
        "sbcs   %[tt], %[aa], %[pp]\n"
        "str    %[tt], [%[tmpres], #48]\n"
        "itttt cs\n"
        "ldrcs %[t], [%[tmpres], #0]\n"
        "ldrcs %[tt], [%[tmpres], #4]\n"
        "strcs %[t], [%[res], #0]\n"
        "strcs %[tt], [%[res], #4]\n"
        "itttt cs\n"
        "ldrcs %[t], [%[tmpres], #8]\n"
        "ldrcs %[tt], [%[tmpres], #12]\n"
        "strcs %[t], [%[res], #8]\n"
        "strcs %[tt], [%[res], #12]\n"
        "itttt cs\n"
        "ldrcs %[t], [%[tmpres], #16]\n"
        "ldrcs %[tt], [%[tmpres], #20]\n"
        "strcs %[t], [%[res], #16]\n"
        "strcs %[tt], [%[res], #20]\n"
        "itttt cs\n"
        "ldrcs %[t], [%[tmpres], #24]\n"
        "ldrcs %[tt], [%[tmpres], #28]\n"
        "strcs %[t], [%[res], #24]\n"
        "strcs %[tt], [%[res], #28]\n"
        "itttt cs\n"
        "ldrcs %[t], [%[tmpres], #32]\n"
        "ldrcs %[tt], [%[tmpres], #36]\n"
        "strcs %[t], [%[res], #32]\n"
        "strcs %[tt], [%[res], #36]\n"
        "itttt cs\n"
        "ldrcs %[t], [%[tmpres], #40]\n"
        "ldrcs %[tt], [%[tmpres], #44]\n"
        "strcs %[t], [%[res], #40]\n"
        "strcs %[tt], [%[res], #44]\n"
        "itt cs\n"
        "ldrcs %[t], [%[tmpres], #48]\n"
        "strcs %[t], [%[res], #48]\n"
        : [t] "+&r" (t), [tt] "=&r" (tt), [aa] "=&r" (aa), [bb] "=&r" (bb), [pp] "=&r" (pp)
        : [res] "r" (res), [tmpres] "r" (tmpres), [a] "r" (a), [b] "r" (b), [p] "r" (p), [one] "r" (1)
        : "cc", "memory");
}

inline static void modsub_C41417_ct(const spint *a, const spint *b, spint *res) {
    spint ae, ao;
    spint t, t1, t2;
    spint t3, t4;
    const spint p0 = 4294967262;
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
    const spint p12 = 2147483647;
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
        "str    %[t3], [%[res], #48]\n"
        "sbcs    %[t], %[t3], %[t3]\n"
        : [t] "=&r" (t), [t1] "=&r" (t1), [t2] "=&r" (t2), [t3] "=&r" (t3), [t4] "=&r" (t4)
        : [b] "r" (b), [a] "r" (a), [res] "r" (res)
        : "cc", "memory");
    t = -t | (t3 > p12);
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
    res[12] = ae;
}

static void modneg_C41417_ct(const spint *a, spint *r) {
    spint zero[13] = {0};
    modsub_C41417_ct(zero, a, r);
}

static void modshl_C41417_ct(int n, spint *a) {
#pragma GCC unroll 12
    for (int i = 12; i > 0; i--) {
        a[i] = (a[i] << n) + (a[i - 1] >> (32 - n));
    }
    a[0] = (a[0] << n);
}

// Only works for n <= 31
static spint modshr_C41417_ct(int n, spint *a) {
    spint r = a[0] & ((1 << n) - 1);
#pragma GCC unroll 12
    for (int i = 0; i < 12; i++) {
        a[i] = (a[i] >> n) | (a[i + 1] << (32 - n));
    }
    a[12] = a[12] >> n;
    return r;
}

static void modcpy_C41417_ct(const spint *a, spint *b) {
#pragma GCC unroll 13
    for (int i = 0; i < 13; i++) {
        b[i] = a[i];
    }
}

static int modis0_C41417_ct(const spint *a) {
    spint c[13] = {0};
    spint d = 0;
    modcpy_C41417_ct(a, c);
    modfsb_C41417_ct(c);
    for (int i = 0; i < 13; i++) {
        d |= c[i];
    }
    return 1 - ((d | -d) >> 31);
}

static int modis1_C41417_ct(const spint *a) {
    spint c[13] = {0};
    spint d = 0;
    redc_C41417_ct(a, c);
    c[0] = c[0] - 1;
    for (int i = 0; i < 13; i++) {
        d |= c[i];
    }
    return 1 - ((d | -d) >> 31);
}

static int modcmp_C41417_ct(const spint *a, const spint *b) {
    spint c[13], d[13];
    int neq = 0;
    redc_C41417_ct(a, c);
    redc_C41417_ct(b, d);
    for (int i = 0; i < 13; i++) {
        neq |= c[i] ^ d[i];
    }
    neq = (neq | -neq) >> 31;
    return 1 - (neq & 1);
}

static int modsign_C41417_ct(const spint *a) {
    spint c[13];
    redc_C41417_ct(a, c);
    return c[0] % 2;
}

NOINLINE static void modnsqr_C41417_ct(spint *a, int n) {
    for (int i = 0; i < n; i++) {
        inner_modsqr_C41417_ct(a, a);
    }
}

// Calculate progenitor
NOINLINE static void modpro_C41417_ct(const spint *w, spint *z) {
    spint x[13];
    spint t0[13];
    spint t1[13];
    spint t2[13];
    modcpy_C41417_ct(w, x);
    modsqr_C41417_ct(x, z);
    modmul_C41417_ct(x, z, z);
    modsqr_C41417_ct(z, t0);
    modmul_C41417_ct(x, t0, t0);
    modcpy_C41417_ct(t0, t1);
    modnsqr_C41417_ct(t1, 3);
    modmul_C41417_ct(t0, t1, t0);
    modcpy_C41417_ct(t0, t1);
    modnsqr_C41417_ct(t1, 6);
    modmul_C41417_ct(t0, t1, t0);
    modcpy_C41417_ct(t0, t1);
    modnsqr_C41417_ct(t1, 12);
    modmul_C41417_ct(t0, t1, t1);
    modsqr_C41417_ct(t1, t0);
    modcpy_C41417_ct(t0, t2);
    modnsqr_C41417_ct(t2, 23);
    modmul_C41417_ct(t1, t2, t1);
    modcpy_C41417_ct(t1, t2);
    modnsqr_C41417_ct(t2, 48);
    modmul_C41417_ct(t1, t2, t1);
    modcpy_C41417_ct(t1, t2);
    modnsqr_C41417_ct(t2, 96);
    modmul_C41417_ct(t1, t2, t1);
    modcpy_C41417_ct(t1, t2);
    modnsqr_C41417_ct(t2, 192);
    modmul_C41417_ct(t1, t2, t1);
    modnsqr_C41417_ct(t1, 25);
    modmul_C41417_ct(t0, t1, t0);
    modmul_C41417_ct(x, t0, t0);
    modnsqr_C41417_ct(t0, 3);
    modmul_C41417_ct(z, t0, z);
}

// Test for quadratic residue, provide progenitor h if available, NULL if not
static int modqr_C41417_ct(const spint *h, const spint *x) {
    spint r[13];
    if (h == NULL) {
        modpro_C41417_ct(x, r);
        modsqr_C41417_ct(r, r);
    }
    else {
        modsqr_C41417_ct(h, r);
    }
    modmul_C41417_ct(r, x, r);
    return modis1_C41417_ct(r);
}

// Modular square root, provide progenitor h if available, NULL if not
static void modsqrt_C41417_ct(const spint *x, const spint *h, spint *r) {
    spint s[13];
    spint y[13];
    if (h == NULL) {
        modpro_C41417_ct(x, y);
    }
    else {
        modcpy_C41417_ct(h, y);
    }
    modmul_C41417_ct(y, x, s);
    modcpy_C41417_ct(s, r);
}

// Calculate inverse, provide progenitor h if available
static void modinv_C41417_ct(const spint *x, const spint *h, spint *z) {
    spint s[13];
    spint t[13];
    if (h == NULL) {
        modpro_C41417_ct(x, t);
    }
    else {
        modcpy_C41417_ct(h, t);
    }
    modcpy_C41417_ct(x, s);
    modnsqr_C41417_ct(t, 2);
    modmul_C41417_ct(s, t, z);
}

static void modzer_C41417_ct(spint *a) {
#pragma GCC unroll 13
    for (int i = 0; i < 13; i++) {
        a[i] = 0;
    }
}

static void modone_C41417_ct(spint *a) {
    a[0] = 68;
    a[1] = 0;
    a[2] = 0;
    a[3] = 0;
    a[4] = 0;
    a[5] = 0;
    a[6] = 0;
    a[7] = 0;
    a[8] = 0;
    a[9] = 0;
    a[10] = 0;
    a[11] = 0;
    a[12] = 0;
}

static void modint_C41417_ct(int x, spint *a) {
    a[0] = (spint)x;
#pragma GCC unroll 12
    for (int i = 1; i < 13; i++) {
        a[i] = 0;
    }
    nres_C41417_ct(a, a);
}

static void mod2r_C41417_ct(unsigned int r, spint *a) {
    unsigned int n = r >> 5;
    unsigned int m = r & 31;
    modzer_C41417_ct(a);
    if (r >= 416) {
        return;
    }
    a[n] = 1 << m;
    nres_C41417_ct(a, a);
}

ALWAYS_INLINE static void mli_C41417_ct(const spint *p, const spint q, spint *r) {
    spint b, t0, t1, t2, t3, t4, t5, t6, t7, t8;
    b = q - 1;
    t8 = 0;
    t0 = p[0];
    t1 = p[1];
    t2 = p[2];
    t3 = p[3];
    t4 = p[4];
    UMAAL(t0, t8, t0, b);
    UMAAL(t1, t8, t1, b);
    UMAAL(t2, t8, t2, b);
    UMAAL(t3, t8, t3, b);
    UMAAL(t4, t8, t4, b);
    r[0] = t0;
    r[1] = t1;
    r[2] = t2;
    r[3] = t3;
    r[4] = t4;
    t0 = p[5];
    t1 = p[6];
    t2 = p[7];
    t3 = p[8];
    t4 = p[9];
    t5 = p[10];
    t6 = p[11];
    t7 = p[12];
    UMAAL(t0, t8, t0, b);
    UMAAL(t1, t8, t1, b);
    UMAAL(t2, t8, t2, b);
    UMAAL(t3, t8, t3, b);
    UMAAL(t4, t8, t4, b);
    UMAAL(t5, t8, t5, b);
    UMAAL(t6, t8, t6, b);
    UMAAL(t7, t8, t7, b);
    r[5] = t0;
    r[6] = t1;
    r[7] = t2;
    r[8] = t3;
    r[9] = t4;
    r[10] = t5;
    r[11] = t6;
    r[12] = t7;
    r[13] = t8;
}

static void modmli_C41417_ct(const spint *p, const spint q, spint *r) {
    spint A[14];
    spint pq0, pq1, pq2, pq3, pq4, pq5, pq6, pq7, pq8, pq9, pq10, pq11, pq12;
    mli_C41417_ct(p, q, A);
    spint t = 0, t2 = 0;
    spint sum = A[13] << 2 | A[12] >> 30;
    A[12] = A[12] & 0x3fffffff;
    pq0 = A[0];
    UMAAL(pq0, t, sum, 17);
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
    pq9 = A[9];
    UMAAL(pq9, t, sum, 0);
    pq10 = A[10];
    UMAAL(pq10, t, sum, 0);
    pq11 = A[11];
    UMAAL(pq11, t, sum, 0);
    pq12 = A[12];
    UMAAL(pq12, t, sum, 0);
    t = t << 2 | pq12 >> 30;
    pq12 = pq12 & 0x3fffffff;
    UMAAL(pq0, t2, t, 17);
    UMAAL(pq1, t2, t, 0);
    UMAAL(pq2, t2, t, 0);
    UMAAL(pq3, t2, t, 0);
    UMAAL(pq4, t2, t, 0);
    UMAAL(pq5, t2, t, 0);
    UMAAL(pq6, t2, t, 0);
    UMAAL(pq7, t2, t, 0);
    UMAAL(pq8, t2, t, 0);
    UMAAL(pq9, t2, t, 0);
    UMAAL(pq10, t2, t, 0);
    UMAAL(pq11, t2, t, 0);
    UMAAL(pq12, t2, t, 0);
    r[0] = pq0;
    r[1] = pq1;
    r[2] = pq2;
    r[3] = pq3;
    r[4] = pq4;
    r[5] = pq5;
    r[6] = pq6;
    r[7] = pq7;
    r[8] = pq8;
    r[9] = pq9;
    r[10] = pq10;
    r[11] = pq11;
    r[12] = pq12;
}

static void modimp_C41417_ct(const char *b, spint *a) {
    const spint *b32 = (const spint *)b;
#pragma GCC unroll 13
    for (int i = 0; i < 13; i++) {
        a[i] = __builtin_bswap32(b32[12 - i]);
    }
    nres_C41417_ct(a, a);
}

// Code for export, not exponentiation
static void modexp_C41417_ct(const spint *a, char *b) {
    spint c[13], *b32 = (spint *)b;
    redc_C41417_ct(a, c);
#pragma GCC unroll 13
    for (int i = 0; i < 13; i++) {
        b32[12 - i] = __builtin_bswap32(c[i]);
    }
}

#define Nlimbs_C41417_ct 13
#define Nbits_C41417_ct  414
#define Nbytes_C41417_ct 52
