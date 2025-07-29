# Uses a specific CMakeLists.txt to build scratch tests that does not run as the part of the main test suite.

file(GLOB SCRATCH_FILES "*.c")
foreach(file ${SCRATCH_FILES})
    get_filename_component(test_name ${file} NAME_WE)
    add_executable(${test_name}_scratch ${file})
    target_include_directories(${test_name}_scratch PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(${test_name}_scratch raylib
        kernel32
        user32
        gdi32
        winmm
        shell32
    )
endforeach()