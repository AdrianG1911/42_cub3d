/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:10:16 by jidler            #+#    #+#             */
/*   Updated: 2025/05/06 11:54:50 by jidler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int	is_directory(const char *path)
{
	int	descriptor;
	int	result;

	result = 0;
	descriptor = open(path, O_DIRECTORY);
	if (descriptor >= 0)
	{
		close(descriptor);
		result = 1;
	}
	return (result);
}

static int	has_cub_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (filename[len - 4] != '.')
		return (0);
	if (filename[len - 3] != 'c')
		return (0);
	if (filename[len - 2] != 'u')
		return (0);
	if (filename[len - 1] != 'b')
		return (0);
	return (1);
}

static int	has_xpm_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (filename[len - 4] != '.')
		return (0);
	if (filename[len - 3] != 'x')
		return (0);
	if (filename[len - 2] != 'p')
		return (0);
	if (filename[len - 1] != 'm')
		return (0);
	return (1);
}

int	check_file_type(const char *filepath, int expect_cub)
{
	int	fd;

	if (is_directory(filepath))
	{
		printf("%s: is a directory\n", filepath);
		return (1);
	}
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		perror(filepath);
		return (1);
	}
	close(fd);
	if (expect_cub && !has_cub_extension(filepath))
	{
		printf("%s: expected a .cub file\n", filepath);
		return (1);
	}
	if (!expect_cub && !has_xpm_extension(filepath))
	{
		printf("%s: expected a .xpm file\n", filepath);
		return (1);
	}
	return (0);
}
