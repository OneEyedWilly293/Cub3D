/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:08:33 by jgueon            #+#    #+#             */
/*   Updated: 2025/12/19 16:00:16 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

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

// FUNCTION TO CHECK RGB VALUES 0~255 and if there is 3 values
// colors must contain exactly 3 numeric strings and then NULL:
// color[0], color[1], color[2], color[3] == NULL
// rgb is an int[3] where we store the result.
static int	parse_rgb_values(char **color, int *rgb)
{
	int	i;

	if (!color || !rgb)
		return (1);
	if (!color[0] || !color[1] || !color[2] || !color[3])
		return (ft_error(INVALID_RGB_VALUE_MSG));
	i = 0;
	while (i < 3)
	{
		if (!is_str_digits(color[i]))
			return (ft_error(INVALID_RGB_CHAR_MSG));
		rgb[i] = ft_atoi_pos(color[i]);
		if (!check_rgb_range(rgb[i]))
			return (ft_error(INVALID_RGB_RANGE_MSG));
		i++;
	}
	return (0);
}


