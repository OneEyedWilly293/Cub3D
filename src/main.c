#include "../includes/game.h"

// Define the map
int map[] =
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,0,0,1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

void	init_player(t_game *game)
{
	game->player = (t_player)
	{
		.x = 4.5f,
		.y = 5.5f,
		.xPos = 0,
		.yPos = 0,
		.dx = cosf(0.0f),
		.dy = sinf(0.0f),
		.da = 0.0f,
		.move_x = 0.0f,
		.move_y = 0.0f,
	};
}

void	init_map(t_game *game)
{
	size_t	map_size;

	map_size = sizeof(map) / sizeof(map[0]);
	game->map = malloc(sizeof(int) * map_size);
	game->tile_size = MAP_W / GRIDX;
	if (!game->map)
		exit(EXIT_FAILURE);
	ft_memcpy(game->map, map, sizeof(map));
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

	create_img(game, &game->img_3d);
	create_img(game, &game->img_map);

	// game->img_3d = mlx_new_image(game->mlx, WIN_W, WIN_H);
	// if(!game->img_3d)
	// {
	// 	mlx_close_window(game->mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	return EXIT_FAILURE;
	// }
	// if(mlx_image_to_window(game->mlx, game->img_3d, 0, 0) == -1)
	// {
	// 	mlx_close_window(game->mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	return EXIT_FAILURE;
	// }
	// mlx_set_instance_depth(&game->img_3d->instances[0], 0);
	// game->img_map = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	// if(!game->img_map)
	// {
	// 	mlx_close_window(game->mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	return EXIT_FAILURE;
	// }
	// if(mlx_image_to_window(game->mlx, game->img_map, 10, 10) == -1)
	// {
	// 	mlx_close_window(game->mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	return EXIT_FAILURE;
	// }
	// mlx_set_instance_depth(&game->img_map->instances[0], 10);
	return(0);
}

int create_img(t_game *game, mlx_image_t **image)
{
	if (*image)
	{
		mlx_delete_image(game->mlx, *image);
		game->img_3d = NULL;
	}
	*image = mlx_new_image(game->mlx, game->window_width, game->window_height);
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
int32_t	main(void)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	game.map_width = GRIDX;
	game.map_height = GRIDY;
	game.window_width = WIN_W;
	game.window_height = WIN_H;
	init_player(&game);
	init_map(&game);
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
