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
from m4prime import Prime

# impltype = None
# impltype_suffix = None
# inline_policy = "__attribute__((noinline))"


def usage():
    print(
        """Usage: python m4test.py <prime name or expression> <reduction> <implementation type>

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

Valid values for <implementation type>: codegen, custom
"""
    )


# adapted from modarith, returns gcd
def gcd(x, y):
    a = x
    b = y
    while b != 0:
        a, b = b, a % b
    return a


# adapted from modarith, returns inverse of a given prime p
def inverse(a, p):
    n = p
    x = a % n
    if x == 0:
        return x
    kn = n
    if x < 0:
        x += n
    if gcd(x, n) != 1:
        return 0
    a = 1
    la = 0
    while x > 1:
        q, r = divmod(n, x)
        t = la - a * q
        la = a
        a = t
        n = x
        x = r
    if a < 0:
        a += kn
    return a


class TestGenerator:

    def __init__(
        self, name=None, reduction=None, type="codegen", inline="", iterations=256
    ):
        self.impltype = type
        self.inline_policy = inline
        self.iterations = iterations
        if type == "codegen":
            self.impltype_suffix = ""
        else:
            self.impltype_suffix = f"_{type}"
        self.prime = Prime(name, reduction)
        if not self.prime:
            return
        self.default_test_functions()
        self.test_functions = {
            "mul": self.gen_mul_test(),
            "sqr": self.gen_sqr_test(),
            "modmul": self.gen_modmul_test(),
            "modsqr": self.gen_modsqr_test(),
            "modmli": self.gen_modmli_test(),
            "modadd": self.gen_modop_2inputs_test("modadd"),
            "modsub": self.gen_modop_2inputs_test("modsub"),
            "modsub_negate": self.gen_modsub_negate_test(),
            "modcpy": self.gen_modcpy_test(),
            "nres": self.gen_nres_test(),
            "redc": self.gen_redc_test(),
            "modneg": self.gen_modneg_test(),
            "modinv": self.gen_modinv_test(),
            "modfsb": self.gen_modfsb_test(),
            "modis1": self.gen_modis1_test(),
            "modis0": self.gen_modis0_test(),
            "modzer": self.gen_modzer_test(),
            "modone": self.gen_modone_test(),
            "modint": self.gen_modint_test(),
            "modcmv": self.gen_modcmv_test(),
            "modcsw": self.gen_modcsw_test(),
            "modsqrt": self.gen_modsqrt_test(),
            "modshr": self.gen_modshr_test(),
            "modshl": self.gen_modshl_test(),
            "mod2r": self.gen_mod2r_test(),
            "modsign": self.gen_modsign_test(),
            "modcmp": self.gen_modcmp_test(),
            "modimp": self.gen_modimp_test(),
            "modexp": self.gen_modexp_test(),
            "acceptance": self.gen_acceptance_test(),
        }
        if self.prime.reduction != "mont":
            self.test_functions["modred"] = self.gen_modred_test()

    def default_test_functions(self, p=None, type_suffix=None):
        p = p or self.prime
        if not p:
            self.tests = []
            return
        type_suffix = type_suffix or self.impltype_suffix
        self.tests = [
            "mul",
            "sqr",
            "modmul",
            "modsqr",
        ]

        if p.reduction != "mont":
            self.tests += ["modred"]

        self.tests += [
            "modmli",
            "modadd",
            "modsub",
            "modsub_negate",
            "modcpy",
            "nres",
            "redc",
            "modneg",
            "modinv",
            "modfsb",
            "modis1",
            "modis0",
            "modzer",
            "modone",
            "modint",
            "modcmv",
            "modcsw",
            "modsqrt",
            "modshr",
            "modshl",
            "mod2r",
            "modsign",
            "modcmp",
            "modimp",
            "modexp",
            "acceptance",
        ]

    def set_test_functions(self, tests=None, type_suffix=None):
        type_suffix = type_suffix or self.impltype_suffix
        if tests:
            self.tests = []
            for t in tests:
                if self.prime.reduction == "mont" and t == "modred":
                    continue
                self.tests.append(t)

    def generate_test_functions(self, tests=None):
        test_list = tests or self.tests
        generated = self.gen_header_ref_fns() + "\n"
        for t in test_list:
            generated += self.test_functions[t]
        generated += self.gen_main_tests_fn(tests=tests)
        return generated

    def print_test_functions(self, tests=None):
        print(self.generate_test_functions(tests))

    def gen_header_ref_fns(self, p=None, inline=None, iterations=None):
        p = p or self.prime
        iterations = iterations or self.iterations
        inline = inline or self.inline_policy
        return f"""\
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "mini-gmp.h"
#include "unity.h"
#include "test_utility.h"

#define ITERATIONS {iterations}
#define ALWAYS_INLINE {inline}

#include "m4-{self.impltype}/code_{p.name}_{p.reduction}.c"

extern gmp_randstate_t state;
extern mpz_t a_mpz, b_mpz, c_mpz, r_mpz, rinv_mpz, w_mpz, lim_mpz, zero_mpz, usedprime, realprime, maxbound;
"""

    def gen_mul_test(self, p=None):
        p = p or self.prime
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void mul_{test_type}(void) {{
    test_mul_{test_type}({p.nlimbs}, mul_{p.name}_ct);
}}

