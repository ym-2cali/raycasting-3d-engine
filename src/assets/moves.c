/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:49:56 by yael-maa          #+#    #+#             */
/*   Updated: 2025/11/17 03:35:01 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void 	update_player(t_map *map)
{
	double	move_steps;

	move_steps = map->player.walk_direction * MOVE_SPEED;
	map->player.rotation_angle += (map->player.turn_direction * ROTAT_SPEED);
	map->player.x += cos(map->player.rotation_angle) * move_steps;
	map->player.y += sin(map->player.rotation_angle) * move_steps;
	mlx_delete_image(map->mlx, map->player_img);
	map->player_img = mlx_new_image(map->mlx, map->x_size, map->y_size);
	player_img(map, get_color(204, 57, 9, 255));
	mlx_image_to_window(map->mlx, map->player_img, map->player.x, map->player.y);
	map->player.walk_direction = 0;
	map->player.turn_direction = 0;
}
