/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:11:58 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/23 23:21:34 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include "../.MLX422/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include "../parsing/get_next_line/get_next_line.h"
# include "../parsing/libft/libft.h"

typedef struct s_mem
{
	void			*ptr;
	struct s_mem	*next;
}	t_mem;

# define TILE_SIZE 32 
# define WINDOW_WIDTH 1088
# define WINDOW_HEIGHT 448
# define MOVE_SPEED 1.5
# define ROTAT_SPEED 0.0261799388
# define FOV 1.0471975512

typedef struct s_cred_list
{
	char				*content;
	struct s_cred_list	*next;
}	t_cred_list;

typedef enum s_spawning_or
{
	N,
	E,
	W,
	S,
}	t_spawning_or;
typedef enum s_player_facing
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
}	t_player_facing;
typedef struct s_player_pos
{
	double			x;
	double			y;
	int				turn_direction;
	int				walk_direction;
	double			rotation_angle;
	t_spawning_or	spg_or;
}	t_player_pos;
typedef struct s_inter
{
	double	x;
	double	y;
}	t_inter;
typedef struct s_map
{
	void				*mlx;
	char				**arr;
	mlx_image_t			*img;
	mlx_image_t			*floor_img;
	mlx_image_t			*wall_img;
	mlx_image_t			*player_img;
	mlx_image_t			*dir_img;
	t_player_pos		player;
	t_inter				inter;
	int					floor_color[3];
	int					ceiling_color[3];
	int					map_height;
	int					map_width;
	int					x_size;
	int					y_size;
	double				rad;
	int					f;
	char				*no_texture;
	char				*so_texture;
	char				*we_texture;
	char				*ea_texture;
	mlx_texture_t		*north_texture;
	mlx_texture_t		*south_texture;
	mlx_texture_t		*west_texture;
	mlx_texture_t		*east_texture;
}	t_map;
typedef struct s_texture_data
{
	double	ray_angle;
	double	hor_dist;
	double	ver_dist;
	int		facing_up;
	int		facing_right;
}	t_texture_data;

typedef struct s_wall_draw
{
	mlx_texture_t	*texture;
	int				x;
	int				wall_start;
	int				wall_end;
	int				tex_x;
	double			wall_dis;
}	t_wall_draw;
typedef struct s_ray_params
{
	int		x;
	double	ray_angle;
	double	hor_dist;
	double	ver_dist;
	double	wall_dis;
}	t_ray_params;

int				get_window(t_map *map);
void			key_events(void *param);
void			player_img(t_map *map, uint32_t color);
void			draw_img(t_map *map, mlx_image_t *img, uint32_t color);
int				get_img(t_map *map);
void			clear_dir_img(t_map *map);
void			ft_bzero(void *s, size_t n);
int				ft_strlens(char *s);
void			player_pos(t_map *map);
uint32_t		get_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
void			line_dir(t_map *map, int x, int y, uint32_t color);
void			map_rendering(t_map *map, int x, int y);
void			draw_imgs(t_map *map);
void			update_player(t_map *map);
void			ray_caster(t_map *map);
int				check_wall(t_map *map, double x, double y);
void			destroy_imgs(t_map *map);
void			calculate_wall_boundaries(double wall_dis, int *wall_start,
					int *wall_end);
void			draw_ceiling(t_map *map, int x, int wall_start);
void			draw_floor(t_map *map, int x, int wall_end);
mlx_texture_t	*select_texture(t_map *map, double ray_angle, double *wall_x);
int				calculate_texture_x(mlx_texture_t *texture, double wall_x,
					t_texture_data *data);
void			draw_textured_wall(t_map *map, t_wall_draw *w);
void			select_hor_texture(t_map *map, double ray_angle,
					mlx_texture_t **texture, double *wall_x);
void			select_ver_texture(t_map *map, double ray_angle,
					mlx_texture_t **texture, double *wall_x);
void			set_var_ver(t_map *map, double *x_inter, double angle);
void			set_var_hor(t_map *map, double *y_inter,
					double angle, double *y_step);
void			set_var_hor1(double *x_step, double angle, double *y_step);
void			set_var_ver1(double *y_step, double *x_step, double angle);
double			horizontal_intersection(t_map *map,
					double angle, double *hit_x, double *hit_y);
void			angle_reset(double *angle);
void			ray_caster_helper(t_map *map, double ray_angle, int i);
double			vertical_intersection(t_map *map, double angle,
					double *hit_x, double *hit_y);
// --------------------------

t_player_facing	player_facing(double *angle, int flag);
mlx_texture_t	*load_texture_safe(const char *path, const char *name);
int				load_all_textures(t_map *map);
void			free_textures(t_map *map);

// --------------------------
t_cred_list		*grap_credantials(int fd);
int				extract_credantials(t_map **cb_st, int fd);
int				valid_map_arg(char *arg);
int				parse_arguments(t_map **cb_st, char **av);
int				missing_or_dup(t_cred_list *list);
int				check_content_order(t_cred_list *list);
int				asign_texters(t_cred_list *list, t_map **cub);
int				asign_colors(t_cred_list *list, t_map **cb_st);
int				get_map(t_cred_list *list, t_map **cub);
int				parse_map(char **map, t_map **cb_st, t_cred_list *list);
char			**dup_map(char **map, t_cred_list *list);
int				empty_line(char *line);
int				is_player(char c);
int				get_largest_row(t_cred_list *list);
void			player_position(char **map, t_map **cub);
int				td_len(char **td);
char			*get_wanted_line(t_cred_list *list, char *wanted);
int				a_valid_argb(char *str);
int				is_map_line(char *line);
int				add_content(t_cred_list **list, char *content);
int				closed_map(char **map);
int				one_player_on_map(char **map);
int				cub_items(char *line);
int				check_dup(t_cred_list *list, char *to_check);
char			*equal_rows(char *line_map, int len);
int				valid_map_arg(char *arg);
int				map_size(t_cred_list *list);
int				asign_map(t_cred_list *list, t_map **cub);
void			player_spwn_or(char s, t_map **cub);
int				validate_all_textures(t_map *map);
void			*alloc(size_t size);
void			clean_all(void);
t_mem			**get_mem(void);
void			draw_wall_with_texture(t_map *map, t_ray_params *params);

#endif