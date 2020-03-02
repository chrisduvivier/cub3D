/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_reader_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:11:42 by cduvivie          #+#    #+#             */
/*   Updated: 2020/03/02 16:48:19 by cduvivie         ###   ########.fr       */
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

void		get_map_res(t_vars *vars, t_map **map, char *line)
{
	line++;
	if (!(*line) || !(ft_isspace(*line)))
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

void		read_cub_param(t_vars *vars, t_map *map, char *line)
{
	printf("==== read_cub_param ====\n");
	if (line && map->start_read_map == 0)
	{
		if (line[0] == 'R' && check_arg(vars, map, 'R'))
			get_map_res(vars, &map, line);
		else if (line[0] == 'N' && line[1] == 'O' && check_arg(vars, map, 'N'))
			map->texture_north = get_texture(vars, line);
		else if (line[0] == 'S' && line[1] == 'O' && check_arg(vars, map, 'S'))
			map->texture_south = get_texture(vars, line);
		else if (line[0] == 'W' && line[1] == 'E' && check_arg(vars, map, 'W'))
			map->texture_west = get_texture(vars, line);
		else if (line[0] == 'E' && line[1] == 'A' && check_arg(vars, map, 'E'))
			map->texture_east = get_texture(vars, line);
		else if (line[0] == 'S' && check_arg(vars, map, 's'))
			map->texture_sprite = get_texture(vars, line);
		else if (line[0] == 'F' && check_arg(vars, map, 'F'))
			map->rgb_floor = get_color(vars, ++line);
		else if (line[0] == 'C' && check_arg(vars, map, 'C'))
			map->rgb_ceiling = get_color(vars, ++line);
		else
			map->start_read_map = check_start_map(map);
	}
}

/*
**
**
**		TODO
**
**
*/

// void		read_cub_param(t_vars *vars, t_map *map, char *line)
// {
// 	char **tab;

// 	printf("==== SPLIT read_cub_param ====\n");
// 	if (line && map->start_read_map == 0)
// 	{
// 		tab = ft_split_sep(line, SPACE_CHAR);
// 		if (ft_strncmp(tab[0], "R", ft_strlen(tab[0])) == 0)
// 		if (line[0] == 'R' && check_arg(vars, map, 'R'))
// 			get_map_res(vars, &map, line);
// 		else if (line[0] == 'N' && line[1] == 'O' && check_arg(vars, map, 'N'))
// 			map->texture_north = get_texture(vars, line);
// 		else if (line[0] == 'S' && line[1] == 'O' && check_arg(vars, map, 'S'))
// 			map->texture_south = get_texture(vars, line);
// 		else if (line[0] == 'W' && line[1] == 'E' && check_arg(vars, map, 'W'))
// 			map->texture_west = get_texture(vars, line);
// 		else if (line[0] == 'E' && line[1] == 'A' && check_arg(vars, map, 'E'))
// 			map->texture_east = get_texture(vars, line);
// 		else if (line[0] == 'S' && check_arg(vars, map, 's'))
// 			map->texture_sprite = get_texture(vars, line);
// 		else if (line[0] == 'F' && check_arg(vars, map, 'F'))
// 			map->rgb_floor = get_color(vars, ++line);
// 		else if (line[0] == 'C' && check_arg(vars, map, 'C'))
// 			map->rgb_ceiling = get_color(vars, ++line);
// 		else
// 			map->start_read_map = check_start_map(map);
// 	}
// }

void		read_cub_map(t_vars *vars, t_map *map, char *line)
{
	printf("==== read_cub_map ====\n");
	if (*line)
	{
		
		// printf("read_cub_map\n");
	}
}
