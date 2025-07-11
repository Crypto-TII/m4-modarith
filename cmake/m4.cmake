set(SCRIPTS_DIR scripts)
set(SRC_DIR src)
set(M4_CODEGEN_DIR m4-codegen)
set(M4_CUSTOM_DIR m4-custom)
set(M4_TESTS_DIR m4-tests)
set(M4_BENCH_DIR m4-bench)

set(SCRIPTS_DIR_FULL ${PROJECT_SOURCE_DIR}/${SCRIPTS_DIR})
set(M4_CODEGEN_DIR_FULL ${PROJECT_SOURCE_DIR}/${M4_CODEGEN_DIR})
set(M4_CUSTOM_DIR_FULL ${PROJECT_SOURCE_DIR}/${M4_CUSTOM_DIR})
set(M4_TESTS_DIR_FULL ${PROJECT_SOURCE_DIR}/${M4_TESTS_DIR})
set(M4_BENCH_DIR_FULL ${PROJECT_SOURCE_DIR}/${M4_BENCH_DIR})

set(M4_TEMP_DIR temp-m4)
set(M4_TEMP_DIR_FULL ${PROJECT_BINARY_DIR}/${M4_TEMP_DIR})

macro(generate_m4_tests_and_benchmarks M4_SRC_FULL M4_TEST_SRC_FULL M4_BENCH_SRC_FULL PNAME PTYPE IMPLTYPE)
    add_custom_command(
        OUTPUT ${M4_TEST_SRC_FULL} ${M4_BENCH_SRC_FULL}
        COMMAND python3 ${SCRIPTS_DIR_FULL}/m4test.py ${PNAME} ${PTYPE} ${IMPLTYPE} > ${M4_TEST_SRC_FULL}
        COMMAND python3 ${SCRIPTS_DIR_FULL}/gen-benchmarks-for-m4.py ${M4_BENCH_DIR_FULL} ${PNAME} ${PTYPE} ${IMPLTYPE}
        COMMENT "Generating ${M4_TEST_SRC_FULL} and ${M4_BENCH_SRC_FULL}"
        DEPENDS ${M4_SRC_FULL} ${SCRIPTS_DIR}/m4test.py ${SCRIPTS_DIR}/gen-benchmarks-for-m4.py
        VERBATIM
    )
endmacro()

macro(generate_m4_code_for_named_prime TARGET_TEST TARGET_BENCH PNAME PTYPE)
    # To prevent weird file names
    string(REGEX REPLACE "[^a-zA-Z0-9]" "" SANITIZED_PNAME "${PNAME}")
    string(SUBSTRING "${SANITIZED_PNAME}" 0 10 SANITIZED_PNAME)

    set(M4_SRC code_${SANITIZED_PNAME}_${PTYPE}.c)
    set(M4_TEST_SRC test_${SANITIZED_PNAME}_${PTYPE}.c)
    set(M4_BENCH_SRC bench_${SANITIZED_PNAME}_${PTYPE}.c)

    set(M4_SRC_FULL ${M4_CODEGEN_DIR_FULL}/${M4_SRC})
    set(M4_TEST_SRC_FULL ${M4_TESTS_DIR_FULL}/${M4_TEST_SRC})
    set(M4_BENCH_SRC_FULL ${M4_BENCH_DIR_FULL}/${M4_BENCH_SRC})

    file(MAKE_DIRECTORY ${M4_TEMP_DIR_FULL}/${SANITIZED_PNAME}_${PTYPE})

    add_custom_command(
        OUTPUT ${M4_SRC_FULL}
        COMMAND python3 ${SCRIPTS_DIR_FULL}/m4generator.py ${PNAME} ${PTYPE} > ${M4_SRC_FULL}
        WORKING_DIRECTORY ${M4_TEMP_DIR_FULL}/${SANITIZED_PNAME}_${PTYPE}
        COMMENT "Generating ${M4_SRC_FULL}"
        DEPENDS ${SCRIPTS_DIR}/m4generator.py
        VERBATIM
    )

    generate_m4_tests_and_benchmarks(${M4_SRC_FULL} ${M4_TEST_SRC_FULL} ${M4_BENCH_SRC_FULL} ${PNAME} ${PTYPE} codegen)

    target_sources(${TARGET_TEST} PRIVATE ${M4_TESTS_DIR}/${M4_TEST_SRC})
    target_sources(${TARGET_BENCH} PRIVATE ${M4_BENCH_DIR}/${M4_BENCH_SRC})

    list(APPEND M4_PNAMES ${PNAME})
    list(APPEND M4_PTYPES ${PTYPE})
    list(APPEND M4_IMPLTYPES codegen)
