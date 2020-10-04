/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_movements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:37:03 by cduvivie          #+#    #+#             */
/*   Updated: 2020/10/04 20:04:17 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move_forward(t_ray *r, int **map, double move_speed)
{
	if (map[(int)(r->pos_x + r->dir_x * move_speed)][(int)(r->pos_y)] != 1)
		r->pos_x += r->dir_x * move_speed;
	if (map[(int)(r->pos_x)][(int)(r->pos_y + r->dir_y * move_speed)] != 1)
		r->pos_y += r->dir_y * move_speed;
}

void	player_move_backward(t_ray *r, int **map, double move_speed)
{
	if (map[(int)(r->pos_x - r->dir_x * move_speed)][(int)(r->pos_y)] != 1)
		r->pos_x -= r->dir_x * move_speed;
	if (map[(int)(r->pos_x)][(int)(r->pos_y - r->dir_y * move_speed)] != 1)
		r->pos_y -= r->dir_y * move_speed;
}

void	player_move_left(t_ray *r, int **map, double move_speed)
{
	if (map[(int)(r->pos_x - r->dir_y * move_speed)][(int)(r->pos_y)] != 1)
		r->pos_x -= r->dir_y * move_speed;
	if (map[(int)(r->pos_x)][(int)(r->pos_y + r->dir_x * move_speed)] != 1)
		r->pos_y += r->dir_x * move_speed;
}

void	player_move_right(t_ray *r, int **map, double move_speed)
{
	if (map[(int)(r->pos_x + r->dir_y * move_speed)][(int)(r->pos_y)] != 1)
		r->pos_x += r->dir_y * move_speed;
	if (map[(int)(r->pos_x)][(int)(r->pos_y - r->dir_x * move_speed)] != 1)
		r->pos_y -= r->dir_x * move_speed;
}
