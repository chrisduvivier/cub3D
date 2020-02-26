/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:32:00 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/26 18:23:16 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  gcc -Wextra -Wall libmlx.a -framework OpenGl -framework AppKit -lz -L minilibx_opengl_20191021/ cub3d.c draw.c colors_1.c colors_2.c
*/

#include "cub3d.h"

void		exit_cub3d(void)
{
	ft_printf("Error: %s\n", strerror(errno));
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

void		get_texture(t_map **map, char *line, char type)
{
	// TODO: change function to get the string.
	if (type == 'N')
		(*map)->texture_north = ft_atoi_w_p(&line + 2);
	else if (type == 'S')
		(*map)->texture_south = ft_atoi_w_p(&line + 2);
	else if (type == 'W')
		(*map)->texture_west = ft_atoi_w_p(&line + 2);
	else if (type == 'E')
		(*map)->texture_east = ft_atoi_w_p(&line + 2);
	else if (type == 's')
		(*map)->texture_sprite = ft_atoi_w_p(&line + 1);
}

void		line_to_map(t_map *map, char *line)
{
	if (line)
	{
		if (line[0] == 'R')
			get_map_res(&map, line);
		else if (line[0] == 'N' && line[1] == 'O')
			get_texture(&map, line, 'N');
		else if (line[0] == 'S' && line[1] == 'O')
			get_texture(&map, line, 'S');
		else if (line[0] == 'W' && line[1] == 'E')
			get_texture(&map, line, 'W');
		else if (line[0] == 'E' && line[1] == 'A')
			get_texture(&map, line, 'E');
		else if (line[0] == 'S')
			get_texture(&map, line, 's');
		else if (line[0] == 'F')
			{}
		else if (line[0] == 'C')
			{}
		printf("res_w [%d] | res_h [%d]\n", map->res_w, map->res_h);
		printf("texture_east [%s]\n", map->texture_east);
		printf("texture_north [%s]\n", map->texture_north);
		printf("texture_south [%s]\n", map->texture_south);
		printf("map->texture_west [%s]\n", map->texture_west);
		printf("map->texture_sprite [%s]\n", map->texture_sprite);
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

t_map		t_map_init(int argc, char *argv[])
{
	t_map	map;
	int 	fd;
	char 	*line;
	int		res;
	
	if (argc >= 2 && argv[1] && ft_check_file_extension(argv[1], ".cub"))
	{
		if (!((fd = open(argv[1], O_RDONLY)) >= 0))
			exit_cub3d();
		// while there is something in line (since it returns 0 when done reading)
		while ((res = get_next_line(fd, &line)) > 0 || *line)
		{
			line_to_map(&map, line);
			free(line);
		}
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
	vars.map = t_map_init(argc, argv);
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