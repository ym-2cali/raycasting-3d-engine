/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 02:30:00 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/23 02:30:00 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_height(char **arr)
{
	int	height;

	height = -1;
	while (arr[++height])
		;
	return (height);
}

uint32_t	get_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	map_len(t_map *map)
{
	int	len;
	int	i;
	int	row_len;

	len = 0;
	i = 0;
	while (map->arr[i])
	{
		row_len = ft_strlens(map->arr[i]);
		if (row_len > len)
			len = row_len;
		i++;
	}
	return (len);
}

t_player_facing	player_facing(double *angle, int flag)
{
	double	a;

	a = *angle;
	while (a < 0)
		a += 2 * M_PI;
	while (a >= 2 * M_PI)
		a -= 2 * M_PI;
	if (flag == 1)
	{
		if (a > 0 && a < M_PI)
			return (DOWN);
		else
			return (UP);
	}
	if (a < M_PI / 2 || a > 3 * M_PI / 2)
		return (RIGHT);
	else
		return (LEFT);
}

int	init_game(t_map *map)
{
	if (get_window(map))
	{
		write(2, "graphics connection Failed\n", 27);
		return (0);
	}
	map->rad = TILE_SIZE / 4;
	if (!load_all_textures(map))
		return (0);
	player_pos(map);
	if (!get_img(map))
		return (0);
	mlx_image_to_window(map->mlx, map->dir_img, 0, 0);
	mlx_loop_hook(map->mlx, &key_events, map);
	return (1);
}
