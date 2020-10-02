/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:47:57 by cduvivie          #+#    #+#             */
/*   Updated: 2020/10/02 13:29:15 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_draw(t_vars *vars)
{	
	t_ray	*ray;

	ray = &(vars->ray);
	if ((ray->buffer_y = (unsigned int*)malloc(sizeof(unsigned int) *
		vars->map.res_h)) == NULL)
		exit_cub3d(vars, ERROR_MALLOC, __FILE__, __LINE__);
	if ((ray->buffer_z = (double*)malloc(sizeof(double) * vars->map.res_w)) == NULL)
		exit_cub3d(vars, ERROR_MALLOC, __FILE__, __LINE__);

	int x;
	x = 0;
	while (x < vars->map.res_w)
	{
		ft_dda_setup(vars, ray, x);

		ft_dda_side_distance(ray);
		
		ft_dda_check_hit(vars, ray);

		ft_dda_wall_distance(vars, ray, &(ray->dda));

		ft_dda_draw_wall(vars, ray, &(ray->dda));

		//draw the pixels of the stripe as a vertical line
		ft_mlx_draw_line(vars, x, ray->dda.draw_start, ray->dda.draw_end, ray->buffer_y);

		// clear buffer_y
		for (int y = 0; y < vars->map.res_h; y++)
			ray->buffer_y[y] = 0;
		
		//SET THE buffer_z FOR THE SPRITE CASTING
     	ray->buffer_z[x] = ray->dda.perp_wall_dist; //perpendicular distance is used

		x++;
	}
	

	/*
	** SPRITE CASTING
	*/
	ft_sprite_order(vars, vars->map.sprites, vars->map.num_sprite);

    //after sorting the sprites, do the projection and draw them
    for (int i = 0; i < vars->map.num_sprite; i++)
    {
		//translate sprite position to relative to camera
		double spriteX = vars->map.sprites[i]->x - ray->pos_x;
		double spriteY = vars->map.sprites[i]->y - ray->pos_y;

		//transform sprite with the inverse camera matrix
		// [ plane_x   dir_x ] -1                                       [ dir_y      -dir_x ]
		// [               ]       =  1/(plane_x*dir_y-dir_x*plane_y) *   [                 ]
		// [ plane_y   dir_y ]                                          [ -plane_y  plane_x ]

		double invDet = 1.0 / (ray->plane_x * ray->dir_y - ray->dir_x * ray->plane_y); //required for correct matrix multiplication

		double transformX = invDet * (ray->dir_y * spriteX - ray->dir_x * spriteY);
		double transformY = invDet * (-(ray->plane_y) * spriteX + ray->plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((vars->map.res_w / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(vars->map.res_h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + vars->map.res_h / 2;
		if (drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + vars->map.res_h / 2;
		if (drawEndY >= vars->map.res_h) drawEndY = vars->map.res_h - 1;

		//calculate width of the sprite
		int spriteWidth = abs((int) (vars->map.res_h / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= vars->map.res_w) drawEndX = vars->map.res_w - 1;

		//loop through every vertical stripe of the sprite on screen
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ray->buffer_z, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < vars->map.res_w && transformY < ray->buffer_z[stripe])
			{
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - vars->map.res_h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * texHeight) / spriteHeight) / 256;

					unsigned int color;
					color = my_mlx_pixel_get(vars->map.walls[4], texX, texY);
					if ((color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(vars, stripe, y, color); //paint pixel if it isn't black, black is the invisible color
				}
			
			}
		}
    }
	
	// mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img[vars->current_img].img, 0, 0);
	
	if (vars->bmp_done == 0)
	{
		ft_create_bmp_file(vars);
		vars->bmp_done = 1;
	}
	
	// printf("ft_draw current_img = [%d]\n", vars->current_img);
	vars->current_img = (vars->current_img == 0) ? 1 : 0;
	// printf("ft_draw after current_img = [%d]\n", vars->current_img);
	
	return (0);
}
