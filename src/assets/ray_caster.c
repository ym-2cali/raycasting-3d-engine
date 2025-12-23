/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:06:17 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/23 02:01:53 by yael-maa         ###   ########.fr       */
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

double	horizontal_intersection(t_map *map,
	double angle, double *hit_x, double *hit_y)
{
	double	y_inter;
	double	y_step;
	double	x_inter;
	double	x_step;
	int		facing_down;

	facing_down = (angle > 0 && angle < M_PI);
	set_var_hor(map, &y_inter, angle, &y_step);
	x_inter = map->player.x + (y_inter - map->player.y) / tan(angle);
	set_var_hor1(&x_step, angle, &y_step);
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

double	vertical_intersection(t_map *map, double angle,
	double *hit_x, double *hit_y)
{
	double	y_inter;
	double	y_step;
	double	x_step;
	double	x_inter;
	int		facing_right;

	facing_right = (angle < M_PI / 2 || angle > 3 * M_PI / 2);
	set_var_ver(map, &x_inter, angle);
	y_inter = map->player.y + (x_inter - map->player.x) * tan(angle);
	set_var_ver1(&y_step, &x_step, angle);
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

void	ray_caster(t_map *map)
{
	double	ray_angle;
	int		i;

	i = -1;
	while ((++i) < WINDOW_WIDTH)
	{
		ray_angle = (map->player.rotation_angle - (FOV / 2))
			+ (i * (FOV / WINDOW_WIDTH));
		angle_reset(&ray_angle);
		ray_caster_helper(map, ray_angle, i);
	}
}
