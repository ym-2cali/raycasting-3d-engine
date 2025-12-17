#include "../../inc/cub3d.h"

static int is_wall(t_map *map, double x, double y)
{
    int mx = (int)(x / TILE_SIZE);
    int my = (int)(y / TILE_SIZE);

    if (mx < 0 || my < 0 || my >= map->map_height || mx >= (int)ft_strlens(map->arr[my]))
        return (1);
    return (map->arr[my][mx] == '1');
}

static double horizontal_intersection(t_map *map, double angle, double *hit_x, double *hit_y)
{
    double y_inter, x_inter;
    double y_step, x_step;

    int facing_down = (angle > 0 && angle < M_PI);
    int facing_up = !facing_down;
    y_inter = floor(map->player.y / TILE_SIZE) * TILE_SIZE;
    if (facing_down) 
		y_inter += TILE_SIZE;
    else
		y_inter -= 0.0001;
    x_inter = map->player.x + (y_inter - map->player.y) / tan(angle);
    y_step = facing_down ? TILE_SIZE : -TILE_SIZE;
    x_step = y_step / tan(angle);
    while (x_inter >= 0 && y_inter >= 0 &&
           x_inter < map->map_width * TILE_SIZE &&
           y_inter < map->map_height * TILE_SIZE)
    {
        if (is_wall(map, x_inter, y_inter))
        {
            *hit_x = x_inter;
            *hit_y = y_inter;
            return hypot(x_inter - map->player.x, y_inter - map->player.y);
        }
        x_inter += x_step;
        y_inter += y_step;
    }
    return 1e30;
}

double vertical_intersection(t_map *map, double angle, double *hit_x, double *hit_y)
{
    double y_inter, x_inter;
    double y_step, x_step;

    int facing_right = (angle < M_PI_2 || angle > 3*M_PI_2);
    int facing_left = !facing_right;
    x_inter = floor(map->player.x / TILE_SIZE) * TILE_SIZE;
    if (facing_right)
		x_inter += TILE_SIZE;
    else
		x_inter -= 0.0001;
    y_inter = map->player.y + (x_inter - map->player.x) * tan(angle);
    x_step = facing_right ? TILE_SIZE : -TILE_SIZE;
    y_step = x_step * tan(angle);
    while (x_inter >= 0 && y_inter >= 0 &&
           x_inter < map->map_width * TILE_SIZE &&
           y_inter < map->map_height * TILE_SIZE)
    {
        if (is_wall(map, x_inter, y_inter))
        {
            *hit_x = x_inter;
            *hit_y = y_inter;
            return hypot(x_inter - map->player.x, y_inter - map->player.y);
        }
        x_inter += x_step;
        y_inter += y_step;
    }
    return 1e30;
}

void draw_wall_with_texture(t_map *map, int x, double ray_angle, double hor_dist, double ver_dist, double wall_dis)
{
    int y = 0;
    int wall_start = WINDOW_HEIGHT / 2 - (int)wall_dis;
    int wall_end = WINDOW_HEIGHT / 2 + (int)wall_dis;
    mlx_texture_t *texture;
    double wall_x;
    int tex_x;
    int facing_up, facing_right;
    
    // Clamp wall boundaries
    if (wall_start < 0)
        wall_start = 0;
    if (wall_end > WINDOW_HEIGHT)
        wall_end = WINDOW_HEIGHT;
    
    // Determine ray direction
    facing_up = (ray_angle > M_PI && ray_angle < 2 * M_PI);
    facing_right = (ray_angle < M_PI_2 || ray_angle > 3 * M_PI_2);
    
    // STEP 1: Select texture based on wall orientation
    if (hor_dist < ver_dist)
    {
        // Horizontal wall hit
        if (facing_up)
            texture = map->north_texture;
        else
            texture = map->south_texture;
        
        // Calculate X position on wall
        wall_x = map->player.x + hor_dist * cos(ray_angle);
    }
    else
    {
        // Vertical wall hit
        if (facing_right)
            texture = map->east_texture;
        else
            texture = map->west_texture;
        
        // Calculate Y position on wall
        wall_x = map->player.y + ver_dist * sin(ray_angle);
    }
    
    // STEP 2: Calculate texture X coordinate
    wall_x /= TILE_SIZE;
    wall_x = wall_x - floor(wall_x);  // Get fractional part
    tex_x = (int)(wall_x * texture->width);
    
    // STEP 3: Handle texture flipping
    // South walls (horizontal, facing down) need flipping
    if (hor_dist < ver_dist && !facing_up)
        tex_x = texture->width - tex_x - 1;
    // East walls (vertical, facing right) need flipping
    if (hor_dist >= ver_dist && facing_right)
        tex_x = texture->width - tex_x - 1;
    
    // Clamp tex_x
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= (int)texture->width)
        tex_x = texture->width - 1;
    
    // Draw ceiling
    while (y < wall_start)
        mlx_put_pixel(map->dir_img, x, y++, get_color(map->ceiling_color[0], 
                     map->ceiling_color[1], map->ceiling_color[2], 255));
    
    // STEP 4: Draw textured wall
    while (wall_start < wall_end)
    {
        // Calculate vertical texture coordinate
        double wall_y = (double)(wall_start - (WINDOW_HEIGHT / 2 - (int)wall_dis)) 
                       / (double)(wall_dis * 2);
        int tex_y = (int)(wall_y * texture->height);
        
        // Clamp tex_y
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= (int)texture->height)
            tex_y = texture->height - 1;
        
        // Get pixel from texture
        int pixel_index = (tex_y * texture->width + tex_x) * texture->bytes_per_pixel;
        uint8_t *pixel = &texture->pixels[pixel_index];
        
        // Compose color (RGBA format)
        uint32_t color = (pixel[0] << 24) | (pixel[1] << 16) | 
                        (pixel[2] << 8) | pixel[3];
        
        mlx_put_pixel(map->dir_img, x, wall_start++, color);
    }
    
    // Draw floor
    while (wall_end < WINDOW_HEIGHT)
        mlx_put_pixel(map->dir_img, x, wall_end++, get_color(map->floor_color[0], 
                     map->floor_color[1], map->floor_color[2], 255));
}


void ray_caster(t_map *map)
{
    double start_angle = map->player.rotation_angle - (FOV / 2);
    double ray_angle;
    double hor_x, hor_y, ver_x, ver_y;
    double hor_dist, ver_dist;
    int n_rays = 320;
	int i;
    double wall_dis;
	i = -1;
    while ((++i) < WINDOW_WIDTH)
    {
        ray_angle = start_angle + (i * (FOV / WINDOW_WIDTH));
        if (ray_angle < 0)
			ray_angle += 2 * M_PI;
        if (ray_angle > 2 * M_PI)
			ray_angle -= 2 * M_PI;
        hor_dist = horizontal_intersection(map, ray_angle, &hor_x, &hor_y);
        ver_dist = vertical_intersection(map, ray_angle, &ver_x, &ver_y);
        double nm = hor_dist < ver_dist ? hor_dist : ver_dist; 
        wall_dis = (TILE_SIZE * WINDOW_HEIGHT) / (nm * cos(ray_angle - map->player.rotation_angle));
        
        // Draw wall with texture
        draw_wall_with_texture(map, i, ray_angle, hor_dist, ver_dist, wall_dis);
    }
}
