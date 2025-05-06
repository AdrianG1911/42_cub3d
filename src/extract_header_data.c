/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_header_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:03:50 by 42student         #+#    #+#             */
/*   Updated: 2025/05/06 11:20:50 by jidler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <ctype.h>

static int	extract_header_loop(t_mapinfo *mapinfo, t_gmap *gmap, int *found,
		int *i)
{
	char	*line;

	while (*i < mapinfo->line_count && mapinfo->file[*i])
	{
		line = mapinfo->file[*i];
		while (*line == ' ' || *line == '\t')
			line++;
		if (ft_isdigit((unsigned char)*line))
			break ;
		if (parse_header_line(line, gmap, found))
			return (1);
		(*i)++;
	}
	return (0);
}

int	extract_header_data(t_mapinfo *mapinfo, t_gmap *gmap, int *map_start_index)
{
	int	found[4];
	int	i;

	found[0] = 0;
	found[1] = 0;
	found[2] = 0;
	found[3] = 0;
	init_gmap_colors(gmap);
	i = 0;
	if (extract_header_loop(mapinfo, gmap, found, &i))
		return (1);
	if (map_start_index)
		*map_start_index = i;
	if (!found[0] || !found[1] || !found[2] || !found[3])
		return (1);
	return (0);
}
