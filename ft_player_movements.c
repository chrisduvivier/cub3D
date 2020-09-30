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

void	player_move_forward(t_ray *ray, int **map, double moveSpeed)
{
	if (map[(int)(ray->posX + ray->dirX * moveSpeed)][(int)(ray->posY)] != 1)
		ray->posX += ray->dirX * moveSpeed;
	if (map[(int)(ray->posX)][(int)(ray->posY + ray->dirY * moveSpeed)] != 1)
		ray->posY += ray->dirY * moveSpeed;
}

void	player_move_backward(t_ray *ray, int **map, double moveSpeed)
{
	if (map[(int)(ray->posX - ray->dirX * moveSpeed)][(int)(ray->posY)] != 1)
		ray->posX -= ray->dirX * moveSpeed;
	if (map[(int)(ray->posX)][(int)(ray->posY - ray->dirY * moveSpeed)] != 1)
		ray->posY -= ray->dirY * moveSpeed;
}

void	player_move_left(t_ray *ray, int **map, double moveSpeed)
{
	if (map[(int)(ray->posX - ray->dirY * moveSpeed)][(int)(ray->posY)] != 1)
		ray->posX -= ray->dirY * moveSpeed;
	if (map[(int)(ray->posX)][(int)(ray->posY + ray->dirX * moveSpeed)] != 1)
		ray->posY += ray->dirX * moveSpeed;
}

void	player_move_right(t_ray *ray, int **map, double moveSpeed)
{
	if (map[(int)(ray->posX + ray->dirY * moveSpeed)][(int)(ray->posY)] != 1)
		ray->posX += ray->dirY * moveSpeed;
	if (map[(int)(ray->posX)][(int)(ray->posY - ray->dirX * moveSpeed)] != 1)
		ray->posY -= ray->dirX * moveSpeed;
}
