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

bench_dir = sys.argv[2]
pname = sys.argv[3]
ptype = sys.argv[4]

# Prevent invalid function names
pname = ''.join(c for c in pname if c.isalnum())

file_name = f"{bench_dir}/bench_{pname}_{ptype}.c"

bench_base_bool = True  # Set to True/False if you want or not to bench base functions

bench_modmli = ""
if ptype == "pseudo":
    bench_modmli = f"""
void bench_modarith_modmli_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct], b, c[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmli_{pname}_ct(a, b+2, c);
    DoNotOptimize(c);
    bm_end();

    printf("{pname}, {ptype}, modarith, modmli, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}
"""
bench_modmli_call = ""
if ptype == "pseudo":
    bench_modmli_call = f"bench_modarith_modmli_{pname}_{ptype}();"

bench_base_call = f"""bench_modarith_modmul_{pname}_{ptype}();
    bench_modarith_modsqr_{pname}_{ptype}();
    bench_modarith_modadd_{pname}_{ptype}();
    bench_modarith_modsub_{pname}_{ptype}();"""

if bench_base_bool == False:
    bench_base_call = ""
    bench_modmli_call = ""

with open(file_name, "w") as file:
    file.write(
        f"""
#include <inttypes.h>
#include "hal.h"
               
#include "code_{pname}_{ptype}.c"
               
#if defined(__clang__)
#define DoNotOptimize(value) asm volatile("" : "+r,m"(value) : : "memory");
#else
#define DoNotOptimize(value) asm volatile("" : "+m,r"(value) : : "memory");
#endif

void bench_modarith_modmul_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct], b[Nlimbs_{pname}_ct], c[2 * Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modmul_{pname}_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("{pname}, {ptype}, modarith, modmul, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

void bench_modarith_modsqr_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct], c[2 * Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    modsqr_{pname}_ct(a, c);
    DoNotOptimize(c);
    bm_end();

    printf("{pname}, {ptype}, modarith, modsqr, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

void bench_modarith_modadd_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct], b[Nlimbs_{pname}_ct], c[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modadd_{pname}_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("{pname}, {ptype}, modarith, modadd, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

void bench_modarith_modsub_{pname}_{ptype}() {{
    spint a[Nlimbs_{pname}_ct], b[Nlimbs_{pname}_ct], c[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modsub_{pname}_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("{pname}, {ptype}, modarith, modsub, cycles, %" PRIu32 "\\n", bm_result());
    usleep(1000); // To avoid SWO buffer overflows
}}

{bench_modmli}

void bench_modarith_{pname}_{ptype}() {{
    {bench_base_call}
    {bench_modmli_call}
    printf("\\n");
}}
"""
    )
