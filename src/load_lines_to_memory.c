/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_lines_to_memory.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:00:00 by <yourlogin>       #+#    #+#             */
/*   Updated: 2025/05/11 13:37:12 by jidler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int	process_newline_segments(char *buffer, ssize_t size, char **lines, int count)
{
	ssize_t i;
	ssize_t line_start;
	ssize_t line_idx;

	i = 0;
	line_start = 0;
	line_idx = 0;
	while (i < size)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			if (line_idx >= count)
				return (-1);
			if (split_line_segment(&buffer[line_start], lines, &line_idx, count))
				return (-1);
			line_start = i + 1;
		}
		i++;
	}
	return (int)line_start | ((int)line_idx << 16);
}

static int	split_buffer_to_lines(char *buffer, ssize_t size, char **lines,
		int count)
{
	ssize_t line_idx;
	ssize_t line_start;
	int packed;

	packed = process_newline_segments(buffer, size, lines, count);
	line_start = (ssize_t)(packed & 0xFFFF);
	line_idx = (ssize_t)((packed >> 16) & 0xFFFF);
	if (line_start < size)
	{
		if (line_idx >= count)
			return (1);
		if (split_line_segment(&buffer[line_start], lines, &line_idx, count))
			return (1);
	}
	if (line_idx < count)
		lines[line_idx] = NULL;
	return (0);
}

static int	fill_lines_array(const char *path, char **lines, int count)
{
	char	*buffer;
	ssize_t	size;
	int		result;

	buffer = NULL;
	size = 0;
	if (read_file_to_buffer(path, &buffer, &size))
		return (1);
	result = split_buffer_to_lines(buffer, size, lines, count);
	free(buffer);
	return (result);
}

int	load_lines_to_memory(const char *path, t_mapinfo *mapinfo)
{
	int	count;

	count = count_lines_in_file(path);
	if (count <= 0)
		return (1);
	mapinfo->file = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!mapinfo->file)
		return (1);
	mapinfo->line_count = count;
	if (fill_lines_array(path, mapinfo->file, count))
	{
		free_lines(mapinfo->file, mapinfo->line_count);
		mapinfo->file = NULL;
		return (1);
	}
	return (0);
}
