set(SCRIPTS_DIR scripts)
set(SRC_DIR src)
set(MODARITH_DIR modarith)
set(MODARITH_OUTPUT_DIR modarith-codegen)
set(MODARITH_BENCH_DIR modarith-bench)
set(MODARITH_TEMP_DIR temp-modarith)

set(SCRIPTS_DIR_FULL ${PROJECT_SOURCE_DIR}/${SCRIPTS_DIR})
set(MODARITH_DIR_FULL ${PROJECT_SOURCE_DIR}/${MODARITH_DIR})
set(MODARITH_OUTPUT_DIR_FULL ${PROJECT_SOURCE_DIR}/${MODARITH_OUTPUT_DIR})
set(MODARITH_BENCH_DIR_FULL ${PROJECT_SOURCE_DIR}/${MODARITH_BENCH_DIR})
set(MODARITH_TEMP_DIR_FULL ${PROJECT_BINARY_DIR}/${MODARITH_TEMP_DIR})

if(NOT EXISTS "${MODARITH_DIR}/monty.py")
    execute_process(COMMAND git submodule update --init --recursive)
endif()

# add_custom_command(
# OUTPUT ${MODARITH_DIR}/monty.py ${MODARITH_DIR}/pseudo.py
# COMMAND python3 ${PROJECT_SOURCE_DIR}/scripts/override-modarith-settings.py
# WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${MODARITH_DIR}
# VERBATIM
# )
if(REGEN_MODARITH_CODE)
    execute_process(
        COMMAND python3 ${SCRIPTS_DIR_FULL}/override-modarith-settings.py
        WORKING_DIRECTORY ${MODARITH_DIR_FULL}
    )
endif()

macro(generate_modarith_code_for_named_prime TGT PNAME PTYPE)
    # To prevent weird file names
    string(REGEX REPLACE "[^a-zA-Z0-9]" "" SANITIZED_PNAME "${PNAME}")
    string(SUBSTRING "${SANITIZED_PNAME}" 0 10 SANITIZED_PNAME)


    set(MODARITH_SRC ${MODARITH_OUTPUT_DIR_FULL}/code_${SANITIZED_PNAME}_${PTYPE}.c)
    set(MODARITH_BENCH_SRC ${MODARITH_BENCH_DIR_FULL}/bench_${SANITIZED_PNAME}_${PTYPE}.c)
    set(TEMP_MODARITH_SRC ${MODARITH_TEMP_DIR_FULL}/${SANITIZED_PNAME}_${PTYPE}/field.c)

    if(REGEN_MODARITH_CODE)
        file(MAKE_DIRECTORY ${MODARITH_TEMP_DIR_FULL}/${SANITIZED_PNAME}_${PTYPE})

        add_custom_command(
            OUTPUT ${MODARITH_SRC} ${MODARITH_BENCH_SRC}
            # In case of failure running Mike's script, remove /dev/null from the line
            # below to troubleshoot
            COMMAND python3 ${MODARITH_DIR_FULL}/${PTYPE}.py 32 ${PNAME} > /dev/null
            COMMAND ${CMAKE_COMMAND} -E rename ${TEMP_MODARITH_SRC} ${MODARITH_SRC}
            COMMAND ${CMAKE_COMMAND} -E remove time.c
            COMMAND
                python3
                ${SCRIPTS_DIR_FULL}/gen-benchmarks-for-modarith.py
                ${MODARITH_OUTPUT_DIR_FULL}
                ${MODARITH_BENCH_DIR_FULL}
                ${PNAME}
                ${PTYPE}
            COMMENT "Generating ${MODARITH_SRC} and ${MODARITH_BENCH_SRC}"
            WORKING_DIRECTORY ${MODARITH_TEMP_DIR_FULL}/${SANITIZED_PNAME}_${PTYPE}
            DEPENDS ${MODARITH_DIR}/${PTYPE}.py ${SCRIPTS_DIR}/gen-benchmarks-for-modarith.py
            VERBATIM
        )
    endif()

    target_sources(${TGT} PRIVATE ${MODARITH_BENCH_DIR}/bench_${SANITIZED_PNAME}_${PTYPE}.c)

    list(APPEND MODARITH_PNAMES ${PNAME})
    list(APPEND MODARITH_PTYPES ${PTYPE})
endmacro()

macro(generate_benchmarks_for_modarith TGT)
    set(MODARITH_BENCH_SRC ${MODARITH_BENCH_DIR}/bench_modarith.c)
    set(RFC7748_CURVES C25519 C448)
    file(WRITE ${MODARITH_BENCH_SRC} "")

    foreach(PNAME PTYPE IN ZIP_LISTS MODARITH_PNAMES MODARITH_PTYPES)
        string(REGEX REPLACE "[^a-zA-Z0-9]" "" SANITIZED_PNAME "${PNAME}")
        string(SUBSTRING "${SANITIZED_PNAME}" 0 10 SANITIZED_PNAME)
        file(APPEND ${MODARITH_BENCH_SRC} "void bench_modarith_${SANITIZED_PNAME}_${PTYPE}(void);
")
    endforeach()

    foreach(CURVE ${RFC7748_CURVES})
        file(APPEND ${MODARITH_BENCH_SRC} "void bench_modarith_rfc7748_${CURVE}(void);
")
    endforeach()

    file(APPEND ${MODARITH_BENCH_SRC} "
void bench_modarith(void) {")

    foreach(PNAME PTYPE IN ZIP_LISTS MODARITH_PNAMES MODARITH_PTYPES)
        string(REGEX REPLACE "[^a-zA-Z0-9]" "" SANITIZED_PNAME "${PNAME}")
        string(SUBSTRING "${SANITIZED_PNAME}" 0 10 SANITIZED_PNAME)
        file(APPEND ${MODARITH_BENCH_SRC} "
    bench_modarith_${SANITIZED_PNAME}_${PTYPE}();")
    endforeach()

    foreach(CURVE ${RFC7748_CURVES})
        file(APPEND ${MODARITH_BENCH_SRC} "
    bench_modarith_rfc7748_${CURVE}();")
    endforeach()

    file(APPEND ${MODARITH_BENCH_SRC} "\n}\n")

    target_sources(${TGT} PRIVATE ${MODARITH_BENCH_SRC})
endmacro()
