/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:06:17 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/23 00:25:52 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_wall(t_map *map, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)(x / TILE_SIZE);
	my = (int)(y / TILE_SIZE);
	if (mx < 0 || my < 0 || my >= map->map_height
		|| mx >= (int)ft_strlens(map->arr[my]))
		return (1);
	return (map->arr[my][mx] == '1');
}

static double	horizontal_intersection(t_map *map,
	double angle, double *hit_x, double *hit_y)
{
	double	y_inter;
	double	y_step;
	double	x_inter;
	double	x_step;
	int		facing_down;

	facing_down = (angle > 0 && angle < M_PI);
	y_inter = floor(map->player.y / TILE_SIZE) * TILE_SIZE;
	if (facing_down)
		y_inter += TILE_SIZE;
	else
		y_inter -= 0.0001;
	x_inter = map->player.x + (y_inter - map->player.y) / tan(angle);
	if (facing_down)
		y_step = TILE_SIZE;
	else
		y_step = -TILE_SIZE;
	x_step = y_step / tan(angle);
	while (x_inter >= 0 && y_inter >= 0
		&& x_inter < map->map_width * TILE_SIZE
		&& y_inter < map->map_height * TILE_SIZE)
	{
		if (is_wall(map, x_inter, y_inter))
		{
			*hit_x = x_inter;
			*hit_y = y_inter;
			return (hypot(x_inter - map->player.x, y_inter - map->player.y));
		}
		x_inter += x_step;
		y_inter += y_step;
	}
	return (1e30);
}

double	vertical_intersection(t_map *map, double angle, double *hit_x, double *hit_y)
{
	double y_inter, x_inter;
	double y_step, x_step;

	int facing_right = (angle < M_PI / 2 || angle > 3 * M_PI / 2);
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
		draw_wall_with_texture(map, i, ray_angle, hor_dist, ver_dist, wall_dis);
	}
}
