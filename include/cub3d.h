/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:02:18 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/23 16:24:47 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
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

#endif