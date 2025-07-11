# How to update the M4 library

This library uses pythons scripts to generate the C files for it's main code, unit tests and benchmarks. To expand one of those aspects, you must edit the corresponding python file.

## Adding a new prime number
First of all, if you're just adding a new pseudo-Mersenne prime and don't need to change any flags, you can simply edit the `cmake/primes.cmake` file like so:
- Add the expression for your prime, such as "2**383-31", as new, uncommented line in the PMLIST definition.
- Make sure the option USE_PMLIST is set to ON.

Now, if instead you wish to add a new prime manually here's all the steps:
- Inside `cmake/primes.cmake` add a new option for the prime and turn it ON. For example:
```cmake
    option(USE_MY_NEW_PRIME "Generate code for ..." ON)
```
- Then add an if block to append it to the PRIMES_M4_EXTRA list, here "pmp_asm" could also be "pmp_c":
```cmake
    if(USE_MY_NEW_PRIME)
        list(APPEND PRIMES_M4_EXTRA MY_NEW_PRIME)
        list(APPEND PRIMES_M4_EXTRA_REDUCTION pmp_asm)
    endif()
```
- Now edit `scripts/m4prime.py` so it recognizes the new prime name. Just add another elif block setting the necessary parameters. You could, for example, add a new Pseudo-Mersenne prime 2^n-c as follows:
```python
    elif name == "MY_NEW_PRIME":
        self.prime = 2**n - c
        self.n = n
        self.c = c
        self.pmp = True
```

Now the build process will also generate code, tests and benchmarks for the newly specified prime.

Note that, in reality there are many more parameters and flags that can be specified individually at prime definition. Here's an exhaustive list:

- **name** (string)
    - The name used internally to refer to the prime.
- **reduction** (string)
    - Algorithm used for reduction, must be "pmp_asm", "pmp_c" or "mont".
- **prime** (int)
    - The actual integer value of the prime.
- **nlimbs** (int)
    - Number of 32-bit limbs needed to represent a number modulo prime.
- **pmp** (bool)
    - *True* when it is a Pseudo-Mersenne prime (PMP), *False* otherwise.
- **n** (int)
    - Used for PMPs, bit-length for the number used in reductions (may be larger than the actual prime, e.g. for C25519 *n* is set to 256).
- **c** (int)
    - Used for PMPs, value of the *c* used for reductions (may be different from actual prime, e.g. for C25519 *c* is set to 38).
- **realn** (int)
    - Used for PMPs, bit-length for the real prime (e.g. for C25519, *realn* is set to 255).
- **realc** (int)
    - Used for PMPs, the *c* value of the  real prime (e.g. for C25519, *realc* is set to 19).
- **optsub** (bool)
    - Do subtraction without using temporary variables, only works for small primes.
- **optfsb** (bool)
    - Do fsb without using temporary variables, only works for small primes.
- **full** (bool / int)
    - Used in reduction, set to *c* when a prime has full size (occupies all limbs fully), must be *False* otherwise.
- **lastbit** (bool)
    - Used in reduction, set to *True* when the last limb has its most significant bit set, must be *False* otherwise.
- **montmli** (bool)
    - Captures the low degree polynomials of a solinas prime. Only used in montgomery mli for primes with this format.
- **modred_inplace** (bool)
    - Determines if modred function should be inplaced or not (currently always False).

## Adding a new unit test
To add a new test to be performed for all enabled primes, you must edit the `scripts/m4test.py` file.
- Inside the class TestGenerator, define a new method for your test, following the pattern of the already present methods. For example:
```python
    def gen_my_test(self, p=None, callback_fixed=None, callback_inputs=None, type_suffix=None):
        return f"""
        // the test logic goes here
        """
```
- Your test generator method must return a string of C code containing the actual test function(s) to be generated.
- Now, on the __init__ method, add an entry on the dictionary `self.test_functions` for your test:
```python
    self.test_functions = {
    . . .
    "my_test": self.gen_my_test(),
    . . .
    }
```
- Now append your test name to the `self.tests` list inside the `default_test_functions` method:
```python
self.tests = [
    . . .
    "my_test",
    . . .
    ]
```

Now rebuilding the project should generate a new test for each prime

## Adding a new benchmark
To measure the performance of modular arithmetic operations, the build process generates `bench.elf`, an executable that runs selected benchmarks on different prime configurations. The script `scripts/gen-benchmarks-for-m4.py` automates this process by embedding benchmark functions into the generated C code.

By default, the script benchmarks the following functions:

- modmul
- modsqr
- modadd
- modsub

To add a new benchmark function for all selected primes, follow these steps:

- Within the `file.write(...)` call, define your new benchmark function in C.
- Alternatively, you can define it in a separate string and conditionally include it in the final code (see examples in the script).
- Add a call to the new benchmark function inside the `void bench_m4_{pname}_{ptype}{impltype_suffix}()` function, which is responsible for calling all benchmark functions.

For example, let's add a new benchmark function that counts the number of cycles for two `modadd` calls. Here is the function definition:

```python
f"""static void test_bench() {{
    uint32_t a[Nlimbs_{pname}_ct], b[Nlimbs_{pname}_ct], c[Nlimbs_{pname}_ct];
    bm_decls;

    bm_start();
    DoNotOptimize(a);
    DoNotOptimize(b);
    modadd_{pname}_ct(a, b, c);
    modadd_{pname}_ct(a, b, c);
    DoNotOptimize(c);
    bm_end();

    printf("{pname}, {ptype}{impltype_optional}, M4, test_bench, cycles, %" PRIu32 "\\n", bm_result());
    usleep(10000); // To avoid SWO buffer overflows
}}
"""
```

In this example, the benchmark is generated for all selected primes, so the function definition is added directly inside the `file.write(...)` call.

Finally, add a call to the new function inside the `void bench_m4_{pname}_{ptype}{impltype_suffix}()` function:

```python
f"""void bench_m4_{pname}_{ptype}{impltype_suffix}() {{
    {bench_base_call}
    {bench_modmli_call}
    {bench_aux_call}
    test_bench();
    printf("\\n");
}}
"""
```

After building the new `bench.elf` and running it, you should see output similar to the following, now including your benchmark function:

```csv
MFP248, mont, M4, modmul, cycles, 246
MFP248, mont, M4, modsqr, cycles, 197
MFP248, mont, M4, modadd, cycles, 60
MFP248, mont, M4, modsub, cycles, 66
MFP248, mont, M4, test_bench, cycles, 172
```
