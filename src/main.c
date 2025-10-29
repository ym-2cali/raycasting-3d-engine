/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:03:21 by yael-maa          #+#    #+#             */
/*   Updated: 2025/10/29 17:25:29 by yael-maa         ###   ########.fr       */
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
	map->mlx = mlx_init(1366, 768, "hello", 0);
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
	// else if (keydata.key == 65)
	// {
		// if ();
		
	// }
	printf("%d\n", keydata.key);
}

int	map_len(t_map *map)
{
	int	len;
	int	i;

	len = 0;
	i = -1;
	while (map->arr[++i])
	{
		if (ft_strlen(map->arr[i]))
			len = ft_strlen(map->arr[i]);
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
	map.y_size = 768 / get_height(map.arr);// mac screen 1920x1080;
	map.x_size = 1366 / map_len(&map);
	player_pos(&map);
	get_img(&map);
	draw_imgs(&map);
	map_rendering(&map, 0, 0);
	mlx_key_hook(map.mlx, &key_events, &map);
	mlx_loop(map.mlx);
	mlx_terminate(map.mlx);
	return (0);
}