/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:02:45 by yael-maa          #+#    #+#             */
/*   Updated: 2025/10/28 16:23:12 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	get_img(t_map *map)
{
	map->floor_img = mlx_new_image(map->mlx, map->x_size, map->y_size);
	map->wall_img = mlx_new_image(map->mlx, map->x_size, map->y_size);
	map->img = mlx_new_image(map->mlx, map->x_size, map->y_size);
	map->player_img = mlx_new_image(map->mlx, map->x_size, map->y_size);
}

void	draw_img(t_map *map, mlx_image_t* img, uint32_t color)
{
	int			x;
	int			y;

	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->x_size)
			mlx_put_pixel(img, x++, y, color);
		y++;
	}
}


void	line_dir(t_map *map, int x, int y, uint32_t color)
{
	int	cx;
	int	cy;

	cx = map->x_size / 2;
	cy = map->y_size / 2;
	if (map->player.spg_or == N)
	{	
		if (x == cx && y < cy)
			mlx_put_pixel(map->player_img, x, y, color);
	}
	else if (map->player.spg_or == S)
	{
		if (x == cx && y > cy)
			mlx_put_pixel(map->player_img, x, y, color);
	}
	else if (map->player.spg_or == E)
	{
		if (x > cx && y == cy)
			mlx_put_pixel(map->player_img, x, y, color);
	}
	else if (map->player.spg_or == W)
	{
		if (x < cx && y == cy)
			mlx_put_pixel(map->player_img, x, y, color);
	}
}

// void	line_dir(t_map *map, int x, int y)
// {
// 	int	cx;
// 	int	cy;

// 	cx = map->x_size / 2;
// 	cy = map->y_size / 2;
// 	// if (x == cx)
// 	// {
// 	// 	if (y < cy && map->player.spg_or = N)
// 	// 		mlx_put_pixel(map->player_img, x, y, color);
// 	// 	else if (map->player.spg_or = S && y > cy)
// 	// 		mlx_put_pixel(map->player_img, x, y, color);
// 	// }
// 	// else if (y == cy)
// 	// {
// 	// 	if (x > cx && map->player.spg_or = E)
// 	// 		mlx_put_pixel(map->player_img, x, y, color);
// 	// 	else if (map->player.spg_or = S && y > cy)
// 	// 		mlx_put_pixel(map->player_img, x, y, color);
// 	// }
// 	if (map->player.spg_or == N)
// 	{	
// 		if (x == cx && y < cy)
// 			mlx_put_pixel(map->player_img, x, y, color);
// 	}
// 	else if (map->player.spg_or == S)
// 	{
// 		if (x == cx && y > cy)
// 			mlx_put_pixel(map->player_img, x, y, color);
// 	}
// 	else if (map->player.spg_or == E)
// 	{
// 		if (x > cx && y == cy)
// 			mlx_put_pixel(map->player_img, x, y, color);
// 	}
// 	else if (map->player.spg_or == W)
// 	{
// 		if (x < cx && y == cy)
// 			mlx_put_pixel(map->player_img, x, y, color);
// 	}
// }

void	player_img(t_map *map, uint32_t color)
{
	int	cx;
	int	cy;
	int	r;
	int	y;
	int	x;
	int	dx;
	int	dy;

	cx = map->x_size / 2;
	cy = map->y_size / 2;
	r = (map->x_size < map->y_size ? map->x_size : map->y_size) / 4;
	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while(x < map->x_size)
		{
			dx = x - cx;
			dy = y - cy;
			line_dir(map, x , y, color);
			if (((dx * dx) + (dy * dy) <= (r * r)))
				mlx_put_pixel(map->player_img, x, y, color);
			x++;
		}
		y++;
	}
}
