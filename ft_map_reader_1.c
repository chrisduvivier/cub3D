/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_reader_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:11:42 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/26 12:31:22 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	check whether all arguments were given before proceeding to the map file.
*/

int			check_start_map(t_map *map)
{
	return (map->map_arg.r && map->res_h != -1 && map->res_w != -1 &&
		map->map_arg.c && map->rgb_ceiling != -1 &&
		map->map_arg.f && map->rgb_floor != -1 &&
		map->map_arg.ea && map->texture_east &&
		map->map_arg.we && map->texture_west &&
		map->map_arg.no && map->texture_north &&
		map->map_arg.so && map->texture_south &&
		map->map_arg.s && map->texture_sprite);
}

/*
**	Check if the argument was already given in the cub file.
**	value are set to 1 once the arg is passed.
**	exit if the argument is duplicated
*/

int			check_arg(t_vars *vars, t_map *map, char type)
{
	printf("==== check_arg ====\n");
	if (type == 'R' && (!map->map_arg.r))
		map->map_arg.r = 1;
	else if (type == 'N' && (!map->map_arg.no))
		map->map_arg.no = 1;
	else if (type == 'S' && (!map->map_arg.so))
		map->map_arg.so = 1;
	else if (type == 'W' && (!map->map_arg.we))
		map->map_arg.we = 1;
	else if (type == 'E' && (!map->map_arg.ea))
		map->map_arg.ea = 1;
	else if (type == 's' && (!map->map_arg.s))
		map->map_arg.s = 1;
	else if (type == 'C' && (!map->map_arg.c))
		map->map_arg.c = 1;
	else if (type == 'F' && (!map->map_arg.f))
		map->map_arg.f = 1;
	else
		exit_cub3d(vars, ERROR_CUB_FILE, __FILE__, __LINE__);
	return (1);
}

/*
**	read from line the given resolution
**	If it exceeds the max width or height, set to allowed max.
*/

void		get_map_resolution(t_vars *vars, t_map **map, char *line)
{
	line++;
	if (!(*line) || !check_arg(vars, *map, 'R'))
		exit_cub3d(vars, ERROR_CUB_RES, __FILE__, __LINE__);
	ft_skip_space(&line);
	if (!(*line) || !(ft_isdigit(*line)))
		exit_cub3d(vars, ERROR_CUB_RES, __FILE__, __LINE__);
	if (((*map)->res_w = ft_atoi_w_p((const char **)&line)) == 0)
		exit_cub3d(vars, ERROR_CUB_RES, __FILE__, __LINE__);
	ft_skip_space(&line);
	if (!(*line) || !(ft_isdigit(*line)))
		exit_cub3d(vars, ERROR_CUB_RES, __FILE__, __LINE__);
	if (((*map)->res_h = ft_atoi_w_p((const char **)&line)) == 0)
		exit_cub3d(vars, ERROR_CUB_RES, __FILE__, __LINE__);
	ft_skip_space(&line);
	if (*line)
		exit_cub3d(vars, ERROR_CUB_RES_NUM_PARAM, __FILE__, __LINE__);
	if ((*map)->res_w > MAX_SCREEN_WIDTH)
		(*map)->res_w = MAX_SCREEN_WIDTH;
	if ((*map)->res_w > MAX_SCREEN_HEIGHT)
		(*map)->res_w = MAX_SCREEN_HEIGHT;
}

/*
**	@param: char *l correspond to one line (gnl) from the mapfile
**	read map arguments as long as `map->start_read_map` is set to 0.
**	This is set to 1 once all arguments are read (path,texture,colors)
*/

void		read_cub_param(t_vars *vars, t_map *map, char *l)
{
	printf("==== read_cub_param ====\n");
	if (!l && map->start_read_map != 0)
		return ;
	if (l[0] == 'R' && (ft_isdigit(l[1]) || ft_isspace(l[1])))
		get_map_resolution(vars, &map, l);
	else if (l[0] == 'N' && l[1] == 'O' && (l[2] == '.' || ft_isspace(l[2])))
		map->texture_north = get_texture_filename(vars, l, 'N');
	else if (l[0] == 'S' && l[1] == 'O' && (l[2] == '.' || ft_isspace(l[2])))
		map->texture_south = get_texture_filename(vars, l, 'S');
	else if (l[0] == 'W' && l[1] == 'E' && (l[2] == '.' || ft_isspace(l[2])))
		map->texture_west = get_texture_filename(vars, l, 'W');
	else if (l[0] == 'E' && l[1] == 'A' && (l[2] == '.' || ft_isspace(l[2])))
		map->texture_east = get_texture_filename(vars, l, 'E');
	else if (l[0] == 'S' && (l[1] == '.' || ft_isspace(l[1])))
		map->texture_sprite = get_texture_filename(vars, l, 's');
	else if (l[0] == 'F' && check_arg(vars, map, 'F'))
		map->rgb_floor = get_color_from_mapfile(vars, ++l);
	else if (l[0] == 'C' && check_arg(vars, map, 'C'))
		map->rgb_ceiling = get_color_from_mapfile(vars, ++l);
	else if (ft_isdigit(l[0]))
		map->start_read_map = check_start_map(map);
	else
		exit_cub3d(vars, ERROR_CUB_FILE, __FILE__, __LINE__);
}

/*
**	Copy the line returned by gnl if the line is not empty.	
**	Add the copied line into Node and add to list.
**	Set the width and height of the map
*/

void		read_cub_map(t_vars *vars, char *line)
{
	char 			*map_line;
	unsigned int 	map_len;
	t_list			*node;
	
	printf("==== read_cub_map ====\n");
	printf("==== line:[%s] ====\n", line);
	if (*line)
	{
		map_line = ft_strdup(line);
		map_len = ft_strlen(map_line);
		if ((node = ft_lstnew(map_line)) == NULL)
			exit_cub3d(vars, ERROR_MALLOC, __FILE__, __LINE__);
		ft_lstadd_back(&(vars->map.head), node);
		vars->map.height++;
		vars->map.width = (map_len > vars->map.width) ? map_len : vars->map.width;
	}
}
