/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:32:00 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/28 14:19:37 by cduvivie         ###   ########.fr       */
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
	if (vars->f_line)
		free(vars->f_line);
}

/*
**	exit cub3d program after freeing allocated memory.
**	@param vars: struct
**	@param manual: non 0 value if the error message was prompt at the caller.
*/

void		exit_cub3d(t_vars *vars, int my_error_text)
{
	if (!my_error_text)
		ft_printf("Error\n%s\n", strerror(errno));
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

void		get_map_res(t_vars *vars, t_map **map, char *line)
{
	printf("--- get_map_res ---\n");
	while (*line && ft_isspace(line))
		line++;
	(*map)->res_w = ft_atoi_w_p((const char **)&line);
	(*map)->res_h = ft_atoi_w_p((const char **)&line);
}

/*
**	skip over alphabet (NO, WE, S, etc.) and space and get the texture's path.
*/

char		*get_texture(t_vars *vars, char *line)
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
**	exit if one of the value exceeds the defined range.
*/

int			get_color(t_vars *vars, char *line)
{
	char **tab;
	int	r;
	int	g;
	int	b;
	
	if (ft_isspace(*line))
		line++;
	r = ft_atoi_w_p((const char **)&line);
	line++;
	g = ft_atoi_w_p((const char **)&line);
	line++;
	b = ft_atoi_w_p((const char **)&line);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_putstr_fd(ERROR_RGB, STDERR_FILENO);
		exit_cub3d(vars, MY_ERROR_MESSAGE);
	}
	return (create_trgb(0, r, g, b));
}

/*
**	check whether all arguments were given before proceeding to the map file.
*/

int			check_start_map(t_map *map)
{
	return (map->map_arg.r && map->res_h != -1 && map->res_w != -1 &&
		map->map_arg.c && map->rgb_ceiling != -1 &&
		map->map_arg.f && map->rgb_floor != -1 &&
		map->map_arg.ea && map->texture_east &&
		map->map_arg.we && map->texture_west &&
		map->map_arg.no && map->texture_north &&
		map->map_arg.so && map->texture_south &&
		map->map_arg.s && map->texture_sprite);
}

/*
**	Check if the argument was already given in the cub file.
**	value are set to 1 once the arg is passed.
*/

int			check_arg(t_vars *vars, t_map *map, char type)
{
	printf("==== check_arg ====\n");
	if (type == 'R' && (!map->map_arg.r))
		map->map_arg.r = 1;
	else if (type == 'N' && (!map->map_arg.no))
		map->map_arg.no = 1;
	else if (type == 'S' && (!map->map_arg.so))
		map->map_arg.so = 1;
	else if (type == 'W' && (!map->map_arg.we))
		map->map_arg.we = 1;
	else if (type == 'E' && (!map->map_arg.ea))
		map->map_arg.ea = 1;
	else if (type == 's' && (!map->map_arg.s))
		map->map_arg.s = 1;
	else if (type == 'C' && (!map->map_arg.c))
		map->map_arg.c = 1;
	else if (type == 'F' && (!map->map_arg.f))
		map->map_arg.f = 1;
	else 
	{
		printf("HERE\n");
		ft_putstr_fd(ERROR_CUB_FILE, STDERR_FILENO);
		exit_cub3d(vars, MY_ERROR_MESSAGE);
	}
	return (1);
}

void		read_cub_param(t_vars *vars, t_map *map, char *line)
{
	printf("==== read_cub_param ====\n");
	if (line && map->start_read_map == 0)
	{
		if (line[0] == 'R' && check_arg(vars, map, 'R'))
			get_map_res(vars, &map, line);
		else if (line[0] == 'N' && line[1] == 'O' && check_arg(vars, map, 'N'))
			map->texture_north = get_texture(vars, line);
		else if (line[0] == 'S' && line[1] == 'O' && check_arg(vars, map, 'S'))
			map->texture_south = get_texture(vars, line);
		else if (line[0] == 'W' && line[1] == 'E' && check_arg(vars, map, 'W'))
			map->texture_west = get_texture(vars, line);
		else if (line[0] == 'E' && line[1] == 'A' && check_arg(vars, map, 'E'))
			map->texture_east = get_texture(vars, line);
		else if (line[0] == 'S' && check_arg(vars, map, 's'))
			map->texture_sprite = get_texture(vars, line);
		else if (line[0] == 'F' && check_arg(vars, map, 'F'))
			map->rgb_floor = get_color(vars, ++line);
		else if (line[0] == 'C' && check_arg(vars, map, 'C'))
			map->rgb_ceiling = get_color(vars, ++line);
		else
		{
			map->start_read_map = check_start_map(map);
			printf("check_start_map OK\n");
		}
	}
}

void		read_cub_map(t_vars *vars, t_map *map, char *line)
{
	printf("==== read_cub_map ====\n");
	if (*line)
	{
		
		// printf("read_cub_map\n");
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

void	s_map_arg_init(t_map *map)
{
	map->map_arg.r = 0;
	map->map_arg.no = 0;
	map->map_arg.so = 0;
	map->map_arg.we = 0;
	map->map_arg.ea = 0;
	map->map_arg.s = 0;
	map->map_arg.c = 0;
	map->map_arg.f = 0;
}

void		t_map_init(t_vars *vars, int argc, char *argv[])
{
	int 	fd;
	int		res;

	if (argc >= 2 && argv[1] && ft_check_file_extension(argv[1], ".cub"))
	{
		vars->map.res_h = -1;
		vars->map.res_w = -1;
		vars->map.rgb_ceiling = -1;
		vars->map.rgb_floor = -1;
		s_map_arg_init(&(vars->map));
		if (!((fd = open(argv[1], O_RDONLY)) >= 0))
			exit_cub3d(vars, 0);
		while ((res = get_next_line(fd, &vars->f_line)) > 0 || *(vars->f_line))
		{
			printf("\nvars->line=[%s]\n", vars->f_line);
			if (!vars->map.start_read_map)
			read_cub_param(vars, &(vars->map), vars->f_line);
			if (vars->map.start_read_map)
				read_cub_map(vars, &(vars->map), vars->f_line);
			free(vars->f_line);
		}
		if (res < 0)
			exit_cub3d(vars, 0);
		// printf("res_w [%d]\nres_h [%d]\n", vars->map.res_w, vars->map.res_h);
		// printf("texture_east [%s]\n", vars->map.texture_east);
		// printf("texture_north [%s]\n", vars->map.texture_north);
		// printf("texture_south [%s]\n", vars->map.texture_south);
		// printf("map->texture_west [%s]\n", vars->map.texture_west);
		// printf("map->texture_sprite [%s]\n", vars->map.texture_sprite);
	}
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
	t_map_init(&vars, argc, argv);
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