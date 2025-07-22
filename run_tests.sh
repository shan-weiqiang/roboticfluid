#!/bin/bash
set -e

BUILD_DIR=build

# Build the project
if [ ! -d "$BUILD_DIR" ]; then
    mkdir $BUILD_DIR
fi
cd $BUILD_DIR
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
make -j$(nproc)
# Copy/rename the Python extension to roboticfluid.so for import
sofile=$(ls roboticfluid_python*.so | head -n1)
cp "$sofile" roboticfluid.so
cd ..

echo "\n=== Running C++ IPC test ==="
./build/tests/ipc_test_cpp

echo "\n=== Running Python IPC test ==="
PYTHONPATH=build python3 tests/ipc_test_python.py 