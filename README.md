# Wave Function Collapse (WFC) 2D Image Generation

This project implements a simplified version of the **Wave Function Collapse (WFC)** algorithm in C++ for generating 2D grid-based images. The generated image consists of tiles, where each tile follows certain adjacency rules to ensure consistency in the final pattern.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [Future Improvements](#future-improvements)
- [License](#license)

## Introduction

The Wave Function Collapse (WFC) algorithm is a procedural generation algorithm that is often used for generating textures, patterns, or game levels. The core idea behind WFC is to iteratively collapse possibilities for each cell in a grid based on the possibilities of its neighbors, following predefined adjacency rules.

This C++ implementation demonstrates the basic principles of WFC in a 2D grid, where each cell represents a "tile" (e.g., grass, water, sand, mountain) with certain constraints on how they can be placed next to each other.

## Features

- Simple 2D grid generation.
- Tile-based placement with adjacency rules.
- Random tile selection based on possible valid neighbors.
- Text-based visualization of the grid.

## Installation

### Prerequisites

- A C++ compiler that supports C++11 or later (e.g., `g++`).
- Basic knowledge of how to compile and run C++ programs.

### Build Instructions

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/wfc-2d-generation.git
   cd wfc-2d-generation

2. Compile the project:

    ```bash
    g++ -o wfc main.cpp
    ```

3. Run the program:

    ```bash
    ./wfc
    ```

## Usage

After running the program, a 10x10 grid will be generated, and tiles will be placed following the adjacency rules. The output will be displayed in the terminal, where each tile is represented by a symbol:

- G: Grass
- W: Water
- S: Sand
- M: Mountain
- .: Empty (if no tile was placed)

Example output:

```bash
G G W W W S S M M M
G G G W W S S S M M
S G G G G S S M M M
S S S G G G G S S M
S S S S G G G M M M
S S S G G W W W W G
W W W G G G W G G G
G G W G S S S G G W
```

## How It Works

1. Grid Initialization: A grid is initialized, where each cell starts with all possible tile types (Grass, Water, Sand, Mountain).
2. Tile Collapsing: The algorithm iteratively collapses the possible tile choices for each cell based on its neighboring cells. Adjacency rules determine which tiles are allowed to be placed next to each other.
3. Random Selection: Once the possible tile choices are reduced, the algorithm randomly selects a tile and sets it for the cell.
4. Visualization: The final grid is printed out in the console as a 2D array of symbols representing each tile.

### Adjacency Rules

Each tile has constraints on which tiles can be placed next to it:

- Grass (G) can be adjacent to Grass, Sand, or Water.
- Water (W) can be adjacent to Water or Grass.
- Sand (S) can be adjacent to Sand, Grass, or Mountain.
- Mountain (M) can be adjacent to Sand or Mountain.

## Future Improvements

- Add support for larger grids with more tile types.
- Implement custom user-defined adjacency rules.
- Visualize the grid using a graphical library (e.g., SDL, SFML).
- Add optimization for faster collapsing of the wave function.
- Support for loading tile sets from an external file.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
