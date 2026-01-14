#include "cub3d.h"

static int get_step(double dir)
{
	if (dir < 0)
		return (-1);
	return (1);
}

static double get_side_dist(t_game *game, bool is_x)
{
	double ret;

	ret = 0;
	if (is_x == true)
	{
		if (game->ray.step_x < 0)
		{
			ret = (game->player.x - game->ray.map_x) * game->ray.delta_dist_x;
			return (ret);
		}
		ret = (game->ray.map_x + 1.0 - game->player.x) * game->ray.delta_dist_x;
		return (ret);
	}
	if (game->ray.step_y < 0)
	{
		ret = (game->player.y - game->ray.map_y) * game->ray.delta_dist_y;
		return (ret);
	}
	ret = (game->ray.map_y + 1.0 - game->player.y) * game->ray.delta_dist_y;
	return (ret);
}

static void	init_ray_struct(double ray_angle, t_game *g)
{
	g->ray.map_x = (int)g->player.x;
	g->ray.map_y = (int)g->player.y;
	g->ray.ray_dir_x = cos(ray_angle);
	g->ray.ray_dir_y = sin(ray_angle);
	g->ray.delta_dist_x = fabs(1 / g->ray.ray_dir_x);
	g->ray.delta_dist_y = fabs(1 / g->ray.ray_dir_y);
	g->ray.step_x = get_step(g->ray.ray_dir_x);
	g->ray.step_y = get_step(g->ray.ray_dir_y);
	g->ray.side_dist_x = get_side_dist(g, true);
	g->ray.side_dist_y = get_side_dist(g, false);
}

static int perform_dda(t_game *game)
{
	int	hit;
	int	side;

	hit = 0;
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
		hit = is_wall(game, game->ray.map_x, game->ray.map_y);
	}
	return (side);
}

double	cast_ray(double ray_angle, t_game *game)
{
	int	side;
	double horizontal_ray;
	double vertical_ray;

	init_ray_struct(ray_angle, game);
	side = perform_dda(game);
	game->ray.side = side;

	vertical_ray = (game->ray.map_x - game->player.x + (1 - game->ray.step_x) * 0.5) / game->ray.ray_dir_x; 
	horizontal_ray = (game->ray.map_y - game->player.y + (1 - game->ray.step_y) * 0.5) / game->ray.ray_dir_y; 

	if (side == 0)
		return (vertical_ray);
	return (horizontal_ray);
}
