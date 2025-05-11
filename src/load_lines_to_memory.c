/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_lines_to_memory.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:00:00 by <yourlogin>       #+#    #+#             */
/*   Updated: 2025/05/11 13:21:37 by jidler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static int	process_newline_segments(char *buffer, ssize_t size, char **lines, int count, ssize_t *line_idx)
{
	ssize_t i = 0;
	ssize_t line_start = 0;
	while (i < size)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			if (*line_idx >= count)
				return (1);
			if (split_line_segment(&buffer[line_start], lines, line_idx, count))
				return (1);
			line_start = i + 1;
		}
		i++;
	}
	return line_start;
}

static int	split_buffer_to_lines(char *buffer, ssize_t size, char **lines,
		int count)
{
	ssize_t line_idx = 0;
	ssize_t line_start;

	line_start = process_newline_segments(buffer, size, lines, count, &line_idx);
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
