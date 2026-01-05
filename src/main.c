#include "../includes/game.h"

// Define the map
int map[] =
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
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
	game->player = (t_player){4.5f, 5.5f, 0, 0, 0.0f, 0.0f, 0.0f, 0, 0, 0};
}

void	init_map(t_game *game)
{
	size_t map_size = sizeof(map) / sizeof(map[0]);

	game->map = malloc(sizeof(int) * map_size);
	game->tile_size = MAP_W / MAPX;
	if (!game->map)
		exit(EXIT_FAILURE);
	ft_memcpy(game->map, map, sizeof(map));
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIN_W, WIN_H, "MLX42", true);
	// game->mlx = NULL;
	if(!game->mlx) 
	{
		puts(mlx_strerror(mlx_errno));
		return EXIT_FAILURE;
	}
	mlx_set_window_title(game->mlx, "title");
	game->img_3d = mlx_new_image(game->mlx, WIN_W, WIN_H);
	// game->img_3d = NULL;
	if(!game->img_3d)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		return EXIT_FAILURE;
	}
	game->img_map = mlx_new_image(game->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	// game->img_map = NULL;
	if(!game->img_map)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		return EXIT_FAILURE;
	}
	if(mlx_image_to_window(game->mlx, game->img_3d, 0, 0) == -1)
		// if(1)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		return EXIT_FAILURE;
	}
	// printf("img_3d instance count: %zu\n", game->img_3d->count);
	if(mlx_image_to_window(game->mlx, game->img_map, 0, 0) == -1)
		// if(1)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		return EXIT_FAILURE;
	}
	return(0);
}

// Main function
int32_t main(void)
{
	t_game game;
	ft_memset(&game, 0, sizeof(t_game));

	game.map_width = MAPX;
	game.map_height = MAPY;
	init_player(&game);
	init_map(&game);
	if(init_mlx(&game) == 1)
	{
		printf("error\n");
		return EXIT_FAILURE;
	}
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_resize_hook(game.mlx, resize_callback, &game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_loop(game.mlx);
	mlx_delete_image(game.mlx, game.img_3d);
	mlx_delete_image(game.mlx, game.img_map);
	mlx_terminate(game.mlx);
	return EXIT_SUCCESS;
}
