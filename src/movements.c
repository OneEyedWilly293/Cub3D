#include "../includes/game.h"

void	up_down(t_game *game)
{
	double move_x;
	double move_y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		move_x = cos(game->player.da) * PLAYER_SPEED;
		move_y = sin(game->player.da) * PLAYER_SPEED;

		if (game->map[(int)(game->player.y + move_y) * MAPX
				+ (int)(game->player.x + move_x)] == 0)
		{
			game->player.x += move_x;
			game->player.y += move_y;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		move_x = cos(game->player.da) * PLAYER_SPEED;
		move_y = sin(game->player.da) * PLAYER_SPEED;

		if (game->map[(int)(game->player.y - move_y) * MAPX
				+ (int)(game->player.x - move_x)] == 0)
		{
			game->player.x -= move_x;
			game->player.y -= move_y;
		}
	}
}

void	left_right(t_game *game)
{
	double move_x;
	double move_y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		move_x = cos(game->player.da - M_PI_2) * PLAYER_SPEED;
		move_y = sin(game->player.da - M_PI_2) * PLAYER_SPEED;

		if (game->map[(int)(game->player.y + move_y) * MAPX
				+ (int)(game->player.x + move_x)] == 0)
		{
			game->player.x += move_x;
			game->player.y += move_y;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		move_x = cos(game->player.da + M_PI_2) * PLAYER_SPEED;
		move_y = sin(game->player.da + M_PI_2) * PLAYER_SPEED;

		if (game->map[(int)(game->player.y + move_y) * MAPX
				+ (int)(game->player.x + move_x)] == 0)
		{
			game->player.x += move_x;
			game->player.y += move_y;
		}
	}
}

void	horizontal_rotation(t_game *game)
{
	if(mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player.da -= 0.05f;
	}
	if(mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player.da += 0.05f;
	}
}

void	vertical_rotation(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->player.camera += CAMERA_SPEED;
		if (game->player.camera > MAX_CAMERA)
			game->player.camera = MAX_CAMERA;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player.camera -= CAMERA_SPEED;
		if (game->player.camera < -MAX_CAMERA)
			game->player.camera = -MAX_CAMERA;
	}

}

void	jump(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
	{
		if (!game->player.is_jumping)
		{
			game->player.is_jumping = 1;
			game->player.jump_velocity = JUMP_SPEED;
		}
	}
	if (game->player.is_jumping)
	{
		game->player.camera += game->player.jump_velocity;
		game->player.jump_velocity -= GRAVITY;
		if (game->player.camera <= 0)
		{
			game->player.camera = 0;
			game->player.is_jumping = 0;
			game->player.jump_velocity = 0;
		}
		if (game->player.camera > MAX_JUMP)
			game->player.camera = MAX_JUMP;
	}
}
