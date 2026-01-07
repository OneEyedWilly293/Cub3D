#include "../includes/game.h"

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_game *g = param;

	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		g->show_map = !g->show_map;
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
		g->mouse= !g->mouse;
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
void game_loop(void* param)
{
	t_game *game;

	game = (t_game *)param;
	if (game->img_3d)
		clear_image(game->img_3d, 0x000000FF);
	if (game->show_map == false)
		clear_image(game->img_map, 0x000000FF);
	render_background(game, game->window_width, game->window_height);
	ft_hook(game);
	drawMap3D(game);       
	if(game->show_map == true)
	{
		clear_image(game->img_map, 0x000000FF);
		game->img_map = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
		mlx_image_to_window(game->mlx, game->img_map, 10, 10);
		drawMap2D(game);       
	}
	if(game->mouse == true)
		init_mouse(game);
}

void mouse_hook(double xpos, double ypos, void *param)
{
	(void)		ypos;
	t_game		*game;
	double		delta_x;
	int			center_x;
	int			center_y;

	game = (t_game *)param;
	center_x = game->window_width / 2;
	center_y = game->window_height / 2;
	delta_x = xpos - center_x;
	game->player.da += delta_x * MOUSE_SENSITIVITY;
	if (game->player.da < 0)
		game->player.da += 2 * M_PI;
	else if (game->player.da > 2 * M_PI)
		game->player.da -= 2 * M_PI;
	game->player.dx = cos(game->player.da);
	game->player.dy = sin(game->player.da);
	mlx_set_mouse_pos(game->mlx, center_x, center_y);
}
