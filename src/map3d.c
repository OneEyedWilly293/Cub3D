#include "../includes/game.h"

double cast_ray(double ray_angle, t_game *g)
{
	int hit = 0;
	int side;

	init_ray_struct(ray_angle, g);
	while (!hit)
	{
		if (g->ray.side_dist_x < g->ray.side_dist_y)
		{
			g->ray.side_dist_x += g->ray.delta_dist_x;
			g->ray.map_x += g->ray.step_x;
			side = 0;
		}
		else
		{
			g->ray.side_dist_y += g->ray.delta_dist_y;
			g->ray.map_y += g->ray.step_y;
			side = 1;
		}

		if (g->ray.map_y < 0 || g->ray.map_y >= MAPY || g->ray.map_x < 0 || g->ray.map_x >= MAPX)
			return 1000; // far away to prevent crash

		if (g->map[g->ray.map_y * MAPX + g->ray.map_x] == 1)
			hit = 1;
	}

	if (side == 0)
		return (g->ray.map_x - g->player->x + (1 - g->ray.step_x) / 2) / g->ray.ray_dir_x;
	else
		return (g->ray.map_y - g->player->y + (1 - g->ray.step_y) / 2) / g->ray.ray_dir_y;
}

void	init_ray_struct(double ray_angle, t_game *g)
{
	g->ray.map_x = (int)g->player->x;
	g->ray.map_y = (int)g->player->y;
	g->ray.ray_dir_x = cos(ray_angle);
	g->ray.ray_dir_y = sin(ray_angle);
	g->ray.delta_dist_x = fabs(1 / g->ray.ray_dir_x);
	g->ray.delta_dist_y = fabs(1 / g->ray.ray_dir_y);
	g->ray.step_x = g->ray.ray_dir_x < 0 ? -1 : 1;
	g->ray.step_y = g->ray.ray_dir_y < 0 ? -1 : 1;
	g->ray.side_dist_x = (g->ray.step_x < 0 ? g->player->x - g->ray.map_x : g->ray.map_x + 1.0 - g->player->x) * g->ray.delta_dist_x;
	g->ray.side_dist_y = (g->ray.step_y < 0 ? g->player->y - g->ray.map_y : g->ray.map_y + 1.0 - g->player->y) * g->ray.delta_dist_y;

}

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
		ray_angle = game->player->da - (double)FOV / 2 + x * (FOV / game->map_width);
		dist = cast_ray(ray_angle, game);
		// fisheye correction
		dist *= cos(ray_angle - game->player->da);

		// prevent extreme wall heights
		if (dist < 0.01)
			dist = 0.01;

		wall_height = ((double)game->map_height / dist);
		wall_top = (game->map_height / 2) - (wall_height / 2) + game->player->camera;
		wall_bottom = (game->map_height / 2) + (wall_height / 2) + game->player->camera;

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
