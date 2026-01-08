#include "../includes/game.h"

// Convert RGB to 32-bit integer
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a) // use uint8_t
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_player(t_game *game)
{
	int	py;
	int	px;

	game->map2d.p_px = (int)(game->player.x * game->map2d.scale_x);
	game->map2d.p_py = (int)(game->player.y * game->map2d.scale_y);
	py = game->map2d.p_py - 2;
	while (py <= game->map2d.p_py + 2)
	{
		px = game->map2d.p_px - 2;
		while (px <= game->map2d.p_px + 2)
		{
			mlx_put_pixel(game->img_map, px, py, RED);
			++px;
		}
		++py;
	}
}
