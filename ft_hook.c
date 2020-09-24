/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:47:59 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/24 19:52:25 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int        destroy_window_hook(t_vars *vars)
{
    t_ray *r;

	r = &(vars->ray);
    printf("The window was closed\n");
    clear_window(vars);
    exit (0);
}