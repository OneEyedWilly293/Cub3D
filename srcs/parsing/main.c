/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:40:38 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/07 20:15:19 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"

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

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_error("Usage: ./parser_tester <map.cub>\n"));
	if (parse_scene(argv[1], &game) != 0)
		return (1);
	ft_putstr_fd("Parsing: OK\n\n", 1);
	print_textures(&game);
	print_colors(&game);
	print_player(&game);
	print_map(&game);
	free_parser_game(&game);
	return (0);
}
