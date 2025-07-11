# M4-MODARITH

This library can be seen as an extension of [modarith](https://github.com/mcarrickscott/modarith), originally a Python script developed by Michael Scott (TII) for general finite field arithmetic using portable C or Rust code. Our library, named `m4-modarith`, generates C code with embedded assembly tailored for the ARM Cortex-M4.

Its main script takes as input the target prime and desired reduction method. It generates efficient C code, optimized for the target prime.

## Main usage

The library can be used on two main ways:
- As a standalone script for generating efficient code for a specific prime and reduction method tailored for the ARM Cortex-M4 architecture
  - Usage: ```python m4generator.py <prime name or expression> <reduction>```
  - `prime name`: a short name for the prime of interest, using valid C identifier characters; e.g. C.25519. Alternatively, an integer or expression can be used directly.
  - Valid values for `reduction`: `pmp_asm`, `pmp_c`, `mont`
    - Description of reduction types and their parameters:
    - `pmp_asm`: reduction modulo pseudo-Mersenne primes, i.e. those of the form $2^n - c$. 
    - `pmp_c`: same as `pmp_asm`, except that reduction is implemented mostly in C, with inline assembly blocks only as needed.
    - `mont`: reduction using Montgomery multiplication.
  - For our inlining policy, please refer to **[inline_policy.md](inline_policy.md)**.
  - Refer to **[modifying.md#adding-a-new-prime-number](modifying.md#adding-a-new-prime-number)** for a reference of other possible options for the script

- As a benchmark suite of several generated code for different primes and reduction methods, as well as a testing platform of each generated function.
  - Refer to **[modifying.md](modifying.md)** for instructions for adding new primes, unit tests, and benchmarks to the project.

---
## Overall building process

This library was built and tested on an [**STM32F407G-DISC1**](https://www.st.com/en/evaluation-tools/stm32f4discovery.html) evaluation board, as well as using [QEMU](https://www.qemu.org) for emulation. Any other usage can be considered experimental and no guarantees are made on its compilation process.

**Note**: The `select_host_board.sh`, `upload.sh`, `monitor.sh`, and `openocd.sh` scripts in the scripts directory should be modified according to your specific board setup and requirements. The variable `STLINK_SERIAL` defined in `select_host_board.sh` must contain the serial for your target board.

### Dependencies ###

- **[arm-none-eabi-gcc](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)** ([clang](https://github.com/ARM-software/LLVM-embedded-toolchain-for-Arm) toolchain currently not supported).
  - For Mac users, please use homebrew's package [gcc-arm-embedded](https://formulae.brew.sh/cask/gcc-arm-embedded) (and not the `arm-none-eabi-gcc` package)
- **[stlink](https://github.com/texane/stlink)** to flash binaries into the development board. Some distribution have packages for this.
- standard development tools: **CMake**, **make**, **git**, **ninja**
- **python** and **python3** (both command must be present and running on the development machine).
- Suggested VS Code extensions: Remote - SSH, CMake Tools, Cortex-Debug
- For **[modarith](https://github.com/mcarrickscott/modarith)**, some additional dependencies are needed. Here are listed the main dependencies, but please check its github repository for any other possible dependency.
  - **[addchain](https://github.com/mmcloughlin/addchain)**
  - **[cpucycles](https://cpucycles.cr.yp.to/)**

### Configure and build ###

For a complete outline of the build process, including code generation, compilation, and testing steps, please refer to **[build.md](build.md)**.

As a quick guide for configuring and building, these commands should fully build the project:

```bash
# From the main project directory
rm -rf build
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=arm-none-eabi-gcc-libopencm3.toolchain -DCMAKE_BUILD_TYPE=Release -G Ninja ..
ninja
```

#### Emulate with QEMU (mostly to run unit tests) ####

```bash
# From the main project directory
qemu-system-arm -M olimex-stm32-h405 -semihosting -nographic -serial null -serial stdio -monitor null -kernel build/run_tests
```

#### Flash to board and monitor via SWO ####

```bash
# From the main project directory
st-flash --reset write build/bench.bin 0x08000000
st-trace -c24
```

---
## Library Structure Overview

For a more complete overview, please refer to **[project_structure.md](project_structure.md)**. Here are its directory components

- **`build`**: Contains CMake-generated build artifacts (object files, binaries).  
- **`cmake`**: Hosts CMake modules for code generation, toolchain setup, and dependency management.  
- **`hw`**: Hardware-specific code (e.g., STM32 HAL, linker scripts).  
- **`libopencm3`**: Submodule for the libopencm3 firmware library (STM32 support).  
- **`m4-bench`**: Generated benchmarks for M4 implementations of primes.  
- **`m4-codegen`**: Generated M4 code for primes.  
- **`m4-custom`**: Custom M4 assembly code for specific primes.  
- **`m4-external`**: Benchmark code for external implementations.
- **`m4-tests`**: Generated unit tests for M4 implementations.  
- **`mini-gmp`**: Minimal GMP implementation for testing.  
- **`modarith`**: Python scripts for original modarith.  
- **`modarith-bench`**: Generated benchmarks for modarith implementations of primes.
- **`modarith-codegen`**: Generated modarith code for primes. 
- **`scripts`**: Python scripts of M4 for code generation, testing, and debugging.
- **`src`**: Necessary support C test and utility code.
- **`unity`**: Submodule for the Unity unit testing framework.  


### Library API
We follow the same API as [modarith](https://github.com/mcarrickscott/modarith). From its README:

Assume the modulus is $p$. The provided functions are

*nres()*   -- Convert a big number to internal format  \
*redc()*   -- Convert back from internal format, result $\lt p$  \
*modfsb()* -- Perform final subtraction to reduce from $\lt 2p$ to $\lt p$  \
*modadd()* -- Modular addition, result $\lt 2p$  \
*modsub()* -- Modular subtraction, result $\lt 2p$  \
*modneg()* -- Modular negation, result $\lt 2p$  \
*modmul()* -- Modular multiplication, result $\lt 2p$  \
*modsqr()* -- Modular squaring, result $\lt 2p$  \
*modmli()* -- Modular multiplication by a small integer, result $\lt 2p$ \
*modcpy()* -- Copy a big number \
*modpro()* -- Calculate progenitor, for subsequent use for modular inverses and square roots  \
*modinv()* -- Modular inversion  \
*modsqrt()* -- Modular square root \
*modis1()* -- Test for equal to unity  \
*modis0()* -- Test for equal to zero  \
*modone()* -- Set equal to unity  \
*modzer()* -- Set equal to zero  \
*modint()* -- Convert an integer to internal format  \
*modqr()*  -- Test for quadratic residue  \
*modcmv()* -- Conditional constant time move  \
*modcsw()* -- Conditional constant time swap  \
*modshl()* -- shift left by bits  \
*modshr()* -- shift right by bits  \
*mod2r()*  -- set to 2^r \
*modexp()* -- export from internal format to byte array \
*modimp()* -- import to internal format from byte array  \
*modsign()* -- Extract sign (parity bit) \
*modcmp()* -- Test for equality \

  ---  
