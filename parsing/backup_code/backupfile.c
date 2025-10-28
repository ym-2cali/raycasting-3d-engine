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
		line = get_next_line(map_fd);
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

	texters = NULL;
	texter = ft_strdup("");
	line = get_next_line(map_fd);
	while (line)
	{
		while (line && !strcmp(line, "\n"))
			line = get_next_line(map_fd);
		if (line && (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)))
		{
			char *temp = ft_strjoin(texter, line);
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

void	check_walls(char *wall)
{
	int	i;

	i = 0;
	while (wall && wall[i])
	{
		if (wall[i] != '1' && wall[i] != ' ')
			return (ft_putstr_fd("MAP MUST BE SURROUNDED BY WALLS!\n", 2), exit(0));
		i++;
	}
}

void	check_wall(char *map_line)
{
	int len;
	int i;

	if (!map_line)
		exit(0);
	len = ft_strlen(map_line);
	if (len == 0)
		exit(0);
	i = 0;
	while (i < len && map_line[i] == ' ')
		i++;
	if (i < len && map_line[i] != '1')
		return (ft_putstr_fd("MAP MUST BE SURROUNDED BY WALLS!\n", 2), exit(EXIT_FAILURE));
	i = len - 1;
	while (i >= 0 && map_line[i] == ' ')
		i--;
	if (i >= 0 && map_line[i] != '1')
		return (ft_putstr_fd("MAP MUST BE SURROUNDED BY WALLS!\n", 2), exit(EXIT_FAILURE));
}

int	cub_items(char *map_line, t_cub *cb_st, int flag)
{
	int	i;

	i = 0;
	if (flag)
	{
		check_walls(map_line);
		return (1);
	}
	while (map_line[i])
	{
		if (map_line[i] == 'N')
			cb_st->plyer_pos.spg_or = N;
		else if (map_line[i] == 'S')
			cb_st->plyer_pos.spg_or = S;
		else if (map_line[i] == 'W')
			cb_st->plyer_pos.spg_or = W;
		else if (map_line[i] == 'E')
			cb_st->plyer_pos.spg_or = E;
		else if (map_line[i] != 'N' &&  map_line[i] != 'S' &&  map_line[i] != 'W'
			&&  map_line[i] != 'E' && map_line[i] != '0' && map_line[i] !=  '1' && map_line[i] != ' ')
			return (0);
		i++;
	}
	check_wall(map_line);
	if (!cb_st->map_w)
		cb_st->map_w = i;
	return (1);
}

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
	dup_map = ft_malloc(cb_st, sizeof(char *) * (map_len(map) + 1));
	while (i < map_len(map))
	{
		dup_map[i] = ft_strdup(map[i]);
		i++;
	}
	dup_map[i] = NULL;
	return (dup_map);
}

void	one_player_on_map(char **map)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = 0;
	while (map && map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'S'
				|| map[y][x] == 'E')
				count++;
			x++;
		}
		y++;
	}
	if (count != 1)
		return (ft_putstr_fd("one player should be on map\n", 2), exit(0));
}

int	parse_map(char **map, t_cub **cb_st)
{
	int	y;
	int max_lines;

	if (!map || !map[0])
		return (ft_putstr_fd("|| EMPTY MAP ! ||", 2), 0);
	max_lines = map_len(map);
	cub_items(map[0], *cb_st, 1);
	y = 1;
	while (y < max_lines - 1)
	{
		if (!cub_items(map[y], *cb_st, 0))
			return (ft_putstr_fd("|| INVALID ITEM ON MAP ! |", 2), 0);
		y++;
	}
	if (max_lines > 1)
		cub_items(map[max_lines - 1], *cb_st, 1);
	one_player_on_map(map);
	(*cb_st)->map_h = max_lines;
	(*cb_st)->map = dup_map(*cb_st, map);
	get_player_pos(cb_st);
	return (1);
}

