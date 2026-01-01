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
#define MAPX  20	//map width
#define MAPY  8	//map height
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
	int		mx;
	int		my;
	int		mp;
	int		dof;
	int		center_x;
	int		center_y;
	float	h_rx;
	float	h_ry;
	float	v_rx;
	float	v_ry;
	float	ra;
	float	xo;
	float	yo;
	float	dist_h;
	float	dist_v;
} t_raycast;

typedef struct s_game {
	mlx_t		*mlx;
	t_player	*player;
	mlx_image_t	*img_map;
	mlx_image_t	*img_3d;
	int			*map;
	int         window_width;
	int         window_height;
	int         map_width;
	int         map_height;
	int			tile_size;
	t_raycast	ray;
} t_game;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color);
void drawray(void *param);
void drawMap2D(void *param);
void drawMap3D(void *param);
void drawPlayer(void *param);
void ft_hook(void* param);
void update(void* param);
void resize_callback(int32_t new_width, int32_t new_height, void *param);

#endif
