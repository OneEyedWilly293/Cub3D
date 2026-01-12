/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:40:25 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/12 22:02:37 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** - Try textures(handle_texture_line) first then try colors(handle_color_line)
** - If line is unknown and not empty => error
*/
static int	handle_one_meta_line(t_game *game, char *trim)
{
	int	ret;

	ret = handle_texture_line(game, trim);
	if (ret == -1)
		return (-1);
	if (ret == 1)
		return (1);
	if (trim[0] == 'F' || trim[0] == 'C')
		return (handle_color_line(game, trim));
	if (*trim == '\0')
		return (0);
	return (ft_error(WRONG_MSG), -1);
}

/*
** Verify that all 6 identifiers exist before allowing the map to start.
*/
static int	check_meta_complete(t_game *game)
{
	if (!game->tex.no || !game->tex.so || !game->tex.we || !game->tex.ea)
		return (ft_error(INVALID_MISSING_TEX));
	if (game->floor.r == -1 && game->ceiling.r == -1)
		return (ft_error(BOTH_IDEN_MISSING));
	if (game->floor.r == -1)
		return (ft_error(INVALID_MISSING_FLOOR));
	if (game->ceiling.r == -1)
		return (ft_error(INVALID_MISSING_CEIL));
	return (0);
}

/*
** helper to ensure when rejecting tabs in any map line should produce
** 'INVALID_MAP_CHAR_MSG, not 'WRONG_MSG'.
** currently, tabs in the first map line are caught while still in 'meta mode'
** so it is printing 'Invalid components'
*/
static int	has_map_tile(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '0' || s[i] == '1' || s[i] == 'N'
			|| s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
			return (1);
		i++;
	}
	return (0);
}

/*
** silent checker(meta_ready) since 'check_meta_complete()' is not a check but a
** validator that prints 'INVALID_MISSING_TEX, 'BOTH_IDEN_MISSING' whenever it's
** not complete.
*/
static int	meta_ready(t_game *game)
{
	if (!game->tex.no || !game->tex.so || !game->tex.we || !game->tex.ea)
		return (0);
	if (game->floor.r == -1 || game->ceiling.r == -1)
		return (0);
	return (1);
}

/*
** Reads line by line until it finds the FIRST map line.
** On success:
** - metadata is complete
** - the fd is positioned right AFTER reading that first map line,
**	 so later I need to sotre it and continue building the grid.
**
**	 For now, this function only enforeces the boundary and returns success.
*/
int	parse_identifiers_until_map(int fd, t_game *game, char **first_line)
{
	char	*line;
	char	*trim;

	*first_line = NULL;
	line = get_line(fd);
	while (line)
	{
		if (!*first_line && is_map_line(line))
		{
			if (check_meta_complete(game))
				return (free(line), 1);
			*first_line = line;
			return (0);
		}
		trim = skip_spaces(line);
		if (meta_ready(game) && *trim != '\0'
			&& has_map_tile(trim) && !is_map_line(line))
			return (free(line), ft_error(INVALID_MAP_CHAR_MSG));
		if (handle_one_meta_line(game, trim) == -1)
			return (free(line), 1);
		free(line);
		line = get_line(fd);
	}
	return (ft_error(EMPTY_MSG));
}
