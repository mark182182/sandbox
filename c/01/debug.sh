#!/bin/bash

current_dir="$(pwd)"
/c/msys64/usr/bin/mintty.exe /mingw64/bin/gdb -ex run -ex backtrace "${current_dir}/build/ca_renderer.exe"