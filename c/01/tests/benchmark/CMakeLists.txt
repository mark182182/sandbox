# Uses a specific CMakeLists.txt to build benchmark tests that does not run as the part of the main test suite.

file(GLOB_RECURSE RENDERER_SRC "../../src/*.c")
list(FILTER RENDERER_SRC EXCLUDE REGEX ".*/main\\.c$")

file(GLOB BENCHMARK_TESTS "*.c")
foreach(test_file ${BENCHMARK_TESTS})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name}_benchmark ${test_file} ${RENDERER_SRC})
    target_include_directories(${test_name}_benchmark PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(${test_name}_benchmark
        raylib
        kernel32
        user32
        gdi32
        winmm
        shell32
    )
endforeach()