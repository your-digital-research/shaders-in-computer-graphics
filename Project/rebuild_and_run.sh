#!/bin/bash

./clean_build.sh

if [ $? -eq 0 ]; then
    ./run.sh
else
    echo "❌ Build failed. Not running."
fi