/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:49:56 by yael-maa          #+#    #+#             */
/*   Updated: 2025/11/17 01:44:17 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// void	move_forward()
// {
	
// }

void 	update_player(t_map *map)
{
	map->player.rotation_angle += (map->player.turn_direction * ROTAT_SPEED);
	// map->player.x += MOVE_SPEED * cos(map->player.turn_direction);
	// map->player.y += MOVE_SPEED * sin(map->player.walk_direction);
    draw_img(map, map->player_img, get_color(0, 0, 0, 0));
    player_img(map, get_color(204, 57, 9, 255));
	map->player.walk_direction = 0;
	map->player.turn_direction = 0;
}
