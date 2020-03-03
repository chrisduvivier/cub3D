/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_vars_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:07:20 by cduvivie          #+#    #+#             */
/*   Updated: 2020/03/03 17:26:03 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
						&img.line_length, &img.endian);
	return (img);
}

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
	int		fd;
	int		res;

	if (argc >= 2 && argv[1] && ft_check_file_extension(argv[1], ".cub"))
	{
		s_map_arg_init(&(vars->map));
		if (!((fd = open(argv[1], O_RDONLY)) >= 0))
			exit_cub3d(vars, 0, __FILE__, __LINE__);
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
			exit_cub3d(vars, 0, __FILE__, __LINE__);
		printf("res_w [%d]\nres_h [%d]\n", vars->map.res_w, vars->map.res_h);
		printf("texture_east [%s]\n", vars->map.texture_east);
		printf("texture_north [%s]\n", vars->map.texture_north);
		printf("texture_south [%s]\n", vars->map.texture_south);
		printf("map->texture_west [%s]\n", vars->map.texture_west);
		printf("map->texture_sprite [%s]\n", vars->map.texture_sprite);
	}
	else
		exit_cub3d(vars, ERROR_RUN, __FILE__, __LINE__);
}

t_vars		t_vars_init(int argc, char *argv[])
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
