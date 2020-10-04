/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:47:57 by cduvivie          #+#    #+#             */
/*   Updated: 2020/10/04 23:49:39 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_raycasting(t_vars *vars)
{
	t_ray	*ray;

	ray = &(vars->ray);
	ft_draw_walls(vars, ray);
	ft_draw_sprites(vars, ray);
	mlx_put_image_to_window(vars->mlx, vars->win,
							vars->img[vars->current_img].img, 0, 0);
	if (vars->bmp_done == 0)
	{
		ft_create_bmp_file(vars);
		vars->bmp_done = 1;
	}
	vars->current_img = (vars->current_img == 0) ? 1 : 0;
	return (0);
}

/*
**	1. Perform DDA algorithm for every x in the screen.
**	2. Draw vertical line based on raycasting.
**	3. clear buffer_y used for Walls.
**	4. store perpandicular distance to wall for sprites.
*/

void	ft_draw_walls(t_vars *vars, t_ray *ray)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < vars->map.res_w)
	{
		ft_dda_setup(vars, ray, x);
		ft_dda_side_distance(ray);
		ft_dda_check_hit(vars, ray);
		ft_dda_wall_distance(vars, ray, &(ray->dda));
		ft_dda_draw_wall(vars, ray, &(ray->dda));
		ft_mlx_draw_line(vars, x, ray->dda.draw_start, ray->dda.draw_end);
		while (y < vars->map.res_h)
			ray->buffer_y[y++] = 0;
		ray->buffer_z[x] = ray->dda.perp_wall_dist;
		x++;
	}
}

/*
**	1. translate sprite position to relative to camera.
**	2. calculate inverse camera matrix for correct matrix multiplication.
**	3. transform sprite with the inverse camera matrix.
**	4. calculate height of the sprite on screen.
**	5. calculate lowest and highest pixel to fill in current stripe.
**	6. calculate width of the sprite.
*/

void	ft_sprite_draw_setup(t_vars *vars, t_ray *r, int text_num)
{
	r->dda.sprite_x = vars->map.sprites[text_num]->x - r->pos_x;
	r->dda.sprite_y = vars->map.sprites[text_num]->y - r->pos_y;
	r->dda.inv_det = 1.0 / (r->plane_x * r->dir_y - r->dir_x * r->plane_y);
	r->dda.transform_x = r->dda.inv_det *
					(r->dir_y * r->dda.sprite_x - r->dir_x * r->dda.sprite_y);
	r->dda.transform_y = r->dda.inv_det * (-(r->plane_y) *
						r->dda.sprite_x + r->plane_x * r->dda.sprite_y);
	r->dda.sprite_screen_x = (int)((vars->map.res_w / 2) *
							(1 + r->dda.transform_x / r->dda.transform_y));
	r->dda.sprite_height = abs((int)(vars->map.res_h / (r->dda.transform_y)));
	r->dda.draw_start_y = -(r->dda.sprite_height) / 2 + vars->map.res_h / 2;
	if (r->dda.draw_start_y < 0)
		r->dda.draw_start_y = 0;
	r->dda.draw_end_y = r->dda.sprite_height / 2 + vars->map.res_h / 2;
	if (r->dda.draw_end_y >= vars->map.res_h)
		r->dda.draw_end_y = vars->map.res_h - 1;
	r->dda.sprite_width = abs((int)(vars->map.res_h / (r->dda.transform_y)));
	r->dda.draw_start_x = -(r->dda.sprite_width) / 2 + r->dda.sprite_screen_x;
	if (r->dda.draw_start_x < 0)
		r->dda.draw_start_x = 0;
	r->dda.draw_end_x = r->dda.sprite_width / 2 + r->dda.sprite_screen_x;
	if (r->dda.draw_end_x >= vars->map.res_w)
		r->dda.draw_end_x = vars->map.res_w - 1;
}

/*
**	paint pixel if it isn't black, black is the invisible color
*/

void	ft_sprite_draw_stripe(t_vars *vars, t_ray *r, int stripe)
{
	int				y;
	int				d;
	unsigned int	color;

	r->dda.tex_x = (int)(256 * (stripe - (-r->dda.sprite_width / 2 +
		r->dda.sprite_screen_x)) * TEXWIDTH / r->dda.sprite_width) / 256;
	if (r->dda.transform_y > 0 && stripe > 0 &&
		stripe < vars->map.res_w && r->dda.transform_y < r->buffer_z[stripe])
	{
		y = r->dda.draw_start_y;
		while (y < r->dda.draw_end_y)
		{
			d = (y) * 256 - vars->map.res_h * 128 + r->dda.sprite_height * 128;
			r->dda.tex_y = ((d * TEXHEIGHT) / r->dda.sprite_height) / 256;
			color = my_mlx_pixel_get(vars->map.walls[4],
									r->dda.tex_x, r->dda.tex_y);
			if ((color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(vars, stripe, y, color);
			y++;
		}
	}
}

void	ft_draw_sprites(t_vars *vars, t_ray *ray)
{
	int i;
	int stripe;

	ft_sprite_order(vars, vars->map.sprites, vars->map.num_sprite);
	i = 0;
	while (i < vars->map.num_sprite)
	{
		ft_sprite_draw_setup(vars, ray, i);
		stripe = ray->dda.draw_start_x;
		while (stripe < ray->dda.draw_end_x)
		{
			ft_sprite_draw_stripe(vars, ray, stripe);
			stripe++;
		}
		i++;
	}
}
