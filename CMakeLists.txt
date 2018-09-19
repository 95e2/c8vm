cmake_minimum_required(VERSION 3.8)
project(c8vm)

if(NOT DEFINED CC)
    set(CMAKE_C_COMPILER clang)
endif()
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-g -Wall -O2 -D_DEBUG")

set(SOURCE_FILES c8vm.c c8vm.h cpu.c cpu.h mem.c mem.h rom.c rom.h)
add_executable(c8vm ${SOURCE_FILES})
