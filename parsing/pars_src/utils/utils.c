/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:11:17 by alel-you          #+#    #+#             */
/*   Updated: 2025/12/13 14:11:54 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	check_dup(t_cred_list *list, char *to_check)
{
	t_cred_list	*tmp;
	char		**p;
	int			counter;

	counter = 0;
	tmp = list;
	while (tmp)
	{
		if (empty_line(tmp->content))
		{
			tmp = tmp->next;
			continue ;
		}
		p = ft_split(tmp->content, ' ');
		if (!p || !p[0])
			return (0);
		if (!ft_strcmp(p[0], to_check))
			counter++;
		tmp = tmp->next;
	}
	return (counter);
}

int	missing_or_dup(t_cred_list *list)
{

	if (check_dup(list, "SO") > 1 || check_dup(list, "WE") > 1 ||  check_dup(list, "EA") > 1
		|| check_dup(list, "NO") > 1 || check_dup(list, "C") > 1 ||check_dup(list, "F") > 1)
		return (printf("error DUPLICATED lines in map file !\n"), 0);
	if (!check_dup(list, "SO") || !check_dup(list, "WE") || !check_dup(list, "EA")
		|| !check_dup(list, "NO") || !check_dup(list, "C") || !check_dup(list, "F"))
		return (printf("error MISSING lines in map file !\n"), 0);
	return (1);
}

int	check_content_order(t_cred_list *list)
{
	t_cred_list	*tmp;
	int			priority_flag;

	priority_flag = 0;
	tmp = list;
	while (tmp && !ft_strcmp(tmp->content, "\n"))
		tmp = tmp->next;
	if (tmp && is_map_line(tmp->content))
		return (printf("map line detected in the wrong order !\n"), 0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "NO", 2) || !ft_strncmp(tmp->content, "SO", 2)
			|| !ft_strncmp(tmp->content, "WE", 2) || !ft_strncmp(tmp->content, "EA", 2)
			|| !ft_strncmp(tmp->content, "F", 1) || !ft_strncmp(tmp->content, "C", 1))
			priority_flag++;
		 if (is_map_line(tmp->content) && priority_flag < 6)
			return (printf("map line detected in the wrong order !\n"), 0);
		tmp = tmp->next;
	}
	return (1);
}

int	asign_texters(t_cred_list *list, t_map **cub)
{
	if(!cub)
		return (0);
	(*cub)->no_texture = get_wanted_line(list, "NO");
	(*cub)->so_texture = get_wanted_line(list, "SO");
	(*cub)->we_texture = get_wanted_line(list, "WE");
	(*cub)->ea_texture = get_wanted_line(list, "EA");
	if (!(*cub)->no_texture || !(*cub)->so_texture 
		|| !(*cub)->ea_texture || !(*cub)->we_texture)
		return (printf("moshkila am3lm"), 0);
	return (1);
}

int	asign_colors(t_cred_list *list, t_map **cb_st)
{
	// int		i;
	char	**c;
	char	**f;
	char	*tmp;
	char	*tmp1;
	
	// i = 0;
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
