/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:00:00 by alel-you          #+#    #+#             */
/*   Updated: 2025/12/19 22:00:00 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	valid_map_arg(char *arg)
{
	char	*s;

	s = ft_strnstr(arg, ".cub", ft_strlen(arg));
	if (s == NULL)
	{
		ft_putstr_fd("INVALID MAP FILE !\n", 2);
		return (0);
	}
	else if (ft_strlen(s) == 4 && ft_strncmp(s, ".cub", 4) == 0)
		return (1);
	ft_putstr_fd("INVALID MAP FILE !\n", 2);
	return (0);
}

int	parse_arguments(t_map **cb_st, char **av)
{
	int	fd;

	if (!valid_map_arg(av[1]))
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror(""), 0);
	(*cb_st)->arr = NULL;
	(*cb_st)->map_height = 0;
	(*cb_st)->map_width = 0;
	(*cb_st)->no_texture = NULL;
	(*cb_st)->so_texture = NULL;
	(*cb_st)->we_texture = NULL;
	(*cb_st)->ea_texture = NULL;
	if (!extract_credantials(cb_st, fd))
		return (0);
	if (!validate_all_textures(*cb_st))
		return (0);
	return (1);
}
