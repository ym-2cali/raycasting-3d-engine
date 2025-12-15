# TODO: Textures & Walls Implementation for cub3d

## Current Status
- ✅ Texture path parsing (NO, SO, WE, EA) working
- ✅ Basic raycasting with wall distance calculation
- ✅ Ceiling and floor colors rendering
- ❌ Texture loading not implemented
- ❌ Texture rendering not implemented (currently solid blue walls)

## Tasks to Complete

### 1. Create Texture Image Files (PNG format)
- [ ] Create or obtain 4 wall texture images (North, South, East, West)
- [ ] Recommended size: 64x64 or 128x128 pixels
- [ ] Format: PNG (MLX42 supports PNG natively)
- [ ] Place in `/textures/` directory

### 2. Load Textures at Initialization
- [ ] Add texture loading in `get_img()` or `main_merge.c`
- [ ] Use `mlx_load_png(path)` to load each texture
- [ ] Store mlx_texture_t* for each direction
- [ ] Handle load failures gracefully

### 3. Add Texture Pointers to t_map Structure
In `inc/cub3d.h`, add to `t_map`:
```c
mlx_texture_t*  north_tex;
mlx_texture_t*  south_tex;
mlx_texture_t*  east_tex;
mlx_texture_t*  west_tex;
```

### 4. Implement Texture Coordinate Calculation
In `src/assets/ray_caster.c`:
- [ ] Track which wall face was hit (vertical/horizontal intersection)
- [ ] Calculate exact hit point on wall
- [ ] Map hit point to texture X coordinate (0 to texture_width)

### 5. Determine Wall Face (N/S/E/W)
- [ ] For horizontal intersections: check if ray faces up (N) or down (S)
- [ ] For vertical intersections: check if ray faces left (W) or right (E)
- [ ] Store wall_face information with ray hit data

### 6. Calculate Texture X Coordinate
- [ ] Get fractional part of hit position (x or y coordinate)
- [ ] Multiply by texture width to get texture column
- [ ] Formula: `tex_x = (int)(hit_frac * texture_width) % texture_width`

### 7. Sample Texture and Draw Textured Walls
In `draw_wall()` function:
- [ ] Calculate texture Y coordinate for each pixel
- [ ] Formula: `tex_y = (pixel_y - wall_start) * tex_height / wall_height`
- [ ] Get pixel color from texture buffer
- [ ] MLX42: `color = texture->pixels[(tex_y * tex_width + tex_x) * 4]`
- [ ] Draw pixel with texture color instead of solid blue

### 8. Update Map Files
- [ ] Replace `./path_to_the_north_texture` with actual paths
- [ ] Example: `NO ./textures/north_wall.png`
- [ ] Update all 4 map files in `/maps/` directory

### 9. Error Handling
- [ ] Check if texture files exist before loading
- [ ] Handle mlx_load_png() returning NULL
- [ ] Display error message and exit gracefully
- [ ] Free allocated textures on cleanup

### 10. Testing
- [ ] Compile and run: `make && ./cub3d maps/test_fixed.cub`
- [ ] Verify all 4 wall textures display correctly
- [ ] Test with different maps
- [ ] Check performance (should be smooth)

---

## Information Needed for Implementation

Please provide the following details:

1. **MLX42 Texture API:**
   - How to load PNG: `mlx_texture_t* mlx_load_png(const char* path)`?
   - How to access pixel data: direct buffer or helper function?
   - Pixel format: RGBA? byte order?
   - How to free textures: `mlx_delete_texture()`?

2. **42 Project Requirements:**
   - Specific texture sampling rules?
   - Handling of texture transparency?
   - Any performance constraints?
   - Error message format?

3. **Texture Files:**
   - Do you have texture files ready?
   - What resolution are they?
   - Where should they be located?

---

## Implementation Order

**Phase 1 (Structure):**
1. Add texture pointers to t_map
2. Create texture loading function
3. Update initialization code

**Phase 2 (Core Logic):**
4. Modify ray_caster to track wall face
5. Calculate texture coordinates
6. Store hit information with face data

**Phase 3 (Rendering):**
7. Rewrite draw_wall() to sample textures
8. Test with one texture first
9. Add all 4 textures

**Phase 4 (Polish):**
8. Update all map files
9. Add comprehensive error handling
10. Final testing

---

## Files to Modify

- `inc/cub3d.h` - Add texture pointers to t_map
- `src/assets/imgs.c` - Add texture loading in get_img()
- `src/assets/ray_caster.c` - Add wall face detection, modify draw_wall()
- `main_merge.c` - Add texture cleanup on exit
- `maps/*.cub` - Update texture paths

---

## Notes

- Current draw_wall() draws solid blue: `get_color(0, 0, 255, 255)`
- Need to replace this with texture pixel sampling
- Remember to free textures with mlx_delete_texture() on cleanup
- Test incrementally - one texture at a time
