#include "../include/cub3d.h"

void	free_gmap(t_gmap *gmap)
{
	int	y;

	if (gmap->map_arr == NULL)
		return ;
	y = 0;
	while (y < gmap->map_height)
	{
		free(gmap->map_arr[y]);
		y++;
	}
	free(gmap->map_arr);
	free(gmap->e_wall_path_texture);
	free(gmap->n_wall_path_texture);
	free(gmap->s_wall_path_texture);
	free(gmap->w_wall_path_texture);
}

void	free_game(t_game *game)
{
	if (game->mlx != NULL)
	{
		if (game->render.north_wall_texture.img_ptr != NULL)
			mlx_destroy_image(game->mlx, \
				game->render.north_wall_texture.img_ptr);
		if (game->render.south_wall_texture.img_ptr != NULL)
			mlx_destroy_image(game->mlx, \
				game->render.south_wall_texture.img_ptr);
		if (game->render.east_wall_texture.img_ptr != NULL)
			mlx_destroy_image(game->mlx, \
				game->render.east_wall_texture.img_ptr);
		if (game->render.west_wall_texture.img_ptr != NULL)
			mlx_destroy_image(game->mlx, \
				game->render.west_wall_texture.img_ptr);
		if (game->render.image_buffer.img_ptr != NULL)
			mlx_destroy_image(game->mlx, game->render.image_buffer.img_ptr);
	}
	free_gmap(&game->gmap);
	if (game->mlx != NULL && game->win != NULL)
		mlx_destroy_window(game->mlx, game->win);
}
