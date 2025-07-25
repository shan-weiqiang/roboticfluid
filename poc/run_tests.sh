#!/bin/bash
set -e

BUILD_DIR=build

# Build the project
if [ ! -d "$BUILD_DIR" ]; then
    mkdir $BUILD_DIR
fi
cd $BUILD_DIR
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)
make install
cd ..

echo "\n=== Running basic functionality test ==="
./tests/run_all_python_tests.sh