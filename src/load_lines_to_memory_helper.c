#include "../include/cub3d.h"
#include <fcntl.h>
#include <unistd.h>

void	free_lines(char **lines, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
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
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
	{
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
