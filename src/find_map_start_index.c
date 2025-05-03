#include "../include/cub3d.h"
#include <ctype.h>

int find_map_start_index(t_mapinfo *mapinfo)
{
    int i = 0;
    while (i < mapinfo->line_count && mapinfo->file[i]) {
        char *line = mapinfo->file[i];
        while (*line == ' ' || *line == '\t')
            line++;
        if (isdigit((unsigned char)*line))
            return i;
        i++;
    }
    return -1;
}
