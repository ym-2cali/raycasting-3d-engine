/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 03:50:34 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/18 23:25:40 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// double	dda(t_map *map, double x0, double x1, double y0, double y1)
// {
// 	double	dx;
// 	double	dy;
// 	double	x_inc;
// 	double	y_inc;
// 	double	steps;
// 	double	x;
// 	double	y;
// 	int		i;

// 	dx = x1 - x0;
// 	dy = y1 - y0;
// 	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
// 	x_inc = dx / steps;
// 	y_inc = dy / steps;
// 	x = x0;
// 	y = y0;
// 	i = -1;
// 	while ((++i) < steps)
// 	{
// 		mlx_put_pixel(map->dir_img, round(x), round(y), get_color(204, 57, 9, 255));
// 		x += x_inc;
// 		y += y_inc;
// 	}
// 	return (sqrt(pow(fabs(x1 - x0), 2) + pow(fabs(y1 - y0), 2)));
// }
