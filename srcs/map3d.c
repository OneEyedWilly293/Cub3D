#include "cub3d.h"

static int get_tex_x(t_game *game, mlx_texture_t *tex, double dist)
{
	double wall_x;
	int tex_x;

	if (game->ray.side == 0)
		wall_x = game->player.y + dist * game->ray.ray_dir_y;
	else
		wall_x = game->player.x + dist * game->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if ((game->ray.side == 0 && game->ray.step_x < 0) ||
			(game->ray.side == 1 && game->ray.step_y > 0))
		tex_x = tex->width - tex_x - 1;
	return tex_x;
}

static void	draw_textured_column(t_game *game, int x, int wall_top, int wall_bottom, double dist)
{
	mlx_texture_t *tex;
	int tex_x;
	int tex_y;
	int wall_height;
	int y;
	uint32_t color;
	uint8_t *p;

	tex = get_wall_texture(game);
	tex_x = get_tex_x(game, tex, dist);
	wall_height = wall_bottom - wall_top + 1;
	y = wall_top;
	while (y <= wall_bottom)
	{
		tex_y = ((y - wall_top) * tex->height) / wall_height;
		p = &tex->pixels[ (tex_y * tex->width + tex_x) * tex->bytes_per_pixel ];
		color = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
		mlx_put_pixel(game->img_3d, x, y, color);
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
		draw_textured_column(game, x, wall_top, wall_bottom, dist);
		x++;
	}
}

void	resize_callback(int new_width, int new_height, void *param)
{
	t_game *game = param;

	if (new_width <= 0 || new_height <= 0)
		return ;

	game->window_width = new_width;
	game->window_height = new_height;

	create_img(game, &game->img_3d, game->window_width, game->window_height);
	create_img(game, &game->img_map, MINIMAP_SIZE, MINIMAP_SIZE);
}
