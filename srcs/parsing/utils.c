/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:06:36 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/07 23:14:47 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/*
** Small helper: skip leading spaces/tabs.
** This allows us to accept lines like "   F 0,0,255" etc.
**   - Windows CRLF leaves a '\r' at end of lines (before '\n').
**  - Treating '\r' as whitespace avoids hidden "Invalid components" issues.
*/
//|| *s == '\v' || *s == '\f
char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t'|| *s == '\r')
		s++;
	return (s);
}
