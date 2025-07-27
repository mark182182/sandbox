file(GLOB INTEGRATION_TESTS "*.c")
foreach(test_file ${INTEGRATION_TESTS})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name}_integration ${test_file})
    target_include_directories(${test_name}_integration PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(${test_name}_integration raylib m) # Only if needed
    add_test(NAME ${test_name}_integration COMMAND ${test_name}_integration)
endforeach()