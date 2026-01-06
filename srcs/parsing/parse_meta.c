/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 13:40:25 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/07 00:34:42 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"

/*
** Checks if a character is allowed in the map.
** Allowed: '0', '1', 'N', 'S', 'E', 'W', space.
*/
static int	is_map_charset(char c)
{
	if (c == '0' || c == '1')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

/*
** A "map line" is any non-empty line that contains ONLY map characters
** (ignoring the trailing '\n', which get_line() removes anyway).
*/
static int	is_map_line(char *line)
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
** get_line() returns lines without '\n, so empty line =="".
** But also treat lines of only spaces
*/
// DELETE LATER. 6.01 no longer needed after check added in map_read.c
// static int	is_empty_line(char *line)
// {
// 	char	*trim;

// 	if (!line)
// 		return (1);
// 	trim = skip_spaces(line);
// 	if (*trim == '\0')
// 		return (1);
// 	return (0);
// }

/*
** A function to set default values for metadatas
*/
static void	init_meta_defaults(t_game *game)
{
	game->floor.r = -1;
	game->floor.g = -1;
	game->floor.b = -1;
	game->ceiling.r = -1;
	game->ceiling.g = -1;
	game->ceiling.b = -1;
	game->tex.no = NULL;
	game->tex.so = NULL;
	game->tex.we = NULL;
	game->tex.ea = NULL;
}

/*
** - Try textures(handle_texture_line) first then try colors(handle_color_line)
** - If line is unknown and not empty => error
*/
static int	handle_one_meta_line(t_game *game, char *trim)
{
	if (handle_texture_line(game, trim) != 0)
		return (1);
	if (trim[0] == 'F' || trim[0] == 'C')
	{
		if (handle_color_line(game, trim))
			return (1);
		return (0);
	}
	if (*trim == '\0')
		return (0);
	return (ft_error(WRONG_MSG));
}

/*
** Verify that all 6 identifiers exist before allowing the map to start.
*/
static int	check_meta_complete(t_game *game)
{
	if (!game->tex.no || !game->tex.so || !game->tex.we || !game->tex.ea)
		return (ft_error(INVALID_MISSING_TEX));
	if (game->floor.r == -1 || game->ceiling.r == -1)
		return (ft_error(BOTH_IDEN_MISSING));
	return (0);
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
	init_meta_defaults(game);
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
		if (handle_one_meta_line(game, trim))
			return (free(line), 1);
		free(line);
		line = get_line(fd);
	}
	return (ft_error(EMPTY_MSG));
}
