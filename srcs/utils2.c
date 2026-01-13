/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 22:00:17 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/14 00:50:12 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check whether a character belongs to the allowed map character set.
 *
 * This helper defines which characters are valid inside the parsed map grid.
 * Accepted characters are:
 * - '0' (floor)
 * - '1' (wall)
 * - 'N', 'S', 'E', 'W' (player start + orientation)
 * - ' ' (space / void padding)
 *
 * It is commonly used by parsing/validation code to reject invalid symbols
 * inside map lines.
 *
 * @param c The character to test.
 *
 * @return 1 if @p c is allowed in the map, 0 otherwise.
 */
int	is_map_charset(char c)
{
	if (c == '0' || c == '1')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}
