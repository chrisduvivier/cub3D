/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 13:14:04 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/23 12:59:13 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**  Clear both images and then clear window with mlx functions
*/

int         clear_window(t_vars *vars)
{
    
    if (vars->img.img)
        mlx_destroy_image(vars->mlx, vars->img.img);
    
    if (vars->mlx && vars->win)
        mlx_destroy_window(vars->mlx, vars->win);
    return (0);
}
