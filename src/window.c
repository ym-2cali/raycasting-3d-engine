/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:09:09 by yael-maa          #+#    #+#             */
/*   Updated: 2025/11/18 11:05:56 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	map_rendering(t_map *map, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (map->arr[++i])
	{
		j = 0;
		while (map->arr[i][j])
		{
			if (map->arr[i][j] == '1')
				mlx_image_to_window(map->mlx, map->wall_img, x, y);
			else if (map->arr[i][j] == '0' || map->arr[i][j] == 'N' || map->arr[i][j] == 'S'
				|| map->arr[i][j] == 'E' || map->arr[i][j] == 'W')
				mlx_image_to_window(map->mlx, map->floor_img, x, y);
			else
				mlx_image_to_window(map->mlx, map->img, x, y);
			x += map->x_size;
			j++;
		}
		x = 0;
		y += map->y_size;
	}
	// mlx_image_to_window(map->mlx, map->dir_img, map->player.x, map->player.y);
	mlx_image_to_window(map->mlx, map->player_img, map->player.x, map->player.y);
}