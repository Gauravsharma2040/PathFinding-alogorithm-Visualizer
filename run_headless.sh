#!/usr/bin/env bash
set -e
ROWS=40
COLS=40
SIGMA=1.0
SEED=12345
echo "🔧 Building (headless)..."
g++ -std=gnu++17 \
    -O2 \
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

./pathfinder --headless \
    --rows "$ROWS" \
    --cols "$COLS" \
    --sigma "$SIGMA" \
    --seed "$SEED"

