# /usr/bin/env python3

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

bench_dir = sys.argv[1]
pname = sys.argv[2]
ptype = sys.argv[3]
impltype = sys.argv[4]

# Prevent invalid function names
pname = ''.join(c for c in pname if c.isalnum())[:10]

if impltype == "codegen":
    file_name = f"{bench_dir}/bench_{pname}_{ptype}.c"
    impltype_optional = ""
    impltype_suffix = ""
else:
    file_name = f"{bench_dir}/bench_{pname}_{ptype}_custom.c"
    impltype_optional = f" {impltype}"
    impltype_suffix = f"_{impltype}"

bench_base_bool = True  # Set to True/False if you want or not to bench base functions
bench_aux_bool = False  # Set to True/False if you want or not to bench aux functions
bench_aux = ""
bench_aux_call = ""

if bench_aux_bool == True and impltype_suffix != "_custom":
    bench_aux_call = f"""
    bench_m4_modfsb_{pname}_{ptype}();
    bench_m4_modneg_{pname}_{ptype}();
    bench_m4_modcpy_{pname}_{ptype}();
    bench_m4_modpro_{pname}_{ptype}();
    bench_m4_modinv_{pname}_{ptype}();
    bench_m4_nres_{pname}_{ptype}();
    bench_m4_redc_{pname}_{ptype}();
    bench_m4_modis1_{pname}_{ptype}();
    bench_m4_modis0_{pname}_{ptype}();
    bench_m4_modzer_{pname}_{ptype}();
    bench_m4_modone_{pname}_{ptype}();
    bench_m4_modint_{pname}_{ptype}();
    bench_m4_modqr_{pname}_{ptype}();
    bench_m4_modcmv_{pname}_{ptype}();
    bench_m4_modcsw_{pname}_{ptype}();
    bench_m4_modsqrt_{pname}_{ptype}();
    bench_m4_modshl_{pname}_{ptype}();
    bench_m4_modshr_{pname}_{ptype}();
    bench_m4_modexp_{pname}_{ptype}();
    bench_m4_modimp_{pname}_{ptype}();
"""
    bench_aux = f"""
static void bench_m4_modfsb_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modfsb_{pname}_ct(a);
    bm_end();

    printf("{pname}, {ptype}, M4, modfsb, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modneg_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct], b[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modneg_{pname}_ct(a, b);
    DoNotOptimize(b);
    bm_end();

    printf("{pname}, {ptype}, M4, modneg, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modcpy_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct], b[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modcpy_{pname}_ct(a, b);
    DoNotOptimize(b);
    bm_end();

    printf("{pname}, {ptype}, M4, modcpy, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modpro_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct], b[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modpro_{pname}_ct(a, b);
    DoNotOptimize(b);
    bm_end();

    printf("{pname}, {ptype}, M4, modpro, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modinv_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct], c[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modinv_{pname}_ct(a, NULL, c);
    DoNotOptimize(c);
    bm_end();

    printf("{pname}, {ptype}, M4, modinv, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_nres_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct], b[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    nres_{pname}_ct(a, b);
    DoNotOptimize(b);
    bm_end();

    printf("{pname}, {ptype}, M4, nres, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_redc_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct], b[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    redc_{pname}_ct(a, b);
    DoNotOptimize(b);
    bm_end();

    printf("{pname}, {ptype}, M4, redc, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modis1_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct];
    int r;
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    r = modis1_{pname}_ct(a);
    DoNotOptimize(r);
    bm_end();

    printf("{pname}, {ptype}, M4, modis1, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modis0_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct];
    int r;
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    r = modis0_{pname}_ct(a);
    DoNotOptimize(r);
    bm_end();

    printf("{pname}, {ptype}, M4, modis0, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modzer_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    modzer_{pname}_ct(a);
    DoNotOptimize(a);
    bm_end();

    printf("{pname}, {ptype}, M4, modzer, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modone_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    modone_{pname}_ct(a);
    DoNotOptimize(a);
    bm_end();

    printf("{pname}, {ptype}, M4, modone, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modint_{pname}_{ptype}() {{
    int x;
    spint a[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(x);
    modint_{pname}_ct(x, a);
    DoNotOptimize(a);
    bm_end();

    printf("{pname}, {ptype}, M4, modint, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modqr_{pname}_{ptype}() {{
    spint x[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(x);
    DoNotOptimizeConst(modqr_{pname}_ct(NULL, x));
    bm_end();

    printf("{pname}, {ptype}, M4, modqr, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modcmv_{pname}_{ptype}() {{
    int x;
    spint a[Nlimbs_{pname}_ct], b[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(x);
    modcmv_{pname}_ct(x, a, b);
    DoNotOptimize(b);
    bm_end();

    printf("{pname}, {ptype}, M4, modcmv, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modcsw_{pname}_{ptype}() {{
    int x;
    spint a[Nlimbs_{pname}_ct], b[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(x);
    modcsw_{pname}_ct(x, a, b);
    DoNotOptimize(b);
    bm_end();

    printf("{pname}, {ptype}, M4, modcsw, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modsqrt_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct], c[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modsqrt_{pname}_ct(a, NULL, c);
    DoNotOptimize(c);
    bm_end();

    printf("{pname}, {ptype}, M4, modsqrt, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modshl_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct];
    int x;
    bm_decls;

    bm_start();
    DoNotOptimize(x);
    modshl_{pname}_ct(x, a);
    DoNotOptimize(a);
    bm_end();

    printf("{pname}, {ptype}, M4, modshl, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modshr_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct];
    int x;
    bm_decls;

    bm_start();
    DoNotOptimize(x);
    modshr_{pname}_ct(x, a);
    DoNotOptimize(a);
    bm_end();

    printf("{pname}, {ptype}, M4, modshr, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modexp_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct];
    char x[Nlimbs_{pname}_ct*32];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modexp_{pname}_ct(a, x);
    DoNotOptimize(x);
    bm_end();

    printf("{pname}, {ptype}, M4, modexp, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

static void bench_m4_modimp_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct];
    char x[Nlimbs_{pname}_ct*32];
    bm_decls;

    bm_start();
    DoNotOptimize(x);
    modimp_{pname}_ct(x, a);
    DoNotOptimize(a);
    bm_end();

    printf("{pname}, {ptype}, M4, modimp, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}
"""





