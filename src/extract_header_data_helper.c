/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_header_data_helper.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:03:50 by johankawamu       #+#    #+#             */
/*   Updated: 2025/05/06 12:04:30 by jidler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <ctype.h>

int	parse_rgb(const char *str, int rgb[3])
{
	int		c;
	int		i;
	char	*end;

	i = 0;
	c = 0;
	while (c < 3)
	{
		while (str[i] && (str[i] == ' ' || str[i] == ','))
			i++;
		if (!str[i] || str[i] == '\n')
			return (1);
		rgb[c] = ft_strtol(&str[i], &end);
		if (&str[i] == end || rgb[c] < 0 || rgb[c] > 255)
			return (1);
		i = (int)(end - str);
		c++;
	}
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	extract_texture_path(char *line, char **texture_path, int *found,
		int offset)
{
	char	*path;
	char	*end;

	if (*found)
		return (1);
	*found = 1;
	path = line + offset;
	while (*path == ' ' || *path == '\t')
		path++;
	end = path + ft_strlen(path) - 1;
	while (end > path && (*end == ' ' || *end == '\t'))
		end--;
	*(end + 1) = '\0';
	*texture_path = ft_strdup(path);
	return (0);
}

void	init_gmap_colors(t_gmap *gmap)
{
	int	c;

	c = 0;
	while (c < 3)
	{
		gmap->floor_color_rgb[c] = -1;
		gmap->ceiling_color_rgb[c] = -1;
		c++;
	}
}
