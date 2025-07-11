# ################################################
# lib opencm3

set(OPENCM3DIR libopencm3)

if(BOARD MATCHES "STM32F4DISCOVERY")
    set(OPENCM3LIB opencm3_stm32f4)
    set(OPENCM3BUILD stm32/f4)
elseif(BOARD MATCHES "NUCLEO-L4R5ZI")
    set(OPENCM3LIB opencm3_stm32l4)
    set(OPENCM3BUILD stm32/l4)
else()
    message(FATAL_ERROR "Invalid development board: options available are STM32F4DISCOVERY or NUCLEO-L4R5ZI")
endif()

add_custom_target(buildlibopencm3 DEPENDS ${PROJECT_SOURCE_DIR}/${OPENCM3DIR}/lib/lib${OPENCM3LIB}.a)

# clone libopencm3 if the user forgot to do it
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/${OPENCM3DIR}/Makefile")
    execute_process(COMMAND git submodule update --init --recursive)
endif()

# build libopencm3
add_custom_command(
    OUTPUT ${PROJECT_SOURCE_DIR}/${OPENCM3DIR}/lib/lib${OPENCM3LIB}.a
    COMMAND make -C ${OPENCM3DIR} TARGETS=${OPENCM3BUILD}
    COMMENT "Building libopencm3"
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_library(libopencm3 STATIC IMPORTED GLOBAL)
add_dependencies(libopencm3 buildlibopencm3)
set_target_properties(libopencm3 PROPERTIES
    IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/${OPENCM3DIR}/lib/lib${OPENCM3LIB}.a

    # INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/${OPENCM3DIR}/include
)
set(LIBOPENCM3_INCLUDE ${PROJECT_SOURCE_DIR}/${OPENCM3DIR}/include)

# #####################################################
# option(USE_QEMU "Use qemu emulator for M4 target. It doesn't affect other targets" OFF)
if("${toolchain}" MATCHES "libopencm3")
    if("${toolchain}" STREQUAL "clang-libopencm3")
        add_compile_options(-Wno-unknown-attributes)
        link_libraries(-lcrt0 -lc -lm)
    elseif("${toolchain}" STREQUAL "arm-none-eabi-gcc-libopencm3")
        add_compile_options(-Wno-attributes)
    endif()

    add_link_options(-L${PROJECT_SOURCE_DIR}/libopencm3/lib)

    set(FULLRAM "")
    if(BOARD MATCHES "FULLRAM")
        set(FULLRAM "_fullram")
    endif()

    if(BOARD MATCHES "STM32F4DISCOVERY")
        message(STATUS "Building for development board STM32F4DISCOVERY")
        add_compile_definitions(STM32F4 STM32F4DISCOVERY)
        add_link_options(-T${PROJECT_SOURCE_DIR}/hw/stm32f4discovery${FULLRAM}.ld)
    elseif(BOARD MATCHES "NUCLEO-L4R5ZI")
        message(STATUS "Building for development board NUCLEO-L4R5ZI")
        add_compile_definitions(STM32L4 NUCLEO_L4R5ZI)
        add_link_options(-T${PROJECT_SOURCE_DIR}/hw/nucleo-l4r5zi${FULLRAM}.ld)
    endif()

    include_directories(${LIBOPENCM3_INCLUDE})
    link_libraries(libopencm3)
    add_library(hal_lib OBJECT ${PROJECT_SOURCE_DIR}/hw/hal.c ${PROJECT_SOURCE_DIR}/hw/syscall_wrappers.c)

    # disable cppcheck and clang-tidy for hal-stm32f4.c
    set_target_properties(hal_lib PROPERTIES C_CPPCHECK "" C_CLANG_TIDY "")
    link_libraries(hal_lib)
    set(EXT .bin)
endif()

# add_executable with additional objcopy step when needed
macro(add_executable)
    _add_executable(${ARGV})
    target_compile_definitions(${ARGV0} PRIVATE TARGET_NAME="${ARGV0}")

    if("${EXT}" STREQUAL ".bin") # add objcopy command
        string(REPLACE ".elf" ".bin" BIN_FILE ${ARGV0})

        add_custom_command(
            OUTPUT ${BIN_FILE}
            COMMENT "Generating ${BIN_FILE}"
            COMMAND ${CMAKE_OBJCOPY} -O binary ${ARGV0} ${BIN_FILE}
            DEPENDS ${ARGV0}
            VERBATIM)

        add_custom_target(objcopy_${BIN_FILE} ALL DEPENDS ${BIN_FILE})
    endif()
endmacro()

include_directories(${PROJECT_SOURCE_DIR}/hw)
