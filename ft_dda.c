/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 00:12:29 by cduvivie          #+#    #+#             */
/*   Updated: 2020/10/02 13:16:46 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**  1. calculate ray position and direction.
**  2. check which box of the map we're in.
**  3. calculate length of ray from one x or y-side to next x or y-side.
**  4. Set wall hit to 0 (none).
*/

void	ft_dda_setup(t_vars *vars, t_ray *r, int x)
{
	r->dda.camera_x = 2 * x / (double)vars->map.res_w - 1;
	r->dda.raydir_x = r->dir_x + r->plane_x * r->dda.camera_x;
	r->dda.raydir_y = r->dir_y + r->plane_y * r->dda.camera_x;
	r->dda.map_x = (int)(r->pos_x);
	r->dda.map_y = (int)(r->pos_y);
	if (r->dda.raydir_y == 0)
		r->dda.delta_dist_x = 0;
	else
		r->dda.delta_dist_x = (r->dda.raydir_x == 0) ? 1 : fabs(1 / r->dda.raydir_x);
	if (r->dda.raydir_x == 0)
		r->dda.delta_dist_y = 0;
	else
		r->dda.delta_dist_y = (r->dda.raydir_y == 0) ? 1 : fabs(1 / r->dda.raydir_y);		
	r->dda.hit = 0;
}

/*
**	Calculate step and initial side distance.
**	Steps are in x or y-direction (either +1 or -1).
*/

void	ft_dda_side_distance(t_ray *r)
{
	if (r->dda.raydir_x < 0)
	{
		r->dda.step_x = -1;
		r->dda.side_dist_x = (r->pos_x - r->dda.map_x) * r->dda.delta_dist_x;
	}
	else
	{
		r->dda.step_x = 1;
		r->dda.side_dist_x = 
			(r->dda.map_x + 1.0 - r->pos_x) * r->dda.delta_dist_x;
	}
	if (r->dda.raydir_y < 0)
	{
		r->dda.step_y = -1;
		r->dda.side_dist_y = (r->pos_y - r->dda.map_y) * r->dda.delta_dist_y;
	}
	else
	{
		r->dda.step_y = 1;
		r->dda.side_dist_y = 
			(r->dda.map_y + 1.0 - r->pos_y) * r->dda.delta_dist_y;
	}
}

/*
**	Core funtion of DDA algorithm.
**	While hit=0, jump to next map square, OR in x-direction, OR in y-direction
**	After each step, check if ray has hit a wall.
*/

void	ft_dda_check_hit(t_vars *vars, t_ray *r)
{
	while (r->dda.hit == 0)
	{
		if (r->dda.side_dist_x < r->dda.side_dist_y)
		{
			r->dda.side_dist_x += r->dda.delta_dist_x;
			r->dda.map_x += r->dda.step_x;
			r->dda.side = 0;
		}
		else
		{
			r->dda.side_dist_y += r->dda.delta_dist_y;
			r->dda.map_y += r->dda.step_y;
			r->dda.side = 1;
		}
		if (vars->map.map[r->dda.map_x][r->dda.map_y] > 0)
			r->dda.hit = 1;
	}
}

/*
**	1. Calculate distance projected on camera direction
**		(Euclidean distance will give fisheye effect).
**	2. Calculate height of line to draw on screen.
**	3. Calculate lowest and highest pixel to fill in current stripe.
**	4. Determine directiuon of wall:
**		side=1 && step_y>0 -> N  |  side=1 && step_y<0 -> S
**		side=0 && step_x>0 -> E  |  side=0 && step_x<0 -> W
**	5. Calculate where exactly the wall was hit.
*/

void	ft_dda_wall_distance(t_vars *vars, t_ray *r, t_dda *d)
{
	d->perp_wall_dist = (d->side == 0) ?
		(d->map_x - r->pos_x + (1 - d->step_x) / 2) / d->raydir_x :
		(d->map_y - r->pos_y + (1 - d->step_y) / 2) / d->raydir_y;
	d->line_height = (int)(vars->map.res_h / d->perp_wall_dist);
	d->draw_start = -(d->line_height) / 2 + vars->map.res_h / 2;
	d->draw_start = (d->draw_start < 0) ? 0 : d->draw_start;
	d->draw_end = d->line_height / 2 + vars->map.res_h / 2;
	if (d->draw_end >= vars->map.res_h)
		d->draw_end = vars->map.res_h - 1;
	if (d->side == 1)
	{
		d->texture_num = (d->step_y > 0) ? 0 : 1;
		d->wall_x = r->pos_x + d->perp_wall_dist * d->raydir_x;
	}
	else
	{
		d->texture_num = (d->step_x > 0) ? 2 : 3;
		d->wall_x = r->pos_y + d->perp_wall_dist * d->raydir_y;
	}
	d->wall_x -= floor((d->wall_x));
}

/*
**	1. Calculate corresponding x coordinate on the texture.
**	2. calculate step: How much to increase the texture coordinate
**					   per screen pixelm.
**	3. Calculate texture_pos: starting texture coordinate.
**	4. Loop over texture wall and store the color in buffer.
**	   Cast the texture coordinate to integer, and mask with
**	   (texHeight - 1) in case of overflow.
*/

void	ft_dda_draw_wall(t_vars *vars, t_ray *r, t_dda *d)
{
	int y;
	
	y = d->draw_start;
	d->texture_x = (int)(d->wall_x * (double)(texWidth));
	if (d->side == 0 && d->raydir_x > 0)
		d->texture_x = texWidth - d->texture_x - 1;
	if (d->side == 1 && d->raydir_y < 0)
		d->texture_x = texWidth - d->texture_x - 1;
	d->texture_step = 1.0 * texHeight / d->line_height;
	d->texture_pos =
		(d->draw_start - vars->map.res_h / 2 + d->line_height / 2) * d->texture_step;
	while (y < d->draw_end)
	{
		d->texture_y = (int)d->texture_pos & (texHeight - 1);
		d->texture_pos += d->texture_step;
		d->color = my_mlx_pixel_get(vars->map.walls[d->texture_num],
										d->texture_x, d->texture_y);
		// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// if (side == 1) color = (color >> 1) & 8355711;
		r->buffer_y[y] = d->color;
		y++;
	}
}
