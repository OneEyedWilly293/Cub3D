#include "../includes/game.h"

void draw_column(mlx_image_t *img, int x, int top, int bottom, uint32_t color)
{
	int y;

	y = top;
	while(y <= bottom)
	{
		mlx_put_pixel(img, x, y, color);
		y++;
	}
}

void drawMap3D(void *param)
{
	t_game	*game;
	double	dist;
	int		wall_height;
	int		wall_top;
	int		wall_bottom;
	int		x;
	double	ray_angle;

	game = (t_game *)param;

	x = 0;
	while(x < game->map_width)
	{
		ray_angle = game->player.da - (double)FOV / 2 + x * (FOV / game->map_width);
		dist = cast_ray(ray_angle, game);
		// fisheye correction
		dist *= cos(ray_angle - game->player.da);

		// prevent extreme wall heights
		if (dist < 0.01)
			dist = 0.01;

		wall_height = ((double)game->map_height / dist);
		wall_top = (game->map_height / 2) - (wall_height / 2) + game->player.camera;
		wall_bottom = (game->map_height / 2) + (wall_height / 2) + game->player.camera;

		// clamp to screen
		if (wall_top < 0) wall_top = 0;
		if (wall_bottom >= game->map_height) wall_bottom = game->map_height - 1;

		draw_column(game->img_3d, x, wall_top, wall_bottom, 0x0000FFFF);
		x++;
	}
}

void resize_callback(int32_t new_width, int32_t new_height, void *param)
{
	t_game *game = (t_game *)param;

	game->window_width = new_width;
	game->window_height = new_height;

	// Scale map width and height
	game->map_width = new_width / 2;
	game->map_height = new_height / 2;

	// Update tile size
	game->tile_size = (float)game->map_width / MAPX;

	// Delete old images
	if (game->img_3d)
		mlx_delete_image(game->mlx, game->img_3d);
	if (game->img_map)
		mlx_delete_image(game->mlx, game->img_map);

	// Create new images
	game->img_3d = mlx_new_image(game->mlx, new_width, new_height);
	if(game->show_map == true)
	{
		game->img_map = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
		mlx_image_to_window(game->mlx, game->img_map, 0, 0);
		drawMap2D(game);       
	}
	mlx_image_to_window(game->mlx, game->img_3d, 0, 0);
	drawMap3D(game);       
}
