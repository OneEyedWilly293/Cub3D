#ifndef GAME_H
#define GAME_H

# include "../lib/libft/include/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <limits.h>
// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIN_W  1024 
#define WIN_H  1024 
#define MINIMAP_SIZE 200

#define MAP_W (WIN_W / 2)
#define MAP_H (WIN_H / 2)
#define MAPX  32	//map width
#define MAPY  16	//map height
				// #define TILE_SIZE (MAP_W / MAPX)   // Size of each tile (in pixels)
#define PLAYER_SIZE 10   // Size of player (in pixels)
#define PLAYER_SPEED 0.1  // Size of player (in pixels)
#define CAMERA_SPEED 5
#define MAX_CAMERA 200
#define JUMP_SPEED 0.1      // initial upward speed
#define GRAVITY    0.005    // downward acceleration
#define MAX_JUMP   0.3      // maximum camera height during jump


#define MAX_DOF 8 
#define NUM_RAYS  30
#define FOV        (M_PI / 3)

#define RED		255,   0,   0, 255
#define GREEN	  0, 255,   0, 255
#define BLUE	  0,   0, 255, 255
#define BLACK	  0,   0,   0, 255
#define WHITE	255, 255, 255, 255

typedef struct s_player {
	float	x;
	float	y;
	int		xPos;
	int		yPos;
	float	dx;
	float	dy;
	float	da;
	double	camera;
	int		is_jumping;       // 0 = not jumping, 1 = jumping
	double	jump_velocity; // current vertical speedfloat	camera;
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

typedef struct s_game {
	bool		show_map;
	mlx_t		*mlx;
	t_player	player;
	mlx_image_t	*img_map;
	mlx_image_t	*img_3d;
	int			*map;
	int         window_width;
	int         window_height;
	int         map_width;
	int         map_height;
	int			tile_size;
	t_raycast	ray;
	t_map2d		map2d;
} t_game;

int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void		draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color);
void		drawray(void *param);
void		drawMap2D(void *param);
void		drawMap3D(void *param);
void		draw_player(t_game *game);
void		ft_hook(void* param);
void		update(void* param);
void		resize_callback(int32_t new_width, int32_t new_height, void *param);
double		cast_ray(double ray_angle, t_game *g);
void		init_ray_struct(double ray_angle, t_game *g);
void		key_hook(mlx_key_data_t keydata, void *param);
void		draw_ray_minimap(t_game *g);
void		drawMap2d_map(t_game *game);
void		draw_border(t_game *game);

void		up_down(t_game *game);
void		left_right(t_game *game);
void		horizontal_rotation(t_game *game);
void		vertical_rotation(t_game *game);
void		jump(t_game *game);

#endif