endmacro()

macro(register_m4_custom_code_for_named_prime TARGET_TEST TARGET_BENCH PNAME PTYPE)
    string(REGEX REPLACE "[^a-zA-Z0-9]" "" SANITIZED_PNAME "${PNAME}")
    string(SUBSTRING "${SANITIZED_PNAME}" 0 10 SANITIZED_PNAME)

    set(M4_SRC code_${SANITIZED_PNAME}_${PTYPE}.c)
    set(M4_TEST_SRC test_${SANITIZED_PNAME}_${PTYPE}_custom.c)
    set(M4_BENCH_SRC bench_${SANITIZED_PNAME}_${PTYPE}_custom.c)

    set(M4_SRC_FULL ${M4_CUSTOM_DIR_FULL}/${M4_SRC})
    set(M4_TEST_SRC_FULL ${M4_TESTS_DIR_FULL}/${M4_TEST_SRC})
    set(M4_BENCH_SRC_FULL ${M4_BENCH_DIR_FULL}/${M4_BENCH_SRC})

    generate_m4_tests_and_benchmarks(${M4_SRC_FULL} ${M4_TEST_SRC_FULL} ${M4_BENCH_SRC_FULL} ${PNAME} ${PTYPE} custom)

    target_sources(${TARGET_TEST} PRIVATE ${M4_TESTS_DIR}/${M4_TEST_SRC})
    target_sources(${TARGET_BENCH} PRIVATE ${M4_BENCH_DIR}/${M4_BENCH_SRC})

    list(APPEND M4_PNAMES ${PNAME})
    list(APPEND M4_PTYPES ${PTYPE})
    list(APPEND M4_IMPLTYPES custom)
endmacro()

macro(impltype_to_suffix IMPLTYPE IMPLTYPE_SUFFIX)
    if(${IMPLTYPE} STREQUAL "codegen")
        set(${IMPLTYPE_SUFFIX} "")
    else()
        set(${IMPLTYPE_SUFFIX} "_custom")
    endif()
endmacro()

