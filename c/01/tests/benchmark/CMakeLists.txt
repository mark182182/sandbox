file(GLOB BENCHMARK_TESTS "*.c")
foreach(test_file ${BENCHMARK_TESTS})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name}_benchmark ${test_file})
    target_include_directories(${test_name}_benchmark PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(${test_name}_benchmark raylib m) # Only if needed
    add_test(NAME ${test_name}_benchmark COMMAND ${test_name}_benchmark)
endforeach()