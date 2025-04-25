/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:02:18 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/25 19:23:56 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <errno.h>
# include <math.h>

//resolution
# define SCREEN_H 900
# define SCREEN_W 1200
//FOV
# define FOV 1.0471975511965977461542
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
	int		map_height;
	int		map_width;
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

typedef struct s_rays
{
	double	distances[SCREEN_W];
	double	on_wall_x_poses[SCREEN_W];
	double	on_wall_y_poses[SCREEN_W];
	char	wall_faces_hit[SCREEN_W];
	double	r_distance;
	double	wall_hit_x;
	double	wall_hit_y;
	char	wall_face_hit;
	int		side;
	int		hit;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	step_x;
	double	step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
}	t_rays;

//player.c
void		update_player(int move, int turn, t_player *player);
void		update_step_sizes(t_player *player);
t_player	*init_player(t_gmap *gmap, t_player *player);
double		normalize_angle(double angle);
//raycaster.c / raycaster_2.c
void		ray_caster(t_rays *rays, t_gmap *gmap, t_player *player);
void		calc_wall_face(t_rays *rays);

#endif