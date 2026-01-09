#ifndef CUB3D_H
#define CUB3D_H

# include "../lib/libft/include/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <limits.h>
// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
# include <stdint.h>
# include "../../lib/libft/include/libft.h"

#define WIN_W  1024 
#define WIN_H  1024 
#define MINIMAP_SIZE 200

#define MAP_W (WIN_W / 2)
#define MAP_H (WIN_H / 2)
#define GRIDX  32	//map width-- change to gridx
#define GRIDY  16	//map height
					// #define TILE_SIZE (MAP_W / MAPX)   // Size of each tile (in pixels)
#define PLAYER_SIZE 10   // Size of player (in pixels)
#define PLAYER_SPEED 0.1  // Size of player (in pixels)
#define MOUSE_SENSITIVITY 0.0009

#define MAX_DOF 8 
#define NUM_RAYS  30
#define FOV        (M_PI / 3)

#define RED			0xFF0000FF
#define GREEN		0x00FF00FF
#define BLUE		0x0000FFFF
#define BLACK		0x000000FF
#define WHITE		0xFFFFFFFF
#define TRANSPARENT 0x00000000
#define SKY_BLUE	0x87CEEBFF
#define DARK_SKY  	0x4682B4FF
#define GRASS     	0x228B22FF
#define DIRT      	0x8B4513FF

typedef struct s_player {
	float	x;
	float	y;
	int		xPos;
	int		yPos;
	float	dx;
	float	dy;
	float	da;
	float	move_x;
	float	move_y;
	char	face;
} t_player;

typedef struct s_raycast{
	int		map_x;
	int		map_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		side;
} t_raycast;

typedef	struct s_map2d {
	double	scale_x;
	double	scale_y;
	int		tile;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		p_px;
	int		p_py;
} t_map2d;

typedef struct s_miniray {
	double	start_angle;
	double	angle_step;
	double	ray_angle;
	double	ray_dist;
	double	x;
	double	y;
	double	rx;
	double	ry;
	double	px;
	double	py;
} t_miniray;

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_textures;

typedef struct s_game {
	bool		show_map;
	bool		mouse;
	mlx_t		*mlx;
	t_player	player;
	mlx_image_t	*img_map;
	mlx_image_t	*img_3d;
	// int			*map;
	int         window_width;
	int         window_height;
	int         map_width;
	int         map_height;
	int			tile_size;
	t_raycast	ray;
	t_miniray	m_ray;
	t_map2d		map2d;

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
} t_game;

int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void		draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color);
void		drawray(void *param);
void		draw_map2d(void *param);
void		draw_map3d(void *param);
void		draw_player(t_game *game);
void		draw_map2d_map(t_game *game);
void		draw_ray_minimap(t_game *g);
void		draw_border(t_game *game);
void		ft_hook(void* param);
void		game_loop(void* param);
void		resize_callback(int32_t new_width, int32_t new_height, void *param);
double		cast_ray(double ray_angle, t_game *g);
void		init_ray_struct(double ray_angle, t_game *g);
void		key_hook(mlx_key_data_t keydata, void *param);
void		init_mouse(t_game *game);
void		mouse_hook(double xpos, double ypos, void *param);
void		clear_image(mlx_image_t *img, uint32_t color);

void		up_down(t_game *game);
void		left_right(t_game *game);
void		horizontal_rotation(t_game *game);
void		vertical_rotation(t_game *game);
void		render_background(t_game *game, int32_t new_width, int32_t new_height);

int create_img(t_game *game, mlx_image_t **image, int width, int height);
int	set_color(t_game *game, int visible, int invisible);
int get_texture(t_game *game);

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

void	ft_putstr_err(const char *s);
int		ft_error(const char *msg);
int		check_args(int argc, char **argv);
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
