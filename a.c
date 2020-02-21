/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:32:00 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/21 11:44:15 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**  gcc -Wextra -Wall libmlx.a -framework OpenGl -framework AppKit -lz -L minilibx_opengl_20191021/ main.c 
*/

// {
// 	{1,2,1,2,1,2,1,2,1,2},
// 	{2,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,2},
// 	{2,0,0,0,0,0,0,0,0,1},
// 	{5,0,0,0,0,0,0,0,0,3},
// 	{2,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,2},
// 	{2,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,2},
// 	{2,1,2,1,2,4,2,1,2,1},
// };

t_img	t_img_init(t_vars vars)
{
	
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:44:45 by cduvivie          #+#    #+#             */
/*   Updated: 2020/02/19 18:49:27 by cduvivie         ###   ########.fr       */
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

/*
**	posX, posY: x and y start position
**	dirX, dirY: initial direction vector
**	planeX, planeY: the 2d raycaster version of camera plane
**	moveSpeed, rotSpeed: constant value
*/

t_ray	t_ray_init(void)
{
	t_ray ray;

	ray.posX = 22;
	ray.posY = 12;
	ray.dirX = -1;
	ray.dirY = 0;
	ray.planeX = 0;
	ray.planeY = 0.66;
	ray.moveSpeed = 0.1;
	ray.rotSpeed = 0.1;
	return (ray);
}

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->img_addr + (y * vars->img_line_length + x * (vars->img_bits_per_pixel / 8));
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
		// calculate ray position and direction
		double cameraX = 2 * x / (double)screenWidth - 1; // x-coordinate in camera space
		double rayDirX = vars->dirX + vars->planeX * cameraX;
		double rayDirY = vars->dirY + vars->planeY * cameraX;
	
		// which box of the map we're in
		int mapX = (int)(vars->posX);
		int mapY = (int)(vars->posY);
		
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
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);

	return (0);
}


int			key_press_hook(int keycode, t_vars *vars)
{
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
			if (worldMap[(int)(vars->posX + vars->dirX * vars->moveSpeed)][(int)(vars->posY)] == 0)
				vars->posX += vars->dirX * vars->moveSpeed;
			if (worldMap[(int)(vars->posX)][(int)(vars->posY + vars->dirY * vars->moveSpeed)] == 0)
				vars->posY += vars->dirY * vars->moveSpeed;
			printf("Ker Press --- keycode: [UP]\n");
		}
		// move backwards if no wall behind you
		if (keycode == KEY_DOWN)
		{
			if (worldMap[(int)(vars->posX - vars->dirX * vars->moveSpeed)][(int)(vars->posY)] == 0)
				vars->posX -= vars->dirX * vars->moveSpeed;
			if (worldMap[(int)(vars->posX)][(int)(vars->posY - vars->dirY * vars->moveSpeed)] == 0)
				vars->posY -= vars->dirY * vars->moveSpeed;
			printf("Ker Press --- keycode: [DOWN]\n");
		}
		//rotate to the right
		if (keycode == KEY_RIGHT)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = vars->dirX;
			vars->dirX = vars->dirX * cos(-(vars->rotSpeed)) - vars->dirY * sin(-(vars->rotSpeed));
			vars->dirY = oldDirX * sin(-(vars->rotSpeed)) + vars->dirY * cos(-(vars->rotSpeed));
			double oldPlaneX = vars->planeX;
			vars->planeX = vars->planeX * cos(-(vars->rotSpeed)) - vars->planeY * sin(-(vars->rotSpeed));
			vars->planeY = oldPlaneX * sin(-(vars->rotSpeed)) + vars->planeY * cos(-(vars->rotSpeed));
		}
		//rotate to the left
		if (keycode == KEY_LEFT)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = vars->dirX;
			vars->dirX = vars->dirX * cos(vars->rotSpeed) - vars->dirY * sin(vars->rotSpeed);
			vars->dirY = oldDirX * sin(vars->rotSpeed) + vars->dirY * cos(vars->rotSpeed);
			double oldPlaneX = vars->planeX;
			vars->planeX = vars->planeX * cos(vars->rotSpeed) - vars->planeY * sin(vars->rotSpeed);
			vars->planeY = oldPlaneX * sin(vars->rotSpeed) + vars->planeY * cos(vars->rotSpeed);
		}
	}
    return (0);
}



int			main(int argc, char *argv[])
{
	t_vars		vars;
	t_ray		ray;
	t_img		img;
	
	// create screen with the resolution of choice:
	vars.mlx = mlx_init();
	ray = t_ray_init();
	img = t_img_init(vars);
	vars.done = 0;
	vars.win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "ray_cast");
	vars.img = mlx_new_image(vars.mlx, screenWidth, screenHeight);
	vars.img_addr = mlx_get_data_addr(vars.img, &vars.img_bits_per_pixel, &vars.img_line_length,
						&vars.img_endian);
	mlx_expose_hook(vars.win, ft_draw(&vars), &vars);
	while (!vars.done)
	{
		// ft_draw(&vars);
		// mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
		mlx_loop_hook(vars.win, ft_draw(&vars), &vars);
		mlx_hook(vars.win, 2, 0L, key_press_hook, &vars);
		mlx_loop(vars.mlx);
	}
	mlx_destroy_window(vars.mlx, vars.win);
}
