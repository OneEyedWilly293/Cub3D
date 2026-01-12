#include "cub3d.h"

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

// mlx_image_t *get_texture(t_game *game)
int	get_texture(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.step_x > 0)
		{
			// mlx_texture_t *blue = mlx_load_png(game->tex.ea);
			// mlx_image_t *ret = mlx_texture_to_image(game->mlx, blue);
			// return (ret); // east
			return (BLUE); // east
						   // return (game->tex.ea); // east
		}
		else
			return (GREEN); // west
	}
	else
	{
		if (game->ray.step_y > 0)
			return (RED); //south
		else
			return (WHITE); // north
	}
	// return(NULL);
}

#if 0

static uint32_t	texture_to_rgb(mlx_texture_t *texture, int x, int y)
{
	uint8_t	*rgb;

	rgb = &texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel];
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | rgb[3]);
}

#endif
