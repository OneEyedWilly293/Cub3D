/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:35:20 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/10 03:20:33 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* CHECK MAP PLAYER START DIRECTION/ FACE DIRECTION  */
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
// ======= ERROR MESSAGE REGARDING TEXUTES =======
# define INVALID_DUP_TEX "Invalid: Duplicate texture identifier\n"
# define INVALID_MISSING_TEX "Invalid: Missing texture identifier\n"
# define INVALID_TEX_EXT_MSG "Invalid: texture extension: Use '*.png' file\n"
// ======= ERROR MESSAGE REGARDING MAPS =======
# define META_AFTER_MAP_MSG "Invalid: Element after map started\n"
# define EMPTY_LINE_IN_MAP_MSG "Invalid: Empty line inside map\n"
# define INVALID_MAP_CHAR_MSG "Invalid character in map\n"
# define PLAYER_COUNT_MSG "Invalid number of players\n"
# define MAP_OPEN_MSG "Map is not closed\n"

/* Color struct */
typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

/* texture struct */
/* rendering can later read 'game->tex.no' etc */
typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_textures;

/* game struct */
typedef struct	s_game
{
	t_color	floor;
	t_color	ceiling;
	t_textures	tex;

	char	**map;	/* padded grid with spaces*/
	int		map_w;
	int		map_h;

	int		player_found; /* 0 = not found, 1 = found */
	char	player_dir; /* 'N', 'S', 'E', 'W' */
	int		player_x;	/* cell x index in grid */
	int		player_y;	/* cell y index in grid */
}	t_game;

void	ft_putstr_err(const char *s);
int		ft_error(const char *msg);
int		check_args(int argc, char **argv);
void	get_line_reset(void);
char	*get_line(int fd);
int	parse_rgb_line(char identifier, char *line, int *rgb);
char	*skip_spaces(char *s);
// int	find_color_lines(int fd, t_game *game);
int	handle_color_line(t_game *game, char *trim);
// int	find_texture_lines(int fd, t_game *game);
int	handle_texture_line(t_game *game, char *trim);
int	is_map_charset(char c);
int	parse_identifiers_until_map(int fd, t_game *game, char **first_line);
int	read_map(int fd, t_game *game, char *first_line);
void	free_map(char **map);
int	validate_map(t_game *game);
int	parse_scene(const char *path, t_game *game);
void	init_parser_game(t_game *g);
void	free_parser_game(t_game *game);
int		validate_map_closed(t_game *g);

#endif
