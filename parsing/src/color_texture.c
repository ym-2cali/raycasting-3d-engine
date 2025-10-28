#include "../header/cub.h"

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
