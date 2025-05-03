#include "../include/cub3d.h"
#include <stdio.h>
#include <ctype.h>

static int parse_rgb(const char *str, int rgb[3])
{
    int i = 0;
    char *end;
    for (int c = 0; c < 3; c++) {
        while (str[i] && (str[i] == ' ' || str[i] == ','))
            i++;
        if (!str[i] || str[i] == '\n') { // missing value or newline before all 3
            return 1;
        }
        rgb[c] = strtol(&str[i], &end, 10);
        if (&str[i] == end || rgb[c] < 0 || rgb[c] > 255) {
            return 1;
        }
        i = end - str;
    }
    // After parsing 3 numbers, only allow whitespace or end of string
    while (str[i]) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            return 1;
        }
        i++;
    }
    return 0;
}

int extract_header_data(t_mapinfo *mapinfo, t_gmap *gmap, int *map_start_index)
{
    int i = 0;
    int no_found = 0, so_found = 0, we_found = 0, ea_found = 0;
    // Initialize color arrays to -1 to detect uninitialized/failed parsing
    for (int c = 0; c < 3; c++) {
        gmap->floor_color_rgb[c] = -1;
        gmap->ceiling_color_rgb[c] = -1;
    }
    while (i < mapinfo->line_count && mapinfo->file[i]) {
        char *line = mapinfo->file[i];
        while (*line == ' ' || *line == '\t') line++;
        if (isdigit((unsigned char)*line))
            break;
        if (strncmp(line, "NO ", 3) == 0) {
            if (no_found) {
                fprintf(stderr, "Error: Duplicate NO texture identifier found.\n");
                return 1;
            }
            no_found = 1;
            char *path = line + 3;
            while (*path == ' ' || *path == '\t') path++;
            char *end = path + strlen(path) - 1;
            while (end > path && (*end == ' ' || *end == '\t')) end--;
            *(end + 1) = '\0';
            gmap->n_wall_path_texture = ft_strdup(path);
        }
        else if (strncmp(line, "SO ", 3) == 0) {
            if (so_found) {
                fprintf(stderr, "Error: Duplicate SO texture identifier found.\n");
                return 1;
            }
            so_found = 1;
            char *path = line + 3;
            while (*path == ' ' || *path == '\t') path++;
            char *end = path + strlen(path) - 1;
            while (end > path && (*end == ' ' || *end == '\t')) end--;
            *(end + 1) = '\0';
            gmap->s_wall_path_texture = ft_strdup(path);
        }
        else if (strncmp(line, "WE ", 3) == 0) {
            if (we_found) {
                fprintf(stderr, "Error: Duplicate WE texture identifier found.\n");
                return 1;
            }
            we_found = 1;
            char *path = line + 3;
            while (*path == ' ' || *path == '\t') path++;
            char *end = path + strlen(path) - 1;
            while (end > path && (*end == ' ' || *end == '\t')) end--;
            *(end + 1) = '\0';
            gmap->w_wall_path_texture = ft_strdup(path);
        }
        else if (strncmp(line, "EA ", 3) == 0) {
            if (ea_found) {
                fprintf(stderr, "Error: Duplicate EA texture identifier found.\n");
                return 1;
            }
            ea_found = 1;
            char *path = line + 3;
            while (*path == ' ' || *path == '\t') path++;
            char *end = path + strlen(path) - 1;
            while (end > path && (*end == ' ' || *end == '\t')) end--;
            *(end + 1) = '\0';
            gmap->e_wall_path_texture = ft_strdup(path);
        }
        else if (strncmp(line, "F ", 2) == 0) {
            if (parse_rgb(line + 2, gmap->floor_color_rgb))
                return 1;
        }
        else if (strncmp(line, "C ", 2) == 0) {
            if (parse_rgb(line + 2, gmap->ceiling_color_rgb))
                return 1;
        }
        i++;
    }
    if (map_start_index)
        *map_start_index = i;
    // Ensure all four texture identifiers are present
    if (!no_found || !so_found || !we_found || !ea_found) {
        fprintf(stderr, "Error: One or more texture identifiers (NO, SO, WE, EA) are missing before the map data.\n");
        return 1;
    }
    return 0;
}
