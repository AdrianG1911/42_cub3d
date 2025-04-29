/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 23:14:02 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/30 03:00:24 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_floor_and_cieling(t_render *render, t_texture *image_buffer)
{
	char	*pixel;

	image_buffer->x = 0;
	while (image_buffer->x < SCREEN_W)
	{
		image_buffer->y = 0;
		while (image_buffer < SCREEN_H)
		{
			pixel = image_buffer->raw_data + \
			(image_buffer->y * image_buffer->line_length + image_buffer->x * \
				(image_buffer->bits_per_pixel / 8));
			if (image_buffer->y < SCREEN_H / 2)
				*(unsigned int *)pixel = render->ceiling_color;
			else
				*(unsigned int *)pixel = render->floor_color;
			image_buffer->y++;
		}
		image_buffer->x++;
	}
}

int	get_wall_point(t_render *render, t_rays *rays, t_texture *image_buffer)
{
	double	wall_point_double;
	int		wall_point_int;
	double	x_pos;
	double	y_pos;
	char	wall_face;

	x_pos = rays->on_wall_x_poses[image_buffer->x];
	y_pos = rays->on_wall_y_poses[image_buffer->x];
	wall_face = rays->wall_faces_hit[image_buffer->x];
	if (wall_face == 'N')
		wall_point_double = fabs(fmod(x_pos, 1.0) - 1.0);
	else if (wall_face == 'S')
		wall_point_double = fmod(x_pos, 1.0);
	else if (wall_face == 'E')
		wall_point_double = fmod(y_pos, 1.0);
	else if (wall_face == 'W')
		wall_point_double = fabs(fmod(y_pos, 1.0) - 1.0);
	wall_point_int = \
	((int)(wall_point_double * render->north_wall_texture.width));
	if (wall_point_int == render->north_wall_texture.width)
		wall_point_int--;
	return (wall_point_int);
}
