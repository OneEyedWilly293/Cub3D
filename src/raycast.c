#include "../includes/game.h"

double	cast_ray(double ray_angle, t_game *game)
{
	int	hit;
	int	side;

	hit = 0;
	init_ray_struct(ray_angle, game);
	while (!hit)
	{
		if (game->ray.side_dist_x < game->ray.side_dist_y)
		{
			game->ray.side_dist_x += game->ray.delta_dist_x;
			game->ray.map_x += game->ray.step_x;
			side = 0;
		}
		else
		{
			game->ray.side_dist_y += game->ray.delta_dist_y;
			game->ray.map_y += game->ray.step_y;
			side = 1;
		}
		if (game->ray.map_y < 0 || game->ray.map_y >= GRIDY || game->ray.map_x < 0 || game->ray.map_x >= GRIDX)
			return (1000);
		if (game->map[game->ray.map_y * GRIDX + game->ray.map_x] == 1)
			hit = 1;
	}
	if (side == 0)
		return ((game->ray.map_x - game->player.x + (1 - game->ray.step_x) / 2) / game->ray.ray_dir_x);
	else
		return ((game->ray.map_y - game->player.y + (1 - game->ray.step_y) / 2) / game->ray.ray_dir_y);
}

void	init_ray_struct(double ray_angle, t_game *g)
{
	g->ray.map_x = (int)g->player.x;
	g->ray.map_y = (int)g->player.y;
	g->ray.ray_dir_x = cos(ray_angle);
	g->ray.ray_dir_y = sin(ray_angle);
	g->ray.delta_dist_x = fabs(1 / g->ray.ray_dir_x);
	g->ray.delta_dist_y = fabs(1 / g->ray.ray_dir_y);
	if (g->ray.ray_dir_x < 0)
		g->ray.step_x = -1;
	else
		g->ray.step_x = 1;
	if (g->ray.ray_dir_y < 0)
		g->ray.step_y = -1;
	else
		g->ray.step_y = 1;
	if (g->ray.step_x < 0)
		g->ray.side_dist_x = (g->player.x - g->ray.map_x) * g->ray.delta_dist_x;
	else
		g->ray.side_dist_x = (g->ray.map_x + 1.0 - g->player.x) * g->ray.delta_dist_x;
	if (g->ray.step_y < 0)
		g->ray.side_dist_y = (g->player.y - g->ray.map_y) * g->ray.delta_dist_y;
	else
		g->ray.side_dist_y = (g->ray.map_y + 1.0 - g->player.y) * g->ray.delta_dist_y;
}
