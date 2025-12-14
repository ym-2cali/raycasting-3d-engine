/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 05:35:00 by alel-you          #+#    #+#             */
/*   Updated: 2025/12/14 16:42:51 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static uint32_t	get_tex_pixel(mlx_texture_t *tex, int x, int y)
{
	int		index;
	uint8_t	*pixel;

	if (!tex || x < 0 || y < 0 || x >= (int)tex->width || y >= (int)tex->height)
		return (0xFF000000);
	index = (y * tex->width + x) * tex->bytes_per_pixel;
	pixel = &tex->pixels[index];
	return ((pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3]);
}

int	get_tex_x(double hit_pos, mlx_texture_t *tex)
{
	int	tex_x;

	tex_x = (int)(hit_pos * tex->width) % tex->width;
	if (tex_x < 0)
		tex_x += tex->width;
	return (tex_x);
}

int	get_tex_y(int pixel_y, int wall_start, int wall_height, mlx_texture_t *tex)
{
	int	tex_y;
	int	d;

	d = pixel_y - wall_start;
	if (wall_height == 0)
		return (0);
	tex_y = (d * (int)tex->height) / wall_height;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)tex->height)
		tex_y = tex->height - 1;
	return (tex_y);
}

uint32_t	sample_texture(mlx_texture_t *tex, double hit_pos,
				int pixel_y, int wall_start, int wall_height)
{
	int	tex_x;
	int	tex_y;

	if (!tex)
		return (0xFF0000FF);
	tex_x = get_tex_x(hit_pos, tex);
	tex_y = get_tex_y(pixel_y, wall_start, wall_height, tex);
	return (get_tex_pixel(tex, tex_x, tex_y));
}