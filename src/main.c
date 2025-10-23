/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:03:21 by yael-maa          #+#    #+#             */
/*   Updated: 2025/09/28 20:24:34 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*c;
	size_t			i;

	c = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		c[i] = 0;
		i++;
	}
}

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

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[++i])
		;
	return (i);
}
int	get_window(t_map *map)
{
	map->mlx = mlx_init(1920, 1080, "hello", 0);
	if (!map->mlx)
		return (1);
	// map->win = mlx_new_window(map->mlx, 1920, 1080, "hello");
	return (0);
}

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
	if (get_window(&map))
		return (write(2, "graphics connection Failed\n", 27), 1);
	int	i = -1;
	float	x = 0;
	float	y = 0;
	map.y_size = 1080 / get_height(mapp);
	map.x_size = 1920 / ft_strlen(mapp[0]);
	get_img(&map);
	draw_img(&map, map.floor_img, get_color(87, 84, 84, 255));
	draw_img(&map, map.wall_img, get_color(0, 0, 0, 255));
	// draw_img(&map, map.player_img, get_color(204, 57, 9, 255));
	player_img(&map, get_color(204, 57, 9, 255));
	draw_img(&map, map.img, get_color(0, 0, 0, 0));

	while (mapp[++i])
	{
		map.x_size = 1920 / ft_strlen(mapp[i]);
		if (map.x_size <= 0 || map.y_size <= 0)
    		return (2);
		int j = 0;
		while (mapp[i][j])
		{
			if (mapp[i][j] == '0')
				mlx_image_to_window(map.mlx, map.floor_img, x, y);
			else if (mapp[i][j] == '1')
				mlx_image_to_window(map.mlx, map.wall_img, x, y);
			else if (mapp[i][j] == 'N')
			{
				mlx_image_to_window(map.mlx, map.floor_img, x, y);
				mlx_image_to_window(map.mlx, map.player_img, x, y);
			}
			else
				mlx_image_to_window(map.mlx, map.img, x, y);
			x += map.x_size;
			j++;
		}
		x = 0;
		y += map.y_size;
	}
	mlx_loop(map.mlx);
	mlx_terminate(map.mlx);
	return (0);
}