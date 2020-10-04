/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:32:30 by cduvivie          #+#    #+#             */
/*   Updated: 2020/10/05 00:57:19 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

# include "mlx.h"
# include "keys.h"
# include "libft/libft.h"

# define MAX_SCREEN_WIDTH 5120
# define MAX_SCREEN_HEIGHT 2880
# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40
# define BYTES_PER_PIXEL 3
# define BMP_FILENAME "output.bmp"
# define NUM_IMG_FILES 5
# define TEXWIDTH 64
# define TEXHEIGHT 64

# define ERROR_CUB_FILE 1
# define ERROR_CUB_RES 2
# define ERROR_CUB_RES_NUM_PARAM 3
# define ERROR_RGB 4
# define ERROR_TEXTURE_FILE 5
# define ERROR_ARG 6
# define ERROR_RUN 7
# define ERROR_MALLOC 8
# define ERROR_BMP_WRITE 9
# define ERROR_INVALID_MAP_ELEM 10
# define ERROR_PLAYER_POS 11
# define ERROR_INVALID_MAP 12

typedef unsigned char	t_byte;

/*
**	DDA and variables needed for drawing walls, sprite.
*/

typedef struct		s_dda {
	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				texture_num;
	int				texture_x;
	int				texture_y;
	double			texture_step;
	double			texture_pos;
	unsigned int	color;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				draw_start_y;
	int				draw_end_y;
	int				tex_x;
	int				tex_y;
}					t_dda;

/*
**	Variables specifically for raycasting.
**	buffer_z is used for sprites: contains the distance to the wall of
**	every vertical stripe.Z
*/

typedef struct		s_ray {
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rot_speed;
	int				setup_done;
	unsigned int	*buffer_y;
	double			*buffer_z;
	t_dda			dda;
}					t_ray;

typedef struct		s_ray_sprite {
	int				*sprite_order;
}					t_ray_sprite;

/*
**	used for img put on to window, and TEXTURE
**	texture keeps the img struct and keep the height, width of the texture
*/

typedef struct		s_img {
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	unsigned long	width;
	unsigned long	height;
}					t_img;

typedef struct		s_sprite {
	double			x;
	double			y;
	int				texture;
	double			distance;
}					t_sprite;

/*
**	boolean values to check if all arguments were passed in the cub file.
*/

typedef struct		s_map_arg
{
	int				r;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				s;
	int				c;
	int				f;
}					t_map_arg;

typedef struct		s_map
{
	int				res_w;
	int				res_h;
	char			*texture_north;
	char			*texture_south;
	char			*texture_west;
	char			*texture_east;
	char			*texture_sprite;
	int				rgb_floor;
	int				rgb_ceiling;
	t_img			walls[NUM_IMG_FILES];
	t_sprite		**sprites;
	int				**map;
	int				height;
	int				width;
	int				start_read_map;
	t_map_arg		map_arg;
	t_list			*head;
	t_list			*head_sprite;
	int				num_sprite;
	int				**visited;
}					t_map;

typedef struct		s_vars
{
	void			*mlx;
	void			*win;
	t_map			map;
	t_ray			ray;
	t_ray_sprite	ray_sprite;
	t_img			img[2];
	int				current_img;
	char			*f_line;
	int				bmp_done;
}					t_vars;

/*
**	Init functions.
*/

t_ray				t_ray_init(void);
t_img				t_img_init(t_vars vars);
void				s_map_arg_init(t_map *map);
void				t_map_init(t_vars *vars, int argc, char *argv[]);
t_vars				t_vars_init(int argc, char *argv[]);

/*
**  Map (cub file) reader functions
*/

int					check_start_map(t_map *map);
int					first_line_of_map(char *line);
int					check_arg(t_vars *vars, t_map *map, char type);
void				get_map_resolution(t_vars *vars, t_map **map, char *line);
void				read_cub_param(t_vars *vars, t_map *map, char *line);
void				read_cub_map(t_vars *vars, char *line);
char				*get_texture_filename(t_vars *vars, char *line, char type);
void				texture_load(t_vars *vars);

/*
**  Color functions
*/

int					create_trgb(int t, int r, int g, int b);
int					get_t(int trgb);
int					get_r(int trgb);
int					get_g(int trgb);
int					get_b(int trgb);
int					add_shade(double distance, int color);
int					get_color_from_mapfile(t_vars *vars, char *line);

/*
**  Draw helper functions
*/

void				my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
unsigned int		my_mlx_pixel_get(t_img img, int x, int y);
void				ft_mlx_draw_line(t_vars *vars, int x, int draw_start,
								int draw_end);
int					ft_raycasting(t_vars *vars);
void				ft_draw_walls(t_vars *vars, t_ray *ray);
void				ft_draw_sprites(t_vars *vars, t_ray *ray);

/*
**	DDA
*/

void				ft_dda_setup(t_vars *vars, t_ray *r, int x);
void				ft_dda_side_distance(t_ray *r);
void				ft_dda_check_hit(t_vars *vars, t_ray *r);
void				ft_dda_wall_distance(t_vars *vars, t_ray *r, t_dda *d);
void				ft_dda_draw_wall(t_vars *vars, t_ray *r, t_dda *d);

/*
**	Map validity check
*/

void				check_neighbor(t_vars *vars, int x, int y);
void				check_map_validity(t_vars *vars, int max_height,
									int max_width);

/*
**  Hook functions
*/

int					key_press_hook(int keycode, t_vars *vars);
int					destroy_window_hook(t_vars *vars);

/*
**	Window function
*/

int					clear_window(t_vars *vars);

/*
**	BMP
*/

void				ft_handle_bmp(int argc, char *argv[], t_vars *vars);
void				ft_create_bmp_file(t_vars *vars);

/*
**	CREATE MAP
*/

void				process_cub_map(t_vars *vars);
int					**malloc_cub_map(t_vars *vars, int height, int width);
void				parse_cub_map(t_vars *vars, int height, int width,
							t_list *head);

/*
**	Sprites
*/

void				add_sprite(t_vars *vars, int y, int x, char sprite_num);
void				set_up_sprite_array(t_vars *vars, t_list *head, int size);
void				ft_sprite_order(t_vars *vars, t_sprite **sprites,
									int size);
void				sort_sprites(t_sprite **sprites, int size);

/*
** ft_player_movements: rotation, move WASD
*/

void				player_move_forward(t_ray *r, int **map,
									double move_speed);
void				player_move_backward(t_ray *r, int **map,
									double move_speed);
void				player_move_left(t_ray *r, int **map, double move_speed);
void				player_move_right(t_ray *r, int **map, double move_speed);
void				player_rot_right(t_ray *ray, double rot_speed);
void				player_rot_left(t_ray *ray, double rot_speed);

/*
**	Clear and Exit function
*/

void				exit_cub3d(t_vars *vars, int my_error_text, char *file,
							int line);
void				free_t_vars(t_vars *vars);
void                ft_put_my_error_text(int my_error_text);

#endif
