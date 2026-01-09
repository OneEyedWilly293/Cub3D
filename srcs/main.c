// #include "parse.h"
#include "cub3d.h"
#include "libft.h"
// #include "../includes/game.h"

// Define the map
// int map[] =
// {
// 	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
// 	1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
// 	1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
// 	1,0,0,1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
// 	1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
// 	1,1,0,0,1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,
// 	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
// };

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
		.move_x = 0.0f,
		.move_y = 0.0f,
		.face = 'E',	
	};
	if (game->player.face == 'N')
		game->player.da = 3 * M_PI_2;
	else if (game->player.face == 'S')
		game->player.da = M_PI_2;
	else if (game->player.face == 'E')
		game->player.da = 0;
	else if (game->player.face == 'W')
		game->player.da = M_PI;
}

// void	init_map(t_game *game)
// {
// 	size_t	map_size;
//
// 	map_size = sizeof(map) / sizeof(map[0]);
// 	game->map = malloc(sizeof(int) * map_size);
// 	game->tile_size = MAP_W / GRIDX;
// 	if (!game->map)
// 		exit(EXIT_FAILURE);
// 	ft_memcpy(game->map, map, sizeof(map));
// }

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

	if (argc != 2)
		return (ft_error("Usage: ./parser_tester <map.cub>\n"));
	if (parse_scene(argv[1], &game) != 0)
		return (1);
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
	free_parser_game(&game);
	return (EXIT_SUCCESS);
}
/*
** This is a SIMPLE TESTER main.c for your parser.
**
** GOAL:
** - Run: ./parser_tester path/to/map.cub
** - It will call parse_scene(), and if parsing succeeds:
**   - Print textures
**   - Print colors
**   - Print player info
**   - Print the padded map grid (so you can visually confirm padding/spaces)
**
** WHY THIS HELPS:
** - You can quickly see if:
**   - Texture paths are correctly stored
**   - Colors are parsed correctly
**   - Player position is detected correctly
**   - The map is padded to map_w and contains spaces where expected
**
** NOTE:
** - Your ft_error() already prints the error message.
** - parse_scene() already frees game on error (it calls free_parser_game()).
** - On success, we must call free_parser_game() ourselves to avoid leaks.
*/

static void	print_textures(t_game *g)
{
	ft_putstr_fd("== Textures ==\n", 1);
	ft_putstr_fd("NO: ", 1);
	ft_putstr_fd(g->tex.no, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("SO: ", 1);
	ft_putstr_fd(g->tex.so, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("WE: ", 1);
	ft_putstr_fd(g->tex.we, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("EA: ", 1);
	ft_putstr_fd(g->tex.ea, 1);
	ft_putstr_fd("\n\n", 1);
}

static void	print_colors(t_game *g)
{
	ft_putstr_fd("== Colors ==\n", 1);
	ft_putstr_fd("Floor: ", 1);
	ft_putnbr_fd(g->floor.r, 1);
	ft_putstr_fd(",", 1);
	ft_putnbr_fd(g->floor.g, 1);
	ft_putstr_fd(",", 1);
	ft_putnbr_fd(g->floor.b, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("Ceiling: ", 1);
	ft_putnbr_fd(g->ceiling.r, 1);
	ft_putstr_fd(",", 1);
	ft_putnbr_fd(g->ceiling.g, 1);
	ft_putstr_fd(",", 1);
	ft_putnbr_fd(g->ceiling.b, 1);
	ft_putstr_fd("\n\n", 1);
}

static void	print_player(t_game *g)
{
	ft_putstr_fd("== Player ==\n", 1);
	ft_putstr_fd("Dir: ", 1);
	ft_putchar_fd(g->player_dir, 1);
	ft_putstr_fd("\nPos (x,y): ", 1);
	ft_putnbr_fd(g->player_x, 1);
	ft_putstr_fd(",", 1);
	ft_putnbr_fd(g->player_y, 1);
	ft_putstr_fd("\n\n", 1);
}

static void	print_map(t_game *g)
{
	int	y;

	ft_putstr_fd("== Map (padded grid) ==\n", 1);
	ft_putstr_fd("map_w: ", 1);
	ft_putnbr_fd(g->map_w, 1);
	ft_putstr_fd(" | map_h: ", 1);
	ft_putnbr_fd(g->map_h, 1);
	ft_putstr_fd("\n", 1);
	y = 0;
	while (g->map && g->map[y])
	{
		ft_putstr_fd(g->map[y], 1);
		ft_putstr_fd("\n", 1);
		y++;
	}
	ft_putstr_fd("\n", 1);
}

// int	main(int argc, char **argv)
// {
// 	t_game	game;
//
// 	if (argc != 2)
// 		return (ft_error("Usage: ./parser_tester <map.cub>\n"));
// 	if (parse_scene(argv[1], &game) != 0)
// 		return (1);
// 	ft_putstr_fd("Parsing: OK\n\n", 1);
// 	print_textures(&game);
// 	print_colors(&game);
// 	print_player(&game);
// 	print_map(&game);
// 	free_parser_game(&game);
// 	return (0);
// }
