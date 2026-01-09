
#include "cub3d.h"
// #include "../includes/game.h"

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

int get_texture(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.step_x > 0)
			return (BLUE);
		else
			return (GREEN);
	}
	else
	{
		if (game->ray.step_y > 0)
			return (RED);
		else
			return (WHITE);
	}
}

#if 0

static uint32_t	texture_to_rgb(mlx_texture_t *texture, int x, int y)
{
	uint8_t	*rgb;

	rgb = &texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel];
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | rgb[3]);
}

#endif
