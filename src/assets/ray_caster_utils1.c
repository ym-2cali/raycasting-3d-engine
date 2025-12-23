/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 01:10:07 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/23 02:05:00 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	set_var_ver(t_map *map, double *x_inter, double angle)
{
	int		facing_right;

	facing_right = (angle < M_PI / 2 || angle > 3 * M_PI / 2);
	*x_inter = floor(map->player.x / TILE_SIZE) * TILE_SIZE;
	if (facing_right)
		*x_inter += TILE_SIZE;
	else
		*x_inter -= 0.0001;
}

void	set_var_ver1(double *y_step, double *x_step, double angle)
{
	int		facing_right;

	facing_right = (angle < M_PI / 2 || angle > 3 * M_PI / 2);
	if (facing_right)
		*x_step = TILE_SIZE;
	else
		*x_step = -TILE_SIZE;
	*y_step = *x_step * tan(angle);
}

void	set_var_hor(t_map *map, double *y_inter, double angle, double *y_step)
{
	int		facing_down;

	facing_down = (angle > 0 && angle < M_PI);
	*y_inter = floor(map->player.y / TILE_SIZE) * TILE_SIZE;
	if (facing_down)
		*y_inter += TILE_SIZE;
	else
		*y_inter -= 0.0001;
}

void	set_var_hor1(double *x_step, double angle, double *y_step)
{
	int		facing_down;

	facing_down = (angle > 0 && angle < M_PI);
	if (facing_down)
		*y_step = TILE_SIZE;
	else
		*y_step = -TILE_SIZE;
	*x_step = *y_step / tan(angle);
}

void	ray_caster_helper(t_map *map, double ray_angle, int i)
{
	double			hor_dist;
	double			ver_dist;
	double			hor_x;
	double			hor_y;
	t_ray_params	params;

	hor_dist = horizontal_intersection(map, ray_angle, &hor_x, &hor_y);
	ver_dist = vertical_intersection(map, ray_angle, &hor_x, &hor_y);
	if (hor_dist < ver_dist)
		params = (t_ray_params){i, ray_angle, hor_dist, ver_dist,
			(TILE_SIZE * WINDOW_HEIGHT)
			/ (hor_dist * cos(ray_angle - map->player.rotation_angle))};
	else
		params = (t_ray_params){i, ray_angle, hor_dist, ver_dist,
			(TILE_SIZE * WINDOW_HEIGHT)
			/ (ver_dist * cos(ray_angle - map->player.rotation_angle))};
	draw_wall_with_texture(map, &params);
}
