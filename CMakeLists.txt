cmake_minimum_required(VERSION 3.0.0)

#include toolchain first
set(CMAKE_TOOLCHAIN_FILE cmake/arm-gcc-toolchain.cmake)
include(${CMAKE_TOOLCHAIN_FILE})

#Project start
project(stm32f4_discovery VERSION 0.1.0)
enable_language(C CXX ASM)

#include toolchain first
set(CMAKE_TOOLCHAIN_FILE cmake/arm-gcc-toolchain.cmake)
include(${CMAKE_TOOLCHAIN_FILE})

set(TARGET stm32f4_discovery)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${TARGET} 
    src/CMSIS/device/ST/startup_stm32f407xx.s
    src/CMSIS/device/ST/system_stm32f4xx.c
    src/syscalls.c
    src/main.cpp
)
target_compile_definitions(${TARGET} PRIVATE 
    -DSTM32F407xx
)
target_include_directories(${TARGET} PUBLIC
    include
    include/CMSIS
    include/CMSIS/device/ST
)

target_compile_options(${TARGET} PRIVATE
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -fdata-sections
    -ffunction-sections
    -Wall
    $<$<CONFIG:Debug>:-Og>
)
target_link_options(${TARGET} PRIVATE
    -T${CMAKE_SOURCE_DIR}/STM32F407VGTx_FLASH.ld
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -specs=nano.specs
    -lc
    -lm
    -lnosys
    -Wl,-Map=${TARGET}.map,--cref
    -Wl,--gc-sections
)

#print size
add_custom_command(
    TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_SIZE_UTIL} ${TARGET}
)

#copy bin/hex
add_custom_command(
    TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${TARGET} ${TARGET}.bin
)

message("Build: ${CMAKE_BUILD_TYPE}")