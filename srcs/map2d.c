#include "cub3d.h"

static void	draw_minimap_background(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	color = set_color(game, BLACK, TRANSPARENT);
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			mlx_put_pixel(game->img_map, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_border(t_game *game)
{
	int	x;
	int	y;
	int	t;
	int	color;
	t = MM_BORDER_THICKNESS;


	color = set_color(game, BLACK, TRANSPARENT);
	/* Top & Bottom */
	y = 0;
	while (y < t)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			mlx_put_pixel(game->img_map, x, y, color);
			mlx_put_pixel(game->img_map, x, MINIMAP_SIZE - 1 - y, color);
			x++;
		}
		y++;
	}

	/* Left & Right */
	x = 0;
	while (x < t)
	{
		y = 0;
		while (y < MINIMAP_SIZE)
		{
			mlx_put_pixel(game->img_map, x, y, color);
			mlx_put_pixel(game->img_map, MINIMAP_SIZE - 1 - x, y, color);
			y++;
		}
		x++;
	}
}

static void	minimap_prepare_tile(int x, int y, t_game *game)
{
	double	cam_x;
	double	cam_y;
	double	rel_x;
	double	rel_y;

	cam_x = game->player.x;
	cam_y = game->player.y;
	game->map2d.tile = game->map[y][x];
	rel_x = (double)x - cam_x;
	rel_y = (double)y - cam_y;
	game->map2d.start_x = (int)(rel_x * game->map2d.scale_x + MM_CENTER);
	game->map2d.start_y = (int)(rel_y * game->map2d.scale_y + MM_CENTER);
	game->map2d.end_x   = (int)((rel_x + 1) * game->map2d.scale_x + MM_CENTER);
	game->map2d.end_y   = (int)((rel_y + 1) * game->map2d.scale_y + MM_CENTER);
}

static void	minimap_draw_tile(t_game *game)
{
	int	color;
	int	py;
	int	px;

	if (game->map2d.end_x < 0 || game->map2d.start_x >= MINIMAP_SIZE ||
			game->map2d.end_y < 0 || game->map2d.start_y >= MINIMAP_SIZE)
		return;
	if (game->show_map == true)
	{
		if (game->map2d.tile == '1')
			color = WHITE;
		else
			color = BLACK;
	}
	else
		color = TRANSPARENT;
	py = game->map2d.start_y;
	while (py < game->map2d.end_y)
	{
		if (py >= 0 && py < MINIMAP_SIZE)
		{
			px = game->map2d.start_x;
			while (px < game->map2d.end_x)
			{
				if (px >= 0 && px < MINIMAP_SIZE)
					mlx_put_pixel(game->img_map, px, py, color);
				px++;
			}
		}
		py++;
	}
}

static void	minimap_draw_ray(t_game *game)
{
	double	i;
	int		r;
	int		color;
	double	cam_x;
	double	cam_y;

	cam_x = game->player.x;
	cam_y = game->player.y;

	color = set_color(game, RED, TRANSPARENT);
	game->m_ray.start_angle = game->player.da - (double)FOV / 2;
	game->m_ray.angle_step = (double)FOV / NUM_RAYS;

	r = 0;
	while (r < NUM_RAYS)
	{
		game->m_ray.ray_angle = game->m_ray.start_angle + r * game->m_ray.angle_step;
		game->m_ray.ray_dist = cast_ray(game->m_ray.ray_angle, game);

		i = 0;
		while (i < game->m_ray.ray_dist)
		{
			double	rx = cam_x + cos(game->m_ray.ray_angle) * i;
			double	ry = cam_y + sin(game->m_ray.ray_angle) * i;

			double	rel_x = rx - cam_x;
			double	rel_y = ry - cam_y;

			int	px = (int)(rel_x * game->map2d.scale_x + MM_CENTER);
			int	py = (int)(rel_y * game->map2d.scale_y + MM_CENTER);

			if (px >= 0 && px < MINIMAP_SIZE && py >= 0 && py < MINIMAP_SIZE)
				mlx_put_pixel(game->img_map, px, py, color);

			i += 0.02;
		}
		r++;
	}
}

void	draw_minimap(void *param)
{
	t_game	*game;
	int		y;
	int		x;

	game = (t_game *)param;
	game->map2d.scale_x = (double)MINIMAP_SIZE / 20.0;
	game->map2d.scale_y = (double)MINIMAP_SIZE / 20.0;
	draw_minimap_background(game);
	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			minimap_prepare_tile(x, y, game);
			minimap_draw_tile(game);
			x++;
		}
		y++;
	}
	draw_player(game);
	minimap_draw_ray(game);
	draw_minimap_border(game);
}
