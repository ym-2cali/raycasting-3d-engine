/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_line_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alel-you          #+#    #+#             */
/*   Updated: 2025/12/23 00:00:00 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static int	ensure_value(char *line, size_t prefix_len)
{
	if (!line[prefix_len]
		|| (line[prefix_len] != ' ' && line[prefix_len] != '\t'))
		return (ft_putstr_fd("Error\ninvalid identifier format\n", 2), 0);
	while (line[prefix_len]
		&& (line[prefix_len] == ' ' || line[prefix_len] == '\t'))
		prefix_len++;
	if (!line[prefix_len])
		return (ft_putstr_fd("Error\nmissing value after identifier\n", 2), 0);
	return (1);
}

static int	validate_identifier(char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (ensure_value(line, 2));
	if (!ft_strncmp(line, "SO", 2))
		return (ensure_value(line, 2));
	if (!ft_strncmp(line, "WE", 2))
		return (ensure_value(line, 2));
	if (!ft_strncmp(line, "EA", 2))
		return (ensure_value(line, 2));
	if (!ft_strncmp(line, "F", 1))
		return (ensure_value(line, 1));
	if (!ft_strncmp(line, "C", 1))
		return (ensure_value(line, 1));
	return (ft_putstr_fd("Error\ninvalid identifier detected\n", 2), 0);
}

static int	store_config_line(t_cred_list **list, char *line)
{
	char	*content;

	content = ft_strtrim(line, " \t\r\v\f\n");
	if (!content)
		return (0);
	if (!content[0])
		return (1);
	if (content[0] == '/' && content[1] == '/')
		return (1);
	if (!validate_identifier(content))
		return (0);
	if (!add_content(list, content))
		return (0);
	return (1);
}

static int	process_line_content(t_cred_list **list, char *line, int *stage)
{
	if (is_map_line(line))
	{
		if (*stage == 2)
		{
			ft_putstr_fd("Error\nmultiple map sections detected\n", 2);
			return (0);
		}
		*stage = 1;
		if (!add_content(list, line))
			return (0);
		return (1);
	}
	if (*stage == 1)
		*stage = 2;
	return (store_config_line(list, line));
}

t_cred_list	*grap_credantials(int fd)
{
	t_cred_list	*list;
	char		*line;
	int			f;

	f = 0;
	line = get_next_line(fd);
	list = alloc(sizeof(t_cred_list));
	if (!list || !line)
		return (NULL);
	list = NULL;
	while (line)
	{
		if (!f && !ft_strcmp(line, "\n"))
		{
			line = get_next_line(fd);
			continue ;
		}
		if (!process_line_content(&list, line, &f))
			return (NULL);
		line = get_next_line(fd);
	}
	return (list);
}
