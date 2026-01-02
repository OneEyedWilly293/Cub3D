#include "../includes/game.h"

// Draw the map
void drawMap2D(void *param)
{
	t_game *game;
	int	y;
	int	x;

	game = (t_game *)param;
	game->map2d.scale_x = (double)MINIMAP_SIZE / (double)MAPX;
	game->map2d.scale_y = (double)MINIMAP_SIZE / (double)MAPY;
	y = 0;
	while(y < MAPY)
	{
		x = 0;
		while(x < MAPX)
		{
			game->map2d.tile = game->map[y * MAPX + x];
			game->map2d.start_x = (int)(x * game->map2d.scale_x);
			game->map2d.start_y = (int)(y * game->map2d.scale_y);
			game->map2d.end_x = (int)((x + 1) * game->map2d.scale_x);
			game->map2d.end_y = (int)((y + 1) * game->map2d.scale_y);
			drawMap2d_map(game);
			// draw_border(game);
			++x;
		}
		++y;
	}
	draw_player(game);
	draw_ray_minimap(game);
}

void	drawMap2d_map(t_game *game)
{
	int color;
	int	py;
	int	px;

	if(game->map2d.tile == 1)
		color = ft_pixel(WHITE);
	else
		color = ft_pixel(BLACK);
	py = game->map2d.start_y;
	while(py < game->map2d.end_y)
	{
		px = game->map2d.start_x;
		while(px < game->map2d.end_x)
		{
			mlx_put_pixel(game->img_map, px, py, color);
			++px;
		}
		++py;
	}
}

// void	draw_border(t_game *game)
// {
// 	int border_color = (game->map2d.tile == 1) ? ft_pixel(BLACK) : ft_pixel(WHITE);
//
// 	for (int px = game->map2d.start_x; px < game->map2d.end_x; ++px)
// 	{
// 		mlx_put_pixel(game->img_map, px, game->map2d.start_y, border_color);
// 		mlx_put_pixel(game->img_map, px, game->map2d.end_y - 1, border_color);
// 	}
// 	for (int py = game->map2d.start_y; py < game->map2d.end_y; ++py)
// 	{
// 		mlx_put_pixel(game->img_map, game->map2d.start_x, py, border_color);
// 		mlx_put_pixel(game->img_map, game->map2d.end_x - 1, py, border_color);
// 	}
// }

void draw_ray_minimap(t_game *game)
{
	double	start_angle;
	double	angle_step;
	double	ray_angle;
	double	ray_dist;
	double	x;
	double	y;
	double	rx;
	double	ry;
	double	px;
	double	py;
	double	i;
	int		r;

	start_angle = game->player.da - (double)FOV / 2 * (FOV / game->map_width) - (FOV / 2);
	angle_step = FOV / NUM_RAYS;
	r = 0;

	while(r < NUM_RAYS)
	{
		ray_angle = start_angle + r * angle_step;
		ray_dist = cast_ray(ray_angle, game);

		x = game->player.x;
		y = game->player.y;
		i = 0;
		while(i < ray_dist)
		{
			rx = x + cos(ray_angle) * i;
			ry = y + sin(ray_angle) * i;

			px = (int)(rx * game->map2d.scale_x);
			py = (int)(ry * game->map2d.scale_y);

			if (px >= 0 && px < MINIMAP_SIZE && py >= 0 && py < MINIMAP_SIZE)
				mlx_put_pixel(game->img_map, px, py, ft_pixel(RED));
			i += 0.02;
		}
		r++;
	}
}
