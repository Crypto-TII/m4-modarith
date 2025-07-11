### **Build System Overview**
The project is composed of:
- **Python scripts** that generate C and assembly code for finite field arithmetic.
- **CMake build system** that organizes the compilation and linking.
- **Testing and benchmarking executables** for performance evaluation.

### **1. Configuration Phase**
- **Prime Selection**:  
  `primes.cmake` defines configurable options (e.g., `USE_C25519`, `USE_C448`) to populate prime lists:
  - `PRIMES_PSEUDO_MONTY`: Primes using pseudo-Mersenne reductions
  - `PRIMES_MONTY`: Primes using Montgomery reductions
  - `PRIMES_CUSTOM_*`: Primes with hand-optimized implementations
  - `PMLIST`: Test primes (optional)

- **Toolchain Setup**:  
  `stm32f4discovery.cmake` initializes hardware-specific dependencies (libopencm3) for STM32F4 targets, including linker scripts and HAL code.

- **Build Caching**:  
  `build_caching.cmake` enables ccache/sccache to accelerate recompilation.

- **Conditional Compilation**:  
  Prime-specific code is excluded at compile time if options like `USE_C25519` are disabled.
---

### **2. Code Generation**
#### `modarith`
- **Scripts**: Uses `monty.py`, `pseudo.py` (from the `modarith` submodule) and `gen-benchmarks-for-modarith.py`.
- **Process**:
  - For each prime (e.g., C25519, C448):
    - Generates `code_<prime>_<type>.c` in `modarith-codegen/`
    - Creates benchmark stubs (`bench_<prime>_<type>.c`) in `modarith-bench/`.

#### `m4`
- **Scripts**: Uses `m4generator.py`, `m4test.py`, and `gen-benchmarks-for-m4.py`.
- **Process**:
  - For each prime and reduction type (e.g., `pmp_asm`, `mont`):
    - Generates code (`code_<prime>_<type>.c`) in `m4-codegen/` or `m4-custom/`.
    - Produces test cases (`test_<prime>_<type>.c`) in `m4-tests/`.
    - Creates benchmarks (`bench_<prime>_<type>.c`) in `m4-bench/`.

---

### **3. Library Compilation**
- **Core Libraries**:
  - `modarith-bench`: Aggregates generated finite field arithmetic code and benchmarks.
  - `m4-bench`: Combines M4 implementations and benchmarks.
  - `mini-gmp`: Provides reference implementations for testing.
  - `unity`: Unit testing framework.

- **RFC7748 Libraries**:  
  For curves like C25519/C448, specialized libraries (`rfc7748-m4-*`, `rfc7748-modarith-*`) are built with compile-time definitions for code variants.

---

### **4. Executable Assembly**
- **`bench.elf`**:
  - Links `modarith-bench`, `m4-bench`, and RFC7748 libraries.
  - Entry point: `src/main.c` (benchmark runner).
  - Output: Binary for performance testing.

- **`run_tests.elf`**:
  - Links `m4-bench`, `unity`, and test-specific code.
  - Entry point: `src/test_utility.c` (test runner).
  - Automatically generated `test_m4.c` includes all test cases via CMake macros.
  - Runs on hardware (via OpenOCD) or emulators.

---

### **5. Post-Build Steps**
- **STM32 Binary Conversion**:  
  For STM32 targets, `.elf` files are converted to `.bin` using `objcopy`.
- **Test Execution**:  
  `add_test` integrates `run_tests.elf` into CTest for automated testing.
