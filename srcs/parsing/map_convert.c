/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 15:48:10 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/04 15:55:19 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	tile_to_int(char c)
{
	if (c == '1')
		return (1);
	if (c == ' ')
		return (-1);
	return (0);
}

int	*map_to_int(const t_game *g)
{
	int	*dst;
	int	x;
	int	y;
	int	i;

	if (!g || !g->map || g->map_w <= 0 || g->map_h <= 0)
		return (NULL);
	dst = (int *)malloc(sizeof(int) * (size_t)(g->map_w * g->map_h));
	if (!dst)
		return (NULL);
	y = 0;
	i = 0;
	while (y < g->map_h)
	{
		x = 0;
		while (x < g->map_h)
		{
			dst[i] = tile_to_int(g->map[y][x]);
			x++;
			i++;
		}
		y++;
	}
	return (dst);
}

