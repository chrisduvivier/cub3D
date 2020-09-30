/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_rotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:20:51 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/28 16:38:09 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_rot_right(t_ray *ray, double rotSpeed)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = ray->dirX;
    ray->dirX = ray->dirX * cos(-(rotSpeed)) - ray->dirY * sin(-(rotSpeed));
    ray->dirY = old_dir_x * sin(-(rotSpeed)) + ray->dirY * cos(-(rotSpeed));
    old_plane_x = ray->planeX;
    ray->planeX = 
        ray->planeX * cos(-(rotSpeed)) - ray->planeY * sin(-(rotSpeed));
    ray->planeY = 
        old_plane_x * sin(-(rotSpeed)) + ray->planeY * cos(-(rotSpeed));
}

void	player_rot_left(t_ray *ray, double rotSpeed)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = ray->dirX;
    ray->dirX = ray->dirX * cos(rotSpeed) - ray->dirY * sin(rotSpeed);
    ray->dirY = old_dir_x * sin(rotSpeed) + ray->dirY * cos(rotSpeed);
    old_plane_x = ray->planeX;
    ray->planeX = ray->planeX * cos(rotSpeed) - ray->planeY * sin(rotSpeed);
    ray->planeY = old_plane_x * sin(rotSpeed) + ray->planeY * cos(rotSpeed);
}