macro(generate_tests_for_m4 TARGET_TEST)
    set(M4_TEST_SRC ${M4_TESTS_DIR}/test_m4.c)
    file(WRITE ${M4_TEST_SRC} "#include \"hal.h\"
#include \"unity.h\"
#include \"mini-gmp.h\"
#include \"test_utility.h\"

gmp_randstate_t state;
mpz_t a_mpz, b_mpz, c_mpz, r_mpz, rinv_mpz, w_mpz, lim_mpz, zero_mpz, usedprime, realprime, maxbound;

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

")

    foreach(PNAME PTYPE IMPLTYPE IN ZIP_LISTS M4_PNAMES M4_PTYPES M4_IMPLTYPES)
        impltype_to_suffix(IMPLTYPE IMPLTYPE_SUFFIX)
        string(REGEX REPLACE "[^a-zA-Z0-9]" "" SANITIZED_PNAME "${PNAME}")
        string(SUBSTRING "${SANITIZED_PNAME}" 0 10 SANITIZED_PNAME)
        file(APPEND ${M4_TEST_SRC} "void test_${SANITIZED_PNAME}_${PTYPE}_ct${IMPLTYPE_SUFFIX}(void);
")
    endforeach()

    file(APPEND ${M4_TEST_SRC} "void test_rfc7748(void);
void test_external(void);

int main(void) {
    hal_setup(CLOCK_FAST);

    gmp_randinit_default(state);
    mpz_init(a_mpz);
    mpz_init(b_mpz);
    mpz_init(c_mpz);
    mpz_init(r_mpz);
    mpz_init(rinv_mpz);
    mpz_init(w_mpz);
    mpz_init(lim_mpz);
    mpz_init_set_ui(zero_mpz, 0);
    mpz_init(usedprime);
    mpz_init(realprime);
    mpz_init(maxbound);

    test_utility_init();

    UNITY_BEGIN();
")

    foreach(PNAME PTYPE IMPLTYPE IN ZIP_LISTS M4_PNAMES M4_PTYPES M4_IMPLTYPES)
        impltype_to_suffix(IMPLTYPE IMPLTYPE_SUFFIX)
        string(REGEX REPLACE "[^a-zA-Z0-9]" "" SANITIZED_PNAME "${PNAME}")
        string(SUBSTRING "${SANITIZED_PNAME}" 0 10 SANITIZED_PNAME)
        file(APPEND ${M4_TEST_SRC} "
    test_${SANITIZED_PNAME}_${PTYPE}_ct${IMPLTYPE_SUFFIX}();")
    endforeach()

    file(APPEND ${M4_TEST_SRC} "
    test_rfc7748();
    test_external();

    gmp_randclear(state);
    mpz_clear(a_mpz);
    mpz_clear(b_mpz);
    mpz_clear(c_mpz);
    mpz_clear(w_mpz);
    mpz_clear(lim_mpz);
    mpz_clear(zero_mpz);
    mpz_clear(usedprime);
    mpz_clear(realprime);
    mpz_clear(maxbound);

    test_utility_clear();

    hal_exit_(UNITY_END());

    // Unreachable
    return 0;
}
")

    target_sources(${TARGET_TEST} PRIVATE ${M4_TEST_SRC})
endmacro()

macro(generate_benchmarks_for_m4 TARGET_BENCH)
    set(M4_BENCH_SRC ${M4_BENCH_DIR}/bench_m4.c)
    set(RFC7748_CURVES C25519 C25519_custom C448 C448_custom)
    file(WRITE ${M4_BENCH_SRC} "void setUp(void) { // needed for Unity, which we had to link due to RFC7748
    // set stuff up here
}

void tearDown(void) { // needed for Unity, which we had to link due to RFC7748
    // clean stuff up here
}

")

    foreach(PNAME PTYPE IMPLTYPE IN ZIP_LISTS M4_PNAMES M4_PTYPES M4_IMPLTYPES)
        impltype_to_suffix(IMPLTYPE IMPLTYPE_SUFFIX)
        string(REGEX REPLACE "[^a-zA-Z0-9]" "" SANITIZED_PNAME "${PNAME}")
        string(SUBSTRING "${SANITIZED_PNAME}" 0 10 SANITIZED_PNAME)
        file(APPEND ${M4_BENCH_SRC} "void bench_m4_${SANITIZED_PNAME}_${PTYPE}${IMPLTYPE_SUFFIX}(void);
")
    endforeach()

    foreach(CURVE ${RFC7748_CURVES})
        file(APPEND ${M4_BENCH_SRC} "void bench_m4_rfc7748_${CURVE}(void);
")
    endforeach()

    file(APPEND ${M4_BENCH_SRC} "void bench_external(void);

void bench_m4(void) {
")

    foreach(PNAME PTYPE IMPLTYPE IN ZIP_LISTS M4_PNAMES M4_PTYPES M4_IMPLTYPES)
        impltype_to_suffix(IMPLTYPE IMPLTYPE_SUFFIX)
        string(REGEX REPLACE "[^a-zA-Z0-9]" "" SANITIZED_PNAME "${PNAME}")
        string(SUBSTRING "${SANITIZED_PNAME}" 0 10 SANITIZED_PNAME)
        file(APPEND ${M4_BENCH_SRC} "    bench_m4_${SANITIZED_PNAME}_${PTYPE}${IMPLTYPE_SUFFIX}();
")
    endforeach()

    foreach(CURVE ${RFC7748_CURVES})
        file(APPEND ${M4_BENCH_SRC} "
    bench_m4_rfc7748_${CURVE}();")
    endforeach()

    file(APPEND ${M4_BENCH_SRC} "
    bench_external();
}
")

    target_sources(${TARGET_BENCH} PRIVATE ${M4_BENCH_SRC})
endmacro()
