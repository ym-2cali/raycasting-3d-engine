/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:38:08 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/01 04:34:08 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	first_inter(t_map *map,double *angle)
{
	double	yf;
	double	xf;
	double adj;
	
	if (*angle > 0 && *angle < M_PI)
		yf = trunc(map->player.y / 32) * 32 + 32;
	else
		yf = trunc(map->player.y / 32) * 32;
		xf = map->player.x + fabs(map->player.y - yf)/ tan(*angle);
		DDA(map, map->player.x, xf, map->player.y, yf);
		map->inter.x = xf;
		map->inter.y = yf;
		return (fabs(map->player.y - yf) / sin(*angle));
	}
	void	ray_caster(t_map *map)
	{
		double	angle = map->player.rotation_angle - (30 * M_PI / 180);
		double	s_angle = map->player.rotation_angle + (30 * M_PI / 180);
		while (angle < s_angle)
		{
			first_inter(map, &angle);
			angle += (60 * M_PI / 180) / 320; 
		}
}