/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:24:02 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/10 04:13:45 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**  Ensure missing identifiers are detectable ('-1') and free_parse_game()
**  can safely free NULL pointers; starting state
*/
void	init_parser_game(t_game *g)
{
	if (!g)
		return ;
	ft_memset(g, 0, sizeof(t_game));
	g->floor.r = -1;
	g->floor.g = -1;
	g->floor.b = -1;
	g->ceiling.r = -1;
	g->ceiling.g = -1;
	g->ceiling.b = -1;
	g->player_found = 0;
	g->player_dir = '\0';
	g->window_width = WIN_W;
	g->window_height = WIN_H;
}

void	free_parser_game(t_game *game)
{
	if (!game)
		return ;
	free(game->tex.no);
	free(game->tex.so);
	free(game->tex.we);
	free(game->tex.ea);
	game->tex.no = NULL;
	game->tex.so = NULL;
	game->tex.we = NULL;
	game->tex.ea = NULL;
	if (game->map)
		free_map(game->map);
	game->map = NULL;
	game->map_w = 0;
	game->map_h = 0;
	game->player_found = 0;
	game->player_dir = '\0';
	game->player_x = 0;
	game->player_y = 0;
}

int	parse_scene(const char *path, t_game *game)
{
	int		fd;
	char	*first_line;

	init_parser_game(game);
	get_line_reset();
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error(CANT_OPEN_MAP));
	if (parse_identifiers_until_map(fd, game, &first_line))
		return (close(fd), free_parser_game(game), 1);
	if (read_map(fd, game, first_line))
		return (close(fd), free_parser_game(game), 1);
	if (validate_map(game))
		return (close(fd), free_parser_game(game), 1);
	close (fd);
	return (0);
}


