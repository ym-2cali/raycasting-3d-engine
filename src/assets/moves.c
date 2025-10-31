/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:49:56 by yael-maa          #+#    #+#             */
/*   Updated: 2025/10/31 18:55:48 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void 	update_player(t_map *map)
{
	double	move_step;

	// map->player.x += cos(double(ROTAT_ANGLE)) * 20;
	move_step = map->player.walk_direction * MOVE_SPEED;
	map->player.rotation_angle += map->player.turn_direction * ROTAT_SPEED;
	map->player.x += cos(map->player.rotation_angle) * move_step;
	map->player.y += sin(map->player.rotation_angle) * move_step;
	map->player.walk_direction = 0;
    map->player.turn_direction = 0;
	map_rendering(map, 0, 0);
}