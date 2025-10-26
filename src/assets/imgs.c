/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:02:45 by yael-maa          #+#    #+#             */
/*   Updated: 2025/10/24 18:03:58 by yael-maa         ###   ########.fr       */
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
	r = (map->x_size < map->y_size ? map->x_size : map->y_size) / 3;
	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while(x < map->x_size)
		{
			dx = x - cx;
			dy = y - cy;
			if ((dx * dx) + (dy * dy) <= (r * r))
				mlx_put_pixel(map->player_img, x, y, color);
			x++;
		}
		y++;
	}
}
