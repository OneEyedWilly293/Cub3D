/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:08:33 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/12 21:36:05 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		n = ft_atoi(color[i]);
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
		trimmed = ft_strtrim(colors[i], " \t\n\r");
		if (!trimmed)
			return (1);
		free(colors[i]);
		colors[i] = trimmed;
		i++;
	}
	return (0);
}$(SRC_DIR)/utils.c \

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
	char	**colors;
	int		i;

	if (!line || !rgb)
		return (ft_error("RGB: NULL input\n"));
	if (line[0] != identifier)
		return (ft_error("RGB: wrong identifier\n"));
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
** Handle ONE trimmed line if it is an F or C identifier.
** - Duplicated detection
** - parse_rgb_line validation
** - Store into game
*/
int	handle_color_line(t_game *game, char *trim)
{
	int	tmp[3];

	if (trim[0] == 'F' && !is_color_line(trim))
		return (ft_error(INVALID_RGB_VALUE_MSG), -1);
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
