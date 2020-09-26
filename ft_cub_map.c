/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 12:22:42 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/26 13:00:05 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void     malloc_cub_map(t_vars *vars, int height, int width)
{
	int i;
	t_map *map;

	i = 0;
	map = &(vars->map);
	if ((map->map = (int **)malloc(height * sizeof(int *))) == NULL)
		exit_cub3d(vars, ERROR_MALLOC, __FILE__, __LINE__);
	while (i < height)
	{
		if ((map->map[i] = (int *)malloc(width * sizeof(int))) == NULL)
			exit_cub3d(vars, ERROR_MALLOC, __FILE__, __LINE__);
		i++;
	}
}

void	parse_cub_map(t_vars *vars, int height, int width, t_list *head)
{
	t_list 	*node;
	int		i;
	int		j;

	i = 0;
	j = 0;
	node = head;
// 	while (node != NULL && i < height)
// 	{
		
// 	}
}

/*
**	- Create the map (malloc)
**	- Copy map content from cub.file (stored in the linked list)
**		- Check for valid map content
*/

void    process_cub_map(t_vars *vars)
{
	malloc_cub_map(vars, vars->map.height, vars->map.width);
	parse_cub_map(vars, vars->map.height, vars->map.width, vars->map.head);
}