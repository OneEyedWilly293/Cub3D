#include "../includes/game.h"

void	render_background(t_game *game, int32_t new_width, int32_t new_height)
{
	size_t	x;
	size_t	y;
	// size_t width = game->window_width;
	//    size_t height = game->window_height;
	size_t width = new_width;
    size_t height = new_height;

	x = 0;
	// printf("width: %d height:%d\n", new_width, new_height);
	if (!game->img_3d)
		return;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			if (y < (height / 2))
				mlx_put_pixel(game->img_3d, x, y, DARK_SKY);
			else
				mlx_put_pixel(game->img_3d, x, y, GRASS);
			y++;
		}
		x++;
	}
}
