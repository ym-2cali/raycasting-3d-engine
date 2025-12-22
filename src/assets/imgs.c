/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:02:45 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/18 22:51:15 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	destroy_imgs(t_map *map)
{
	if (map->floor_img)
		mlx_delete_image(map->mlx, map->floor_img);
	if (map->wall_img)
		mlx_delete_image(map->mlx, map->wall_img);
	if (map->img)
		mlx_delete_image(map->mlx, map->img);
	if (map->player_img)
		mlx_delete_image(map->mlx, map->player_img);
	if (map->dir_img)
		mlx_delete_image(map->mlx, map->dir_img);
}

int	get_img(t_map *map)
{
	map->floor_img = mlx_new_image(map->mlx, TILE_SIZE, TILE_SIZE);
	map->wall_img = mlx_new_image(map->mlx, TILE_SIZE, TILE_SIZE);
	map->img = mlx_new_image(map->mlx, TILE_SIZE, TILE_SIZE);
	map->player_img = mlx_new_image(map->mlx, TILE_SIZE, TILE_SIZE);
	map->dir_img = mlx_new_image(map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!map->floor_img || !map->wall_img || !map->img
		|| !map->player_img || !map->dir_img)
	{
		write(2, "Image Creation Failed\n", 23);
		destroy_imgs(map);
		return (0);
	}
	return (1);
}

void	clear_dir_img(t_map *map)
{
	int	x;
	int	y;
	int	w;
	int	h;

	w = WINDOW_WIDTH;
	h = WINDOW_HEIGHT;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
			mlx_put_pixel(map->dir_img, x++, y, get_color(0, 0, 0, 0));
		y++;
	}
}

void	draw_img(t_map *map, mlx_image_t *img, uint32_t color)
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

	cx = TILE_SIZE / 2;
	cy = TILE_SIZE / 2;
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