"""
        return test_code

    def gen_modmul_test(self, p=None):
        p = p or self.prime
        is_mont = ""
        ispmp = " 1," if p.reduction != "mont" else " 0,"
        if p.reduction == "mont":
            is_mont = "_mont"
            lgap = p.nlimbs * 32 - p.n
            is_mont += "" if lgap < 2 else "_2p"
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void modmul_{test_type}(void) {{
    test_modmul_{test_type}({p.nlimbs},{ispmp if test_type == "fixed" else ""} modmul_{p.name}_ct, compare_with_ref_modmul{is_mont});
}}

"""
        return test_code

    def gen_sqr_test(self, p=None):
        p = p or self.prime
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void sqr_{test_type}(void) {{
    test_sqr_{test_type}({p.nlimbs}, sqr_{p.name}_ct);
}}

"""
        return test_code

    def gen_modsqr_test(self, p=None):
        p = p or self.prime
        is_mont = ""
        ispmp = " 1," if p.reduction != "mont" else " 0,"
        if p.reduction == "mont":
            is_mont = "_mont"
            lgap = p.nlimbs * 32 - p.n
            is_mont += "" if lgap < 2 else "_2p"
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void modsqr_{test_type}(void) {{
    test_modsqr_{test_type}({p.nlimbs},{ispmp if test_type == "fixed" else ""} modsqr_{p.name}_ct, compare_with_ref_modmul{is_mont});
}}

"""
        return test_code

    def gen_modred_test(self, p=None, inplace=None):
        p = p or self.prime
        inplace = inplace or self.prime.modred_inplace

        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void modred_{test_type}(void) {{
    test_modred{"_inplace" if inplace else ""}_{test_type}({p.nlimbs}, {self.prime.n}, modred_{p.name}_ct);
}}

"""
        return test_code

    def gen_modneg_test(self, p=None):
        p = p or self.prime
        ispmp = 1 if p.reduction != "mont" else 0
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void modneg_{test_type}(void) {{
    test_modneg_{test_type}({p.nlimbs}, {ispmp}, modneg_{p.name}_ct);
}}

"""
        return test_code

    def gen_modop_2inputs_test(self, operation, p=None, extra_decor=""):
        p = p or self.prime
        ispmp = 1 if p.reduction != "mont" else 0
        return f"""\
static void {operation}{extra_decor}_fixed(void) {{
    test_op2inputs_fixed({p.nlimbs}, {ispmp}, {1 if operation == "modsub" else 0}, {operation}_{p.name}_ct, compare_with_ref_{operation});
}}

static void {operation}{extra_decor}_random(void) {{
    test_op2inputs_random({p.nlimbs}, {ispmp}, {1 if operation + extra_decor == "modsub_negate" else 0}, {operation}_{p.name}_ct, compare_with_ref_{operation});
}}

"""

    def gen_modsub_negate_test(self, p=None):
        return self.gen_modop_2inputs_test("modsub", extra_decor="_negate")

    def gen_modmli_test(self, p=None):
        p = p or self.prime
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void modmli_{test_type}(void) {{
    test_modmli_{test_type}({p.nlimbs}, modmli_{p.name}_ct);
}}

"""
        return test_code

    def gen_redc_test(self, p=None):
        p = p or self.prime
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void redc_{test_type}(void) {{
    test_redc_{test_type}({p.nlimbs}, {1 if p.reduction != "mont" else 0}, redc_{p.name}_ct, modfsb_{p.name}_ct);
}}

"""
        return test_code

    def gen_nres_test(self, p=None):
        p = p or self.prime
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void nres_{test_type}(void) {{
    test_nres_{test_type}({p.nlimbs}, {1 if p.reduction != "mont" else 0}, nres_{p.name}_ct);
}}

