/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:34:34 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/26 13:52:49 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	function that accepts a double (distance) and a int (color) as arguments,
**	0 will add no shading to the color whilst 1 will make the color completely dark.
**	0.5 will dim it halfway, and .25 a quarter way.
*/

int		add_shade(double distance, int color)
{
	int b;
	int g;
	int r;
	int t;

	if (distance > 0 && distance <= 1)
	{
		t = get_t(color);
		r = (distance * 0 + (1 - distance) * (get_r(color) >> 16));
		g = (distance * 0 + (1 - distance) * (get_g(color) >> 8));
		b = (distance * 0 + (1 - distance) * (get_b(color) >> 0));
		return (t << 24 | r << 16 | g << 8 | b);
	}
	return (color);
}
