/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:05:48 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/23 22:08:19 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

int	ft_strlens(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	player_pos_helper(t_map *map, int i, int j)
{
	map->player.x = j * TILE_SIZE + TILE_SIZE / 2;
	map->player.y = i * TILE_SIZE + TILE_SIZE / 2;
}

void	player_pos_helper1(t_map *map, int i, int j)
{
	if (map->arr[i][j] == 'N')
	{
		map->player.spg_or = N;
		map->player.rotation_angle = 3 * M_PI / 2;
		player_pos_helper(map, i, j);
	}
	else if (map->arr[i][j] == 'E')
	{
		map->player.spg_or = E;
		map->player.rotation_angle = 0;
		player_pos_helper(map, i, j);
	}
	else if (map->arr[i][j] == 'W')
	{
		map->player.spg_or = W;
		map->player.rotation_angle = M_PI;
		player_pos_helper(map, i, j);
	}
	else if (map->arr[i][j] == 'S')
	{
		map->player.spg_or = S;
		map->player.rotation_angle = M_PI / 2;
		player_pos_helper(map, i, j);
	}
}

void	player_pos(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->arr[++i])
	{
		j = 0;
		while (map->arr[i][j])
		{
			player_pos_helper1(map, i, j);
			j++;
		}
	}
}
