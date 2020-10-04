/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_my_error_text.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 00:07:29 by cduvivie          #+#    #+#             */
/*   Updated: 2020/10/05 00:38:44 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_my_error_text(int my_error_text)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (my_error_text == ERROR_CUB_FILE)
		ft_putstr_fd("Invalid .cub file\n", STDERR_FILENO);
	else if (my_error_text == ERROR_CUB_RES)
		ft_putstr_fd("Invalid resolution in .cub file\n", STDERR_FILENO);
	else if (my_error_text == ERROR_CUB_RES_NUM_PARAM)
		ft_putstr_fd("Invalid num parameters for res\n", STDERR_FILENO);
	else if (my_error_text == ERROR_RGB)
		ft_putstr_fd("RGB value out of range\n", STDERR_FILENO);
	else if (my_error_text == ERROR_TEXTURE_FILE)
		ft_putstr_fd("Could not find texture file\n", STDERR_FILENO);
	else if (my_error_text == ERROR_ARG)
		ft_putstr_fd("Unrecognized arguments were passed\n", STDERR_FILENO);
	else if (my_error_text == ERROR_RUN)
		ft_putstr_fd("Run with a .cub file as argument\n", STDERR_FILENO);
	else if (my_error_text == ERROR_MALLOC)
		ft_putstr_fd("Memory allocation failed\n", STDERR_FILENO);
	else if (my_error_text == ERROR_BMP_WRITE)
		ft_putstr_fd("failed to write to bmp file\n", STDERR_FILENO);
	else if (my_error_text == ERROR_INVALID_MAP_ELEM)
		ft_putstr_fd("nvalid character found in the map:\n", STDERR_FILENO);
	else if (my_error_text == ERROR_PLAYER_POS)
		ft_putstr_fd("Player position has to be unique\n", STDERR_FILENO);
	else if (my_error_text == ERROR_INVALID_MAP)
		ft_putstr_fd("The map must be closed by walls\n", STDERR_FILENO);
}
