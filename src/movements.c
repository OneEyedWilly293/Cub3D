#include "../includes/game.h"

void	up_down(t_game *game)
{
	double move_x;
	double move_y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		move_x = cos(game->player.da) * PLAYER_SPEED;
		move_y = sin(game->player.da) * PLAYER_SPEED;

		if (game->map[(int)(game->player.y + move_y) * GRIDX
				+ (int)(game->player.x + move_x)] == 0)
		{
			game->player.x += move_x;
			game->player.y += move_y;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		move_x = cos(game->player.da) * PLAYER_SPEED;
		move_y = sin(game->player.da) * PLAYER_SPEED;

		if (game->map[(int)(game->player.y - move_y) * GRIDX
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

	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		move_x = cos(game->player.da - M_PI_2) * PLAYER_SPEED;
		move_y = sin(game->player.da - M_PI_2) * PLAYER_SPEED;

		if (game->map[(int)(game->player.y + move_y) * GRIDX
				+ (int)(game->player.x + move_x)] == 0)
		{
			game->player.x += move_x;
			game->player.y += move_y;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		move_x = cos(game->player.da + M_PI_2) * PLAYER_SPEED;
		move_y = sin(game->player.da + M_PI_2) * PLAYER_SPEED;

		if (game->map[(int)(game->player.y + move_y) * GRIDX
				+ (int)(game->player.x + move_x)] == 0)
		{
			game->player.x += move_x;
			game->player.y += move_y;
		}
	}
}

void	horizontal_rotation(t_game *game)
{
	if(mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->player.da -= 0.05f;
	}
	if(mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->player.da += 0.05f;
	}
}

void	init_mouse(t_game *game)
{
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(game->mlx, mouse_hook, game);
}