bench_modmli = f"""
static void bench_m4_modmli_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct], b, c[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmli_{pname}_ct(a, b+2, c);
    DoNotOptimize(c);
    bm_end();

    printf("{pname}, {ptype}{impltype_optional}, M4, modmli, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}
"""
bench_modmli_call = f"bench_m4_modmli_{pname}_{ptype}();"

bench_base_call = f"""bench_m4_modmul_{pname}_{ptype}();
    bench_m4_modsqr_{pname}_{ptype}();
    bench_m4_modadd_{pname}_{ptype}();
    bench_m4_modsub_{pname}_{ptype}();"""

if bench_base_bool == False:
    bench_base_call = ""
    bench_modmli_call = ""

with open(file_name, "w") as file:
    file.write(
        f"""
#include <inttypes.h>
#include "hal.h"

#include "m4-{impltype}/code_{pname}_{ptype}.c"

#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "r,m"(value) : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#define DoNotOptimizeConst(value) asm volatile("" : : "m,r"(value) : "memory");
#endif

static void bench_m4_modmul_{pname}_{ptype}() {{
    uint32_t a[Nlimbs_{pname}_ct], b[Nlimbs_{pname}_ct], c[2 * Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmul_{pname}_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("{pname}, {ptype}{impltype_optional}, M4, modmul, cycles, %" PRIu32 "\\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}}

static void bench_m4_modsqr_{pname}_{ptype}() {{
    uint32_t a[Nlimbs_{pname}_ct], c[2 * Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modsqr_{pname}_ct(a, c);
    DoNotOptimize(c);
    bm_end();

    printf("{pname}, {ptype}{impltype_optional}, M4, modsqr, cycles, %" PRIu32 "\\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}}

static void bench_m4_modadd_{pname}_{ptype}() {{
    uint32_t a[Nlimbs_{pname}_ct], b[Nlimbs_{pname}_ct], c[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modadd_{pname}_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("{pname}, {ptype}{impltype_optional}, M4, modadd, cycles, %" PRIu32 "\\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}}

static void bench_m4_modsub_{pname}_{ptype}() {{
    uint32_t a[Nlimbs_{pname}_ct], b[Nlimbs_{pname}_ct], c[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modsub_{pname}_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("{pname}, {ptype}{impltype_optional}, M4, modsub, cycles, %" PRIu32 "\\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}}
{bench_modmli}
{bench_aux}
void bench_m4_{pname}_{ptype}{impltype_suffix}() {{
    {bench_base_call}
    {bench_modmli_call}
    {bench_aux_call}
    printf("\\n");
}}
"""
    )
