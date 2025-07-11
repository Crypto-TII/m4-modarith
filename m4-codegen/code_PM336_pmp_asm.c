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

static int modfsb_PM336_ct(spint *a) {
    const spint p0 = 4294967293;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 4294967295;
    const spint p4 = 4294967295;
    const spint p5 = 4294967295;
    const spint p6 = 4294967295;
    const spint p7 = 4294967295;
    const spint p8 = 4294967295;
    const spint p9 = 4294967295;
    const spint p10 = 65535;
    spint t0, t1;
    spint tmpvec[11];
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
        "str    %[t0], [%[tmpvec], #40]\n"
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
        "itt cs\n"
        "ldrcs %[t0], [%[tmpvec], #40]\n"
        "strcs %[t0], [%[a], #40]\n"
        "adc    %[r], %[r], %[r]\n"
        : [t0] "=&r" (t0), [t1] "=&r" (t1), [r] "+&r" (r)
        : [a] "r" (a), [p0] "rI" (p0), [p1] "rI" (p1), [p2] "rI" (p2), [p3] "rI" (p3), [p4] "rI" (p4), [p5] "rI" (p5), [p6] "rI" (p6), [p7] "rI" (p7), [p8] "rI" (p8), [p9] "rI" (p9), [p10] "rI" (p10), [tmpvec] "r" (tmpvec)
        : "cc", "memory");

    return 1 - r;
}

