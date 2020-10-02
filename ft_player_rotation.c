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

void	player_rot_right(t_ray *ray, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = ray->dir_x;
	ray->dir_x = ray->dir_x * cos(-(rot_speed)) - ray->dir_y * sin(-(rot_speed));
	ray->dir_y = old_dir_x * sin(-(rot_speed)) + ray->dir_y * cos(-(rot_speed));
	old_plane_x = ray->plane_x;
	ray->plane_x =
		ray->plane_x * cos(-(rot_speed)) - ray->plane_y * sin(-(rot_speed));
	ray->plane_y =
		old_plane_x * sin(-(rot_speed)) + ray->plane_y * cos(-(rot_speed));
}

void	player_rot_left(t_ray *ray, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = ray->dir_x;
	ray->dir_x = ray->dir_x * cos(rot_speed) - ray->dir_y * sin(rot_speed);
	ray->dir_y = old_dir_x * sin(rot_speed) + ray->dir_y * cos(rot_speed);
	old_plane_x = ray->plane_x;
	ray->plane_x = ray->plane_x * cos(rot_speed) - ray->plane_y * sin(rot_speed);
	ray->plane_y = old_plane_x * sin(rot_speed) + ray->plane_y * cos(rot_speed);
}
