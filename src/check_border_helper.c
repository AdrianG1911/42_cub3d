/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:49:14 by jidler            #+#    #+#             */
/*   Updated: 2025/05/06 11:35:14 by jidler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <string.h>

int	is_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_allowed(char c)
{
	return (c == '0' || c == '1' || is_spawn(c) || c == ' ' || c == '\t');
}

int	check_row_walls(const char *row)
{
	int	i;

	i = 0;
	while (row[i] == ' ' || row[i] == '\t')
		i++;
	while (row[i])
	{
		if (row[i] != '1' && row[i] != ' ' && row[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int	check_side_walls(const char *row)
{
	int	left;
	int	right;

	left = 0;
	right = (int)ft_strlen(row) - 1;
	while (row[left] && (row[left] == ' ' || row[left] == '\t'))
		left++;
	while (right >= 0 && (row[right] == ' ' || row[right] == '\t'))
		right--;
	if (left > right)
		return (1);
	if (row[left] != '1' || row[right] != '1')
		return (1);
	return (0);
}

int	get_last_valid_row(t_gmap *gmap)
{
	int	last_row;
	int	j;
	int	only_whitespace;

	last_row = gmap->map_height - 1;
	while (last_row >= 0)
	{
		only_whitespace = 1;
		j = 0;
		while (j < gmap->map_width)
		{
			if (gmap->map_arr[last_row][j] != ' '
				&& gmap->map_arr[last_row][j] != '\t')
			{
				only_whitespace = 0;
				break ;
			}
			j++;
		}
		if (!only_whitespace)
			break ;
		last_row--;
	}
	return (last_row);
}
