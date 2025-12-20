/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:00:00 by alel-you          #+#    #+#             */
/*   Updated: 2025/12/19 22:00:00 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static int	check_left_right(char **map, int y, int x, int len)
{
	if (x == 0 || map[y][x - 1] == ' ')
		return (printf("Error\nmap exposed (left)\n"), 0);
	if (x == len - 1 || map[y][x + 1] == ' ')
		return (printf("Error\nmap exposed (right)\n"), 0);
	return (1);
}

static int	check_up_down(char **map, int y, int x)
{
	if (y == 0 || (size_t)x >= ft_strlen(map[y - 1])
		|| map[y - 1][x] == ' ' || map[y - 1][x] == '\n')
		return (printf("Error\nmap exposed (up)\n"), 0);
	if (y == td_len(map) - 1 || (size_t)x >= ft_strlen(map[y + 1])
		|| map[y + 1][x] == ' ' || map[y + 1][x] == '\n')
		return (printf("Error\nmap exposed (down)\n"), 0);
	return (1);
}

static int	check_cell(char **map, int y, int x, int len)
{
	if (!check_left_right(map, y, x, len))
		return (0);
	if (!check_up_down(map, y, x))
		return (0);
	return (1);
}

int	closed_map(char **map)
{
	int	y;
	int	x;
	int	len;

	if (!map)
		return (0);
	y = 0;
	while (map[y])
	{
		len = ft_strlen(map[y]);
		if (len > 0 && map[y][len - 1] == '\n')
			len--;
		x = 0;
		while (x < len)
		{
			if (map[y][x] == '0' || is_player(map[y][x]))
			{
				if (!check_cell(map, y, x, len))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
