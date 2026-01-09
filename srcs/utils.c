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

// #include "parse.h"
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
