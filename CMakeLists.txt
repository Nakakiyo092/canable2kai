cmake_minimum_required(VERSION 3.25)

project(canable2kai C ASM)

# Board selection. Use a preset (cmake --list-presets) instead of setting
# BOARD directly.
set(BOARD "" CACHE STRING "Target board")
if(NOT BOARD STREQUAL "canable2")
    message(FATAL_ERROR
        "Unsupported BOARD \"${BOARD}\". Configure with a preset (cmake --list-presets).")
endif()

# Debug build: enables the debug-only commands used by the test suite.
option(FW_DEBUG "Enable debug-only commands (required by the tests)" OFF)

set(FW_NAME ${BOARD})
set(FW_OUT_BASE ${CMAKE_BINARY_DIR}/${FW_NAME})
set(TINYUSB_DIR ${CMAKE_SOURCE_DIR}/lib/tinyusb/src)
set(PRINTF_DIR ${CMAKE_SOURCE_DIR}/lib/printf/src)

# Settings shared by the application and the libraries.
# inc/ provides stm32g4xx_hal_conf.h and tusb_config.h to the libraries.
add_library(fw_config INTERFACE)
target_compile_options(fw_config INTERFACE
    -Wall -g -ffunction-sections -fdata-sections -Os)
target_compile_definitions(fw_config INTERFACE
    STM32G431xx HSI48_VALUE=48000000)
# printf: no aliasing of the standard names (call snprintf_() explicitly, so
# that a missing include cannot silently fall back to newlib's stdio) and no
# unused features.
# These must be the same for printf.c and for the code including printf.h.
target_compile_definitions(fw_config INTERFACE
    PRINTF_ALIAS_STANDARD_FUNCTION_NAMES_SOFT=0
    PRINTF_ALIAS_STANDARD_FUNCTION_NAMES_HARD=0
    PRINTF_SUPPORT_DECIMAL_SPECIFIERS=0
    PRINTF_SUPPORT_EXPONENTIAL_SPECIFIERS=0
    PRINTF_SUPPORT_MSVC_STYLE_INTEGER_SPECIFIERS=0
    PRINTF_SUPPORT_WRITEBACK_SPECIFIER=0
    PRINTF_SUPPORT_LONG_LONG=0)
target_include_directories(fw_config INTERFACE
    ${CMAKE_SOURCE_DIR}/inc
    ${TINYUSB_DIR}
    ${PRINTF_DIR})
set(FW_CONFIG_TARGET fw_config)

include(cmake/stm32g4.cmake)
include(cmake/upload.cmake)

find_program(ARM_SIZE arm-none-eabi-size REQUIRED)

add_executable(${FW_NAME}
    src/main.c
    src/system_stm32g4xx.c
    src/gpio.c
    src/fdcan.c
    src/tim.c
    src/interrupts.c
    src/usb_device.c
    src/usb_descriptors.c
    src/buffer.c
    src/can.c
    src/generator.c
    src/led.c
    src/nvm.c
    src/parser.c
    src/startup_stm32g431xx.s
    ${TINYUSB_DIR}/tusb.c
    ${TINYUSB_DIR}/common/tusb_fifo.c
    ${TINYUSB_DIR}/device/usbd.c
    ${TINYUSB_DIR}/class/cdc/cdc_device.c
    ${TINYUSB_DIR}/portable/st/stm32_fsdev/dcd_stm32_fsdev.c
    ${TINYUSB_DIR}/portable/st/stm32_fsdev/fsdev_common.c
    ${PRINTF_DIR}/printf/printf.c
)

# GIT_VERSION / GIT_REMOTE are regenerated at every build.
set(GIT_VERSION_HEADER ${CMAKE_BINARY_DIR}/generated/git_version.h)
add_custom_target(git_version
    COMMAND ${CMAKE_COMMAND}
        -DSOURCE_DIR=${CMAKE_SOURCE_DIR}
        -DOUTPUT=${GIT_VERSION_HEADER}
        -P ${CMAKE_SOURCE_DIR}/cmake/git_version.cmake
    BYPRODUCTS ${GIT_VERSION_HEADER}
)
add_dependencies(${FW_NAME} git_version)
target_compile_options(${FW_NAME} PRIVATE "SHELL:-include \"${GIT_VERSION_HEADER}\"")

if(FW_DEBUG)
    target_compile_definitions(${FW_NAME} PRIVATE DEBUG)
endif()

set(LD_SCRIPT ${CMAKE_SOURCE_DIR}/ldscripts/STM32G431CBTx_FLASH.ld)
target_link_options(${FW_NAME} PRIVATE
    -T${LD_SCRIPT}
    -static
    -fno-exceptions
    -Wl,--gc-sections
    -Wl,-Map=${FW_OUT_BASE}.map)
target_link_libraries(${FW_NAME} PRIVATE stm32g4xx_hal fw_config c m nosys)
set_target_properties(${FW_NAME} PROPERTIES
    LINK_DEPENDS ${LD_SCRIPT}
    ADDITIONAL_CLEAN_FILES ${FW_OUT_BASE}.map)

add_custom_command(TARGET ${FW_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${FW_NAME}> ${FW_OUT_BASE}.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${FW_NAME}> ${FW_OUT_BASE}.hex
    COMMAND ${ARM_SIZE} $<TARGET_FILE:${FW_NAME}>
    BYPRODUCTS ${FW_OUT_BASE}.bin ${FW_OUT_BASE}.hex
    VERBATIM
)

fw_add_upload_target(${FW_NAME})
