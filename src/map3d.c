#include "../includes/game.h"

void	draw_column(mlx_image_t *img, int x, int top, int bottom, uint32_t color)
{
	int	y;

	y = top;
	while (y <= bottom)
	{
		mlx_put_pixel(img, x, y, color);
		y++;
	}
}

void	draw_map3d(void *param)
{
	t_game	*game;
	double	ray_angle;
	double	dist;
	int		screen_w;
	int		screen_h;
	int		x;
	int		wall_height;
	int		wall_top;
	int		wall_bottom;

	x = 0;
	game = param;
	screen_w = game->img_3d->width;
	screen_h = game->img_3d->height;
	while (x < screen_w)
	{
		ray_angle = game->player.da - (double)FOV / 2 + ((double)x / screen_w) * FOV;
		dist = cast_ray(ray_angle, game);
		dist *= cos(ray_angle - game->player.da);
		if (dist < 0.01)
			dist = 0.01;
		wall_height = (int)((double)screen_h / dist);
		wall_top = (screen_h / 2) - (wall_height / 2);
		wall_bottom = wall_top + wall_height;
		if (wall_top < 0)
			wall_top = 0;
		if (wall_bottom >= screen_h)
			wall_bottom = screen_h - 1;
		draw_column(game->img_3d, x, wall_top, wall_bottom, 0x0000FFFF);
		x++;
	}
}

void	resize_callback(int32_t new_width, int32_t new_height, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (new_width <= 0 || new_height <= 0)
		return ;
	game->window_width = new_width;
	game->window_height = new_height;
	game->map_width = new_width / 2;
	game->map_height = new_height / 2;
	game->tile_size = (float)game->map_width / GRIDX;

	// create_img(game, &game->img_3d);
	if (game->img_3d)
		mlx_delete_image(game->mlx, game->img_3d);
	game->img_3d = mlx_new_image(game->mlx, new_width, new_height);
	draw_map3d(game);
	if (game->img_map)
		mlx_delete_image(game->mlx, game->img_map);
	mlx_image_to_window(game->mlx, game->img_3d, 0, 0);
	if (game->show_map == true)
	{
		clear_image(game->img_map, 0x000000FF);
		game->img_map = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
		mlx_image_to_window(game->mlx, game->img_map, 10, 10);
		draw_map2d(game);
	}
}
