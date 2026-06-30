# Gen IV Battle Frontier Analyzer

A high-performance C++ backend designed to simulate and analyze 1v1 Pokémon battles. This engine provides the computational foundation for optimizing decision-making across Battle Frontier facilities.

## Core Architecture & Technologies
* **Language:** C++
* **Build System:** CMake
* **Concurrency:** Utilizes multi-threading to parallelize battle simulations, significantly reducing computation time.
* **AI/Logic:** Implements heuristic-based lookahead algorithms to evaluate move efficiency.

## Purpose
The engine writes battle outcomes to file. Its outputs are designed for integration with external analytics tools to guide users through complex decision trees in facilities like the Battle Factory and Battle Hall.

## How to Build
```bash
mkdir build
cd build
cmake ..
make
./gen_iv_battle_frontier_analyzer