#ifndef CUB3D_H
#define CUB3D_H

# include "../lib/libft/include/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <fcntl.h>
# include <stdint.h>
#include <stdio.h>

#define WIN_W  1024 
#define WIN_H  1024 
#define MINIMAP_SIZE 200
#define MM_CENTER (MINIMAP_SIZE / 2)
#define MM_BORDER_THICKNESS 10
#define MAP_W (WIN_W / 2)
#define MAP_H (WIN_H / 2)
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
# define NO_MAP "No map file provided: program + <map> required\n"
# define MANY_ARG_MSG "Too many arguments provided\n"
# define INVALID_ARG_MSG "Invalid parameters: program + <map> required\n"
# define PATH_MSG "Generic: There is not a valid path\n"
# define WALL_MSG "Map don't have closed walls\n"
# define WRONG_MSG "Invalid components\n"
# define CANT_OPEN_MAP "Cannot open map file\n"
// ======= ERROR MESSAGE REGARDING COLORS =======
# define INVALID_RGB_CHAR_MSG "Only numeric characters are accepted\n"
# define INVALID_RGB_VALUE_MSG "Invalid rgb values\n"
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
# define EMPTY_LINE_IN_MAP "Invalid: Empty line inside map\n"
# define INVALID_MAP_CHAR_MSG "Invalid character in map\n"
# define PLAYER_COUNT_MSG "Invalid number of players\n"
# define MAP_OPEN_MSG "Map is not closed\n"

typedef struct s_player t_player;
typedef struct s_raycast t_raycast ;
typedef	struct s_map2d t_map2d;
typedef struct s_miniray t_miniray;
typedef struct s_color t_color;
typedef struct s_textures t_textures;

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

typedef struct s_game {
	bool		mouse;
	bool		show_map;
	char		**map;	/* padded grid with spaces*/
	char		player_dir; /* 'N', 'S', 'E', 'W' */
	int			tile_size;
	int			map_h;
	int			map_w;
	int			player_found; /* 0 = not found, 1 = found */
	int			player_x;	/* cell x index in grid */
	int			player_y;	/* cell y index in grid */
	int         window_height;
	int         window_width;
	mlx_image_t	*img_3d;
	mlx_image_t	*img_map;
	mlx_t		*mlx;
	t_color		ceiling;
	t_color		floor;
	t_map2d		map2d;
	t_miniray	m_ray;
	t_player	player;
	t_raycast	ray;
	t_textures	tex;
} t_game;

double		cast_ray(double ray_angle, t_game *g);
int			create_img(t_game *game, mlx_image_t **image, int width, int height);
int			get_texture(t_game *game);
// mlx_image_t *get_texture(t_game *game);
int			set_color(t_game *game, int visible, int invisible);
int			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void		clear_image(mlx_image_t *img, uint32_t color);
void		draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color);
void		draw_minimap(void *param);
void		draw_map3d(void *param);
void		draw_player(t_game *game);
void		ft_hook(void* param);
void		game_loop(void* param);
void		horizontal_rotation(t_game *game);
void		init_mouse(t_game *game);
void		key_hook(mlx_key_data_t keydata, void *param);
void		left_right(t_game *game);
void		mouse_hook(double xpos, double ypos, void *param);
void		render_background(t_game *game, int32_t new_width, int32_t new_height);
void		resize_callback(int32_t new_width, int32_t new_height, void *param);
void		up_down(t_game *game);
void		vertical_rotation(t_game *game);

char		*get_line(int fd);
char		*skip_spaces(char *s);
int			check_args(int argc, char **argv);
int			ft_error(const char *msg);
int			validate_map_closed(t_game *g);
int			handle_color_line(t_game *game, char *trim);
int			handle_texture_line(t_game *game, char *trim);
int			is_map_charset(char c);
int			parse_identifiers_until_map(int fd, t_game *game, char **first_line);
int			parse_rgb_line(char identifier, char *line, int *rgb);
int			parse_scene(const char *path, t_game *game);
int			read_map(int fd, t_game *game, char *first_line);
int			validate_map(t_game *game);
void		free_map(char **map);
void		free_parser_game(t_game *game);
void		ft_putstr_err(const char *s);
void		get_line_reset(void);
void		init_parser_game(t_game *g);
#endif
