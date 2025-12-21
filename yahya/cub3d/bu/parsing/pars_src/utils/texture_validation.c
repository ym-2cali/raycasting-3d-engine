/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 05:20:00 by alel-you          #+#    #+#             */
/*   Updated: 2025/12/14 05:20:00 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

static char	*extract_texture_path(char *line)
{
	char	**parts;
	char	*path;
	char	*trimmed;
	int		i;

	if (!line)
		return (NULL);
	parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1])
		return (NULL);
	trimmed = ft_strtrim(parts[1], " \n\t\r");
	path = ft_strdup(trimmed);
	free(trimmed);
	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (path);
}

static int	check_file_exists(char *filepath)
{
	int	fd;

	if (!filepath)
		return (0);
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static int	validate_texture_file(char *texture_line, char *direction)
{
	char	*path;
	int		result;

	path = extract_texture_path(texture_line);
	if (!path)
	{
		printf("Error\n%s texture: Invalid path format\n", direction);
		return (0);
	}
	result = check_file_exists(path);
	if (!result)
	{
		printf("Error\n%s texture file not found: %s\n", direction, path);
		free(path);
		return (0);
	}
	free(path);
	return (1);
}

int	validate_all_textures(t_map *map)
{
	if (!map)
		return (0);
	if (!validate_texture_file(map->no_texture, "North"))
		return (0);
	if (!validate_texture_file(map->so_texture, "South"))
		return (0);
	if (!validate_texture_file(map->we_texture, "West"))
		return (0);
	if (!validate_texture_file(map->ea_texture, "East"))
		return (0);
	return (1);
}
