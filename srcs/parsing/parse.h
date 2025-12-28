/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:35:20 by jgueon            #+#    #+#             */
/*   Updated: 2025/12/28 19:52:13 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

// include <cub3d.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include "../../lib/libft/include/libft.h"

// ======= MAP FEATURES =======
# define MAP_EXTENSION ".cub"
# define N "NO"
# define E "EA"
# define S "SO"
# define W "WE"
# define F "F"
# define C "C"
# define BUFFER_SIZE 100

// ======= ERROR MESSAGES =======
# define FILE_EXT_MSG "Invalid file extension: Use '*.cub' file\n"
# define EMPTY_MSG "Map is empty\n"
# define NO_MAP "No map file provided\n"
# define MANY_ARG_MSG "Too many arguments provided\n"
# define INVALID_ARG_MSG "Invalid parameters entered: program + map required\n"
# define PATH_MSG "There is not a valid path\n"
# define WALL_MSG "Map don't have closed walls\n"
# define WRONG_MSG "Invalid components\n"
# define CANT_OPEN_MAP "Cannot open map file\n"
// ======= ERROR MESSAGE REGARDING COLORS =======
# define INVALID_RGB_CHAR_MSG "Only numeric characters are accepted\n"
# define INVALID_RGB_VALUE_MSG "Invalid amount of rgb values\n"
# define INVALID_RGB_RANGE_MSG "The rgb value must be in the range of [0~255]\n"
# define INVALID_DUP_FLOOR "Invalid: More than one 'F' identifier given\n"
# define INVALID_DUP_CEIL "Invalid: More than one 'C' identifier given\n"
# define INVALID_MISSING_FLOOR "Invalid: Missing 'F' identifier\n"
# define INVALID_MISSING_CEIL "Invalid: Missing 'C' indentifier\n"
# define BOTH_IDEN_MISSING "Both Identifiers 'F' and 'C' are missing\n"

/* Color struct */
typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

/* game struct */
typedef struct	s_game
{
	t_color	floor;
	t_color	ceiling;
}	t_game;

/* errors + args */
void	ft_putstr_err(const char *s);
int		ft_error(const char *msg);
int		check_args(int argc, char **argv);

/* line reader */
char	*get_line(int fd);

/* colors parsing */
int	parse_rgb_line(char identifier, char *line, int *rgb);
char	*skip_spaces(char *s);
int	find_color_lines(int fd, t_game *game);

#endif
