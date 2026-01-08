#include "../includes/game.h"

void	render_background(t_game *game, int32_t new_width, int32_t new_height)
{
	size_t	x;
	size_t	y;
	size_t	width;
	size_t	height;

	x = 0;
	width = new_width;
	height = new_height;
	if (!game->img_3d)
		return ;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			if (y < (height / 2))
				mlx_put_pixel(game->img_3d, x, y, DARK_SKY);
			else
				mlx_put_pixel(game->img_3d, x, y, GRASS);
			y++;
		}
		x++;
	}
}

#if 0

static uint32_t	texture_to_rgb(mlx_texture_t *texture, int x, int y)
{
	uint8_t	*rgb;

	rgb = &texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel];
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | rgb[3]);
}

static mlx_texture_t	*get_wall(t_game *game, t_raycast *raycast)
{
	if (raycast->is_horizontal)
	{
		if (raycast->ray_angle > PI && raycast->ray_angle < PI_360)
			return (game->no_text);
		else
			return (game->so_text);
	}
	else
	{
		if (raycast->ray_angle < PI_90 || raycast->ray_angle > PI_270)
			return (game->ea_text);
		else
			return (game->we_text);
	}
}

#endif
