/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:30:55 by adrgutie          #+#    #+#             */
/*   Updated: 2025/05/06 14:36:34 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update_step_sizes(t_player *player)
{
	player->x_stepsize = cos(player->direction_radians) * SPEED;
	player->y_stepsize = sin(player->direction_radians) * SPEED;
}

void	init_player(t_gmap *gmap, t_player *player)
{
	char		direction;

	player->x_pos = (double)gmap->player_starting_x_pos + 0.5;
	player->y_pos = (double)gmap->player_starting_y_pos + 0.5;
	direction = gmap->player_starting_direciton;
	if (direction == 'N')
		player->direction_radians = PI * 1.5;
	else if (direction == 'S')
		player->direction_radians = PI / 2;
	else if (direction == 'E')
		player->direction_radians = 0;
	else if (direction == 'W')
		player->direction_radians = PI;
	update_step_sizes(player);
}

//if the angle goes outside: (angle >= 0 && angle < PI * 2.0) it gets normalized
double	normalize_angle(double angle)
{
	if (angle >= 0 && angle < PI * 2.0)
		return (angle);
	angle = fmod(angle, PI * 2.0);
	if (angle < 0)
		angle += PI * 2.0;
	return (angle);
}

void	update_player(t_game *game, t_player *player, t_gmap *gmap)
{
	double	new_dir;
	char	cur_tile;
	int		move;
	int		turn;
	int		strafe;

	move = game->move_foward_flag - game->move_back_flag;
	turn = game->turn_right_flag - game->turn_left_flag;
	strafe = game->move_right_flag - game->move_left_flag;
	player->x_pos += player->x_stepsize * move;
	player->y_pos += player->y_stepsize * move;
	player->x_pos += -player->y_stepsize * strafe;
	player->y_pos += player->x_stepsize * strafe;
	new_dir = player->direction_radians + ((double)turn * TURN_SPEED);
	if (new_dir != player->direction_radians)
	{
		player->direction_radians = normalize_angle(new_dir);
		update_step_sizes(player);
	}
	cur_tile = gmap->map_arr[(int)player->y_pos][(int)player->x_pos];
	if (cur_tile == '1' || cur_tile == ' ')
	{
		player->x_pos = (double)gmap->player_starting_x_pos + 0.5;
		player->y_pos = (double)gmap->player_starting_y_pos + 0.5;
	}
}
