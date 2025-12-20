# Cub3D - 3D Raycasting Game Engine

A Wolf3D-inspired raycasting game engine built in C using the MLX42 graphics library. This project creates a realistic 3D perspective from a 2D map using raycasting techniques.

![Cub3D Demo](https://raw.githubusercontent.com/42School/42-Subjects/master/cub3d/resources/cub3d_example.png)

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Roadmap](#roadmap)
- [Controls](#controls)
- [Map Configuration](#map-configuration)
- [Technical Details](#technical-details)
- [Resources](#resources)

## 🎮 Overview

Cub3D is a 42 School project that implements a raycasting engine similar to Wolfenstein 3D. The program takes a map file as input and renders a first-person 3D view using 2D raycasting algorithms.

### What You'll Learn

- **Raycasting algorithms** (DDA algorithm)
- **Graphics programming** with MLX42
- **Mathematical concepts**: trigonometry, vector mathematics
- **C programming**: memory management, parsing, optimization
- **Game development**: player movement, collision detection
- **42 Norminette** compliance

## ✨ Features

- ✅ Real-time raycasting rendering
- ✅ Textured walls (N/S/E/W directions)
- ✅ Customizable floor and ceiling colors
- ✅ Player movement (WASD) and rotation (arrows/mouse)
- ✅ Collision detection
- ✅ Map validation
- ✅ Procedurally generated space-themed textures
- ✅ Comprehensive error handling

## 🔧 Prerequisites

Before starting, ensure you have:

```bash
# Required packages
- gcc or clang compiler
- make
- CMake (for MLX42)
- GLFW3 library
- Python3 (for texture generation)
- PIL/Pillow (Python imaging library)

# On Debian/Ubuntu:
sudo apt update
sudo apt install build-essential cmake libglfw3-dev python3 python3-pip

# Install Python dependencies:
pip3 install Pillow
```

## 📦 Installation

### Step 1: Clone the Repository

```bash
git clone <your-repository-url> cub3d
cd cub3d
```

### Step 2: Initialize MLX42 Submodule

```bash
cd MLX422
cmake -B build
cmake --build build -j4
cd ..
```

### Step 3: Generate Textures

```bash
python3 generate_textures.py
```

This creates four 512x512 PNG textures:
- `textures/north_wall.png` - Purple nebula
- `textures/south_wall.png` - Black hole
- `textures/east_wall.png` - Galaxy spiral
- `textures/west_wall.png` - Planet surface

### Step 4: Compile the Project

```bash
make
```

### Step 5: Run the Game

```bash
./cub3d maps/smap.cub
```

## 🎯 Usage

```bash
./cub3d <map_file.cub>
```

### Example:

```bash
./cub3d maps/smap.cub
```

## 📁 Project Structure

```
cub3d/
├── inc/
│   └── cub3d.h              # Main header file
├── src/
│   ├── main.c               # Entry point
│   ├── window.c             # Window management
│   ├── assets/
│   │   ├── ray_caster.c     # Raycasting engine
│   │   ├── wall_projection.c # Wall rendering
│   │   ├── moves.c          # Player movement
│   │   └── imgs.c           # Image handling
│   └── utils/
│       └── lib_ft.c         # Utility functions
├── parsing/
│   ├── pars_src/
│   │   ├── parse.c          # Main parsing logic
│   │   ├── utils/
│   │   │   ├── map_utils.c  # Map validation
│   │   │   ├── texture_loader.c # Texture loading
│   │   │   └── utils.c      # Color parsing
│   │   └── tools.c          # Helper tools
│   ├── get_next_line/       # File reading
│   └── libft/               # 42 Libft library
├── MLX422/                  # MLX42 graphics library
├── maps/                    # Map files (.cub)
├── textures/                # Wall textures (.png)
├── generate_textures.py     # Texture generator
├── RAYCASTING_EXPLAINED.md  # Algorithm documentation
├── Makefile                 # Build configuration
└── README.md

```

## 🗺️ Roadmap

### Phase 1: Setup & Understanding (Week 1)

#### Goals:
- Understand raycasting concepts
- Set up development environment
- Study MLX42 documentation

#### Tasks:
1. **Research raycasting**
   - Read [RAYCASTING_EXPLAINED.md](RAYCASTING_EXPLAINED.md)
   - Watch Lode's raycasting tutorial
   - Understand DDA algorithm

2. **Install dependencies**
   - Follow [Installation](#installation) steps
   - Test MLX42 with simple window

3. **Study existing code**
   - Read through `ray_caster.c`
   - Understand function flow
   - Trace ray calculations

### Phase 2: Parsing (Week 2)

#### Goals:
- Parse .cub map files
- Validate map structure
- Load textures and colors

#### Tasks:
1. **File parsing** (`parsing/pars_src/parse.c`)
   - Implement `get_next_line()` integration
   - Parse textures (NO, SO, WE, EA)
   - Parse colors (F, C)
   - Extract map data

2. **Map validation** (`parsing/pars_src/utils/map_utils.c`)
   - Check walls are closed
   - Validate characters (0, 1, N, S, E, W)
   - Ensure single player spawn
   - Verify map is rectangular

3. **Texture loading** (`parsing/pars_src/utils/texture_loader.c`)
   - Load PNG files with MLX42
   - Validate file existence
   - Handle loading errors

**Expected Output**: Program reads .cub file and prints parsed data

### Phase 3: Basic Raycasting (Week 3-4)

#### Goals:
- Implement ray casting algorithm
- Render untextured walls
- Display player position

#### Tasks:
1. **Player structure** (`inc/cub3d.h`)
   ```c
   typedef struct s_player {
       double x;              // Position X
       double y;              // Position Y
       double rotation_angle; // Facing direction
   } t_player;
   ```

2. **Ray casting logic** (`src/assets/ray_caster.c`)
   - `is_wall()` - Check if position is wall
   - `horizontal_intersection()` - Find horizontal wall hit
   - `vertical_intersection()` - Find vertical wall hit
   - `ray_caster()` - Main casting loop

3. **Wall projection** (`src/assets/wall_projection.c`)
   - Calculate wall height based on distance
   - Apply fish-eye correction
   - Draw vertical strips

**Expected Output**: Untextured 3D view with solid colored walls

### Phase 4: Texturing (Week 5)

#### Goals:
- Apply textures to walls
- Calculate texture coordinates
- Render textured walls

#### Tasks:
1. **Texture selection** (`ray_caster.c:select_texture()`)
   - Determine wall face (N/S/E/W)
   - Select appropriate texture
   - Calculate wall hit position

2. **Texture mapping** (`ray_caster.c:calculate_texture_x()`)
   - Calculate X coordinate on texture
   - Apply horizontal mirroring
   - Handle edge cases

3. **Textured rendering** (`ray_caster.c:draw_textured_wall()`)
   - Calculate Y coordinate per pixel
   - Sample texture pixels
   - Draw to screen buffer

**Expected Output**: Textured 3D walls with proper perspective

### Phase 5: Player Controls (Week 6)

#### Goals:
- Implement player movement
- Add rotation controls
- Collision detection

#### Tasks:
1. **Movement system** (`src/assets/moves.c`)
   - WASD for movement
   - Arrow keys for rotation
   - Mouse look (optional)

2. **Collision detection** (`moves.c`)
   ```c
   int check_collision(t_map *map, double new_x, double new_y)
   {
       int mx = (int)(new_x / TILE_SIZE);
       int my = (int)(new_y / TILE_SIZE);
       return (map->arr[my][mx] == '1');
   }
   ```

3. **Smooth movement**
   - Delta time calculation
   - Consistent speed across frame rates
   - Smooth rotation

**Expected Output**: Playable game with smooth controls

### Phase 6: Polish & Optimization (Week 7)

#### Goals:
- Optimize rendering performance
- Add floor/ceiling colors
- Error handling and cleanup

#### Tasks:
1. **Performance optimization**
   - Profile code (identify bottlenecks)
   - Reduce texture lookups
   - Optimize ray calculations

2. **Visual improvements**
   - Draw ceiling (`draw_ceiling()`)
   - Draw floor (`draw_floor()`)
   - Add shading based on distance (optional)

3. **Memory management**
   - Free all allocated memory
   - Proper texture cleanup
   - Handle errors gracefully

**Expected Output**: Polished, leak-free game running at 60+ FPS

### Phase 7: Norminette Compliance (Week 8)

#### Goals:
- Pass 42 norminette checks
- Refactor long functions
- Clean up code style

#### Tasks:
1. **Install norminette**
   ```bash
   pip3 install --break-system-packages norminette
   ```

2. **Fix violations**
   - Max 25 lines per function
   - Max 5 functions per file
   - Proper indentation (tabs)
   - Max 80 characters per line

3. **Code refactoring**
   - Split long functions into helpers
   - Move functions to separate files
   - Add proper comments

**Expected Output**: Clean norminette output

```bash
norminette -R CheckForbiddenSourceHeader
# Result: All files OK!
```

### Phase 8: Testing & Submission (Week 9)

#### Goals:
- Test edge cases
- Create comprehensive maps
- Prepare for defense

#### Tasks:
1. **Create test maps**
   - Minimum size map
   - Maximum size map
   - Complex layouts
   - Invalid maps (should fail gracefully)

2. **Edge case testing**
   - Invalid texture paths
   - Missing map elements
   - Non-rectangular maps
   - Unclosed maps

3. **Documentation**
   - Update README
   - Comment complex algorithms
   - Prepare defense answers

**Expected Output**: Robust, well-tested program ready for evaluation

## 🎮 Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate left |
| `→` | Rotate right |
| `ESC` | Exit game |

## 🗺️ Map Configuration

### .cub File Format

```
NO ./textures/north_wall.png
SO ./textures/south_wall.png
WE ./textures/west_wall.png
EA ./textures/east_wall.png

F 64,64,64
C 135,206,235

1111111111
1000000001
1000N00001
1000000001
1111111111
```

### Map Elements

| Character | Meaning |
|-----------|---------|
| `0` | Empty space (floor) |
| `1` | Wall |
| `N` | Player facing North |
| `S` | Player facing South |
| `E` | Player facing East |
| `W` | Player facing West |
| ` ` (space) | Void (outside map) |

### Rules

1. Map must be surrounded by walls (`1`)
2. Exactly one player spawn point
3. No holes in walls exposing void
4. Only valid characters: `0`, `1`, `N`, `S`, `E`, `W`, ` `, `\n`

## 🔬 Technical Details

### Raycasting Algorithm

1. **For each vertical column on screen:**
   - Cast a ray from player position
   - Calculate intersection with horizontal grid lines
   - Calculate intersection with vertical grid lines
   - Choose closest wall hit

2. **Wall projection:**
   ```c
   wall_height = (TILE_SIZE * WINDOW_HEIGHT) / (distance * cos(angle))
   ```

3. **Fish-eye correction:**
   - Multiply distance by `cos(ray_angle - player_angle)`
   - Prevents distortion at screen edges

### Constants

```c
#define WINDOW_WIDTH  1088
#define WINDOW_HEIGHT 448
#define TILE_SIZE     32
#define FOV           (60 * M_PI / 180)  // 60 degrees
```

### Performance

- **Target**: 60+ FPS
- **Resolution**: 1088x448
- **Ray count**: WINDOW_WIDTH (1088 rays per frame)

## 📚 Resources

### Essential Reading

1. **[RAYCASTING_EXPLAINED.md](RAYCASTING_EXPLAINED.md)** - Detailed algorithm breakdown
2. [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
3. [MLX42 Documentation](https://github.com/codam-coding-college/MLX42)
4. [42 Norminette Guide](https://github.com/42School/norminette)

### Video Tutorials

- [Raycasting Explained](https://www.youtube.com/watch?v=gYRrGTC7GtA)
- [Wolf3D Engine Overview](https://www.youtube.com/watch?v=eOCQfxRQ2pY)

### Mathematical Concepts

- **Trigonometry**: sin, cos, tan
- **Pythagorean theorem**: distance calculation
- **DDA algorithm**: grid traversal
- **Vector mathematics**: direction and movement

## 🛠️ Troubleshooting

### Common Issues

**Textures not loading:**
```bash
# Regenerate textures
python3 generate_textures.py

# Check file permissions
chmod 644 textures/*.png
```

**Segmentation fault:**
- Check map validation
- Verify texture pointers aren't NULL
- Ensure array bounds are respected

**Norminette errors:**
```bash
# Check specific file
norminette src/assets/ray_caster.c

# Common fixes:
# - Replace spaces with tabs
# - Split functions > 25 lines
# - Limit lines to 80 characters
```

**Compilation errors:**
```bash
# Clean and rebuild
make fclean
make
```

## 📝 License

This project is part of the 42 School curriculum.

## 👥 Authors

- Your Name (@your-github-username)

## 🎓 42 School Project

**Grade**: _/100  
**Status**: In progress / Completed  
**Evaluation**: [Date]

---

**Good luck with your Cub3D journey! 🚀**