/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:32:30 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/26 17:40:30 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

# include "mlx.h"
# include "keys.h"
# include "libft/libft.h"

# define screenWidth 1280
# define screenHeight 960
# define mapWidth 24
# define mapHeight 24

/*
**	dimensions of textures
*/

#define texWidth 64
#define texHeight 64

# define RGB_Red create_trgb(0, 255, 0, 0);
# define RGB_Green create_trgb(0, 0, 255, 0);
# define RGB_Blue create_trgb(0, 0, 0, 255);
# define RGB_White create_trgb(0, 255, 255, 255);
# define RGB_Yellow create_trgb(0, 255, 255, 0);

# define RGB_CEILING create_trgb(0, 0, 0, 0);
# define RGB_FLOOR create_trgb(0, 45, 45, 45);

typedef struct  s_ray {
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double 		moveSpeed; //the constant value is in squares/second
	double 		rotSpeed;
}               t_ray;

typedef struct  s_img {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}               t_img;

typedef struct 	s_map
{
	int			*map;
	int			height;
	int			width;
	int			res_w;
	int			res_h;
	char		*texture_north;
	char		*texture_south;
	char		*texture_west;
	char		*texture_east;
	char		*texture_sprite;
	int			rgb_floor;
	int			rgb_ceiling;
}				t_map;

typedef struct  s_vars {
	void        *mlx;
	void        *win;
	int			done;
	t_map		map;
	t_ray       ray;
	int			current_img;
	t_img       img[2];
}               t_vars;


/*
**  Color functions
*/

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		add_shade(double distance, int color);

/*
**  Draw functions
*/

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
void	ft_mlx_draw_line(t_vars *vars, int x, int drawStart, int drawEnd, int color);
int		ft_draw(t_vars *vars);

/*
**  Hook functions
*/

int			key_press_hook(int keycode, t_vars *vars);

#endif 