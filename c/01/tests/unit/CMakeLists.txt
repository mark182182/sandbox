file(GLOB UNIT_TESTS "*.c")
file(GLOB_RECURSE RENDERER_SRC "../../src/*.c")
list(FILTER RENDERER_SRC EXCLUDE REGEX ".*/main\\.c$")

foreach(test_file ${UNIT_TESTS})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name}_unit ${test_file} ${RENDERER_SRC})
    target_include_directories(${test_name}_unit PRIVATE ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/tests)
    target_link_libraries(${test_name}_unit
        raylib
        kernel32
        user32
        gdi32
        winmm
        shell32
    )
    add_test(NAME ${test_name}_unit COMMAND ${test_name}_unit)
endforeach()