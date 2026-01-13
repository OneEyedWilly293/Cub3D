#include "cub3d.h"

void	init_player(t_game *game)
{
	game->player = (t_player)
	{
		// positions of player
		.x = game->player_x,
		.y = game->player_y,
		.xPos = 0,
		.yPos = 0,
		.dx = cosf(0.0f),
		.dy = sinf(0.0f),
		.move_x = 0.0f,
		.move_y = 0.0f,
	};
	if (game->player_dir == 'N')
		game->player.da = 3 * M_PI_2;
	else if (game->player_dir== 'S')
		game->player.da = M_PI_2;
	else if (game->player_dir== 'E')
		game->player.da = 0;
	else if (game->player_dir == 'W')
		game->player.da = M_PI;
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIN_W, WIN_H, "MLX42", true);
	if (!game->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_set_window_title(game->mlx, "title");
	create_img(game, &game->img_3d, game->window_width, game->window_height);
	create_img(game, &game->img_map, MINIMAP_SIZE, MINIMAP_SIZE);
	return(0);
}

int create_img(t_game *game, mlx_image_t **image, int width, int height)
{
	if (*image)
	{
		mlx_delete_image(game->mlx, *image);
		*image = NULL;
	}
	*image = mlx_new_image(game->mlx, width, height);
	if (!*image)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(game->mlx, *image, 0, 0) == -1)
	{
		mlx_delete_image(game->mlx, *image);
		*image = NULL;
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// Main function
int	main(int argc, char **argv)
{
	t_game	game;

	if (check_args(argc, argv))
		return (1);
	if (parse_scene(argv[1], &game) != 0)
		return (1);
	set_spawn_tile_walkable(game);
	// game.map_width = game.map_w;
	// game.map_height = game.map_h;
	// game.window_width = WIN_W;
	// game.window_height = WIN_H;
	game.tile_size = game.map_w/ game.map_h;
	init_player(&game);
	// init_map(&game);
	if (init_mlx(&game) == 1)
	{
		printf("error\n");
		return (EXIT_FAILURE);
	}
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_resize_hook(game.mlx, resize_callback, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	mlx_delete_image(game.mlx, game.img_3d);
	mlx_delete_image(game.mlx, game.img_map);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
