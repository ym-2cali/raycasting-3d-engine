/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 05:30:00 by alel-you          #+#    #+#             */
/*   Updated: 2025/12/22 21:42:29 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	*get_texture_path(char *line)
{
	char	**parts;
	char	*path;
	char	*trimmed;
	int		i;

	parts = ft_split(line, ' ');
	if (!parts)
		return (NULL);
	i = 1;
	while (parts[i] && (parts[i][0] == ' ' || parts[i][0] == '\t'))
		i++;
	if (!parts[i])
		return (NULL);
	trimmed = ft_strtrim(parts[i], " \n\t");
	path = ft_strdup(trimmed);
	return (path);
}

static mlx_texture_t	*load_one_texter(char *texture_line)
{
	char			*path;
	mlx_texture_t	*texture;

	path = get_texture_path(texture_line);
	if (!path)
		return (NULL);
	texture = mlx_load_png(path);
	return (texture);
}

int	load_all_textures(t_map *map)
{
	if (!map)
		return (0);
	map->north_texture = load_one_texter(map->no_texture);
	if (!map->north_texture)
		return (printf("Error\nFailed to load North texture\n"), 0);
	map->south_texture = load_one_texter(map->so_texture);
	if (!map->south_texture)
		return (printf("Error\nFailed to load South texture\n"), 0);
	map->west_texture = load_one_texter(map->we_texture);
	if (!map->west_texture)
		return (printf("Error\nFailed to load West texture\n"), 0);
	map->east_texture = load_one_texter(map->ea_texture);
	if (!map->east_texture)
		return (printf("Error\nFailed to load East texture\n"), 0);
	return (1);
}

void	free_textures(t_map *map)
{
	if (!map)
		return ;
	if (map->north_texture)
		mlx_delete_texture(map->north_texture);
	if (map->south_texture)
		mlx_delete_texture(map->south_texture);
	if (map->west_texture)
		mlx_delete_texture(map->west_texture);
	if (map->east_texture)
		mlx_delete_texture(map->east_texture);
}
