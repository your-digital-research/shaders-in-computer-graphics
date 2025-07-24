#!/bin/bash

# Define the executable path (adjust if your binary has a different name)
EXECUTABLE="./build/bin/ShadersInComputerGraphics"

# Check if executable exists
if [ -f "$EXECUTABLE" ]; then
    echo "🚀 Running application..."
    "$EXECUTABLE"
else
    echo "❌ Executable not found at $EXECUTABLE."
    echo "💡 Make sure to build the project first (e.g. run ./clean_build.sh)."
fi