/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:00:17 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/29 23:12:38 by adrgutie         ###   ########.fr       */
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
	init_player(&(game->gmap), &(game->player));
	init_render(game, &(game->gmap), &(game->render));
}

void	make_buffer_green(t_texture *main_buffer)//test function
{
	int		x;
	int		y;
	int		color;
	char	*pixel;

	color = 0x00FF00;
	y = 0;
	while (y < main_buffer->height)
	{
		x = 0;
		while (x < main_buffer->width)
		{
			pixel = main_buffer->raw_data + \
			(y * main_buffer->line_length + x * \
				(main_buffer->bits_per_pixel / 8));
			*(unsigned int *)pixel = color;
			x++;
		}
		y++;
	}
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
	//mlx_loop_hook(game.mlx, game_loop, (void *)&game);
	make_buffer_green(&game.render.image_buffer);
	mlx_put_image_to_window(game.mlx, game.win, \
		game.render.image_buffer.img_ptr, 0, 0);
	mlx_loop(game.mlx);
	return (0);
}
