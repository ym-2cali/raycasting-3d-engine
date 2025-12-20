/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:19:55 by alel-you          #+#    #+#             */
/*   Updated: 2025/12/13 13:34:43 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	td_len(char **td)
{
	int	i;

	i = 0;
	while (td && td[i])
		i++;
	return (i);
}

static void	copy_char(char *dup, char *line_map, int *x, int *i)
{
	if (line_map[*i] != '\n' && line_map[*i] != ' ')
	{
		dup[(*x)++] = line_map[(*i)++];
		return ;
	}
	else if (line_map[*i] == ' ')
	{
		dup[(*x)++] = '.';
		(*i)++;
		return ;
	}
	(*i)++;
}

char	*equal_rows(char *line_map, int len)
{
	char	*dup;
	int		i;
	int		x;

	x = 0;
	i = 0;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (i < len && line_map[i])
		copy_char(dup, line_map, &x, &i);
	while (x < len - 1)
		dup[x++] = '.';
	dup[len - 1] = '\n';
	dup[len] = '\0';
	return (dup);
}

int	valid_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	if (line[0] && line[0] != '1')
		return (printf("Error\nmap must be close by walls\n"), 0);
	while (line[i])
	{
		if ((line[i + 1] && line[i] == '0' && line[i + 1] == ' '))
			return (printf("Error\nMap persed '-'\n"), 0);
		else if (line[i + 1] && line[i] == ' ' && line[i + 1] != ' '
			&& line[i + 1] != '1')
			return (printf("Error\nMap persed '-'\n"), 0);
		else if (!line[i + 1] && line[i] == '\n' && line[i - 1] != '1')
			return (printf("Error\nmap is not closed\n"), 0);
		i++;
	}
	return (1);
}
