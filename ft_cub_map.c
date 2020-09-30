/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 12:22:42 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/30 22:28:28 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		**malloc_cub_map(t_vars *vars, int height, int width)
{
	int i;
	int	**res;

	i = 0;
	if ((res = (int **)malloc(height * sizeof(int *))) == NULL)
		exit_cub3d(vars, ERROR_MALLOC, __FILE__, __LINE__);
	while (i < height)
	{
		if ((res[i] = (int *)malloc(width * sizeof(int))) == NULL)
			exit_cub3d(vars, ERROR_MALLOC, __FILE__, __LINE__);
		i++;
	}
	return (res);
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
**	Creates MAP[HEIGHT][WIDTH] from the content stored in the linkedlist.
*/

void	parse_cub_map(t_vars *vars, int height, int width, t_list *head)
{
	t_list 	*node;
	char	*line;
	int		i;
	int		j;

	j = 0;
	node = head;
	while (node != NULL && j < height)
	{
		i = 0;
		line = (char *)node->content;
		printf("MAP: ");
		while (i < width)
		{
			// printf("%c", line[i]);
			if (line[i] == '0' || line[i] == ' ')
				vars->map.map[j][i] = 0;
			else if (line[i] == '1')
				vars->map.map[j][i] = 1;
			else if (line[i] == '2')
			{
				add_sprite(vars, i, j, line[i]);
				vars->map.map[j][i] = 0;
			}
			else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			{
				set_player_position(vars, i, j, line[i]);
				vars->map.map[j][i] = 0;
			}
			else if (!line[i])
			{
				while (i < width)
				{
					vars->map.map[j][i++] = 0;
					printf("%i", vars->map.map[j][i]);
				}
			}
			else
				exit_cub3d(vars, ERROR_INVALID_MAP_ELEM, __FILE__, __LINE__);	
			printf("%i", vars->map.map[j][i]);
			i++;
		}
		printf("\n");
		j++;
		node = node->next;
	}
}

/*
**	DFS algorithm
*/

void	check_neighbor(t_vars *vars, int x, int y)
{	
	if (x < 0 || x >= vars->map.width || y < 0 || y >= vars->map.height)
		exit_cub3d(vars, ERROR_INVALID_MAP, __FILE__, __LINE__);
	if (vars->map.visited[y][x] == 1)
		return ;
	vars->map.visited[y][x] = 1;
	if (vars->map.map[y][x] == 1)
		return ;
	else if (vars->map.map[y][x] == 0)
	{
		check_neighbor(vars, x-1, y);
		check_neighbor(vars, x+1, y);
		check_neighbor(vars, x, y-1);
		check_neighbor(vars, x, y+1);
	}
}

/*
**	exist if invalid. 
*/

void	check_map_validity(t_vars *vars, int **map, int max_height, int max_width)
{
	int x;
	int y;
	
	vars->map.visited = malloc_cub_map(vars, max_height, max_width);
	x = 0;
	y = 0;
	while (y < max_height)
	{
		x = 0;
		while (x < max_width)
		{
			vars->map.visited[y][x] = 0;
			x++;
		}
		y++;
	}
	x = vars->ray.posX;
	y = vars->ray.posY;
	
	check_neighbor(vars, y, x);
}

/*
**	- Create the map (malloc)
**	- Copy map content from cub.file (stored in the linked list)
**		- Check for valid map content
*/

void    process_cub_map(t_vars *vars)
{
	vars->map.map = malloc_cub_map(vars, vars->map.height, vars->map.width);
	parse_cub_map(vars, vars->map.height, vars->map.width, vars->map.head);
	set_up_sprite_array(vars, vars->map.head_sprite, vars->map.num_sprite);
	check_map_validity(vars, vars->map.map, vars->map.height, vars->map.width);
}