#include "../includes/game.h"

void	draw_border(t_game *game);
void	draw_player(t_game *game);
void draw_ray_minimap(t_game *g);

// Convert RGB to 32-bit integer
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a) // use uint8_t
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// Draw the map
void drawMap2D(void *param)
{
	t_game *game;

	game = (t_game *)param;
	game->map2d.scale_x = (double)MINIMAP_SIZE / (double)MAPX;
	game->map2d.scale_y = (double)MINIMAP_SIZE / (double)MAPY;
	// int x, y;
	for (int y = 0; y < MAPY; ++y)
	{
		for (int x = 0; x < MAPX; ++x)
		{
			game->map2d.tile = game->map[y * MAPX + x];
			int color = (game->map2d.tile == 1) ? ft_pixel(WHITE) : ft_pixel(BLACK);

			game->map2d.start_x = (int)(x * game->map2d.scale_x);
			game->map2d.start_y = (int)(y * game->map2d.scale_y);
			game->map2d.end_x = (int)((x + 1) * game->map2d.scale_x);
			game->map2d.end_y = (int)((y + 1) * game->map2d.scale_y);

			for (int py = game->map2d.start_y; py < game->map2d.end_y; ++py)
			{
				for (int px = game->map2d.start_x; px < game->map2d.end_x; ++px)
				{
					mlx_put_pixel(game->img_map, px, py, color);
				}
			}
			// draw_border(game);
		}
	}
	draw_player(game);
	draw_ray_minimap(game);
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

void	draw_player(t_game *game)
{
	// draw player on top
	game->map2d.p_px = (int)(game->player->x * game->map2d.scale_x);
	game->map2d.p_py = (int)(game->player->y * game->map2d.scale_y);

	for (int py = game->map2d.p_py - 2; py <= game->map2d.p_py + 2; ++py)
		for (int px = game->map2d.p_px - 2; px <= game->map2d.p_px + 2; ++px)
			mlx_put_pixel(game->img_map, px, py, ft_pixel(RED));
}

void draw_ray_minimap(t_game *g)
{
    double start_angle;
    double angle_step;

	start_angle = g->player->da - (double)FOV / 2 * (FOV / g->map_width) - (FOV / 2);
    angle_step = FOV / NUM_RAYS;

    for (int r = 0; r < NUM_RAYS; r++)
    {
        double ray_angle = start_angle + r * angle_step;
        double ray_dist = cast_ray(ray_angle, g);

        // Map-space ray marching
        double x = g->player->x;
        double y = g->player->y;

        for (double i = 0; i < ray_dist; i += 0.02)
        {
            double rx = x + cos(ray_angle) * i;
            double ry = y + sin(ray_angle) * i;

            int px = (int)(rx * g->map2d.scale_x);
            int py = (int)(ry * g->map2d.scale_y);

            if (px >= 0 && px < MINIMAP_SIZE && py >= 0 && py < MINIMAP_SIZE)
                mlx_put_pixel(g->img_map, px, py, ft_pixel(RED));
        }
    }
}

