/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:11:58 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/13 18:24:19 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include "/home/yael-maa/cub3d/MLX422/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include "../parsing/get_next_line/get_next_line.h"
# include "../parsing/libft/libft.h"

// # define ROTAT_ANGLE (M_PI / 2)
# define TILE_SIZE 32 
# define WINDOW_WIDTH (34 * TILE_SIZE)
# define WINDOW_HEIGHT (14 * TILE_SIZE)
# define MOVE_SPEED 3.0
# define ROTAT_SPEED (3 * (M_PI / 180))
# define FOV 60 * (M_PI / 180)
// # define TILE_SIZE (2 * (M_PI / 180))

typedef struct s_cred_list
{
	char						*content;
	struct s_cred_list			*next;
}	t_cred_list;

typedef enum s_spawning_or
{
    N,
    E,
    W,
    S,
}   t_spawning_or;

typedef enum s_player_facing
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
}   t_player_facing;

typedef struct s_player_pos
{
    double          x;
    double			y;
	int				turn_direction;
	int				walk_direction;
	double			rotation_angle;
    t_spawning_or   spg_or; 
}   t_player_pos;

typedef struct s_inter
{
	double	x;
	double	y;
} t_inter;

typedef struct s_map
{
	void*			mlx;
	char			**arr;
	mlx_image_t*	img;
	mlx_image_t*	floor_img;
	mlx_image_t*	wall_img;
	mlx_image_t*	player_img;
	mlx_image_t*	dir_img;
	t_player_pos	player;
	t_inter			inter;
	int				floor_color[3];
	int				ceiling_color[3];
	int				map_height;
	int				map_width;
	int				x_size;
	int				y_size;
	double			rad;
	int				f;
	char				*no_texture;
	char				*so_texture;
	char				*we_texture;
	char				*ea_texture;
} t_map ;

void		player_img(t_map *map, uint32_t color);
void		draw_img(t_map *map, mlx_image_t* img, uint32_t color);
void		get_img(t_map *map);
void		clear_dir_img(t_map *map);
void		ft_bzero(void *s, size_t n);
int			ft_strlens(char *s);
void		player_pos(t_map *map);
uint32_t	get_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
void		line_dir(t_map *map, int x, int y, uint32_t color);
void		map_rendering(t_map *map, int x, int y);
void		draw_imgs(t_map *map);
void 		update_player(t_map *map);
double		DDA(t_map *map, double x0, double x1, double y0, double y1);
void		ray_caster(t_map *map);
int			check_wall(t_map *map, double x, double y);
t_player_facing	player_facing(double *angle, int flag);
// --------------------------
t_cred_list	*grap_credantials(int fd);
int 		extract_credantials(t_map **cb_st, int fd);
int 		valid_map_arg(char *arg);
int			parse_arguments(t_map **cb_st, char **av);
int			missing_or_dup(t_cred_list *list);
int			check_content_order(t_cred_list *list);
int			asign_texters(t_cred_list *list, t_map **cub);
int			asign_colors(t_cred_list *list, t_map **cb_st);
int			get_map(t_cred_list *list, t_map **cub);
int			parse_map(char **map, t_map **cb_st, t_cred_list *list);
char		**dup_map(char **map, t_cred_list *list);
int			empty_line(char *line);
int			is_player(char c);
int	get_largest_row(t_cred_list *list);
void	player_position(char **map, t_map **cub);
int	td_len(char **td);
char	*get_wanted_line(t_cred_list *list, char *wanted);
int	a_valid_argb(char *str);
int	is_map_line(char *line);
int	add_content(t_cred_list **list, char *content);
int closed_map(char **map);
int	one_player_on_map(char **map);
int	cub_items(char *line);
void	print_cred(t_map *cb);

#endif