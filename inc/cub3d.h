/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:11:58 by yael-maa          #+#    #+#             */
/*   Updated: 2025/09/28 20:17:39 by yael-maa         ###   ########.fr       */
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

typedef enum s_part
{
	FLOOR,
	WALL,
} t_part ;

typedef struct s_map
{
	void*			mlx;
	mlx_image_t*	img;
	mlx_image_t*	floor_img;
	mlx_image_t*	wall_img;
	mlx_image_t*	player_img;
	int			x_size;
	int			y_size;
} t_map ;

#endif