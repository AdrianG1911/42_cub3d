#include "../include/cub3d.h"
#include <math.h>

void init_player_from_spawn(t_player *player, int row, int col, char dir)
{
    player->x_pos = (double)col + 0.5;
    player->y_pos = (double)row + 0.5;
    if (dir == 'N')
        player->direction_radians = M_PI_2; // pi/2
    else if (dir == 'S')
        player->direction_radians = 3 * M_PI_2; // 3pi/2
    else if (dir == 'E')
        player->direction_radians = 0;
    else if (dir == 'W')
        player->direction_radians = M_PI;
    update_step_sizes(player);
}
