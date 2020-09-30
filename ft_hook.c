/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:47:59 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/30 10:20:54 by cduvivie         ###   ########.fr       */
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

int			key_press_hook(int keycode, t_vars *vars)
{
	t_ray *r;

	r = &(vars->ray);
	if (keycode == KEY_ESC)
	{
		printf("ESC: Closing the window\n");
		// mlx_destroy_window(vars->mlx, vars->win);
		exit (0);
	}
	else if (keycode == KEY_UP)
		player_move_forward(r, vars->map.map, r->moveSpeed);
	else if (keycode == KEY_DOWN)
		player_move_backward(r, vars->map.map, r->moveSpeed);
	else if (keycode == KEY_MOVE_LEFT)
		player_move_left(r, vars->map.map, r->moveSpeed);
	else if (keycode == KEY_MOVE_RIGHT)
		player_move_right(r, vars->map.map, r->moveSpeed);
	else if (keycode == KEY_LOOK_LEFT)
		player_rot_left(r, r->rotSpeed);
	else if (keycode == KEY_LOOK_RIGHT)
		player_rot_right(r, r->rotSpeed);
	ft_draw(vars);
	return (0);
}