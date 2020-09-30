/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 12:22:42 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/30 11:01:43 by cduvivie         ###   ########.fr       */
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

/*
**	Read direction of the player camera and rotate the view.
**	added 0.5 to player position so that it comes at the center of square
**	TODO: clarify more about the rotation mechanism here
*/

void	set_player_position(t_vars *vars, int y, int x, char c)
{
	if (vars->ray.setupDone == 1)
		exit_cub3d(vars, ERROR_PLAYER_POS, __FILE__, __LINE__);
	vars->ray.posX = x + 0.5;
	vars->ray.posY = y + 0.5;
	if (c == 'N')
		player_rot_right(&(vars->ray), 6.3);
	else if (c == 'W')
		player_rot_right(&(vars->ray), 4.7);
	else if (c == 'S')
		player_rot_right(&(vars->ray), 3.1);
	else if (c == 'E')
		player_rot_right(&(vars->ray), 1.6);
	vars->ray.setupDone = 1;
}

/*
**	append sprite to the list. Count number of sprites in map.
*/

void	add_sprite(t_vars *vars, int y, int x, char spriteNum)
{
	t_list			*node;
	t_sprite		*sprite;

	// printf("==== add_sprite ====\n");
	if ((sprite = (t_sprite*)malloc(sizeof(t_sprite))) == NULL)
		exit_cub3d(vars, ERROR_MALLOC, __FILE__, __LINE__);
	sprite->x = x + 0.5;
	sprite->y = y + 0.5;
	sprite->texture = (int)(spriteNum - '0');
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
	// printf("==== set_up_sprite_array ====\n");

	t_list 		*node;
	t_sprite	*sprite;
	int 		i;

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
**	Creates MAP[HEIGHT][WIDTH] from the content stored in the linkedlist.
*/

void	parse_cub_map(t_vars *vars, int height, int width, t_list *head)
{
	t_list 	*node;
	char	*line;
	int		i;
	int		j;

	// printf("==== parse_cub_map ====\n");
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
				add_sprite(vars, i, j, line[i]);
				vars->map.map[j][i] = 0;
			}
			else if (ft_strchr("NSWE", line[i]) != NULL)
			{
				set_player_position(vars, i, j, line[i]);
				vars->map.map[j][i] = 0;
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
	set_up_sprite_array(vars, vars->map.head_sprite, vars->map.num_sprite);
	// DFS to check validity
}