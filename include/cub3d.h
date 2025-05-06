/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:02:18 by adrgutie          #+#    #+#             */
/*   Updated: 2025/05/06 11:03:04 by jidler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// resolution
# define SCREEN_H 900
# define SCREEN_W 1200

// FOV
# define FOV 1.0471975511965977461542

// PI used for angles
# define PI 3.14159265358979323846

// used to change how far the player moves per timestep
# define SPEED 0.05

// used to change how far the player turns per timestep
# define TURN_SPEED 0.05

// inputs
# define NO_MOVE 0
# define FORWARD 1
# define BACKWARD -1
# define NO_TURN 0
# define LEFT -1
# define RIGHT 1

typedef struct s_mapinfo
{
	int				fd;
	int				line_count;
	char			*path;
	char			**file;
	int				height;
	int				width;
	int				index_end_of_map;
}					t_mapinfo;

// map_structure
typedef struct s_gmap
{
	char			**map_arr;
	int				map_height;
	int				map_width;
	char			*n_wall_path_texture;
	char			*s_wall_path_texture;
	char			*w_wall_path_texture;
	char			*e_wall_path_texture;
	int				floor_color_rgb[3];
	int				ceiling_color_rgb[3];
	int				player_starting_x_pos;
	int				player_starting_y_pos;
	char			player_starting_direciton;
}					t_gmap;

typedef struct s_player
{
	double			direction_radians;
	double			x_stepsize;
	double			y_stepsize;
	double			x_pos;
	double			y_pos;
}					t_player;

typedef struct s_rays
{
	double			distances_corrected[SCREEN_W];
	double			on_wall_x_poses[SCREEN_W];
	double			on_wall_y_poses[SCREEN_W];
	char			wall_faces_hit[SCREEN_W];
	double			r_distance;
	double			wall_hit_x;
	double			wall_hit_y;
	char			wall_face_hit;
	int				side;
	int				hit;
	double			ray_dir_x;
	double			ray_dir_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			step_x;
	double			step_y;
	double			side_dist_x;
	double			side_dist_y;
	int				map_x;
	int				map_y;
}					t_rays;

typedef struct s_texture
{
	void			*img_ptr;
	char			*raw_data;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				x;
	int				y;
	double			pixel_per_screen_pixel;
	double			drawing_pos;
}					t_texture;

typedef struct s_render
{
	t_texture		image_buffer;
	t_texture		north_wall_texture;
	t_texture		east_wall_texture;
	t_texture		west_wall_texture;
	t_texture		south_wall_texture;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	int				wall_height;
	int				wall_slice_index;
	t_texture		current_wall;
}					t_render;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_gmap			gmap;
	t_player		player;
	int				move_foward_flag;
	int				move_back_flag;
	int				turn_left_flag;
	int				turn_right_flag;
	t_rays			rays;
	t_render		render;
}					t_game;

// player.c
void				update_player(int move, int turn, t_player *player,
						t_gmap *gmap);
void				update_step_sizes(t_player *player);
void				init_player(t_gmap *gmap, t_player *player);
double				normalize_angle(double angle);

// raycaster.c / raycaster_2.c
void				ray_caster(t_rays *rays, t_gmap *gmap, t_player *player);
void				calc_wall_face(t_rays *rays);

// input
int					key_press(int keycode, void *param);
int					key_release(int keycode, void *param);
int					close_window(void *param);

// render
void				init_render(t_game *game, t_gmap *gmap, t_render *render);
// void		draw_floor_and_cieling(t_render *render, t_texture *image_buffer);
int					get_wall_point(t_render *render, t_rays *rays,
						t_texture *image_buffer);
void				set_cur_wall(t_render *render, t_rays *rays,
						t_texture *image_buffer);
void				draw_wall(t_render *render, t_texture *image_buffer);
void				render_loop(t_rays *rays, t_texture *image_buffer,
						t_render *render);

int					check_file_type(const char *filepath, int expect_cub);
t_gmap				validate_map(char *path);

int					is_spawn(char c);
int					is_allowed(char c);
int					check_row_walls(const char *row);
int					check_side_walls(const char *row);

// Map parsing and validation
int					load_lines_to_memory(const char *path, t_mapinfo *mapinfo);
int					extract_header_data(t_mapinfo *mapinfo, t_gmap *gmap,
						int *map_start_index);
int					find_map_start_index(t_mapinfo *mapinfo);
int					build_2d_grid(t_mapinfo *mapinfo, t_gmap *gmap,
						int map_start_index);
int					check_color_texture(t_gmap *gmap);
int					check_borders(t_gmap *gmap, char *player_dir);
int					get_last_valid_row(t_gmap *gmap);
void				free_lines(char **lines, int count);
// free
void				free_game(t_game *game);
#endif
