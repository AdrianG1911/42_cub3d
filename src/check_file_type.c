#include "../include/cub3d.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
**  Validates that the input is not a directory and has the correct file extension
*/

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
	if (filename[len - 4] == '.' && filename[len - 3] == 'c' && filename[len
		- 2] == 'u' && filename[len - 1] == 'b')
		return (1);
	return (0);
}

static int	has_xpm_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (filename[len - 4] == '.' && filename[len - 3] == 'x' && filename[len
		- 2] == 'p' && filename[len - 1] == 'm')
		return (1);
	return (0);
}

int	check_file_type(const char *filepath, int expect_cub)
{
	int	fd;

	if (is_directory(filepath))
	{
		fprintf(stderr, "%s: is a directory\n", filepath);
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
		fprintf(stderr, "%s: expected a .cub file\n", filepath);
		return (1);
	}
	if (!expect_cub && !has_xpm_extension(filepath))
	{
		fprintf(stderr, "%s: expected a .xpm file\n", filepath);
		return (1);
	}
	return (0);
}
