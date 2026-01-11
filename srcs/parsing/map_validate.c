/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 01:22:11 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/11 19:33:18 by jgueon           ###   ########.fr       */
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

static int	store_player(t_game *g, int y, int x, char c)
{
	if (g->player_found)
		return (ft_error(PLAYER_COUNT_MSG));
	g->player_found = 1;
	g->player_dir = c;
	g->player_x = x;
	g->player_y = y;
	return (0);
}

static int	check_player_and_chars(t_game *g)
{
	int		y;
	int		x;
	char	c;

	g->player_found = 0;
	y = 0;
	while (y < g->map_h)
	{
		x = 0;
		while (x < g->map_w)
		{
			c = g->map[y][x];
			if (!is_valid_map_char(c))
				return (ft_error(INVALID_MAP_CHAR_MSG));
			if (is_player(c) && store_player(g, y, x, c))
				return (1);
			x++;
		}
		y++;
	}
	if (!g->player_found)
		return (ft_error(PLAYER_COUNT_MSG));
	return (0);
}

int	validate_map(t_game *game)
{
	if (!game->map || game->map_h <= 0 || game->map_w <= 0)
		return (ft_error(EMPTY_MSG));
	if (check_player_and_chars(game))
		return (1);
	if (validate_map_closed(game))
		return (1);
	return (0);
}
