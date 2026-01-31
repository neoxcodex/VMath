#!/usr/bin/env bash
set -e

# ----------------------------
# 1. Check for VS Code
# ----------------------------
if ! command -v code &>/dev/null; then
  echo "❌ VS Code not found. Install it first."
  exit 1
fi

# ----------------------------
# 2. Install system deps
# ----------------------------
echo "📦 Installing clang, clangd, cmake, ninja, gdb..."
sudo apt update
sudo apt install -y clang clangd cmake ninja-build gdb

# ----------------------------
# 3. Remove AI extensions
# ----------------------------
echo "🧹 Removing AI extensions..."
AI_EXTENSIONS=(
  "GitHub.copilot"
  "GitHub.copilot-chat"
  "TabNine.tabnine-vscode"
  "VisualStudioExptTeam.vscodeintellicode"
)

for ext in "${AI_EXTENSIONS[@]}"; do
  if code --list-extensions | grep -q "^${ext}$"; then
    code --uninstall-extension "$ext" || true
  fi
done

# ----------------------------
# 4. Install required extensions
# ----------------------------
echo "🧩 Installing essential extensions..."
REQUIRED_EXTENSIONS=(
  "llvm-vs-code-extensions.vscode-clangd"
  "ms-vscode.cmake-tools"
  "ms-vscode.cpptools"
  "eamodio.gitlens"
)

for ext in "${REQUIRED_EXTENSIONS[@]}"; do
  code --install-extension "$ext" || true
done

# ----------------------------
# 5. VS Code settings
# ----------------------------
echo "🛠️ Applying VS Code settings..."

SETTINGS_DIR="$HOME/.config/Code/User"
SETTINGS_FILE="$SETTINGS_DIR/settings.json"
mkdir -p "$SETTINGS_DIR"

cat > "$SETTINGS_FILE" << 'EOF'
{
  "workbench.startupEditor": "none",
  "workbench.colorTheme": "Default Dark+",
  "editor.fontFamily": "JetBrains Mono, Menlo, Monaco, 'Courier New', monospace",
  "editor.fontSize": 13,
  "editor.cursorStyle": "line",
  "editor.cursorBlinking": "solid",
  "editor.cursorWidth": 2,

  "editor.minimap.enabled": false,
  "editor.renderWhitespace": "boundary",
  "editor.scrollBeyondLastLine": false,
  "editor.formatOnSave": false,
  "editor.wordWrap": "off",

  "telemetry.telemetryLevel": "off",

  "C_Cpp.intelliSenseEngine": "disabled",
  "clangd.arguments": [
    "--background-index",
    "--clang-tidy",
    "--completion-style=detailed",
    "--header-insertion=iwyu",
    "--pch-storage=memory"
  ],

  "cmake.generator": "Ninja",
  "cmake.configureOnOpen": true,
  "cmake.useCMakePresets": true,

  "files.trimTrailingWhitespace": true,
  "files.insertFinalNewline": true
}
EOF

# ----------------------------
# 6. Create C++ scaffold in current directory
# ----------------------------
echo "📁 Creating C++ scaffold in the current folder..."

PROJECT_ROOT="$(pwd)"
SRC_DIR="$PROJECT_ROOT/src"
INCLUDE_DIR="$PROJECT_ROOT/include"
BUILD_DIR="$PROJECT_ROOT/build"

mkdir -p "$SRC_DIR" "$INCLUDE_DIR" "$BUILD_DIR"

cat > "$PROJECT_ROOT/CMakeLists.txt" << 'EOF'
cmake_minimum_required(VERSION 3.20)

project(MyCppProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(MyCppProject
  src/main.cpp
)

target_include_directories(MyCppProject
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(MyCppProject
  PRIVATE
    -Wall -Wextra -Wpedantic
)
EOF

cat > "$SRC_DIR/main.cpp" << 'EOF'
#include <iostream>

int main() {
    std::cout << "Hello, C++ world!\n";
    return 0;
}
EOF

cat > "$PROJECT_ROOT/.clang-format" << 'EOF'
BasedOnStyle: Google
IndentWidth: 4
ColumnLimit: 100
EOF

cat > "$PROJECT_ROOT/CMakePresets.json" << 'EOF'
{
  "version": 3,
  "configurePresets": [
    {
      "name": "default",
      "displayName": "Default (Ninja + Clang)",
      "generator": "Ninja",
      "binaryDir": "${sourceDir}/build",
      "cacheVariables": {
        "CMAKE_C_COMPILER": "clang",
        "CMAKE_CXX_COMPILER": "clang++"
      }
    }
  ]
}
EOF

echo "✅ Done. Your project scaffold is ready."
echo "Now run:"
echo "  code ."
echo "Then: CMake: Configure → Build → Run"
