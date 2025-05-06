#include "../include/cub3d.h"
#include <stdio.h>

void	print_gmap(const t_gmap *gmap)
{
	printf("t_gmap struct contents:\n");
	printf("  n_wall_path_texture: %s\n", gmap->n_wall_path_texture);
	printf("  s_wall_path_texture: %s\n", gmap->s_wall_path_texture);
	printf("  w_wall_path_texture: %s\n", gmap->w_wall_path_texture);
	printf("  e_wall_path_texture: %s\n", gmap->e_wall_path_texture);
	printf("  floor_color_rgb: [%d, %d, %d]\n", gmap->floor_color_rgb[0],
		gmap->floor_color_rgb[1], gmap->floor_color_rgb[2]);
	printf("  ceiling_color_rgb: [%d, %d, %d]\n", gmap->ceiling_color_rgb[0],
		gmap->ceiling_color_rgb[1], gmap->ceiling_color_rgb[2]);
	printf("  player_starting_x_pos: %d\n", gmap->player_starting_x_pos);
	printf("  player_starting_y_pos: %d\n", gmap->player_starting_y_pos);
	printf("  player_starting_direciton: %c\n",
		gmap->player_starting_direciton);
	printf("  map_height: %d\n", gmap->map_height);
	printf("  map_width: %d\n", gmap->map_width);
	if (gmap->map_arr)
	{
		printf("  map_arr:\n");
		for (int i = 0; i < gmap->map_height; i++)
		{
			printf("    %s\n", gmap->map_arr[i]);
		}
	}
	else
	{
		printf("  map_arr: (null)\n");
	}
}

t_gmap	validate_map(char *path)
{
	t_mapinfo	map_data;
	t_gmap		gmap;
	int			map_start_index;
	char		player_dir;
	int			extract_result;

	if (check_file_type(path, 1) == 1)
	{
		printf("Error: Map file Type is not valid\n");
		exit(1);
	}
	if (load_lines_to_memory(path, &map_data))
	{
		printf("Error: Could not load lines to memory\n");
		exit(1);
	}
	map_start_index = find_map_start_index(&map_data);
	extract_result = extract_header_data(&map_data, &gmap, &map_start_index);
	if (extract_result)
	{
		printf("Error: Failed to extract header data\n");
		exit(1);
	}
	if (build_2d_grid(&map_data, &gmap, map_start_index))
	{
		printf("Error: Could not build 2D grid\n");
		exit(1);
	}
	print_gmap(&gmap);
	printf("Texture paths:\n");
	printf("  North: %s\n", gmap.n_wall_path_texture);
	printf("  South: %s\n", gmap.s_wall_path_texture);
	printf("  West:  %s\n", gmap.w_wall_path_texture);
	printf("  East:  %s\n", gmap.e_wall_path_texture);
	printf("Floor RGB: %d,%d,%d\n", gmap.floor_color_rgb[0],
		gmap.floor_color_rgb[1], gmap.floor_color_rgb[2]);
	printf("Ceiling RGB: %d,%d,%d\n", gmap.ceiling_color_rgb[0],
		gmap.ceiling_color_rgb[1], gmap.ceiling_color_rgb[2]);
	if (check_borders(&gmap, &player_dir) == 1)
	{
		printf("Error: Map borders are not valid\n");
		exit(1);
	}
	if (check_color_texture(&gmap) == 1)
	{
		printf("Error: Map colors or textures are not valid\n");
		exit(1);
	}
	gmap.player_starting_direciton = player_dir;
	free_lines(map_data.file, map_data.line_count);
	return (gmap);
}
