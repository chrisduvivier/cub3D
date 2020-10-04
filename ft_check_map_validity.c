/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_validity.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 15:15:09 by cduvivie          #+#    #+#             */
/*   Updated: 2020/10/04 16:08:59 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		check_neighbor(vars, x - 1, y);
		check_neighbor(vars, x + 1, y);
		check_neighbor(vars, x, y - 1);
		check_neighbor(vars, x, y + 1);
	}
}

/*
**	exist if invalid.
*/

void	check_map_validity(t_vars *vars, int max_height, int max_width)
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
	x = vars->ray.pos_x;
	y = vars->ray.pos_y;
	check_neighbor(vars, y, x);
}
