#ifndef  CUB3D_H
#define  CUB3D_H

# include   "../libft/libft.h"
# include  "../get_next_line/get_next_line.h"
# include   "fcntl.h"
# include   "string.h"
# include   "stdio.h"
# include   "stdlib.h"

typedef enum s_spawning_or
{
    N,
    E,
    W,
    S,
}   t_spawning_or;

typedef struct s_player_pos
{
    int             x;
    int             y;
    t_spawning_or   spg_or; 
}   t_player_pos;

typedef struct s_garbage_node
{
    void                    *ptr;
    struct s_garbage_node   *next;
}   t_garbage_node;

typedef struct s_cub
{
   char **map;
   int  map_h;
   int  map_w;
   char *no_texture;
   char *so_texture;
   char *we_texture;
   char *ea_texture;
   int floor_color[3];
   int ceiling_color[3];
   t_player_pos plyer_pos;
   t_garbage_node *garbage_head;
}   t_cub;

void	*ft_malloc(size_t size);
t_cub	*get_st_cb(t_cub *cub);
void	garbage_add(t_cub *cub, void *ptr);
void	garbage_remove(t_cub *cub, void *ptr);
void	ft_free_gc(t_cub *cub, void *ptr);
void	garbage_collector_cleanup(t_cub *cub);
int		garbage_collector_count(t_cub *cub);
void	garbage_track_ptr(t_cub *cub, void *ptr);

int		is_wall(char *wall);
char	**get_map(int map_fd);
char	**get_txtrs_path(int map_fd);
char	**get_rgb_collors(int map_fd);
void	get_player_pos(t_cub **cb);

void	check_walls(char *wall);
void	check_wall(char *map_line);
int		cub_items(char *map_line, t_cub *cb_st, int flag);
void	one_player_on_map(char **map);
int		parse_map(char **map, t_cub **cb_st);

int		get_size_col_line(char *collor_line);
int		str_is_digit(char *str);
void	set_collors(char **collors, t_cub **cb_st);
void	set_texters(char **texters, t_cub **cb_st);
void	valid_map_file(t_cub **cb_st, char *map_file);

int		map_len(char **td);
char	**dup_map(t_cub *cb_st, char **map);
void	printf_array(char **arr);

void	valid_map_arg(char *arg);
void	parce_argument(t_cub *cb_st, int ac, char **av);

#endif