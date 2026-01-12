#include "cub3d.h"

void	up_down(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->player.move_x = cos(game->player.da) * PLAYER_SPEED;
		game->player.move_y = sin(game->player.da) * PLAYER_SPEED;
		if (game->map[(int)(game->player.y + game->player.move_y)][(int)(game->player.x + game->player.move_x)] == '0')
		{
			game->player.x += game->player.move_x;
			game->player.y += game->player.move_y;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player.move_x = cos(game->player.da) * PLAYER_SPEED;
		game->player.move_y = sin(game->player.da) * PLAYER_SPEED;
		if (game->map[(int)(game->player.y - game->player.move_y)][(int)(game->player.x - game->player.move_x)] == '0')
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
		if (game->map[(int)(game->player.y + game->player.move_y)][(int)(game->player.x + game->player.move_x)] == '0')
		{
			game->player.x += game->player.move_x;
			game->player.y += game->player.move_y;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player.move_x = cos(game->player.da + M_PI_2) * PLAYER_SPEED;
		game->player.move_y = sin(game->player.da + M_PI_2) * PLAYER_SPEED;
		if (game->map[(int)(game->player.y + game->player.move_y)][(int)(game->player.x + game->player.move_x)] == '0')
		{
			game->player.x += game->player.move_x;
			game->player.y += game->player.move_y;
		}
	}
}

// =========================================================================
//	POSSIBLE SOLUTION
// static int	is_wall(t_game *game, double x, double y)
// {
// 	int	mx;
// 	int	my;

// 	mx = (int)x;
// 	my = (int)y;
// 	if (mx < 0 || my < 0 || my >= game->map_h || mx >= game->map_w)
// 		return (1);
// 	if (game->map[my][mx] == '1')
// 		return (1);
// 	if (game->map[my][mx] == ' ')
// 		return (1);
// 	return (0);
// }

// static int	can_move_to(t_game *game, double nx, double ny)
// {
// 	/*
// 	 * Player is not a point: give it a small "radius".
// 	 * If any side of the player would be inside a wall, block the move.
// 	 */
// 	double	r;

// 	r = 0.20;
// 	if (is_wall(game, nx - r, ny))
// 		return (0);
// 	if (is_wall(game, nx + r, ny))
// 		return (0);
// 	if (is_wall(game, nx, ny - r))
// 		return (0);
// 	if (is_wall(game, nx, ny + r))
// 		return (0);
// 	return (1);
// }

// void	up_down(t_game *game)
// {
// 	double	nx;
// 	double	ny;

// 	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
// 	{
// 		game->player.move_x = cos(game->player.da) * PLAYER_SPEED;
// 		game->player.move_y = sin(game->player.da) * PLAYER_SPEED;
// 		nx = game->player.x + game->player.move_x;
// 		ny = game->player.y + game->player.move_y;
// 		if (can_move_to(game, nx, ny))
// 		{
// 			game->player.x = nx;
// 			game->player.y = ny;
// 		}
// 	}
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
// 	{
// 		game->player.move_x = cos(game->player.da) * PLAYER_SPEED;
// 		game->player.move_y = sin(game->player.da) * PLAYER_SPEED;
// 		nx = game->player.x - game->player.move_x;
// 		ny = game->player.y - game->player.move_y;
// 		if (can_move_to(game, nx, ny))
// 		{
// 			game->player.x = nx;
// 			game->player.y = ny;
// 		}
// 	}
// }

// void	left_right(t_game *game)
// {
// 	double	nx;
// 	double	ny;

// 	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
// 	{
// 		game->player.move_x = cos(game->player.da - M_PI_2) * PLAYER_SPEED;
// 		game->player.move_y = sin(game->player.da - M_PI_2) * PLAYER_SPEED;
// 		nx = game->player.x + game->player.move_x;
// 		ny = game->player.y + game->player.move_y;
// 		if (can_move_to(game, nx, ny))
// 		{
// 			game->player.x = nx;
// 			game->player.y = ny;
// 		}
// 	}
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
// 	{
// 		game->player.move_x = cos(game->player.da + M_PI_2) * PLAYER_SPEED;
// 		game->player.move_y = sin(game->player.da + M_PI_2) * PLAYER_SPEED;
// 		nx = game->player.x + game->player.move_x;
// 		ny = game->player.y + game->player.move_y;
// 		if (can_move_to(game, nx, ny))
// 		{
// 			game->player.x = nx;
// 			game->player.y = ny;
// 		}
// 	}
// }
// ========================= END (BEYOND HERE IS THE ORIGINAL CODE)===========
// ===========================================================================

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
