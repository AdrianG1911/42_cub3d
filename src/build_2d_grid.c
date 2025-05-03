#include "../include/cub3d.h"
#include <stdlib.h>
#include <string.h>

int build_2d_grid(t_mapinfo *mapinfo, t_gmap *gmap, int map_start_index)
{
    int i, j;
    int map_height = mapinfo->line_count - map_start_index;
    int map_width = 0;

    // Find the longest line (map_width)
    for (i = map_start_index; i < mapinfo->line_count; i++) {
        int len = (int)ft_strlen(mapinfo->file[i]);
        if (len > map_width)
            map_width = len;
    }
    gmap->map_height = map_height;
    gmap->map_width = map_width;

    // Allocate map_arr
    gmap->map_arr = (char **)ft_calloc(map_height + 1, sizeof(char *));
    if (!gmap->map_arr)
        return 1;

    // Copy and pad each line
    for (i = 0; i < map_height; i++) {
        gmap->map_arr[i] = (char *)ft_calloc(map_width + 1, sizeof(char));
        if (!gmap->map_arr[i]) {
            // Free previously allocated rows
            for (j = 0; j < i; j++)
                free(gmap->map_arr[j]);
            free(gmap->map_arr);
            return 1;
        }
        int line_len = (int)ft_strlen(mapinfo->file[map_start_index + i]);
        for (j = 0; j < map_width; j++) {
            if (j < line_len)
                gmap->map_arr[i][j] = mapinfo->file[map_start_index + i][j];
            else
                gmap->map_arr[i][j] = ' ';
        }
        gmap->map_arr[i][map_width] = '\0';
    }
    gmap->map_arr[map_height] = NULL;
    return 0;
}
