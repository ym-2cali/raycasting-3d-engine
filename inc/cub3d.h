/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:11:58 by yael-maa          #+#    #+#             */
/*   Updated: 2025/11/16 02:32:38 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include "/home/yael-maa/cub3d/MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>

// # define ROTAT_ANGLE (M_PI / 2)
# define MOVE_SPEED 3.0
# define ROTAT_SPEED (3 * (M_PI / 180))
# define FOV 60
// # define TILE_SIZE (2 * (M_PI / 180))

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
	int				turn_direction;
	int				walk_direction;
	double			rotation_angle;
    t_spawning_or   spg_or; 
}   t_player_pos;

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
	int				map_height;
	int				map_width;
	int				x_size;
	int				y_size;
} t_map ;

void		player_img(t_map *map, uint32_t color);
void		draw_img(t_map *map, mlx_image_t* img, uint32_t color);
void		get_img(t_map *map);
void		ft_bzero(void *s, size_t n);
int			ft_strlen(char *s);
void		player_pos(t_map *map);
uint32_t	get_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
void		put_line(t_map *map, int x, int y);
void		line_dir(t_map *map, int x, int y, uint32_t color);
void		map_rendering(t_map *map, int x, int y);
void		draw_imgs(t_map *map);
void 		update_player(t_map *map);
void		DDA(t_map *map, double x0, double x1, double y0, double y1);

#endif