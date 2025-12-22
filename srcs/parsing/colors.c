/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:08:33 by jgueon            #+#    #+#             */
/*   Updated: 2025/12/22 14:42:49 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../../lib/libft/include/libft.h"

// =========================== DELETE ===================================

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	len;

	start = 0;
	len = ft_strlen(s1);
	if (!s1)
		return (NULL);
	while (start < len && ft_strchr(set, s1[start]))
		start++;
	while (len > start && ft_strchr(set, s1[len - 1]))
		len--;
	return (ft_substr(s1, start, len - start));
}


static size_t	count_words(char const *s, char c);
static char		**allocate_array(char const *s, char c, char **arr);
static void		free_array(char **arr, size_t i);

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	arr = malloc(sizeof(char *) * (word_count + 1));
	if (!arr)
		return (NULL);
	arr = allocate_array(s, c, arr);
	if (!arr)
		return (NULL);
	arr[word_count] = NULL;
	return (arr);
}

// Counts how many words to split the string into.
static size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

// Allocates each single word into its array.
static char	**allocate_array(char const *s, char c, char **arr)
{
	size_t	i;
	size_t	word_len;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (ft_strchr(s, c))
				word_len = ft_strchr(s, c) - s;
			else
				word_len = ft_strlen(s);
			arr[i] = ft_substr(s, 0, word_len);
			if (!arr[i])
			{
				free_array(arr, i);
				return (NULL);
			}
			s += word_len;
			i++;
		}
	}
	return (arr);
}

// Frees all allocated arrays.
static void	free_array(char **arr, size_t i)
{
	while (i > 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr[i]);
	arr[i] = NULL;
	free(arr);
	arr = NULL;
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	c = (unsigned char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *) &s[i]);
	return (NULL);
}


// =======================================================================

//MOVE TO utils later
int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

// MOve to utils later
int	is_str_digits(const char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return(0);
	while (s[i] != '\0')
	{
		if (!is_digit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

// move to utils later
int	ft_atoi_pos(const char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		n = (n * 10) + (s[i] - '0');
		i++;
	}
	return (n);
}

int get_nb_comma(char *line)
{
	int	n;

	n = 0;
	if (!line || !*line)
		return(n);
	while (*line)
	{
		if (*line == ',')
			n++;
		line++;
	}
	return (n);
}

int check_rgb_range(int i)
{
	return ((i >= 0) && (i <= 255));
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

// FUNCTION TO CHECK RGB VALUES 0~255 and if there is 3 values
// color: char ** from ft_split(..., ',')
// rgb: int[3] output
static int	parse_rgb_values(char **color, int *rgb)
{
	int	i;
	int	n;

	if (!color || !rgb)
		return (1);
	if (arrlen(color) != 3)
		return (ft_error(INVALID_RGB_VALUE_MSG));
	i = 0;
	while (i < 3)
	{
		if (!is_str_digits(color[i]))
			return (ft_error(INVALID_RGB_CHAR_MSG));
		n = ft_atoi_pos(color[i]);
		if (!check_rgb_range(n))
			return (ft_error(INVALID_RGB_RANGE_MSG));
		rgb[i] = n;
		i++;
	}
	return (0);
}

// Handling spaces: trim tokens after ft_split
// ft_split: "220, 100, 0" becomes tokens: "220" , " 100" , " 0"
// This function creates new allocated strings so we need to free the old ones.
static int	trim_tokens(char **colors)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (colors[i])
	{
		trimmed = ft_strtrim(colors[i], " \t"); // TO CHECK: \n
		if (!trimmed)
		return (1);
		free(colors[i]);
		colors[i] = trimmed;
		i++;
	}
	return (0);
}

// move to utils later
static void free_split(char **colors)
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

// Function to parse a full line like
// "F 220, 100, 0"
// "C 225,30,0"
// Identifier: 'F' or 'C'
// Steps:
// 1) Skip the identifier and spaces -> "200,100,0"
// 2) Check there are exactly 2 commas
// 3) Split by ',' using ft_split
// 4) parse_rgb_values(colors, rgb)
int	parse_rgb_line(char identifier, char *line, int *rgb)
{
	char	*meta;
	char 	**colors;
	int		i;

	if (!line || !rgb)
		return (1);
	if (line[0] != identifier)
		return (1);
	meta = line + 1;
	while (*meta == ' ' || *meta == '\t')
		meta++;
	if (get_nb_comma(meta) != 2)
		return (ft_error(INVALID_RGB_VALUE_MSG));
	colors = ft_split(meta, ',');
	if (!colors)
		return (ft_error("ft_split failed"));
	if (trim_tokens(colors))
	{
		free_split(colors);
		return (ft_error("ft_strtrim failed"));
	}
	i = parse_rgb_values(colors, rgb);
	free_split(colors);
	return (i);
}

/*
** Flow example:
** colors = ft_split(meta, ',');
** trim_tokens(colors);
** parse_rgb_values(colors, rgb);
** free_split(colors);
*/


/*
** Small helper: skip leading spaces/tabs.
** This allows us to accept lines like "   F 0,0,255" etc.
*/
char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

/* This function:
**	- Reads the file line-by-line
**	- Looks only for F and C lines
**	- Stores the parsed RGB into floor_rbg and ceiling_rgb
**
**	Returns: 0 for success and 1 for error
*/
static int	parse_colors_only(int fd, int *floor_rgb, int *ceiling_rgb)
{
	char	*line;
	char	*trim;

	line = get_line(fd);
	while (line)
	{
		trim = skip_spaces(line);
		if (trim[0] == 'F' && (trim[1] == ' ' || trim[1] == '\t'))
		{
			if (parse_rgb_line('F', trim, floor_rgb))
				return (free(line), 1);
		}
		if (trim[0] == 'C' && (trim[1] == ' ' || trim[1] == '\t'))
		{
			if (parse_rgb_line('C', trim, ceiling_rgb))
				return (free(line), 1);
		}
		free(line);
		line = get_line(fd);
	}
	return (0);
}
