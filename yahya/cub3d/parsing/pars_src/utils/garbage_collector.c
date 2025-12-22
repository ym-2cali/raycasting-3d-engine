/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:00:00 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/22 21:54:47 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

t_mem	**get_mem(void)
{
	static t_mem	*head;
	return (&head);
}

void	*alloc(size_t size)
{
	void	*ptr;
	t_mem	*node;
	t_mem	**head;

	if (size == 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = malloc(sizeof(t_mem));
	if (!node)
		return (free(ptr), NULL);
	head = get_mem();
	node->ptr = ptr;
	node->next = *head;
	*head = node;
	return (ptr);
}

void	clean_one(void *ptr)
{
	t_mem	*curr;
	t_mem	*prev;
	t_mem	**head;

	if (!ptr)
		return ;
	head = get_mem();
	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (curr->ptr == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free(curr->ptr);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	clean_all(void)
{
	t_mem	*curr;
	t_mem	*next;
	t_mem	**head;

	head = get_mem();
	curr = *head;
	while (curr)
	{
		next = curr->next;
		if (curr->ptr)
			free(curr->ptr);
		free(curr);
		curr = next;
	}
	*head = NULL;
}
