/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:49:56 by yael-maa          #+#    #+#             */
/*   Updated: 2025/11/01 15:59:49 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void 	update_player(t_map *map)
{
	map->player.x += MOVE_SPEED * map->player.turn_direction;
	map->player.y += MOVE_SPEED * map->player.walk_direction;
	map->player.walk_direction = 0;
	map->player.turn_direction = 0;
	map_rendering(map, 0, 0);
}