/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:25:32 by adrgutie          #+#    #+#             */
/*   Updated: 2025/05/06 11:37:34 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	code_to_key(int keycode)
{
	if (keycode == 97)
		return ('L');
	if (keycode == 100)
		return ('R');
	if (keycode == 119)
		return ('F');
	if (keycode == 115)
		return ('B');
	if (keycode == 65307)
		return ('Q');
	return ('N');
}

int	key_press(int keycode, void *param)
{
	t_game	*game;
	char	key;

	game = (t_game *)param;
	key = code_to_key(keycode);
	if (key == 'N')
		return (0);
	if (key == 'Q')
	{
		free_game(game);
		exit(0);
	}
	if (key == 'L')
		game->turn_left_flag = 1;
	else if (key == 'R')
		game->turn_right_flag = 1;
	else if (key == 'B')
		game->move_back_flag = 1;
	else if (key == 'F')
		game->move_foward_flag = 1;
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_game	*game;
	char	key;

	game = (t_game *)param;
	key = code_to_key(keycode);
	if (key == 'N')
		return (0);
	if (key == 'L')
		game->turn_left_flag = 0;
	else if (key == 'R')
		game->turn_right_flag = 0;
	else if (key == 'B')
		game->move_back_flag = 0;
	else if (key == 'F')
		game->move_foward_flag = 0;
	return (0);
}

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_game(game);
	exit(0);
	return (0);
}
