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

static int	set_floor_ceiling_values(t_map **cb_st, char **f, char **c)
{
	(*cb_st)->floor_color[0] = ft_atoi(f[0]);
	(*cb_st)->floor_color[1] = ft_atoi(f[1]);
	(*cb_st)->floor_color[2] = ft_atoi(f[2]);
	(*cb_st)->ceiling_color[0] = ft_atoi(c[0]);
	(*cb_st)->ceiling_color[1] = ft_atoi(c[1]);
	(*cb_st)->ceiling_color[2] = ft_atoi(c[2]);
	if ((*cb_st)->floor_color[0] < 0 || (*cb_st)->ceiling_color[1] < 0
		|| (*cb_st)->floor_color[1] < 0 || (*cb_st)->ceiling_color[0] < 0
		|| (*cb_st)->floor_color[2] < 0 || (*cb_st)->ceiling_color[2] < 0)
		return (0);
	return (1);
}

int	asign_colors(t_cred_list *list, t_map **cb_st)
{
	char	**c;
	char	**f;
	char	*tmp;
	char	*tmp1;

	tmp1 = get_wanted_line(list, "C");
	tmp = get_wanted_line(list, "F");
	if (!tmp1 || !tmp)
		return (0);
	if (!a_valid_argb(tmp1) || !a_valid_argb(tmp))
		return (printf("error\n"), 0);
	c = ft_split(tmp1 + 2, ',');
	f = ft_split(tmp + 2, ',');
	if (!c || !f)
		return (0);
	if (td_len(f) < 3 || td_len(c) < 3)
		return (printf("Error\nmissing a colors\n"), 0);
	return (set_floor_ceiling_values(cb_st, f, c));
}
