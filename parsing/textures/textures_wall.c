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

void	draw_wall_with_texture(t_map *map, t_ray_params *params)
{
	t_wall_draw			w;
	t_texture_data		data;
	double				wall_x;

	map->inter.x = params->hor_dist;
	map->inter.y = params->ver_dist;
	calculate_wall_boundaries(params->wall_dis, &w.wall_start, &w.wall_end);
	w.texture = select_texture(map, params->ray_angle, &wall_x);
	data.ray_angle = params->ray_angle;
	data.hor_dist = params->hor_dist;
	data.ver_dist = params->ver_dist;
	w.tex_x = calculate_texture_x(w.texture, wall_x, &data);
	w.x = params->x;
	w.wall_dis = params->wall_dis;
	draw_ceiling(map, params->x, w.wall_start);
	draw_textured_wall(map, &w);
	draw_floor(map, params->x, w.wall_end);
}
