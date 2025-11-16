/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:03:21 by yael-maa          #+#    #+#             */
/*   Updated: 2025/11/16 03:03:39 by yael-maa         ###   ########.fr       */
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
	map->mlx = mlx_init(1920, 1080, "hello", 0);//wsl screen (1366, 768)
	if (!map->mlx)
		return (1);
	// map->win = mlx_new_window(map->mlx, 1920, 1080, "hello");
	return (0);
}

void	key_events(mlx_key_data_t keydata, void* param)
{
	t_map *map = (t_map *)param;

	if (keydata.key == 256)
	{
		mlx_terminate(map->mlx);
		exit (0);
	}
	else if (keydata.key == 65)
	{
		map->player.turn_direction = -1;
		update_player(map);
	}
	else if (keydata.key == 83)
	{
		map->player.walk_direction = 1;
		update_player(map);
	}
	else if (keydata.key == 87)
	{
		map->player.walk_direction = -1;
		update_player(map);
	}
	else if (keydata.key == 68)
	{
		map->player.turn_direction = 1;
		update_player(map);
	}
	else if (keydata.key == 262)
	{
		map->player.turn_direction = 1;
		update_player(map);
	}
	// printf("%d\n", keyddata.key);
}

// void key_events(mlx_key_data_t keydata, void *param)
// {
//     t_map *map = (t_map *)param;

//     if (keydata.key == 256 && keydata.action == 1) // ESC
//         mlx_terminate(map->mlx);

//     // Press
//     if (keydata.action == 1)
//     {
//         if (keydata.key == 87) map->player.walk_direction = 1;   // W
//         if (keydata.key == 83) map->player.walk_direction = -1;  // S
//         if (keydata.key == 65) map->player.turn_direction = -1;  // A
//         if (keydata.key == 68) map->player.turn_direction = 1;   // D
//     }
//     // Release
//     else if (keydata.action == 0)
//     {
//         if (keydata.key == 87 || keydata.key == 83) map->player.walk_direction = 0;
//         if (keydata.key == 65 || keydata.key == 68) map->player.turn_direction = 0;
//     }
// }

int	map_len(t_map *map)
{
	int	len;
	int	i;
	int	row_len;

	len = 0;
	i = 0;
	while (map->arr[i])
	{
		row_len = ft_strlen(map->arr[i]);
		if (row_len > len)
			len = row_len;
		i++;
	}
	return (len);
}

int	main(int ac, char **av)
{
	t_map map;
	char *mapp[] = {
	    "1111111111111111111111111",
	    "1000000000110000000000001",
	    "1011000001110000000000001",
	    "1001000000000000000000001",
	    "111111111011000001110000011111111",
	    "100000000011000001110111111111111",
	    "11110111111111011100000010001",
	    "11110111111111011101010010001",
	    "11000000110101011100000010001",
	    "10000000000000001100000010001",
	    "10000000000000001101010010001",
	    "11000001110101011111011110N0111",
	    "11110111 1110101 101111010001",
	    "11111111 1111111 111111111111",
	    NULL
	};
	(void)ac;
	(void)av;
	ft_bzero(&map, sizeof(t_map));
	map.arr = mapp;
	if (get_window(&map))
		return (write(2, "graphics connection Failed\n", 27), 1);
	float	x = 0;
	float	y = 0;
	map.map_height = get_height(map.arr);
	map.map_width = map_len(&map);
	map.y_size = 1080 / get_height(map.arr);// mac screen 1920x1080;// laptop screen (1366, 768)
	map.x_size = 1920 / map_len(&map);
	player_pos(&map);
	get_img(&map);
	draw_imgs(&map);
	map_rendering(&map, 0, 0);
	// mlx_key_hook(map.mlx, &key_events, &map);
	mlx_loop(map.mlx);
	mlx_terminate(map.mlx);
	return (0);
}