/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:01:06 by alel-you          #+#    #+#             */
/*   Updated: 2025/12/13 12:16:04 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	if (line[0] == '\0' || empty_line(line))
		return (0);
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& line[i] != '\n'
			&& line[i] != 'W' && line[i] != 'S'
			&& line[i] != 'N' && line[i] != 'E')
			return (0);
		i++;
	}
	return (1);
}

int	map_size(t_cred_list *list)
{
	t_cred_list	*tmp;
	int			counter;

	counter = 0;
	tmp = list;
	while (tmp && !is_map_line(tmp->content))
		tmp = tmp->next;
	while (tmp && is_map_line(tmp->content))
	{
		counter++;
		tmp = tmp->next;
	}
	return (counter);
}

int	get_largest_row(t_cred_list *list)
{
	t_cred_list	*tmp;
	int			largest;
	int			len;

	if (!list)
		return (0);
	largest = 0;
	len = 0;
	tmp = list;
	while (tmp && !is_map_line(tmp->content))
		tmp = tmp->next;
	while (tmp && is_map_line(tmp->content))
	{
		len = ft_strlen(tmp->content);
		if (tmp->next && len > largest)
			largest = len;
		tmp = tmp->next;
	}
	return (largest);
}

static int	fill_map_array(char **map, t_cred_list *list)
{
	t_cred_list	*tmp;
	int			index;

	index = 0;
	tmp = list;
	while (tmp && !is_map_line(tmp->content))
		tmp = tmp->next;
	while (tmp && is_map_line(tmp->content))
	{
		map[index] = ft_strdup(tmp->content);
		if (!map[index])
			return (0);
		index++;
		tmp = tmp->next;
	}
	return (1);
}

int	get_map(t_cred_list *list, t_map **cub)
{
	char	**map;

	map = alloc(sizeof(char *) * (map_size(list) + 1));
	if (!map)
		return (0);
	map[map_size(list)] = NULL;
	if (!fill_map_array(map, list))
		return (0);
	(*cub)->map_width = get_largest_row(list);
	if (!parse_map(map, cub, list))
		return (0);
	(*cub)->arr = dup_map(map, list);
	if (!(*cub)->arr)
		return (0);
	return (1);
}
