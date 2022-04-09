cmake_minimum_required(VERSION 3.21)
project(lab3 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab3
        task0a/lab3_mergesort.c task0b/hexaPrint.c task1a/virusDetector.c task1b/virusDetector.c task1c/virusDetector.c)
