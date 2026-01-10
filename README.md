## Version 3.0 Update

This release refactors the framework into a research-grade, reproducible system
designed for large-scale, deterministic experimentation and collaborative analysis.

## New in v3.0
- Headless execution mode for non-interactive experiments
- Deterministic experiment control via fixed RNG seeds
- Clean separation between algorithmic core and SFML visualization
- Dockerized build and execution for cross-platform reproducibility
- Unified experiment output (path cost and node expansions) for automated analysis
- Scalable grid configurations for stress-testing heuristics under noise

## Version 2.0 Update

This release extends the original visualizer into an experimental framework
for studying the robustness of A* heuristics under noise.

### New in v2.0
- Weighted terrain
- Gaussian noise on traversal cost
- Multiple heuristic regimes (h=0, admissible, noisy, aggressive)
- Node expansion metrics
- Empirically validated Dijkstra baseline


# Pathfinding Algorithm Visualizer

A desktop application built using **C++ and SFML** to visually demonstrate how different pathfinding algorithms explore a grid and compute optimal paths.  
This tool is designed to help students, developers, and enthusiasts understand the behavior, strengths, and weaknesses of common graph-search algorithms.

---
# 🚀 Features

- 🟩 **Interactive Grid** – Place start, end, and walls using your mouse  
- 🔄 **Real-Time Visualization**  
- 🧠 **Supported Algorithms**
  - **Breadth-First Search (BFS)**
  - **Depth-First Search (DFS)**
  - **Dijkstra’s Algorithm**
  - **A\* Search Algorithm**
- 🎨 Clean SFML-rendered window  
- ⏸️ Pause / Reset options  
- 📏 Grid-based traversal with smooth animations  

## 📦 Installation & Setup

### **1. Clone this repository**
```sh
git clone https://github.com/Gauravsharma2040/PathFinding-alogorithm-Visualizer.git
cd PathFinding-alogorithm-Visualizer
---
2. Install SFML

Download SFML from:
https://www.sfml-dev.org/download.php

Follow the installation steps for your compiler (MinGW / MSVC).
---

#3. Build the project
g++ -IC:/SFML/include -LC:/SFML/lib src/*.cpp -o visualizer.exe -lsfml-graphics -lsfml-window -lsfml-system(using ucrt64 for compiling code is reccomended since it supports SFML but g++ works just as well)

#4.How to use:-
| Action      | Description    |
| ----------- | -------------- |
| Left Click  | Place/remvove  |
|             |    Walls       |
| B           | Run BFS        |
| C           | Run DFS        |
| D           | Run Dijkstra   |
| A           | Run A*         |
| R           | Reset Grid     |

---

BFS

Guarantees shortest path in an unweighted grid.
Expands equally in all directions.

DFS

Depth-first exploration.
Does not guarantee shortest path.

Dijkstra

Guarantees the shortest path using weighted cost = distance.

A*

Improves Dijkstra by adding a heuristic (Manhattan distance).
Often the fastest and most optimal for grid search.

---


#5.Project Structure:-
├── src/
│   ├── Grid.cpp
│   ├── BFS.cpp
│   ├── DFS.cpp
│   ├── Dijkstra.cpp
│   ├── AStar.cpp
│   └── main.cpp
├── include/
│   ├── Grid.h
│   ├── BFS.h
│   ├── DFS.h
│   ├── Dijkstra.h
│   └── AStar.h
├── assets/ (optional)
└── README.md

🛠️ Future Improvements

Weighted grids

Diagonal movement

Maze generation algorithms

Speed control slider

Dark mode
Primary implementation and framework design by Gaurav Sharma.
📜 License

This project is open-source and available under the MIT License

🤝 Contributions

Pull requests are welcome!
Feel free to open an issue if you want to add features or report bugs.

