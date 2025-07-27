cmake_minimum_required(VERSION 3.11)
project(standalone_tests C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls ${COMMON_FLAGS}")

message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")

# Get all .c standalone test files in this directory
file(GLOB STANDALONE_FILES "*.c")

foreach(file ${STANDALONE_FILES})
    get_filename_component(test_name ${file} NAME_WE)
    add_executable(${test_name}_standalone ${file})
endforeach()