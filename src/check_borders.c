#include "../include/cub3d.h"
#include <string.h>

static int is_spawn(char c) {
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int is_allowed(char c) {
    return (c == '0' || c == '1' || is_spawn(c) || c == ' ' || c == '\t');
}

static int check_row_walls(const char *row) {
    int i = 0;
    // Skip leading spaces/tabs
    while (row[i] == ' ' || row[i] == '\t')
        i++;
    // All remaining must be '1', space, or tab
    for (; row[i]; i++) {
        if (row[i] != '1' && row[i] != ' ' && row[i] != '\t')
            return 1;
    }
    return 0;
}

static int check_side_walls(const char *row) {
    int left = 0, right = (int)strlen(row) - 1;
    // Find first non-space/tab
    while ((row[left] == ' ' || row[left] == '\t') && row[left])
        left++;
    // Find last non-space/tab
    while (right >= 0 && (row[right] == ' ' || row[right] == '\t'))
        right--;
    // printf("[DEBUG] check_side_walls: row='%s' | left=%d ('%c') | right=%d ('%c')\n", row, left, row[left], right, row[right]);
    if (left > right)
        return 1; // empty row
    if (row[left] != '1' || row[right] != '1')
        return 1;
    return 0;
}

int check_borders(t_gmap *gmap, int *player_x, int *player_y, char *player_dir)
{
    int spawn_count = 0;
    int i, j;
    int h = gmap->map_height;
    int w = gmap->map_width;

    // Find the last non-empty row (not all spaces/tabs)
    int last_row = h - 1;
    int found_nonempty = 0;
    for (; last_row >= 0; last_row--) {
        int only_whitespace = 1;
        for (j = 0; j < w; j++) {
            if (gmap->map_arr[last_row][j] != ' ' && gmap->map_arr[last_row][j] != '\t') {
                only_whitespace = 0;
                break;
            }
        }
        if (!only_whitespace) {
            found_nonempty = 1;
            break;
        }
    }
    if (!found_nonempty || last_row < 0)
        return 1; // No valid map rows

    // Top border
    if (check_row_walls(gmap->map_arr[0]))
        return 1;
    // Bottom border (last non-empty row)
    if (check_row_walls(gmap->map_arr[last_row]))
        return 1;
    // Middle rows
    for (i = 1; i < last_row; i++) {
        if (check_side_walls(gmap->map_arr[i]))
            return 1;
    }
    // Allowed characters and single player
    for (i = 0; i <= last_row; i++) {
        for (j = 0; j < w; j++) {
            char c = gmap->map_arr[i][j];
            if (!is_allowed(c))
                return 1;
            if (is_spawn(c)) {
                spawn_count++;
                if (spawn_count > 1)
                    return 1;
                if (player_x) *player_x = j;
                if (player_y) *player_y = i;
                if (player_dir) *player_dir = c;
                gmap->map_arr[i][j] = '0';
            }
        }
    }
    if (spawn_count != 1)
        return 1;
    return 0;
}
