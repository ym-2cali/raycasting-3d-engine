/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:49:56 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/13 12:42:26 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"


void	round_it(t_map *map, int *i, int *j, int *flag)
{
	if (map->player.rotation_angle >= 0 && map->player.rotation_angle <  M_PI / 2)
	{
		while (*j % 32)
			(*j)--;
		while (*i % 32)
			(*i)--;
		*flag = 1;
	}
	else if (map->player.rotation_angle >= M_PI / 2 && map->player.rotation_angle < M_PI)
	{
		while (*j % 32)
			(*j)++;
		while (*i % 32)
			(*i)--;	
		*flag = 2;
	}
	else if (map->player.rotation_angle >= M_PI && map->player.rotation_angle < 3 * M_PI / 2)
	{
		while (*j % 32)
			(*j)++;
		while (*i % 32)
			(*i)++;
		*flag = 3;	
	}
	else if (map->player.rotation_angle >= 3 * M_PI / 2 && map->player.rotation_angle < 2 * M_PI)
	{
		while (*j % 32)
			(*j)--;
		while (*i % 32)
			(*i)++;
		*flag = 4;
	}
}

int	check_horizontal(t_map *map, double x, double y)
{
	int	i;
	int	j;

	i = trunc(y);
	j = trunc(x);
	while (j % 32 != 0)
		j--;
	i /= TILE_SIZE;
	j /= TILE_SIZE;
	if (i < 0 || i >= map->map_height || j < 0 || j >= ft_strlens(map->arr[i]))
		return (0);
	if (map->arr[i][j] != '1')
		return (1);
	return (0);
}


int	check_vertical(t_map *map, double x, double y)
{
	int	i;
	int	j;

	i = trunc(y);
	j = trunc(x);
	while (i % 32 != 0)
		i--;
	i /= TILE_SIZE;
	j /= TILE_SIZE;
	if (i < 0 || i >= map->map_height || j < 0 || j >= ft_strlens(map->arr[i]))
		return (0);
	if (map->arr[i][j] != '1')
		return (1);
	return (0);
}

int	check_between(t_map *map, double x, double y)
{
	int	i;
	int	j;
	int	flag;

	// i = floor(y);
	// j = floor(x);
	// flag = 0;
	// round_it(map, &i, &j, &flag);
	// i /= TILE_SIZE;
	// j /= TILE_SIZE;
	// printf("%d\n",flag);
	// if (flag == 1)
	// {
	// 	if (map->arr[i - 1][j] == '1' && map->arr[i][j - 1] == '1')
	// 		return (0);
	// }
	// else if (flag == 2)
	// {
	// 	if (map->arr[i][j] == '1' && map->arr[i - 1][j - 1] == '1')
	// 		return (0);
	// }
	// else if (flag == 3)
	// {
	// 	if (map->arr[i][j - 1] == '1' && map->arr[i - 1][j] == '1')
	// 		return (0);
	// }
	// else if (flag == 4)
	// {
	// 	if (map->arr[i][j] != '1' && map->arr[i - 1][j - 1] != '1')	
	// 		return (0);
	// }
	return (1);
}

int	check_wall(t_map *map, double x, double y)
{
	int	j;
	int	i;

	j = (int)(x / map->x_size);
	i = (int)(y / map->y_size);	
	if (i < 0 || i >= map->map_height || j < 0 || j >= ft_strlens(map->arr[i]))
		return (0);
	if (check_horizontal(map, x, y) && check_vertical(map, x, y) && check_between(map, x, y))
		return (1);
	// return 1;
	return (0);
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
