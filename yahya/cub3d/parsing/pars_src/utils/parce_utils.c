/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:58:14 by alel-you          #+#    #+#             */
/*   Updated: 2025/12/13 13:57:03 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static int	process_line_content(t_cred_list **list, char *line, int *f)
{
	char	*content;

	if (!is_map_line(line))
	{
		content = ft_strtrim(line, " ");
		if (!content)
			return (0);
		if (!add_content(list, content))
			return (0);
	}
	else
	{
		*f = 1;
		if (!add_content(list, line))
			return (0);
	}
	return (1);
}

t_cred_list	*grap_credantials(int fd)
{
	t_cred_list	*list;
	char		*line;
	int			f;

	f = 0;
	line = get_next_line(fd);
	list = malloc(sizeof(t_cred_list));
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

void	print_list(t_cred_list *list)
{
	t_cred_list	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("%s", tmp->content);
		tmp = tmp->next;
	}
}

int	parse_map(char **map, t_map **cb_st, t_cred_list *list)
{
	int		y;

	(void)list;
	y = 0;
	if (!map || !map[0])
		return (printf("Error\n missing map\n"), 0);
	if (!closed_map(map))
		return (0);
	while (map[y] != NULL)
	{
		if (empty_line(map[y]))
			return (printf("remove emty lines from map\n"), 0);
		if (!cub_items(map[y]))
			return (printf("map has unknow item\n"), 0);
		y++;
	}
	if (!one_player_on_map(map))
		return (printf("Error\n"), 0);
	player_position(map, cb_st);
	return (1);
}

int	extract_credantials(t_map **cb_st, int fd)
{
	t_cred_list	*list;

	list = grap_credantials(fd);
	if (!list)
		return (0);
	if (!missing_or_dup(list) || !check_content_order(list))
		return (0);
	else if (!asign_texters(list, cb_st))
		return (0);
	else if (!asign_colors(list, cb_st))
		return (0);
	else if (!get_map(list, cb_st))
		return (0);
	return (1);
}
