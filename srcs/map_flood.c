/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:08:41 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/07 01:09:30 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parse.h"

#include "cub3d.h"
/*
** Dupicate the padded grid so we can mark visited cells.
** Important: set cpy[g->map_h] = NULL early so free_map() is always safe.
*/
static char	**dup_grid(t_game *g)
{
	char	**cpy;
	int		y;

	cpy = (char **)malloc(sizeof(char *) * (size_t)(g->map_h + 1));
	if (!cpy)
		return (NULL);
	cpy[g->map_h] = NULL;
	y = 0;
	while (y < g->map_h)
	{
		cpy[y] = ft_strdup(g->map[y]);
		if (!cpy[y])
			return (free_map(cpy), NULL);
		y++;
	}
	return (cpy);
}

/*
** Helper function to decide if a cell is walkable for flood fill.
** '0' and player letters are/should be walkable
** '1' and ' ' are not walkable (space means "void/outside)
** Possible edge case: space in the middle of the map(?) ===> I'll add a this somehow
*/
static int	is_walkable(char c)
{
	if (c == '0')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	is_void_neighbor(char **m, t_game *g, int y, int x)
{
	if (y == 0 || x == 0 || y == g->map_h - 1 || x == g->map_w - 1)
		return (1);
	if (m[y - 1][x] == ' ' || m[y + 1][x] == ' ' || m[y][x - 1] == ' '
		|| m[y][x + 1] == ' ')
		return (1);
	return (0);
}
/*
** Recursive flood fill.
** Returns 1 if map is OPEN (invalid), 0 if OK.
** We mark visited cells as 'V' so we don't loop forever.
*/
static int	flood(char **m, t_game *g, int y, int x)
{
	if (y < 0 || x < 0 || y >= g->map_h || x >= g->map_w)
		return (1);
	if (!is_walkable(m[y][x]))
		return (0);
	if (is_void_neighbor(m, g, y, x))
		return (1);
	m[y][x] = 'V';
	if (flood(m, g, y - 1, x))
		return (1);
	if (flood(m, g, y + 1, x))
		return (1);
	if (flood(m, g, y, x - 1))
		return (1);
	if (flood(m, g, y, x + 1))
		return (1);
	return (0);
}

int	validate_map_closed(t_game *g)
{
	char	**cpy;
	int		open;

	cpy = dup_grid(g);
	if (!cpy)
		return (ft_error("Malloc failed\n"));
	open = flood(cpy, g, g->player_y, g->player_x);
	free_map(cpy);
	if (open)
		return (ft_error(MAP_OPEN_MSG));
	return (0);
}
