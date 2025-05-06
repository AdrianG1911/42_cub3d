/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:00:17 by adrgutie          #+#    #+#             */
/*   Updated: 2025/05/06 10:11:23 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	err_msg_exit(char *error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	exit(1);
}

long	get_time_mili(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		exit (1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	game_loop(void *param)
{
	t_game	*game;
	long	time_at_last_frame;

	time_at_last_frame = get_time_mili();
	game = (t_game *)param;
	update_player(game->move_foward_flag - game->move_back_flag, \
	game->turn_right_flag - game->turn_left_flag, &(game->player), &game->gmap);
	ray_caster(&(game->rays), &(game->gmap), &(game->player));
	render_loop(&game->rays, &game->render.image_buffer, &game->render);
	mlx_put_image_to_window(game->mlx, game->win, \
		game->render.image_buffer.img_ptr, 0, 0);
	while (get_time_mili() - time_at_last_frame < 15)
		;
	return (0);
}

void	init_stuff(t_game *game)
{
	init_player(&(game->gmap), &(game->player));
	init_render(game, &(game->gmap), &(game->render));
}

int	main(int argc, char *argv[])
{
	t_game		game;

	ft_bzero(&game, sizeof(game));
	if (argc != 2)
		err_msg_exit("Error\nmap path as arg\n");
	game.gmap = validate_map(argv[1]);
	game.mlx = mlx_init();
	if (game.mlx == NULL)
		return (free_game(&game), err_msg_exit("Error\nmlx fail\n"), 1);
	init_stuff(&game);
	game.win = mlx_new_window(game.mlx, SCREEN_W, SCREEN_H, "cub3d");
	if (game.win == NULL)
		return (free_game(&game), err_msg_exit("Error\nwindow fail\n"), 1);
	mlx_hook(game.win, 17, 0, close_window, (void *)&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, (void *)&game);
	mlx_hook(game.win, 3, 1L << 1, key_release, (void *)&game);
	mlx_loop_hook(game.mlx, game_loop, (void *)&game);
	mlx_loop(game.mlx);
	return (0);
}
