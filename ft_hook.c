/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:47:59 by cduvivie          #+#    #+#             */
/*   Updated: 2020/10/04 00:53:59 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int        destroy_window_hook(t_vars *vars)
{
    t_ray *r;

	r = &(vars->ray);
    clear_window(vars);
	free_t_vars(vars);
    exit (0);
}

int			key_press_hook(int keycode, t_vars *vars)
{
	t_ray *r;

	r = &(vars->ray);
	if (keycode == KEY_ESC)
		destroy_window_hook(vars);
	else if (keycode == KEY_UP)
		player_move_forward(r, vars->map.map, r->move_speed);
	else if (keycode == KEY_DOWN)
		player_move_backward(r, vars->map.map, r->move_speed);
	else if (keycode == KEY_MOVE_LEFT)
		player_move_left(r, vars->map.map, r->move_speed);
	else if (keycode == KEY_MOVE_RIGHT)
		player_move_right(r, vars->map.map, r->move_speed);
	else if (keycode == KEY_LOOK_LEFT)
		player_rot_left(r, r->rot_speed);
	else if (keycode == KEY_LOOK_RIGHT)
		player_rot_right(r, r->rot_speed);
	ft_raycasting(vars);
	return (0);
}
