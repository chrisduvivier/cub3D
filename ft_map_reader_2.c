/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_reader_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:11:42 by cduvivie          #+#    #+#             */
/*   Updated: 2020/10/04 20:10:50 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	check if the line is the 1st line of the Map and is valid.
*/

int			first_line_of_map(char *line)
{
	char	*ptr;

	ptr = line;
	while (ptr && *ptr)
	{
		if (ft_isdigit(*ptr))
			return (1);
		ptr++;
	}
	return (0);
}

/*
**	skip over alphabet (NO, WE, S, etc.) and space and get the texture's path.
*/

char		*get_texture_filename(t_vars *vars, char *line, char type)
{
	char	*filename;

	check_arg(vars, &(vars->map), type);
	while (ft_isalpha(*line) && (*line != '.'))
		line++;
	while (ft_isspace(*line))
		line++;
	if (!(filename = ft_strdup(line)))
		exit_cub3d(vars, ERROR_TEXTURE_FILE, __FILE__, __LINE__);
	return (filename);
}

void		sprite_load(t_vars *vars)
{
	int		width;
	int		height;

	vars->map.walls[4].img = mlx_xpm_file_to_image(vars->mlx,
			vars->map.texture_sprite, &width, &height);
	vars->map.walls[4].addr = mlx_get_data_addr(vars->map.walls[4].img,
		&vars->map.walls[4].bits_per_pixel,
		&vars->map.walls[4].line_length, &vars->map.walls[4].endian);
}

/*
**	Load texture from the cleaned path read from map.
**	Keep the width and height (even though in our case
**	they are all the same so tech. no need)
**	https://github.com/Denis2222/wolf3d/blob/master/texture.c
**
**	N: 0 / S:1 / W:2 / E:3
*/

void		texture_load(t_vars *vars)
{
	int		width;
	int		height;
	int		num;

	num = 0;
	vars->map.walls[0].img = mlx_xpm_file_to_image(vars->mlx,
			vars->map.texture_north, &width, &height);
	vars->map.walls[1].img = mlx_xpm_file_to_image(vars->mlx,
			vars->map.texture_south, &width, &height);
	vars->map.walls[2].img = mlx_xpm_file_to_image(vars->mlx,
			vars->map.texture_west, &width, &height);
	vars->map.walls[3].img = mlx_xpm_file_to_image(vars->mlx,
			vars->map.texture_east, &width, &height);
	while (num < 4)
	{
		vars->map.walls[num].addr = mlx_get_data_addr(vars->map.walls[num].img,
			&vars->map.walls[num].bits_per_pixel,
			&vars->map.walls[num].line_length, &vars->map.walls[num].endian);
		num++;
	}
	sprite_load(vars);
}
