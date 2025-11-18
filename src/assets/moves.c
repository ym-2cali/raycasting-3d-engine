/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:49:56 by yael-maa          #+#    #+#             */
/*   Updated: 2025/11/18 10:45:13 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_right(t_map *map, double x, double y)
{
	int	i;
	int	j;

	i = trunc(y - (TILE_SIZE / 2));
	j = trunc(x + (TILE_SIZE / 2));
	while (i % 32 != 0)
		i--;
	while (j % 32 != 0)
		j--;
	i /= TILE_SIZE;
	j /= TILE_SIZE;
	if (i < 0 || i >= map->map_height || j < 0 || j >= ft_strlen(map->arr[i]))
		return (0);
	if (map->arr[i][j] != '1')
		return (1);
	return (0);
}

int	check_bottom(t_map *map, double x, double y)
{
	int	i;
	int	j;

	i = trunc(y + (TILE_SIZE / 2));
	j = trunc(x - (TILE_SIZE / 2));
	while (i % 32 != 0)
		i--;
	while (j % 32 != 0)
		j--;
	i /= TILE_SIZE;
	j /= TILE_SIZE;
	if (i < 0 || i >= map->map_height || j < 0 || j >= ft_strlen(map->arr[i]))
		return (0);
	if (map->arr[i][j] != '1')
		return (1);
	return (0);
}

int	check_wall(t_map *map, double x, double y)
{
	int	j;
	int	i;

	j = (int)(x / map->x_size);
	i = (int)(y / map->y_size);	
	if (i < 0 || i >= map->map_height || j < 0 || j >= ft_strlen(map->arr[i]))
		return (0);
	if (map->arr[i][j] != '1' && check_bottom(map, x, y) && check_right(map, x, y))
		return (1);
	return (0);
}

void 	update_player(t_map *map)
{
	double	move_steps;
	double	x;
	double	y;

	move_steps = map->player.walk_direction * MOVE_SPEED;
	map->player.rotation_angle += (map->player.turn_direction * ROTAT_SPEED);
	x = map->player.x + cos(map->player.rotation_angle) * move_steps;
	y = map->player.y + sin(map->player.rotation_angle) * move_steps;
	if (check_wall(map, x, y))
	{	
		map->player.x = x;
		map->player.y = y;
		mlx_delete_image(map->mlx, map->player_img);
		map->player_img = mlx_new_image(map->mlx, map->x_size, map->y_size);
		player_img(map, get_color(204, 57, 9, 255));
		mlx_image_to_window(map->mlx, map->player_img, map->player.x, map->player.y);
	}
	map->player.walk_direction = 0;
	map->player.turn_direction = 0;
}
