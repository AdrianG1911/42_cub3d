/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:00:17 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/27 21:48:15 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	err_msg_exit(char *error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	exit(1);
}

int	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	update_player(game->move_foward_flag - game->move_back_flag, \
	game->turn_right_flag - game->turn_left_flag, &(game->player));
	ray_caster(&(game->rays), &(game->gmap), &(game->player));
	//rendering step here
	return (0);
}

void	init_stuff(t_game *game)
{
	//init gmap
	init_player(&(game->gmap), &(game->player));
}

int	main(int argc, char *argv[])
{
	t_game		game;

	ft_bzero(&game, sizeof(game));
	if (argc != 2)
		err_msg_exit("Error\nmap path as arg\n");
	//map validation
	init_stuff(&game);
	(void)argv;//to be removed
	game.mlx = mlx_init();
	if (game.mlx == NULL)
		err_msg_exit("Error\nmlx fail\n");
	game.win = mlx_new_window(game.mlx, SCREEN_W, SCREEN_H, "cub3d");
	if (game.win == NULL)
		err_msg_exit("Error\nwindow fail\n");
	mlx_hook(game.win, 17, 0, close_window, (void *)&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, (void *)&game);
	mlx_hook(game.win, 3, 1L << 1, key_release, (void *)&game);
	// mlx_loop_hook(game.mlx, game_loop, (void *)&game);
	mlx_loop(game.mlx);
	return (0);
}
