/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 12:22:42 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/28 13:25:37 by cduvivie         ###   ########.fr       */
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

void	set_player_position(t_vars *vars, int y, int x, char c)
{
	if (vars->ray.setupDone == 1)
		exit_cub3d(vars, ERROR_PLAYER_POS, __FILE__, __LINE__);
	vars->ray.posX = x;
	vars->ray.posY = y;
	if (c == 'N')
	{
		vars->ray.dirX = 0;
		vars->ray.dirY = 1;
	}
	else if (c == 'S')
	{
		vars->ray.dirX = 0;
		vars->ray.dirY = -1;
	}
	else if (c == 'E')
	{
		vars->ray.dirX = 1;
		vars->ray.dirY = 0;
	}
	else if (c == 'W')
	{
		vars->ray.dirX = -1;
		vars->ray.dirY = 0;
	}
	vars->ray.setupDone = 1;
}

/*
**	append sprite to the list
*/

void	add_sprite(t_vars *vars, int y, int x)
{
	
}

/*
**	Creates MAP[HEIGHT][WIDTH] from the content stored in the linkedlist.
*/

void	parse_cub_map(t_vars *vars, int height, int width, t_list *head)
{
	t_list 	*node;
	char	*line;
	int		i;
	int		j;

	printf("==== parse_cub_map ====\n");
	j = 0;
	node = head;
	while (node != NULL && j < height)
	{
		i = 0;
		line = (char *)node->content;
		printf("MAP: ");
		while (i < width)
		{
			printf("%c", line[i]);
			if (line[i] == '0' || line[i] == ' ')
				vars->map.map[j][i] = 0;
			else if (line[i] == '1')
				vars->map.map[j][i] = 1;
			else if (line[i] == '2')
			{
				//TODO: need to keep them in a array to sort posX posY of sprite for raycasting
				// add_sprite(vars, j, i);
				vars->map.map[j][i] = 2;
			}
			else if (ft_strchr("NSWE", line[i]) != NULL)
			{
				// set_player_position(vars, j, i, line[i]);
			}
			else
				exit_cub3d(vars, ERROR_INVALID_MAP_ELEM, __FILE__, __LINE__);	
			i++;
		}
		printf("\n");
		j++;
		node = node->next;
	}
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