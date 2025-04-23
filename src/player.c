/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:30:55 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/23 22:12:52 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_step_sizes(t_player *player)
{
	player->x_stepsize = cos(player->direction_radians) * SPEED;
	player->y_stepsize = sin(player->direction_radians) * SPEED;
}

t_player	*init_player(t_gmap *gmap, t_player *player)
{
	char		direction;

	player->x_pos = (double)gmap->player_starting_x_pos;
	player->y_pos = (double)gmap->player_starting_y_pos;
	direction = gmap->player_starting_direciton;
	if (direction == 'N')
		player->direction_radians = (PI * 3.0) / 2.0;
	else if (direction == 'S')
		player->direction_radians = PI / 2.0;
	else if (direction == 'E')
		player->direction_radians = 0;
	else if (direction == 'W')
		player->direction_radians = PI;
	update_step_sizes(player);
}
