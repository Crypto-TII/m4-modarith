cmake_minimum_required(VERSION 3.21)
project(m4-modarith C ASM)

# help macro
macro(log var)
    message(STATUS "${var}: ${${var}}")
endmacro()

# Other not used flags: -fsanitize=address -Wformat -Wformat-security -Wall -Wextra
execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
    OUTPUT_VARIABLE GCC_VERSION)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")
log(CMAKE_MODULE_PATH)

option(USE_BUILD_CACHING "Speed up compilation using ccache or sccache" ON)
option(REGEN_MODARITH_CODE "Regenerate modarith code" ON)
option(UNROLL_LOOPS "Pass the -funroll-loops flag to the compiler" ON)
set(BOARD "STM32F4DISCOVERY" CACHE STRING "Development board to target: STM32F4DISCOVERY, STM32F4DISCOVERY-FULLRAM, NUCLEO-L4R5ZI or NUCLEO-L4R5ZI-FULLRAM")

if (UNROLL_LOOPS)
    set(UNROLL_FLAG "-funroll-loops")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # These options may be required to compile with clang:
    # -fomit-frame-pointer -mllvm -exhaustive-register-search
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 ${UNROLL_FLAG}")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2 ${UNROLL_FLAG} -Wformat=0 -Werror -Wno-unused-function -Wno-unused-result -Wno-strict-prototypes") # -Wunused-value -Wunused-variable -fsanitize=address -Wcast-align
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Os -Wformat=0 -Werror -Wno-unused-function -Wno-unused-result -Wno-strict-prototypes") # -Wunused-value -Wunused-variable -fsanitize=address -Wcast-align
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Og -Wformat=0 -Werror -Wno-unused-function -Wno-unused-result -Wno-strict-prototypes") # -Wunused-value -Wunused-variable -fsanitize=address -Wcast-align
else()
    message(FATAL_ERROR "CMAKE_BUILD_TYPE not valid")
endif()

include(cmake/build_caching)
include(cmake/board)
include(CTest)
include(cmake/m4)
include(cmake/modarith)
include(cmake/primes)

log(CMAKE_C_COMPILER)
log(CMAKE_C_FLAGS)

set(CMAKE_C_STANDARD 11)

if(NOT("${toolchain}" STREQUAL "arm-none-eabi-libopencm3"))
    set(TEST_ITERATIONS 1000000)
else()
    set(TEST_ITERATIONS 1000)
endif()

add_library(unity unity/unity.c)
target_include_directories(unity INTERFACE unity)

add_library(mini-gmp mini-gmp/mini-gmp.c mini-gmp/mini-gmp-rand.c mini-gmp/xoshiro128plusplus.c)
target_include_directories(mini-gmp INTERFACE mini-gmp)

# executable
add_library(modarith-bench STATIC)
target_include_directories(modarith-bench PRIVATE modarith-codegen)

add_library(m4-bench STATIC)
target_include_directories(m4-bench PRIVATE .)

add_executable(bench.elf src/main.c)
target_link_libraries(bench.elf PRIVATE modarith-bench m4-bench)
target_compile_definitions(bench.elf PRIVATE M4_MODARITH_BENCH)

add_executable(run_tests.elf src/test_utility.c)
target_include_directories(run_tests.elf PRIVATE include .)
target_compile_definitions(run_tests.elf PRIVATE M4_MODARITH_TEST)
target_link_libraries(run_tests.elf PRIVATE unity mini-gmp)

foreach(PRIME REDUCTION IN ZIP_LISTS PRIMES_PSEUDO_MONTY PRIMES_PSEUDO_MONTY_REDUCTION)
    generate_modarith_code_for_named_prime(modarith-bench ${PRIME} pseudo)
    generate_modarith_code_for_named_prime(modarith-bench ${PRIME} monty)
    generate_m4_code_for_named_prime(run_tests.elf m4-bench ${PRIME} ${REDUCTION})
    generate_m4_code_for_named_prime(run_tests.elf m4-bench ${PRIME} mont)
endforeach()

