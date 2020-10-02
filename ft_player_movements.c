/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_movements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:37:03 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/28 21:34:44 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move_forward(t_ray *ray, int **map, double move_speed)
{
	if (map[(int)(ray->pos_x + ray->dir_x * move_speed)][(int)(ray->pos_y)] != 1)
		ray->pos_x += ray->dir_x * move_speed;
	if (map[(int)(ray->pos_x)][(int)(ray->pos_y + ray->dir_y * move_speed)] != 1)
		ray->pos_y += ray->dir_y * move_speed;
}

void	player_move_backward(t_ray *ray, int **map, double move_speed)
{
	if (map[(int)(ray->pos_x - ray->dir_x * move_speed)][(int)(ray->pos_y)] != 1)
		ray->pos_x -= ray->dir_x * move_speed;
	if (map[(int)(ray->pos_x)][(int)(ray->pos_y - ray->dir_y * move_speed)] != 1)
		ray->pos_y -= ray->dir_y * move_speed;
}

void	player_move_left(t_ray *ray, int **map, double move_speed)
{
	if (map[(int)(ray->pos_x - ray->dir_y * move_speed)][(int)(ray->pos_y)] != 1)
		ray->pos_x -= ray->dir_y * move_speed;
	if (map[(int)(ray->pos_x)][(int)(ray->pos_y + ray->dir_x * move_speed)] != 1)
		ray->pos_y += ray->dir_x * move_speed;
}

void	player_move_right(t_ray *ray, int **map, double move_speed)
{
	if (map[(int)(ray->pos_x + ray->dir_y * move_speed)][(int)(ray->pos_y)] != 1)
		ray->pos_x += ray->dir_y * move_speed;
	if (map[(int)(ray->pos_x)][(int)(ray->pos_y - ray->dir_x * move_speed)] != 1)
		ray->pos_y -= ray->dir_x * move_speed;
}
