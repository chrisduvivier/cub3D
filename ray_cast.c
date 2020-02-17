/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 20:18:17 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/17 17:17:16 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  gcc -Wextra -Wall libmlx.a -framework OpenGl -framework AppKit -lz -L minilibx_opengl_20191021/ main.c 
*/

#include "mlx.h"
#include <stdio.h>
#include <math.h>

#define screenWidth 640
#define screenHeight 480
#define mapWidth 10
#define mapHeight 10

#define RGB_Red create_trgb(0, 255, 0, 0);
#define RGB_Green create_trgb(0, 0, 255, 0);
#define RGB_Blue create_trgb(0, 0, 0, 255);
#define RGB_White create_trgb(0, 255, 255, 255);
#define RGB_Yellow create_trgb(0, 255, 255, 0);

typedef struct  s_vars {
    void        *mlx;
    void        *win;
	int			done;
	double		posX;
	double		posY;
	double		dirX;
	double		planeX;
	double		dirY;
	double		planeY;
}               t_vars;

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1},
	{2,0,0,0,0,0,0,0,0,2},
	{3,0,0,0,0,0,0,0,0,3},
	{4,0,0,0,0,0,0,0,0,4},
	{5,0,0,0,0,0,0,0,0,5},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1},
};

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
		t = get_t(color);
		r = (distance * 0 + (1 - distance) * (get_r(color) >> 16));
		g = (distance * 0 + (1 - distance) * (get_g(color) >> 8));
		b = (distance * 0 + (1 - distance) * (get_b(color) >> 0));
		return (t << 24 | r << 16 | g << 8 | b);
	}
	return (color);
}

void	ft_draw(t_vars *vars)
{
	for (int x = 0; x < screenWidth; x++)
	{
		// calculate ray position and direction
		double cameraX = 2 * x / screenWidth - 1; // x-coordinate in camera space
		double rayDirX = vars->dirX + vars->planeX * cameraX;
		double rayDirY = vars->dirY + vars->planeY * cameraX;
	
		// which box of the map we're in
		int mapX = (int)(vars->posX);
		int mapY = (int)(vars->posY);
		
		// length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		// length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : abs(1 / rayDirX));
		double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : abs(1 / rayDirY));
		
		// what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
			
		int hit = 0; // was there a wall hit?
		int side; // was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (vars->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - vars->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (vars->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - vars->posY) * deltaDistY;
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
			perpWallDist = (mapX - vars->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - vars->posY + (1 - stepY) / 2) / rayDirY;
		
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

		switch(worldMap[mapX][mapY])
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
		// verLine(x, drawStart, drawEnd, color);
		mlx_pixel_put(vars->mlx, vars->win, x, drawStart, color);
		mlx_pixel_put(vars->mlx, vars->win, x, drawEnd, color);
	} //end for loop
}

int main(int argc, char *argv[])
{
	t_vars      vars;
	
	double posX = 5, posY = 5;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	
	// create screen with the resolution of choice:
	vars.mlx = mlx_init();
	vars.done = 0;
    vars.win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "ray_cast");
    
	while (!vars.done)
	{
		// ft_draw(&vars);
		
		for (int x = 0; x < screenWidth; x++)
		{
			// calculate ray position and direction
			double cameraX = 2 * x / screenWidth - 1; // x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;
		
			// which box of the map we're in
			int mapX = (int)(posX);
			int mapY = (int)(posY);
			
			// length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;
			
			// length of ray from one x or y-side to next x or y-side
			double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : abs(1 / rayDirX));
			double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : abs(1 / rayDirY));
			
			// what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;
				
			int hit = 0; // was there a wall hit?
			int side; // was a NS or a EW wall hit?

			//calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
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
				perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
			
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

			switch(worldMap[mapX][mapY])
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
				color = add_shade(0.5, color);
			}

			//draw the pixels of the stripe as a vertical line
			// verLine(x, drawStart, drawEnd, color);
			mlx_pixel_put(vars.mlx, vars.win, x, drawStart, color);
			mlx_pixel_put(vars.mlx, vars.win, x, drawEnd, color);
		} //end for loop

		double moveSpeed = 0.5; //the constant value is in squares/second
		double rotSpeed = 0.3; 
		
		mlx_loop(vars.mlx);
	}
}