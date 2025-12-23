# Cub3D - 3D Raycasting Game Engine

Cub3D is a minimalist first-person experience inspired by Wolfenstein 3D. It transforms a 2D map into a pseudo-3D maze with MLX42, letting the player walk through textured corridors using straightforward controls.

## Overview
- Raycasting projects each screen column into the scene to determine which wall segment to draw.
- A fixed 60° field of view and 32×32 tiles keep movement predictable and gameplay readable.
- Player state (position, facing, movement) drives both rendering and collision checks.

## Features
- Textured walls for the four cardinal directions.
- Independent floor and ceiling colors.
- Keyboard movement with strafing, rotation, and collision detection.
- Support for custom `.cub` map files that describe textures, colors, and layout.

## Installation
1. Install GCC, Make, GLFW, MLX42, and the math library (`-lm`).
2. Clone and build the project:
   ```bash
   git clone <repository-url>
   cd cub3d
   make
   ```

## Usage
- Run the program with a map file: `./cub3d maps/sample.cub`.
- Controls: `W/S` (forward/back), `A/D` (strafe), arrow keys (rotate), `ESC` (exit).

## Architecture
```
cub3d/
├── inc/            # Headers
├── src/            # Rendering, input, game loop
├── parsing/        # Map parsing, libft, get_next_line, textures
├── maps/           # Sample .cub maps
├── textures/       # PNG assets
└── Makefile
```
The game flow parses a map, initializes MLX, updates player input each frame, casts rays per column, draws walls/floor/ceiling, and repeats until exit.

## Map Fundamentals
A `.cub` file is plain text with three sections:
1. Texture paths (`NO`, `SO`, `WE`, `EA`).
2. Floor (`F`) and ceiling (`C`) RGB colors.
3. A grid made of `1`, `0`, and one player spawn (`N`, `S`, `E`, or `W`).

Example:
```
NO textures/north.png
SO textures/south.png
WE textures/west.png
EA textures/east.png

F 220,100,0
C 225,30,0

111111
100001
10N001
111111
```

## Authors
- yael-maa
- alel-you
