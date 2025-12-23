/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:20:34 by yael-maa          #+#    #+#             */
/*   Updated: 2025/12/23 00:25:58 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

mlx_texture_t	*select_texture(t_map *map, double ray_angle, double *wall_x)
{
	mlx_texture_t	*texture;

	texture = NULL;
	if (map->inter.x < map->inter.y)
		select_hor_texture(map, ray_angle, &texture, wall_x);
	else
		select_ver_texture(map, ray_angle, &texture, wall_x);
	return (texture);
}

static int	calculate_texture_x_helper(mlx_texture_t *texture, int tex_x,
	t_texture_data *data)
{
	if (data->hor_dist < data->ver_dist && !data->facing_up)
		tex_x = texture->width - tex_x - 1;
	if (data->hor_dist >= data->ver_dist && data->facing_right)
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

int	calculate_texture_x(mlx_texture_t *texture, double wall_x,
	t_texture_data *data)
{
	int	tex_x;

	if (!texture)
		return (0);
	data->facing_up = (data->ray_angle > M_PI
			&& data->ray_angle < 2 * M_PI);
	data->facing_right = (data->ray_angle < M_PI / 2
			|| data->ray_angle > 3 * M_PI / 2);
	wall_x /= TILE_SIZE;
	wall_x = wall_x - floor(wall_x);
	tex_x = (int)(wall_x * texture->width);
	tex_x = calculate_texture_x_helper(texture, tex_x, data);
	return (tex_x);
}

static void	draw_textured_wall_helper(t_map *map, t_wall_draw *w)
{
	int			tex_y;
	int			pixel_index;
	uint8_t		*pixel;
	uint32_t	color;
	double		wall_y;

	wall_y = (double)(w->wall_start - (WINDOW_HEIGHT / 2 - (int)w->wall_dis))
		/ (double)(w->wall_dis * 2);
	tex_y = (int)(wall_y * w->texture->height);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)w->texture->height)
		tex_y = w->texture->height - 1;
	pixel_index = (tex_y * w->texture->width + w->tex_x)
		* w->texture->bytes_per_pixel;
	pixel = &w->texture->pixels[pixel_index];
	color = (pixel[0] << 24) | (pixel[1] << 16)
		| (pixel[2] << 8) | pixel[3];
	mlx_put_pixel(map->dir_img, w->x, w->wall_start, color);
}

void	draw_textured_wall(t_map *map, t_wall_draw *w)
{
	if (!w->texture)
		return ;
	while (w->wall_start < w->wall_end)
	{
		draw_textured_wall_helper(map, w);
		w->wall_start++;
	}
}
