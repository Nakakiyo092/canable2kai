# "upload" target: flashes the binary through the STM32 system bootloader
# (USB DFU). Enter the bootloader with the boot jumper before running it.
#
# fw_add_upload_target(<executable target>)

find_program(DFU_UTIL dfu-util)

function(fw_add_upload_target target)
    if(DFU_UTIL)
        add_custom_target(upload
            COMMAND ${DFU_UTIL} -w -d 0483:df11 -c 1 -i 0 -a 0
                    -s 0x08000000:leave -D ${CMAKE_BINARY_DIR}/${target}.bin
            DEPENDS ${target}
            USES_TERMINAL
        )
    else()
        add_custom_target(upload
            COMMAND ${CMAKE_COMMAND} -E echo "dfu-util not found in PATH"
            COMMAND ${CMAKE_COMMAND} -E false
            DEPENDS ${target}
        )
    endif()
endfunction()
