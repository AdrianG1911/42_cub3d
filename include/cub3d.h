/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:02:18 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/24 13:27:25 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <errno.h>
# include <math.h>

//PI used for angles
# define PI 3.14159265358979323846
//used to change how far the player moves per timestep
# define SPEED 0.05
//used to change how far the player turns per timestep
# define TURN_SPEED 0.05
//inputs
# define NO_MOVE 0
# define FORWARD 1
# define BACKWARD -1
# define NO_TURN 0
# define LEFT -1
# define RIGHT 1

//map_structure
//player_starting_direction is N, S, E or W
typedef struct s_gmap
{
	char	**map_arr;
	char	*n_wall_path_texture;
	char	*s_wall_path_texture;
	char	*w_wall_path_texture;
	char	*e_wall_path_texture;
	int		floor_color_rgb[3];
	int		ceiling_color_rgb[3];
	int		player_starting_x_pos;
	int		player_starting_y_pos;
	char	player_starting_direciton;
}	t_gmap;

typedef struct s_player
{
	double	direction_radians;
	double	x_stepsize;
	double	y_stepsize;
	double	x_pos;
	double	y_pos;
}	t_player;

#endif