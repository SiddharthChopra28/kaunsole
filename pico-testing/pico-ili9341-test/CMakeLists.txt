cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_ili9341_test C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

pico_sdk_init()

add_subdirectory(../pico-displayDrivs/ili9341 ili9341)
add_subdirectory(../pico-displayDrivs/gfx gfx)

# ponytail: keep the unmodified driver's legacy pointer calls buildable; fix signatures in the driver if maintained.
target_compile_options(ili9341 PRIVATE -Wno-incompatible-pointer-types)

set(GFX_COMPAT_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/gfx_compat.h)
target_compile_options(gfx PRIVATE
        $<$<COMPILE_LANGUAGE:C>:-include${GFX_COMPAT_HEADER}>
        )
target_link_libraries(gfx ili9341)

set(CHR_BIN ${CMAKE_CURRENT_BINARY_DIR}/smb3_chr)
set(CHR_OBJ ${CMAKE_CURRENT_BINARY_DIR}/smb3_chr.o)
add_custom_command(
        OUTPUT ${CHR_OBJ}
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/../../roms/smb3/assets/smb3_chr.bin
                ${CHR_BIN}
        COMMAND arm-none-eabi-objcopy -I binary -O elf32-littlearm -B arm
                smb3_chr smb3_chr.o
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../../roms/smb3/assets/smb3_chr.bin
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM
        )

add_executable(pico_ili9341_test
        ../../src/audio.c
        ../../src/collision.c
        ../../src/engine.c
        ../../src/graphics.c
        ../../src/backends/pico.c
        ../../roms/smb3/main.c
        ../../roms/smb3/camera.c
        ${CHR_OBJ}
        )
target_compile_definitions(pico_ili9341_test PRIVATE
        STATIC_ROM
        PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS=5000
        )

target_link_libraries(pico_ili9341_test pico_stdlib ili9341 gfx)

pico_enable_stdio_uart(pico_ili9341_test 0)
pico_enable_stdio_usb(pico_ili9341_test 1)

pico_add_extra_outputs(pico_ili9341_test)
