/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:49:56 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/18 02:40:19 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_wall(t_map *map, double x, double y)
{
	int		j;
	int		i;
	double	rad;
	int		tx;
	int		ty;

	rad = 3.0;
	j = (int)(x / TILE_SIZE);
	i = (int)(y / TILE_SIZE);
	printf("i = %d j = %d\n", i, j);
	if (i < 0 || i >= map->map_height || j < 0 || j >= ft_strlens(map->arr[i]))
		return (0);
	if (map->arr[i][j] == '1')
		return (0);
	i = -rad;
	while (i <= rad)
	{
		j = -rad;
		while (j <= rad)
		{
			tx = (x + j) / TILE_SIZE;
			ty = (y + i) / TILE_SIZE;
			if (map->arr[ty][tx] == '1'){
				printf("ty = %d tx = %d\n", ty, tx);
				return (0);
			}
			j += rad;
		}
		i += rad;
	}
	// if (check_horizontal(map, x, y) && check_vertical(map, x, y))
	// 	return (1);
	return (1);
}

void 	update_player(t_map *map)
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
	if (map->player.rotation_angle < 0)
		map->player.rotation_angle += 2 * M_PI;
    if (map->player.rotation_angle > 2 * M_PI)
		map->player.rotation_angle -= 2 * M_PI;
	if (map->f == 0)
	{
		x = map->player.x + cos(map->player.rotation_angle) * move_steps;
		y = map->player.y + sin(map->player.rotation_angle) * move_steps;
	}
	else if (map->f == 1)
	{
		angle = map->player.rotation_angle - (M_PI / 2);
		if (angle <= 0)
			angle += 2 * M_PI;
    	if (angle > 2 * M_PI)
			angle -= 2 * M_PI;
		x = map->player.x + cos(angle) * move_steps;
		y = map->player.y + sin(angle) * move_steps;		
	}
	else if (map->f == 2)
	{
		angle = map->player.rotation_angle + (M_PI / 2);
		if (angle <= 0)
			angle += 2 * M_PI;
    	if (angle > 2 * M_PI)
			angle -= 2 * M_PI;
		x = map->player.x + cos(angle) * move_steps;
		y = map->player.y + sin(angle) * move_steps;
	}
	if (check_wall(map, x, y))
	{	
		map->player.x = x;
		map->player.y = y;
		clear_dir_img(map);
		ray_caster(map);
		mlx_delete_image(map->mlx, map->player_img);
		map->player_img = mlx_new_image(map->mlx, TILE_SIZE, TILE_SIZE);
		player_img(map, get_color(204, 57, 9, 255));
		mlx_image_to_window(map->mlx, map->player_img, map->player.x - TILE_SIZE / 2, map->player.y - TILE_SIZE / 2);
	}
	map->player.walk_direction = 0;
	map->player.turn_direction = 0;
	map->f = 0;
}
