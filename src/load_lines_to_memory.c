/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_lines_to_memory.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:00:00 by <yourlogin>       #+#    #+#             */
/*   Updated: 2025/05/06 10:56:46 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <fcntl.h>
#include <unistd.h>


static int read_file_to_buffer(const char *path, char **out_buffer, ssize_t *out_size)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0)
		return 1;
	char *buffer = malloc(4096 * 1024); // 4MB max file size
	if (!buffer)
	{
		close(fd);
		return 1;
	}
	ssize_t total = 0;
	ssize_t bytes_read;
	while ((bytes_read = read(fd, buffer + total, 4096)) > 0)
		total += bytes_read;
	close(fd);
	if (bytes_read < 0)
	{
		free(buffer);
		return 1;
	}
	*out_buffer = buffer;
	*out_size = total;
	return 0;
}

static int split_buffer_to_lines(char *buffer, ssize_t size, char **lines)
{
	ssize_t i = 0, line_start = 0, line_idx = 0;
	while (i < size)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			if (copy_line_to_array(&buffer[line_start], lines, line_idx))
			{
				free_lines(lines, line_idx);
				return 1;
			}
			line_idx++;
			line_start = i + 1;
		}
		i++;
	}
	if (line_start < size)
	{
		if (copy_line_to_array(&buffer[line_start], lines, line_idx))
		{
			free_lines(lines, line_idx);
			return 1;
		}
		line_idx++;
	}
	lines[line_idx] = NULL;
	return 0;
}

static int fill_lines_array(const char *path, char **lines)
{
	char *buffer = NULL;
	ssize_t size = 0;
	if (read_file_to_buffer(path, &buffer, &size))
		return 1;
	int result = split_buffer_to_lines(buffer, size, lines);
	free(buffer);
	return result;
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
	if (fill_lines_array(path, mapinfo->file))
		return (1);
	return (0);
}
