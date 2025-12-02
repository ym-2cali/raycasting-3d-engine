/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:02:45 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/02 16:53:24 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	get_img(t_map *map)
{
	map->floor_img = mlx_new_image(map->mlx, map->x_size, map->y_size);
	map->wall_img = mlx_new_image(map->mlx, map->x_size, map->y_size);
	map->img = mlx_new_image(map->mlx, map->x_size, map->y_size);
	map->player_img = mlx_new_image(map->mlx, map->x_size, map->y_size);
	map->dir_img = mlx_new_image(map->mlx, map->map_width * TILE_SIZE, map->map_height * TILE_SIZE);
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

void	player_img(t_map *map, uint32_t color)
{
	double	cx;
	double	cy;
	double	y;
	double	x;
	double	dx;
	double	dy;

	cx = TILE_SIZE / 2;
	cy = TILE_SIZE / 2;
	// DDA(map, TILE_SIZE / 2, TILE_SIZE / 2 + cos(map->player.rotation_angle) * 16, TILE_SIZE / 2, TILE_SIZE / 2 + sin(map->player.rotation_angle) * 16);
	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while(x < map->x_size)
		{
			dx = x - cx;
			dy = y - cy;
			if (((dx * dx) + (dy * dy) <= (map->rad * map->rad)))
				mlx_put_pixel(map->player_img, x, y, color);
			x++;
		}
		y++;
	}
}

void	DDA(t_map *map, double x0, double x1, double y0, double y1)
{
	double	dx;
	double	dy;
	double	x_inc;
	double	y_inc;
	double	steps;
	double	x;
	double	y;
	int		i;

	dx = x1 - x0;
	dy = y1 - y0;
	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	x = x0;
	y = y0;
	i = -1;
	while ((++i) < steps)
	{
		mlx_put_pixel(map->dir_img, round(x), round(y), get_color(204, 57, 9, 255));
		x += x_inc;
		y += y_inc;
	}
}

void	draw_imgs(t_map *map)//  int fla
{
	draw_img(map, map->floor_img, get_color(87, 84, 84, 255));
	draw_img(map, map->wall_img, get_color(0, 0, 0, 255));
	draw_img(map, map->img, get_color(0, 0, 0, 0));
	player_img(map, get_color(204, 57, 9, 255));
	ray_caster(map);
}
