/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_merge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:32:51 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/18 22:51:54 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

int	main(int ac, char **av)
{
	t_map *map;

	// pars ----------------------------------
	if (ac <= 1)
		return (printf("invalid arguments !!!\n"), 1);
	map = malloc(sizeof(t_map));
	if (!map)
		return (perror(""), 1);
	if (!parse_arguments(&map, av))
		return (1);
//	rc
	if (get_window(map))
		return (write(2, "graphics connection Failed\n", 27), 1);
	double	x = 0;
	double	y = 0;
	map->rad = TILE_SIZE / 4;
	player_pos(map);
	get_img(map);
	// draw_imgs(map);
	// map_rendering(map, 0, 0);
	mlx_image_to_window(map->mlx, map->dir_img, 0, 0);
	mlx_loop_hook(map->mlx, &key_events, map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
}