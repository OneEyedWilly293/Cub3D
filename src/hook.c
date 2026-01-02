#include "../includes/game.h"

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_game *g = param;

	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		g->show_map = !g->show_map;
}

// Handle key events
void ft_hook(void* param)
{
	t_game *game;

	game = (t_game *)param;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);

	up_down(game);
	left_right(game);
	horizontal_rotation(game);
	vertical_rotation(game);
	jump(game);
}

void clear_image(mlx_image_t *img, uint32_t color, int width, int height)
{
	int	y;
	int x;

	y = 0;
	while(y < height)
	{
		x = 0;
		while(x < width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

// Update the game state
void update(void* param)
{
	t_game *game;

	game = (t_game *)param;

	clear_image(game->img_3d, 0x000000FF, game->map_width, game->map_height);
	clear_image(game->img_map, 0x000000FF, MINIMAP_SIZE, MINIMAP_SIZE);
	ft_hook(game);
	drawMap3D(game);       
	if(game->show_map == true)
		drawMap2D(game);       
}
