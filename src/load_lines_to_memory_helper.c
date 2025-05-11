/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_lines_to_memory_helper.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:49:05 by jidler            #+#    #+#             */
/*   Updated: 2025/05/11 13:21:54 by jidler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <fcntl.h>
#include <unistd.h>

int	split_line_segment(char *buffer, char **lines, ssize_t *line_idx,
		size_t line_start, int count)
{
	ssize_t	i;

	if (*line_idx >= count)
	{
		return (1);
	}
	if (copy_line_to_array(&buffer[line_start], lines, *line_idx))
	{
		free_lines(lines, *line_idx);
		{
			i = *line_idx;
			while (lines[i])
			{
				lines[i] = NULL;
				i++;
			}
		}
		return (1);
	}
	(*line_idx)++;
	return (0);
}

void	free_lines(char **lines, int count)
{
	int	j;

	if (!lines)
		return ;
	j = 0;
	while (j < count)
	{
		if (lines[j])
			free(lines[j]);
		j++;
	}
	free(lines);
}

int	count_lines_in_file(const char *path)
{
	int		fd;
	char	buffer[4096];
	ssize_t	bytes_read;
	int		count;
	int		i;

	count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (1)
	{
		bytes_read = read(fd, buffer, sizeof(buffer));
		if (bytes_read <= 0)
			break ;
		i = 0;
		while (i < bytes_read)
		{
			if (buffer[i] == '\n')
				count++;
			i++;
		}
	}
	close(fd);
	return (count);
}

int	copy_line_to_array(char *buffer, char **lines, int i)
{
	size_t	len;

	len = ft_strlen(buffer);
	if (len > 0 && buffer[len - 1] == '\n')
		buffer[len - 1] = '\0';
	lines[i] = ft_strdup(buffer);
	if (!lines[i])
		return (1);
	return (0);
}
