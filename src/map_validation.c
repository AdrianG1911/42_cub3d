/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:21:12 by jidler            #+#    #+#             */
/*   Updated: 2025/05/06 11:22:05 by jidler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

static int	validate_file_and_load(const char *path, t_mapinfo *map_data)
{
	if (check_file_type(path, 1) == 1)
	{
		printf("Error\nInvalid file type\n");
		return (1);
	}
	if (load_lines_to_memory(path, map_data))
	{
		printf("Error\nFailed to load map file into memory\n");
		return (1);
	}
	return (0);
}

static int	validate_header(const t_mapinfo *map_data, t_gmap *gmap,
		int *map_start_index)
{
	*map_start_index = find_map_start_index((t_mapinfo *)map_data);
	if (*map_start_index == -1)
	{
		printf("Error\nCould not find start of map in file\n");
		return (1);
	}
	if (extract_header_data((t_mapinfo *)map_data, gmap, map_start_index))
	{
		printf("Error\nFailed to extract header data\n");
		return (1);
	}
	return (0);
}

static int	validate_grid_and_borders(const t_mapinfo *map_data, t_gmap *gmap,
		int map_start_index, char *player_dir)
{
	if (build_2d_grid((t_mapinfo *)map_data, gmap, map_start_index))
	{
		printf("Error\nFailed to build 2D grid from map\n");
		return (1);
	}
	if (check_borders(gmap, player_dir) == 1)
	{
		printf("Error\nMap borders or player position invalid\n");
		return (1);
	}
	if (check_color_texture(gmap) == 1)
	{
		printf("Error\nInvalid color or texture information\n");
		return (1);
	}
	return (0);
}

t_gmap	validate_map(char *path)
{
	t_gmap		gmap = {0};
	t_mapinfo	map_data = {0};
	int			map_start_index;
	char		player_dir;

	if (validate_file_and_load(path, &map_data))
		exit(1);
	if (validate_header(&map_data, &gmap, &map_start_index))
	{
		if (map_data.file)
			free_lines(map_data.file, map_data.line_count);
		exit(1);
	}
	if (validate_grid_and_borders(&map_data, &gmap, map_start_index,
			&player_dir))
	{
		if (map_data.file)
			free_lines(map_data.file, map_data.line_count);
		exit(1);
	}
	gmap.player_starting_direciton = player_dir;
	free_lines(map_data.file, map_data.line_count);
	return (gmap);
}
