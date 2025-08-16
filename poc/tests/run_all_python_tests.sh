#!/bin/bash
set -e

# Run all Python unittest test files in the tests/ directory
# Output will show which tests pass/fail

PYTHONPATH=$(dirname "$0")/../build python3 -m unittest discover -v tests 