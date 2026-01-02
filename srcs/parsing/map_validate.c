/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 01:22:11 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/03 01:36:16 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (is_player(c))
		return (1);
	return (0);
}

static int check_player_and_chars(t_game *game)
{
	int	y;
	int	x;
	int	players;

	y = 0;
	players = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			if (!is_valid_map_char(game->map[y][x]))
				return (ft_error(INVALID_MAP_CHAR_MSG));
			if (is_player(game->map[y][x]))
				players++;
			x++;
		}
		y++;
	}
	if (players != 1)
		return (ft_error(PLAYER_COUNT_MSG));
	return (0);
}

static int	tile_open(t_game *g, int y, int x)
{
	if (y == 0 || x == 0 || y == g->map_h - 1 || x == g->map_w - 1)
		return (1);
	if (g->map[y - 1][x] == ' ' || g->map[y + 1][x] == ' ')
		return (1);
	if (g->map[y][[x - 1]] == ' ' || g->map[y][x + 1] == ' ')
		return (1);
	return (0);
}

int	validate_map(t_game *game)
{
	int		y;
	int		x;
	char	c;

	if (!game->map || game->map_h <= 0 || game->map_w <= 0)
		return (ft_error(EMPTY_MSG));
	if (check_player_and_chars(game))
		return (1);
	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			c = game->map[y][x];
			if ((c == '0' || is_player(c)) && tile_open(game, y, x))
				return (ft_error(MAP_OPEN_MSG));
			x++;
		}
		y++;
	}
	return (0);
}
