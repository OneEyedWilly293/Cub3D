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

void clear_image(mlx_image_t *img, uint32_t color)
{
	uint32_t *p;
	int count;
	int i;

	p = (uint32_t *)img->pixels;
	count = img->width * img->height;
	i = 0;
	while(i < count)
	{
		p[i] = color;
		i++;
	}
}


// Update the game state
void update(void* param)
{
	t_game *game;

	game = (t_game *)param;

	clear_image(game->img_3d, 0x000000FF);
	clear_image(game->img_map, 0x000000FF);
	ft_hook(game);
	drawMap3D(game);       
	if(game->show_map == true)
		drawMap2D(game);       
}
