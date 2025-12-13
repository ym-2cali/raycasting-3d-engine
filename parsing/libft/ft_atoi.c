/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 22:53:56 by alel-you          #+#    #+#             */
/*   Updated: 2025/10/20 23:11:43 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	parse_line(char const *str)
{
	int	i;

	i = 0;
	if (ft_strchr(str, '-'))
		return (printf("Error\nonly feeds on positive numbers\n"), 0);
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '\n')
		return (printf("Error\nmissing color\n"), 0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != '\n')
			return (printf("Error\ncolors must be digits\n"), 0);
		else if (str[i + 1] && str[i] == 32 && ft_isdigit(str[i + 1]))
			return (printf("Error\ninvalid numbers\n"), 0);
		i++;
	}
	return (1);	
}

int	ft_atoi(char const *str)
{
	int		i;
	long	tmp;

	i = 0;
	tmp = 0;
	if (!str)
		return (-1);
	else if (!parse_line(str))
		return (-1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		tmp = (tmp * 10) + (str[i] - '0');
		i++;
	}
	if (tmp > 255)
		return (ft_putstr_fd ("Error\nvalue must be between 0 && 255\n", 2), -1);
	return (tmp);
}
