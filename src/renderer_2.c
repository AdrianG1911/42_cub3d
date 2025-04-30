/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 23:14:02 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/30 19:56:30 by adrgutie         ###   ########.fr       */
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
		while (image_buffer->y < SCREEN_H)
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
		wall_point_double = fabs(fmod(y_pos, 1.0) - 1.0);
	else if (wall_face == 'W')
		wall_point_double = fmod(y_pos, 1.0);
	wall_point_int = \
	((int)(wall_point_double * render->north_wall_texture.width));
	if (wall_point_int == render->north_wall_texture.width)
		wall_point_int--;
	return (wall_point_int);
}

void	set_cur_wall(t_render *render, t_rays *rays, t_texture *image_buffer)
{
	char	cur_wall;

	cur_wall = rays->wall_faces_hit[image_buffer->x];
	if (cur_wall == 'N')
		render->current_wall = render->north_wall_texture;
	else if (cur_wall == 'E')
		render->current_wall = render->east_wall_texture;
	else if (cur_wall == 'W')
		render->current_wall = render->west_wall_texture;
	else if (cur_wall == 'S')
		render->current_wall = render->south_wall_texture;
}

void	get_and_draw_pixel_to_buffer(t_texture *image_buffer, \
	t_texture *cur_wall, t_render *render)
{
	char			*pixel;
	unsigned int	color;

	pixel = cur_wall->raw_data + (cur_wall->y * cur_wall->line_length) + \
		(render->wall_slice_index * (cur_wall->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	pixel = image_buffer->raw_data + \
	(image_buffer->y * image_buffer->line_length) + \
	(image_buffer->x * (image_buffer->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	draw_wall(t_render *render, t_texture *image_buffer)
{
	t_texture		cur_wall;

	cur_wall = render->current_wall;
	cur_wall.y = 0;
	image_buffer->y = (SCREEN_H / 2) - (render->wall_height / 2);
	if (image_buffer->y < 0)
		image_buffer->y = 0;
	cur_wall.pixel_per_screen_pixel = \
		(double)cur_wall.height / render->wall_height;
	cur_wall.drawing_pos = cur_wall.pixel_per_screen_pixel * \
		(image_buffer->y - ((SCREEN_H / 2) - (render->wall_height / 2)));
	if (cur_wall.drawing_pos < 0)
		cur_wall.drawing_pos = 0;
	while (image_buffer->y < SCREEN_H && \
		(int)cur_wall.drawing_pos < cur_wall.height)
	{
		cur_wall.y = (int)cur_wall.drawing_pos;
		get_and_draw_pixel_to_buffer(image_buffer, &cur_wall, render);
		cur_wall.drawing_pos += cur_wall.pixel_per_screen_pixel;
		image_buffer->y++;
	}
}
