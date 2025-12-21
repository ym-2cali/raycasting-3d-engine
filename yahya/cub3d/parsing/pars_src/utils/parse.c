/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:58:22 by alel-you          #+#    #+#             */
/*   Updated: 2025/12/13 14:22:35 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
		return (1);
	return (0);
}
