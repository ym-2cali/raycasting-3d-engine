/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:03:21 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/17 02:11:49 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_height(char **arr)
{
	int height;

	height = -1;
	while (arr[++height])
		;
	return (height);
}

uint32_t	get_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_window(t_map *map)
{
	printf("map width: %d, map height: %d\n", map->map_width, map->map_height);
	map->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "hello", 0);
	if (!map->mlx)
		return (1);
	// map->win = mlx_new_window(map->mlx, 1920, 1080, "hello");
	return (0);
}

void	key_events(void* param)
{
	t_map *map = (t_map *)param;

	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(map->mlx);
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
    double a = *angle;

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
    if (a < M_PI_2 || a > 3 * M_PI_2)
        return (RIGHT);
    else
        return (LEFT);
}

int	main(int ac, char **av)
{
	t_map *map;

// pars ----------------------------------
	printf("here 1\n");
	map = NULL;
	printf("here 2\n");
	// ft_bzero(map, sizeof(t_map));
	printf("here 3\n");
	if (ac <= 1)
		return (printf("invalid arguments !!!\n"), 1);
	map = malloc(sizeof(t_map));
	if (!map)
		return (perror(""), 1);
	if (!parse_arguments(&map, av))
		return (1);
//	rc ---------------------------------
	if (get_window(map))
		return (write(2, "graphics connection Failed\n", 27), 1);
	double	x = 0;
	double	y = 0;
	map->rad = TILE_SIZE / 4;
	player_pos(map);
	map->no_texture = "textures/download.png";
	// Load textures
	map->north_texture = mlx_load_png(map->no_texture);
	map->south_texture = mlx_load_png(map->no_texture);
	map->west_texture = mlx_load_png(map->no_texture);
	map->east_texture = mlx_load_png(map->no_texture);
	if (!map->north_texture || !map->south_texture || 
		!map->west_texture || !map->east_texture)
	{
		printf("Error loading textures\n");
		return (1);
	}
	if (!get_img(map))
		return (1);
	draw_imgs(map);
	// map_rendering(&map, 0, 0);
	mlx_image_to_window(map->mlx, map->dir_img, 0, 0);
	mlx_loop_hook(map->mlx, &key_events, map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
}
