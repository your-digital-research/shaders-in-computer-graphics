#!/usr/bin/env bash
set -euo pipefail

# Resolve script and project directories
SCRIPTDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPTDIR/.." && pwd)"

echo "🔄 Cleaning build directory..."
rm -rf "$PROJECT_ROOT/build"

echo "📁 Creating build directory..."
mkdir -p "$PROJECT_ROOT/build"
cd "$PROJECT_ROOT/build"

echo "🛠️ Configuring with CMake..."
cmake ..

echo "⚙️ Building project..."
cmake --build . --parallel $(sysctl -n hw.ncpu)

echo "✅ Done!"
