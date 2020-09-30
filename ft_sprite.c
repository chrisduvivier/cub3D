/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:07:01 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/30 12:23:17 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites(t_vars *vars, t_sprite **sprites, int size)
{
	t_sprite *tmp;
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = i;
		while (j-1 >= 0 && sprites[j]->distance > sprites[j-1]->distance)
		{
			tmp = sprites[j];
			sprites[j] = sprites[j-1];
			sprites[j-1] = tmp;
			j--;
		}
		i++;
	}
}

/*
**	Return the order of sprites sorted based on distance.
*/

void	ft_sprite_order(t_vars *vars, t_sprite **sprites, int size)
{
	int 	i;

	i = 0;
	while (i < size)
	{
		sprites[i]->distance = (
			(vars->ray.posX - sprites[i]->x) * (vars->ray.posX - sprites[i]->x)
	  		+ (vars->ray.posY - sprites[i]->y) * (vars->ray.posY - sprites[i]->y));
		i++;
	}
	sort_sprites(vars, sprites, size);
}