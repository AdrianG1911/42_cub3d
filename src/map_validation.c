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

t_gmap	validate_map(char *path)
{
	t_mapinfo	map_data;
	t_gmap		gmap;
	int			map_start_index;
	char		player_dir;
	int			extract_result;

	if (check_file_type(path, 1) == 1)
		exit(1);
	if (load_lines_to_memory(path, &map_data))
		exit(1);
	map_start_index = find_map_start_index(&map_data);
	extract_result = extract_header_data(&map_data, &gmap, &map_start_index);
	if (extract_result)
		exit(1);
	if (build_2d_grid(&map_data, &gmap, map_start_index))
		exit(1);
	if (check_borders(&gmap, &player_dir) == 1)
		exit(1);
	if (check_color_texture(&gmap) == 1)
		exit(1);
	gmap.player_starting_direciton = player_dir;
	free_lines(map_data.file, map_data.line_count);
	return (gmap);
}
