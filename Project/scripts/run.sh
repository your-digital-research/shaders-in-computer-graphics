#!/usr/bin/env bash

set -euo pipefail

# Resolve script and project directories
SCRIPTDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPTDIR/.." && pwd)"

# Define the executable path
EXECUTABLE="$PROJECT_ROOT/build/bin/ShadersInComputerGraphics"

# Check if executable exists
if [ -f "$EXECUTABLE" ]; then
    echo "🚀 Running application..."
    "$EXECUTABLE"
else
    echo "❌ Executable not found at $EXECUTABLE."
    echo "💡 Make sure to build the project first (e.g. run clean_build.sh)."
fi
