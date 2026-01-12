/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 21:48:53 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/12 21:53:06 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// strlen but with a NULL check(and int instead of size_t)
int	row_len(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return (i);
}

void	free_partial_grid(char **grid, int y)
{
	while (y > 0)
	{
		y--;
		free(grid[y]);
	}
	free(grid);
}
