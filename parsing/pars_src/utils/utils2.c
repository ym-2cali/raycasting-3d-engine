/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:00:00 by alel-you          #+#    #+#             */
/*   Updated: 2025/12/19 22:00:00 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static int	color_error(const char *msg)
{
	ft_putstr_fd((char *)msg, 2);
	return (0);
}

static int	component_is_numeric(char *value)
{
	int	i;

	if (!value || !value[0])
		return (color_error("Error\nempty color value\n"));
	i = 0;
	while (value[i] && value[i] != '\n')
	{
		if (!ft_isdigit(value[i]))
			return (color_error("Error\ncolor values must be digits only\n"));
		i++;
	}
	if (value[i] == '\n' && value[i + 1])
		return (color_error("Error\ninvalid color value\n"));
	return (1);
}

static int	validate_component_triplet(char **colors)
{
	int	len;
	int	i;

	if (!colors)
		return (0);
	len = td_len(colors);
	if (len != 3)
		return (color_error("Error\ncolor requires exactly 3 values\n"));
	i = 0;
	while (i < 3)
	{
		if (!component_is_numeric(colors[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	assign_color_triplet(int *dst, char **src)
{
	int	value;
	int	i;

	i = 0;
	while (i < 3)
	{
		value = ft_atoi(src[i]);
		if (value < 0 || value > 255)
			return (color_error("Error\ncolor value must be in [0,255]\n"));
		dst[i] = value;
		i++;
	}
	return (1);
}

int	asign_colors(t_cred_list *list, t_map **cb_st)
{
	char	**values[2];
	char	*raw[2];
	char	*start[2];
	int		index;

	raw[0] = get_wanted_line(list, "C");
	raw[1] = get_wanted_line(list, "F");
	if (!raw[0] || !raw[1])
		return (0);
	if (!a_valid_argb(raw[0]) || !a_valid_argb(raw[1]))
		return (printf("error\n"), 0);
	index = -1;
	while (++index < 2)
	{
		start[index] = raw[index] + 2;
		while (*start[index]
			&& (*start[index] == ' ' || *start[index] == '\t'))
			start[index]++;
		values[index] = ft_split(start[index], ',');
		if (!values[index]
			|| !validate_component_triplet(values[index]))
			return (0);
	}
	return (assign_color_triplet((*cb_st)->ceiling_color, values[0])
		&& assign_color_triplet((*cb_st)->floor_color, values[1]));
}
