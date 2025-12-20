/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:16:35 by alel-you          #+#    #+#             */
/*   Updated: 2025/12/13 14:28:47 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

char	*get_wanted_line(t_cred_list *list, char *wanted)
{
	t_cred_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, wanted, ft_strlen(wanted)))
			return (ft_strdup(tmp->content));
		tmp = tmp->next;
	}
	return (NULL);
}

int	a_valid_argb(char *str)
{
	int	comma_counter;
	int	i;

	i = 0;
	comma_counter = 0;
	while (str && str[i])
	{
		if (str[i] == ',')
			comma_counter++;
		i++;
	}
	if (comma_counter > 2)
		return (ft_putstr_fd ("Error\ninvalid color format '-,-' !\n", 2), 0);
	if (comma_counter < 2)
		return (ft_putstr_fd ("Error\nmissing a color!\n", 2), 0);
	return (1);
}

int	add_content(t_cred_list **list, char *content)
{
	t_cred_list	*node;
	t_cred_list	*tmp;

	tmp = NULL;
	node = malloc(sizeof(t_cred_list));
	if (!node || !list || !content)
		return (0);
	node->content = content;
	node->next = NULL;
	if (!*list)
	{
		*list = node;
		return (1);
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (1);
}
