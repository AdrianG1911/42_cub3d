#include "../include/cub3d.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

static int check_texture_path(const char *path) {
    if (!path || strlen(path) == 0) {
        fprintf(stderr, "Error: Texture path is empty.\n");
        return 1;
    }
    // Check for .xpm extension
    size_t len = strlen(path);
    if (len < 4 || strcmp(path + len - 4, ".xpm") != 0) {
        fprintf(stderr, "Error: Texture path '%s' does not end with .xpm\n", path);
        return 1;
    }
    // Check if path is a directory
    int dir_fd = open(path, O_DIRECTORY);
    if (dir_fd >= 0) {
        close(dir_fd);
        fprintf(stderr, "Error: Texture path '%s' is a directory.\n", path);
        return 1;
    }
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        // Try ../textures/ if path starts with "textures/"
        if (strncmp(path, "textures/", 9) == 0) {
            char alt_path[PATH_MAX];
            snprintf(alt_path, sizeof(alt_path), "../%s", path);
            fd = open(alt_path, O_RDONLY);
            if (fd < 0) {
                return 1;
            }
            close(fd);
            return 0;
        }
        return 1;
    }
    close(fd);
    return 0;
}

static int check_rgb(int rgb[3]) {
    for (int i = 0; i < 3; i++) {
        if (rgb[i] == -1 || rgb[i] < 0 || rgb[i] > 255)
            return 1;
    }
    return 0;
}

int check_color_texture(t_gmap *gmap)
{
    // Check for missing texture paths
    if (!gmap->n_wall_path_texture) {
        fprintf(stderr, "Error: North wall texture path is missing (gmap->n_wall_path_texture is NULL)\n");
        return 1;
    }
    if (!gmap->s_wall_path_texture) {
        fprintf(stderr, "Error: South wall texture path is missing (gmap->s_wall_path_texture is NULL)\n");
        return 1;
    }
    if (!gmap->w_wall_path_texture) {
        fprintf(stderr, "Error: West wall texture path is missing (gmap->w_wall_path_texture is NULL)\n");
        return 1;
    }
    if (!gmap->e_wall_path_texture) {
        fprintf(stderr, "Error: East wall texture path is missing (gmap->e_wall_path_texture is NULL)\n");
        return 1;
    }

    // Check that each texture file is valid
    if (check_texture_path(gmap->n_wall_path_texture)) {
        fprintf(stderr, "Error: Invalid north wall texture path: \"%s\"\n",
                gmap->n_wall_path_texture);
        return 1;
    }
    if (check_texture_path(gmap->s_wall_path_texture)) {
        fprintf(stderr, "Error: Invalid south wall texture path: \"%s\"\n",
                gmap->s_wall_path_texture);
        return 1;
    }
    if (check_texture_path(gmap->w_wall_path_texture)) {
        fprintf(stderr, "Error: Invalid west wall texture path: \"%s\"\n",
                gmap->w_wall_path_texture);
        return 1;
    }
    if (check_texture_path(gmap->e_wall_path_texture)) {
        fprintf(stderr, "Error: Invalid east wall texture path: \"%s\"\n",
                gmap->e_wall_path_texture);
        return 1;
    }

    // Check RGB ranges for floor and ceiling
    if (check_rgb(gmap->floor_color_rgb)) {
        int r = gmap->floor_color_rgb[0],
            g = gmap->floor_color_rgb[1],
            b = gmap->floor_color_rgb[2];
        fprintf(stderr,
                "Error: Floor color RGB out of range: (%d, %d, %d). "
                "Each component must be 0–255.\n",
                r, g, b);
        return 1;
    }
    if (check_rgb(gmap->ceiling_color_rgb)) {
        int r = gmap->ceiling_color_rgb[0],
            g = gmap->ceiling_color_rgb[1],
            b = gmap->ceiling_color_rgb[2];
        fprintf(stderr,
                "Error: Ceiling color RGB out of range: (%d, %d, %d). "
                "Each component must be 0–255.\n",
                r, g, b);
        return 1;
    }

    return 0;
}
