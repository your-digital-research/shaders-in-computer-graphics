#!/usr/bin/env bash

set -euo pipefail

# Resolve script and project directories
SCRIPTDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPTDIR/.." && pwd)"

# Define the executable path and binary directory
EXECUTABLE="$PROJECT_ROOT/build/bin/ShadersInComputerGraphics"
BIN_DIR="$PROJECT_ROOT/build/bin"

# Check if executable exists
if [ -f "$EXECUTABLE" ]; then
    echo "🚀 Running application..."
    cd "$BIN_DIR"
    ./ShadersInComputerGraphics
else
    echo "❌ Executable not found at $EXECUTABLE."
    echo "💡 Make sure to build the project first (e.g. run clean_build.sh)."
fi
