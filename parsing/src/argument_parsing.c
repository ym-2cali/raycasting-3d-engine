#include "../header/cub.h"

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
