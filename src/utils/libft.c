/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:05:48 by yael-maa          #+#    #+#             */
/*   Updated: 2025/10/28 15:56:16 by yael-maa         ###   ########.fr       */
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
			
			if (map->arr[i][j] == 'N')
			{
				map->player.spg_or = N;
				map->player.x = j;
				map->player.y = i; 
			}
			else if (map->arr[i][j] == 'E')
			{
				map->player.spg_or = E;
				map->player.x = j;
				map->player.y = i; 
			}
			else if (map->arr[i][j] == 'W')
			{
				map->player.spg_or = W;
				map->player.x = j;
				map->player.y = i; 
			}
			else if (map->arr[i][j] == 'S')
			{
				map->player.spg_or = S;
				map->player.x = j;
				map->player.y = i;
			}
			j++;
		}
	}
}