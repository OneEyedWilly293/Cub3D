#include "../includes/game.h"

static	void	update_map2d(int x, int y, t_game *game)
{
	game->map2d.tile = game->map[y * GRIDX + x];
	game->map2d.start_x = (int)(x * game->map2d.scale_x);
	game->map2d.start_y = (int)(y * game->map2d.scale_y);
	game->map2d.end_x = (int)((x + 1) * game->map2d.scale_x);
	game->map2d.end_y = (int)((y + 1) * game->map2d.scale_y);
}

// Draw the map
void	draw_map2d(void *param)
{
	t_game	*game;
	int		y;
	int		x;

	game = (t_game *)param;
	game->map2d.scale_x = (double)MINIMAP_SIZE / (double)GRIDX;
	game->map2d.scale_y = (double)MINIMAP_SIZE / (double)GRIDY;
	y = 0;
	while (y < GRIDY)
	{
		x = 0;
		while (x < GRIDX)
		{
			update_map2d(x, y, game);
			draw_map2d_map(game);
			++x;
		}
		++y;
	}
	draw_player(game);
	draw_ray_minimap(game);
}

void	draw_map2d_map(t_game *game)
{
	int	color;
	int	py;
	int	px;

	if(game->show_map == true)
	{
	if (game->map2d.tile == 1)
		color = WHITE;
	else
		color = BLACK;
	}
	else
		color = TRANSPARENT;
	py = game->map2d.start_y;
	while (py < game->map2d.end_y)
	{
		px = game->map2d.start_x;
		while (px < game->map2d.end_x)
		{
			mlx_put_pixel(game->img_map, px, py, color);
			++px;
		}
		++py;
	}
}

void	draw_ray_minimap(t_game *game)
{
	double	i;
	int		r;
	int		color;

	color = set_color(game, RED, TRANSPARENT);
	game->m_ray.start_angle = game->player.da - (double)FOV / 2 * (FOV / game->map_width) - (FOV / 2);
	game->m_ray.angle_step = FOV / NUM_RAYS;
	r = 0;
	while (r < NUM_RAYS)
	{
		game->m_ray.ray_angle = game->m_ray.start_angle + r * game->m_ray.angle_step;
		game->m_ray.ray_dist = cast_ray(game->m_ray.ray_angle, game);
		game->m_ray.x = game->player.x;
		game->m_ray.y = game->player.y;
		i = 0;
		while (i < game->m_ray.ray_dist)
		{
			game->m_ray.rx = game->m_ray.x + cos(game->m_ray.ray_angle) * i;
			game->m_ray.ry = game->m_ray.y + sin(game->m_ray.ray_angle) * i;
			game->m_ray.px = (int)(game->m_ray.rx * game->map2d.scale_x);
			game->m_ray.py = (int)(game->m_ray.ry * game->map2d.scale_y);
			if (game->m_ray.px >= 0 && game->m_ray.px < MINIMAP_SIZE && game->m_ray.py >= 0 && game->m_ray.py < MINIMAP_SIZE)
				mlx_put_pixel(game->img_map, game->m_ray.px, game->m_ray.py, color);
			i += 0.02;
		}
		r++;
	}
}
