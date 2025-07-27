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

cmake -S . -B build \
    -G "MinGW Makefiles" \
    -DCMAKE_BUILD_TYPE="$build_type" \
    -DCMAKE_C_COMPILER="clang" \
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