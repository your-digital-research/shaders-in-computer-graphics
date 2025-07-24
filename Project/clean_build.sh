#!/bin/bash

echo "🔄 Cleaning build directory..."
rm -rf build

echo "📁 Creating build directory..."
mkdir build && cd build

echo "🛠️ Configuring with CMake..."
cmake ..

echo "⚙️ Building project..."
cmake --build .

echo "✅ Done!"