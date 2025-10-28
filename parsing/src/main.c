#include "../header/cub.h"

t_cub	*get_st_cb(t_cub *cub)
{
	static t_cub	*cb;

	if (cub)
		cb = cub;
	return (cb);
}

int main(int ac, char **av)
{
	t_cub	*cb_st;

	cb_st = malloc(sizeof(t_cub));
	if (!cb_st)
		exit(EXIT_FAILURE);
	cb_st->garbage_head = NULL;
	get_st_cb(cb_st);
	parce_argument(cb_st, ac, av);
	printf("%s\n", cb_st->ea_texture);
	printf("%s\n", cb_st->no_texture);
	printf("%s\n", cb_st->so_texture);
	printf("%s\n", cb_st->we_texture);
	printf("%i, %i, %i\n", cb_st->floor_color[0], cb_st->floor_color[1], cb_st->floor_color[2]);
	printf("%i, %i, %i\n", cb_st->ceiling_color[0], cb_st->ceiling_color[1], cb_st->ceiling_color[2]);
	printf_array(cb_st->map);
	garbage_collector_cleanup(cb_st);
	free(cb_st);
	return (0);
}