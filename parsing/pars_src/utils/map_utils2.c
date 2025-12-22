/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:00:00 by alel-you          #+#    #+#             */
/*   Updated: 2025/12/19 22:00:00 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

char	**dup_map(char **map, t_cred_list *list)
{
	char	**dup_map;
	int		i;
	int		largest_row;

	if (!map || !list)
		return (NULL);
	i = 0;
	largest_row = get_largest_row(list);
	dup_map = alloc(sizeof(char *) * (td_len(map) + 1));
	if (!dup_map)
		return (0);
	while (i < td_len(map))
	{
		dup_map[i] = equal_rows(map[i], largest_row);
		i++;
	}
	dup_map[i] = NULL;
	return (dup_map);
}

void	player_spwn_or(char s, t_map **cub)
{
	if (s == 'N')
		(*cub)->player.spg_or = N;
	else if (s == 'S')
		(*cub)->player.spg_or = S;
	else if (s == 'W')
		(*cub)->player.spg_or = W;
	else if (s == 'E')
		(*cub)->player.spg_or = E;
}

void	player_position(char **map, t_map **cub)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'E'
				|| map[y][x] == 'S' || map[y][x] == 'W')
			{
				player_spwn_or(map[y][x], cub);
				(*cub)->player.x = x;
				(*cub)->player.y = y;
			}
			x++;
		}
		y++;
	}
	(*cub)->map_height = y;
}

int	cub_items(char *line)
{
	int		i;
	char	*map_line;

	i = 0;
	map_line = ft_strtrim(line, " ");
	while (map_line && map_line[i])
	{
		if (map_line[i] != 'N' && map_line[i] != 'S'
			&& map_line[i] != 'W' && map_line[i] != 'E'
			&& map_line[i] != '0' && map_line[i] != '1'
			&& map_line[i] != ' ' && map_line[i] != '\n')
			return (printf("Error\nmap contains none cub items\n"), 0);
		i++;
	}
	if (!map_line)
		return (printf("Error\n"), 0);
	return (1);
}

int	one_player_on_map(char **map)
{
	int		count;
	int		x;
	int		y;

	count = 0;
	y = 0;
	while (map && map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'S'
				|| map[y][x] == 'E')
				count++;
			x++;
		}
		y++;
	}
	if (count > 1 || count < 1)
		return (ft_putstr_fd("one player should be on map!!\n", 2), 0);
	return (1);
}