foreach(PRIME REDUCTION IN ZIP_LISTS PRIMES_M4_EXTRA PRIMES_M4_EXTRA_REDUCTION)
    generate_m4_code_for_named_prime(run_tests.elf m4-bench ${PRIME} ${REDUCTION})
    generate_m4_code_for_named_prime(run_tests.elf m4-bench ${PRIME} mont)
endforeach()

foreach(PRIME ${PRIMES_MONTY})
    generate_modarith_code_for_named_prime(modarith-bench ${PRIME} monty)
    generate_m4_code_for_named_prime(run_tests.elf m4-bench ${PRIME} mont)
endforeach()

foreach(PRIME ${PRIMES_CUSTOM_MONTY})
    register_m4_custom_code_for_named_prime(run_tests.elf m4-bench ${PRIME} mont)
endforeach()

foreach(PRIME REDUCTION IN ZIP_LISTS PRIMES_CUSTOM_PSEUDO PRIMES_CUSTOM_PSEUDO_REDUCTION)
    register_m4_custom_code_for_named_prime(run_tests.elf m4-bench ${PRIME} ${REDUCTION})
endforeach()

set(RFC7748_CODEGENS modarith modarith m4 m4 m4 m4)
set(RFC7748_CURVES C25519 C448 C25519 C25519_CUSTOM C448 C448_CUSTOM)

foreach(CODEGEN CURVE IN ZIP_LISTS RFC7748_CODEGENS RFC7748_CURVES)
    string(TOUPPER ${CODEGEN} CODEGEN_UPPER)
    string(TOUPPER ${CURVE} CURVE_UPPER)

    add_library(rfc7748-${CODEGEN}-${CURVE} STATIC src/rfc7748.c)

    target_include_directories(rfc7748-${CODEGEN}-${CURVE} PUBLIC .)
    target_compile_definitions(rfc7748-${CODEGEN}-${CURVE} PUBLIC RFC7748_${CODEGEN_UPPER} RFC7748_${CURVE_UPPER})

    foreach(APPLICATION bench test)
        add_library(rfc7748-${CODEGEN}-${CURVE}-${APPLICATION} STATIC src/test_bench_rfc7748.c)
        target_link_libraries(rfc7748-${CODEGEN}-${CURVE}-${APPLICATION} PRIVATE rfc7748-${CODEGEN}-${CURVE})
    endforeach()

    target_compile_definitions(rfc7748-${CODEGEN}-${CURVE}-bench PRIVATE M4_MODARITH_BENCH)
    add_dependencies(rfc7748-${CODEGEN}-${CURVE}-bench ${CODEGEN}-bench)
    target_link_libraries(bench.elf PRIVATE rfc7748-${CODEGEN}-${CURVE}-bench)

    target_compile_definitions(rfc7748-${CODEGEN}-${CURVE}-test PRIVATE M4_MODARITH_TEST)
    target_link_libraries(rfc7748-${CODEGEN}-${CURVE}-test PRIVATE unity)
    target_link_libraries(run_tests.elf PRIVATE rfc7748-${CODEGEN}-${CURVE}-test)
endforeach()

# Set up dependencies to ensure correct build order
set(RFC7748_TARGETS
    modarith-C25519 modarith-C448
    m4-C25519 m4-C448)
set(RFC7748_SOURCES
    modarith-codegen/code_C25519_pseudo.c modarith-codegen/code_C448_monty.c
    m4-codegen/code_C25519_pmp_asm.c m4-codegen/code_C448_mont.c)

foreach(TARGET SOURCE IN ZIP_LISTS RFC7748_TARGETS RFC7748_SOURCES)
    add_custom_target(rfc7748-${TARGET}-code DEPENDS ${SOURCE})

    add_dependencies(rfc7748-${TARGET} rfc7748-${TARGET}-code)
endforeach()

target_sources(run_tests.elf PRIVATE src/tests_rfc7748.c)

generate_benchmarks_for_modarith(modarith-bench)
generate_tests_for_m4(run_tests.elf)
generate_benchmarks_for_m4(m4-bench)

add_subdirectory(m4-external)

add_test(NAME run_tests COMMAND run_tests.elf)
