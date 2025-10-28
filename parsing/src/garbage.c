#include "../header/cub.h"

void	*ft_malloc(size_t size)
{
	void			*ptr;
	t_garbage_node	*new_node;
	t_cub			*cub;

    cub = get_st_cb(NULL);
	if (!cub)
	{
		ptr = malloc(size);
		if (!ptr)
			exit(EXIT_FAILURE);
		return (ptr);
	}
	ptr = malloc(size);
	if (!ptr)
		exit(EXIT_FAILURE);
	new_node = malloc(sizeof(t_garbage_node));
	if (!new_node)
	{
		free(ptr);
		exit(EXIT_FAILURE);
	}
	new_node->ptr = ptr;
	new_node->next = cub->garbage_head;
	cub->garbage_head = new_node;
	return (ptr);
}

void	garbage_add(t_cub *cub, void *ptr)
{
	t_garbage_node	*new_node;

	if (!ptr || !cub)
		return ;
	new_node = malloc(sizeof(t_garbage_node));
	if (!new_node)
		return ;
	new_node->ptr = ptr;
	new_node->next = cub->garbage_head;
	cub->garbage_head = new_node;
}

void	garbage_remove(t_cub *cub, void *ptr)
{
	t_garbage_node	*current;
	t_garbage_node	*prev;

	if (!ptr || !cub || !cub->garbage_head)
		return ;
	current = cub->garbage_head;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				cub->garbage_head = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_free_gc(t_cub *cub, void *ptr)
{
	if (!ptr || !cub)
		return ;
	garbage_remove(cub, ptr);
	free(ptr);
}

void	garbage_collector_cleanup(t_cub *cub)
{
	t_garbage_node	*current;
	t_garbage_node	*next;

	if (!cub)
		return ;
	current = cub->garbage_head;
	while (current)
	{
		next = current->next;
		if (current->ptr)
			free(current->ptr);
		free(current);
		current = next;
	}
	cub->garbage_head = NULL;
}

int	garbage_collector_count(t_cub *cub)
{
	t_garbage_node	*current;
	int				count;

	count = 0;
	if (!cub)
		return (count);
	current = cub->garbage_head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	garbage_track_ptr(t_cub *cub, void *ptr)
{
	if (!cub || !ptr)
		return ;
	garbage_add(cub, ptr);
}