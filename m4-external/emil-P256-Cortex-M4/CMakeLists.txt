if(USE_EXTERNAL_EMIL_P256_M4)
    add_library(external-emil-p256-m4 STATIC benchmark.c p256-cortex-m4-asm-gcc.S p256-cortex-m4.c)
    target_include_directories(external-emil-p256-m4 PUBLIC .)
    target_compile_definitions(external-emil-p256-m4 PUBLIC EXTERNAL_EMIL_P256_M4)
    target_compile_definitions(external-emil-p256-m4 PRIVATE has_fpu=0)
endif()


if(USE_EXTERNAL_EMIL_P256_M4F)
    add_library(external-emil-p256-m4f STATIC benchmark.c p256-cortex-m4-asm-gcc.S p256-cortex-m4.c)
    target_include_directories(external-emil-p256-m4f PUBLIC .)
    target_compile_definitions(external-emil-p256-m4f PUBLIC EXTERNAL_EMIL_P256_M4F)
    target_compile_definitions(external-emil-p256-m4f PRIVATE has_fpu=1)
endif()
