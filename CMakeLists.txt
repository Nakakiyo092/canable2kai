cmake_minimum_required(VERSION 3.25)

project(canable2kai C ASM)

# Board selection. Use a preset (cmake --list-presets) instead of setting
# BOARD directly.
set(BOARD "" CACHE STRING "Target board")
if(NOT BOARD STREQUAL "canable2")
    message(FATAL_ERROR
        "Unsupported BOARD \"${BOARD}\". Configure with a preset (cmake --list-presets).")
endif()

set(FW_NAME ${BOARD})
set(FW_OUT_BASE ${CMAKE_BINARY_DIR}/${FW_NAME})
set(USB_DIR ${CMAKE_SOURCE_DIR}/lib/stm32_mw_usb_device)

# Settings shared by the application and the libraries.
# inc/ provides stm32g4xx_hal_conf.h and usbd_conf.h to the libraries.
add_library(fw_config INTERFACE)
target_compile_options(fw_config INTERFACE
    -Wall -g -ffunction-sections -fdata-sections -Os)
target_compile_definitions(fw_config INTERFACE
    STM32G431xx HSI48_VALUE=48000000 HSE_VALUE=16000000)
target_include_directories(fw_config INTERFACE
    ${CMAKE_SOURCE_DIR}/inc
    ${USB_DIR}/Core/Inc
    ${USB_DIR}/Class/CDC/Inc)
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
    src/usbd_conf.c
    src/usbd_cdc_if.c
    src/usb_device.c
    src/usbd_desc.c
    src/buffer.c
    src/can.c
    src/generator.c
    src/led.c
    src/nvm.c
    src/parser.c
    src/startup_stm32g431xx.s
    ${USB_DIR}/Core/Src/usbd_ctlreq.c
    ${USB_DIR}/Core/Src/usbd_ioreq.c
    ${USB_DIR}/Core/Src/usbd_core.c
    ${USB_DIR}/Class/CDC/Src/usbd_cdc.c
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
