/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 20:24:31 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/08 19:51:26 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parse.h"
#include "cub3d.h"
#include "libft.h"

// strlen but with a NULL check(and int instead of size_t)
static int	row_len(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return (i);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static int	push_line(char ***arr, int *n, char *line)
{
	char	**new_arr;
	int		i;

	new_arr = (char **)malloc(sizeof(char *) * (size_t)(*n + 2));
	if (!new_arr)
		return (1);
	i = 0;
	while (i < *n)
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	new_arr[*n] = line;
	new_arr[*n + 1] = NULL;
	free(*arr);
	*arr = new_arr;
	*n += 1;
	return (0);
}

static void	free_partial_grid(char **grid, int y)
{
	while (y > 0)
	{
		y--;
		free(grid[y]);
	}
	free(grid);
}

static int	build_grid(t_game *game, char **lines)
{
	int		y;
	char	*row;

	game->map = (char **)malloc(sizeof(char *) * (size_t)(game->map_h + 1));
	if (!game->map)
		return (1);
	game->map[game->map_h] = NULL;
	y = 0;
	while (y < game->map_h)
	{
		row = (char *)malloc((size_t)game->map_w + 1);
		if (!row)
		{
			free_partial_grid(game->map, y);
			game->map = NULL;
			return (1);
		}
		ft_memset(row, ' ', (size_t)game->map_w);
		row[game->map_w] = '\0';
		ft_memcpy(row, lines[y], (size_t)row_len(lines[y]));
		game->map[y] = row;
		y++;
	}
	return (0);
}

/*
** Helper function to validate a map line under "map mode rules"
** - spaces-only line => EMPTY_LINE_IN_MAP_MSG
** - contains non-map charset => META_AFTER_MCAP_MSG
*/
static int	check_map_mode_line(char *line)
{
	int	i;

	if (*skip_spaces(line) == '\0')
		return (ft_error(EMPTY_LINE_IN_MAP_MSG));
	i = 0;
	while (line[i])
	{
		if (line[i] == '\r')
		{
			i++;
			continue;
		}C
		if (!is_map_charset(line[i]))
			return (ft_error(INVALID_MAP_CHAR_MSG));
		i++;
	}
	return (0);
}

/*
** Helper function to read map lines for read_map() for Norm compliance.
**
*/
static int read_map_lines(int fd, t_game *game, char ***lines)
{
	char	*line;
	int		i;

	line = get_line(fd);
	while (line)
	{
		if (check_map_mode_line(line))
			return (free(line), free_map(*lines), 1);
		i = row_len(line);
		if (i > game->map_w)
			game->map_w = i;
		if (push_line(lines, &game->map_h, line))
			return (free(line), free_map(*lines), ft_error("Malloc failed\n"));
		line = get_line(fd);
	}
	return (0);
}

int	read_map(int fd, t_game *game, char *first_line)
{
	char	**lines;

	lines = NULL;
	game->map = NULL;
	game->map_h = 0;
	game->map_w = row_len(first_line);
	if (check_map_mode_line(first_line))
		return (free(first_line), 1);
	if (push_line(&lines, &game->map_h, first_line))
		return (free(first_line), ft_error("Malloc failed\n"));
	if (read_map_lines(fd, game, &lines))
		return (1);
	if (build_grid(game, lines))
		return (free_map(lines), ft_error("Malloc failed\n"));
	free_map(lines);
	return (0);
}
