/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_map_start_index.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:11:07 by jidler            #+#    #+#             */
/*   Updated: 2025/05/06 11:11:36 by jidler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <ctype.h>

int	find_map_start_index(t_mapinfo *mapinfo)
{
	int		i;
	char	*line;

	i = 0;
	while (i < mapinfo->line_count && mapinfo->file[i])
	{
		line = mapinfo->file[i];
		while (*line == ' ' || *line == '\t')
			line++;
		if (isdigit((unsigned char)*line))
			return (i);
		i++;
	}
	return (-1);
}
