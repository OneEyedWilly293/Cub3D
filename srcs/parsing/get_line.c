/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:36:47 by jgueon            #+#    #+#             */
/*   Updated: 2025/12/22 18:31:41 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"

static int	has_nl(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*append_buf(char *line, char *buf)
{
	char	*new_line;

	if (!line)
		return (ft_strdup(buf));
	new_line = ft_strjoin(line, buf);
	free(line);
	return (new_line);
}

static char	*extract_line(char **stash)
{
	int		i;
	char	*line;
	char	*rest;

	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	line = ft_substr(*stash, 0, i);
	if ((*stash)[i] == '\n')
		i++;
	rest = ft_strdup(*stash + i);
	free(*stash);
	*stash = rest;
	return (line);
}

char	*get_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	static char	*stash;
	int			r;

	r = 1;
	while (!stash || !has_nl(stash))
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r <= 0)
			break;
		buf[r] = '\0';
		stash = append_buf(stash, buf);
		if (!stash)
			return (NULL);
	}
	if (!stash || stash[0] == '\0')
		return (free(stash), stash = NULL, NULL);
	if (r == 0 || has_nl(stash))
		return (extract_line(&stash));
	return (NULL);
}
