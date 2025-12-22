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

static void	calculate_wall_boundaries(double wall_dis, int *wall_start, int *wall_end)
{
	*wall_start = WINDOW_HEIGHT / 2 - (int)wall_dis;
	*wall_end = WINDOW_HEIGHT / 2 + (int)wall_dis;
	
	if (*wall_start < 0)
		*wall_start = 0;
	if (*wall_end > WINDOW_HEIGHT)
		*wall_end = WINDOW_HEIGHT;
}

static void draw_ceiling(t_map *map, int x, int wall_start)
{
	int y;
	
	y = 0;
	while (y < wall_start)
	{
		mlx_put_pixel(map->dir_img, x, y++, get_color(map->ceiling_color[0], 
					 map->ceiling_color[1], map->ceiling_color[2], 255));
	}
}

static void draw_floor(t_map *map, int x, int wall_end)
{
	int y;
	
	y = wall_end;
	while (y < WINDOW_HEIGHT)
	{
		mlx_put_pixel(map->dir_img, x, y++, get_color(map->floor_color[0], 
					 map->floor_color[1], map->floor_color[2], 255));
	}
}

static mlx_texture_t*	select_texture(t_map *map, double ray_angle, 
									  double hor_dist, double ver_dist, double *wall_x)
{
	int facing_up;
	int facing_right;
	mlx_texture_t *texture;
	
	facing_up = (ray_angle > M_PI && ray_angle < 2 * M_PI);
	facing_right = (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2);
	
	if (hor_dist < ver_dist)
	{
		if (facing_up)
			texture = map->north_texture;
		else
			texture = map->south_texture;
		*wall_x = map->player.x + hor_dist * cos(ray_angle);
	}
	else
	{
		if (facing_right)
			texture = map->east_texture;
		else
			texture = map->west_texture;
		*wall_x = map->player.y + ver_dist * sin(ray_angle);
	}
	return texture;
}

static int calculate_texture_x(mlx_texture_t *texture, double wall_x, 
								double ray_angle, double hor_dist, double ver_dist)
{
	int facing_up;
	int facing_right;
	int tex_x;
	
	if (!texture)
		return (0);
	facing_up = (ray_angle > M_PI && ray_angle < 2 * M_PI);
	facing_right = (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2);
	wall_x /= TILE_SIZE;
	wall_x = wall_x - floor(wall_x);
	tex_x = (int)(wall_x * texture->width);
	if (hor_dist < ver_dist && !facing_up)
		tex_x = texture->width - tex_x - 1;
	if (hor_dist >= ver_dist && facing_right)
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)texture->width)
		tex_x = texture->width - 1;
	return tex_x;
}

static void draw_textured_wall(t_map *map, mlx_texture_t *texture, int x, 
								int wall_start, int wall_end, int tex_x, double wall_dis)
{
	int tex_y;
	int pixel_index;
	uint8_t *pixel;
	uint32_t color;
	double wall_y;
	
	if (!texture)
		return ;
	while (wall_start < wall_end)
	{
		wall_y = (double)(wall_start - (WINDOW_HEIGHT / 2 - (int)wall_dis)) 
				/ (double)(wall_dis * 2);
		tex_y = (int)(wall_y * texture->height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)texture->height)
			tex_y = texture->height - 1;
		pixel_index = (tex_y * texture->width + tex_x) * texture->bytes_per_pixel;
		pixel = &texture->pixels[pixel_index];
		color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
		mlx_put_pixel(map->dir_img, x, wall_start++, color);
	}
}

void draw_wall_with_texture(t_map *map, int x, double ray_angle, 
							 double hor_dist, double ver_dist, double wall_dis)
{
	int wall_start;
	int wall_end;
	mlx_texture_t *texture;
	double wall_x;
	int tex_x;
	
	calculate_wall_boundaries(wall_dis, &wall_start, &wall_end);
	texture = select_texture(map, ray_angle, hor_dist, ver_dist, &wall_x);
	tex_x = calculate_texture_x(texture, wall_x, ray_angle, hor_dist, ver_dist);
	
	draw_ceiling(map, x, wall_start);
	draw_textured_wall(map, texture, x, wall_start, wall_end, tex_x, wall_dis);
	draw_floor(map, x, wall_end);
}
