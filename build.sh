#!/bin/bash

# Create and navigate to the build directory
mkdir -p build
cd build

# Run CMake to configure the project
cmake ..

# Build the project
make

# Navigate back to the root directory
cd ..
