/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:47:57 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/21 12:07:49 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int worldMap[mapWidth][mapHeight]=
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;
	t_img	i;

	i = vars->img[vars->current_img];
	// i = vars->i;
	dst = i.addr + (y * i.line_length + x * (i.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_mlx_draw_line(t_vars *vars, int x, int drawStart, int drawEnd, int color)
{
	int y;

	y = drawStart;
	while (y <= drawEnd)
	{
		if (y == drawStart || y == drawEnd)
		{
			// mlx_pixel_put(vars->mlx, vars->win, x, y++, color);
			my_mlx_pixel_put(vars, x, y++, color);
		}
		else
		{
			// mlx_pixel_put(vars->mlx, vars->win, x, y++, add_shade(0.5, color));
			my_mlx_pixel_put(vars, x, y++, add_shade(0.5, color));
		}
	}
}

int		ft_draw(t_vars *vars)
{
	for (int x = 0; x < screenWidth; x++)
	{
		t_ray	ray;

		ray = vars->ray;
		// calculate ray position and direction
		double cameraX = 2 * x / (double)screenWidth - 1; // x-coordinate in camera space
		double rayDirX = ray.dirX + ray.planeX * cameraX;
		double rayDirY = ray.dirY + ray.planeY * cameraX;
	
		// which box of the map we're in
		int mapX = (int)(ray.posX);
		int mapY = (int)(ray.posY);
		
		// length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		// length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
		
		// what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
			
		int hit = 0; // was there a wall hit?
		int side; // was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (ray.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - ray.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (ray.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - ray.posY) * deltaDistY;
		}
		
		// perform DDA
		while (hit == 0)
		{
			// jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			
			// Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		// Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		double perpWallDist;
		if (side == 0)
			perpWallDist = (mapX - ray.posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - ray.posY + (1 - stepY) / 2) / rayDirY;
		
		// Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;

		// choose wall color
		/*
		**	Transparency: 0xFF000000
		**	Red: 0x00FF0000;
		**	Green: 0x0000FF00;
		**	Blue: 0x000000FF;
		**
		*/
		int color;

		switch (worldMap[mapX][mapY])
		{
			case 1:  color = RGB_Red;  	 break; //red
			case 2:  color = RGB_Green;  break; //green
			case 3:  color = RGB_Blue;   break; //blue
			case 4:  color = RGB_White;  break; //white
			default: color = RGB_Yellow; break; //yellow
		}

		//give x and y sides different brightness
		if (side == 1)
		{
			color = color / 2;
			// color = add_shade(0.5, color);
		}

		//draw the pixels of the stripe as a vertical line
		ft_mlx_draw_line(vars, x, drawStart, drawEnd, color);
	} //end for loop
	printf("ft_draw done\n");
	// mlx_clear_window(vars->mlx, vars->win);
	// mlx_put_image_to_window(vars->mlx, vars->win, vars->i.img, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img[vars->current_img].img, 0, 0);

	return (0);
}

int			key_press_hook(int keycode, t_vars *vars)
{
	t_ray r;

	r = vars->ray;
	if (keycode == KEY_ESC)
	{
		printf("ESC: Closing the window\n");
		vars->done = 1;
		mlx_destroy_window(vars->mlx, vars->win);
		exit (0);
	}
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT || keycode == KEY_DOWN || keycode == KEY_UP)
	{
		// ft_player_motion(vars);
		// move forward if no wall in front of you
		if (keycode == KEY_UP)
		{
			if (worldMap[(int)(r.posX + r.dirX * r.moveSpeed)][(int)(r.posY)] == 0)
				r.posX += r.dirX * r.moveSpeed;
			if (worldMap[(int)(r.posX)][(int)(r.posY + r.dirY * r.moveSpeed)] == 0)
				r.posY += r.dirY * r.moveSpeed;
			printf("Ker Press --- keycode: [UP]\n");
		}
		// move backwards if no wall behind you
		if (keycode == KEY_DOWN)
		{
			if (worldMap[(int)(r.posX - r.dirX * r.moveSpeed)][(int)(r.posY)] == 0)
				r.posX -= r.dirX * r.moveSpeed;
			if (worldMap[(int)(r.posX)][(int)(r.posY - r.dirY * r.moveSpeed)] == 0)
				r.posY -= r.dirY * r.moveSpeed;
			printf("Ker Press --- keycode: [DOWN]\n");
		}
		//rotate to the right
		if (keycode == KEY_RIGHT)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = r.dirX;
			r.dirX = r.dirX * cos(-(r.rotSpeed)) - r.dirY * sin(-(r.rotSpeed));
			r.dirY = oldDirX * sin(-(r.rotSpeed)) + r.dirY * cos(-(r.rotSpeed));
			double oldPlaneX = r.planeX;
			r.planeX = r.planeX * cos(-(r.rotSpeed)) - r.planeY * sin(-(r.rotSpeed));
			r.planeY = oldPlaneX * sin(-(r.rotSpeed)) + r.planeY * cos(-(r.rotSpeed));
		}
		//rotate to the left
		if (keycode == KEY_LEFT)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = r.dirX;
			r.dirX = r.dirX * cos(r.rotSpeed) - r.dirY * sin(r.rotSpeed);
			r.dirY = oldDirX * sin(r.rotSpeed) + r.dirY * cos(r.rotSpeed);
			double oldPlaneX = r.planeX;
			r.planeX = r.planeX * cos(r.rotSpeed) - r.planeY * sin(r.rotSpeed);
			r.planeY = oldPlaneX * sin(r.rotSpeed) + r.planeY * cos(r.rotSpeed);
		}
	}
	return (0);
}