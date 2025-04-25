/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 00:22:24 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/25 19:26:50 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ray_travel_step_side_dist(t_rays *rays, t_player *player)
{
	if (rays->ray_dir_x < 0)
	{
		rays->step_x = -1;
		rays->side_dist_x = (player->x_pos - rays->map_x) * rays->delta_dist_x;
	}
	else
	{
		rays->step_x = 1;
		rays->side_dist_x = \
		(rays->map_x + 1.0 - player->x_pos) * rays->delta_dist_x;
	}
	if (rays->ray_dir_y < 0)
	{
		rays->step_y = -1;
		rays->side_dist_y = (player->y_pos - rays->map_y) * rays->delta_dist_y;
	}
	else
	{
		rays->step_y = 1;
		rays->side_dist_y = \
		(rays->map_y + 1.0 - player->y_pos) * rays->delta_dist_y;
	}
}

void	ray_travel_setup(double ray_angle, t_rays *rays, \
	t_gmap *gmap, t_player *player)
{
	rays->ray_dir_x = cos(ray_angle);
	rays->ray_dir_y = sin(ray_angle);
	rays->delta_dist_x = fabs(1 / rays->ray_dir_x);
	rays->delta_dist_y = fabs(1 / rays->ray_dir_y);
	rays->map_x = (int)player->x_pos;
	rays->map_y = (int)player->y_pos;
	ray_travel_step_side_dist(rays, player);
	rays->hit = 0;
}

void	ray_travel(double ray_angle, t_rays *rays, \
	t_gmap *gmap, t_player *player)
{
	ray_travel_setup(ray_angle, rays, gmap, player);
	while (rays->hit != 1)
	{
		if (rays->side_dist_x < rays->side_dist_y)
		{
			rays->side_dist_x += rays->delta_dist_x;
			rays->map_x += rays->step_x;
			rays->side = 0;
		}
		else
		{
			rays->side_dist_y += rays->delta_dist_y;
			rays->map_y += rays->step_y;
			rays->side = 1;
		}
		if (gmap->map_arr[rays->map_y][rays->map_x] == '1')
			rays->hit = 1;
	}
	if (rays->side == 0)
		rays->r_distance = rays->side_dist_x - rays->delta_dist_x;
	else
		rays->r_distance = rays->side_dist_y - rays->delta_dist_y;
	rays->wall_hit_x = player->x_pos + rays->ray_dir_x * rays->r_distance;
	rays->wall_hit_y = player->y_pos + rays->ray_dir_y * rays->r_distance;
	calc_wall_face(rays);
}

void	ray_caster(t_rays *rays, t_gmap *gmap, t_player *player)
{
	double	ray_angle;
	int		i;

	i = 0;
	while (i < SCREEN_W)
	{
		ray_angle = player->direction_radians - \
		(FOV / 2.0) + ((i + 0.5) * (FOV / SCREEN_W));
		ray_angle = normalize_angle(ray_angle);
		ray_travel(ray_angle, rays, gmap, player);
		rays->distances[i] = rays->r_distance;
		rays->on_wall_x_poses[i] = rays->wall_hit_x;
		rays->on_wall_y_poses[i] = rays->wall_hit_y;
		rays->wall_faces_hit[i] = rays->wall_face_hit;
		i++;
	}
}
