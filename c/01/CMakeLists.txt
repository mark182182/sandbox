cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+

# Use Clang
set(CMAKE_C_COMPILER "clang")

# Set the C standard to C17, as it's one of the most recent stable standards, widely supported.
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Weverything -Wno-c98-compat -mavx2")

# Add flags specifically to the target, excluding e.g. raylib warnings
add_compile_options(
    -Wno-everything
    $<$<COMPILE_LANGUAGE:C>:-Wno-reserved-id-macro>
    $<$<COMPILE_LANGUAGE:C>:-Wno-documentation>
    $<$<COMPILE_LANGUAGE:C>:-Wno-documentation-unknown-command>
)

project("ca_renderer")

# Add source to this project's executable.
add_executable (ca_renderer "main.c" "${CMAKE_SOURCE_DIR}/resources" "const.c"  "str.c" "gen_gol2d.c" "font.c" "renderer.c" "hash.c" "menu.c" "cells.c")

# Raylib
set(RAYLIB_VERSION 5.5)
set(RAYLIB_CACHE_DIR "${CMAKE_SOURCE_DIR}/external/raylib-${RAYLIB_VERSION}")

# First check if raylib is already built in our cache directory
if(EXISTS "${RAYLIB_CACHE_DIR}/build")
    message(STATUS "Using pre-built raylib from ${RAYLIB_CACHE_DIR}/build")
    set(raylib_DIR "${RAYLIB_CACHE_DIR}/build/raylib")
endif()

# Then try to find raylib
find_package(raylib ${RAYLIB_VERSION} QUIET)

# Only download and build if not found
if (NOT raylib_FOUND)
    include(FetchContent)
    
    # Check if we have source cached
    if(EXISTS "${RAYLIB_CACHE_DIR}")
        message(STATUS "Using cached raylib source from ${RAYLIB_CACHE_DIR}")
        FetchContent_Declare(
            raylib
            SOURCE_DIR "${RAYLIB_CACHE_DIR}"
        )
    else()
        message(STATUS "Downloading raylib ${RAYLIB_VERSION}")
        FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
            SOURCE_DIR "${RAYLIB_CACHE_DIR}"
        )
    endif()

    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    endif()
endif()
target_link_libraries(${PROJECT_NAME} raylib)

# Copy resources directory to the output directory
add_custom_command(TARGET ca_renderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:ca_renderer>/resources)

# TODO: Add tests and install targets if needed.
