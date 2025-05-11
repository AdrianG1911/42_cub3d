/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_lines_to_memory_extra_helper.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 00:00:00 by jidler            #+#    #+#             */
/*   Updated: 2025/05/11 13:33:25 by jidler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	read_fd_to_buffer(int fd, char **out_buffer, ssize_t *out_size)
{
	char	*buffer;
	ssize_t	total;
	ssize_t	bytes_read;

	buffer = malloc(4096 * 1024);
	if (!buffer)
		return (1);
	total = 0;
	while (1)
	{
		bytes_read = read(fd, buffer + total, 4096);
		if (bytes_read <= 0)
			break ;
		total += bytes_read;
	}
	if (bytes_read < 0)
	{
		free(buffer);
		return (1);
	}
	*out_buffer = buffer;
	*out_size = total;
	return (0);
}

int	read_file_to_buffer(const char *path, char **out_buffer, ssize_t *out_size)
{
	int	fd;
	int	result;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	result = read_fd_to_buffer(fd, out_buffer, out_size);
	close(fd);
	return (result);
}
