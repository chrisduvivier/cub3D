/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:32:00 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/27 16:19:04 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  gcc -Wextra -Wall libmlx.a -framework OpenGl -framework AppKit -lz -L minilibx_opengl_20191021/ cub3d.c draw.c colors_1.c colors_2.c
*/

#include "cub3d.h"

void		free_t_map(t_map *map)
{
	if (map->texture_east)
		free(map->texture_east);
	if (map->texture_north)
		free(map->texture_north);
	if (map->texture_south)
		free(map->texture_south);
	if (map->texture_west)
		free(map->texture_west);
	if (map->texture_sprite)
		free(map->texture_sprite);
}

void		free_t_vars(t_vars *vars)
{
	if (vars)
	{
		free_t_map(&(vars->map));
	}
}

/*
**	exit cub3d program after freeing allocated memory.
**	@param vars: struct
**	@param manual: non 0 value if the error message was prompt at the caller.
*/

void		exit_cub3d(t_vars *vars, int my_error_text)
{
	if (!my_error_text)
		ft_printf("Error: %s\n", strerror(errno));
	free_t_vars(vars);
	system("leaks a.out > leaks.txt");
	exit(0);
}

t_ray		t_ray_init(void)
{
	t_ray	ray;
	
	ray.posX = 22;
	ray.posY = 12;  //x and y start position
	ray.dirX = -1;
	ray.dirY = 0; //initial direction vector
	ray.planeX = 0;
	ray.planeY = 0.66; //the 2d raycaster version of camera plane
	ray.moveSpeed = 0.3; //the constant value is in squares/second
	ray.rotSpeed = 0.1;
	return (ray);
}

t_img		t_img_init(t_vars vars)
{
	t_img	img;

	img.img = mlx_new_image(vars.mlx, screenWidth, screenHeight);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	return (img);
}

void		get_map_res(t_map **map, char *line)
{
	line++;
	(*map)->res_w = ft_atoi_w_p(&line);
	(*map)->res_h = ft_atoi_w_p(&line);
}

/*
**	skip over alphabet (NO, WE, S, etc.) and space and get the texture's path.
*/

char		*get_texture(t_vars *vars, char *line, char type)
{
	char	*filename;
	
	while (ft_isalpha(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	if (!(filename = ft_strdup(line)))
	{
		ft_putstr_fd(ERROR_TEXTURE_FILE, STDERR_FILENO);
		exit_cub3d(vars, MY_ERROR_MESSAGE);
	}
	return (filename);
}

/*
**	@get_color
**	R,G,B colors (in this order) in range [0,255]: 0, 255, 255
*/

int			get_color(t_vars *vars, char *line)
{
	char **tab;
	int	r;
	int	g;
	int	b;
	
	if (ft_isspace(*line))
		line++;
	r = ft_atoi_w_p(&line);
	line++;
	g = ft_atoi_w_p(&line);
	line++;
	b = ft_atoi_w_p(&line);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_putstr_fd(ERROR_RGB, STDERR_FILENO);
		exit_cub3d(vars, 1);
	}
	return (create_trgb(0, r, g, b));
}

void		line_to_map(t_vars *vars, t_map *map, char *line)
{
	if (line)
	{
		if (line[0] == 'R')
			get_map_res(&map, line);
		else if (line[0] == 'N' && line[1] == 'O')
			map->texture_north = get_texture(vars, line, 'N');
		else if (line[0] == 'S' && line[1] == 'O')
			map->texture_south = get_texture(vars, line, 'S');
		else if (line[0] == 'W' && line[1] == 'E')
			map->texture_west = get_texture(vars, line, 'W');
		else if (line[0] == 'E' && line[1] == 'A')
			map->texture_east = get_texture(vars, line, 'E');
		else if (line[0] == 'S')
			map->texture_sprite = get_texture(vars, line, 's');
		else if (line[0] == 'F')
			map->rgb_floor = get_color(vars, ++line);
		else if (line[0] == 'C')
			map->rgb_ceiling = get_color(vars, ++line);
	}
}

// https://github.com/Denis2222/wolf3d/blob/master/texture.c
// void	texture_load(t_env *e)
// {
// 	int		width;
// 	int		height;

// 	e->wall[0] = mlx_xpm_file_to_image(e->mlx,
// 			"gfx/floor.xpm", &width, &height);
// 	e->wall[1] = mlx_xpm_file_to_image(e->mlx,
// 			"gfx/ceil.xpm", &width, &height);
// 	e->wall[2] = mlx_xpm_file_to_image(e->mlx,
// 			"gfx/blue_brick.xpm", &width, &height);
// 	e->wall[3] = mlx_xpm_file_to_image(e->mlx,
// 			"gfx/blue_brick2.xpm", &width, &height);
// 	e->wall[4] = mlx_xpm_file_to_image(e->mlx,
// 			"gfx/blue_brick3.xpm", &width, &height);
// 	e->wall[5] = mlx_xpm_file_to_image(e->mlx,
// 			"gfx/blue_brick_hi.xpm", &width, &height);
// 	e->wall[6] = mlx_xpm_file_to_image(e->mlx,
// 			"gfx/wall_brown.xpm", &width, &height);
// 	e->wall[7] = mlx_xpm_file_to_image(e->mlx,
// 			"gfx/wall_red1.xpm", &width, &height);
// 	e->wall[8] = mlx_xpm_file_to_image(e->mlx,
// 			"gfx/wall_red2.xpm", &width, &height);
// 	e->wall[9] = mlx_xpm_file_to_image(e->mlx,
// 			"gfx/wall_red_door.xpm", &width, &height);
// 	texture_sprite_load(e);
// }

t_map		t_map_init(t_vars *vars, int argc, char *argv[])
{
	t_map	map;
	int 	fd;
	char 	*line;
	int		res;
	
	if (argc >= 2 && argv[1] && ft_check_file_extension(argv[1], ".cub"))
	{
		if (!((fd = open(argv[1], O_RDONLY)) >= 0))
			exit_cub3d(vars, 0);
		// while there is something in line (since it returns 0 when done reading)
		while ((res = get_next_line(fd, &line)) > 0 || *line)
		{
			line_to_map(vars, &map, line);
			free(line);
		}
		if (res < 0)
			exit_cub3d(vars, 0);
		printf("res_w [%d]\nres_h [%d]\n", map.res_w, map.res_h);
		printf("texture_east [%s]\n", map.texture_east);
		printf("texture_north [%s]\n", map.texture_north);
		printf("texture_south [%s]\n", map.texture_south);
		printf("map->texture_west [%s]\n", map.texture_west);
		printf("map->texture_sprite [%s]\n", map.texture_sprite);
	}
	return (map);
}

t_vars      t_vars_init(int argc, char *argv[])
{
	t_vars	vars;
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "ray_cast");
	vars.done = 0;
	vars.ray = t_ray_init();
	vars.img[0] = t_img_init(vars);
	vars.img[1] = t_img_init(vars);
	vars.current_img = 0;
	vars.map = t_map_init(&vars, argc, argv);
	return (vars);
}

int			main(int argc, char *argv[])
{
	t_vars      vars;

	vars = t_vars_init(argc, argv);
	
	mlx_expose_hook(vars.win, ft_draw(&vars), &vars);
	while (!vars.done)
	{
		// ft_draw(&vars);
		// mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
		// mlx_loop_hook(vars.win, ft_draw(&vars), &vars);
		mlx_hook(vars.win, 2, 0L, key_press_hook, &vars);
		mlx_loop(vars.mlx);
	}
	return (0);
}