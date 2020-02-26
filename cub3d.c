/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:32:00 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/26 14:44:43 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  gcc -Wextra -Wall libmlx.a -framework OpenGl -framework AppKit -lz -L minilibx_opengl_20191021/ cub3d.c draw.c colors_1.c colors_2.c
*/

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
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	return (img);
}

void		line_to_map(t_map *map, char *line)
{
	if (line)
	{
		if (line[0] == 'R')
		{
			printf("line [%s]\n", line);
			line++;
			map->res_w = ft_atoi_w_p(&line);
			map->res_h = ft_atoi_w_p(&line);
		}
		printf("res_w [%d] | res_h [%d]\n", map->res_w, map->res_h);
	}
}

t_map		t_map_init(int argc, char *argv[])
{
	t_map	map;
	int 	fd;
	char 	*line;
	int		res;
	
	if (argc >= 2 && argv[1])
	{
		printf("argv[1]= [%s]\n", argv[1]);
		if ((fd = open(argv[1], O_RDONLY)) > 0)
		{
			// while there is something in line (since it returns 0 when done reading)
			while ((res = get_next_line(fd, &line)) > 0 || *line)
			{
				printf("---------[%c]\n", *line);
				line_to_map(&map, line);
				// printf("---------[%c]\n", *line);
				free(line);
			}
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