#include "../includes/game.h"

// void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
// {
// 	int dx;
// 	int dy;
// 	int sx;
// 	int sy;
// 	int err;
//
// 	dx = abs(x1 - x0);
// 	dy = abs(y1 - y0);
// 	sx = 2 * (x0 < x1) -1;
// 	sy = 2 * (y0 < y1) -1;
// 	err = dx - dy;
//
// 	while (1)
// 	{
// 		mlx_put_pixel(img, x0, y0, color);
// 		if (x0 == x1 && y0 == y1)
// 			break;
// 		int e2 = 2 * err;
// 		if (e2 > -dy)
// 		{
// 			err -= dy;
// 			x0 += sx;
// 		}
// 		if (e2 <  dx)
// 		{
// 			err += dx;
// 			y0 += sy;
// 		}
// 	}
// }
