/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:32:00 by cduvivie          #+#    #+#             */
/*   Updated: 2020/03/02 13:44:25 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  gcc -Wextra -Wall libmlx.a -framework OpenGl -framework AppKit -lz -L minilibx_opengl_20191021/ cub3d.c draw.c colors_1.c colors_2.c
*/

#include "cub3d.h"

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

int			main(int argc, char *argv[])
{
	t_vars      vars;

	vars = t_vars_init(argc, argv);
	
	mlx_expose_hook(vars.win, ft_draw, &vars);
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