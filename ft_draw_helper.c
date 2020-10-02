/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 10:17:39 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/30 10:20:15 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;
	t_img	i;

	i = vars->img[vars->current_img];
	dst = i.addr + (y * i.line_length + x * (i.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int	my_mlx_pixel_get(t_img img, int x, int y)
{
	unsigned int	color;
	char			*ptr;

	ptr = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	color = *(unsigned int *)ptr;
	return (color);
}

/*
**	Draws a vertical line, from top to bottom and put each pixel to img
*/

void			ft_mlx_draw_line(t_vars *vars, int x, int draw_start,
								int draw_end, unsigned int *buffer)
{
	int 	y;
	int 	rgb_ceiling;
	int 	rgb_floor;

	y = 0;
	rgb_ceiling = RGB_CEILING;
	rgb_floor = RGB_FLOOR;
	while (y < draw_start)
		my_mlx_pixel_put(vars, x, y++, rgb_ceiling);
	while (y <= draw_end)
	{
		my_mlx_pixel_put(vars, x, y, buffer[y]);
		y++;
	}
	while (y <= vars->map.res_h)
		my_mlx_pixel_put(vars, x, y++, rgb_floor);
}
