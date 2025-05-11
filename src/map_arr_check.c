/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_arr_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:35:36 by adrgutie          #+#    #+#             */
/*   Updated: 2025/05/11 22:25:41 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#define VISITED 1

int	is_out_of_bounds(int p_x, int p_y, t_gmap *gmap)
{
	if (p_x < 0 || p_y < 0)
		return (1);
	if (p_x >= gmap->map_width)
		return (1);
	if (p_y >= gmap->map_height)
		return (1);
	return (0);
}

void	turn_back(t_gmap *gmap)
{
	int		y;
	int		x;
	char	*tile;

	y = 0;
	x = 0;
	while (y < gmap->map_height)
	{
		x = 0;
		while (x < gmap->map_width)
		{
			tile = gmap->map_arr[y] + x;
			if (*tile == VISITED)
				*tile = '0';
			x++;
		}
		y++;
	}
}

void	print_map(t_gmap *gmap)
{
	int	y;
	int	x;

	y = 0;
	while (y < gmap->map_height)
	{
		x = 0;
		while (x < gmap->map_width)
		{
			if (gmap->map_arr[y][x] == ' ')
				printf("H");
			else
				printf("%c", gmap->map_arr[y][x]);
			x++;
		}
		y++;
		printf("\n");
	}
}

int	flood_fill(int p_x, int p_y, int *fail, t_gmap *gmap)
{
	char	*tile;

	if (is_out_of_bounds(p_x, p_y, gmap) == 1)
	{
		*fail = 1;
		return (0);
	}
	tile = gmap->map_arr[p_y] + p_x;
	if (*tile != '0' && *tile != '1' && *tile != VISITED)
		*fail = 1;
	if (*tile == '1' || *tile == VISITED)
		return (0);
	if (*tile != '1')
		*tile = VISITED;
	flood_fill(p_x + 1, p_y + 1, fail, gmap);
	flood_fill(p_x + 1, p_y - 1, fail, gmap);
	flood_fill(p_x + 1, p_y, fail, gmap);
	flood_fill(p_x, p_y + 1, fail, gmap);
	flood_fill(p_x, p_y - 1, fail, gmap);
	flood_fill(p_x - 1, p_y + 1, fail, gmap);
	flood_fill(p_x - 1, p_y - 1, fail, gmap);
	flood_fill(p_x - 1, p_y, fail, gmap);
	return (0);
}

int	flood_check(t_gmap *gmap)
{
	int	fail;

	fail = 0;
	flood_fill(gmap->player_starting_x_pos, \
		gmap->player_starting_y_pos, &fail, gmap);
	if (fail == 1)
		return (1);
	turn_back(gmap);
	return (0);
}
