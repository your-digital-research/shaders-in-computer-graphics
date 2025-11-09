#!/usr/bin/env bash

# Resolve script and project directories
SCRIPTDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPTDIR/.." && pwd)"

echo "🔄 Cleaning build directory..."
rm -rf "$PROJECT_ROOT/build"

echo "✅ Done!"
