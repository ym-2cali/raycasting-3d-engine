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
    // bool facing_left = !facing_right;
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

static mlx_texture_t	*get_wall_texture(t_map *map, int vertical, double a)
{
	if (vertical)
	{
		if (a < M_PI_2 || a > 3 * M_PI_2)
			return (map->east_tex);
		return (map->west_tex);
	}
	if (a > 0 && a < M_PI)
		return (map->south_tex);
	return (map->north_tex);
}

static double	get_hit_pos(double hit_x, double hit_y, int vertical)
{
	double	pos;

	if (vertical)
		pos = fmod(hit_y, TILE_SIZE) / TILE_SIZE;
	else
		pos = fmod(hit_x, TILE_SIZE) / TILE_SIZE;
	if (pos < 0)
		pos += 1.0;
	return (pos);
}

void draw_wall(t_map *map, t_ray_data ray, int x)
{
	int				y;
	int				wall_h;
	mlx_texture_t	*tex;
	double			hit_pos;
	uint32_t		color;

	y = 0;
	wall_h = ray.wall_end - ray.wall_start;
	tex = get_wall_texture(map, ray.is_vertical, ray.angle);
	hit_pos = get_hit_pos(ray.hit_x, ray.hit_y, ray.is_vertical);
	while (y < ray.wall_start)
		mlx_put_pixel(map->dir_img, x, y++, get_color(map->ceiling_color[0],
				map->ceiling_color[1], map->ceiling_color[2], 255));
	while (y < ray.wall_end)
	{
		color = sample_texture(tex, hit_pos, y, ray.wall_start, wall_h);
		mlx_put_pixel(map->dir_img, x, y++, color);
	}
	while (y < WINDOW_HEIGHT)
		mlx_put_pixel(map->dir_img, x, y++, get_color(map->floor_color[0],
				map->floor_color[1], map->floor_color[2], 255));
}

static void	init_ray(t_ray_data *ray, t_map *map, int i)
{
	double	start_angle;

	start_angle = map->player.rotation_angle - (FOV / 2);
	ray->angle = start_angle + (i * (FOV / WINDOW_WIDTH));
	if (ray->angle < 0)
		ray->angle += 2 * M_PI;
	if (ray->angle > 2 * M_PI)
		ray->angle -= 2 * M_PI;
}

static void	calc_wall_proj(t_ray_data *ray, double dist, double p_angle)
{
	double	corrected_dist;

	corrected_dist = dist * cos(ray->angle - p_angle);
	if (corrected_dist < 0.1)
		corrected_dist = 0.1;
	ray->wall_dis = (TILE_SIZE * (WINDOW_HEIGHT / 2.0)) / corrected_dist;
	if (ray->wall_dis > WINDOW_HEIGHT * 1.5)
		ray->wall_dis = WINDOW_HEIGHT * 1.5;
	ray->wall_start = (WINDOW_HEIGHT / 2) - (int)ray->wall_dis;
	ray->wall_end = (WINDOW_HEIGHT / 2) + (int)ray->wall_dis;
	if (ray->wall_start < 0)
		ray->wall_start = 0;
	if (ray->wall_end > WINDOW_HEIGHT)
		ray->wall_end = WINDOW_HEIGHT;
}

void ray_caster(t_map *map)
{
	t_ray_data	ray;
	double		hor_x, hor_y, ver_x, ver_y;
	double		hor_dist, ver_dist, dist;
	int			i;

	i = -1;
	while ((++i) < WINDOW_WIDTH)
	{
		init_ray(&ray, map, i);
		hor_dist = horizontal_intersection(map, ray.angle, &hor_x, &hor_y);
		ver_dist = vertical_intersection(map, ray.angle, &ver_x, &ver_y);
		ray.is_vertical = (ver_dist < hor_dist);
		if (ray.is_vertical)
		{
			ray.hit_x = ver_x;
			ray.hit_y = ver_y;
			dist = ver_dist;
		}
		else
		{
			ray.hit_x = hor_x;
			ray.hit_y = hor_y;
			dist = hor_dist;
		}
		calc_wall_proj(&ray, dist, map->player.rotation_angle);
		draw_wall(map, ray, i);
	}
}
