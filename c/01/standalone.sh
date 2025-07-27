#!/bin/bash
set -e

source "$(dirname "$0")/common.sh"

cd "tests/standalone"

rm -rf build
mkdir -p build

cmake -S . -B build \
    -G "MinGW Makefiles" \
    -DCMAKE_BUILD_TYPE="DEBUG" \
    -DCMAKE_C_COMPILER="clang" \
    -DCMAKE_MAKE_PROGRAM="make" \
    -DCOMMON_FLAGS="$COMMON_FLAGS"

cmake --build build