/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:08:33 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/08 19:19:26 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"

//MOVE TO utils later OR DELETE IF NOT USED
int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/**
 * This function converts the initial portion of the string pointed to by str
 * to an integer representation. It skips all white-space characters at the
 * beginning, takes an optional plus or minus sign followed by as many digits
 * as possible, and interprets them as a numerical value.
 * ft_atoi - Converts a string to an integer
 *
 * @param str: The string to be converted
 * @return The converted integer value
 */
int	ft_dan_atoi(const char *str)
{
	int		sign;
	int		result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

static int	is_signed_number(char *s)
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

/*
** Returns 1 if a t_color is already assigned (not -1,-1,-1 anymore)
*/
static int	is_color_set(t_color c)
{
	return (c.r != -1 && c.g != -1 && c.b != -1);
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
		if (!is_signed_number(color[i]))
			return (ft_error(INVALID_RGB_CHAR_MSG));
		n = ft_dan_atoi(color[i]);
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
		return (ft_error("RGB: NULL input\n"));
	if (line[0] != identifier)
		return (ft_error("RGB: wrong identifier\n"));;
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
** Helper: verifies there is something after the identifier.
** Example valid: "F 0,0,255"
** Example invalid: "F"
*/
static int	is_color_line(char *trim)
{
	int	i;

	i = 1;
	while (trim[i] == ' ' || trim[i] == '\t')
		i++;
	if (trim[i] == '\0')
		return (0);
	if (trim[i] < '0' || trim[i] > '9')
		return (0);
	return (1);
}


/*
** Store parsed RGB into game struct.
** This MUST be called, otherwise game stays at -1,-1,-1.
*/
static void store_color(t_game *game, char id, int *tmp)
{
	if (id == 'F')
	{
		game->floor.r = tmp[0];
		game->floor.g = tmp[1];
		game->floor.b = tmp[2];
	}
	else
	{
		game->ceiling.r = tmp[0];
		game->ceiling.g = tmp[1];
		game->ceiling.b = tmp[2];
	}
}

/*
** Called after EOF: both identifiers must exist
*/
static int	check_missing_colors(t_game *game)
{
	if (!is_color_set(game->floor) && !is_color_set(game->ceiling))
		return (ft_error(BOTH_IDEN_MISSING));
	if (!is_color_set(game->floor))
		return (ft_error(INVALID_MISSING_FLOOR));
	if (!is_color_set(game->ceiling))
		return (ft_error(INVALID_MISSING_CEIL));
	return (0);
}

/*
** Handle ONE trimmed line if it is an F or C identifier.
** - Duplicated detection
** - parse_rgb_line validation
** - Store into game
*/
int	handle_color_line(t_game *game, char *trim)
{
	int	tmp[3];

	if (trim[0] == 'F' && !is_color_line(trim))
		return (ft_error("Invalid floor color format\n"), -1);
	if (trim[0] == 'C' && !is_color_line(trim))
		return (ft_error("Invalid ceiling color format\n"), -1);
	if (trim[0] == 'F' && is_color_line(trim))
	{
		if (is_color_set(game->floor))
			return (ft_error(INVALID_DUP_FLOOR), -1);
		if (parse_rgb_line('F', trim, tmp))
			return (-1);
		store_color(game, 'F', tmp);
	}
	else if (trim[0] == 'C' && is_color_line(trim))
	{
		if (is_color_set(game->ceiling))
			return (ft_error(INVALID_DUP_CEIL), -1);
		if (parse_rgb_line('C', trim, tmp))
			return (-1);
		store_color(game, 'C', tmp);
	}
	return (1);
}

/*
** Reads the file and apply the helpers.
*/
// int	find_color_lines(int fd, t_game *game)
// {
// 	char	*line;
// 	char	*trim;

// 	game->floor.r = game->floor.g = game->floor.b = -1;
// 	game->ceiling.r = game->ceiling.g = game->ceiling.b = -1;
// 	line = get_line(fd);
// 	while (line)
// 	{
// 		trim = skip_spaces(line);
// 		if (handle_color_line(game, trim))
// 			return (free(line), 1);
// 		free(line);
// 		line = get_line(fd);
// 	}
// 	return (check_missing_colors(game));
// }

