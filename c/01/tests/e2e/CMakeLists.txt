file(GLOB_RECURSE RENDERER_SRC "../../src/*.c")
list(FILTER RENDERER_SRC EXCLUDE REGEX ".*/main\\.c$")

file(GLOB E2E_TESTS "*.c")
foreach(test_file ${E2E_TESTS})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name}_e2e ${test_file} ${RENDERER_SRC})
    target_include_directories(${test_name}_e2e PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(${test_name}_e2e raylib
        kernel32
        user32
        gdi32
        winmm
        shell32
    )
    add_test(NAME ${test_name}_e2e COMMAND ${test_name}_e2e)
endforeach()