/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_vars_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:07:20 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/29 13:59:22 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	t_ray contains the player's camera info, which is used to cast the ray
**	params:
**	@posX, posY: x and y starting position
**	@dirX, dirY: initial direction vector
**	@planeX, planeY: the 2d raycaster version of camera plane
**	@moveSpeed, rotSpeed: speed in squares/second
*/

t_ray		t_ray_init(void)
{
	t_ray	ray;

	ray.posX = 0;
	ray.posY = 0;
	ray.dirX = -1;
	ray.dirY = 0;
	ray.planeX = 0;
	ray.planeY = 0.66;
	ray.moveSpeed = 0.3;
	ray.rotSpeed = 0.15;
	ray.setupDone = 0;
	return (ray);
}

/*
**	Initialize image
*/

t_img		t_img_init(t_vars vars)
{
	t_img	img;

	img.img = mlx_new_image(vars.mlx, vars.map.res_w, vars.map.res_h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
						&img.line_length, &img.endian);
	return (img);
}

/*
**	Initialize map argument to 0. Used to check if all args are passed.
*/

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

/*
**	map initializer. proceed if given argument has `.cub` filename
**	FLOW: read cub_param -> cub_map
**	while gnl:  read map parameters until all of them are given.
**				proceed to read map once all others are given
*/

void		t_map_init(t_vars *vars, int argc, char *argv[])
{
	int		fd;
	int		res;

	if (argc >= 2 && argv[1] && ft_check_file_extension(argv[1], ".cub"))
	{
		s_map_arg_init(&(vars->map));
		vars->map.head = NULL;
		vars->map.head_sprite = NULL;
		vars->map.num_sprite = 0;
		if (!((fd = open(argv[1], O_RDONLY)) >= 0))
			exit_cub3d(vars, 0, __FILE__, __LINE__);
		while ((res = get_next_line(fd, &vars->f_line)) > 0 || *(vars->f_line))
		{
			if (!vars->map.start_read_map)
				read_cub_param(vars, &(vars->map), vars->f_line);
			if (vars->map.start_read_map)
				read_cub_map(vars, vars->f_line);
			free(vars->f_line);
		}
		if (res < 0)
			exit_cub3d(vars, 0, __FILE__, __LINE__);
	}
	else
		exit_cub3d(vars, ERROR_RUN, __FILE__, __LINE__);
}

/*
**	Start from getting the map info
*/

t_vars		t_vars_init(int argc, char *argv[])
{
	t_vars	vars;

	t_map_init(&vars, argc, argv);
	vars.ray = t_ray_init();
	process_cub_map(&vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.map.res_w, vars.map.res_h, "ray_cast");
	vars.img[0] = t_img_init(vars);
	vars.img[1] = t_img_init(vars);
	vars.current_img = 0;
	vars.bmp_done = 1;
	texture_load(&vars);
	return (vars);
}
