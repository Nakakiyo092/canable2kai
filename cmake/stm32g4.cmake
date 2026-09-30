# STM32G4 family: CPU flags, CMSIS and HAL.
#
# stm32g4_cpu     INTERFACE  CPU flags for compiling and linking
# stm32g4xx_hal   STATIC     HAL driver (all sources; unused objects are
#                            dropped by the linker)
#
# The HAL is configured by stm32g4xx_hal_conf.h, which the application
# provides through FW_CONFIG_TARGET (include path and definitions).

set(STM32G4_LIB_DIR ${CMAKE_SOURCE_DIR}/lib)

add_library(stm32g4_cpu INTERFACE)
target_compile_options(stm32g4_cpu INTERFACE -mcpu=cortex-m4 -mthumb)
target_link_options(stm32g4_cpu INTERFACE -mcpu=cortex-m4 -mthumb)
target_include_directories(stm32g4_cpu INTERFACE
    ${STM32G4_LIB_DIR}/cmsis_core/Include
    ${STM32G4_LIB_DIR}/cmsis_device_g4/Include
    ${STM32G4_LIB_DIR}/stm32g4xx_hal_driver/Inc
)

file(GLOB STM32G4_HAL_SOURCES CONFIGURE_DEPENDS
    ${STM32G4_LIB_DIR}/stm32g4xx_hal_driver/Src/*.c)
add_library(stm32g4xx_hal STATIC ${STM32G4_HAL_SOURCES})
target_link_libraries(stm32g4xx_hal PUBLIC stm32g4_cpu ${FW_CONFIG_TARGET})
