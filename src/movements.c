#include "../includes/game.h"

void	up_down(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->player.move_x = cos(game->player.da) * PLAYER_SPEED;
		game->player.move_y = sin(game->player.da) * PLAYER_SPEED;
		if (game->map[(int)(game->player.y + game->player.move_y) * GRIDX
			+ (int)(game->player.x + game->player.move_x)] == 0)
		{
			game->player.x += game->player.move_x;
			game->player.y += game->player.move_y;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player.move_x = cos(game->player.da) * PLAYER_SPEED;
		game->player.move_y = sin(game->player.da) * PLAYER_SPEED;
		if (game->map[(int)(game->player.y - game->player.move_y) * GRIDX
			+ (int)(game->player.x - game->player.move_x)] == 0)
		{
			game->player.x -= game->player.move_x;
			game->player.y -= game->player.move_y;
		}
	}
}

void	left_right(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player.move_x = cos(game->player.da - M_PI_2) * PLAYER_SPEED;
		game->player.move_y = sin(game->player.da - M_PI_2) * PLAYER_SPEED;
		if (game->map[(int)(game->player.y + game->player.move_y) * GRIDX
			+ (int)(game->player.x + game->player.move_x)] == 0)
		{
			game->player.x += game->player.move_x;
			game->player.y += game->player.move_y;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player.move_x = cos(game->player.da + M_PI_2) * PLAYER_SPEED;
		game->player.move_y = sin(game->player.da + M_PI_2) * PLAYER_SPEED;
		if (game->map[(int)(game->player.y + game->player.move_y) * GRIDX
			+ (int)(game->player.x + game->player.move_x)] == 0)
		{
			game->player.x += game->player.move_x;
			game->player.y += game->player.move_y;
		}
	}
}

void	horizontal_rotation(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->player.da -= 0.05f;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->player.da += 0.05f;
	}
}

void	init_mouse(t_game *game)
{
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(game->mlx, mouse_hook, game);
}
