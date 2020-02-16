/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:47:28 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/16 21:46:40 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  gcc -Wextra -Wall libmlx.a -framework OpenGl -framework AppKit -lz -L minilibx_opengl_20191021/ main.c 
*/

#include "mlx.h"
#include <stdio.h>

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*
**	Transparency: 0xFF000000
**	Red: 0x00FF0000;
**	Green: 0x0000FF00;
**	Blue: 0x000000FF;
*/
int		create_trgb(int t, int r, int g, int b)
{
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
		// printf("original color: [%#x]\n", color);
		// printf("individual color: R[%#x] G[%#x] B[%#x]\n", get_r(color), get_g(color), get_b(color));
		t = get_t(color);
		r = (distance * 0 + (1 - distance) * (get_r(color) >> 16));
		g = (distance * 0 + (1 - distance) * (get_g(color) >> 8));
		b = (distance * 0 + (1 - distance) * (get_b(color) >> 0));
		// printf("shaded individual color: R[%#x] G[%#x] B[%#x]\n", r, g, b);
		// printf("dimmed color: [%#x]\n\n", t << 24 | r << 16 | g << 8 | b);
		return (t << 24 | r << 16 | g << 8 | b);
	}
	else
		return (color);
}

int		get_opposite(int color)
{
	int b;
	int g;
	int r;
	int t;

	// printf("original color: [%#x]\n", color);
	// printf("individual color: R[%#x] G[%#x] B[%#x]\n", get_r(color), get_g(color), get_b(color));
	t = get_t(color);
	r = 0xFF0000 - get_r(color);
	g = 0xFF00 - get_g(color);
	b = 0xFF - get_b(color);
	// printf("inverted individual color: R[%#x] G[%#x] B[%#x]\n", r, g, b);
	// printf("inverted individual color shifted: R[%#x] G[%#x] B[%#x]\n", r << 8, g << 16, b << 24);
	// printf("inverted color: [%#x]\n\n", (t | r | g | b));
	return (t | r | g | b);
}

int     main(void)
{
	void	*mlx;
	void    *mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello, world!");
	img.img = mlx_new_image(mlx, 1920, 1080);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);

	int c = create_trgb(0, 255, 255, 155); // t, r, g, b
	printf("color c:[%#x] \n", c);
	// loop to make a square
	int x = 0;
	int y = 0;
	while (x < 20)
	{
		y = 0;
		while (y < 20)
		{
			if (x > 10 && y > 10)
				my_mlx_pixel_put(&img, x, y++, add_shade(0.5, c));
			else
			{
				my_mlx_pixel_put(&img, x, y++, c);
			}
		}
		x++;
	}
	// my_mlx_pixel_put(&img, 5, 5, c);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
