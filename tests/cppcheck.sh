#!/bin/bash

# Run Cppcheck for static code analysis
echo "Running Cppcheck..."
cppcheck --enable=all --inconclusive --force --xml ./src 2> cppcheck_report.xml
