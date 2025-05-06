/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_header_data_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:03:50 by johankawamu       #+#    #+#             */
/*   Updated: 2025/05/06 10:56:43 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <ctype.h>

static int	parse_texture_line(char *line, t_gmap *gmap, int *found)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (extract_texture_path(line, &gmap->n_wall_path_texture,
			&found[0], 3));
	if (!ft_strncmp(line, "SO ", 3))
		return (extract_texture_path(line, &gmap->s_wall_path_texture,
			&found[1], 3));
	if (!ft_strncmp(line, "WE ", 3))
		return (extract_texture_path(line, &gmap->w_wall_path_texture,
			&found[2], 3));
	if (!ft_strncmp(line, "EA ", 3))
		return (extract_texture_path(line, &gmap->e_wall_path_texture,
			&found[3], 3));
	return (0);
}

static int	parse_color_line(char *line, t_gmap *gmap, int *found)
{
	if (!ft_strncmp(line, "F ", 2))
		return (parse_rgb(line + 2, gmap->floor_color_rgb));
	if (!ft_strncmp(line, "C ", 2))
		return (parse_rgb(line + 2, gmap->ceiling_color_rgb));
	return (0);
}

int	parse_header_line(char *line, t_gmap *gmap, int *found)
{
	if (parse_texture_line(line, gmap, found))
		return (1);
	if (parse_color_line(line, gmap, found))
		return (1);
	return (0);
} 
