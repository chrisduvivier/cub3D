/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:32:00 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/24 13:59:17 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  gcc -Wextra -Wall libmlx.a -framework OpenGl -framework AppKit -lz -L minilibx_opengl_20191021/ cub3d.c draw.c colors_1.c colors_2.c
*/

#include "cub3d.h"

/*
**	main function. The commented lines are probaly of no use.
*/

int			main(int argc, char *argv[])
{
	t_vars      vars;

	vars = t_vars_init(argc, argv);
	// ft_handle_bmp(argc, argv, &vars);
	mlx_expose_hook(vars.win, ft_draw, &vars);
	mlx_hook(vars.win, 2, 0L, key_press_hook, &vars); //keyPress Hook for ALL keys
	mlx_hook(vars.win, 17, 0L, destroy_window_hook, &vars); //Destroy Window
	mlx_loop(vars.mlx);
	return (0);
}

