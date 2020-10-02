/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:07:01 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/30 12:35:53 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	append sprite to the list. Count number of sprites in map.
*/

void	add_sprite(t_vars *vars, int y, int x, char sprite_num)
{
	t_list			*node;
	t_sprite		*sprite;

	if ((sprite = (t_sprite*)malloc(sizeof(t_sprite))) == NULL)
		exit_cub3d(vars, ERROR_MALLOC, __FILE__, __LINE__);
	sprite->x = x + 0.5;
	sprite->y = y + 0.5;
	sprite->texture = (int)(sprite_num - '0');
	if ((node = ft_lstnew(sprite)) == NULL)
		exit_cub3d(vars, ERROR_MALLOC, __FILE__, __LINE__);
	ft_lstadd_back(&(vars->map.head_sprite), node);
	vars->map.num_sprite++;
}

/*
**	Load the sprites from the linked list to a array of sprites
*/

void	set_up_sprite_array(t_vars *vars, t_list *head, int size)
{
	t_list		*node;
	t_sprite	*sprite;
	int			i;

	if (!(vars->map.sprites = (t_sprite **)malloc(sizeof(t_sprite*) * size)))
		exit_cub3d(vars, ERROR_MALLOC, __FILE__, __LINE__);
	node = head;
	i = 0;
	while (node != NULL && i < size)
	{
		sprite = (t_sprite *)(node->content);
		vars->map.sprites[i] = sprite;
		node = node->next;
		i++;
	}
}

/*
**	Insertion sort
*/

void	sort_sprites(t_sprite **sprites, int size)
{
	t_sprite	*tmp;
	int			i;
	int			j;

	i = 0;
	while (i < size)
	{
		j = i;
		while (j - 1 >= 0 && sprites[j]->distance > sprites[j - 1]->distance)
		{
			tmp = sprites[j];
			sprites[j] = sprites[j - 1];
			sprites[j - 1] = tmp;
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
	int		i;
	t_ray	ray;

	i = 0;
	ray = vars->ray;
	while (i < size)
	{
		sprites[i]->distance = (
			(ray.pos_x - sprites[i]->x) * (ray.pos_x - sprites[i]->x) +
			(ray.pos_y - sprites[i]->y) * (ray.pos_y - sprites[i]->y));
		i++;
	}
	sort_sprites(sprites, size);
}
