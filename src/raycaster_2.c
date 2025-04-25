/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:04:10 by adrgutie          #+#    #+#             */
/*   Updated: 2025/04/25 19:22:10 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calc_wall_face(t_rays *rays)
{
	if (rays->side == 0)
	{
		if (rays->ray_dir_x > 0)
			rays->wall_face_hit = 'W';
		else
			rays->wall_face_hit = 'E';
	}
	else
	{
		if (rays->ray_dir_y > 0)
			rays->wall_face_hit = 'N';
		else
			rays->wall_face_hit = 'S';
	}
}
