#include "../header/cub.h"

int	map_len(char **td)
{
	int	i;

	i = 0;
	while (td[i])
		i++;
	return (i);
}

char	**dup_map(t_cub *cb_st, char **map)
{
	char	**dup_map;
	int		i;

	if (!map || !map)
		return (NULL);
	i = 0;
	dup_map = ft_malloc(sizeof(char *) * (map_len(map) + 1));
	while (i < map_len(map))
	{
		dup_map[i] = ft_strdup(map[i]);
		i++;
	}
	dup_map[i] = NULL;
	return (dup_map);
}

void	printf_array(char **arr)
{
	int i = 0;
	while (arr[i++])
	{
		if (!arr[i])
		{
			puts("here");
			break ;
		}
		printf("%s\n", arr[i]);
	}
}
