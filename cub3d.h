/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:32:30 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/19 15:38:03 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include <stdio.h>
# include <math.h>

# include "mlx.h"
# include "keys.h"

# define screenWidth 1280
# define screenHeight 960
# define mapWidth 24
# define mapHeight 24

# define RGB_Red create_trgb(0, 255, 0, 0);
# define RGB_Green create_trgb(0, 0, 255, 0);
# define RGB_Blue create_trgb(0, 0, 0, 255);
# define RGB_White create_trgb(0, 255, 255, 255);
# define RGB_Yellow create_trgb(0, 255, 255, 0);

/*
**  Color functions
*/

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		add_shade(double distance, int color);

#endif 