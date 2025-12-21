/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:35:20 by jgueon            #+#    #+#             */
/*   Updated: 2025/12/21 20:16:44 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

// include <cub3d.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
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
# define INVALID_RGB_CHAR_MSG "Only numeric characters are accepted\n"
# define INVALID_RGB_VALUE_MSG "Invalid amount of rgb values\n"
# define INVALID_RGB_RANGE_MSG "The rgb value must be in the range of [0~255]\n"

void	ft_putstr_err(const char *s);
int		ft_error(const char *msg);
int		check_args(int argc, char **argv);
char	*get_line(int fd);
int	is_digit(char c);
int	is_str_digits(const char *s);
int get_nb_comma(char *line);
int	ft_atoi_pos(const char *s);
int	arrlen(char **arr);
static int	has_nl(const char *s);

#endif
