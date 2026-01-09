/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:47:47 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/08 15:03:40 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parse.h"
#include "cub3d.h"
#include "libft.h"

static int	is_ws(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f');
}

/*
** Checks if the trimmed line starts with "NO ", "SO ", "WE ", or "EA ".
** RULE: strict space/tab after 2 letters to prevent false matches like 'NOO'.
*/
static int	is_id(char *s, char *id)
{
	if (!s || !id)
		return (0);
	if (s[0] != id[0] || s[1] != id[1])
		return (0);
	if (!is_ws(s[2]))
		return (0);
	return (1);
}

static int	has_png_ext(char *path)
{
	int	len;

	if (!path)
		return (0);
	len = (int)ft_strlen(path);
	if (len < 4)
		return (0);
	if (path[len - 4] != '.' || path[len -3] != 'p')
		return (0);
	if (path[len - 2] != 'n' || path[len - 1] != 'g')
		return (0);
	return (1);
}


/*
** Validate and store one texture path.
** - Duplicate protection: if *dst already set => error
** - path must exist/openable
** - Extension must be "*.png".
** - Stores a duplicated copy(ft_strdup) so it survives after the line is freed.
 */
static int	store_texture(char **dst, char *path)
{
	int	fd;

	if (*dst != NULL)
		return (ft_error(INVALID_DUP_TEX));
	if (!path || *path == '\0')
		return (ft_error(PATH_MSG));
	if (!has_png_ext(path))
		return (ft_error(INVALID_TEX_EXT_MSG));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error(PATH_MSG));
	close(fd);
	*dst = ft_strdup(path);
	if (*dst == NULL)
		return (ft_error("Malloc failed\n"));
	return (0);
}

/*
** - If line is a texture identifier line, parse and store the path.
** - If not a texture line, return 0 (no error).
*/
int	handle_texture_line(t_game *game, char *trim)
{
	char	*path;
	int		ret;

	if (is_id(trim, N))
		path = skip_spaces(trim + 2);
	else if (is_id(trim, S))
		path = skip_spaces(trim + 2);
	else if (is_id(trim, W))
		path = skip_spaces(trim + 2);
	else if (is_id(trim, E))
		path = skip_spaces(trim + 2);
	else
		return (0);
	if (is_id(trim, N))
		ret = store_texture(&game->tex.no, path);
	else if (is_id(trim, S))
		ret = store_texture(&game->tex.so, path);
	else if (is_id(trim, W))
		ret = store_texture(&game->tex.we, path);
	else
		ret = store_texture(&game->tex.ea, path);
	if (ret != 0)
		return (-1);
	return (1);
}


/*
** - Scans the whole .cub file and store NO/SO/WE/EA.
** - This function is the same "scan all lines" approach like find_color_lines().
** TO DO: MERGE THEM INTO ONE PASS LATER
*/
// int find_texture_lines(int fd, t_game *game)
// {
// 	char	*line;
// 	char	*trim;

// 	game->tex.no = NULL;
// 	game->tex.so = NULL;
// 	game->tex.we = NULL;
// 	game->tex.ea = NULL;
// 	line = get_line(fd);
// 	while (line)
// 	{
// 		trim = skip_spaces(line);
// 		if (handle_texture_line(game, trim))
// 			return (free(line), 1);
// 		free(line);
// 		line = get_line(fd);
// 	}
// 	if (!game->tex.no || !game->tex.so || !game->tex.we || !game->tex.ea)
// 		return (ft_error(INVALID_MISSING_TEX));
// 	return (0);
// }
