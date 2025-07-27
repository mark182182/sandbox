#!/bin/bash

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
    echo "No build type specified. Defaulting to 'Debug'."
    build_type="Debug"
fi

if [[ "$*" == *"--rebuild"* ]]; then
    echo "Rebuilding the project..."
    rm -rf build
else
    echo "Building the project..."
fi

mkdir -p build

cmake -S . -B build \
    -G "MinGW Makefiles" \
    -DCMAKE_BUILD_TYPE="$build_type" \
    -DCMAKE_C_COMPILER="clang" \
    -DCMAKE_MAKE_PROGRAM="make"

# build the project
cmake --build build

if [ $? -eq 0 ]; then
    echo "Build completed successfully"
else
    echo "Build failed"
    exit 1
fi