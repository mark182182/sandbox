#!/bin/bash
set -e

source "$(dirname "$0")/common.sh"

if ! command -v clang &> /dev/null; then
    echo "Error: clang compiler not found"
    exit 1
fi

if ! command -v make &> /dev/null; then
    echo "Error: make not found. Please install using: choco install make"
    exit 1
fi

build_type=$1
if [ -z "$build_type" ]; then
    echo "No build type specified. Defaulting to 'DEBUG'."
    build_type="DEBUG"
fi

if [[ "$*" == *"--rebuild"* ]]; then
    echo "Rebuilding the project..."
    rm -rf build
else
    echo "Building the project..."
fi

verbose_mode=""
if [[ "$*" == *"-v"* ]]; then
    echo "Verbose mode enabled."
    verbose_mode="--verbose"
fi

dump_mode=""
if [[ "$*" == *"--dump"* ]]; then
    echo "AST dump mode enabled."
    dump_mode="--dump"
fi

mkdir -p build

# Need to patch raylib's CMakeLists.txt, otherwise it would try to use the CXX compiler as well, but it does not actually need it.

raylib_cmake_path="external/raylib-5.5/CMakeLists.txt"
if [ -f "$raylib_cmake_path" ]; then
    echo "Patching raylib CMakeLists.txt..."
    sed -i 's/project(raylib)/project(raylib LANGUAGES C)/' "$raylib_cmake_path"
else
    echo "Warning: raylib CMakeLists.txt not found at $raylib_cmake_path"
fi

# Needs MSYS2 and `pacman -S mingw-w64-x86_64-clang`, otherwise the MSVC linker would be used.

# Target: x86_64-w64-windows-gnu

if [[ "$*" != *"--no-tidy"* ]]; then
    echo "Running clang-tidy..."
    clang-tidy -p build ./src/**/*.c -checks=-*,clang-analyzer-*,concurrency-*,modernize-*,performance-*,readability-*
fi

export CC=clang
cmake -S . -B build \
    -G "MinGW Makefiles" \
    -DCMAKE_BUILD_TYPE="$build_type" \
    -DCMAKE_C_COMPILER="C:/msys64/mingw64/bin/clang.exe" \
    -DCMAKE_MAKE_PROGRAM="make" \
    -DCLANG_VERBOSE="$verbose_mode" \
    -DCLANG_DUMP_AST="$dump_mode" \
    -DCOMMON_FLAGS="$COMMON_FLAGS"

# build the project
cmake --build build $verbose_mode

if [ $? -eq 0 ]; then
    echo "Build completed successfully"
else
    echo "Build failed"
    exit 1
fi

# Run tests (excluding standalone)
echo "Running tests..."
cd build
ctest --output-on-failure
