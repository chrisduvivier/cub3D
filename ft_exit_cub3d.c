/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_cub3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:27:52 by cduvivie          #+#    #+#             */
/*   Updated: 2020/10/05 01:57:41 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_free_2d_array(int **map, int size)
{
	int i;

	i = 0;
	if (map)
	{
		while (i < size)
		{
			if (map[i])
				free(map[i]);
			i++;
		}
		free(map);
	}
}

void		free_t_map(t_map *map)
{
	if (map->texture_east)
		free(map->texture_east);
	if (map->texture_north)
		free(map->texture_north);
	if (map->texture_south)
		free(map->texture_south);
	if (map->texture_west)
		free(map->texture_west);
	if (map->texture_sprite)
		free(map->texture_sprite);
	if (map->head)
		ft_lstclear(&(map->head), free);
	if (map->map)
		ft_free_2d_array(map->map, map->height);
	if (map->visited)
		ft_free_2d_array(map->visited, map->height);
	if (map->head_sprite)
		ft_lstclear(&(map->head), free);
	if (map->sprites)
		free(map->sprites);
}

void		free_t_vars(t_vars *vars)
{
	if (vars)
	{
		free_t_map(&(vars->map));
		if (vars->ray.buffer_y)
			free(vars->ray.buffer_y);
		if (vars->ray.buffer_z)
			free(vars->ray.buffer_z);
	}
	if (vars->f_line)
		free(vars->f_line);
}

/*
**	exit cub3d program after freeing allocated memory.
**	@param vars: struct
**	@param my_error_text: non 0 (null) string if specific
**						  error message to print.
**	To check for leaks, add line:
**	system("leaks a.out > leaks.txt");
*/

void		exit_cub3d(t_vars *vars, int my_error_text, char *file, int line)
{
	ft_printf("\033[0;31m");
	if (!my_error_text)
		ft_printf("Error\n%s\n", strerror(errno));
	else
		ft_put_my_error_text(my_error_text);
	if (file && line)
		ft_printf("Program exited in [%s] at line [%d]\n", file, line);
	ft_printf("\033[0m");
	destroy_window_hook(vars);
	exit(0);
}
