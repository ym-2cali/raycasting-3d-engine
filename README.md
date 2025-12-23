# Cub3D - 3D Raycasting Game Engine

A 3D game engine inspired by Wolfenstein 3D, built using raycasting techniques. This project renders a first-person perspective maze from a 2D map using the MLX42 graphics library.

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Architecture](#architecture)
- [Implementation Details](#implementation-details)
- [Map Format](#map-format)

---

## 🎮 Overview

Cub3D is a raycasting engine that creates a 3D graphical representation of a maze from a bird's-eye view. The player can navigate through the maze using keyboard controls, with textured walls, floor, and ceiling.

### Key Concepts
- **Raycasting**: Projects 2D map data into 3D space
- **DDA Algorithm**: Digital Differential Analysis for ray-wall intersections
- **Texture Mapping**: Applies textures to walls based on direction
- **Player Movement**: Smooth navigation with collision detection

---

## ✨ Features

- ✅ First-person 3D navigation
- ✅ Textured walls (North, South, East, West)
- ✅ Configurable floor and ceiling colors
- ✅ Smooth player movement and rotation
- ✅ Collision detection
- ✅ Map validation and parsing
- ✅ Memory leak protection with garbage collector
- ✅ Support for custom `.cub` map files

---

## 🔧 Installation

### Prerequisites
- GCC compiler
- Make
- MLX42 library (included in project)
- GLFW library
- Math library (-lm)

### Build Instructions
```bash
# Clone the repository
git clone <repository-url>
cd cub3d

# Compile the project
make

# Run with a map file
./cub3d maps/test_fixed.cub
```

### Clean Commands
```bash
make clean   # Remove object files
make fclean  # Remove object files and executable
make re      # Rebuild from scratch
```

---

## 🎯 Usage

### Controls
- **W/↑**: Move forward
- **S/↓**: Move backward
- **A**: Strafe left
- **D**: Strafe right
- **←**: Rotate left
- **→**: Rotate right
- **ESC**: Exit game

### Running the Program
```bash
./cub3d [map_file.cub]
```

Example:
```bash
./cub3d maps/test_fixed.cub
```

---

## 🏗️ Architecture

### Project Structure
```
cub3d/
├── inc/
│   └── cub3d.h              # Main header file
├── src/
│   ├── main.c               # Entry point
│   ├── window.c             # Window initialization
│   ├── assets/
│   │   ├── imgs.c           # Image creation/management
│   │   ├── moves.c          # Player movement logic
│   │   ├── ray_caster.c     # Main raycasting algorithm
│   │   └── ray_caster_utils1.c
├── parsing/
│   ├── textures/
│   │   ├── texture_loader.c       # Load PNG textures
│   │   ├── texture_validation.c   # Validate texture files
│   │   ├── texture_utils.c        # Texture selection
│   │   ├── wall_projection.c      # Wall rendering
│   │   └── ray_caster_utils.c     # Ray intersection helpers
│   ├── pars_src/utils/
│   │   ├── parse.c               # Main parsing logic
│   │   ├── map_utils.c           # Map validation
│   │   ├── utils.c               # Color/texture parsing
│   │   └── garbage_collector.c   # Memory management
│   ├── libft/                # Custom C library
│   └── get_next_line/        # File reading utility
├── textures/                 # PNG texture files
├── maps/                     # Map files (.cub)
└── Makefile
```

---

## 🔍 Implementation Details

### 1. Program Flow

```
main() 
  ↓
Parse Arguments → Validate Map → Load Textures
  ↓
Initialize MLX Window
  ↓
Setup Player Position
  ↓
Create Images (floor, ceiling, walls)
  ↓
Main Game Loop:
  - Handle Input (key_events)
  - Update Player Position
  - Cast Rays (ray_caster)
  - Render Frame
  - Display to Window
  ↓
Cleanup & Exit
```

### 2. Parsing System

**File Format** (`.cub`):
```
NO ./textures/north.png
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png

F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

**Parsing Steps**:
1. **Read file** (`get_next_line`)
2. **Extract textures** (NO, SO, WE, EA)
3. **Parse colors** (F = floor, C = ceiling) → RGB format
4. **Validate map**:
   - Surrounded by walls (1)
   - Contains exactly one player (N/S/E/W)
   - No invalid characters
   - Properly closed (no holes)
5. **Store in `t_map` structure**

### 3. Raycasting Algorithm

**Core Concept**: Cast rays from the player's position at each column of the screen to determine wall distances and heights.

```c
// For each screen column (WINDOW_WIDTH)
for (i = 0; i < WINDOW_WIDTH; i++)
{
    // Calculate ray angle
    ray_angle = player_angle - (FOV/2) + (i * FOV/WINDOW_WIDTH)
    
    // Find wall intersections
    hor_dist = horizontal_intersection(...)
    ver_dist = vertical_intersection(...)
    
    // Use closest intersection
    wall_dist = min(hor_dist, ver_dist)
    
    // Calculate wall height
    wall_height = (TILE_SIZE * WINDOW_HEIGHT) / 
                  (wall_dist * cos(ray_angle - player_angle))
    
    // Draw textured wall column
    draw_wall_with_texture(...)
}
```

**Horizontal Intersection**:
- Checks intersections with horizontal grid lines
- Steps through the map horizontally
- Returns distance to nearest wall

**Vertical Intersection**:
- Checks intersections with vertical grid lines
- Steps through the map vertically
- Returns distance to nearest wall

### 4. Rendering Pipeline

```
Ray Casting → Distance Calculation → Wall Height
      ↓
Texture Selection (N/S/E/W based on ray direction)
      ↓
Draw Ceiling (top to wall_start)
      ↓
Draw Textured Wall (wall_start to wall_end)
      ↓
Draw Floor (wall_end to bottom)
```

**Texture Mapping**:
1. Determine which wall face was hit (N/S/E/W)
2. Calculate exact hit position on wall
3. Map texture coordinate (x) to wall position
4. For each pixel height (y):
   - Calculate texture coordinate (y)
   - Fetch pixel color from texture
   - Draw to screen

### 5. Player Movement

**Movement System**:
```c
// Forward/Backward
new_x = player.x + cos(angle) * MOVE_SPEED
new_y = player.y + sin(angle) * MOVE_SPEED

// Rotation
player.rotation_angle += turn_direction * ROTAT_SPEED

// Strafing (A/D keys)
strafe_angle = player.rotation_angle ± 90°
```

**Collision Detection**:
- Check 3-pixel radius around player
- Prevent movement if wall detected
- Smooth sliding along walls

### 6. Memory Management

**Garbage Collector**:
- All `malloc` replaced with custom `alloc()`
- Tracks allocations in linked list
- `clean_all()` frees everything on exit
- No manual `free()` needed for tracked memory

**Exception**: System library functions (`ft_split`, `ft_strdup`, etc.) still use regular `malloc` and must be freed manually.

### 7. Texture System

**Loading**:
```c
mlx_texture_t* texture = mlx_load_png(path)
```

**Selection** (based on ray direction):
- Horizontal hit + facing down → South texture
- Horizontal hit + facing up → North texture
- Vertical hit + facing right → East texture
- Vertical hit + facing left → West texture

**Cleanup**:
```c
mlx_delete_texture(texture)  // Called on exit
```

---

## 🗺️ Map Format

### File Extension
`.cub` (plain text)

### Structure

#### 1. Texture Paths
```
NO ./path/to/north_texture.png
SO ./path/to/south_texture.png
WE ./path/to/west_texture.png
EA ./path/to/east_texture.png
```

#### 2. Colors (RGB format: 0-255)
```
F 220,100,0    # Floor color
C 225,30,0     # Ceiling color
```

#### 3. Map Grid
```
111111111
100000001
101010101
100N00001
111111111
```

**Characters**:
- `0` = Empty space (walkable)
- `1` = Wall
- `N/S/E/W` = Player start position and direction
- Space = Outside map (must be surrounded by walls)

### Validation Rules
1. ✅ Map must be surrounded by walls
2. ✅ Exactly one player spawn point
3. ✅ No holes in walls (player can't escape)
4. ✅ All texture files must exist
5. ✅ RGB values must be 0-255

---

## 🐛 Known Issues & Notes

### Memory Leaks
The program shows ~40KB of memory leaks on exit. These are **NOT** from the project code but from system libraries:
- `libfontconfig.so` (font caching)
- `libglfw` (graphics library)
- OpenGL/X11 internal allocations

**Verification**: Run with address sanitizer - no leaks show `cub3d+0x` addresses.

### Performance
- Window size: 1088×448 pixels (34×14 tiles)
- Target: 60 FPS
- Tile size: 32 pixels

---

## 📚 Key Algorithms

### DDA (Digital Differential Analysis)
Used for ray-grid intersection to find wall hits efficiently.

### Field of View (FOV)
60° viewing angle, split across screen width for proper perspective.

### Fish-Eye Correction
```c
corrected_distance = distance * cos(ray_angle - player_angle)
```
Prevents distortion at screen edges.

---

## 🎓 Learning Outcomes

- **Computer Graphics**: Raycasting, texture mapping, 3D projection
- **Mathematics**: Trigonometry, vectors, linear algebra
- **Memory Management**: Custom allocator, leak prevention
- **Parsing**: File validation, error handling
- **Game Development**: Game loop, input handling, collision detection

---

## 👥 Authors

- **yael-maa** - Raycasting engine, rendering, movement
- **alel-you** - Parsing system, map validation, memory management

---

## 📄 License

This project is part of the 42 School curriculum.
