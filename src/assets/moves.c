/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:49:56 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/18 23:22:12 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_radius(t_map *map, double x, double y, int i)
{
	double	rad;
	int		j;
	int		tx;
	int		ty;

	rad = 3.0;
	j = -rad;
	while (j <= rad)
	{
		tx = (x + j) / TILE_SIZE;
		ty = (y + i) / TILE_SIZE;
		if (map->arr[ty][tx] == '1')
			return (0);
		j += rad;
	}
	return (1);
}

int	check_wall(t_map *map, double x, double y)
{
	int		j;
	int		i;
	double	rad;

	rad = 3.0;
	j = (int)(x / TILE_SIZE);
	i = (int)(y / TILE_SIZE);
	if (i < 0 || i >= map->map_height || j < 0
		|| j >= ft_strlens(map->arr[i]) || map->arr[i][j] == '1')
		return (0);
	i = -rad;
	while (i <= rad)
	{
		if (!check_radius(map, x, y, i))
			return (0);
		i += rad;
	}
	return (1);
}

void	angle_reset(double *angle)
{
	if (*angle <= 0)
		*angle += 2 * M_PI;
	if (*angle > 2 * M_PI)
		*angle -= 2 * M_PI;
}

void	choose_angle(t_map *map, double *angle)
{
	if (map->f == 0)
		*angle = map->player.rotation_angle;
	else if (map->f == 1)
		*angle = map->player.rotation_angle - (M_PI / 2);
	else if (map->f == 2)
		*angle = map->player.rotation_angle + (M_PI / 2);
}

void	update_player(t_map *map)
{
	double	move_steps;
	double	angle;
	double	x;
	double	y;

	if (map->f != 0)
		move_steps = MOVE_SPEED;
	else
		move_steps = map->player.walk_direction * MOVE_SPEED;
	map->player.rotation_angle += (map->player.turn_direction * ROTAT_SPEED);
	angle_reset(&map->player.rotation_angle);
	choose_angle(map, &angle);
	angle_reset(&angle);
	x = map->player.x + cos(angle) * move_steps;
	y = map->player.y + sin(angle) * move_steps;
	if (check_wall(map, x, y))
	{	
		map->player.x = x;
		map->player.y = y;
		clear_dir_img(map);
		ray_caster(map);
	}
	map->player.walk_direction = 0;
	map->player.turn_direction = 0;
	map->f = 0;
}
