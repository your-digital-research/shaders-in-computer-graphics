#!/usr/bin/env bash

set -euo pipefail

# Resolve script and project directories
SCRIPTDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Rebuild and run using the other scripts in this directory
if "$SCRIPTDIR/clean_build.sh"; then
    "$SCRIPTDIR/run.sh"
else
    echo "❌ Build failed. Not running."
fi
