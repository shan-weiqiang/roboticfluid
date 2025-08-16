#!/bin/bash

rm -rf build
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
./build/pet_benchmark
python3 plot_results_performance_only.py
python3 plot_results.py
python3 performance_analysis.py