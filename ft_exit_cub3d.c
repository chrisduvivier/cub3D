/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_cub3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:27:52 by cduvivie          #+#    #+#             */
/*   Updated: 2020/03/02 15:17:06 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

void		free_t_vars(t_vars *vars)
{
	if (vars)
	{
		free_t_map(&(vars->map));
	}
	if (vars->f_line)
		free(vars->f_line);
}

/*
**	exit cub3d program after freeing allocated memory.
**	@param vars: struct
**	@param manual: non 0 value if the error message was prompt at the caller.
*/

void		exit_cub3d(t_vars *vars, char *my_error_text, char *file, int line)
{
	ft_printf("\033[0;31m");
	if (!my_error_text)
		ft_printf("Error\n%s\n", strerror(errno));
	else
		ft_putstr_fd(my_error_text, STDERR_FILENO);
	if (file && line)
		ft_printf("Program exited in [%s] at line [%d]\n", file, line);
	ft_printf("\033[0m");
	free_t_vars(vars);
	system("leaks a.out > leaks.txt");
	exit(0);
}
