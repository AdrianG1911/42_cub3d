/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:52:33 by jidler            #+#    #+#             */
/*   Updated: 2025/05/06 10:02:35 by jidler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <string.h>

static int	check_border_rows(t_gmap *gmap, int last_row)
{
	if (last_row < 0)
		return (1);
	if (check_row_walls(gmap->map_arr[0]))
		return (1);
	if (check_row_walls(gmap->map_arr[last_row]))
		return (1);
	return (0);
}

static int	validate_middle_rows(t_gmap *gmap, int last_row)
{
	int	i;

	i = 1;
	while (i < last_row)
	{
		if (check_side_walls(gmap->map_arr[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	process_row_characters(t_gmap *gmap, int row, char *dir,
		int *spawn_count)
{
	int		j;
	char	c;

	j = -1;
	while (++j < gmap->map_width)
	{
		c = gmap->map_arr[row][j];
		if (!is_allowed(c))
			return (1);
		if (is_spawn(c))
		{
			if (++(*spawn_count) > 1)
				return (1);
			gmap->player_starting_x_pos = j;
			gmap->player_starting_y_pos = row;
			if (dir)
				*dir = c;
			gmap->map_arr[row][j] = '0';
		}
	}
	return (0);
}

static int	validate_characters_and_spawn(t_gmap *gmap, int last_row, char *dir)
{
	int	i;
	int	spawn_count;

	spawn_count = 0;
	i = -1;
	while (++i <= last_row)
	{
		if (process_row_characters(gmap, i, dir, &spawn_count))
			return (1);
	}
	return (spawn_count != 1);
}

int	check_borders(t_gmap *gmap, char *player_dir)
{
	int	last_row;

	last_row = get_last_valid_row(gmap);
	if (check_border_rows(gmap, last_row))
		return (1);
	if (validate_middle_rows(gmap, last_row))
		return (1);
	if (validate_characters_and_spawn(gmap, last_row, player_dir))
		return (1);
	return (0);
}
