/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:03:21 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/23 22:00:57 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_window(t_map *map)
{
	printf("map width: %d, map height: %d\n", map->map_width, map->map_height);
	map->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "hello", 0);
	if (!map->mlx)
		return (1);
	return (0);
}

void	key_events(void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
	{
		destroy_imgs(map);
		free_textures(map);
		mlx_terminate(map->mlx);
		clean_all();
		exit (0);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		map->player.turn_direction = -1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		map->player.turn_direction = 1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
		map->player.walk_direction = 1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
		map->player.walk_direction = -1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		map->f = 1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
		map->f = 2;
	update_player(map);
}

int	main(int ac, char **av)
{
	t_map	*map;

	map = NULL;
	if (ac <= 1)
		return (printf("invalid arguments !!!\n"), 1);
	map = alloc(sizeof(t_map));
	if (!parse_arguments(&map, av))
		return (clean_all(), 1);
	if (get_window(map))
		return (write(2, "graphics connection Failed\n", 27), clean_all(), 1);
	map->rad = TILE_SIZE / 4;
	if (!load_all_textures(map))
		return (clean_all(), 1);
	player_pos(map);
	if (!get_img(map))
		return (clean_all(), 1);
	mlx_image_to_window(map->mlx, map->dir_img, 0, 0);
	mlx_loop_hook(map->mlx, &key_events, map);
	mlx_loop(map->mlx);
	destroy_imgs(map);
	free_textures(map);
	mlx_terminate(map->mlx);
	clean_all();
	return (0);
}
