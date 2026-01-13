/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_meta.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 22:02:22 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/13 19:10:34 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** A "map line" is any non-empty line that contains ONLY map characters
** (ignoring the trailing '\n', which get_line() removes anyway).
*/
int	is_map_line(char *line)
{
	int	i;
	int	has_tile;

	if (!line || !*line)
		return (0);
	i = 0;
	has_tile = 0;
	while (line[i])
	{
		if (!is_map_charset(line[i]))
			return (0);
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			has_tile = 1;
		i++;
	}
	return (has_tile);
}

/*
** Function to replace the spawn character with '0' in the map after parsing.
*/
void	set_spawn_tile_walkable(t_game game)
{
	if ( !game.map)
		return ;
	if (game.player_y < 0 || game.player_x < 0)
		return ;
	game.map[game.player_y][game.player_x] = '0';
}
