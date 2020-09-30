/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:47:57 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/30 11:02:20 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

// int worldMap[mapWidth][mapHeight]=
// {
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
// };

// int worldMap[mapWidth][mapHeight]=
// {
//   {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
//   {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
//   {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
//   {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
//   {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
//   {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
//   {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
//   {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
//   {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
//   {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
//   {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
//   {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
//   {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
//   {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
//   {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
//   {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
//   {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
//   {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
//   {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
//   {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
//   {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
//   {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
//   {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
//   {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
// };

// int worldMap[mapWidth][mapHeight] =
// {
//   {8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
//   {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
//   {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
//   {8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
//   {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
//   {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
//   {8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
//   {7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
//   {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
//   {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
//   {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
//   {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
//   {7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
//   {2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
//   {2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
//   {2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
//   {1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
//   {2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
//   {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
//   {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
//   {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
//   {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
//   {2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
// };

int		ft_draw(t_vars *vars)
{
	unsigned int buffer[vars->map.res_h]; // y-coordinate first because it works per scanline
	
	//1D Zbuffer for sprites
	// contains the distance to the wall of every vertical stripe
	double ZBuffer[vars->map.res_w];
	t_ray	*ray;
	
	for (int x = 0; x < vars->map.res_w; x++)
	{

		ray = &(vars->ray);
		// calculate ray position and direction
		double cameraX = 2 * x / (double)vars->map.res_w - 1; // x-coordinate in camera space
		double rayDirX = ray->dirX + ray->planeX * cameraX;
		double rayDirY = ray->dirY + ray->planeY * cameraX;
	
		// which box of the map we're in
		int mapX = (int)(ray->posX);
		int mapY = (int)(ray->posY);
		
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

		// calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (ray->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - ray->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (ray->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - ray->posY) * deltaDistY;
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
			if (vars->map.map[mapX][mapY] > 0)
				hit = 1;
		}
		// Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		double perpWallDist;
		if (side == 0)
			perpWallDist = (mapX - ray->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - ray->posY + (1 - stepY) / 2) / rayDirY;
		
		// Calculate height of line to draw on screen
		int lineHeight = (int)(vars->map.res_h / perpWallDist);

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + vars->map.res_h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + vars->map.res_h / 2;
		if (drawEnd >= vars->map.res_h)
			drawEnd = vars->map.res_h - 1;
		
		//texturing calculations (TEMPRARY THING. NOT USED)
		int texNum = vars->map.map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		// determine directiuon of wall
		if (side == 1) //N or S wall
		{
			if (stepY > 0) texNum = 0;
			else texNum = 1;
		}
		else // E or W wall
		{
			if (stepX > 0) texNum = 2;
			else texNum = 3;
		}

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = ray->posY + perpWallDist * rayDirY;
		else           wallX = ray->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(texWidth));
		if (side == 0 && rayDirX > 0)
		{
			texX = texWidth - texX - 1;
		}
		if (side == 1 && rayDirY < 0)
		{
			texX = texWidth - texX - 1;
		}
		
		// How much to increase the texture coordinate per screen pixelm 
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - vars->map.res_h / 2 + lineHeight / 2) * step;
		
		/*
		**	Here comes the loop over y axis, where we put read the color of the texture and put that to
		**	a buffer.
		*/
		for (int y = drawStart; y<drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			// Uint32 color = texture[texNum][texHeight * texY + texX];
			unsigned int color;
			color = my_mlx_pixel_get(vars->map.walls[texNum], texX, texY);

			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			// if (side == 1) color = (color >> 1) & 8355711;
			buffer[y] = color;
		}

		//draw the pixels of the stripe as a vertical line
		ft_mlx_draw_line(vars, x, drawStart, drawEnd, buffer);

		// clear buffer
		for (int y = 0; y < vars->map.res_h; y++)
			buffer[y] = 0;
		
		//SET THE ZBUFFER FOR THE SPRITE CASTING
     	ZBuffer[x] = perpWallDist; //perpendicular distance is used
	}

	/*
	** SPRITE CASTING
	*/
    // sort sprites from far to close
	
	int		spriteOrder[vars->map.num_sprite];
	double 	spriteDistance[vars->map.num_sprite];
	
	// printf("=============== num_sprite: %i ============\n", vars->map.num_sprite);
    for (int i = 0; i < vars->map.num_sprite; i++)
    {
      	spriteOrder[i] = i;
      	spriteDistance[i] = ((ray->posX - vars->map.sprites[i]->x) * (ray->posX - vars->map.sprites[i]->x)
	  		+ (ray->posY - vars->map.sprites[i]->y) * (ray->posY - vars->map.sprites[i]->y)); //sqrt not taken, unneeded
    }
	// TODO
    // sortSprites(spriteOrder, spriteDistance, NUM_SPRITES);

    //after sorting the sprites, do the projection and draw them
    for (int i = 0; i < vars->map.num_sprite; i++)
    {
		//translate sprite position to relative to camera
		double spriteX = vars->map.sprites[spriteOrder[i]]->x - ray->posX;
		double spriteY = vars->map.sprites[spriteOrder[i]]->y - ray->posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (ray->planeX * ray->dirY - ray->dirX * ray->planeY); //required for correct matrix multiplication

		double transformX = invDet * (ray->dirY * spriteX - ray->dirX * spriteY);
		double transformY = invDet * (-(ray->planeY) * spriteX + ray->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

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
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < vars->map.res_w && transformY < ZBuffer[stripe])
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
