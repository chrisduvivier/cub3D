/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_reader_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:11:42 by cduvivie          #+#    #+#             */
/*   Updated: 2020/03/03 17:53:11 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	skip over alphabet (NO, WE, S, etc.) and space and get the texture's path.
*/

char		*get_texture(t_vars *vars, char *line, char type)
{
	char	*filename;

	printf("==== get_texture ====\n");
	check_arg(vars, &(vars->map), type);
	while (ft_isalpha(*line) && (*line != '.'))
		line++;
	while (ft_isspace(*line))
		line++;
	if (!(filename = ft_strdup(line)))
		exit_cub3d(vars, ERROR_TEXTURE_FILE, __FILE__, __LINE__);
	return (filename);
}
