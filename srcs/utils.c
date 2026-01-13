/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:06:36 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/08 19:20:34 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Small helper: skip leading spaces/tabs.
** This allows us to accept lines like "   F 0,0,255" etc.
**   - Windows CRLF leaves a '\r' at end of lines (before '\n').
**  - Treating '\r' as whitespace avoids hidden "Invalid components" issues.
*/
char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t'|| *s == '\r' || *s == '\v' || *s == '\f')
		s++;
	return (s);
}

int	is_wall(t_game *game, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (mx < 0 || my < 0 || my >= game->map_h || mx >= game->map_w)
		return (1);
	if (game->map[my][mx] == '1')
		return (1);
	if (game->map[my][mx] == ' ')
		return (1);
	return (0);
}

int	can_move_to(t_game *game, double nx, double ny)
{
	if (is_wall(game, nx - PLAYER_RADIUS, ny))
		return (0);
	if (is_wall(game, nx + PLAYER_RADIUS, ny))
		return (0);
	if (is_wall(game, nx, ny - PLAYER_RADIUS))
		return (0);
	if (is_wall(game, nx, ny + PLAYER_RADIUS))
		return (0);
	return (1);
}

void	init_mouse(t_game *game)
{
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(game->mlx, mouse_hook, game);
}
