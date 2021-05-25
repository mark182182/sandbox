#!/bin/bash
# Compiles and executes the artifact with strict Clang options (C++ 17 standard)

filename=$1
if [[ $1 == '' || $1 == ' ' ]]; then
 echo "cl"
 exit 0;
fi

echo "Compiling $filename..."
clang -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -Werror -std=c++17 --output=compiled.exe $filename
output_file=$(find . | grep compiled.exe)
echo "Executing $output_file..."
./${output_file}
exit 0