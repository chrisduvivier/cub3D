/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:34:34 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/24 14:19:39 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		create_trgb(int t, int r, int g, int b)
{
	printf("create_trgb\n");
	return (t << 24 | r << 16 | g << 8 | b);
}

int		get_t(int trgb)
{
	return (trgb & 0xFF000000);
}

int		get_r(int trgb)
{
	return (trgb & 0xFF0000);
}

int		get_g(int trgb)
{
	return (trgb & 0xFF00);
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}
