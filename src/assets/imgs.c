/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:02:45 by yael-maa          #+#    #+#             */
/*   Updated: 2025/11/16 03:05:02 by yael-maa         ###   ########.fr       */
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
	DDA(map, cx, cx, cy, cy - 30);
	while (y < map->y_size)
	{
		x = 0;
		while(x < map->x_size)
		{
			dx = x - cx;
			dy = y - cy;
			// line_dir(map, x , y, color);
			if (((dx * dx) + (dy * dy) <= (r * r)))
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
		// printf("here : x = %f , y = %f\n", x , y);
		mlx_put_pixel(map->player_img, round(x), round(y), get_color(204, 57, 9, 255));
		x += x_inc;
		y += y_inc;
	}
}

void	draw_imgs(t_map *map)//  int fla
{
	draw_img(map, map->floor_img, get_color(87, 84, 84, 255));
	draw_img(map, map->wall_img, get_color(0, 0, 0, 255));
	// draw_img(&map, map.player_img, get_color(204, 57, 9, 255));
	draw_img(map, map->img, get_color(0, 0, 0, 0));
	// if (flag == 0)
	player_img(map, get_color(204, 57, 9, 255));
}
