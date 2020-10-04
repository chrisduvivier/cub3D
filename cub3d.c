/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:32:00 by cduvivie          #+#    #+#             */
/*   Updated: 2020/10/05 00:54:22 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char *argv[])
{
	t_vars	vars;

	vars = t_vars_init(argc, argv);
	ft_handle_bmp(argc, argv, &vars);
	mlx_expose_hook(vars.win, ft_raycasting, &vars);
	mlx_hook(vars.win, 2, 0L, key_press_hook, &vars);
	mlx_hook(vars.win, 17, 0L, destroy_window_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
