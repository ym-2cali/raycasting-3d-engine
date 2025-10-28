/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:11:58 by yael-maa          #+#    #+#             */
/*   Updated: 2025/10/28 16:22:42 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
// # include <string.h>
# include <errno.h>
# include "/home/yael-maa/cub3d/MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>

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
void	line_dir(t_map *map, int x, int y, uint32_t color);

#endif