/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:32:30 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/30 12:36:53 by cduvivie         ###   ########.fr       */
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

# define MAX_SCREEN_WIDTH 5120
# define MAX_SCREEN_HEIGHT 2880

# define NUM_WALL_TEXTURES 6
# define NUM_SPRITES 0

# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40
# define BYTES_PER_PIXEL 3
# define BMP_FILENAME "output.bmp"

# define ERROR_CUB_FILE "Error\nInvalid .cub file\n"
# define ERROR_CUB_RES "Error\nInvalid resolution in .cub file\n\
see: 'R width height' where width and height must be positive\n"
# define ERROR_CUB_RES_NUM_PARAM "Error\nInvalid number of parameters for \
resolution in .cub file\n see: 'R width height'\n"
# define ERROR_RGB "Error\n@get_color_from_mapfile: .cub file has RGB value \
out of range\n"
# define ERROR_TEXTURE_FILE "Error\n@get_texture_filename: Could not find texture file\n"
# define ERROR_ARG "Error\nUnrecognized arguments were passed\n\
see: 'a.out map.cub --save'\n"
# define ERROR_RUN "Error\ncub3d: Run with a .cub file as argument\n\
see: 'a.out map.cub'\n"
# define ERROR_MALLOC "Error\ncub3d: Memory allocation failed\n"
# define ERROR_BMP_WRITE "Error\ncub3d: failed to write to bmp file\n"
# define ERROR_INVALID_MAP_ELEM "Error\nInvalid character found in the map\n\
  List of valid char: '0', '1', '2', ' ', 'N', 'S', 'W', 'E' \n"
# define ERROR_PLAYER_POS "Error\nPlayer position has to be unique in the map\n"

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

typedef unsigned char t_byte;

typedef struct  s_ray {
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double 		moveSpeed;
	double 		rotSpeed;
	int			setupDone;
}               t_ray;

typedef struct  s_ray_sprite {
	int			*sprite_order;
}               t_ray_sprite;

/*
**	used for img put on to window, and TEXTURE
**	texture keeps the img struct and keep the height, width of the texture
*/

typedef struct  s_img {
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	unsigned long	width;
	unsigned long	height;
}               t_img;

typedef struct 	s_sprite {
	double x;
	double y;
	int texture;
	double distance;
}				t_sprite;

/*
**	boolean values to check if all arguments were passed in the cub file.
*/

typedef struct 	s_map_arg
{
	int			r;
	int			no;
	int			so;
	int			we;
	int			ea;
	int			s;
	int			c;
	int			f;
}				t_map_arg;

typedef struct 	s_map
{
	int			res_w;
	int			res_h;
	char		**tab;
	char		*texture_north;
	char		*texture_south;
	char		*texture_west;
	char		*texture_east;
	char		*texture_sprite;
	int			rgb_floor;
	int			rgb_ceiling;
	t_img		walls[NUM_WALL_TEXTURES - 1];
	t_sprite	**sprites;
	int			**map;
	int			height;
	int			width;
	int			start_read_map;
	t_map_arg	map_arg;
	t_list		*head;
	t_list		*head_sprite;
	int			num_sprite;
}				t_map;

typedef struct  	s_vars {
	void        	*mlx;
	void        	*win;
	t_map			map;
	t_ray       	ray;
	t_ray_sprite	ray_sprite;
	t_img       	img[2];
	int				current_img; 
	char			*f_line;
	int				bmp_done;
}               	t_vars;

// int worldMap[mapWidth][mapHeight];

/*
**	Init
*/

t_ray		t_ray_init(void);
t_img		t_img_init(t_vars vars);
void		s_map_arg_init(t_map *map);
void		t_map_init(t_vars *vars, int argc, char *argv[]);
t_vars		t_vars_init(int argc, char *argv[]);

/*
**  Map (cub file) reader functions
*/

int			check_start_map(t_map *map);
int			check_arg(t_vars *vars, t_map *map, char type);
void		get_map_resolution(t_vars *vars, t_map **map, char *line);
void		read_cub_param(t_vars *vars, t_map *map, char *line);
void		read_cub_map(t_vars *vars, char *line);

char		*get_texture_filename(t_vars *vars, char *line, char type);
void		texture_load(t_vars *vars);

/*
**  Color functions
*/

int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
int			add_shade(double distance, int color);
int			get_color_from_mapfile(t_vars *vars, char *line);

/*
**  Draw helper functions
*/

void			my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
unsigned int 	my_mlx_pixel_get(t_img img, int x, int y);
void			ft_mlx_draw_line(t_vars *vars, int x, 
					int drawStart, int drawEnd, unsigned int *buffer);
int				ft_draw(t_vars *vars);

/*
**  Hook functions
*/

int			key_press_hook(int keycode, t_vars *vars);
int	        destroy_window_hook(t_vars *vars);

/*
**	Window function
*/

int 		clear_window(t_vars *vars);

/*
**	BMP
*/

void		ft_handle_bmp(int argc, char *argv[], t_vars *vars);
void    	ft_create_bmp_file(t_vars *vars);

/*
**	CREATE MAP 
*/

void	    process_cub_map(t_vars *vars);
void 	    malloc_cub_map(t_vars *vars, int height, int width);
void		parse_cub_map(t_vars *vars, int height, int width, t_list *head);

/*
**	Sprites
*/

void	add_sprite(t_vars *vars, int y, int x, char spriteNum);
void	set_up_sprite_array(t_vars *vars, t_list *head, int size);
void	ft_sprite_order(t_vars *vars, t_sprite **sprites, int size);
void	sort_sprites(t_vars *vars, t_sprite **sprites, int size);

/*
** ft_player_movements
*/

void	player_move_forward(t_ray *ray, int **map, double moveSpeed);
void	player_move_backward(t_ray *ray, int **map, double moveSpeed);
void	player_move_left(t_ray *ray, int **map, double moveSpeed);
void	player_move_right(t_ray *ray, int **map, double moveSpeed);

void	player_rot_right(t_ray *ray, double rotSpeed);
void	player_rot_left(t_ray *ray, double rotSpeed);

/*
**	Clear and Exit function
*/

void		exit_cub3d(t_vars *vars, char* my_error_text, char *file, int line);

#endif 