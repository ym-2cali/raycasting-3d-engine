/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:38:08 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/08 01:01:31 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
// reset angle after any change
double	first_inter(t_map *map,double *angle)
{
	double	yf;
	double	xf;
	double	adj;
  
	if (*angle >= ((M_PI / 2)  - (FOV / 2))  && *angle < ((M_PI / 2)  + (FOV / 2)))
	{
		printf("here 1\n");
		yf = trunc(map->player.y / 32) * 32 + 32;
		xf = map->player.x - ((map->player.y - yf) / tan(*angle));
	}
	else if (*angle >= (3 * M_PI / 2) - (FOV / 2)  && *angle < (3 * M_PI / 2) + (FOV / 2))
	{
		printf("here 3\n");
		yf = trunc(map->player.y / 32) * 32;
		xf = map->player.x + (map->player.y - yf) / tan(*angle);
	}
	else if (cos(*angle) < 0)
	{
		// printf("py = %f\n");
		xf = floor(map->player.x / 32) * 32;
		yf = map->player.y + (map->player.x - xf) * tan(*angle);
	}
	else if (cos(*angle) > 0)   // EAST
	{
	    xf = floor(map->player.x / 32) * 32 + 32;
	    yf = map->player.y + (xf - map->player.x) * tan(*angle);
	}
	// printf("%f === %f\n",xf,yf);
	DDA(map, map->player.x, xf, map->player.y, yf);
	map->inter.x = xf;
	map->inter.y = yf;
	return (fabs(map->player.y - yf) / fabs(sin(*angle)));
}

double	hor_sample(t_map *map, double *angle)
{
	double	x_step;
	double	y_step;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(*angle);
	if (*angle > 0 && *angle < M_PI / 2)
		DDA(map, map->inter.x, map->inter.x + x_step, map->inter.y, map->inter.y + y_step);
	else if (*angle > M_PI / 2 && *angle < M_PI)
		DDA(map, map->inter.x, map->inter.x - x_step, map->inter.y, map->inter.y + y_step);
	else if (*angle > M_PI  && *angle < (3 * M_PI / 2))
		DDA(map, map->inter.x, map->inter.x - x_step, map->inter.y, map->inter.y - y_step);
	else if (*angle > (3 * M_PI / 2) && *angle < 2 * M_PI)
		DDA(map, map->inter.x, map->inter.x + x_step, map->inter.y, map->inter.y - y_step);
	// if (*angle == M_PI / 2)
	// 	DDA(map, map->inter.x, map->inter.x, map->inter.y, map->inter.y + TILE_SIZE);
	return (fabs(TILE_SIZE / sin(*angle)));
}

void	ray_caster(t_map *map)
{
	double	angle;
	double	s_angle;
	double	m_angle;

	// map->player.rotation_angle - (30 * M_PI / 180)
	angle = map->player.rotation_angle - (30 * M_PI / 180);
	s_angle = map->player.rotation_angle + (30 * M_PI / 180);
	if (s_angle >= 0 && s_angle <= FOV / 2)
	{
		while (angle < 2 * M_PI)
		{
			if (angle >= 2 * M_PI)
				angle -= (2 * M_PI);
			else if (angle < 0)
				angle += (2 * M_PI);
			first_inter(map, &angle);
			// hor_sample(map, &angle);
			// if (angle < s_angle)
			angle += (60 * M_PI / 180) / 320;
		}
		angle = 0;
		while (angle < FOV / 2)
		{
			if (angle >= 2 * M_PI)
				angle -= (2 * M_PI);
			else if (angle < 0)
				angle += (2 * M_PI);
			first_inter(map, &angle);
			// hor_sample(map, &angle);
			// if (angle < s_angle)
			angle += (60 * M_PI / 180) / 320;
		}
	}
	else
	{
		while (angle < s_angle)
		{
			if (angle >= 2 * M_PI)
			angle -= (2 * M_PI);
			else if (angle < 0)
			angle += (2 * M_PI);
			first_inter(map, &angle);
			// hor_sample(map, &angle);
			// if (angle < s_angle)
			angle += (60 * M_PI / 180) / 320;
		}
	}
}
