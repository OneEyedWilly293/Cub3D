/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 20:24:31 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/05 17:08:28 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"

// strlen but with a NULL check(and int instead of size_t)
static int  row_len(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void    free_map(char **map)
{
	int i;

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
		return (ft_error("Malloc failed\n"));
	game->map[game->map_h] = NULL;
	y = 0;
	while (y < game->map_h)
	{
		row = (char *)malloc((size_t)game->map_w + 1);
		if (!row)
			return (free_partial_grid(game->map, y), game->map = NULL,
				ft_error("Malloc failed\n"));
		ft_memset(row, ' ', (size_t)game->map_w);
		row[game->map_w] = '\0';
		ft_memcpy(row, lines[y], (size_t)row_len(lines[y]));
		game->map[y] = row;
		y++;
	}
	return (0);
}

int read_map(int fd, t_game *game, char *first_line)
{
	char 	**lines;
	char    *line;
	int     i;

	lines = NULL;
	game->map = NULL;
	game->map_h = 0;
	game->map_w = row_len(first_line);
	if (push_line(&lines, &game->map_h, first_line))
		return (free(first_line), ft_error("Malloc failed\n"));
	line = get_line(fd);
	while (line)
	{
		i = row_len(line);
		if (i > game->map_w)
			game->map_w = i;
		if (push_line(&lines, &game->map_h, line))
			return (free(line), free_map(lines), ft_error("Malloc failed\n"));
		line = get_line(fd);
	}
	if (build_grid(game, lines))
		return (free_map(lines), 1);
	free_map(lines);
	return (0);
}
