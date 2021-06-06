#!/bin/bash
# Compiles and executes the artifact with strict Clang options (C++ 17 standard)
# Example: cl main.cpp -v -reload -purge

PURGE=$5
if [[ $PURGE == "-purge" ]]; then
  echo "🚮  Purging on exit"
  trap ../purge_artifacts.sh EXIT
fi

FILENAME=$1
LIBS=$2
RELOAD=$4
COMPILED_NAME=$(date --date='now' | tr -d ' :')
if [[ $1 == '' || $1 == ' ' ]]; then
  echo "No-op, exiting."
  exit 0
fi

if [[ $3 == '-v' ]]; then
  echo "🧾  Using verbose mode"
fi

invoke_clang() {
  echo "🏗️  Compiling $FILENAME..."
  clang++ -l$LIBS -pedantic-errors $4 -Wall -Weffc++ -Wextra -Wsign-conversion -Werror -std=c++17 --output=$COMPILED_NAME.exe $FILENAME
  output_file=$(find . | grep $COMPILED_NAME.exe)
  echo "🚀  Executing $output_file..."
  ./${output_file}
}

if [[ $RELOAD == '-reload' ]]; then
  echo "♻️  Using reload"
  while true; do
    CHECK_FILE_OLD=$CHECK_FILE_NEW
    CHECK_FILE_NEW=$(ls -latrh $FILENAME)
    if [[ $CHECK_FILE_OLD != $CHECK_FILE_NEW ]]; then
      echo ""
      echo "🟡  Reloading  🟡"
      invoke_clang
    fi
    sleep 2
  done
else
  invoke_clang
fi
