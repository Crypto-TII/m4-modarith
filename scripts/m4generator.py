#!/usr/bin/env python3

# Copyright 2025 Technology Innovation Institute

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import sys
import subprocess
from m4prime import Prime
from enum import Enum
from m4verifier import Verifier


# Selects the inline policy for the generated code, to trade off between speed and size.
class InlinePolicy(Enum):
    HANDSOFF = 1  # Mostly defer inlining decisions to the compiler, except for some critical functions.
    SIZE = 2  # Never inline any functions. Sacrifices speed for size.
    BALANCED_SIZE = 3  # Inline some functions. Sacrifices some size for speed.
    BALANCED_SPEED = 4  # Inline more functions, always inlining small ones. Sacrifices some speed for size.
    SPEED = 5  # Always inline every function. Sacrifices size for speed.


class CodeGenerator:
    def __init__(self, p=None, name=None, reduction=None, inline_policy=None):
        self.prime = p
        if not p:
            self.prime = Prime(name, reduction)
        # governs usage of inline for generated script
        self.inline_policy = inline_policy or InlinePolicy.HANDSOFF
        if self.inline_policy == InlinePolicy.HANDSOFF:
            self.small_inline_attribute = ""
            self.medium_inline_attribute = ""
            self.large_inline_attribute = ""
        elif self.inline_policy == InlinePolicy.SIZE:
            self.small_inline_attribute = "NOINLINE "
            self.medium_inline_attribute = "NOINLINE "
            self.large_inline_attribute = "NOINLINE "
        elif self.inline_policy == InlinePolicy.BALANCED_SIZE:
            self.small_inline_attribute = "inline "
            self.medium_inline_attribute = ""
            self.large_inline_attribute = "NOINLINE "
        elif self.inline_policy == InlinePolicy.BALANCED_SPEED:
            self.small_inline_attribute = "ALWAYS_INLINE "
            self.medium_inline_attribute = "inline "
            self.large_inline_attribute = ""
        elif self.inline_policy == InlinePolicy.SPEED:
            self.small_inline_attribute = "ALWAYS_INLINE "
            self.medium_inline_attribute = "ALWAYS_INLINE "
            self.large_inline_attribute = "ALWAYS_INLINE "
        else:
            sys.exit(1)

    # generates the header of the generated file with necessary macros
    def gen_header(self, p=None):
        p = p or self.prime
        print(
            f"""\
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
"""
        )

    # Generates footer for C file
    def gen_footer(self, p=None, name=None, n=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        n = n or p.realn
        nlimbs = nlimbs or p.nlimbs
        nbytes = nlimbs * 4
        print(f"#define Nlimbs_{name}_ct {nlimbs}")
        print(f"#define Nbits_{name}_ct  {n}")
        print(f"#define Nbytes_{name}_ct {nbytes}")

    # Selects an inline policy based on prime size in limbs
    def inline_size_limbs(self, nlimbs):
        if nlimbs <= 8:
            return self.small_inline_attribute
        elif nlimbs <= 12:
            return self.medium_inline_attribute
        else:
            return self.large_inline_attribute

    # generates inline assembly conditional constant time store code segments, used in modfsb, modadd, montgomery modmul/sqr
    def gen_asm_conditional_store(self, varname, memreg, startvar=0, startmem=0, p=None, nlimbs=None):
        p = p or self.prime
        n = nlimbs or p.nlimbs
        limb = startvar  # limb position
        addr = startmem
        for _itblock in range(n // 4):
            print(f'        "itttt cs\\n"')
            for i in range(limb, limb + 4):
                print(f'        "strcs %[{varname}{i}], [%[{memreg}], #{addr}]\\n"')
                addr += 4
            limb += 4
        rmd_itblock = n % 4  #
        if rmd_itblock > 0:  # is not a multiple of 4, need a final it block
            itstring = "t" * rmd_itblock
            print(f'        "i{itstring} cs\\n"')
            for i in range(limb, limb + rmd_itblock):
                print(f'        "strcs %[{varname}{i}], [%[{memreg}], #{addr}]\\n"')
                addr += 4

    # generates inline assembly conditional constant time load+store code segments, used in modfsb and modadd
    def gen_asm_conditional_loadstore(self, varlist, ldrvec, strvec, startldr=0, startstr=0, p=None, nlimbs=None, cond="cs"):
        p = p or self.prime
        n = nlimbs or p.nlimbs
        ldraddr = startldr  # limb position
        straddr = startstr
        v = varlist  # size must be at least 2 and even

        for _itblock in range(n // 2):
            print(f'        "itttt {cond}\\n"')
            print(f'        "ldr{cond} %[{v[0]}], [%[{ldrvec}], #{ldraddr}]\\n"')
            print(f'        "ldr{cond} %[{v[1]}], [%[{ldrvec}], #{ldraddr+4}]\\n"')
            print(f'        "str{cond} %[{v[0]}], [%[{strvec}], #{straddr}]\\n"')
            print(f'        "str{cond} %[{v[1]}], [%[{strvec}], #{straddr+4}]\\n"')
            v = v[2:] + v[:2]  # rotate varlist
            ldraddr += 8
            straddr += 8
        if n % 2 > 0:  # check if there is one last ldr+str
            print(f'        "itt {cond}\\n"')
            print(f'        "ldr{cond} %[{v[0]}], [%[{ldrvec}], #{ldraddr}]\\n"')
            print(f'        "str{cond} %[{v[0]}], [%[{strvec}], #{straddr}]\\n"')

    # generates constant time conditional subtraction for numbers with a small amount of limbs (8 or less generally)
    # * optsub indicates a strategy of minimizing temp variables, only works for small primes (8 limbs generally)
    # * optfsb indicates a strategy of minimizing temp variables for modfsb, only works for small primes (8 limbs generally)
    def gen_modfsb_small_code(self, pf, p=None, nlimbs=None):
        p = p or self.prime
        n = nlimbs or p.nlimbs
        for i in range(n):
            print(f"    const spint p{i} = {pf[i]};")
        print(f"    spint a0 = a[0]", end="")
        for i in range(1, n):
            print(f", a{i} = a[{i}]", end="")
        print(";")
        print(f"    int r = 0;")
        print(f"    asm volatile(")
        print(f'        "subs   %[a0], %[a0], %[p0]\\n"')
        for i in range(1, n):
            print(f'        "sbcs   %[a{i}], %[a{i}], %[p{i}]\\n"')

        self.gen_asm_conditional_store("a", "a", 0, 0, p, n)

        print(f'        "adc    %[r], %[r], %[r]\\n"')
        print(f'        : [a0] "+&r" (a0)', end="")
        for i in range(1, n):
            print(f', [a{i}] "+&r" (a{i})', end="")
        print(f', [r] "+&r" (r)')
        print(f'        : [a] "r" (a)', end="")
        for i in range(n):
            print(f', [p{i}] "rI" (p{i})', end="")
        print(f'\n        : "cc", "memory");')
        print(f"")
        print(f"    return 1 - r;")

    # generates constant time conditional subtraction for primes that have medium size (more than 8, less than 15 generally)
    # * optsub indicates a strategy of minimizing temp variables, only works for small primes (8 limbs generally)
    # * optfsb indicates a strategy of minimizing temp variables for modfsb, only works for small primes (8 limbs generally)
    def gen_modfsb_medium_code(self, pf, p=None, nlimbs=None):
        p = p or self.prime
        n = nlimbs or p.nlimbs
        for i in range(n):
            print(f"    const spint p{i} = {pf[i]};")
        print(f"    spint t0, t1;")
        print(f"    spint tmpvec[{n}];")
        print(f"    int r = 0;")
        print(f"    asm volatile(")
        print(f'        "ldr    %[t0], [%[a], #0]\\n"')
        print(f'        "subs   %[t0], %[t0], %[p0]\\n"')
        for i in range(1, n):
            if i % 2 == 0:
                rc, rp = "t0", "t1"
            else:
                rc, rp = "t1", "t0"
            print(f'        "ldr    %[{rc}], [%[a], #{i * 4}]\\n"')
            print(f'        "str    %[{rp}], [%[tmpvec], #{(i - 1) * 4}]\\n"')
            print(f'        "sbcs   %[{rc}], %[{rc}], %[p{i}]\\n"')
        print(f'        "str    %[{rc}], [%[tmpvec], #{(n - 1) * 4}]\\n"')

        self.gen_asm_conditional_loadstore(["t0", "t1"], "tmpvec", "a", 0, 0, p, n)

        print(f'        "adc    %[r], %[r], %[r]\\n"')
        print(f'        : [t0] "=&r" (t0), [t1] "=&r" (t1), [r] "+&r" (r)')
        print(f'        : [a] "r" (a)', end="")
        for i in range(n):
            print(f', [p{i}] "rI" (p{i})', end="")
        print(f', [tmpvec] "r" (tmpvec)')
        print(f'        : "cc", "memory");')
        print(f"")
        print(f"    return 1 - r;")

    # generates constant time conditional subtraction for primes that have medium size (more than 8, less than 15 generally)
    # * optsub indicates a strategy of minimizing temp variables, only works for small primes (8 limbs generally)
    # * optfsb indicates a strategy of minimizing temp variables for modfsb, only works for small primes (8 limbs generally)
    def gen_modfsb_large_code(self, pf, p=None, nlimbs=None):
        p = p or self.prime
        n = nlimbs or p.nlimbs
        print(f"    const spint p[{n}] = {{{pf[0]}", end="")
        for i in range(1, n):
            print(f", {pf[i]}", end="")
        print(f"}};")
        print(f"    spint t0, t1, t2, t3;")
        print(f"    spint tmpvec[{n}];")
        print(f"    int r = 0;")
        print(f"    asm volatile(")
        print(f'        "ldr    %[t0], [%[a], #0]\\n"')
        print(f'        "ldr    %[t2], [%[p], #0]\\n"')
        print(f'        "subs   %[t0], %[t0], %[t2]\\n"')
        for i in range(1, n):
            if i % 2 == 0:
                rc, rp = "t0", "t1"
            else:
                rc, rp = "t1", "t0"
            print(f'        "ldr    %[{rc}], [%[a], #{i * 4}]\\n"')
            print(f'        "ldr    %[t2], [%[p], #{i * 4}]\\n"')
            print(f'        "str    %[{rp}], [%[tmpvec], #{(i - 1) * 4}]\\n"')
            print(f'        "sbcs   %[{rc}], %[{rc}], %[t2]\\n"')
        print(f'        "str    %[{rc}], [%[tmpvec], #{(n - 1) * 4}]\\n"')

        self.gen_asm_conditional_loadstore(["t0", "t1", "t2", "t3"], "tmpvec", "a", 0, 0, p, n)

        print(f'        "adc    %[r], %[r], %[r]\\n"')
        print(f'        : [t0] "=&r" (t0), [t1] "=&r" (t1), [t2] "=&r" (t2), [t3] "=&r" (t3), [r] "+&r" (r)')
        print(f'        : [a] "r" (a), [p] "r" (p), [tmpvec] "r" (tmpvec)')
        print(f'        : "cc", "memory");')
        print(f"")
        print(f"    return 1 - r;")

    # generates modfsb code given a certain prime/number size
    def gen_modfsb_code(self, p=None, name=None, prime=None, nlimbs=None, optfsb=None, optsub=None):
        p = p or self.prime
        name = name or p.name
        prime = prime or p.prime
        nlimbs = nlimbs or p.nlimbs
        optfsb = p.optfsb if optfsb is None else optfsb
        optsub = p.optsub if optsub is None else optsub
        prime_factors = p.prime_factors(prime, nlimbs)
        if optsub:
            print(f"{self.small_inline_attribute}static int modfsb_{name}_ct(spint *a) {{")
            self.gen_modfsb_small_code(prime_factors, p, nlimbs)
        elif optfsb:
            print(f"{self.medium_inline_attribute}static int modfsb_{name}_ct(spint *a) {{")
            self.gen_modfsb_medium_code(prime_factors, p, nlimbs)
        else:
            print(f"{self.medium_inline_attribute}static int modfsb_{name}_ct(spint *a) {{")
            self.gen_modfsb_large_code(prime_factors, p, nlimbs)
        print(f"}}\n")

    # Helper function for multiplication and squaring, generates a single "row" for multiplication strategy
    # Representing the multiplication rhombus as a square, this would be equivalent to any row of either a or b blocks for the example below
    # aaaa[bbbb] <== possible usage of gen_mul_row_asm
    # aaaabbbb
    # aaaabbbb
    # aaaabbbb
    # aaaabbbb
    # aaaabbbb
    # aaaabbbb
    # aaaabbbb
    def gen_mul_row_asm(self, v=["t0", "t1", "t2", "t3", "t4"], first_mul="umaal", block_size=4):
        mul = first_mul
        for i in range(block_size):
            print(f'        "{mul}  %[{v[i]}], %[{v[block_size]}], %[a], %[b{i}]\\n"')
            mul = "umaal"
        return

    # Helper function for multiplication/squaring, generates the first block when it is a single row for a multiplication/squaring strategy
    # Representing the multiplication rhombus as a square, this would be equivalent to the b block for the example below
    # aaaa[b]
    # aaaa[b]
    # aaaa[b]
    # aaaa[b]
    # aaaa[b]
    def gen_mul_first_block_single_row_asm(self, n, init=0):
        # First Block with 1 row
        blocks = n // 4
        v = ["t0", "t1", "t2", "t3", "t4"]
        q_label = "q"
        if init > 0:  # we are in a squaring, use p instead of q
            q_label = "p"
        p_addr = 4 * init
        r_addr = 4 * init
        # invert logic, now a is responsible for q operand and b for p operand
        print(f"    a = {q_label}[0];")
        print("    asm volatile(")
        print('        ".p2align 2\\n"')
        for t in v[1:-1]:
            print(f'        "mov.w  %[{t}], #0\\n"')
        # Generate all rows
        # join ldr/str for efficiency
        first_mul = "umull"
        for i in range(blocks):
            for j in range(4):
                print(f'        "ldr.w  %[b{j}], [%[p], #{p_addr}]\\n"')
                p_addr += 4
            self.gen_mul_row_asm(v, first_mul=first_mul)
            first_mul = "umaal"
            for t in v[:-1]:
                print(f'        "str.w  %[{t}], [%[r], #{r_addr}]\\n"')
                r_addr += 4
            if i < blocks - 1:
                # Not final round, clear necessary registers
                for t in v[:-1]:
                    print(f'        "mov.w  %[{t}], #0\\n"')
            elif init == 0:  # need to do final multiplication (if init==1 there is no need)
                # Generate final multiplication (since n%4==1) and did full round
                print(f'        "mov.w  %[t0], #0\\n"')
                print(f'        "ldr.w  %[b0], [%[p], #{p_addr}]\\n"')
                print(f'        "umaal  %[t0], %[t4], %[a], %[b0]\\n"')
                print(f'        "str.w  %[t0], [%[r], #{r_addr}]\\n"')
                r_addr += 4
        print(f'        "str.w  %[t4], [%[r], #{r_addr}]\\n"')  # final store
        print('        : [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [b0] "=&r"(b0),')
        print('          [b1] "=&r"(b1), [b2] "=&r"(b2), [b3] "=&r"(b3)')
        print('        : [a] "r"(a), [p] "r"(p), [r] "r"(r)')
        print('        : "cc", "memory");')

    # Helper function for multiplication/squaring, generates the first block for a multiplication/squaring strategy
    # Representing the multiplication rhombus as a square, this would be equivalent to the b block for the example below
    # aaaa[bbb]
    # aaaa[bbb]
    # aaaa[bbb]
    # aaaa[bbb]
    # aaaa[bbb]
    # aaaa[bbb]
    # aaaa[bbb]
    def gen_mul_first_block_asm(self, n, rmd, init=0):
        block_size = rmd if rmd > 0 else 4
        q_label = "q"
        if init > 0:  # we are in a squaring, use p instead of q
            q_label = "p"
        v = []
        for i in range(block_size + 1):
            v += [f"t{i}"]

        # if block has size one, change logic of generation for efficiency
        if block_size == 1:
            self.gen_mul_first_block_single_row_asm(n, init)
            return
        # block size != 1, continue with same logic

        # First Block with block_size rows
        for i in range(block_size):
            print(f"    b{i} = {q_label}[{i}];")
        print("    asm volatile(")
        print('        ".p2align 2\\n"')
        # zeroing registers
        p_addr = 0
        r_addr = 0
        if init > 0:  # we are in a squaring
            p_addr = 4
            r_addr = 4
            for t in v[2:]:
                print(f'        "mov.w  %[{t}], #0\\n"')
            self.gen_sqr_incomplete_rows(v, r_addr, block_size)
            v = v[block_size - 1 :] + v[: block_size - 1]
            p_addr = 4 * block_size
            r_addr = 4 * block_size
        else:  # regular multiplication
            for t in v[1:-1]:
                print(f'        "mov.w  %[{t}], #0\\n"')
        # Gen first load
        # loading from p
        print(f'        "ldr.w   %[a], [%[p], #{p_addr}]\\n"')
        p_addr += 4
        # Gen rows
        first_mul = "umaal" if init > 0 else "umull"
        for a in range(init, n):
            # generating row
            self.gen_mul_row_asm(v, first_mul=first_mul, block_size=block_size)
            first_mul = "umaal"
            t = v[0]
            if a < n - 1:
                # storing and zeroing register and loading next
                print(f'        "ldr.w   %[a], [%[p], #{p_addr}]\\n"')
                print(f'        "str.w  %[{t}], [%[r], #{r_addr}]\\n"')
                print(f'        "mov.w  %[{t}], #0\\n"')
                # rotate register list, update adresses
                v = v[1:] + v[:1]
                r_addr += 4
                p_addr += 4
            else:
                # last row
                for t in v:
                    print(f'        "str.w  %[{t}], [%[r], #{r_addr}]\\n"')
                    r_addr += 4
        # gen variables for inline asm
        print("        : ", end="")
        for t in v:
            print(f'[{t}] "=&r"({t}), ', end="")
        print('[a] "=&r"(a)')
        print("        : ", end="")
        for i in range(block_size):
            print(f'[b{i}] "r"(b{i}), ', end="")
        print('[p] "r"(p), [r] "r"(r)')
        print('        : "cc", "memory");')
        return

    # Function for multiplication using inline assembly
    # Representing the multiplication rhombus as a square, the strategy follows the example below for 10 limbs,
    # where there are 3 blocks, starting from c towards a
    # aaaabbbbcc
    # aaaabbbbcc
    # aaaabbbbcc
    # aaaabbbbcc
    # aaaabbbbcc
    # aaaabbbbcc
    # aaaabbbbcc
    # aaaabbbbcc
    # aaaabbbbcc
    # aaaabbbbcc
    def gen_mul_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        n = nlimbs or p.nlimbs
        print(f"ALWAYS_INLINE static void mul_{name}_ct(const spint *p, const spint *q, spint *r) {{")
        print("    spint t0, t1, t2, t3, t4, a, b0, b1, b2, b3;")

        # assume result is greater or equal to 1
        blocks = n // 4  # number of full blocks
        rmd = n % 4  # remainder (first block row size)

        # First Block
        r_addr = 0
        p_addr = 0
        self.gen_mul_first_block_asm(n, rmd)

        initial_row = rmd if rmd > 0 else 4
        blocks = blocks if rmd > 0 else blocks - 1

        # Gen other blocks (obligatory to be a 4 element per row block)
        for c in range(blocks):
            r_addr = (c * 4) + initial_row
            print(f"    b0 = q[{r_addr+0}];")
            print(f"    b1 = q[{r_addr+1}];")
            print(f"    b2 = q[{r_addr+2}];")
            print(f"    b3 = q[{r_addr+3}];")
            print(f"    t0 = r[{r_addr+0}];")
            print(f"    t1 = r[{r_addr+1}];")
            print(f"    t2 = r[{r_addr+2}];")
            print(f"    t3 = r[{r_addr+3}];")
            print(f"    t4 = 0;")
            print("    asm volatile(")
            print('        ".p2align 2\\n"')
            r_addr *= 4
            p_addr = 0
            v = ["t0", "t1", "t2", "t3", "t4"]
            add = "adds"
            end_n_rows = 4 if c == 0 else 3  # if first full block we did not fill with carry row n-4
            # Generate first n-(3 or 4) rows (reloading partial values from previous column)
            for i in range(n - end_n_rows):
                t0 = v[0]
                t4 = v[4]
                # generating row
                print(f'        "ldr.w   %[a], [%[p], #{p_addr}]\\n"')
                self.gen_mul_row_asm(v)
                # storing and zeroing register
                print(f'        "ldr.w   %[a], [%[r], #{r_addr+16}]\\n"')
                print(f'        "str.w  %[{t0}], [%[r], #{r_addr}]\\n"')
                print(f'        "mov.w  %[{t0}], #0\\n"')
                print(f'        "{add}.w %[{t4}], %[{t4}], %[a]\\n"')
                # rotate register list, update adresses
                r_addr += 4
                p_addr += 4
                v = v[1:] + v[:1]
                add = "adcs"
            # Generate last 3 or 4 rows without partial values loading
            print(f'        "ldr.w   %[a], [%[p], #{p_addr}]\\n"')
            for i in range(end_n_rows):
                t0 = v[0]
                t4 = v[4]
                # generating row
                self.gen_mul_row_asm(v)
                if i < (end_n_rows - 1):
                    p_addr += 4
                    # storing and zeroing register
                    print(f'        "ldr.w   %[a], [%[p], #{p_addr}]\\n"')
                    print(f'        "str.w  %[{t0}], [%[r], #{r_addr}]\\n"')
                    print(f'        "mov.w  %[{t0}], #0\\n"')
                    print(f"#ifdef __clang__")
                    print(f'        "adcs   %[{t4}], %[{t4}], #0\\n"')
                    print(f"#else")
                    print(f'        "adcs.w %[{t4}], %[{t4}], #0\\n"')
                    print(f"#endif")

                    # rotate register list, update adresses
                    r_addr += 4
                    v = v[1:] + v[:1]
                else:
                    # store all last values

                    print(f"#ifdef __clang__")
                    print(f'        "adcs   %[{t4}], %[{t4}], #0\\n"')
                    print(f"#else")
                    print(f'        "adcs.w %[{t4}], %[{t4}], #0\\n"')
                    print(f"#endif")
                    for t in v:
                        print(f'        "str.w  %[{t}], [%[r], #{r_addr}]\\n"')
                        r_addr += 4
                    if c < blocks - 1:
                        print(f'        "mov.w  %[{t0}], #0\\n"')
                        print(f"#ifdef __clang__")
                        print(f'        "adcs   %[{t0}], %[{t0}], #0\\n"')
                        print(f"#else")
                        print(f'        "adcs.w %[{t0}], %[{t0}], #0\\n"')
                        print(f"#endif")
                        print(f'        "str.w  %[{t0}], [%[r], #{r_addr}]\\n"')

            print('        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)')
            print('        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)')
            print('        : "cc", "memory");')

        print("}\n")

    # Helper function for squaring, generate incomplete rows of multiplication for squaring strategy
    # Representing the squaring rhombus as a triangle, this would be equivalent to 'a' in the example below
    #      b       [aaa]bbb
    #     b b       [aa]bbb
    #    b b b  <==> [a]bbb
    #   a b b b         bbb
    #  a a b b b         bb
    # a a a b b b         b
    #
    def gen_sqr_incomplete_rows(self, v, r_addr, size):
        # Gen incomplete rows
        # generating row
        if size > 1:
            print(f'        "umull  %[{v[0]}], %[{v[1]}], %[b0], %[b1]\\n"')
            print(f'        "str.w  %[{v[0]}], [%[r], #{r_addr}]\\n"')
            print(f'        "mov.w  %[{v[0]}], #0\\n"')
            r_addr += 4
        if size > 2:
            print(f'        "umaal  %[{v[1]}], %[{v[3]}], %[b0], %[b2]\\n"')
            print(f'        "umaal  %[{v[2]}], %[{v[3]}], %[b1], %[b2]\\n"')
            print(f'        "str.w  %[{v[1]}], [%[r], #{r_addr}]\\n"')
            print(f'        "mov.w  %[{v[1]}], #0\\n"')
            r_addr += 4
        if size > 3:
            print(f'        "umaal  %[{v[2]}], %[{v[0]}], %[b0], %[b3]\\n"')
            print(f'        "umaal  %[{v[3]}], %[{v[0]}], %[b1], %[b3]\\n"')
            print(f'        "umaal  %[{v[4]}], %[{v[0]}], %[b2], %[b3]\\n"')
            print(f'        "str.w  %[{v[2]}], [%[r], #{r_addr}]\\n"')
            print(f'        "mov.w  %[{v[2]}], #0\\n"')
        return

    # Function for squaring using inline assembly (specialized for 256bits)
    def gen_sqr_256bits_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        print(f"ALWAYS_INLINE static void sqr_{name}_ct(const spint *p, spint *r) {{")
        print(f"    spint t5", end="")
        for i in range(6, (nlimbs * 2) - 1):
            print(f", t{i}", end="")
        print(";")
        print(f"    spint T", end="")
        for i in range(4, nlimbs * 2):
            print(f", T{i}", end="")
        print(";")
        # first part in assembly
        print(
            """
    spint t, a0, a1, a2, a3, a4;

    T = 0;

    asm volatile(
        ".p2align 2\\n"
        "ldr.w %[a0], [%[a]]\\n"
        "ldr.w %[a1], [%[a], #4]\\n"
        "umull  %[t], %[t8],  %[a0],  %[a1]\\n"
        "umull %[T0], %[T1],  %[a0],  %[a0]\\n"
        "umaal %[T1], %[T],   %[two], %[t]\\n"
        "ldr.w %[a2], [%[a], #8]\\n"
        "str.w %[T0], [%[res]]\\n"
        "ldr.w %[a3], [%[a], #12]\\n"
        "str.w %[T1], [%[res], #4]\\n"
        "mov.w  %[t], #0\\n"
        "umaal  %[t], %[t8],  %[a0],  %[a2]\\n"
        "umull %[T0], %[T1],  %[a1],  %[a1]\\n"
        "umaal %[T0], %[T],   %[two], %[t]\\n"
        "umull  %[t], %[t10], %[a0],  %[a3]\\n"
        "umaal  %[t], %[t8],  %[a1],  %[a2]\\n"
        "umaal %[T1], %[T],   %[two], %[t]\\n"
        "ldr.w %[a4], [%[a], #16]\\n"
        "str.w %[T0], [%[res], #8]\\n"
        "str.w %[T1], [%[res], #12]\\n"
        "mov.w  %[t], #0\\n"
        "umaal  %[t], %[t10], %[a0],  %[a4]\\n"
        "umaal  %[t], %[t8],  %[a1],  %[a3]\\n"
        "umull %[T0], %[T1],  %[a2],  %[a2]\\n"
        "umaal %[T0], %[T],   %[two], %[t]\\n"
        "str.w %[T0], [%[res], #16]\\n"
        : [a0] "=&r"(a0), [a1] "=&r"(a1), [a2] "=&r"(a2), [a3] "=&r"(a3), [a4] "=&r"(a4), [t] "=&r"(t), [t8] "=&r"(t8),
          [t10] "=&r"(t10), [T0] "=&r"(T4), [T1] "=&r"(T5), [T] "+&r"(T)
        : [a] "r"(p), [res] "r"(r), [two] "r"(2)
        : "memory");"""
        )
        # middle part in c
        print(
            """

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
    r[9] = T9;"""
        )
        # last part in c
        print(
            """

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
    r[15] = T15;"""
        )
        print("}\n")

    # Given a number of limbs, determine best block allocation.
    # Returns the number of full 4-row blocks, the size of the first block and the size of the last triangular block
    def gen_sqr_define_rhombus_blocks(self, nlimbs=None):
        n = nlimbs or self.prime.nlimbs
        # result is greater or equal to 1 (since n > 8)
        blocks = n // 4 - 1  # number of full blocks
        rmd = n % 4  # remainder (determines last block size)
        first_block_size = 0
        last_block_size = 0
        # if rmd == 0:  # last block is a triangle of size 3
        #     first_block_size = 4
        #     last_block_size = 3
        if rmd == 0:  # incorporate a 3-sized incomplete row to a triangle of 4, so now last block is a triangle of size 7
            first_block_size = 4
            blocks -= 1
            last_block_size = 7
        elif rmd == 1:  # last block is a triangle of size 4
            first_block_size = 4
            last_block_size = 4
        elif rmd == 2:  # incorporate a 2-sized incomplete row, so now last block is a triangle of size 5
            first_block_size = 4
            last_block_size = 5
        elif rmd == 3:  # incorporate a 3-sized incomplete row, so now last block is a triangle of size 6
            first_block_size = 4
            last_block_size = 6
        else:  # should never reach this now.
            first_block_size = rmd
            last_block_size = 3
        return blocks, first_block_size, last_block_size

    # Function for squaring using inline assembly
    # Representing the squaring rhombus as a triangle, the strategy follows the example below for 12 limbs,
    # where there are 3 blocks, starting from c towards a, with a final pass x doubling and multiplying the intermediary results
    # xaaabbbbcccc
    #  xaabbbbcccc
    #   xabbbbcccc
    #    xbbbbcccc
    #     xbbbcccc
    #      xbbcccc
    #       xbcccc
    #        xcccc
    #         xccc
    #          xcc
    #           xc
    #            x
    def gen_sqr_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        n = nlimbs or p.nlimbs
        # assumes n>=8
        if n == 8:
            # special 256bit case (i.e. case with only a single full last triangular block without partial values)
            self.gen_sqr_256bits_code(p, name, n)
            return
        if n < 8:
            # not supported for now!
            print("Sqr generation not supported for numbers with fewer than 8 limbs (256-bits)!")
            exit(1)
        # We can assume n>=9 now.
        print(f"ALWAYS_INLINE static void sqr_{name}_ct(const spint *p, spint *r) {{")
        print("    spint t0, t1, t2, t3, t4, a, b0, b1, b2, b3;")

        # Determine block sizes/strategy
        blocks, initial_row, last_row = self.gen_sqr_define_rhombus_blocks(n)

        # ==== Generate ai*aj values ====

        # First Block (size determined by initial_row)
        r_addr = 0  # current address offset for return array
        p_addr = 0  # current address offset for input array
        v = ["t0", "t1", "t2", "t3", "t4"]  # ordering of temporary variables
        # generate first block (different since there are no partial values to load)
        self.gen_mul_first_block_asm(n, initial_row % 4, init=initial_row)
        blocks = blocks if initial_row < 4 else blocks - 1  # decrease number of full blocks to compute

        # Gen other full blocks
        r_addr_init = 1 + 2 * initial_row  # address offset after first block
        end_n_rows = 4  # n-end_n_rows determines the number of rows that need to load partial values
        for c in range(blocks):
            r_addr = r_addr_init + (c * 8)  # set current address offset for output writing/reading partial values
            # r_addr = (c * 8) + 2 * initial_row + 1
            p_addr = (c * 4) + initial_row  # set current address offset for input reading
            # load input and as many partial values as possible
            print(f"    b0 = p[{p_addr+0}];")
            print(f"    b1 = p[{p_addr+1}];")
            print(f"    b2 = p[{p_addr+2}];")
            print(f"    b3 = p[{p_addr+3}];")
            print(f"    t0 = r[{r_addr+0}];")
            print(f"    t1 = r[{r_addr+1}];")
            print(f"    t2 = r[{r_addr+2}];")
            print(f"    t3 = r[{r_addr+3}];")
            print(f"    t4 = r[{r_addr+4}];")
            print("    asm volatile(")
            print('        ".p2align 2\\n"')
            v = ["t0", "t1", "t2", "t3", "t4"]
            r_addr *= 4

            # Gen incomplete rows ("triangle part of block")
            # generating row
            print(f'        "mov.w  %[a], #0\\n"')
            print(f'        "umaal  %[{v[0]}], %[a], %[b0], %[b1]\\n"')
            print(f'        "str.w  %[{v[0]}], [%[r], #{r_addr}]\\n"')
            print(f'        "mov.w  %[{v[0]}], #0\\n"')
            r_addr += 4
            print(f'        "umaal  %[{v[1]}], %[a], %[b0], %[b2]\\n"')
            print(f'        "umaal  %[{v[2]}], %[a], %[b1], %[b2]\\n"')
            print(f'        "ldr.w  %[{v[0]}], [%[r], #{r_addr+16}]\\n"')
            print(f'        "str.w  %[{v[1]}], [%[r], #{r_addr}]\\n"')
            print(f'        "mov.w  %[{v[1]}], #0\\n"')
            print(f'        "adds.w %[{v[3]}], %[{v[3]}], %[a]\\n"')
            print(f'        "mov.w  %[a], #0\\n"')
            print(f"#ifdef __clang__")
            print(f'        "adcs   %[{v[4]}], %[{v[4]}], #0\\n"')
            print(f"#else")
            print(f'        "adcs.w %[{v[4]}], %[{v[4]}], #0\\n"')
            print(f"#endif")
            r_addr += 4
            print(f'        "umaal  %[{v[2]}], %[a], %[b0], %[b3]\\n"')
            print(f'        "umaal  %[{v[3]}], %[a], %[b1], %[b3]\\n"')
            print(f'        "umaal  %[{v[4]}], %[a], %[b2], %[b3]\\n"')
            print(f'        "ldr.w  %[{v[1]}], [%[r], #{r_addr+16}]\\n"')
            print(f'        "str.w  %[{v[2]}], [%[r], #{r_addr}]\\n"')
            print(f'        "mov.w  %[{v[2]}], #0\\n"')
            print(f"#ifdef __clang__")
            print(f'        "adcs   %[{v[0]}], %[{v[0]}], %[a]\\n"')
            print(f'        "adcs   %[{v[1]}], %[{v[1]}], #0\\n"')
            print(f"#else")
            print(f'        "adcs.w %[{v[0]}], %[{v[0]}], %[a]\\n"')
            print(f'        "adcs.w %[{v[1]}], %[{v[1]}], #0\\n"')
            print(f"#endif")

            v = ["t3", "t4", "t0", "t1", "t2"]

            start_mid_rows = ((c + 1) * 4) + initial_row  # start_mid_rows indicates the first full row of the block
            p_addr = start_mid_rows * 4
            r_addr += 4

            # add = "adcs"
            end_n_rows = 4 if c == 0 else 3  # if first full block we did not fill with carry row n-4
            # Generate first n-end_n_rows rows (reloading partial values from previous column)
            for i in range(start_mid_rows, n - end_n_rows):
                t0 = v[0]
                t4 = v[4]
                # generating row
                print(f'        "ldr.w   %[a], [%[p], #{p_addr}]\\n"')
                self.gen_mul_row_asm(v)
                # storing and zeroing register
                print(f'        "ldr.w   %[a], [%[r], #{r_addr+16}]\\n"')
                print(f'        "str.w  %[{t0}], [%[r], #{r_addr}]\\n"')
                print(f'        "mov.w  %[{t0}], #0\\n"')
                print(f"#ifdef __clang__")
                print(f'        "adcs   %[{t4}], %[{t4}], %[a]\\n"')
                print(f"#else")
                print(f'        "adcs.w %[{t4}], %[{t4}], %[a]\\n"')
                print(f"#endif")
                # rotate register list, update adresses
                r_addr += 4
                p_addr += 4
                v = v[1:] + v[:1]
                # add = "adcs"

            # Generate last 3 or 4 rows without partial values loading
            print(f'        "ldr.w   %[a], [%[p], #{p_addr}]\\n"')
            for i in range(end_n_rows):
                t0 = v[0]
                t4 = v[4]
                # generating row
                self.gen_mul_row_asm(v)
                if i < (end_n_rows - 1):
                    p_addr += 4
                    # storing and zeroing register
                    print(f'        "ldr.w   %[a], [%[p], #{p_addr}]\\n"')
                    print(f'        "str.w  %[{t0}], [%[r], #{r_addr}]\\n"')
                    print(f'        "mov.w  %[{t0}], #0\\n"')
                    print(f"#ifdef __clang__")
                    print(f'        "adcs   %[{t4}], %[{t4}], #0\\n"')
                    print(f"#else")
                    print(f'        "adcs.w %[{t4}], %[{t4}], #0\\n"')
                    print(f"#endif")
                    # rotate register list, update adresses
                    r_addr += 4
                    v = v[1:] + v[:1]
                else:
                    # store all last values
                    print(f"#ifdef __clang__")
                    print(f'        "adcs   %[{t4}], %[{t4}], #0\\n"')
                    print(f"#else")
                    print(f'        "adcs.w %[{t4}], %[{t4}], #0\\n"')
                    print(f"#endif")
                    for t in v:
                        print(f'        "str.w  %[{t}], [%[r], #{r_addr}]\\n"')
                        r_addr += 4
                    print(f'        "mov.w  %[{t0}], #0\\n"')
                    print(f"#ifdef __clang__")
                    print(f'        "adcs   %[{t0}], %[{t0}], #0\\n"')
                    print(f"#else")
                    print(f'        "adcs.w %[{t0}], %[{t0}], #0\\n"')
                    print(f"#endif")
                    print(f'        "str.w  %[{t0}], [%[r], #{r_addr}]\\n"')

            print('        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)')
            print('        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [p] "r"(p), [r] "r"(r)')
            print('        : "cc", "memory");')

        # Generate last incomplete ai*aj triangle rows
        r_addr = r_addr_init + (blocks * 8)
        # r_addr = (c * 8) + 2 * initial_row + 1
        p_addr = (blocks * 4) + initial_row
        # gen initialization for last block of sizes 3 or 4

        # Gen incomplete rows
        # generating 3 rows
        if last_row <= 3:
            print(f"    b0 = p[{p_addr+0}]; b1 = p[{p_addr+1}]; b2 = p[{p_addr+2}]; b3 = p[{p_addr+3}];")
            t3_text = f"r[{r_addr+3}]" if end_n_rows == 3 else "0"
            t4_text = "0"
            print(f"    t0 = r[{r_addr+0}]; t1 = r[{r_addr+1}]; t2 = r[{r_addr+2}]; t3 = {t3_text}; t4 = {t4_text};")
            v = ["t0", "t1", "t2", "t3", "t4"]
            r_addr *= 4

            print("    asm volatile(")
            print('        ".p2align 2\\n"')
            print(f'        "mov.w  %[a], #0\\n"')
            print(f'        "umaal  %[{v[0]}], %[{v[4]}], %[b0], %[b1]\\n"')
            print(f'        "str.w  %[{v[0]}], [%[r], #{r_addr}]\\n"')
            print(f'        "mov.w  %[{v[0]}], #0\\n"')
            print(f'        "umaal  %[{v[1]}], %[{v[4]}], %[b0], %[b2]\\n"')
            print(f'        "umaal  %[{v[2]}], %[{v[4]}], %[b1], %[b2]\\n"')
            print(f'        "umaal  %[{v[2]}], %[{v[0]}], %[b0], %[b3]\\n"')
            print(f'        "umaal  %[{v[3]}], %[{v[0]}], %[b1], %[b3]\\n"')
            print(f'        "umaal  %[{v[3]}], %[{v[4]}], %[a],  %[a]\\n"')
            print(f'        "umaal  %[{v[4]}], %[{v[0]}], %[b2], %[b3]\\n"')
            print(f'        "str.w  %[{v[1]}], [%[r], #{r_addr+4}]\\n"')
            print(f'        "str.w  %[{v[2]}], [%[r], #{r_addr+8}]\\n"')
            print(f'        "str.w  %[{v[3]}], [%[r], #{r_addr+12}]\\n"')
            print(f'        "str.w  %[{v[4]}], [%[r], #{r_addr+16}]\\n"')
            print(f'        "str.w  %[{v[0]}], [%[r], #{r_addr+20}]\\n"')
            print('        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4), [a] "=&r"(a)')
            print('        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [r] "r"(r)')
            print('        : "memory");')
        elif last_row == 4:
            # generating 4 rows
            print(f"    b0 = p[{p_addr+0}]; b1 = p[{p_addr+1}]; b2 = p[{p_addr+2}]; b3 = p[{p_addr+3}];")
            t3_text = f"r[{r_addr+3}]" if end_n_rows == 3 else "0"
            t4_text = "0"
            print(f"    a = p[{p_addr+4}];")
            t3_text = f"r[{r_addr+3}]"
            print(f"    t0 = r[{r_addr+0}]; t1 = r[{r_addr+1}]; t2 = r[{r_addr+2}]; t3 = {t3_text}; t4 = {t4_text};")
            v = ["t4", "t0", "t1", "t2", "t3"]
            r_addr *= 4
            print("    asm volatile(")
            print('        ".p2align 2\\n"')
            print(f'        "umaal  %[{v[0]}], %[{v[1]}], %[b0], %[b1]\\n"')
            print(f'        "umaal  %[{v[1]}], %[{v[2]}], %[b0], %[b2]\\n"')
            print(f'        "str.w  %[{v[0]}], [%[r], #{r_addr}]\\n"')
            print(f'        "str.w  %[{v[1]}], [%[r], #{r_addr+4}]\\n"')
            print(f'        "mov.w  %[{v[0]}], #0\\n"')
            print(f'        "umaal  %[{v[2]}], %[{v[3]}], %[b0], %[b3]\\n"')
            print(f'        "umaal  %[{v[2]}], %[{v[0]}], %[b1], %[b2]\\n"')
            print(f'        "umaal  %[{v[3]}], %[{v[0]}], %[b0], %[a]\\n"')
            print(f'        "umaal  %[{v[3]}], %[{v[4]}], %[b1], %[b3]\\n"')
            if end_n_rows == 3:
                print(f'        "ldr.w   %[{v[1]}], [%[r], #{r_addr+16}]\\n"')
            else:
                print(f'        "mov.w  %[{v[1]}], #0\\n"')
            print(f'        "str.w  %[{v[2]}], [%[r], #{r_addr+8}]\\n"')
            print(f'        "str.w  %[{v[3]}], [%[r], #{r_addr+12}]\\n"')
            print(f'        "mov.w  %[{v[2]}], #0\\n"')
            print(f'        "umaal  %[{v[4]}], %[{v[0]}], %[b1], %[a]\\n"')
            print(f'        "umaal  %[{v[4]}], %[{v[1]}], %[b2], %[b3]\\n"')
            print(f'        "umaal  %[{v[0]}], %[{v[1]}], %[b2], %[a]\\n"')
            print(f'        "umaal  %[{v[1]}], %[{v[2]}], %[b3], %[a]\\n"')
            print(f'        "str.w  %[{v[4]}], [%[r], #{r_addr+16}]\\n"')
            print(f'        "str.w  %[{v[0]}], [%[r], #{r_addr+20}]\\n"')
            print(f'        "str.w  %[{v[1]}], [%[r], #{r_addr+24}]\\n"')
            print(f'        "str.w  %[{v[2]}], [%[r], #{r_addr+28}]\\n"')
            print('        : [t0] "+&r"(t0), [t1] "+&r"(t1), [t2] "+&r"(t2), [t3] "+&r"(t3), [t4] "+&r"(t4)')
            print('        : [b0] "r"(b0), [b1] "r"(b1), [b2] "r"(b2), [b3] "r"(b3), [a] "r"(a), [r] "r"(r)')
            print('        : "memory");')
            v = ["t0", "t1", "t2", "t3", "t4"]
        elif last_row == 5:
            r_addr *= 4
            # generating last block with 5 rows
            print(f"    spint a0 = p[{p_addr+0}], a1 = p[{p_addr+1}], a2 = p[{p_addr+2}], a3 = p[{p_addr+3}], a4 = p[{p_addr+4}], a5 = p[{p_addr+5}], c0, c1;")
            print("    asm volatile(")
            print('        ".p2align 2\\n"')
            print(f'        "ldr.w   %[c0], [%[r], #{r_addr}]\\n"')
            print(f'        "mov.w   %[t0], #0\\n"')
            print(f'        "mov.w   %[t1], #0\\n"')
            print(f'        "umaal   %[c0], %[t0], %[a1], %[a0]\\n"')
            print(f'        "ldr.w   %[c1], [%[r], #{r_addr+4}]\\n"')
            print(f'        "str.w   %[c0], [%[r], #{r_addr}]\\n"')
            print(f'        "umaal   %[c1], %[t0], %[a2], %[a0]\\n"')
            print(f'        "ldr.w   %[c0], [%[r], #{r_addr+8}]\\n"')
            print(f'        "str.w   %[c1], [%[r], #{r_addr+4}]\\n"')
            print(f'        "umaal   %[c0], %[t0], %[a3], %[a0]\\n"')
            print(f'        "umaal   %[c0], %[t1], %[a2], %[a1]\\n"')
            print(f'        "ldr.w   %[c1], [%[r], #{r_addr+12}]\\n"')
            print(f'        "str.w   %[c0], [%[r], #{r_addr+8}]\\n"')
            print(f'        "umaal   %[c1], %[t0], %[a4], %[a0]\\n"')
            print(f'        "umaal   %[c1], %[t1], %[a3], %[a1]\\n"')
            print(f'        "ldr.w   %[c0], [%[r], #{r_addr+16}]\\n"')
            print(f'        "str.w   %[c1], [%[r], #{r_addr+12}]\\n"')
            print(f'        "umaal   %[c0], %[t0], %[a5], %[a0]\\n"')
            print(f'        "mov.w   %[a0], #0\\n"')
            print(f'        "umaal   %[c0], %[t1], %[a4], %[a1]\\n"')
            print(f'        "umaal   %[c0], %[a0], %[a3], %[a2]\\n"')
            if end_n_rows == 3:  # there is a partial value on r_addr+20
                print(f'        "ldr.w   %[c1], [%[r], #{r_addr+20}]\\n"')
            else:
                print(f'        "mov.w  %[c1], #0\\n"')
            print(f'        "str.w   %[c0], [%[r], #{r_addr+16}]\\n"')
            print(f'        "umaal   %[c1], %[t0], %[a5], %[a1]\\n"')
            print(f'        "mov.w   %[a1], #0\\n"')
            print(f'        "umaal   %[c1], %[t1], %[a4], %[a2]\\n"')
            print(f'        "umaal   %[c1], %[a0], %[a1], %[a1]\\n"')  # way to add with carry without need for adcs/carry logic
            print(f'        "str.w   %[c1], [%[r], #{r_addr+20}]\\n"')
            print(f'        "umaal   %[t0], %[t1], %[a5], %[a2]\\n"')
            print(f'        "umaal   %[t0], %[a0], %[a4], %[a3]\\n"')
            print(f'        "str.w   %[t0], [%[r], #{r_addr+24}]\\n"')
            print(f'        "umaal   %[t1], %[a0], %[a5], %[a3]\\n"')
            print(f'        "str.w   %[t1], [%[r], #{r_addr+28}]\\n"')
            print(f'        "umaal   %[a0], %[a1], %[a5], %[a4]\\n"')
            print(f'        "str.w   %[a0], [%[r], #{r_addr+32}]\\n"')
            print(f'        "str.w   %[a1], [%[r], #{r_addr+36}]\\n"')
            # print('        : [a0] "=&r"(a0), [a1] "=&r"(a1), [a2] "=&r"(a2), [a3] "=&r"(a3), [a4] "=&r"(a4), [a5] "=&r"(a5),')
            print('        : [a0] "+&r"(a0), [a1] "+&r"(a1), [c0] "=&r"(c0), [c1] "=&r"(c1), [t0] "=&r"(t0), [t1] "=&r"(t1)')
            print('        : [a2] "r"(a2), [a3] "r"(a3), [a4] "r"(a4), [a5] "r"(a5), [r] "r"(r)')
            print('        : "memory");')

        elif last_row == 6:
            r_addr *= 4
            # generating last block with 6 rows
            print(f"    spint a0=p[{p_addr+0}], a1=p[{p_addr+1}], a2=p[{p_addr+2}], a3=p[{p_addr+3}], a4=p[{p_addr+4}], a5=p[{p_addr+5}], a6=p[{p_addr+6}], c0, c1;")
            print("    asm volatile(")
            print('        ".p2align 2\\n"')
            print(f'        "ldr.w   %[c0], [%[r], #{r_addr}]\\n"')
            print(f'        "mov.w   %[t0], #0\\n"')
            print(f'        "mov.w   %[t1], #0\\n"')
            print(f'        "mov.w   %[t2], #0\\n"')
            print(f'        "umaal   %[c0], %[t0], %[a1], %[a0]\\n"')
            print(f'        "ldr.w   %[c1], [%[r], #{r_addr+4}]\\n"')
            print(f'        "str.w   %[c0], [%[r], #{r_addr}]\\n"')
            print(f'        "umaal   %[c1], %[t0], %[a2], %[a0]\\n"')
            print(f'        "ldr.w   %[c0], [%[r], #{r_addr+8}]\\n"')
            print(f'        "str.w   %[c1], [%[r], #{r_addr+4}]\\n"')
            print(f'        "umaal   %[c0], %[t0], %[a3], %[a0]\\n"')
            print(f'        "umaal   %[c0], %[t1], %[a2], %[a1]\\n"')
            print(f'        "ldr.w   %[c1], [%[r], #{r_addr+12}]\\n"')
            print(f'        "str.w   %[c0], [%[r], #{r_addr+8}]\\n"')
            print(f'        "umaal   %[c1], %[t0], %[a4], %[a0]\\n"')
            print(f'        "umaal   %[c1], %[t1], %[a3], %[a1]\\n"')
            print(f'        "ldr.w   %[c0], [%[r], #{r_addr+16}]\\n"')
            print(f'        "str.w   %[c1], [%[r], #{r_addr+12}]\\n"')
            print(f'        "umaal   %[c0], %[t0], %[a5], %[a0]\\n"')
            print(f'        "umaal   %[c0], %[t1], %[a4], %[a1]\\n"')
            print(f'        "umaal   %[c0], %[t2], %[a3], %[a2]\\n"')
            print(f'        "ldr.w   %[c1], [%[r], #{r_addr+20}]\\n"')
            print(f'        "str.w   %[c0], [%[r], #{r_addr+16}]\\n"')
            print(f'        "umaal   %[c1], %[t0], %[a6], %[a0]\\n"')
            print(f'        "umaal   %[c1], %[t1], %[a5], %[a1]\\n"')
            print(f'        "umaal   %[c1], %[t2], %[a4], %[a2]\\n"')
            if end_n_rows == 3:  # there is a partial value on r_addr+24
                print(f'        "ldr.w   %[c0], [%[r], #{r_addr+24}]\\n"')
            else:
                print(f'        "mov.w  %[c0], #0\\n"')
            print(f'        "str.w   %[c1], [%[r], #{r_addr+20}]\\n"')
            print(f'        "umaal   %[c0], %[t0], %[a6], %[a1]\\n"')
            print(f'        "umaal   %[c0], %[t1], %[a5], %[a2]\\n"')
            print(f'        "umaal   %[c0], %[t2], %[a4], %[a3]\\n"')
            print(f'        "str.w   %[c0], [%[r], #{r_addr+24}]\\n"')
            print(f'        "umaal   %[t0], %[t1], %[a6], %[a2]\\n"')
            print(f'        "umaal   %[t0], %[t2], %[a5], %[a3]\\n"')
            print(f'        "str.w   %[t0], [%[r], #{r_addr+28}]\\n"')
            print(f'        "mov.w   %[c0], #0\\n"')
            print(f'        "umaal   %[t1], %[t2], %[a6], %[a3]\\n"')
            print(f'        "umaal   %[t1], %[c0], %[a5], %[a4]\\n"')
            print(f'        "str.w   %[t1], [%[r], #{r_addr+32}]\\n"')
            print(f'        "umaal   %[t2], %[c0], %[a6], %[a4]\\n"')
            print(f'        "str.w   %[t2], [%[r], #{r_addr+36}]\\n"')
            print(f'        "mov.w   %[t0], #0\\n"')
            print(f'        "umaal   %[c0], %[t0], %[a6], %[a5]\\n"')
            print(f'        "str.w   %[c0], [%[r], #{r_addr+40}]\\n"')
            print(f'        "str.w   %[t0], [%[r], #{r_addr+44}]\\n"')
            print('        : [c0] "=&r"(c0), [c1] "=&r"(c1), [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2)')
            print('        : [a0] "r"(a0), [a1] "r"(a1), [a2] "r"(a2), [a3] "r"(a3), [a4] "r"(a4), [a5] "r"(a5), [a6] "r"(a6), [r] "r"(r)')
            print('        : "memory");')
        elif last_row == 7:
            r_addr *= 4
            # generating last block with 6 rows
            print(f"    spint a0=p[{p_addr+0}], a1=p[{p_addr+1}], a2=p[{p_addr+2}], a3=p[{p_addr+3}];")
            print(f"    spint a4=p[{p_addr+4}], a5=p[{p_addr+5}], a6=p[{p_addr+6}], a7=p[{p_addr+7}], c0;")
            print("    asm volatile(")
            print('        ".p2align 2\\n"')
            print(f'        "ldr.w   %[c0], [%[r], #{r_addr}]\\n"')
            print(f'        "mov.w   %[t0], #0\\n"')
            print(f'        "mov.w   %[t1], #0\\n"')
            print(f'        "mov.w   %[t2], #0\\n"')

            print(f'        "umaal   %[c0], %[t0], %[a1], %[a0]\\n"')
            print(f'        "ldr.w   %[t3], [%[r], #{r_addr+4}]\\n"')
            print(f'        "str.w   %[c0], [%[r], #{r_addr}]\\n"')

            print(f'        "umaal   %[t3], %[t0], %[a2], %[a0]\\n"')
            print(f'        "ldr.w   %[c0], [%[r], #{r_addr+8}]\\n"')
            print(f'        "str.w   %[t3], [%[r], #{r_addr+4}]\\n"')

            print(f'        "umaal   %[c0], %[t0], %[a3], %[a0]\\n"')
            print(f'        "umaal   %[c0], %[t1], %[a2], %[a1]\\n"')
            print(f'        "ldr.w   %[t3], [%[r], #{r_addr+12}]\\n"')
            print(f'        "str.w   %[c0], [%[r], #{r_addr+8}]\\n"')

            print(f'        "umaal   %[t3], %[t0], %[a4], %[a0]\\n"')
            print(f'        "umaal   %[t3], %[t1], %[a3], %[a1]\\n"')
            print(f'        "ldr.w   %[c0], [%[r], #{r_addr+16}]\\n"')
            print(f'        "str.w   %[t3], [%[r], #{r_addr+12}]\\n"')

            print(f'        "umaal   %[c0], %[t0], %[a5], %[a0]\\n"')
            print(f'        "umaal   %[c0], %[t1], %[a4], %[a1]\\n"')
            print(f'        "umaal   %[c0], %[t2], %[a3], %[a2]\\n"')
            print(f'        "ldr.w   %[t3], [%[r], #{r_addr+20}]\\n"')
            print(f'        "str.w   %[c0], [%[r], #{r_addr+16}]\\n"')

            print(f'        "umaal   %[t3], %[t0], %[a6], %[a0]\\n"')
            print(f'        "umaal   %[t3], %[t1], %[a5], %[a1]\\n"')
            print(f'        "umaal   %[t3], %[t2], %[a4], %[a2]\\n"')
            print(f'        "ldr.w   %[c0], [%[r], #{r_addr+24}]\\n"')
            print(f'        "str.w   %[t3], [%[r], #{r_addr+20}]\\n"')
            print(f'        "mov.w   %[t3], #0\\n"')

            print(f'        "umaal   %[c0], %[t0], %[a7], %[a0]\\n"')
            print(f'        "umaal   %[c0], %[t1], %[a6], %[a1]\\n"')
            print(f'        "umaal   %[c0], %[t2], %[a5], %[a2]\\n"')
            print(f'        "umaal   %[c0], %[t3], %[a4], %[a3]\\n"')

            if end_n_rows == 3:  # there is a partial value on r_addr+24
                print(f'        "ldr.w   %[a0], [%[r], #{r_addr+28}]\\n"')
                print(f'        "str.w   %[c0], [%[r], #{r_addr+24}]\\n"')
                print(f'        "umaal   %[a0], %[t0], %[a7], %[a1]\\n"')
                print(f'        "umaal   %[a0], %[t1], %[a6], %[a2]\\n"')
                print(f'        "mov.w   %[c0], #0\\n"')
                print(f'        "umaal   %[a0], %[t2], %[a5], %[a3]\\n"')
                print(f'        "umaal   %[a0], %[t3], %[c0], %[c0]\\n"')
                print(f'        "str.w   %[a0], [%[r], #{r_addr+28}]\\n"')
            else:
                print(f'        "str.w   %[c0], [%[r], #{r_addr+24}]\\n"')
                print(f'        "umaal   %[t0], %[t1], %[a7], %[a1]\\n"')
                print(f'        "umaal   %[t0], %[t2], %[a6], %[a2]\\n"')
                print(f'        "umaal   %[t0], %[t3], %[a5], %[a3]\\n"')
                print(f'        "str.w   %[t0], [%[r], #{r_addr+28}]\\n"')
                print(f'        "mov.w   %[t0], #0\\n"')

            print(f'        "umaal   %[t0], %[t1], %[a7], %[a2]\\n"')
            print(f'        "umaal   %[t0], %[t2], %[a6], %[a3]\\n"')
            print(f'        "umaal   %[t0], %[t3], %[a5], %[a4]\\n"')
            print(f'        "str.w   %[t0], [%[r], #{r_addr+32}]\\n"')

            print(f'        "umaal   %[t1], %[t2], %[a7], %[a3]\\n"')
            print(f'        "umaal   %[t1], %[t3], %[a6], %[a4]\\n"')
            print(f'        "str.w   %[t1], [%[r], #{r_addr+36}]\\n"')

            print(f'        "mov.w   %[t0], #0\\n"')
            print(f'        "umaal   %[t2], %[t3], %[a7], %[a4]\\n"')
            print(f'        "umaal   %[t2], %[t0], %[a6], %[a5]\\n"')
            print(f'        "str.w   %[t2], [%[r], #{r_addr+40}]\\n"')

            print(f'        "umaal   %[t3], %[t0], %[a7], %[a5]\\n"')
            print(f'        "str.w   %[t3], [%[r], #{r_addr+44}]\\n"')
            print(f'        "mov.w   %[t1], #0\\n"')

            print(f'        "umaal   %[t0], %[t1], %[a7], %[a6]\\n"')
            print(f'        "str.w   %[t0], [%[r], #{r_addr+48}]\\n"')
            print(f'        "str.w   %[t1], [%[r], #{r_addr+52}]\\n"')

            print('        : [a0] "+&r"(a0), [c0] "=&r"(c0), [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3)')
            print('        : [a1] "r"(a1), [a2] "r"(a2), [a3] "r"(a3), [a4] "r"(a4), [a5] "r"(a5), [a6] "r"(a6), [a7] "r"(a7), [r] "r"(r)')
            print('        : "memory");')

        # generate doubling and ai*ai code
        p_addr = 0
        r_addr = 0
        print(f"    r[0] = 0;")
        print(f"    r[{(n*2)-1}] = 0;")
        print(f"    asm volatile(")
        print(f'        ".p2align 2\\n"')
        print(f'        "mov.w  %[a], #2\\n"')
        print(f'        "mov.w  %[{v[4]}], #0\\n"')
        vb = ["b0", "b1", "b2", "b3"]
        for c in range(n // 2):
            b0 = vb[0]
            b1 = vb[1]
            print(f'        "ldr.w   %[{b0}], [%[p], #{p_addr}]\\n"')
            print(f'        "ldr.w   %[{b1}], [%[p], #{p_addr+4}]\\n"')
            print(f'        "umull  %[{v[0]}], %[{v[1]}], %[{b0}], %[{b0}]\\n"')
            print(f'        "umull  %[{v[2]}], %[{v[3]}], %[{b1}], %[{b1}]\\n"')
            print(f'        "ldr.w   %[{b0}], [%[r], #{r_addr}]\\n"')
            print(f'        "ldr.w   %[{b1}], [%[r], #{r_addr+4}]\\n"')
            print(f'        "umaal  %[{v[0]}], %[{v[4]}], %[a], %[{b0}]\\n"')
            print(f'        "umaal  %[{v[1]}], %[{v[4]}], %[a], %[{b1}]\\n"')
            print(f'        "ldr.w   %[{b0}], [%[r], #{r_addr+8}]\\n"')
            print(f'        "ldr.w   %[{b1}], [%[r], #{r_addr+12}]\\n"')
            print(f'        "str.w  %[{v[0]}], [%[r], #{r_addr}]\\n"')
            print(f'        "str.w  %[{v[1]}], [%[r], #{r_addr+4}]\\n"')
            print(f'        "umaal  %[{v[2]}], %[{v[4]}], %[a], %[{b0}]\\n"')
            print(f'        "umaal  %[{v[3]}], %[{v[4]}], %[a], %[{b1}]\\n"')
            print(f'        "str.w  %[{v[2]}], [%[r], #{r_addr+8}]\\n"')
            print(f'        "str.w  %[{v[3]}], [%[r], #{r_addr+12}]\\n"')
            p_addr += 8
            r_addr += 16
            vb = vb[2:] + vb[:-2]
        if n % 2 > 0:
            b0 = vb[0]
            b1 = vb[1]
            print(f'        "ldr.w   %[{b0}], [%[p], #{p_addr}]\\n"')
            print(f'        "ldr.w   %[{b1}], [%[r], #{r_addr}]\\n"')
            print(f'        "umull  %[{v[0]}], %[{v[1]}], %[{b0}], %[{b0}]\\n"')
            print(f'        "umaal  %[{v[0]}], %[{v[4]}], %[a], %[{b1}]\\n"')
            print(f'        "add.w  %[{v[1]}], %[{v[1]}], %[{v[4]}]\\n"')
            print(f'        "str.w  %[{v[0]}], [%[r], #{r_addr}]\\n"')
            print(f'        "str.w  %[{v[1]}], [%[r], #{r_addr+4}]\\n"')

        print('        : [t0] "=&r"(t0), [t1] "=&r"(t1), [t2] "=&r"(t2), [t3] "=&r"(t3), [t4] "=&r"(t4), [a] "=&r"(a),')
        print('          [b0] "=&r"(b0), [b1] "=&r"(b1), [b2] "=&r"(b2), [b3] "=&r"(b3)')
        print('        : [p] "r"(p), [r] "r"(r)')
        print('        : "cc", "memory");')

        print("}\n")

        return

    # generates general reduction code for pseudo-Mersenne primes
    # calls specialized efficient code when prime allows
    # asmfinalred indicates if final part of reduction uses inline assembly or not
    # inplace indicates if reduction should be made inplace
    def gen_modred_pmp_standard_code(self, p=None, name=None, n=None, c=None, realn=None, realc=None, inplace=None):
        p = p or self.prime
        name = name or p.name
        n = n or p.n
        c = c or p.c
        realn = realn or p.n
        realc = realc or p.c

        nlimbs = (n + 31) // 32
        lgap = p.gap
        rgap = 32 - lgap

        # Verify bounds and stop code generation if verification fails
        verifier = Verifier(input_ub=(2**realn-realc-1)**2, output_ub=2*(2**realn-realc)-1)
        verifier.modred_pmp_standard(c, nlimbs, lgap, rgap)
        if not verifier.validate():
            print("Could not verify that the output respects the required bounds!")
            print(f"\nOutput interval:\n{verifier.output}")
            print(f"\nRequired interval:\n{verifier.required}")
            sys.exit(1)

        # Although this may not be a "small" function per se, it's performance is very critical, so we treat it as if
        # it were a small one
        print(f"{self.small_inline_attribute}static void modred_{name}_ct({'const spint *c, spint *r' if inplace==False else 'spint *c'}) {{")
        print(f"    spint t0 = 0, t, m, k = {c}, mask=0x{2**rgap-1:x};")
        print(f"    spint t1 = 0;")
        print("")
        r = "r" if inplace == False else "c"
        for i in range(0, nlimbs):
            m_shifts = f"c[{i + nlimbs}]" if lgap == 0 else f"(c[{i+nlimbs}] << {lgap}) + (c[{i+nlimbs-1}] >> {rgap})"
            print(f"    t = c[{i}]; m = {m_shifts};")
            if lgap > 0 and i == nlimbs - 1:
                print(f"    t &= mask;")
            print(f"    UMAAL(t, t0, m, k);")
            if lgap > 0 and i == nlimbs - 1:
                print(f"    t0 = (t0 << {lgap}) + (t >> {rgap});")
                print(f"    t &= mask;")
            print(f"    {r}[{i}] = t;")
        print(f"    t0 *= k;")
        print("")
        print(f"    UMAAL({r}[0], t1, 1, t0);")
        for i in range(1, nlimbs - 1):
            print(f"    UMAAL({r}[{i}], t1, 0, 0);")
        if lgap > 0:
            print(f"    UMAAL({r}[{nlimbs-1}], t1, 0, 0);")
            print(f"    t1 = {r}[{nlimbs-1}] >> {rgap};")
            print(f"    {r}[{nlimbs-1}] &= mask;")
        else:
            print(f"    UMAAL({r}[{nlimbs-1}], t1, 0, 0);")
        print(f"    t1 *= k;")
        print(f"    {r}[0] += t1;")
        print("}\n")


    # generates efficient reduction code for pseudo-Mersenne primes of the form 2**n-c
    # calls general PMP reduction code if prime does not allow more efficient reduction
    # inplace indicates if reduction should be made inplace
    # Can be divided into three algorithms:
    # * if n%32==0, perform traditional reduction using inline assembly where possible, similar to PM512
    # * if 0 < n%32 <= 16 and c.bit_length() + 32-n%32 <= 32, perform very efficient reduction, similar to PM266
    # * if 16 < n%32 < 32 and c.bit_length() + 32-n%32 <= n%32, perform very efficient reduction, similar to C25519
    # * else, use traditional reduction from gen_pmp_red_code_C
    def gen_modred_pmp_full_lastlimb_code(self, p=None, name=None, realn=None, realc=None, inplace=None):
        p = p or self.prime
        name = name or p.name
        n = realn or p.realn
        c = realc or p.realc
        inplace = inplace or p.modred_inplace
        nlimbs = (n + 31) // 32
        c_i_offset = 0
        nfullblocks = nlimbs // 4
        npartiallimbs = nlimbs - (nfullblocks * 4)

        # Reduction for cases like PM512 (n is multiple of 32)

        # Although this may not be a "small" function per se, it's performance is very critical, so we treat it as if
        # it were a small one
        print(f"{self.small_inline_attribute}static void modred_{name}_ct({'const spint *c, spint *r' if inplace==False else 'spint *c'}) {{")
        print(f"    spint t0, k;")
        print("    void *c_i_n;")
        print("")

        c_i = "r" if inplace == False else "c_i"
        upd = "!" if inplace == False else ""
        print("    asm volatile(")
        print(f'        "mov   %[k], #{c}\\n"')
        print(f'        "mov   %[t0], #0\\n"')
        print(f'        "add   %[c_i_n], %[c_i], #{4 * nlimbs}\\n"')
        # complete all possible full 4 regs blocks
        for i in range(0, 4 * nfullblocks, 4):
            print('        "ldmia %[c_i_n]!, {r2-r5}\\n"')
            print(f'        "ldm   %[c_i]{upd}, {{r6-r9}}\\n"')
            # multiply high*k + low
            print('        "umaal r6, %[t0], r2, %[k]\\n"')
            print('        "umaal r7, %[t0], r3, %[k]\\n"')
            print('        "umaal r8, %[t0], r4, %[k]\\n"')
            print('        "umaal r9, %[t0], r5, %[k]\\n"')
            if i < 4 * nfullblocks - 4 or npartiallimbs > 0:
                # there are more rounds, store current lowregs
                print(f'        "stmia %[{c_i}]!, {{r6-r9}}\\n"')
                c_i_offset += 16
        # complete last partial block
        last_block_size = npartiallimbs if npartiallimbs > 0 else 4
        last_reg = last_block_size + 5
        if npartiallimbs > 0:
            reg_str = "r2" if npartiallimbs == 1 else f"r2-r{last_reg-4}"
            print(f'        "ldmia %[c_i_n]!, {{{reg_str}}}\\n"')
            # load lower part of partial block
            reg_str = "r6" if npartiallimbs == 1 else f"r6-r{last_reg}"
            print(f'        "ldm   %[c_i]{upd}, {{{reg_str}}}\\n"')
            # multiply high*k + low
            for i in range(npartiallimbs):
                print(f'        "umaal r{i+6}, %[t0], r{i+2}, %[k]\\n"')

        # complete reduction with additions of c
        print(f'        "sub   %[{c_i}], %[{c_i}], #{c_i_offset}\\n"')
        c_i_offset = 0
        print('        "mul   %[t0], %[t0], %[k]\\n"')

        addblocks = nfullblocks - 1 if npartiallimbs == 0 else nfullblocks
        for i in range(0, 4 * addblocks, 4):
            print(f'        "ldm   %[{c_i}], {{r2-r5}}\\n"')
            if i == 0:
                print('        "adds  r2, r2, %[t0]\\n"')
            else:
                print('        "adcs  r2, r2, #0\\n"')
            print('        "adcs  r3, r3, #0\\n"')
            print('        "adcs  r4, r4, #0\\n"')
            print('        "adcs  r5, r5, #0\\n"')
            if nlimbs > 8:
                print(f'        "stm   %[{c_i}]!, {{r2-r5}}\\n"')
                c_i_offset += 16

        if nlimbs <= 4:
            print('        "adds  r6, r6, %[t0]\\n"')
        else:
            print('        "adcs  r6, r6, #0\\n"')
        for i in range(1, last_block_size):
            print(f'        "adcs  r{i+6}, r{i+6}, #0\\n"')
        flag_it = "cs"

        if nlimbs > 8:
            if npartiallimbs == 1:
                print(f'        "str   r6, [%[{c_i}]]\\n"')
            else:
                print(f'        "stm   %[{c_i}], {{r6-r{last_reg}}}\\n"')

        if nlimbs <= 4:
            print(f'        "it    {flag_it}\\n"')
            print(f'        "add{flag_it} r6, r6, %[k]\\n"')
            reg_str = f"r6" if npartiallimbs == 1 else f"r6-r{last_reg}"
            print(f'        "stm   %[c_i], {{{reg_str}}}\\n"')
        else:
            if nlimbs > 8:
                print(f'        "ldr   r2, [%[{c_i}], #-{c_i_offset}]\\n"')

            print(f'        "it    {flag_it}\\n"')
            print(f'        "add{flag_it} r2, r2, %[k]\\n"')

            if nlimbs <= 8:
                reg_str = "r2" if npartiallimbs == 1 else f"r2-r{last_reg}"
                print(f'        "stm   %[{c_i}], {{{reg_str}}}\\n"')
            else:
                print(f'        "str   r2, [%[{c_i}], #-{c_i_offset}]\\n"')

        need_r = ', [r] "+&r"(r)' if inplace == False else ""
        print(f'        : [t0] "=&r"(t0), [c_i] "+&r"(c), [c_i_n] "=&r"(c_i_n), [k] "=&r"(k){need_r}')
        print("        :")
        print('        : "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "cc", "memory"')
        print("    );")
        print("}\n")

    def gen_modred_pmp_smaller_lastlimb_code(self, p=None, name=None, realn=None, realc=None, inplace=None):
        p = p or self.prime
        name = name or p.name
        n = realn or p.realn
        c = realc or p.realc
        inplace = inplace or p.modred_inplace
        shr = n % 32
        shl = 32 - shr
        in_limbs = (n + 31) // 32
        # out_limbs = (2 * (n + 1) + 31) // 32
        
        # Verify bounds and stop code generation if verification fails
        verifier = Verifier(input_ub=(2**realn-realc-1)**2, output_ub=2*(2**realn-realc)-1)
        verifier.modred_pmp_smaller_lastlimb(n, c, shr, shl, in_limbs)
        if not verifier.validate():
            print("Could not verify that the output respects the required bounds!")
            print(f"\nOutput interval:\n{verifier.output}")
            print(f"\nRequired interval:\n{verifier.required}")
            sys.exit(1)

        # Although this may not be a "small" function per se, it's performance is very critical, so we treat it as if
        # it were a small one
        print(f"{self.small_inline_attribute}static void modred_{name}_ct(const spint *c, spint *r) {{")
        if n % 32 > 16:
            # Case 1: similar to M127, C25519 (empty space in last limb is smaller than 16 bits)
            print(f"    spint t, rH, cc = 0;")
            loop_range = in_limbs - 1
        else:
            # Case 2: similar to PM266, NIST521 (empty space in last limb is greater or equal to 16 bits)
            print(f"    spint t, rH, rT, cc = 0;")
            loop_range = in_limbs - 2

        print()
        print(f"    rH = c[{loop_range}];")
        print(f"    UMAAL(rH, cc, c[{loop_range + in_limbs}], {c} << {shl});")
        print()

        if n % 32 > 16:
            print(f"    cc = {c} * ((cc << {shl}) | (rH >> {shr}));")
            print(f"    rH &= 0x{((1 << shr) - 1):08x};")
        else:
            print(f"    rT = c[{in_limbs - 1}];")
            print(f"    UMAAL(rT, cc, c[{2 * in_limbs - 1}], {c} << {shl});")
            print(f"    cc = {c} * ((cc << {shl}) | (rT >> {shr}));")
            print(f"    rT &= 0x{((1 << shr) - 1):08x};")

        print()

        for i in range(loop_range):
            print(f"    t = c[{i}];")
            print(f"    UMAAL(t, cc, c[{in_limbs + i}], {c} << {shl});")
            print(f"    r[{i}] = t;")
            print()

        if n % 32 > 16:
            print(f"    r[{in_limbs - 1}] = rH + cc;")
        else:
            print(f"    UMAAL(rH, cc, 0, 0);")
            print(f"    r[{in_limbs - 2}] = rH;")
            print()
            print(f"    r[{in_limbs - 1}] = rT + cc;")
        print("}\n")


    # chooses appropriate method for modular reduction (only used in pmp)
    def gen_modred_code(self, p=None, name=None, inplace=None):
        p = p or self.prime
        name = name or p.name
        inplace = inplace or p.modred_inplace
        if p.reduction != "mont":
            n = p.realn
            c = p.realc
            shr = n % 32
            shl = 32 - shr
            # if prime allows efficient reduction send to proper function generator
            if shr == 0:
                # Bound verification does not work for this case yet
                self.gen_modred_pmp_full_lastlimb_code(p, name, n, c, inplace)
            elif (c.bit_length() + shl <= 32 and shr <= 16) or (shr > 16 and c.bit_length() + shl <= shr):
                self.gen_modred_pmp_smaller_lastlimb_code(p, name, n, c, inplace)
            else:
                self.gen_modred_pmp_standard_code(p, name, p.n, p.c, n, c, inplace)
        else:
            pass

    def modop_inline_options(self, op):
        # Although these may be large functions, they are performance-critical, so treat them as if they were
        # medium-sized
        maybe_inner = ""
        if op == "sqr" and (self.inline_policy == InlinePolicy.HANDSOFF or self.inline_policy == InlinePolicy.BALANCED_SIZE or self.inline_policy == InlinePolicy.BALANCED_SPEED):
            maybe_inner = "inner_"

        inline = self.medium_inline_attribute
        if maybe_inner == "inner_":
            inline = "ALWAYS_INLINE "

        return maybe_inner, inline

    def gen_modop_outer_function(self, op, name):
        if op == "mul":
            print(f"{self.medium_inline_attribute}static void modmul_{name}_ct(const spint *a, const spint *b, spint *res) {{")
            print(f"    inner_mod{op}_{name}_ct(a, b, res);")
            print(f"}}\n")
        elif op == "sqr":
            print(f"{self.medium_inline_attribute}static void modsqr_{name}_ct(const spint *a, spint *res) {{")
            print(f"    inner_mod{op}_{name}_ct(a, res);")
            print(f"}}\n")

    # generates modular multiplication, squaring or mli code for any prime with Montgomery reduction
    # * full is filled with 'c' for PM primes when the prime is 'full' of a sufficient size (i.e. it fills its last limb completely, and has more than 12 limbs)
    # * lastbit indicates whether the most significant bit on the last limb is set or not
    # * optsub indicates a strategy of minimizing temp variables, only works for small primes (8 limbs generally)
    # * optfsb indicates a strategy of minimizing temp variables for modfsb, only works for small primes (8 limbs generally)
    # while it supports mli for Solinas primes, please use gen_montmli_code when possible for these primes
    def gen_modop_mont_code(self, op, p=None, name=None, prime=None, nlimbs=None, optsub=None, full=None, lastbit=None, optfsb=None):
        p = p or self.prime
        name = name or p.name
        prime = prime or self.prime.prime
        n = nlimbs or p.nlimbs
        optsub = p.optsub if optsub is None else optsub
        full = p.full if full is None else full
        lastbit = p.lastbit if lastbit is None else lastbit
        optfsb = p.optfsb if optfsb is None else optfsb

        mu = pow(-prime, -1, 2 ** (32))
        gap = p.gap
        primeFactors = p.prime_factors(prime, nlimbs)

        p_plus_1 = prime + 1
        num_zeros = (p_plus_1 & -p_plus_1).bit_length() - 1
        zero_limbs = num_zeros // 32

        (maybe_inner, inline) = self.modop_inline_options(op)

        if op == "mul":
            print(f"{inline}static void {maybe_inner}modmul_{name}_ct(const spint *a, const spint *b, spint *res) {{")
        elif op == "sqr":
            print(f"{inline}static void {maybe_inner}modsqr_{name}_ct(const spint *a, spint *res) {{")
        else:
            sys.exit(1)

        if mu != 1:
            print(f"    const spint mu = {mu};")
        print(f"    spint A[{n*2}];")
        print("    spint ", end="")
        for i in range(n * 2 - 1):
            print(f"A{i}, ", end="")
        print(f"A{n*2 - 1};")
        if optsub == True and gap < 2 and lastbit == True and not full:
            for i in range(n):
                print(f"    const spint p{i} = {(prime // 2**(32*i)) % 2**32};")
        else:
            for i in range(zero_limbs, n):
                print(f"    const spint p{i} = {(prime // 2**(32*i)) % 2**32};")
        print(f"    spint q, t, t2 = 0;")
        if gap < 2 and lastbit == True and optfsb == False:
            print(f"    spint t3, t4;")
        # if lastbit == True and optsub == False:
        #    print(f"    spint t3, t4;")
        print("")

        if op == "mul":
            print(f"    mul_{name}_ct(a, b, A);")
        elif op == "sqr":
            print(f"    sqr_{name}_ct(a, A);")
        elif op == "mli":
            print(f"    mli_{name}_ct(a, b, A);")
        else:
            sys.exit(1)

        print("")

        for i in range(n + 1):
            print(f"    A{i} = A[{i}];")

        for i in range(n + 1, 2 * n):
            if op == "mli":
                print(f"    A{i} = 0;")
            else:
                print(f"    A{i} = A[{i}];")

        print("")

        for i in range(n):
            if mu != 1:
                print(f"    q = mu * A{i};")
            else:
                print(f"    q = A{i};")
            if i == 0 or zero_limbs + 1 < n:  # can't use t from previous round to propagate, must clear t
                print(f"    t = 0;")
            if zero_limbs > 0:
                print(f"    UMAAL(A{i + zero_limbs}, t, q, p{zero_limbs} + 1);")
            else:
                print(f"    UMAAL(A{i}, t, q, p0);")

            for j in range(zero_limbs + 1, n):
                print(f"    UMAAL(A{i+j}, t, q, p{j});")
            if zero_limbs + 1 < n:  # can't use t from previous round to propagate, must use t2
                print(f"    UMAAL(A{i+n}, t2, 1, t);")
            elif i == n - 1:  # can use only t but its the last value, must propagate t now
                print(f"    A{i+n} += t;")
            print("")

        if gap < 2:
            if full:
                print(f"    t = 0;")
                print(f"    UMAAL(A{n}, t, t2, {full});")
                print(f"    res[0] = A{n};")
                for i in range(n + 1, 2 * n):
                    print(f"    UMAAL(A{i}, t, 0, 0);")
                    print(f"    res[{i-n}] = A{i};")
            elif lastbit == False or optsub == False:
                for i in range(n):
                    print(f"    res[{i}] = A{i+n};")
            if lastbit == True and not full:
                if optsub == True:
                    for i in range(n):
                        print(f"    res[{i}] = A{i+n};")
                else:
                    if optfsb == True:
                        for i in range(n):
                            print(f"    spint subv{i} = {primeFactors[i]}*t2;")
                    else:
                        print(f"    spint subv[{n}] = {{{primeFactors[0]}*t2", end="")
                        for i in range(1, n):
                            print(f", {primeFactors[i]}*t2", end="")
                        print(f"}};")
                print(f"    asm volatile(")
                if optsub == True:
                    print(f'        "subs %[A{n}], %[A{n}], %[p0]\\n"')
                    for i in range(1, n):
                        print(f'        "sbcs %[A{n+i}], %[A{n+i}], %[p{i}]\\n"')
                    print(f'        "subs %[t2], %[t2], #1\\n"')

                    self.gen_asm_conditional_store("A", "res", int(n), 0, p, n)

                    print(f'        : [A{n}] "+&r" (A{n})', end="")
                    for i in range(1, n):
                        print(f', [A{n+i}] "+&r" (A{n+i})', end="")
                    print(f', [t2] "+&r" (t2)\n        : [res] "r" (res)', end="")
                    for i in range(n):
                        print(f', [p{i}] "rI" (p{i})', end="")
                    print(f'\n        : "cc", "memory");')
                else:
                    if optfsb == True:
                        print(f'        "ldr    %[t], [%[res], #0]\\n"')
                        print(f'        "subs   %[t], %[t], %[subv0]\\n"')
                        for i in range(1, n):
                            if i % 2 == 0:
                                rc, rp = "t", "t2"
                            else:
                                rc, rp = "t2", "t"
                            print(f'        "ldr    %[{rc}], [%[res], #{i * 4}]\\n"')
                            print(f'        "str    %[{rp}], [%[res], #{(i - 1) * 4}]\\n"')
                            print(f'        "sbcs   %[{rc}], %[{rc}], %[subv{i}]\\n"')
                        print(f'        "str    %[{rc}], [%[res], #{(n - 1) * 4}]\\n"')
                        print(f'        : [t] "+&r" (t), [t2] "+&r" (t2)')
                        print(f'        : [res] "r" (res)', end="")
                        for i in range(n):
                            print(f', [subv{i}] "r" (subv{i})', end="")
                        print(f'\n        : "cc", "memory");')
                    else:
                        print(f'        "ldrd %[t], %[t2], [%[res]]\\n"')
                        print(f'        "ldrd %[t3], %[t4], [%[subv]]\\n"')
                        print(f'        "subs %[t], %[t], %[t3]\\n"')
                        print(f'        "sbcs %[t2], %[t2], %[t4]\\n"')
                        print(f'        "strd %[t], %[t2], [%[res]]\\n"')
                        for i in range(2, n - 1, 2):
                            print(f'        "ldrd %[t], %[t2], [%[res], #{i*4}]\\n"')
                            print(f'        "ldrd %[t3], %[t4], [%[subv], #{i*4}]\\n"')
                            print(f'        "sbcs %[t], %[t], %[t3]\\n"')
                            print(f'        "sbcs %[t2], %[t2], %[t4]\\n"')
                            print(f'        "strd %[t], %[t2], [%[res], #{i*4}]\\n"')
                        if n % 2 == 1:
                            print(f'        "ldr %[t], [%[res], #{(n-1)*4}]\\n"')
                            print(f'        "ldr %[t3], [%[subv], #{(n-1)*4}]\\n"')
                            print(f'        "sbcs %[t], %[t], %[t3]\\n"')
                            print(f'        "str %[t], [%[res], #{(n-1)*4}]\\n"')
                        print(f'        : [t] "+&r" (t), [t2] "+&r" (t2), [t3] "=&r" (t3), [t4] "=&r" (t4)')
                        print(f'        : [res] "r" (res), [subv] "r" (subv)')
                        print(f'        : "cc", "memory");')
            print("")
            print(f"    modfsb_{name}_ct(res);")
        else:
            for i in range(n):
                print(f"    res[{i}] = A{i+n};")

        print("}\n")
        if maybe_inner == "inner_":
            self.gen_modop_outer_function(op, name)

    # generates calls for modmul and modsqr (used only for pseudo-mersenne primes)
    # inplace indicates whether modred is inplace or not
    def gen_modmul_modsqr_pmp_code(self, p=None, name=None, nlimbs=None, inplace=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        inplace = inplace or p.modred_inplace
        res = "res" if inplace == True else "z"
        z = "" if inplace == True else "z, "

        (maybe_inner, inline) = self.modop_inline_options("mul")

        print(f"{inline}static void {maybe_inner}modmul_{name}_ct(const spint *a, const spint *b, spint *res) {{")
        if inplace == False:
            print(f"    spint z[{nlimbs*2}];")
        print(f"    mul_{name}_ct(a, b, {res});")
        print(f"    modred_{name}_ct({z}res);")
        print("}\n")

        if maybe_inner == "inner_":
            self.gen_modop_outer_function("mul", name)

        (maybe_inner, inline) = self.modop_inline_options("sqr")

        print(f"{inline}static void {maybe_inner}modsqr_{name}_ct(const spint *a, spint *res) {{")
        if inplace == False:
            print(f"    spint z[{nlimbs*2}];")
        print(f"    sqr_{name}_ct(a, {res});")
        print(f"    modred_{name}_ct({z}res);")
        print("}\n")

        if maybe_inner == "inner_":
            self.gen_modop_outer_function("sqr", name)

    # Chooses which generator function to deploy for modmul and modsqr
    def gen_modmul_modsqr_code(self, p=None):
        p = p or self.prime
        if p.reduction == "mont":
            self.gen_modop_mont_code("mul", p)
            self.gen_modop_mont_code("sqr", p)
        else:
            self.gen_modmul_modsqr_pmp_code(p)

    # generates multiply by a 32bit value function, without reduction
    def gen_mli_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        print(f"ALWAYS_INLINE static void mli_{name}_ct(const spint *p, const spint q, spint *r) {{")
        blocks = nlimbs // 8
        first = nlimbs % 8 if nlimbs % 8 > 0 else 8
        print("    spint b, t0, t1, t2, t3, t4, t5, t6, t7, t8;")
        res = "r"
        print("    b = q - 1;")
        print("    t8 = 0;")

        for i in range(first):
            print(f"    t{i} = p[{i}];")
        for i in range(first):
            print(f"    UMAAL(t{i}, t8, t{i}, b);")
        blocks = blocks if nlimbs % 8 > 0 else blocks - 1
        addr_inc = first
        if blocks > 0:
            for i in range(first):
                print(f"    {res}[{i}] = t{i};")
            for i in range(blocks):
                for i in range(8):
                    print(f"    t{i} = p[{addr_inc+i}];")
                for i in range(8):
                    print(f"    UMAAL(t{i}, t8, t{i}, b);")
                for i in range(8):
                    print(f"    {res}[{addr_inc+i}] = t{i};")
                addr_inc += 8
        else:
            for i in range(nlimbs):
                print(f"    {res}[{i}] = t{i};")
        print(f"    {res}[{nlimbs}] = t8;")
        print("}\n")

    # generates multiply by a 32bit value function with Montgomery reduction, only used for Solinas primes!
    # montmli receives the lower coefficients of a solinas prime
    def gen_modmli_mont_solinas_code(self, p=None, montmli=None):
        p = p or self.prime
        montmli = montmli or p.montmli
        if not montmli:
            return
        realn = p.realn
        n = p.nlimbs
        name = p.name
        gap = realn % 32
        mask = hex(2**gap - 1)
        # Although this may be a large function, it is performance-critical, so treat it as if it were a medium one
        print(f"{self.medium_inline_attribute}static void modmli_{name}_ct(const spint *p, const spint q, spint *r) {{")
        print(f"    spint A[{n+1}];")
        print(f"    spint pq0", end="")
        for i in range(1, n):
            print(f", pq{i}", end="")
        print(f";")
        print(f"    mli_{name}_ct(p, q, A);")
        print(f"    spint t = 0, t2 = 0;")
        if gap:
            print(f"    spint sum = A[{n}] << {32-gap} | A[{n-1}] >> {gap};")
            print(f"    A[{n-1}] = A[{n-1}] & {mask};")
        else:
            print(f"    spint sum = A[{n}];")
        for i in range(n):
            print(f"    pq{i} = A[{i}];")
            print(f"    UMAAL(pq{i}, t, sum, {(montmli >> (i*32))%(2**32)});")
        if gap:
            print(f"    t = t << {32-gap} | pq{n-1} >> {gap};")
            print(f"    pq{n-1} = pq{n-1} & {mask};")
        for i in range(n):
            print(f"    UMAAL(pq{i}, t2, t, {(montmli >> (i*32))%(2**32)});")
        for i in range(n):
            print(f"    r[{i}] = pq{i};")
        print(f"}}\n")

    # generates multiply by a 32bit value function with PMP reduction
    def gen_modmli_pmp_code(self, p=None):
        p = p or self.prime
        name = p.name
        n = p.n
        c = p.c
        inplace = p.modred_inplace
        nlimbs = (n + 31) // 32
        lgap = p.gap
        need_shift = True if lgap > 0 else False

        # Although this may be a large function, it is performance-critical, so treat it as if it were a medium one
        print(f"{self.medium_inline_attribute}static void modmli_{name}_ct(const spint *p, const spint q, spint *r) {{")
        blocks = nlimbs // 8
        first = nlimbs % 8 if nlimbs % 8 > 0 else 8
        print("    spint t0, t1, t2, t3, t4, t5, t6, t7, t8, b;")
        res = "r"
        if need_shift == True:
            res = "tmp"
            print(f"    spint {res}[{nlimbs*2}] = {{0}};")
        print("    b = q - 1;")
        print("    t8 = 0;")

        for i in range(first):
            print(f"    t{i} = p[{i}];")
        for i in range(first):
            print(f"    UMAAL(t{i}, t8, t{i}, b);")
        if (inplace == False or need_shift == True) and blocks <= 1:
            for i in range(first):
                print(f"    {res}[{i}] = t{i};")
        blocks = blocks if nlimbs % 8 > 0 else blocks - 1
        addr_inc = first
        if blocks > 0:
            for i in range(first):
                print(f"    {res}[{i}] = t{i};")
            for i in range(blocks):
                for i in range(8):
                    print(f"    t{i} = p[{addr_inc+i}];")
                for i in range(8):
                    print(f"    UMAAL(t{i}, t8, t{i}, b);")
                for i in range(8):
                    print(f"    {res}[{addr_inc+i}] = t{i};")
                addr_inc += 8
            if need_shift == False:
                print("    b = 0;")
                print(f"    spint c = {c};")
                print(f"    UMAAL({res}[0], b, t8, c);")
                print(f"    t8 = 0;")
        else:
            if need_shift == False:
                print("    b = 0;")
                print(f"    spint c = {c};")
                print(f"    UMAAL(t0, b, t8, c);")
                print(f"    t8 = 0;")
        if need_shift == False:
            print("    asm volatile(")
            print('        ".p2align 2\\n"')
            p_addr = 4
            r_addr = 4
            if blocks > 0:
                if first == 1:
                    print(f'        "ldr.w  %[t0], [%[r], #{p_addr}]\\n"')
                    p_addr += 4
                    print(f'        "adds.w %[t0], %[t0], %[b]\\n"')
                    print(f'        "str.w  %[t0], [%[r], #{r_addr}]\\n"')
                    r_addr += 4
                else:
                    for i in range(1, first):
                        print(f'        "ldr.w   %[t{i}], [%[r], #{p_addr}]\\n"')
                        p_addr += 4
                    print(f'        "adds.w %[t1], %[t1], %[b]\\n"')
            else:
                print(f'        "adds.w %[t1], %[t1], %[b]\\n"')
            for i in range(2, first):
                print(f"#ifdef __clang__")
                print(f'        "adcs   %[t{i}], %[t{i}], #0\\n"')
                print(f"#else")
                print(f'        "adcs.w %[t{i}], %[t{i}], #0\\n"')
                print(f"#endif")
            for i in range(1, first):
                print(f'        "str.w  %[t{i}], [%[r], #{r_addr}]\\n"')
                r_addr += 4
            for i in range(blocks):
                for i in range(8):
                    print(f'        "ldr.w  %[t{i}], [%[r], #{p_addr}]\\n"')
                    p_addr += 4
                for i in range(8):
                    print(f"#ifdef __clang__")
                    print(f'        "adcs   %[t{i}], %[t{i}], #0\\n"')
                    print(f"#else")
                    print(f'        "adcs.w %[t{i}], %[t{i}], #0\\n"')
                    print(f"#endif")
                for i in range(8):
                    print(f'        "str.w  %[t{i}], [%[r], #{r_addr}]\\n"')
                    r_addr += 4
            print(f"#ifdef __clang__")
            print(f'        "adcs   %[t8], %[t8], #0\\n"')
            print(f"#else")
            print(f'        "adcs.w %[t8], %[t8], #0\\n"')
            print(f"#endif")
            if blocks > 0:
                print('        : [t0] "=&r" (t0), [t1] "=&r" (t1), [t2] "=&r" (t2), [t3] "=&r" (t3),')
                print('          [t4] "=&r" (t4), [t5] "=&r" (t5), [t6] "=&r" (t6), [t7] "=&r" (t7), [t8] "+&r" (t8)')
            else:
                print('        : [t1] "+&r" (t1), [t2] "+&r" (t2), [t3] "+&r" (t3),')
                print('          [t4] "+&r" (t4), [t5] "+&r" (t5), [t6] "+&r" (t6), [t7] "+&r" (t7), [t8] "+&r" (t8)')
            print(f'        : [b] "r" (b), [r] "r"({res})')
            print('        : "cc", "memory");')
            print("    b = 0;")
            if blocks > 0:
                print(f"    UMAAL({res}[0], b, t8, c);")
            else:
                print(f"    UMAAL(t0, b, t8, c);")
                print(f"    {res}[0] = t0;")
        else:
            print(f"    {res}[{addr_inc}] = t8;")
            if inplace == False:
                print(f"    modred_{name}_ct({res}, r);")
            else:
                print(f"    modred_{name}_ct({res});")
                for i in range(nlimbs):
                    print(f"    r[{i}] = {res}[{i}];")
        print("}\n")

    def gen_modmli_generic_code(self, p=None):
        p = p or self.prime
        name = p.name
        n = p.n
        nlimbs = (n + 31) // 32

        # Although this may be a large function, it is performance-critical, so treat it as if it were a medium one
        print(f"{self.medium_inline_attribute}static void modmli_{name}_ct(const spint *p, const spint q, spint *r) {{")
        print(f"    spint t[{nlimbs}];")
        print(f"    modint_{name}_ct(q, t);")
        print(f"    modmul_{name}_ct(p, t, r);")
        print(f"}}\n")

    def gen_modmli_code(self, p=None):
        p = p or self.prime
        if p.reduction != "mont":
            self.gen_modmli_pmp_code(p)
        elif p.montmli:
            self.gen_modmli_mont_solinas_code(p)
        else:
            self.gen_modmli_generic_code(p)

    # Convert a big number to Montgomery format, for PMP only copies the number
    def gen_nres_code(self, p=None, name=None, prime=None, n=None, reduction=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        prime = prime or p.prime
        n = n or p.n
        reduction = reduction or p.reduction
        gap = p.gap
        print(f"{self.small_inline_attribute}static void nres_{name}_ct(const spint *a, spint *b) {{")
        if reduction == "mont":
            r = 2 ** (nlimbs * 32)
            nres = (r * r) % prime
            nres_factors = []
            for i in range(nlimbs):
                nres_factors.append((nres >> 32 * i) % (2**32))
            print(f"    spint nresfactor[] = {{{nres_factors[0]}", end="")
            for i in range(1, nlimbs):
                print(f", {nres_factors[i]}", end="")
            print(f"}};")
            print(f"    modmul_{name}_ct(a, nresfactor, b);")
        else:
            for i in range(nlimbs):
                print(f"    b[{i}] = a[{i}];")
        print(f"}}\n")

    # Convert back from internal format, result < p for Montgomery primes, performs final conditional subtraction for PMP
    def gen_redc_code(self, p=None, name=None, prime=None, n=None, reduction=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        prime = prime or p.prime
        n = n or p.n
        reduction = reduction or p.reduction
        print(f"{self.small_inline_attribute}static void redc_{name}_ct(const spint *a, spint *b) {{")
        if reduction == "mont":
            gap = p.gap
            print(f"    spint rinv[] = {{1", end="")
            for i in range(1, nlimbs):
                print(f", 0", end="")
            print(f"}};")
            print(f"    modmul_{name}_ct(a, rinv, b);")
            if gap >= 2:
                print(f"    modfsb_{name}_ct(b);")
        else:
            gap = n - prime.bit_length()
            for i in range(nlimbs):
                print(f"    b[{i}] = a[{i}];")
            for i in range(2**gap):
                print(f"    modfsb_{name}_ct(b);")
        print(f"}}\n")

    # Conditional constant time move
    def gen_modcmv_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        print(f"{self.medium_inline_attribute}static void modcmv_{name}_ct(int d, const spint *a, volatile spint *b) {{")
        print(f"    spint c0, c1, s, t, aux;")
        print(f"    spint r = 0x5aa5a55a;")
        print(f"    c0 = (~d) & (r + 1);")
        print(f"    c1 = d + r;")
        print(f"    for (int i = 0; i < {nlimbs}; i++) {{")
        print(f"        s = a[i];")
        print(f"        t = b[i];")
        print(f"        b[i] = aux = c0 * t + c1 * s;")
        print(f"        b[i] = aux - r * (t + s);")
        print(f"    }}")
        print(f"}}\n")

    # Conditional constant time swap
    def gen_modcsw_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        print(f"{self.medium_inline_attribute}static void modcsw_{name}_ct(int d, volatile spint *a, volatile spint *b) {{")
        print(f"    spint c0, c1, s, t, w, aux;")
        print(f"    spint r = 0x5aa5a55a;")
        print(f"    c0 = (~d) & (r + 1);")
        print(f"    c1 = d + r;")
        print(f"    for (int i = 0; i < {nlimbs}; i++) {{")
        print(f"        s = a[i];")
        print(f"        t = b[i];")
        print(f"        w = r * (t + s);")
        print(f"        b[i] = aux = c0 * t + c1 * s;")
        print(f"        b[i] = aux - w;")
        print(f"        a[i] = aux = c0 * s + c1 * t;")
        print(f"        a[i] = aux - w;")
        print(f"    }}")
        print(f"}}\n")

    # generates efficient modular addition code for PM primes
    def gen_modadd_pmp_code(self, p=None, name=None, nlimbs=None, realc=None, realn=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        c = realc or p.realc
        realn = realn or p.realn
        gap = realn % 32
        mask2 = hex(2**gap - 1)
        inline = self.medium_inline_attribute
        if self.inline_policy == InlinePolicy.HANDSOFF:
            inline = "inline "
        # Although this may be a large function, it is performance-critical, so treat it as if it were a medium one
        print(f"{inline}static void modadd_{name}_ct(const spint *a, const spint *b, spint *res) {{")
        if gap == 0:
            print(f"   spint t2 = 0;")
            print(f"    spint a0", end="")
            for i in range(1, nlimbs):
                print(f", a{i}", end="")
            print(";")
            print(f"    spint b0", end="")
            for i in range(1, nlimbs):
                print(f", b{i}", end="")
            print(";")
            print(f"    spint t = 0;")
            for i in range(nlimbs):
                print(f"    a{i} = a[{i}];")
                print(f"    b{i} = b[{i}];")
                print(f"    UMAAL(a{i}, t, 1, b{i});")
            print(f"    UMAAL(a0, t2, t, {c});")
            for i in range(1, nlimbs):
                print(f"    UMAAL(a{i}, t2, 0, 0);")
                print(f"    res[{i}] = a{i};")
            print(f"    a0 += {c} * t2;")
            print(f"    res[0] = a0;")
        else:
            print(f"    spint t = 0;")
            print(f"    spint a0", end="")
            for i in range(1, nlimbs):
                print(f", a{i}", end="")
            print(";")
            print(f"    spint b0", end="")
            for i in range(1, nlimbs):
                print(f", b{i}", end="")
            print(";")
            print(f"    a{nlimbs-1} = a[{nlimbs-1}];")
            print(f"    b{nlimbs-1} = b[{nlimbs-1}];")
            print(f"    UMAAL(a{nlimbs-1}, t, 1, b{nlimbs-1});")
            print(f"    t = {c} * ((a{nlimbs-1} >> {gap}) + (t << {32-gap}));")
            print(f"    a{nlimbs-1} = a{nlimbs-1} & {mask2};")

            for i in range(0, nlimbs - 1):
                print(f"    a{i} = a[{i}];")
                print(f"    b{i} = b[{i}];")
                print(f"    UMAAL(a{i}, t, 1, b{i});")
                print(f"    res[{i}] = a{i};")
            print(f"    UMAAL(a{nlimbs-1}, t, 0, 0);")
            print(f"    res[{nlimbs-1}] = a{nlimbs-1};")
        print("}\n")

    # generates modular addition code for any prime
    # * lastbit indicates whether the most significant bit on the last limb is set or not
    # * optsub indicates a strategy of minimizing temp variables, only works for small primes (8 limbs generally)
    def gen_modadd_mont_large_code(self, p=None, name=None, prime=None, nlimbs=None, lastbit=None):
        p = p or self.prime
        name = name or p.name
        prime = prime or p.prime
        n = nlimbs or p.nlimbs
        lastbit = p.lastbit if lastbit is None else lastbit
        gap = p.gap
        if gap >= 2:
            primeFactors = p.prime_factors(2 * prime, nlimbs)
        else:
            primeFactors = p.prime_factors(prime, nlimbs)
        inline = self.medium_inline_attribute
        if self.inline_policy == InlinePolicy.HANDSOFF:
            inline = "inline "
        # Although this may be a large function, it is performance-critical, so treat it as if it were a medium one
        print(f"{inline}static void modadd_{name}_ct(const spint *a, const spint *b, spint *res) {{")
        print(f"    const spint p[{n}] = {{{primeFactors[0]}", end="")
        for i in range(1, n):
            print(f", {primeFactors[i]}", end="")
        print(f"}};")
        print(f"    spint tmpres[{n}];")
        print(f"    spint t = 0, pp, tt, aa, bb;")
        print(f"")
        print(f"    asm volatile(")
        print(f'        "ldr    %[aa], [%[a]]\\n"')
        print(f'        "ldr    %[bb], [%[b]]\\n"')
        print(f'        "ldr    %[pp], [%[p]]\\n"')
        print(f'        "umaal  %[aa], %[t], %[one], %[bb]\\n"')
        print(f'        "str    %[aa], [%[res]]\\n"')
        print(f'        "subs   %[tt], %[aa], %[pp]\\n"')

        for i in range(1, n):
            print(f'        "ldr    %[aa], [%[a], #{4 * i}]\\n"')
            print(f'        "ldr    %[bb], [%[b], #{4 * i}]\\n"')
            print(f'        "ldr    %[pp], [%[p], #{4 * i}]\\n"')
            print(f'        "str    %[tt], [%[tmpres], #{4 * (i - 1)}]\\n"')
            print(f'        "umaal  %[aa], %[t], %[one], %[bb]\\n"')
            print(f'        "str    %[aa], [%[res], #{4 * i}]\\n"')
            print(f'        "sbcs   %[tt], %[aa], %[pp]\\n"')

        print(f'        "str    %[tt], [%[tmpres], #{4 * (n - 1)}]\\n"')

        if lastbit:
            print(f'        "adcs  %[t],  %[t], %[t]\\n"')

        self.gen_asm_conditional_loadstore(["t", "tt"], "tmpres", "res", 0, 0, p, n, "ne" if lastbit else "cs")

        print(f'        : [t] "+&r" (t), [tt] "=&r" (tt), [aa] "=&r" (aa), [bb] "=&r" (bb), [pp] "=&r" (pp)')
        print(f'        : [res] "r" (res), [tmpres] "r" (tmpres), [a] "r" (a), [b] "r" (b), [p] "r" (p), [one] "r" (1)')
        print(f'        : "cc", "memory");')
        print(f"}}\n")

    # generates modular addition code for any prime
    # * lastbit indicates whether the most significant bit on the last limb is set or not
    # * optsub indicates a strategy of minimizing temp variables, only works for small primes (8 limbs generally)
    def gen_modadd_mont_small_code(self, p=None, name=None, prime=None, nlimbs=None, lastbit=None):
        p = p or self.prime
        name = name or p.name
        prime = prime or p.prime
        n = nlimbs or p.nlimbs
        lastbit = p.lastbit if lastbit is None else lastbit
        gap = p.gap
        if gap >= 2:
            primeFactors = p.prime_factors(2 * prime, nlimbs)
        else:
            primeFactors = p.prime_factors(prime, nlimbs)
        inline = self.medium_inline_attribute
        if self.inline_policy == InlinePolicy.HANDSOFF:
            inline = "inline "
        print(f"{inline}static void modadd_{name}_ct(const spint *a, const spint *b, spint *res) {{")
        print(f"    spint a0", end="")
        for i in range(1, n):
            print(f", a{i}", end="")
        print(";")
        print(f"    spint b0", end="")
        for i in range(1, n):
            print(f", b{i}", end="")
        print(";")
        print(f"    spint t = 0;")
        print(f"    const spint p0 = {primeFactors[0]};")
        for i in range(1, n):
            print(f"    const spint p{i} = {primeFactors[i]};")
        # regular addition without reduction
        for i in range(n):
            print(f"    a{i} = a[{i}];")
            print(f"    b{i} = b[{i}];")
            print(f"    UMAAL(a{i}, t, 1, b{i});")
            print(f"    res[{i}] = a{i};")
        # conditional subtraction for maitaining res insisde prime range
        print(f"    asm volatile(")
        print(f'        "subs %[a0], %[a0], %[p0]\\n"')
        for i in range(1, n):
            print(f'        "sbcs %[a{i}], %[a{i}], %[p{i}]\\n"')

        self.gen_asm_conditional_store("a", "res", 0, 0, p, n)

        print(f'        : [a0] "+&r" (a0)', end="")
        for i in range(1, n):
            print(f', [a{i}] "+&r" (a{i})', end="")
        print(f'\n        : [res] "r" (res)', end="")
        for i in range(n):
            print(f', [p{i}] "rI" (p{i})', end="")
        print(f'\n        : "cc", "memory");')
        if lastbit:
            for i in range(n):
                print(f"    res[{i}] = a{i}*t - res[{i}]*(t-1);")
        print(f"}}\n")

    # generates modular addition code
    def gen_modadd_code(self, p=None, reduction=None, optsub=None):
        p = p or self.prime
        reduction = reduction or p.reduction
        optsub = p.optsub if optsub is None else optsub
        if reduction == "mont":
            if optsub:
                self.gen_modadd_mont_small_code(p)
            else:
                self.gen_modadd_mont_large_code(p)
        else:
            self.gen_modadd_pmp_code(p)

    # generates modular subtraction code for any small prime
    # * uses a strategy of minimizing temp variables, only works for small primes (max 8 limbs generally)
    def gen_modsub_small_code(self, p=None, name=None, prime=None, n=None, c=None, realn=None, nlimbs=None, reduction=None):
        p = p or self.prime
        name = name or p.name
        prime = prime or p.prime
        nlimbs = nlimbs or p.nlimbs
        n = n or p.n
        c = c or p.c
        realn = realn or p.realn
        reduction = reduction or p.reduction
        gap = p.gap
        if reduction != "mont" and n != realn:
            prime = 2**n - c
        if reduction == "mont" and gap >= 2:
            primeFactors = p.prime_factors(2 * prime, nlimbs)
        else:
            primeFactors = p.prime_factors(prime, nlimbs)
        inline = self.medium_inline_attribute
        if self.inline_policy == InlinePolicy.HANDSOFF:
            inline = "inline "
        print(f"{inline}static void modsub_{name}_ct(const spint *a, const spint *b, spint *res) {{")
        print(f"    spint a0 = a[0]", end="")
        for i in range(1, nlimbs):
            print(f", a{i} = a[{i}]", end="")
        print(";")
        print(f"    spint t, t1, t2;")
        for i in range(nlimbs):
            print(f"    const spint p{i} = {primeFactors[i]};")
        print(f"    asm volatile(")
        print(f'        "ldrd %[t1], %[t2], [%[b]]\\n"')
        print(f'        "subs %[a0], %[a0], %[t1]\\n"')
        print(f'        "sbcs %[a1], %[a1], %[t2]\\n"')
        for i in range(2, nlimbs - 1, 2):
            print(f'        "ldrd %[t1], %[t2], [%[b], #{4*i}]\\n"')
            print(f'        "sbcs %[a{i}], %[a{i}], %[t1]\\n"')
            print(f'        "sbcs %[a{i+1}], %[a{i+1}], %[t2]\\n"')
        if nlimbs % 2 == 1:
            print(f'        "ldr %[t1], [%[b], #{4*(nlimbs-1)}]\\n"')
            print(f'        "sbcs %[a{nlimbs-1}], %[a{nlimbs-1}], %[t1]\\n"')
        print(f'        "sbcs  %[t], %[t1], %[t1]\\n"')
        print(f'        : [a0] "+&r" (a0)', end="")
        for i in range(1, nlimbs):
            print(f', [a{i}] "+&r" (a{i})', end="")
        print(f', [t] "=&r" (t), [t1] "=&r" (t1), [t2] "=&r" (t2)')
        print(f'        : [b] "r" (b)')
        print('        : "cc", "memory");')
        print(f"    t = -t;")
        print(f"    t2 = 0;")
        for i in range(nlimbs):
            print(f"    UMAAL(a{i}, t2, t, p{i});")
        for i in range(nlimbs):
            print(f"    res[{i}] = a{i};")
        print(f"}}\n")

    # generates modular subtraction code for any prime
    # * uses a strategy for larger primes (more than 8 limbs generally)
    def gen_modsub_large_code(self, p=None, name=None, prime=None, n=None, c=None, realn=None, nlimbs=None, reduction=None):
        p = p or self.prime
        name = name or p.name
        prime = prime or p.prime
        nlimbs = nlimbs or p.nlimbs
        n = n or p.n
        c = c or p.c
        realn = realn or p.realn
        reduction = reduction or p.reduction
        gap = p.gap
        if reduction != "mont" and n != realn:
            prime = 2**n - c
        if reduction == "mont" and gap >= 2:
            primeFactors = p.prime_factors(2 * prime, nlimbs)
        else:
            primeFactors = p.prime_factors(prime, nlimbs)
        inline = self.medium_inline_attribute
        if self.inline_policy == InlinePolicy.HANDSOFF:
            inline = "inline "
        # Although this may be a large function, it is performance-critical, so treat it as if it were a medium one
        print(f"{inline}static void modsub_{name}_ct(const spint *a, const spint *b, spint *res) {{")
        print(f"    spint ae, ao;")
        print(f"    spint t, t1, t2;")
        print(f"    spint t3, t4;")
        for i in range(nlimbs):
            print(f"    const spint p{i} = {primeFactors[i]};")
        print(f"    asm volatile(")
        print(f'        "ldr    %[t3], [%[a], #0]\\n"')
        print(f'        "ldr    %[t4], [%[b], #0]\\n"')
        print(f'        "subs   %[t3], %[t3], %[t4]\\n"')
        for i in range(1, nlimbs):
            if i % 2 == 0:
                rc, rp = "t3", "t1"
            else:
                rc, rp = "t1", "t3"
            print(f'        "ldr    %[{rc}], [%[a], #{i * 4}]\\n"')
            print(f'        "ldr    %[t4], [%[b], #{i * 4}]\\n"')
            print(f'        "str    %[{rp}], [%[res], #{(i - 1) * 4}]\\n"')
            print(f'        "sbcs   %[{rc}], %[{rc}], %[t4]\\n"')
        print(f'        "str    %[{rc}], [%[res], #{(nlimbs - 1) * 4}]\\n"')
        print(f'        "sbcs    %[t], %[t3], %[t3]\\n"')
        print(f'        : [t] "=&r" (t), [t1] "=&r" (t1), [t2] "=&r" (t2), [t3] "=&r" (t3), [t4] "=&r" (t4)')
        print(f'        : [b] "r" (b), [a] "r" (a), [res] "r" (res)')
        print(f'        : "cc", "memory");')
        print(f"    t = -t | ({rc} > p{nlimbs-1});")
        print(f"    t2 = 0;")
        print(f"    ae = res[0];")
        print(f"    UMAAL(ae, t2, t, p0);")
        for i in range(1, nlimbs):
            if i % 2 == 0:
                rc, rp = "ae", "ao"
            else:
                rc, rp = "ao", "ae"
            print(f"    {rc} = res[{i}];")
            print(f"    res[{i - 1}] = {rp};")
            print(f"    UMAAL({rc}, t2, t, p{i});")
        print(f"    res[{nlimbs - 1}] = {rc};")
        print(f"}}\n")

    # generates appropriate code for modsub depending or small or large prime determined by optsub
    # * optsub indicates a strategy of minimizing temp variables, only works for small primes (8 limbs generally)
    def gen_modsub_code(self, p=None, optsub=None):
        p = p or self.prime
        optsub = p.optsub if optsub is None else optsub
        if optsub:
            self.gen_modsub_small_code(p)
        else:
            self.gen_modsub_large_code(p)

    # Modular negation, result < 2p
    def gen_modneg_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        print(f"{self.medium_inline_attribute}static void modneg_{name}_ct(const spint *a, spint *r) {{")
        print(f"    spint zero[{nlimbs}] = {{0}};")
        print(f"    modsub_{name}_ct(zero, a, r);")
        print(f"}}\n")

    # shift left by n bits
    def gen_modshl_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        inline = self.inline_size_limbs(nlimbs)
        print(f"{inline}static void modshl_{name}_ct(int n, spint *a) {{")
        if self.inline_policy != InlinePolicy.SIZE:
            print(f"#pragma GCC unroll {nlimbs - 1}")
        print(f"    for (int i = {nlimbs - 1}; i > 0; i--) {{")
        print(f"        a[i] = (a[i] << n) + (a[i - 1] >> (32 - n));")
        print(f"    }}")
        print(f"    a[0] = (a[0] << n);")
        print(f"}}\n")

    # shift right by n bits
    def gen_modshr_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        inline = self.inline_size_limbs(nlimbs)
        print(f"// Only works for n <= 31")
        print(f"{inline}static spint modshr_{name}_ct(int n, spint *a) {{")
        print(f"    spint r = a[0] & ((1 << n) - 1);")
        if self.inline_policy != InlinePolicy.SIZE:
            print(f"#pragma GCC unroll {nlimbs - 1}")
        print(f"    for (int i = 0; i < {nlimbs - 1}; i++) {{")
        print(f"        a[i] = (a[i] >> n) | (a[i + 1] << (32 - n));")
        print(f"    }}")
        print(f"    a[{nlimbs-1}] = a[{nlimbs-1}] >> n;")
        print(f"    return r;")
        print(f"}}\n")

    # Copy a big number
    def gen_modcpy_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        print(f"{self.medium_inline_attribute}static void modcpy_{name}_ct(const spint *a, spint *b) {{")
        if self.inline_policy != InlinePolicy.SIZE:
            print(f"#pragma GCC unroll {nlimbs}")
        print(f"    for (int i = 0; i < {nlimbs}; i++) {{")
        print(f"        b[i] = a[i];")
        print(f"    }}")
        print(f"}}\n")

    # Test for equal to zero
    def gen_modis0_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        print(f"{self.small_inline_attribute}static int modis0_{name}_ct(const spint *a) {{")
        print(f"    spint c[{nlimbs}] = {{0}};")
        print(f"    spint d = 0;")
        print(f"    modcpy_{name}_ct(a, c);")
        print(f"    modfsb_{name}_ct(c);")
        if self.inline_policy == InlinePolicy.SIZE:
            print(f"#pragma GCC unroll 1")
        print(f"    for (int i = 0; i < {nlimbs}; i++) {{")
        print(f"        d |= c[i];")
        print(f"    }}")
        print(f"    return 1 - ((d | -d) >> 31);")
        print(f"}}\n")

    # Test for equal to unity
    def gen_modis1_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        print(f"{self.small_inline_attribute}static int modis1_{name}_ct(const spint *a) {{")
        print(f"    spint c[{nlimbs}] = {{0}};")
        print(f"    spint d = 0;")
        print(f"    redc_{name}_ct(a, c);")
        print(f"    c[0] = c[0] - 1;")
        if self.inline_policy == InlinePolicy.SIZE:
            print(f"#pragma GCC unroll 1")
        print(f"    for (int i = 0; i < {nlimbs}; i++) {{")
        print(f"        d |= c[i];")
        print(f"    }}")
        print(f"    return 1 - ((d | -d) >> 31);")
        print(f"}}\n")

    # Test for equality, return 0 if different, 1 if equal
    def gen_modcmp_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        print(f"{self.small_inline_attribute}static int modcmp_{name}_ct(const spint *a, const spint *b) {{")
        print(f"    spint c[{nlimbs}], d[{nlimbs}];")
        print(f"    int neq = 0;")
        print(f"    redc_{name}_ct(a, c);")
        print(f"    redc_{name}_ct(b, d);")
        if self.inline_policy == InlinePolicy.SIZE:
            print(f"#pragma GCC unroll 1")
        print(f"    for (int i = 0; i < {nlimbs}; i++) {{")
        print(f"        neq |= c[i] ^ d[i];")
        print(f"    }}")
        print(f"    neq = (neq | -neq) >> 31;")
        print(f"    return 1 - (neq & 1);")
        print(f"}}\n")

    # Return the sign of an integer
    def gen_modsign_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        print(f"{self.small_inline_attribute}static int modsign_{name}_ct(const spint *a) {{")
        print(f"    spint c[{nlimbs}];")
        print(f"    redc_{name}_ct(a, c);")
        print(f"    return c[0] % 2;")
        print(f"}}\n")

    # performs n squarings
    def gen_modnsqr_code(self, p=None, name=None):
        p = p or self.prime
        name = name or p.name
        (maybe_inner, _) = self.modop_inline_options("sqr")
        if self.inline_policy == InlinePolicy.SIZE:
            inline = "ALWAYS_INLINE "
        elif self.inline_policy == InlinePolicy.BALANCED_SIZE or self.inline_policy == InlinePolicy.HANDSOFF:
            inline = "NOINLINE "
        elif self.inline_policy == InlinePolicy.BALANCED_SPEED:
            inline = ""
        elif self.inline_policy == InlinePolicy.SPEED:
            inline = "inline "
        print(f"{inline}static void modnsqr_{name}_ct(spint *a, int n) {{")
        if self.inline_policy == InlinePolicy.SIZE or self.inline_policy == InlinePolicy.BALANCED_SIZE:
            print(f"#pragma GCC unroll 1")
        print(f"    for (int i = 0; i < n; i++) {{")
        print(f"        {maybe_inner}modsqr_{name}_ct(a, a);")
        print(f"    }}")
        print(f"}}\n")

    # Calculate progenitor, for subsequent use for modular inverses and square roots, adapted from modarith
    # uses https://github.com/mmcloughlin/addchain to create addition chain
    def gen_modpro_code(self, p=None, name=None, prime=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        prime = prime or p.prime
        nlimbs = nlimbs or p.nlimbs
        decor = f"_{name}_ct"
        pm1d2, roi, pe = p.inv_values(prime, nlimbs)

        cline = f'addchain search "{hex(pe)}" > inv.acc'
        subprocess.call(cline, shell=True, stderr=subprocess.DEVNULL)
        subprocess.call("addchain gen inv.acc > ac.txt", shell=True)
        subprocess.call("rm inv.acc", shell=True)

        f = open("ac.txt")
        lines = f.readlines()
        info = lines[0].split()
        ntmps = len(info) - 1
        str = f"// Calculate progenitor\n"
        str += f"NOINLINE static void modpro{decor}(const spint *w, spint *z) {{\n"
        str += f"    spint x[{nlimbs}];\n"
        for i in range(0, ntmps):
            str += f"    spint t{i}[{nlimbs}];\n"
        str += f"    modcpy{decor}(w, x);\n"
        for i in range(1, len(lines)):
            info = lines[i].split()
            if info[0] == "double":
                str += f"    modsqr{decor}({info[2]}, {info[1]});\n"
            if info[0] == "add":
                str += f"    modmul{decor}({info[2]}, {info[3]}, {info[1]});\n"
            if info[0] == "shift":
                if info[1] != info[2]:
                    str += f"    modcpy{decor}({info[2]}, {info[1]});\n"
                str += f"    modnsqr{decor}({info[1]}, {int(info[3])});\n"
        str += f"}}\n"
        subprocess.call("rm ac.txt", shell=True)
        print(str)

    # Test for quadratic residue, adapted from modarith
    def gen_modqr_code(self, p=None, name=None, prime=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        prime = prime or p.prime
        decor = f"_{name}_ct"
        pm1d2, roi, pe = p.inv_values(prime, nlimbs)
        str = "// Test for quadratic residue, provide progenitor h if available, NULL if not\n"
        str += f"{self.medium_inline_attribute}static int modqr{decor}(const spint *h, const spint *x) {{\n"
        str += f"    spint r[{nlimbs}];\n"
        str += f"    if (h == NULL) {{\n"
        str += f"        modpro{decor}(x, r);\n"
        str += f"        modsqr{decor}(r, r);\n"
        str += f"    }}\n"
        str += f"    else {{\n"
        str += f"        modsqr{decor}(h, r);\n"
        str += f"    }}\n"
        str += f"    modmul{decor}(r, x, r);\n"
        if pm1d2 > 1:
            str += f"    modnsqr{decor}(r, {pm1d2 - 1});\n"
        str += f"    return modis1{decor}(r);\n"
        str += f"}}\n"
        print(str)

    # Modular square root, adapted from modarith
    def gen_modsqrt_code(self, p=None, name=None, prime=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        prime = prime or p.prime
        nlimbs = nlimbs or p.nlimbs
        pm1d2, roi, pe = p.inv_values(prime, nlimbs)
        decor = f"_{name}_ct"
        str = "// Modular square root, provide progenitor h if available, NULL if not\n"
        str += f"{self.medium_inline_attribute}static void modsqrt{decor}(const spint *x, const spint *h, spint *r) {{\n"
        if pm1d2 > 1:
            str += f"    spint t[{nlimbs}];\n"
            str += f"    spint b[{nlimbs}];\n"
            str += f"    spint v[{nlimbs}];\n"
            str += f"    spint z[{nlimbs}] = {{"
            for i in range(0, nlimbs - 1):
                str += hex(roi[i])
                str += f"u, "
            str += hex(roi[nlimbs - 1])
            str += f"u}};\n"
        str += f"    spint s[{nlimbs}];\n"
        str += f"    spint y[{nlimbs}];\n"
        str += f"    if (h == NULL) {{\n"
        str += f"        modpro{decor}(x, y);\n"
        str += f"    }}\n"
        str += f"    else {{\n"
        str += f"        modcpy{decor}(h, y);\n"
        str += f"    }}\n"
        str += f"    modmul{decor}(y, x, s);\n"
        if pm1d2 > 1:
            str += f"    modmul{decor}(s, y, t);\n"
            str += f"    nres{decor}(z, z);\n"
            str += f"    for (int k = {pm1d2}; k > 1; k--) {{\n"
            str += f"        modcpy{decor}(t, b);\n"
            str += f"        modnsqr{decor}(b, k-2);\n"
            str += f"        int d = 1 - modis1{decor}(b);\n"
            str += f"        modmul{decor}(s, z, v);\n"
            str += f"        (void)modcmv{decor}(d, v, s);\n"
            str += f"        modsqr{decor}(z, z);\n"
            str += f"        modmul{decor}(t, z, v);\n"
            str += f"        (void)modcmv{decor}(d, v, t);\n"
            str += f"    }}\n"
        str += f"    modcpy{decor}(s, r);\n"
        str += f"}}\n"
        print(str)
        return

    # Modular inversion, adapted from modarith
    def gen_modinv_code(self, p=None, name=None, prime=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        prime = prime or p.prime
        nlimbs = nlimbs or p.nlimbs
        decor = f"_{name}_ct"
        pm1d2, roi, pe = p.inv_values(prime, nlimbs)
        str = "// Calculate inverse, provide progenitor h if available\n"
        str += f"{self.medium_inline_attribute}static void modinv{decor}(const spint *x, const spint *h, spint *z) {{\n"
        str += f"    spint s[{nlimbs}];\n"
        str += f"    spint t[{nlimbs}];\n"
        str += f"    if (h == NULL) {{\n"
        str += f"        modpro{decor}(x, t);\n"
        str += f"    }}\n"
        str += f"    else {{\n"
        str += f"        modcpy{decor}(h, t);\n"
        str += f"    }}\n"
        str += f"    modcpy{decor}(x, s);\n"
        if pm1d2 > 1:
            str += f"    for (int i = 0; i < ({pm1d2 - 1}); i++) {{\n"
            str += f"        modsqr{decor}(s, s);\n"
            str += f"        modmul{decor}(s, x, s);\n"
            str += f"    }}\n"
        str += f"    modnsqr{decor}(t, {pm1d2 + 1});\n"
        str += f"    modmul{decor}(s, t, z);\n"
        str += f"}}\n"
        print(str)

    #  Set equal to zero
    def gen_modzer_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        print(f"{self.medium_inline_attribute}static void modzer_{name}_ct(spint *a) {{")
        if self.inline_policy != InlinePolicy.SIZE:
            print(f"#pragma GCC unroll {nlimbs}")
        print(f"    for (int i = 0; i < {nlimbs}; i++) {{")
        print(f"        a[i] = 0;")
        print(f"    }}")
        print(f"}}\n")

    # Set equal to unity
    def gen_modone_code(self, p=None, name=None, prime=None, reduction=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        prime = prime or p.prime
        reduction = reduction or p.reduction
        print(f"{self.medium_inline_attribute}static void modone_{name}_ct(spint *a) {{")
        if reduction == "mont":
            r = 2 ** (nlimbs * 32) % prime
            one_factors = []
            for i in range(nlimbs):
                one_factors.append((r >> 32 * i) % (2**32))
            for i in range(nlimbs):
                print(f"    a[{i}] = {one_factors[i]};")
        else:
            print(f"    a[0] = 1;")
            if self.inline_policy != InlinePolicy.SIZE:
                print(f"#pragma GCC unroll {nlimbs - 1}")
            print(f"    for (int i = 1; i < {nlimbs}; i++) {{")
            print(f"        a[i] = 0;")
            print(f"    }}")
        print(f"}}\n")

    # Convert an integer to internal format (Montgomery format or simple limb copy)
    def gen_modint_code(self, p=None, name=None, reduction=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        reduction = reduction or p.reduction
        print(f"{self.medium_inline_attribute}static void modint_{name}_ct(int x, spint *a) {{")
        print(f"    a[0] = (spint)x;")
        if self.inline_policy != InlinePolicy.SIZE:
            print(f"#pragma GCC unroll {nlimbs - 1}")
        print(f"    for (int i = 1; i < {nlimbs}; i++) {{")
        print(f"        a[i] = 0;")
        print(f"    }}")
        if reduction == "mont":
            print(f"    nres_{name}_ct(a, a);")
        print(f"}}\n")

    # Set equal to 2^r
    def gen_mod2r_code(self, p=None, name=None, reduction=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        reduction = reduction or p.reduction
        limit = nlimbs * 32
        if reduction != "mont" and not p.lastbit:
            limit = p.realn + 1
        print(f"{self.small_inline_attribute}static void mod2r_{name}_ct(unsigned int r, spint *a) {{")
        print(f"    unsigned int n = r >> 5;")
        print(f"    unsigned int m = r & 31;")
        print(f"    modzer_{name}_ct(a);")
        print(f"    if (r >= {limit}) {{")
        print(f"        return;")
        print(f"    }}")
        print(f"    a[n] = 1 << m;")
        print(f"    nres_{name}_ct(a, a);")
        print("}\n")

    # Import to internal format from byte array
    def gen_modimp_code(self, p=None, name=None, reduction=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        reduction = reduction or p.reduction
        print(f"{self.medium_inline_attribute}static void modimp_{name}_ct(const char *b, spint *a) {{")
        print(f"    const spint *b32 = (const spint *)b;")
        if self.inline_policy != InlinePolicy.SIZE:
            print(f"#pragma GCC unroll {nlimbs}")
        print(f"    for (int i = 0; i < {nlimbs}; i++) {{")
        print(f"        a[i] = __builtin_bswap32(b32[{nlimbs - 1} - i]);")
        print(f"    }}")
        if reduction == "mont":
            print(f"    nres_{name}_ct(a, a);")
        print(f"}}\n")

    # export from Montgomery format to byte array (for PMP does final conditional subtraction and copy into char array)
    def gen_modexp_code(self, p=None, name=None, nlimbs=None):
        p = p or self.prime
        name = name or p.name
        nlimbs = nlimbs or p.nlimbs
        print(f"// Code for export, not exponentiation")
        print(f"{self.medium_inline_attribute}static void modexp_{name}_ct(const spint *a, char *b) {{")
        print(f"    spint c[{nlimbs}], *b32 = (spint *)b;")
        print(f"    redc_{name}_ct(a, c);")
        if self.inline_policy != InlinePolicy.SIZE:
            print(f"#pragma GCC unroll {nlimbs}")
        print(f"    for (int i = 0; i < {nlimbs}; i++) {{")
        print(f"        b32[{nlimbs - 1} - i] = __builtin_bswap32(c[i]);")
        print(f"    }}")
        print(f"}}\n")

    def generate_all_code(self, p=None):
        p = p or self.prime
        self.gen_header(p)
        self.gen_modfsb_code(p)
        self.gen_mul_code(p)
        self.gen_sqr_code(p)
        self.gen_modred_code(p)
        self.gen_modmul_modsqr_code(p)
        self.gen_nres_code(p)
        self.gen_redc_code(p)
        self.gen_modcmv_code(p)
        self.gen_modcsw_code(p)
        self.gen_modadd_code(p)
        self.gen_modsub_code(p)
        self.gen_modneg_code(p)
        self.gen_modshl_code(p)
        self.gen_modshr_code(p)
        self.gen_modcpy_code(p)
        self.gen_modis0_code(p)
        self.gen_modis1_code(p)
        self.gen_modcmp_code(p)
        self.gen_modsign_code(p)
        self.gen_modnsqr_code(p)
        self.gen_modpro_code(p)
        self.gen_modqr_code(p)
        self.gen_modsqrt_code(p)
        self.gen_modinv_code(p)
        self.gen_modzer_code(p)
        self.gen_modone_code(p)
        self.gen_modint_code(p)
        self.gen_mod2r_code(p)
        if p.reduction == "mont" and p.montmli:
            self.gen_mli_code(p)
        self.gen_modmli_code(p)
        self.gen_modimp_code(p)
        self.gen_modexp_code(p)
        self.gen_footer(p)


def usage():
    print(
        """Usage: python m4generator.py <prime name or expression> <reduction>

<prime name>: a short name for the prime of interest, using valid C identifier characters; e.g. C.25519. Alternatively,
              an integer or expression can be used directly.

Valid values for <reduction>: pmp_asm, pmp_c, mont

Description of reduction types and their parameters:
    pmp_asm: reduction modulo pseudo-Mersenne primes, i.e. those of the form 2^n - c. Assumes n is a multiple of 32;
             otherwise (e.g. in the case of 2^255 - 19), partial reductions must be used, such as modulo 2^256 - 38.
             This version is implemented using a single inline assembly block, to work around a limitation in gcc on
             the number of operands in inline assembly, and is necessary e.g. for 512-bit primes.

    pmp_c: same as pmp_asm, except that reduction is implemented mostly in C, with inline assembly blocks only as
           needed (but, unfortunately, subject to the restriction mentioned above). Whether it performs better or
           worse than pmp_asm on primes that do no hit gcc's limitation is unclear, and should be confirmed by
           performance testing.

    mont: reduction using Montgomery multiplication.
"""
    )


if __name__ == "__main__":
    if len(sys.argv) < 3:
        usage()
        sys.exit(1)

    nam = sys.argv[1]
    red = sys.argv[2]
    reductions = ["pmp_asm", "pmp_c", "mont"]

    if red not in reductions:
        print("Invalid reduction.\n")
        usage()
        sys.exit(1)

    p = Prime(nam, red)
    if not p.prime:
        print("Invalid prime name\n")
        usage()
        sys.exit(1)

    g = CodeGenerator(p)
    g.generate_all_code()
