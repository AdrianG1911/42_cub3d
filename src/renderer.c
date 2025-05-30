/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:36:13 by adrgutie          #+#    #+#             */
/*   Updated: 2025/05/06 10:56:52 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_texture	load_xpm(t_game *game, char *path_to_xpm)
{
	t_texture	texture;

	texture.img_ptr = mlx_xpm_file_to_image(game->mlx, path_to_xpm, \
		&texture.width, &texture.height);
	if (texture.img_ptr == NULL)
	{
		ft_putstr_fd("Failed to load texture\n", 2);
		exit(1);
	}
	texture.raw_data = mlx_get_data_addr(texture.img_ptr, \
		&texture.bits_per_pixel, &texture.line_length, &texture.endian);
	texture.x = 0;
	texture.y = 0;
	return (texture);
}

t_texture	load_image_buffer(t_game *game)
{
	t_texture	texture;

	texture.img_ptr = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	if (texture.img_ptr == NULL)
	{
		ft_putstr_fd("Failed to load image buffer\n", 2);
		exit(1);
	}
	texture.raw_data = mlx_get_data_addr(texture.img_ptr, \
		&texture.bits_per_pixel, &texture.line_length, &texture.endian);
	texture.width = SCREEN_W;
	texture.height = SCREEN_H;
	texture.x = 0;
	texture.y = 0;
	return (texture);
}

void	init_render(t_game *game, t_gmap *gmap, t_render *render)
{
	render->north_wall_texture = load_xpm(game, gmap->n_wall_path_texture);
	render->south_wall_texture = load_xpm(game, gmap->s_wall_path_texture);
	render->east_wall_texture = load_xpm(game, gmap->e_wall_path_texture);
	render->west_wall_texture = load_xpm(game, gmap->w_wall_path_texture);
	render->image_buffer = load_image_buffer(game);
	render->floor_color = gmap->floor_color_rgb[0] << 16;
	render->floor_color += gmap->floor_color_rgb[1] << 8;
	render->floor_color += gmap->floor_color_rgb[2];
	render->ceiling_color = gmap->ceiling_color_rgb[0] << 16;
	render->ceiling_color += gmap->ceiling_color_rgb[1] << 8;
	render->ceiling_color += gmap->ceiling_color_rgb[2];
}

void	draw_floor_and_cieling_strip(t_render *render, t_texture *image_buffer)
{
	int		floor_ceiling_h;
	int		y;
	char	*pixel;

	floor_ceiling_h = (SCREEN_H - render->wall_height) / 2;
	y = 0;
	while (y < floor_ceiling_h)
	{
		pixel = image_buffer->raw_data + \
		(y * image_buffer->line_length + image_buffer->x * \
		(image_buffer->bits_per_pixel / 8));
		*(unsigned int *)pixel = render->ceiling_color;
		y++;
	}
	y += render->wall_height;
	while (y < SCREEN_H)
	{
		pixel = image_buffer->raw_data + \
		(y * image_buffer->line_length + image_buffer->x * \
		(image_buffer->bits_per_pixel / 8));
		*(unsigned int *)pixel = render->floor_color;
		y++;
	}
}

void	render_loop(t_rays *rays, t_texture *image_buffer, t_render *render)
{
	image_buffer->x = 0;
	while (image_buffer->x < SCREEN_W)
	{
		render->wall_height = (int)(SCREEN_H / \
				rays->distances_corrected[image_buffer->x]);
		render->wall_height &= ~1;
		render->wall_slice_index = get_wall_point(render, rays, image_buffer);
		set_cur_wall(render, rays, image_buffer);
		draw_floor_and_cieling_strip(render, image_buffer);
		draw_wall(render, image_buffer);
		image_buffer->x++;
	}
}
