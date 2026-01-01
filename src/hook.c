#include "../includes/game.h"

// Handle key events
void ft_hook(void* param)
{
	t_game *game;

	game = (t_game *)param;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);

	double move_x;
	double move_y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		move_x = cos(game->player->da) * PLAYER_SPEED;
		move_y = sin(game->player->da) * PLAYER_SPEED;

		if (game->map[(int)(game->player->y + move_y) * MAPX
				+ (int)(game->player->x + move_x)] == 0)
		{
			game->player->x += move_x;
			game->player->y += move_y;
		}
	}

	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		move_x = cos(game->player->da) * PLAYER_SPEED;
		move_y = sin(game->player->da) * PLAYER_SPEED;

		if (game->map[(int)(game->player->y - move_y) * MAPX
				+ (int)(game->player->x - move_x)] == 0)
		{
			game->player->x -= move_x;
			game->player->y -= move_y;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		move_x = cos(game->player->da - M_PI_2) * PLAYER_SPEED;
		move_y = sin(game->player->da - M_PI_2) * PLAYER_SPEED;

		if (game->map[(int)(game->player->y + move_y) * MAPX
				+ (int)(game->player->x + move_x)] == 0)
		{
			game->player->x += move_x;
			game->player->y += move_y;
		}
	}

	/* STRAFE RIGHT */
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		move_x = cos(game->player->da + M_PI_2) * PLAYER_SPEED;
		move_y = sin(game->player->da + M_PI_2) * PLAYER_SPEED;

		if (game->map[(int)(game->player->y + move_y) * MAPX
				+ (int)(game->player->x + move_x)] == 0)
		{
			game->player->x += move_x;
			game->player->y += move_y;
		}
	}

	// Rotation
	if(mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player->da -= 0.05f;
	}
	if(mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player->da += 0.05f;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->player->camera += CAMERA_SPEED;
		if (game->player->camera > MAX_CAMERA)
			game->player->camera = MAX_CAMERA;
	}

	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player->camera -= CAMERA_SPEED;
		if (game->player->camera < -MAX_CAMERA)
			game->player->camera = -MAX_CAMERA;
	}

	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
	{
		if (!game->player->is_jumping)
		{
			game->player->is_jumping = 1;
			game->player->jump_velocity = JUMP_SPEED;
		}
	}
	if (game->player->is_jumping)
	{
		// Apply velocity
		game->player->camera += game->player->jump_velocity;

		// Apply gravity
		game->player->jump_velocity -= GRAVITY;

		// Check if player landed
		if (game->player->camera <= 0)
		{
			game->player->camera = 0;
			game->player->is_jumping = 0;
			game->player->jump_velocity = 0;
		}

		// Clamp to maximum jump
		if (game->player->camera > MAX_JUMP)
			game->player->camera = MAX_JUMP;
	}
}

void clear_image(mlx_image_t *img, uint32_t color, int width, int height)
{
	int	y;
	int x;

	y = 0;
	while(y < height)
	{
		x = 0;
		while(x < width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

// Update the game state
void update(void* param)
{
	t_game *game;

	game = (t_game *)param;

	clear_image(game->img_3d, 0x000000FF, WIN_W, WIN_H);
	clear_image(game->img_map, 0x000000FF, MINIMAP_SIZE, MINIMAP_SIZE);
	ft_hook(game);
	// drawPlayer(game);
	drawray(game);
	drawMap3D(game);       
	drawMap2D(game);       
}
