cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+

# Set the C standard to C17, as it's one of the most recent stable standards, widely supported.
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

if (MSVC)
    # For MSVC, set the runtime library to MultiThreaded for release builds
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    # For other compilers, use the default C runtime library
    set(CMAKE_C_STANDARD_LIBRARIES "")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Debug build should not optimize and should include debug symbols
# Would add -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls as well, but tricky using on Windows with msys2/MINGW, so gdb has to be used instead
set(CMAKE_C_FLAGS_DEBUG "-O0 -g -gcodeview -gdwarf-4 -Wno-declaration-after-statement")

# Release build should optimize and not include debug symbols, disable asserts
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

# Set compiler flags for the project
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Weverything -Wno-missing-prototypes -Wno-strict-prototypes -mavx2")

# Conditionally dump AST if requested
if (CLANG_DUMP_AST)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Xclang -ast-dump -Xclang -ast-dump-filter=ca_renderer -o ${CMAKE_BINARY_DIR}/ca_renderer.ast")
    message(STATUS "AST dump will be generated at ${CMAKE_BINARY_DIR}/ca_renderer.ast")
else()
endif()

# Conditionally set flags based on what is passed to CMake
if (CLANG_VERBOSE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -v")
endif()

# Print the compiler flags for debugging purposes
message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
message(STATUS "CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# Print the actual compiler flags that will be used

# Add common flags specifically to the target, excluding e.g. raylib warnings
add_compile_options(
    -Wno-everything
    $<$<COMPILE_LANGUAGE:C>:-Wno-reserved-id-macro>
    $<$<COMPILE_LANGUAGE:C>:-Wno-documentation>
    $<$<COMPILE_LANGUAGE:C>:-Wno-documentation-unknown-command>
)

if (CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    add_link_options(-fuse-ld=lld -g -Wl,--pdb=)
else()
    add_link_options(-fuse-ld=lld)
endif()

project(ca_renderer LANGUAGES C)

# Add any test directories

enable_testing()
add_subdirectory(tests/scratch)
add_subdirectory(tests/unit)
add_subdirectory(tests/integration)
add_subdirectory(tests/benchmark)
add_subdirectory(tests/e2e)

# Add source to this project's executable.
file(GLOB_RECURSE CA_RENDERER_SRC CONFIGURE_DEPENDS "src/*.c")
add_executable(ca_renderer "${CMAKE_SOURCE_DIR}/resources" ${CA_RENDERER_SRC})
target_include_directories(ca_renderer PRIVATE src external/raylib/src)

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
        set(GRAPHICS GRAPHICS_API_OPENGL_43 CACHE STRING "" FORCE)
        FetchContent_MakeAvailable(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    endif()
endif()

if(MSVC OR MINGW OR MINGW32 OR MINGW64)
    # For MSVC or MinGW, link against Windows libraries
    target_link_libraries(${PROJECT_NAME}
        raylib
        kernel32
        user32
        gdi32
        winmm
        shell32
    )
else()
    # Other compilers, possibly Unix-like
    target_link_libraries(${PROJECT_NAME}
        raylib
        m
        c
    )
endif()

# Copy resources directory to the output directory
add_custom_command(TARGET ca_renderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:ca_renderer>/resources)

# TODO: Add tests and install targets if needed.