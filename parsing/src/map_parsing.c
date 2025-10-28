#include "../header/cub.h"

int	is_wall(char *wall)
{
	int	i;

	i = 0;
	if (!wall)
		return (0);
	while (wall[i] && wall[i] == ' ')
		i++;
	if (!wall[i] || wall[i] == '\n')
		return (0);
	while (wall[i] && wall[i] != '\n')
	{
		if (wall[i] != '1' && wall[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char    **get_map(int map_fd)
{
	char    *line;
	char    *map_line;
	char    *temp;
	char    **map;

	map_line = ft_strdup("");
	if (!map_line)
		return (NULL);
	line = get_next_line(map_fd);
	if (!line)
		return (NULL);
	while (line && !is_wall(line))
	{
		line = get_next_line(map_fd);
	}
	while (line)
	{
	   temp = ft_strjoin(map_line, line);
	   map_line = temp;
	   line = get_next_line(map_fd); 
	}
	if (!map_line || strlen(map_line) == 0)
		return (NULL);
	map = ft_split(map_line, '\n');
	if (!map)
		return (NULL);
	close(map_fd);
	return (map);
}

char	**get_txtrs_path(int map_fd)
{
	char	*line;
	char	*texter;
	char	**texters;
	char	*temp;

	texters = NULL;
	texter = ft_strdup("");
	line = get_next_line(map_fd);
	while (line)
	{
		while (line && !strcmp(line, "\n"))
			line = get_next_line(map_fd);
		if (line && (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)))
		{
			temp = ft_strjoin(texter, line);
			texter = temp;
			temp = ft_strjoin(texter, " ");
			texter = temp;
		}
		line = get_next_line(map_fd);
	}
	if (!texter)
		return (NULL);
	texters = ft_split(texter, ' ');
	if (!texters)
		return (NULL);
	return (texters);
}

char	**get_rgb_collors(int map_fd)
{
	char	*line;
	char	*color;
	char	**colors;

	colors = NULL;
	color = ft_strdup("");
	line = get_next_line(map_fd);
	while (line)
	{
		while (line && !strcmp(line, "\n"))
			line = get_next_line(map_fd);
		if (line && (!ft_strncmp(line, "C", 1) || !ft_strncmp(line, "F", 1)))
		{
			char *temp = ft_strjoin(color, line);
			color = temp;
			temp = ft_strjoin(color, " ");
			color = temp;
		}
		line = get_next_line(map_fd);
	}
	if (!color)
		return (NULL);
	colors = ft_split(color, ' ');
	if (!colors)
		return (NULL);
	return (colors);
}

void	get_player_pos(t_cub **cb)
{
	int		x;
	int		y;
	char	**map;

	if (!cb || !*cb || !(*cb)->map)
		return;
	y = 0;
	map = (*cb)->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'S'
				|| map[y][x] == 'E')
			{
				(*cb)->plyer_pos.x = x;
				(*cb)->plyer_pos.y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
