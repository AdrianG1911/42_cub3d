#include "../include/cub3d.h"
#include <stdio.h>

// Reads all lines from the file at 'path' into mapinfo->file, sets mapinfo->line_count.
// Returns 0 on success, 1 on error.
int load_lines_to_memory(const char *path, t_mapinfo *mapinfo)
{
    FILE *fp;
    char buffer[4096];
    int count = 0;
    int i = 0;

    // First pass: count lines
    fp = fopen(path, "r");
    if (!fp)
        return (1);
    while (fgets(buffer, sizeof(buffer), fp))
        count++;
    fclose(fp);
    if (count == 0)
        return (1);

    // Allocate array (+1 for NULL terminator)
    mapinfo->file = (char **)ft_calloc(count + 1, sizeof(char *));
    if (!mapinfo->file)
        return (1);
    mapinfo->line_count = count;

    // Second pass: fill array
    fp = fopen(path, "r");
    if (!fp)
        return (1);
    while (fgets(buffer, sizeof(buffer), fp))
    {
        size_t len = ft_strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
        mapinfo->file[i] = ft_strdup(buffer);
        if (!mapinfo->file[i])
        {
            // Free previously allocated lines
            for (int j = 0; j < i; j++)
                free(mapinfo->file[j]);
            free(mapinfo->file);
            fclose(fp);
            return (1);
        }
        i++;
    }
    mapinfo->file[i] = NULL;
    fclose(fp);
    return (0);
}