ALWAYS_INLINE static void mul_PM336_ct(const spint *p, const spint *q, spint *r) {
    spint t0, t1, t2, t3, t4, a, b0, b1, b2, b3;
    b0 = q[0];
    b1 = q[1];
    b2 = q[2];
    asm volatile(
        ".p2align 2\n"
        "mov.w  %[t1], #0\n"
        "mov.w  %[t2], #0\n"
        "ldr.w   %[a], [%[p], #0]\n"
        "umull  %[t0], %[t3], %[a], %[b0]\n"
        "umaal  %[t1], %[t3], %[a], %[b1]\n"
        "umaal  %[t2], %[t3], %[a], %[b2]\n"
        "ldr.w   %[a], [%[p], #4]\n"
        "str.w  %[t0], [%[r], #0]\n"
        "mov.w  %[t0], #0\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "ldr.w   %[a], [%[p], #8]\n"
        "str.w  %[t1], [%[r], #4]\n"
        "mov.w  %[t1], #0\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t0], %[t1], %[a], %[b2]\n"
        "ldr.w   %[a], [%[p], #12]\n"
        "str.w  %[t2], [%[r], #8]\n"
        "mov.w  %[t2], #0\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t0], %[t2], %[a], %[b1]\n"
        "umaal  %[t1], %[t2], %[a], %[b2]\n"
        "ldr.w   %[a], [%[p], #16]\n"
        "str.w  %[t3], [%[r], #12]\n"
        "mov.w  %[t3], #0\n"
        "umaal  %[t0], %[t3], %[a], %[b0]\n"
        "umaal  %[t1], %[t3], %[a], %[b1]\n"
        "umaal  %[t2], %[t3], %[a], %[b2]\n"
        "ldr.w   %[a], [%[p], #20]\n"
        "str.w  %[t0], [%[r], #16]\n"
        "mov.w  %[t0], #0\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "ldr.w   %[a], [%[p], #24]\n"
        "str.w  %[t1], [%[r], #20]\n"
        "mov.w  %[t1], #0\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t0], %[t1], %[a], %[b2]\n"
        "ldr.w   %[a], [%[p], #28]\n"
        "str.w  %[t2], [%[r], #24]\n"
        "mov.w  %[t2], #0\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t0], %[t2], %[a], %[b1]\n"
        "umaal  %[t1], %[t2], %[a], %[b2]\n"
        "ldr.w   %[a], [%[p], #32]\n"
        "str.w  %[t3], [%[r], #28]\n"
        "mov.w  %[t3], #0\n"
        "umaal  %[t0], %[t3], %[a], %[b0]\n"
        "umaal  %[t1], %[t3], %[a], %[b1]\n"
        "umaal  %[t2], %[t3], %[a], %[b2]\n"
        "ldr.w   %[a], [%[p], #36]\n"
        "str.w  %[t0], [%[r], #32]\n"
        "mov.w  %[t0], #0\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "ldr.w   %[a], [%[p], #40]\n"
        "str.w  %[t1], [%[r], #36]\n"
        "mov.w  %[t1], #0\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t0], %[t1], %[a], %[b2]\n"
        "str.w  %[t2], [%[r], #40]\n"
        "str.w  %[t3], [%[r], #44]\n"
        "str.w  %[t0], [%[r], #48]\n"
        "str.w  %[t1], [%[r], #52]\n"
        : [t2] "=&r"(t2), [t3] "=&r"(t3), [t0] "=&r"(t0), [t1] "=&r"(t1), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = q[3];
    b1 = q[4];
    b2 = q[5];
    b3 = q[6];
    t0 = r[3];
    t1 = r[4];
    t2 = r[5];
    t3 = r[6];
    t4 = 0;
    asm volatile(
        ".p2align 2\n"
        "ldr.w   %[a], [%[p], #0]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #28]\n"
        "str.w  %[t0], [%[r], #12]\n"
        "mov.w  %[t0], #0\n"
        "adds.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #4]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #32]\n"
        "str.w  %[t1], [%[r], #16]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #8]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #36]\n"
        "str.w  %[t2], [%[r], #20]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #12]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #40]\n"
        "str.w  %[t3], [%[r], #24]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #16]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #44]\n"
        "str.w  %[t4], [%[r], #28]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #20]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #48]\n"
        "str.w  %[t0], [%[r], #32]\n"
        "mov.w  %[t0], #0\n"
        "adcs.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #24]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #52]\n"
        "str.w  %[t1], [%[r], #36]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #28]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #32]\n"
        "str.w  %[t2], [%[r], #40]\n"
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
        "ldr.w   %[a], [%[p], #36]\n"
        "str.w  %[t3], [%[r], #44]\n"
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
        "ldr.w   %[a], [%[p], #40]\n"
        "str.w  %[t4], [%[r], #48]\n"
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
#ifdef __clang__
        "adcs   %[t4], %[t4], #0\n"
#else
        "adcs.w %[t4], %[t4], #0\n"
#endif
        "str.w  %[t0], [%[r], #52]\n"
        "str.w  %[t1], [%[r], #56]\n"
        "str.w  %[t2], [%[r], #60]\n"
        "str.w  %[t3], [%[r], #64]\n"
        "str.w  %[t4], [%[r], #68]\n"
        "mov.w  %[t0], #0\n"
#ifdef __clang__
        "adcs   %[t0], %[t0], #0\n"
#else
        "adcs.w %[t0], %[t0], #0\n"
#endif
        "str.w  %[t0], [%[r], #72]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    b0 = q[7];
    b1 = q[8];
    b2 = q[9];
    b3 = q[10];
    t0 = r[7];
    t1 = r[8];
    t2 = r[9];
    t3 = r[10];
    t4 = 0;
    asm volatile(
        ".p2align 2\n"
        "ldr.w   %[a], [%[p], #0]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #44]\n"
        "str.w  %[t0], [%[r], #28]\n"
        "mov.w  %[t0], #0\n"
        "adds.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #4]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #48]\n"
        "str.w  %[t1], [%[r], #32]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #8]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #52]\n"
        "str.w  %[t2], [%[r], #36]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #12]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #56]\n"
        "str.w  %[t3], [%[r], #40]\n"
        "mov.w  %[t3], #0\n"
        "adcs.w %[t2], %[t2], %[a]\n"
        "ldr.w   %[a], [%[p], #16]\n"
        "umaal  %[t4], %[t3], %[a], %[b0]\n"
        "umaal  %[t0], %[t3], %[a], %[b1]\n"
        "umaal  %[t1], %[t3], %[a], %[b2]\n"
        "umaal  %[t2], %[t3], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #60]\n"
        "str.w  %[t4], [%[r], #44]\n"
        "mov.w  %[t4], #0\n"
        "adcs.w %[t3], %[t3], %[a]\n"
        "ldr.w   %[a], [%[p], #20]\n"
        "umaal  %[t0], %[t4], %[a], %[b0]\n"
        "umaal  %[t1], %[t4], %[a], %[b1]\n"
        "umaal  %[t2], %[t4], %[a], %[b2]\n"
        "umaal  %[t3], %[t4], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #64]\n"
        "str.w  %[t0], [%[r], #48]\n"
        "mov.w  %[t0], #0\n"
        "adcs.w %[t4], %[t4], %[a]\n"
        "ldr.w   %[a], [%[p], #24]\n"
        "umaal  %[t1], %[t0], %[a], %[b0]\n"
        "umaal  %[t2], %[t0], %[a], %[b1]\n"
        "umaal  %[t3], %[t0], %[a], %[b2]\n"
        "umaal  %[t4], %[t0], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #68]\n"
        "str.w  %[t1], [%[r], #52]\n"
        "mov.w  %[t1], #0\n"
        "adcs.w %[t0], %[t0], %[a]\n"
        "ldr.w   %[a], [%[p], #28]\n"
        "umaal  %[t2], %[t1], %[a], %[b0]\n"
        "umaal  %[t3], %[t1], %[a], %[b1]\n"
        "umaal  %[t4], %[t1], %[a], %[b2]\n"
        "umaal  %[t0], %[t1], %[a], %[b3]\n"
        "ldr.w   %[a], [%[r], #72]\n"
        "str.w  %[t2], [%[r], #56]\n"
        "mov.w  %[t2], #0\n"
        "adcs.w %[t1], %[t1], %[a]\n"
        "ldr.w   %[a], [%[p], #32]\n"
        "umaal  %[t3], %[t2], %[a], %[b0]\n"
        "umaal  %[t4], %[t2], %[a], %[b1]\n"
        "umaal  %[t0], %[t2], %[a], %[b2]\n"
        "umaal  %[t1], %[t2], %[a], %[b3]\n"
        "ldr.w   %[a], [%[p], #36]\n"
        "str.w  %[t3], [%[r], #60]\n"
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
        "ldr.w   %[a], [%[p], #40]\n"
        "str.w  %[t4], [%[r], #64]\n"
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
#ifdef __clang__
        "adcs   %[t4], %[t4], #0\n"
#else
        "adcs.w %[t4], %[t4], #0\n"
#endif
        "str.w  %[t0], [%[r], #68]\n"
        "str.w  %[t1], [%[r], #72]\n"
        "str.w  %[t2], [%[r], #76]\n"
        "str.w  %[t3], [%[r], #80]\n"
        "str.w  %[t4], [%[r], #84]\n"
        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
}

ALWAYS_INLINE static void sqr_PM336_ct(const spint *p, spint *r) {
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
        "str.w  %[t4], [%[r], #40]\n"
        "str.w  %[t0], [%[r], #44]\n"
        "str.w  %[t1], [%[r], #48]\n"
        "str.w  %[t2], [%[r], #52]\n"
        "str.w  %[t3], [%[r], #56]\n"
        : [t4] "=&r"(t4), [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3), [a] "=&r"(a)
        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
    spint a0=p[4], a1=p[5], a2=p[6], a3=p[7], a4=p[8], a5=p[9], a6=p[10], c0, c1;
    asm volatile(
        ".p2align 2\n"
        "ldr.w   %[c0], [%[r], #36]\n"
        "mov.w   %[t0], #0\n"
        "mov.w   %[t1], #0\n"
        "mov.w   %[t2], #0\n"
        "umaal   %[c0], %[t0], %[a1], %[a0]\n"
        "ldr.w   %[c1], [%[r], #40]\n"
        "str.w   %[c0], [%[r], #36]\n"
        "umaal   %[c1], %[t0], %[a2], %[a0]\n"
        "ldr.w   %[c0], [%[r], #44]\n"
        "str.w   %[c1], [%[r], #40]\n"
        "umaal   %[c0], %[t0], %[a3], %[a0]\n"
        "umaal   %[c0], %[t1], %[a2], %[a1]\n"
        "ldr.w   %[c1], [%[r], #48]\n"
        "str.w   %[c0], [%[r], #44]\n"
        "umaal   %[c1], %[t0], %[a4], %[a0]\n"
        "umaal   %[c1], %[t1], %[a3], %[a1]\n"
        "ldr.w   %[c0], [%[r], #52]\n"
        "str.w   %[c1], [%[r], #48]\n"
        "umaal   %[c0], %[t0], %[a5], %[a0]\n"
        "umaal   %[c0], %[t1], %[a4], %[a1]\n"
        "umaal   %[c0], %[t2], %[a3], %[a2]\n"
        "ldr.w   %[c1], [%[r], #56]\n"
        "str.w   %[c0], [%[r], #52]\n"
        "umaal   %[c1], %[t0], %[a6], %[a0]\n"
        "umaal   %[c1], %[t1], %[a5], %[a1]\n"
        "umaal   %[c1], %[t2], %[a4], %[a2]\n"
        "mov.w  %[c0], #0\n"
        "str.w   %[c1], [%[r], #56]\n"
        "umaal   %[c0], %[t0], %[a6], %[a1]\n"
        "umaal   %[c0], %[t1], %[a5], %[a2]\n"
        "umaal   %[c0], %[t2], %[a4], %[a3]\n"
        "str.w   %[c0], [%[r], #60]\n"
        "umaal   %[t0], %[t1], %[a6], %[a2]\n"
        "umaal   %[t0], %[t2], %[a5], %[a3]\n"
        "str.w   %[t0], [%[r], #64]\n"
        "mov.w   %[c0], #0\n"
        "umaal   %[t1], %[t2], %[a6], %[a3]\n"
        "umaal   %[t1], %[c0], %[a5], %[a4]\n"
        "str.w   %[t1], [%[r], #68]\n"
        "umaal   %[t2], %[c0], %[a6], %[a4]\n"
        "str.w   %[t2], [%[r], #72]\n"
        "mov.w   %[t0], #0\n"
        "umaal   %[c0], %[t0], %[a6], %[a5]\n"
        "str.w   %[c0], [%[r], #76]\n"
        "str.w   %[t0], [%[r], #80]\n"
        : [c0] "=&r"(c0), [c1] "=&r"(c1), [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2)
        : [a0] "r"(a0), [a1] "r"(a1), [a2] "r"(a2), [a3] "r"(a3), [a4] "r"(a4), [a5] "r"(a5), [a6] "r"(a6), [r] "r"(r)
        : "memory");
    r[0] = 0;
    r[21] = 0;
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
        "ldr.w   %[b3], [%[r], #80]\n"
        "umull  %[t0], %[t1], %[b2], %[b2]\n"
        "umaal  %[t0], %[t4], %[a], %[b3]\n"
        "add.w  %[t1], %[t1], %[t4]\n"
        "str.w  %[t0], [%[r], #80]\n"
        "str.w  %[t1], [%[r], #84]\n"
        : [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [a] "=&r"(a),
          [b0] "=&r"(b0), [b1] "=&r"(b1), [b2] "=&r"(b2), [b3] "=&r"(b3)
        : [p] "r"(p), [r] "r"(r)
        : "cc", "memory");
}

static void modred_PM336_ct(const spint *c, spint *r) {
    spint t, rH, rT, cc = 0;

    rH = c[9];
    UMAAL(rH, cc, c[20], 3 << 16);

    rT = c[10];
    UMAAL(rT, cc, c[21], 3 << 16);
    cc = 3 * ((cc << 16) | (rT >> 16));
    rT &= 0x0000ffff;

    t = c[0];
    UMAAL(t, cc, c[11], 3 << 16);
    r[0] = t;

    t = c[1];
    UMAAL(t, cc, c[12], 3 << 16);
    r[1] = t;

    t = c[2];
    UMAAL(t, cc, c[13], 3 << 16);
    r[2] = t;

    t = c[3];
    UMAAL(t, cc, c[14], 3 << 16);
    r[3] = t;

    t = c[4];
    UMAAL(t, cc, c[15], 3 << 16);
    r[4] = t;

    t = c[5];
    UMAAL(t, cc, c[16], 3 << 16);
    r[5] = t;

    t = c[6];
    UMAAL(t, cc, c[17], 3 << 16);
    r[6] = t;

    t = c[7];
    UMAAL(t, cc, c[18], 3 << 16);
    r[7] = t;

    t = c[8];
    UMAAL(t, cc, c[19], 3 << 16);
    r[8] = t;

    UMAAL(rH, cc, 0, 0);
    r[9] = rH;

    r[10] = rT + cc;
}

static void modmul_PM336_ct(const spint *a, const spint *b, spint *res) {
    spint z[22];
    mul_PM336_ct(a, b, z);
    modred_PM336_ct(z, res);
}

ALWAYS_INLINE static void inner_modsqr_PM336_ct(const spint *a, spint *res) {
    spint z[22];
    sqr_PM336_ct(a, z);
    modred_PM336_ct(z, res);
}

static void modsqr_PM336_ct(const spint *a, spint *res) {
    inner_modsqr_PM336_ct(a, res);
}

static void nres_PM336_ct(const spint *a, spint *b) {
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
}

static void redc_PM336_ct(const spint *a, spint *b) {
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
    modfsb_PM336_ct(b);
}

static void modcmv_PM336_ct(int d, const spint *a, volatile spint *b) {
    spint c0, c1, s, t, aux;
    spint r = 0x5aa5a55a;
    c0 = (~d) & (r + 1);
    c1 = d + r;
    for (int i = 0; i < 11; i++) {
        s = a[i];
        t = b[i];
        b[i] = aux = c0 * t + c1 * s;
        b[i] = aux - r * (t + s);
    }
}

static void modcsw_PM336_ct(int d, volatile spint *a, volatile spint *b) {
    spint c0, c1, s, t, w, aux;
    spint r = 0x5aa5a55a;
    c0 = (~d) & (r + 1);
    c1 = d + r;
    for (int i = 0; i < 11; i++) {
        s = a[i];
        t = b[i];
        w = r * (t + s);
        b[i] = aux = c0 * t + c1 * s;
        b[i] = aux - w;
        a[i] = aux = c0 * s + c1 * t;
        a[i] = aux - w;
    }
}

inline static void modadd_PM336_ct(const spint *a, const spint *b, spint *res) {
    spint t = 0;
    spint a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10;
    spint b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10;
    a10 = a[10];
    b10 = b[10];
    UMAAL(a10, t, 1, b10);
    t = 3 * ((a10 >> 16) + (t << 16));
    a10 = a10 & 0xffff;
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
    UMAAL(a10, t, 0, 0);
    res[10] = a10;
}

inline static void modsub_PM336_ct(const spint *a, const spint *b, spint *res) {
    spint ae, ao;
    spint t, t1, t2;
    spint t3, t4;
    const spint p0 = 4294967293;
    const spint p1 = 4294967295;
    const spint p2 = 4294967295;
    const spint p3 = 4294967295;
    const spint p4 = 4294967295;
    const spint p5 = 4294967295;
    const spint p6 = 4294967295;
    const spint p7 = 4294967295;
    const spint p8 = 4294967295;
    const spint p9 = 4294967295;
    const spint p10 = 65535;
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
        "str    %[t3], [%[res], #40]\n"
        "sbcs    %[t], %[t3], %[t3]\n"
        : [t] "=&r" (t), [t1] "=&r" (t1), [t2] "=&r" (t2), [t3] "=&r" (t3), [t4] "=&r" (t4)
        : [b] "r" (b), [a] "r" (a), [res] "r" (res)
        : "cc", "memory");
    t = -t | (t3 > p10);
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
    res[10] = ae;
}

static void modneg_PM336_ct(const spint *a, spint *r) {
    spint zero[11] = {0};
    modsub_PM336_ct(zero, a, r);
}

static void modshl_PM336_ct(int n, spint *a) {
#pragma GCC unroll 10
    for (int i = 10; i > 0; i--) {
        a[i] = (a[i] << n) + (a[i - 1] >> (32 - n));
    }
    a[0] = (a[0] << n);
}

// Only works for n <= 31
static spint modshr_PM336_ct(int n, spint *a) {
    spint r = a[0] & ((1 << n) - 1);
#pragma GCC unroll 10
    for (int i = 0; i < 10; i++) {
        a[i] = (a[i] >> n) | (a[i + 1] << (32 - n));
    }
    a[10] = a[10] >> n;
    return r;
}

static void modcpy_PM336_ct(const spint *a, spint *b) {
#pragma GCC unroll 11
    for (int i = 0; i < 11; i++) {
        b[i] = a[i];
    }
}

static int modis0_PM336_ct(const spint *a) {
    spint c[11] = {0};
    spint d = 0;
    modcpy_PM336_ct(a, c);
    modfsb_PM336_ct(c);
    for (int i = 0; i < 11; i++) {
        d |= c[i];
    }
    return 1 - ((d | -d) >> 31);
}

static int modis1_PM336_ct(const spint *a) {
    spint c[11] = {0};
    spint d = 0;
    redc_PM336_ct(a, c);
    c[0] = c[0] - 1;
    for (int i = 0; i < 11; i++) {
        d |= c[i];
    }
    return 1 - ((d | -d) >> 31);
}

static int modcmp_PM336_ct(const spint *a, const spint *b) {
    spint c[11], d[11];
    int neq = 0;
    redc_PM336_ct(a, c);
    redc_PM336_ct(b, d);
    for (int i = 0; i < 11; i++) {
        neq |= c[i] ^ d[i];
    }
    neq = (neq | -neq) >> 31;
    return 1 - (neq & 1);
}

static int modsign_PM336_ct(const spint *a) {
    spint c[11];
    redc_PM336_ct(a, c);
    return c[0] % 2;
}

NOINLINE static void modnsqr_PM336_ct(spint *a, int n) {
    for (int i = 0; i < n; i++) {
        inner_modsqr_PM336_ct(a, a);
    }
}

// Calculate progenitor
NOINLINE static void modpro_PM336_ct(const spint *w, spint *z) {
    spint x[11];
    spint t0[11];
    spint t1[11];
    modcpy_PM336_ct(w, x);
    modsqr_PM336_ct(x, z);
    modmul_PM336_ct(x, z, z);
    modsqr_PM336_ct(z, z);
    modmul_PM336_ct(x, z, z);
    modcpy_PM336_ct(z, t0);
    modnsqr_PM336_ct(t0, 3);
    modmul_PM336_ct(z, t0, z);
    modsqr_PM336_ct(z, t0);
    modmul_PM336_ct(x, t0, t0);
    modcpy_PM336_ct(t0, t1);
    modnsqr_PM336_ct(t1, 6);
    modmul_PM336_ct(z, t1, z);
    modcpy_PM336_ct(z, t1);
    modnsqr_PM336_ct(t1, 7);
    modmul_PM336_ct(t0, t1, t0);
    modcpy_PM336_ct(t0, t1);
    modnsqr_PM336_ct(t1, 20);
    modmul_PM336_ct(t0, t1, t0);
    modcpy_PM336_ct(t0, t1);
    modnsqr_PM336_ct(t1, 40);
    modmul_PM336_ct(t0, t1, t0);
    modcpy_PM336_ct(t0, t1);
    modnsqr_PM336_ct(t1, 80);
    modmul_PM336_ct(t0, t1, t0);
    modcpy_PM336_ct(t0, t1);
    modnsqr_PM336_ct(t1, 160);
    modmul_PM336_ct(t0, t1, t0);
    modnsqr_PM336_ct(t0, 13);
    modmul_PM336_ct(z, t0, z);
}

// Test for quadratic residue, provide progenitor h if available, NULL if not
static int modqr_PM336_ct(const spint *h, const spint *x) {
    spint r[11];
    if (h == NULL) {
        modpro_PM336_ct(x, r);
        modsqr_PM336_ct(r, r);
    }
    else {
        modsqr_PM336_ct(h, r);
    }
    modmul_PM336_ct(r, x, r);
    modnsqr_PM336_ct(r, 1);
    return modis1_PM336_ct(r);
}

// Modular square root, provide progenitor h if available, NULL if not
static void modsqrt_PM336_ct(const spint *x, const spint *h, spint *r) {
    spint t[11];
    spint b[11];
    spint v[11];
    spint z[11] = {0xf559d3b8u, 0x6b804827u, 0xb93eac63u, 0xa4c94538u, 0xfca8b95du, 0x1f61eda9u, 0x3df798c4u, 0x38b2b455u, 0x527811fcu, 0xc3e031efu, 0xf93fu};
    spint s[11];
    spint y[11];
    if (h == NULL) {
        modpro_PM336_ct(x, y);
    }
    else {
        modcpy_PM336_ct(h, y);
    }
    modmul_PM336_ct(y, x, s);
    modmul_PM336_ct(s, y, t);
    nres_PM336_ct(z, z);
    for (int k = 2; k > 1; k--) {
        modcpy_PM336_ct(t, b);
        modnsqr_PM336_ct(b, k-2);
        int d = 1 - modis1_PM336_ct(b);
        modmul_PM336_ct(s, z, v);
        (void)modcmv_PM336_ct(d, v, s);
        modsqr_PM336_ct(z, z);
        modmul_PM336_ct(t, z, v);
        (void)modcmv_PM336_ct(d, v, t);
    }
    modcpy_PM336_ct(s, r);
}

// Calculate inverse, provide progenitor h if available
static void modinv_PM336_ct(const spint *x, const spint *h, spint *z) {
    spint s[11];
    spint t[11];
    if (h == NULL) {
        modpro_PM336_ct(x, t);
    }
    else {
        modcpy_PM336_ct(h, t);
    }
    modcpy_PM336_ct(x, s);
    for (int i = 0; i < (1); i++) {
        modsqr_PM336_ct(s, s);
        modmul_PM336_ct(s, x, s);
    }
    modnsqr_PM336_ct(t, 3);
    modmul_PM336_ct(s, t, z);
}

static void modzer_PM336_ct(spint *a) {
#pragma GCC unroll 11
    for (int i = 0; i < 11; i++) {
        a[i] = 0;
    }
}

static void modone_PM336_ct(spint *a) {
    a[0] = 1;
#pragma GCC unroll 10
    for (int i = 1; i < 11; i++) {
        a[i] = 0;
    }
}

static void modint_PM336_ct(int x, spint *a) {
    a[0] = (spint)x;
#pragma GCC unroll 10
    for (int i = 1; i < 11; i++) {
        a[i] = 0;
    }
}

static void mod2r_PM336_ct(unsigned int r, spint *a) {
    unsigned int n = r >> 5;
    unsigned int m = r & 31;
    modzer_PM336_ct(a);
    if (r >= 337) {
        return;
    }
    a[n] = 1 << m;
    nres_PM336_ct(a, a);
}

static void modmli_PM336_ct(const spint *p, const spint q, spint *r) {
    spint t0, t1, t2, t3, t4, t5, t6, t7, t8, b;
    spint tmp[22] = {0};
    b = q - 1;
    t8 = 0;
    t0 = p[0];
    t1 = p[1];
    t2 = p[2];
    UMAAL(t0, t8, t0, b);
    UMAAL(t1, t8, t1, b);
    UMAAL(t2, t8, t2, b);
    tmp[0] = t0;
    tmp[1] = t1;
    tmp[2] = t2;
    tmp[0] = t0;
    tmp[1] = t1;
    tmp[2] = t2;
    t0 = p[3];
    t1 = p[4];
    t2 = p[5];
    t3 = p[6];
    t4 = p[7];
    t5 = p[8];
    t6 = p[9];
    t7 = p[10];
    UMAAL(t0, t8, t0, b);
    UMAAL(t1, t8, t1, b);
    UMAAL(t2, t8, t2, b);
    UMAAL(t3, t8, t3, b);
    UMAAL(t4, t8, t4, b);
    UMAAL(t5, t8, t5, b);
    UMAAL(t6, t8, t6, b);
    UMAAL(t7, t8, t7, b);
    tmp[3] = t0;
    tmp[4] = t1;
    tmp[5] = t2;
    tmp[6] = t3;
    tmp[7] = t4;
    tmp[8] = t5;
    tmp[9] = t6;
    tmp[10] = t7;
    tmp[11] = t8;
    modred_PM336_ct(tmp, r);
}

static void modimp_PM336_ct(const char *b, spint *a) {
    const spint *b32 = (const spint *)b;
#pragma GCC unroll 11
    for (int i = 0; i < 11; i++) {
        a[i] = __builtin_bswap32(b32[10 - i]);
    }
}

// Code for export, not exponentiation
static void modexp_PM336_ct(const spint *a, char *b) {
    spint c[11], *b32 = (spint *)b;
    redc_PM336_ct(a, c);
#pragma GCC unroll 11
    for (int i = 0; i < 11; i++) {
        b32[10 - i] = __builtin_bswap32(c[i]);
    }
}

#define Nlimbs_PM336_ct 11
#define Nbits_PM336_ct  336
#define Nbytes_PM336_ct 44
