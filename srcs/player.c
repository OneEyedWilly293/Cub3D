#include "cub3d.h"

// Convert RGB to 32-bit integer
// int	ft_pixel(int r, int g, int b, int a) // use uint8_t
int	ft_pixel(t_color color) // use uint8_t
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | 0xFF);
}

// void	draw_player(t_game *game)
// {
// 	int	py;
// 	int	px;
// 	int	color;
//
// 	color = set_color(game, RED, TRANSPARENT);
// 	game->map2d.p_px = (int)(game->player.x * game->map2d.scale_x);
// 	game->map2d.p_py = (int)(game->player.y * game->map2d.scale_y);
// 	py = game->map2d.p_py - 2;
// 	while (py <= game->map2d.p_py + 2)
// 	{
// 		px = game->map2d.p_px - 2;
// 		while (px <= game->map2d.p_px + 2)
// 		{
// 			mlx_put_pixel(game->img_map, px, py, color);
// 			++px;
// 		}
// 		++py;
// 	}
// }

void	draw_player(t_game *game)
{
	int	x = MM_CENTER;
	int	y = MM_CENTER;

	mlx_put_pixel(game->img_map, x, y, GREEN);
}

int	set_color(t_game *game, int visible, int invisible)
{
	int	color;

	if(game->show_map == true)
	{
		color = visible;
	}
	else
		color = invisible;
	return (color);
}
