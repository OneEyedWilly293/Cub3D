#include "../includes/game.h"

// Define the map
int map[] =
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

// Main function
int32_t main(void)
{
	t_game game;
	ft_memset(&game, 0, sizeof(t_game));

	game.player = &(t_player){4.5f, 5.5f, 0, 0, 0.0f, 0.0f, 0.0f}; // Initial player position
	size_t map_size = sizeof(map) / sizeof(map[0]);

	game.map = malloc(sizeof(int) * map_size);
	game.tile_size = MAP_W / MAPX;
	if (!game.map)
		exit(EXIT_FAILURE);

	ft_memcpy(game.map, map, sizeof(map));

	// Initialize MLX
	if (!(game.mlx = mlx_init(WIN_W, WIN_H, "MLX42", true))) {
		puts(mlx_strerror(mlx_errno));
		return EXIT_FAILURE;
	}
	mlx_set_window_title(game.mlx, "title");
	if(!(game.img_map = mlx_new_image(game.mlx, MAP_W, MAP_H)))
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return EXIT_FAILURE;
	}
	if(!(game.img_3d  = mlx_new_image(game.mlx, WIN_W - MAP_W, WIN_H)))
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return EXIT_FAILURE;
	}
	if(mlx_image_to_window(game.mlx, game.img_map, 0, 0) == -1)
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return EXIT_FAILURE;
	}
	if(mlx_image_to_window(game.mlx, game.img_3d, MAP_W, 0) == -1)
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return EXIT_FAILURE;
	}

	mlx_loop_hook(game.mlx, update, &game);
	mlx_loop(game.mlx);
	mlx_delete_image(game.mlx, game.img_map);
	mlx_delete_image(game.mlx, game.img_3d);
	mlx_terminate(game.mlx);
	return EXIT_SUCCESS;
}

