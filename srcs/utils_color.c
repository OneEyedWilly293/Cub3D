/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 21:27:19 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/12 22:11:45 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_nb_comma(char *line)
{
	int	n;

	n = 0;
	if (!line || !*line)
		return (n);
	while (*line)
	{
		if (*line == ',')
			n++;
		line++;
	}
	return (n);
}

int	check_rgb_range(int i)
{
	return ((i >= 0) && (i <= 255));
}

/*
** Returns 1 if a t_color is already assigned (not -1,-1,-1 anymore)
*/
int	is_color_set(t_color c)
{
	return (c.r != -1 && c.g != -1 && c.b != -1);
}

/*
** Store parsed RGB into game struct.
** This MUST be called, otherwise game stays at -1,-1,-1.
*/
void	store_color(t_game *game, char id, int *tmp)
{
	if (id == 'F')
	{
		game->floor.r = tmp[0];
		game->floor.g = tmp[1];
		game->floor.b = tmp[2];
	}
	else
	{
		game->ceiling.r = tmp[0];
		game->ceiling.g = tmp[1];
		game->ceiling.b = tmp[2];
	}
}
