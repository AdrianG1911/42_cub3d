/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:00:17 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/30 19:02:48 by adrgutie         ###   ########.fr       */
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
	while (get_time_mili() - time_at_last_frame < 10)
		;
	return (0);
}

void	init_stuff(t_game *game)
{
	//init gmap
	game->gmap.n_wall_path_texture = ft_strdup("textures/North.xpm");//for testing
	game->gmap.s_wall_path_texture = ft_strdup("textures/South.xpm");//for testing
	game->gmap.e_wall_path_texture = ft_strdup("textures/East.xpm");//for testing
	game->gmap.w_wall_path_texture = ft_strdup("textures/West.xpm");//for testing
	game->gmap.ceiling_color_rgb[0] = 100;//test
	game->gmap.ceiling_color_rgb[1] = 200;//test
	game->gmap.ceiling_color_rgb[2] = 100;//test
	game->gmap.floor_color_rgb[0] = 100;//test
	game->gmap.floor_color_rgb[1] = 50;//test
	game->gmap.floor_color_rgb[2] = 100;//test
	game->gmap.player_starting_direciton = 'N';//test
	game->gmap.player_starting_x_pos = 3;//test
	game->gmap.player_starting_y_pos = 3;//test
	game->gmap.map_arr = (char **)ft_calloc(6, sizeof(char *));//test
	game->gmap.map_height = 6;//test
	game->gmap.map_width = 6;//test
	game->gmap.map_arr[0] = ft_strdup("111111");//test
	game->gmap.map_arr[1] = ft_strdup("101011");//test
	game->gmap.map_arr[2] = ft_strdup("100001");//test
	game->gmap.map_arr[3] = ft_strdup("100001");//test
	game->gmap.map_arr[4] = ft_strdup("101001");//test
	game->gmap.map_arr[5] = ft_strdup("111111");//test
	init_player(&(game->gmap), &(game->player));
	init_render(game, &(game->gmap), &(game->render));
}

int	main(int argc, char *argv[])
{
	t_game		game;

	ft_bzero(&game, sizeof(game));
	if (argc != 2)
		err_msg_exit("Error\nmap path as arg\n");
	//map validation
	
	(void)argv;//to be removed
	game.mlx = mlx_init();
	if (game.mlx == NULL)
		err_msg_exit("Error\nmlx fail\n");
	init_stuff(&game);
	game.win = mlx_new_window(game.mlx, SCREEN_W, SCREEN_H, "cub3d");
	if (game.win == NULL)
		err_msg_exit("Error\nwindow fail\n");
	mlx_hook(game.win, 17, 0, close_window, (void *)&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, (void *)&game);
	mlx_hook(game.win, 3, 1L << 1, key_release, (void *)&game);
	mlx_loop_hook(game.mlx, game_loop, (void *)&game);
	mlx_loop(game.mlx);
	return (0);
}
