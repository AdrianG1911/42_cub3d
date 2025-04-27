/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:00:17 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/27 17:39:06 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

void	err_msg_exit(char *error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	exit(1);
}

int	main(int argc, char *argv[])
{
	t_game		game;

	if (argc != 2)
		err_msg_exit("Error\nmap path as arg\n");
	(void)argv;
	game.mlx = mlx_init();
	if (game.mlx == NULL)
		err_msg_exit("Error\nmlx fail\n");
	game.win = mlx_new_window(game.mlx, SCREEN_W, SCREEN_H, "cub3d");
	if (game.win == NULL)
		err_msg_exit("Error\nwindow fail\n");
	mlx_hook(game.win, 17, 0, close_window, (void *)&game);
	mlx_loop(game.mlx);
	return (0);
}
