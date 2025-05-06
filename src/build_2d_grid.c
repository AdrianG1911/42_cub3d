/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_2d_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:48:18 by jidler            #+#    #+#             */
/*   Updated: 2025/05/06 09:48:36 by jidler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>
#include <string.h>

static int	get_max_width(char **file, int start, int end)
{
	int	max_width;
	int	len;
	int	i;

	max_width = 0;
	i = start;
	while (i < end)
	{
		len = (int)ft_strlen(file[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

static int	allocate_map_array(t_gmap *gmap, int map_height, int map_width)
{
	int	i;

	gmap->map_arr = (char **)ft_calloc(map_height + 1, sizeof(char *));
	if (!gmap->map_arr)
		return (1);
	i = 0;
	while (i < map_height)
	{
		gmap->map_arr[i] = (char *)ft_calloc(map_width + 1, sizeof(char));
		if (!gmap->map_arr[i])
		{
			while (--i >= 0)
				free(gmap->map_arr[i]);
			free(gmap->map_arr);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	copy_and_pad_lines(t_mapinfo *mapinfo, t_gmap *gmap, int map_start)
{
	int	i;
	int	j;
	int	line_len;

	i = 0;
	while (i < gmap->map_height)
	{
		line_len = (int)ft_strlen(mapinfo->file[map_start + i]);
		j = 0;
		while (j < gmap->map_width)
		{
			if (j < line_len)
				gmap->map_arr[i][j] = mapinfo->file[map_start + i][j];
			else
				gmap->map_arr[i][j] = ' ';
			j++;
		}
		gmap->map_arr[i][gmap->map_width] = '\0';
		i++;
	}
	gmap->map_arr[gmap->map_height] = NULL;
}

int	build_2d_grid(t_mapinfo *mapinfo, t_gmap *gmap, int map_start_index)
{
	int	map_height;
	int	map_width;

	map_height = mapinfo->line_count - map_start_index;
	map_width = get_max_width(mapinfo->file, map_start_index,
			mapinfo->line_count);
	gmap->map_height = map_height;
	gmap->map_width = map_width;
	if (allocate_map_array(gmap, map_height, map_width))
		return (1);
	copy_and_pad_lines(mapinfo, gmap, map_start_index);
	return (0);
}
