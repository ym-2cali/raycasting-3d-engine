/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_merge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:32:51 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/13 12:03:31 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

int	main(int ac, char **av)
{
	t_map *map;

	// pars ----------------------------------
	map = NULL;
	ft_bzero(map, sizeof(t_map));
	if (ac <= 1)
		return (printf("invalid arguments !!!\n"), 1);
	map = malloc(sizeof(t_cub));
	if (!map)
		return (perror(""), 1);
	if (!parse_arguments(&map, av))
		return (1);
//	rc
	if (get_window(&map))
		return (write(2, "graphics connection Failed\n", 27), 1);
		double	x = 0;
	double	y = 0;
	map.y_size = TILE_SIZE;
	map.x_size = TILE_SIZE;
	map.rad = (map.x_size < map.y_size ? map.x_size : map.y_size) / 4;
	player_pos(&map);
	get_img(&map);
	draw_imgs(&map);
	// map_rendering(&map, 0, 0);
	mlx_image_to_window(map.mlx, map.dir_img, 0, 0);
	mlx_loop_hook(map.mlx, &key_events, &map);
	mlx_loop(map.mlx);
	mlx_terminate(map.mlx);
}