"""
        return test_code

    def gen_modcpy_test(self, p=None):
        p = p or self.prime
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void modcpy_{test_type}(void) {{
    test_modcpy_{test_type}({p.nlimbs}, modcpy_{p.name}_ct);
}}

"""
        return test_code

    def gen_modinv_test(self, p=None):
        p = p or self.prime
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void modinv_{test_type}(void) {{
    test_modinv_{test_type}({p.nlimbs}, nres_{p.name}_ct, modinv_{p.name}_ct, redc_{p.name}_ct);
}}

"""
        return test_code

    def gen_modfsb_test(self, p=None):
        p = p or self.prime
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void modfsb_{test_type}(void) {{
    test_modfsb_{test_type}({p.nlimbs}, modfsb_{p.name}_ct);
}}

"""
        return test_code

    def gen_modis1_test(self, p=None):
        p = p or self.prime
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void modis1_{test_type}(void) {{
    test_modis1_{test_type}({p.nlimbs}, nres_{p.name}_ct, modis1_{p.name}_ct);
}}

"""
        return test_code

    def gen_modis0_test(self, p=None):
        p = p or self.prime
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void modis0_{test_type}(void) {{
    test_modis0_{test_type}({p.nlimbs}{", nres_" + p.name + "_ct" if test_type == "fixed" else ""}, modis0_{p.name}_ct);
}}

"""
        return test_code

    def gen_modzer_test(self, p=None):
        p = p or self.prime
        return f"""\
static void modzer_random(void) {{
    test_modzer_random({p.nlimbs}, modzer_{p.name}_ct);
}}

"""

    def gen_modone_test(self, p=None):
        p = p or self.prime
        return f"""\
static void modone_random(void) {{
    test_modone_random({p.nlimbs}, modone_{p.name}_ct, redc_{p.name}_ct);
}}

"""

    def gen_modint_test(self, p=None):
        p = p or self.prime
        return f"""\
static void modint_random(void) {{
    test_modint_random({p.nlimbs}, modint_{p.name}_ct, redc_{p.name}_ct);
}}

"""

    def gen_modshr_test(self, p=None):
        p = p or self.prime
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void modshr_{test_type}(void) {{
    test_modshr_{test_type}({p.nlimbs}, modshr_{p.name}_ct);
}}

"""
        return test_code

    def gen_modshl_test(self, p=None):
        p = p or self.prime
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void modshl_{test_type}(void) {{
    test_modshl_{test_type}({p.nlimbs}, modshl_{p.name}_ct);
}}

"""
        return test_code

    def gen_modcmv_test(self, p=None):
        p = p or self.prime
        return f"""\
static void modcmv_random(void) {{
    test_modcmv_random({p.nlimbs}, modcmv_{p.name}_ct);
}}

"""

    def gen_modcsw_test(self, p=None):
        p = p or self.prime
        return f"""\
static void modcsw_random(void) {{
    test_modcsw_random({p.nlimbs}, modcsw_{p.name}_ct);
}}

"""

    def gen_modsqrt_test(self, p=None):
        p = p or self.prime
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void modsqrt_{test_type}(void) {{
    test_modsqrt_{test_type}({p.nlimbs}, nres_{p.name}_ct, modsqrt_{p.name}_ct, redc_{p.name}_ct);
}}

"""
        return test_code

    def gen_mod2r_test(self, p=None):
        p = p or self.prime
        ispmp = 1 if p.reduction != "mont" else 0
        test_code = ""
        for test_type in ["random", "fixed"]:
            test_code += f"""\
static void mod2r_{test_type}(void) {{
    test_mod2r_{test_type}({p.nlimbs}, {ispmp}, mod2r_{p.name}_ct);
}}

