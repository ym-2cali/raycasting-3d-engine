#include "../header/cub.h"

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
