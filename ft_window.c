/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 13:14:04 by cduvivie          #+#    #+#             */
/*   Updated: 2020/10/04 23:44:44 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**  Clear both images and then clear window with mlx functions.
**  Clear the textures and the sprite as well if exists.
*/

int		clear_window(t_vars *vars)
{
	int i;

	i = 0;
	if (vars->img[0].img)
		mlx_destroy_image(vars->mlx, vars->img[0].img);
	if (vars->img[1].img)
		mlx_destroy_image(vars->mlx, vars->img[1].img);
	while (i < 5)
	{
		if (vars->map.walls[i].img)
			mlx_destroy_image(vars->mlx, vars->map.walls[i].img);
		i++;
	}
	if (vars->mlx && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}
