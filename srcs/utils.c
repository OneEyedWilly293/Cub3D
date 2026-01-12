/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:06:36 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/12 22:12:13 by jgueon           ###   ########.fr       */
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
	while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\v' || *s == '\f')
		s++;
	return (s);
}

void	free_split(char **colors)
{
	int	i;

	if (!colors)
		return ;
	i = 0;
	while (colors[i])
	{
		free(colors[i]);
		i++;
	}
	free(colors);
}

int	is_signed_number(char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

// Helper function: to count elements in a NULL-terminated char **.
// MOVE TO utils later
int	arrlen(char **arr)
{
	int	len;

	len = 0;
	if (!arr)
		return (0);
	while (arr[len])
		len++;
	return (len);
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
