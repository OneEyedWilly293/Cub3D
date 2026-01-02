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
		return (g->ray.map_x - g->player.x + (1 - g->ray.step_x) / 2) / g->ray.ray_dir_x;
	else
		return (g->ray.map_y - g->player.y + (1 - g->ray.step_y) / 2) / g->ray.ray_dir_y;
}

void	init_ray_struct(double ray_angle, t_game *g)
{
	g->ray.map_x = (int)g->player.x;
	g->ray.map_y = (int)g->player.y;
	g->ray.ray_dir_x = cos(ray_angle);
	g->ray.ray_dir_y = sin(ray_angle);
	g->ray.delta_dist_x = fabs(1 / g->ray.ray_dir_x);
	g->ray.delta_dist_y = fabs(1 / g->ray.ray_dir_y);
	g->ray.step_x = g->ray.ray_dir_x < 0 ? -1 : 1;
	g->ray.step_y = g->ray.ray_dir_y < 0 ? -1 : 1;
	g->ray.side_dist_x = (g->ray.step_x < 0 ? g->player.x - g->ray.map_x : g->ray.map_x + 1.0 - g->player.x) * g->ray.delta_dist_x;
	g->ray.side_dist_y = (g->ray.step_y < 0 ? g->player.y - g->ray.map_y : g->ray.map_y + 1.0 - g->player.y) * g->ray.delta_dist_y;

}
