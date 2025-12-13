/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:29:28 by alel-you          #+#    #+#             */
/*   Updated: 2025/10/16 16:50:05 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words_count(char *s, char c)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && s[i] && s[i + 1] == c)
			count++;
		else if (s[i] != c && s[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}

static int	ft_lenght(char *s, char c)
{
	int	i;
	int	len;

	if (!s)
		return (0);
	i = 0;
	len = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		if (s[i] != c)
			len++;
		i++;
	}
	return (len);
}

char	**ft_split(char *s, char c)
{
	t_var	p;

	p.i = 0;
	p.len = 0;
	p.n = 0;
	p.words = ft_words_count(s, c);
	p.sp = malloc(sizeof(char *) * (p.words + 1));
	while (p.i < p.words)
	{
		p.x = 0;
		p.len = ft_lenght(s + p.n, c);
		p.sp[p.i] = malloc(p.len + 1);
		while (s[p.n] && s[p.n] == c)
			p.n++;
		while (s[p.n] && s[p.n] != c)
			p.sp[p.i][p.x++] = s[p.n++];
		p.sp[p.i][p.x] = '\0';
		p.i++;
	}
	p.sp[p.i] = (NULL);
	return (p.sp);
}
