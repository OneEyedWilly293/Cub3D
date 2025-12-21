/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:36:47 by jgueon            #+#    #+#             */
/*   Updated: 2025/12/21 19:14:02 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../../lib/libft/include/libft.h"

// ============================= delete later ===============================
char	*ft_strdup(const char *s)
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (newstr)
	{
		while (s[i])
		{
			newstr[i] = s[i];
			i++;
		}
		newstr[i] = '\0';
	}
	return (newstr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*array;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	array = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!array)
		return (NULL);
	ft_memcpy(array, s1, s1_len);
	ft_memcpy(array + s1_len, s2, s2_len);
	array[s1_len + s2_len] = '\0';
	return (array);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*string;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		string = malloc(1);
		if (!string)
			return (NULL);
		string[0] = '\0';
		return (string);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	string = malloc(len + 1);
	if (!string)
		return (NULL);
	ft_memcpy(string, s + start, len);
	string[len] = '\0';
	return (string);
}

size_t	ft_strlen(const char *s)
{
	int	p;

	p = 0;
	while (*s++)
		++p;
	return (p);
}


void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char			*tmp_dst;
	const unsigned char		*tmp_src;

	tmp_dst = (unsigned char *) dest;
	tmp_src = (const unsigned char *) src;
	while (n--)
		*(tmp_dst++) = *(tmp_src++);
	return (dest);
}
// ===================================================================

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