int	get_size_col_line(char *collor_line)
{
	int	i;

	i = 0;
	while (collor_line[i] && !ft_isdigit(collor_line[i]))
	{
		while (collor_line[i] == ' ')
			return (ft_putstr_fd("error color must be an int\n", 2), exit(0), 0);
		while (collor_line[i] == ' ')
			i++;
		i++;
	}
	return (i);
}

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	set_collors(char **collors, t_cub **cb_st)
{
	int		i;
	char	**f;
	char	**c;
	char	*temp;

	f = NULL;
	c = NULL;
	i = 0;
	
	if (!collors || !collors[0] || !collors[1] || !collors[2] || !collors[3])
		return (ft_putstr_fd("missing color definitions\n", 2), exit(0));
	temp = ft_strtrim(collors[1], "\n");
	f = ft_split(temp, ',');
	temp = ft_strtrim(collors[3], "\n");
	c = ft_split(temp, ',');
	if (!f || !c || !f[0] || !f[1]
			|| !f[2] || !c[0] || !c[1] || !c[2])
		return (ft_putstr_fd("collor must be 255,255,255\n", 2), exit(0));
	while (f && c && f[i] && c[i])
	{
		if (!str_is_digit(f[i]) || !str_is_digit(c[i]))
			return (ft_putstr_fd("collors must be digit\n", 2), exit(0));
		i++;
	}
	(*cb_st)->floor_color[0] = ft_atoi(f[0]);
	(*cb_st)->floor_color[1] = ft_atoi(f[1]);
	(*cb_st)->floor_color[2] = ft_atoi(f[2]);
	(*cb_st)->ceiling_color[0] = ft_atoi(c[0]);
	(*cb_st)->ceiling_color[1] = ft_atoi(c[1]);
	(*cb_st)->ceiling_color[2] = ft_atoi(c[2]);
	if ((*cb_st)->floor_color[0] > 255 || (*cb_st)->ceiling_color[1] > 255
		|| (*cb_st)->floor_color[1] > 255 || (*cb_st)->ceiling_color[0] > 255
		|| (*cb_st)->floor_color[2] > 255 || (*cb_st)->ceiling_color[2] > 255)
			return (ft_putstr_fd ("value must be between 0 && 255\n", 2), exit(EXIT_FAILURE));
}

void	set_texters(char **texters, t_cub **cb_st)
{
	char *temp;
	
	if (!texters || !texters[0] || !texters[1] || !texters[2] || !texters[3] || 
		!texters[4] || !texters[5] || !texters[6] || !texters[7])
		return (ft_putstr_fd("missing texture definitions\n", 2), exit(0));
	if (ft_strncmp(texters[0], "NO", 2) != 0 || ft_strncmp(texters[2], "SO", 2) != 0
		|| ft_strncmp(texters[4], "WE", 2) != 0 || ft_strncmp(texters[6], "EA", 2) != 0)
			return (ft_putstr_fd("texters directions must be present\n", 2), exit(0));
	temp = ft_strtrim(texters[1], "\n");
	(*cb_st)->no_texture = temp;
	temp = ft_strtrim(texters[3], "\n");
	(*cb_st)->so_texture = temp;
	temp = ft_strtrim(texters[5], "\n");
	(*cb_st)->we_texture = temp;
	temp = ft_strtrim(texters[7], "\n");
	(*cb_st)->ea_texture = temp;
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

void valid_map_file(t_cub **cb_st, char *map_file)
{
    char    **map;
    char    **texters;
    char    **collors;
    int     fd;

    fd = open(map_file, O_RDONLY);
    if (fd < 0)
        return (ft_putstr_fd("invalid map !", 2), exit(EXIT_FAILURE));
    texters = get_txtrs_path(fd);
    close(fd);
    fd = open(map_file, O_RDONLY);
    collors = get_rgb_collors(fd);
    close(fd);
    if (!texters || !collors)
        return (ft_putstr_fd("no collors or missing texters path !!\n", 2), exit(EXIT_FAILURE));
    set_texters(texters, cb_st);
    set_collors(collors, cb_st);
    fd = open(map_file, O_RDONLY);
    map = get_map(fd);
    close(fd);
    if (!parse_map(map, cb_st))
        exit(EXIT_FAILURE);
}

void	valid_map_arg(char *arg)
{
	char	*s;

	s = NULL;
	s = ft_strnstr(arg, ".cub", ft_strlen(arg));
	if (s == NULL)
		return (ft_putstr_fd("INVALID MAP FILE !\n", 2), exit(0));
	if (ft_strncmp(s, ".cub", 4) == 0 && ft_strlen(s) == 4)
		return ;
	return (ft_putstr_fd("INVALID MAP FILE !\n", 2), exit(0));
}

void    parce_argument(t_cub *cb_st, int ac, char **av)
{
	if (ac <= 1)
		return (ft_putstr_fd("missing map file !", 2), exit(EXIT_FAILURE));
	cb_st->map = NULL;
	cb_st->map_h = 0;
	cb_st->map_w = 0;
	cb_st->no_texture = NULL;
	cb_st->so_texture = NULL;
	cb_st->we_texture = NULL;
	cb_st->ea_texture = NULL;
	valid_map_arg(av[1]);
	valid_map_file(&cb_st, av[1]);
}

int main(int ac, char **av)
{
	static t_cub	*cb_st;

	cb_st = ft_malloc(sizeof(t_cub));
	cb_st->garbage_head = NULL;
	parce_argument(cb_st, ac, av);
	printf("%s\n", cb_st->ea_texture);
	printf("%s\n", cb_st->no_texture);
	printf("%s\n", cb_st->so_texture);
	printf("%s\n", cb_st->we_texture);
	printf("%i, %i, %i\n", cb_st->floor_color[0], cb_st->floor_color[1], cb_st->floor_color[2]);
	printf("%i, %i, %i\n", cb_st->ceiling_color[0], cb_st->ceiling_color[1], cb_st->ceiling_color[2]);
	printf_array(cb_st->map);
	garbage_collector_cleanup(cb_st);
	return (0);
}