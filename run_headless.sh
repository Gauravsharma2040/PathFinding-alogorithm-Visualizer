#!/usr/bin/env bash
set -e

echo "🔧 Building (headless)..."

g++ -std=gnu++17 -O2 \
    -Iinclude \
    src/main_headless.cpp \
    src/Grid.cpp \
    src/Node.cpp \
    src/Algorithms/Astar.cpp \
    src/Algorithms/BFS.cpp \
    src/Algorithms/DFS.cpp \
    src/Algorithms/Dijkstra.cpp \
    -o pathfinder

echo "🚀 Running headless experiment"
echo "----------------------------------"
echo "Args: $@"

# Forward ALL arguments directly to C++
./pathfinder "$@"
