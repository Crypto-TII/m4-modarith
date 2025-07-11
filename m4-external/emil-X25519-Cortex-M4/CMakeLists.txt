if(USE_EXTERNAL_EMIL_X25519_M4)
    add_library(external-emil-x25519-m4 STATIC x25519-cortex-m4-gcc.s)
    target_include_directories(external-emil-x25519-m4 PUBLIC .)
    target_compile_definitions(external-emil-x25519-m4 PUBLIC EXTERNAL_EMIL_X25519_M4)

    add_library(external-emil-x25519-m4-test-bench STATIC benchmark.c test.c)
    target_link_libraries(external-emil-x25519-m4-test-bench PRIVATE external-emil-x25519-m4 unity)
endif()

if(USE_EXTERNAL_EMIL_X25519_M4F)
    add_library(external-emil-x25519-m4f STATIC curve25519-m4f-ptrswap-gcc.s)
    target_include_directories(external-emil-x25519-m4f PUBLIC .)
    target_compile_definitions(external-emil-x25519-m4f PUBLIC EXTERNAL_EMIL_X25519_M4F)

    add_library(external-emil-x25519-m4f-test-bench STATIC benchmark.c test.c)
    target_link_libraries(external-emil-x25519-m4f-test-bench PRIVATE external-emil-x25519-m4f unity)
endif()
