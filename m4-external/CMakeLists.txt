option(USE_EXTERNAL_EMIL_P256_M4 "Include benchmarks and tests for Emil Lenngren's P256 M4 implementation" OFF)
option(USE_EXTERNAL_EMIL_P256_M4F "Include benchmarks and tests for Emil Lenngren's P256 M4F implementation" ON)
option(USE_EXTERNAL_EMIL_X25519_M4 "Include benchmarks and tests for Emil Lenngren's X25519 M4 implementation" ON)
option(USE_EXTERNAL_EMIL_X25519_M4F "Include benchmarks and tests for Emil Lenngren's X25519 M4F implementation" ON)
option(USE_EXTERNAL_FIAT "Include benchmarks for Fiat Crypto" ON)
option(USE_EXTERNAL_P256_M "Include benchmarks for p256-m code" ON)
option(USE_EXTERNAL_HAASE "Include benchmarks for Bjoern Haase code" ON)
option(USE_EXTERNAL_MSRECC "Include benchmarks for MSRECC code" ON)

add_subdirectory(emil-P256-Cortex-M4)
add_subdirectory(emil-X25519-Cortex-M4)
add_subdirectory(fiat-crypto)
add_subdirectory(p256-m)
add_subdirectory(BjoernMHaase)
add_subdirectory(MSRECC)

foreach(LIBRARY external-bench external-test)
    add_library(${LIBRARY} STATIC ${LIBRARY}.c)

    if(USE_EXTERNAL_EMIL_X25519_M4)
        target_compile_definitions(${LIBRARY} PRIVATE EXTERNAL_EMIL_X25519_M4)
        target_link_libraries(${LIBRARY} PRIVATE external-emil-x25519-m4-test-bench)
    endif()

    if(USE_EXTERNAL_EMIL_X25519_M4F)
        target_compile_definitions(${LIBRARY} PRIVATE EXTERNAL_EMIL_X25519_M4F)
        target_link_libraries(${LIBRARY} PRIVATE external-emil-x25519-m4f-test-bench)
    endif()
endforeach()

if(USE_EXTERNAL_EMIL_P256_M4)
    target_compile_definitions(external-bench PRIVATE EXTERNAL_EMIL_P256_M4)
    target_link_libraries(external-bench PRIVATE external-emil-p256-m4)
endif()

if(USE_EXTERNAL_EMIL_P256_M4F)
    target_compile_definitions(external-bench PRIVATE EXTERNAL_EMIL_P256_M4F)
    target_link_libraries(external-bench PRIVATE external-emil-p256-m4f)
endif()

if(USE_EXTERNAL_FIAT)
    target_compile_definitions(external-bench PRIVATE EXTERNAL_FIAT)
    target_link_libraries(external-bench PRIVATE external-fiat)
endif()

if(USE_EXTERNAL_HAYATO)
    target_compile_definitions(external-bench PRIVATE EXTERNAL_HAYATO)
    target_link_libraries(external-bench PRIVATE external-hayato)
endif()

if(USE_EXTERNAL_P256_M)
    target_compile_definitions(external-bench PRIVATE EXTERNAL_P256_M)
    target_link_libraries(external-bench PRIVATE external-p256-m)
endif()

if(USE_EXTERNAL_HAASE)
    target_compile_definitions(external-bench PRIVATE EXTERNAL_HAASE)
    target_link_libraries(external-bench PRIVATE external-haase)
endif()

if(USE_EXTERNAL_AZARDERAKHSH)
    target_compile_definitions(external-bench PRIVATE EXTERNAL_AZARDERAKHSH)
    target_link_libraries(external-bench PRIVATE external-azarderakhsh)
endif()

if(USE_EXTERNAL_MSRECC)
    target_compile_definitions(external-bench PRIVATE EXTERNAL_MSRECC)
    target_link_libraries(external-bench PRIVATE external-msrecc)
endif()

if(USE_EXTERNAL_UECC)
    target_compile_definitions(external-bench PRIVATE EXTERNAL_UECC)
    target_link_libraries(external-bench PRIVATE external-uecc)
endif()

target_link_libraries(external-test PRIVATE unity)

target_link_libraries(m4-bench PRIVATE external-bench)
target_link_libraries(run_tests.elf PRIVATE external-test)
