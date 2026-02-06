#!/bin/bash

# 1. Nuke old build to force a clean Makefile generation
rm -rf build
mkdir build

echo "--- 🛠️  Configuring & Building (Chaos Mode) ---"

# 2. Build with specific generator
cd build || exit
cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" ..

# 3. Compile
make -j$(nproc)

# 4. Execution
if [ $? -eq 0 ]; then
    echo "--- 🚀 Build Successful. ---"
    ./VMathVisualizer
else
    echo "--- ❌ Build Failed. ---"
    exit 1
fi
