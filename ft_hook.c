/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:47:59 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/24 19:52:25 by cduvivie         ###   ########.fr       */
/*   Updated: 2020/09/23 12:59:10 by cduvivie         ###   ########.fr       */
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

// int			key_press_hook(int keycode, t_vars *vars)
// {
// 	t_ray *r;

// 	r = &(vars->ray);
// 	if (keycode == KEY_ESC)
// 	{
// 		printf("ESC: Closing the window\n");
// 		vars->done = 1;
// 		// mlx_destroy_window(vars->mlx, vars->win);
// 		exit (0);
// 	}
// 	else if (keycode == KEY_MOVE_LEFT || keycode == KEY_MOVE_RIGHT || keycode == KEY_DOWN || keycode == KEY_UP)
// 	{
// 		// move forward if no wall in front of you
// 		if (keycode == KEY_UP)
// 		{
// 			if (worldMap[(int)(r->posX + r->dirX * r->moveSpeed)][(int)(r->posY)] == 0)
// 				r->posX += r->dirX * r->moveSpeed;
// 			if (worldMap[(int)(r->posX)][(int)(r->posY + r->dirY * r->moveSpeed)] == 0)
// 				r->posY += r->dirY * r->moveSpeed;
// 		}
// 		// move backwards if no wall behind you
// 		if (keycode == KEY_DOWN)
// 		{
// 			if (worldMap[(int)(r->posX - r->dirX * r->moveSpeed)][(int)(r->posY)] == 0)
// 				r->posX -= r->dirX * r->moveSpeed;
// 			if (worldMap[(int)(r->posX)][(int)(r->posY - r->dirY * r->moveSpeed)] == 0)
// 				r->posY -= r->dirY * r->moveSpeed;
// 		}
// 		if (keycode == KEY_MOVE_LEFT)
// 		{
// 			double newDirX;
// 			double newDirY;
// 			newDirX = -(r->dirY);
// 			newDirY = r->dirX;
// 			if (worldMap[(int)(r->posX + newDirX * r->moveSpeed)][(int)(r->posY)] == 0)
// 				r->posX += newDirX * r->moveSpeed;
// 			if (worldMap[(int)(r->posX)][(int)(r->posY + newDirY * r->moveSpeed)] == 0)
// 				r->posY += newDirY * r->moveSpeed;
// 		}
// 		if (keycode == KEY_MOVE_RIGHT)
// 		{
// 			double newDirX;
// 			double newDirY;
// 			newDirX = -(r->dirY);
// 			newDirY = r->dirX;
// 			if (worldMap[(int)(r->posX + newDirX * r->moveSpeed)][(int)(r->posY)] == 0)
// 				r->posX -= newDirX * r->moveSpeed;
// 			if (worldMap[(int)(r->posX)][(int)(r->posY + newDirY * r->moveSpeed)] == 0)
// 				r->posY -= newDirY * r->moveSpeed;
// 		}
// 	}
// 	else if (keycode == KEY_LOOK_LEFT || keycode == KEY_LOOK_RIGHT)
// 	{
// 		//rotate to the left
// 		if (keycode == KEY_LOOK_LEFT)
// 		{
// 			//both camera direction and camera plane must be rotated
// 			double oldDirX = r->dirX;
// 			r->dirX = r->dirX * cos(r->rotSpeed) - r->dirY * sin(r->rotSpeed);
// 			r->dirY = oldDirX * sin(r->rotSpeed) + r->dirY * cos(r->rotSpeed);
// 			double oldPlaneX = r->planeX;
// 			r->planeX = r->planeX * cos(r->rotSpeed) - r->planeY * sin(r->rotSpeed);
// 			r->planeY = oldPlaneX * sin(r->rotSpeed) + r->planeY * cos(r->rotSpeed);
// 			// printf("Ker Press --- keycode: [LEFT]\n");
// 		}
// 		//rotate to the right
// 		if (keycode == KEY_LOOK_RIGHT)
// 		{
// 			//both camera direction and camera plane must be rotated
// 			double oldDirX = r->dirX;
// 			r->dirX = r->dirX * cos(-(r->rotSpeed)) - r->dirY * sin(-(r->rotSpeed));
// 			r->dirY = oldDirX * sin(-(r->rotSpeed)) + r->dirY * cos(-(r->rotSpeed));
// 			double oldPlaneX = r->planeX;
// 			r->planeX = r->planeX * cos(-(r->rotSpeed)) - r->planeY * sin(-(r->rotSpeed));
// 			r->planeY = oldPlaneX * sin(-(r->rotSpeed)) + r->planeY * cos(-(r->rotSpeed));
// 			// printf("Ker Press --- keycode: [RIGHT]\n");
// 		}
// 	}
// 	ft_draw(vars);
// 	return (0);
// }
