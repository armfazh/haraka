cmake_minimum_required(VERSION 3.0)
project(aesni_optimized, C)

set(CMAKE_C_FLAGS "-O3 -march=native -mtune=native -fomit-frame-pointer")
set(SOURCE_FILES
        haraka.c
        haraka.h
        main.c
        timing.h)

add_executable(aesni_optimized ${SOURCE_FILES})