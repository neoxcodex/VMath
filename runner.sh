#!/usr/bin/env bash
set -e

# ----------------------------
# Config
# ----------------------------
BUILD_DIR="build"
EXEC_NAME="MyCppProject"

# ----------------------------
# Build
# ----------------------------
echo "🛠 Building..."
cmake -S . -B "$BUILD_DIR" -G Ninja
cmake --build "$BUILD_DIR"

# ----------------------------
# Run
# ----------------------------
echo "▶ Running..."
"$BUILD_DIR/$EXEC_NAME"

# ----------------------------
# Clean executable
# ----------------------------
echo "🧹 Cleaning output..."
rm -f "$BUILD_DIR/$EXEC_NAME"

echo "✅ Done."
