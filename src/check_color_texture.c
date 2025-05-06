/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:04:39 by jidler            #+#    #+#             */
/*   Updated: 2025/05/06 11:44:08 by jidler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH_LEN 1024

static int	check_texture_extension(const char *path)
{
	size_t	len;

	if (!path || *path == '\0')
		return (1);
	len = ft_strlen(path);
	if (len < 4 || strcmp(path + len - 4, ".xpm") != 0)
		return (1);
	return (0);
}

static int	try_open_texture_path(const char *path)
{
	int		fd;
	char	alt_path[MAX_PATH_LEN];

	fd = open(path, O_RDONLY);
	if (fd >= 0)
	{
		close(fd);
		return (0);
	}
	if (ft_strncmp(path, "textures/", 9) == 0)
	{
		if (snprintf(alt_path, MAX_PATH_LEN, "../%s", path) >= MAX_PATH_LEN)
			return (1);
		fd = open(alt_path, O_RDONLY);
		if (fd < 0)
			return (1);
		close(fd);
		return (0);
	}
	return (1);
}

static int	is_valid_texture_path(const char *path)
{
	if (check_texture_extension(path))
		return (1);
	if (try_open_texture_path(path))
		return (1);
	return (0);
}

static int	is_valid_rgb(int rgb[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (1);
		i++;
	}
	return (0);
}

int	check_color_texture(t_gmap *gmap)
{
	if (!gmap->n_wall_path_texture || !gmap->s_wall_path_texture
		|| !gmap->w_wall_path_texture || !gmap->e_wall_path_texture)
		return (1);
	if (is_valid_texture_path(gmap->n_wall_path_texture)
		|| is_valid_texture_path(gmap->s_wall_path_texture)
		|| is_valid_texture_path(gmap->w_wall_path_texture)
		|| is_valid_texture_path(gmap->e_wall_path_texture))
		return (1);
	if (is_valid_rgb(gmap->floor_color_rgb)
		|| is_valid_rgb(gmap->ceiling_color_rgb))
		return (1);
	return (0);
}
