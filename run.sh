#!/usr/bin/env bash

set -e  # stop on first error

echo "🔧 Building project..."

g++ -std=gnu++17 \
    -Iinclude \
    -Iinclude/Algorithms \
    -Iinclude/visualization \
    -I/ucrt64/include \
    src/main.cpp \
    src/Grid.cpp \
    src/Node.cpp \
    src/visualization/Render.cpp \
    src/Algorithms/Astar.cpp \
    src/Algorithms/BFS.cpp \
    src/Algorithms/dfs.cpp \
    src/Algorithms/Dijkstra.cpp \
    src/utils/input.cpp \
    src/utils/Timer.cpp \
    -L/ucrt64/lib \
    -lsfml-graphics \
    -lsfml-window \
    -lsfml-system \
    -o pathfinder

echo "🚀 Running..."
./pathfinder