"""
        return test_code
        
    def gen_modsign_test(self, p=None):
        p = p or self.prime
        ispmp = 1 if p.reduction != "mont" else 0
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void modsign_{test_type}(void) {{
    test_modsign_{test_type}({p.nlimbs}, {ispmp}, modsign_{p.name}_ct);
}}

"""
        return test_code
            
    def gen_modcmp_test(self, p=None):
        p = p or self.prime
        ispmp = 1 if p.reduction != "mont" else 0
        return f"""\
static void modcmp_random(void) {{
    test_modcmp_random({p.nlimbs}, {ispmp}, modcmp_{p.name}_ct);
}}

"""
        return test_code

    def gen_modimp_test(self, p=None):
        p = p or self.prime
        ispmp = 1 if p.reduction != "mont" else 0
        test_code = ""
        for test_type in ["fixed", "random"]:
            test_code += f"""\
static void modimp_{test_type}(void) {{
    test_modimp_{test_type}({p.nlimbs}, {ispmp}, modimp_{p.name}_ct);
}}

"""
        return test_code

    def gen_modexp_test(self, p=None):
        p = p or self.prime
        ispmp = 1 if p.reduction != "mont" else 0
        return f"""\
static void modexp_random(void) {{
    test_modexp_random({p.nlimbs}, {ispmp}, modexp_{p.name}_ct);
}}

"""
        return test_code

    def gen_acceptance_test(self, p=None):
        p = p or self.prime
        return f"""\
static void acceptance_random(void) {{
    test_acceptance_random({p.nlimbs}, {1 if p.reduction != "mont" else 0}, nres_{p.name}_ct, modadd_{p.name}_ct, modsub_{p.name}_ct, modmul_{p.name}_ct, modsqr_{p.name}_ct, modinv_{p.name}_ct, modsqrt_{p.name}_ct, redc_{p.name}_ct, modfsb_{p.name}_ct);
}}

"""

    def gen_main_tests_fn(self, p=None, tests=None, type_suffix=None):
        p = p or self.prime
        type_suffix = type_suffix or self.impltype_suffix
        tests = tests or self.tests
        set_prime = ""
        if p.reduction == "mont" or p.c == None:
            set_realprime = f'mpz_set_str(realprime, "0x{p.prime:x}", 0);'
            if p.nlimbs * 32 >= p.prime.bit_length() + 2:
                set_prime = f'mpz_add(usedprime, realprime, realprime);'
            else:
                set_prime = f'mpz_set(usedprime, realprime);'
            set_r_rinv = f'mpz_set_ui(r_mpz, 1);\n    mpz_mul_2exp(r_mpz, r_mpz, {p.nlimbs * 32});\n    mpz_invert(rinv_mpz, r_mpz, realprime);'
        else:
            set_realprime = f"mpz_set_ui(realprime, 1);\n    mpz_mul_2exp(realprime, realprime, {p.realn});\n    mpz_sub_ui(realprime, realprime, {p.realc});"
            if p.realn == p.n and p.realc == p.c:
                set_prime = "mpz_set(usedprime, realprime);"
            elif p.c == p.realc * 2 ** (p.n - p.realn):
                set_prime = f"mpz_mul_2exp(usedprime, realprime, {p.n - p.realn});"
            else:
                set_prime = f"mpz_set_ui(usedprime, 1);\n    mpz_mul_2exp(usedprime, usedprime, {p.n});\n    mpz_sub_ui(usedprime, usedprime, {p.c});"
            set_r_rinv = f'mpz_set_ui(r_mpz, 1);\n    mpz_mul_2exp(r_mpz, r_mpz, {p.nlimbs * 32});'
        if p.n % 32 == 0:
            set_maxbound = f"mpz_set_ui(maxbound, 1);\n    mpz_mul_2exp(maxbound, maxbound, {p.n});\n    mpz_sub_ui(maxbound, maxbound, 1);"
        else:
            set_maxbound = f"mpz_set_ui(maxbound, 1);\n    mpz_mul_2exp(maxbound, maxbound, {p.n+1});\n    mpz_sub_ui(maxbound, maxbound, 1);"
        types = ["random", "fixed"]
        notfixed = ["modzer", "modone", "modint", "modcmv", "modcsw", "modcmp", "modexp", "acceptance"]
        generated = f"""\
void test_{p.name}_{p.reduction}_ct{type_suffix}(void) {{
    printf("Testing {p.name}_{p.reduction}{type_suffix}\\n");
    {set_realprime}
    {set_prime}
    {set_maxbound}
    {set_r_rinv}
"""
        for op in tests:
            for type in types:
                if type == "fixed" and op in notfixed:
                    continue
                generated += f"    RUN_TEST({op}_{type});\n"
        generated += f"""\
    printf("\\n");
}}"""
        return generated


if __name__ == "__main__":
    if len(sys.argv) < 3:
        usage()
        sys.exit(1)

    name = sys.argv[1]
    reduction = sys.argv[2]
    reductions = ["pmp_asm", "pmp_c", "mont"]
    impltype = sys.argv[3]
    if impltype == "codegen":
        impltype_suffix = ""
    else:
        impltype_suffix = f"_{impltype}"

    if reduction not in reductions:
        print("Invalid reduction.\n")
        usage()
        sys.exit(1)

    inline_policy = "__attribute__((noinline))"
    iterations = 256
    test_gen = TestGenerator(name, reduction, impltype, inline_policy, iterations)
    if not test_gen.prime:
        print("Invalid prime name\n")
        usage()
        sys.exit(1)
    # test_gen.set_test_functions(tests=["mod2r", "modsign", "modcmp"])
    test_gen.print_test_functions()
