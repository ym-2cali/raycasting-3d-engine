/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:20:34 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/23 00:25:58 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	calculate_wall_boundaries(double wall_dis, int *wall_start,
	int *wall_end)
{
	*wall_start = WINDOW_HEIGHT / 2 - (int)wall_dis;
	*wall_end = WINDOW_HEIGHT / 2 + (int)wall_dis;
	if (*wall_start < 0)
		*wall_start = 0;
	if (*wall_end > WINDOW_HEIGHT)
		*wall_end = WINDOW_HEIGHT;
}

void	draw_ceiling(t_map *map, int x, int wall_start)
{
	int			y;
	uint32_t	color;

	y = 0;
	color = get_color(map->ceiling_color[0], map->ceiling_color[1],
			map->ceiling_color[2], 255);
	while (y < wall_start)
	{
		mlx_put_pixel(map->dir_img, x, y, color);
		y++;
	}
}

void	draw_floor(t_map *map, int x, int wall_end)
{
	int			y;
	uint32_t	color;

	y = wall_end;
	color = get_color(map->floor_color[0], map->floor_color[1],
			map->floor_color[2], 255);
	while (y < WINDOW_HEIGHT)
	{
		mlx_put_pixel(map->dir_img, x, y, color);
		y++;
	}
}

void	select_hor_texture(t_map *map, double ray_angle,
	mlx_texture_t **texture, double *wall_x)
{
	int	facing_up;

	facing_up = (ray_angle > M_PI && ray_angle < 2 * M_PI);
	if (facing_up)
		*texture = map->north_texture;
	else
		*texture = map->south_texture;
	*wall_x = map->player.x + map->inter.x * cos(ray_angle);
}

void	select_ver_texture(t_map *map, double ray_angle,
	mlx_texture_t **texture, double *wall_x)
{
	int	facing_right;

	facing_right = (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2);
	if (facing_right)
		*texture = map->east_texture;
	else
		*texture = map->west_texture;
	*wall_x = map->player.y + map->inter.y * sin(ray_angle);
}
