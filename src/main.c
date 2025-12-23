/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:03:21 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/23 00:04:18 by yael-maa         ###   ########.fr       */
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
	{
		write(2, "graphics connection Failed\n", 27);
		return (clean_all(), 1);
	}
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
