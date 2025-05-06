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

static int	count_lines_in_file(const char *path)
{
	FILE	*fp;
	char	buffer[4096];
	int		count;

	count = 0;
	fp = fopen(path, "r");
	if (!fp)
		return (-1);
	while (fgets(buffer, sizeof(buffer), fp))
		count++;
	fclose(fp);
	return (count);
}

static int	copy_line_to_array(char *buffer, char **lines, int i)
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

static int	fill_lines_array(const char *path, char **lines)
{
	FILE	*fp;
	char	buffer[4096];
	int		i;

	i = 0;
	fp = fopen(path, "r");
	if (!fp)
		return (1);
	while (fgets(buffer, sizeof(buffer), fp))
	{
		if (copy_line_to_array(buffer, lines, i))
		{
			free_lines(lines, i);
			fclose(fp);
			return (1);
		}
		i++;
	}
	lines[i] = NULL;
	fclose(fp);
	return (0);
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
