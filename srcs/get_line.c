/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:36:47 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/10 03:32:22 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static char	*extract_line(char *content, char *buf)
{
	int		i;
	char	*line;

	if (!content || content[0] == '\0')
		return (free(content), NULL);
	i = 0;
	while (content[i] && content[i] != '\n')
		i++;
	line = ft_substr(content, 0, i);
	if (!line)
		return (free(content), NULL);
	if (content[i] == '\n')
		i++;
	ft_strlcpy(buf, content + i, BUFFER_SIZE + 1);
	free(content);
	return (line);
}

void	get_line_reset(void)
{
	char	*buf;

	buf = get_line(-1);
	(void)buf;
}


char	*get_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*content;
	char		tmp[BUFFER_SIZE + 1];
	ssize_t		r;

	if (fd < 0)
	{
		buf[0] = '\0';
		return (NULL);
	}
	content = ft_strdup(buf);
	if (!content)
		return (NULL);
	while (!has_nl(content))
	{
		r = read(fd, tmp, BUFFER_SIZE);
		if (r <= 0)
			break;
		tmp[r] = '\0';
		content = append_buf(content, tmp);
		if (!content)
			return (NULL);
	}
	return (extract_line(content, buf));
}
