/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:08:33 by jgueon            #+#    #+#             */
/*   Updated: 2025/12/19 16:05:59 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_str_digits(const char *s)
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

static int	ft_atoi_pos(const char *s)
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

static int get_nb_comma(char *line)
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
static int	arrlen(char **arr)
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
		if (!check_rgb_range(r))
			return (ft_error(INVALID_RGB_RANGE_MSG));
		rgb[i] = n;
		i++;
	}
	return (0);
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
	i = parse_rgb_values(colors, rgb);
	while (*colors)
	{
		free(*colors);
		colors++;
	}
	return (i);
}