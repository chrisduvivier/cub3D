/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:34:42 by cduvivie          #+#    #+#             */
/*   Updated: 2020/09/25 14:09:34 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

// typedef struct 	s_bmp_file
// {
// 	t_bmp_info header;
// 	unsigned char* data; 
// }				s_bmp_file;


void	ft_bmp_fill_header(t_vars *vars, 
	t_byte file_header[FILE_HEADER_SIZE], 
	t_byte info_header[INFO_HEADER_SIZE])
{
	int bmpfile_size;

	bmpfile_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + 
		(BYTES_PER_PIXEL * vars->map.res_w + 
		((4 - (vars->map.res_w * BYTES_PER_PIXEL) % 4) % 4))* vars->map.res_h;
	ft_bzero(file_header, FILE_HEADER_SIZE);
	ft_bzero(info_header, INFO_HEADER_SIZE);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(bmpfile_size);
	file_header[3] = (unsigned char)(bmpfile_size >> 8);
	file_header[4] = (unsigned char)(bmpfile_size >> 16);
	file_header[5] = (unsigned char)(bmpfile_size >> 24);
	file_header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
	info_header[0] = (unsigned char)(INFO_HEADER_SIZE);
	info_header[4] = (unsigned char)(vars->map.res_w);
	info_header[5] = (unsigned char)(vars->map.res_w >> 8);
	info_header[6] = (unsigned char)(vars->map.res_w >> 16);
	info_header[7] = (unsigned char)(vars->map.res_w >> 24);
	info_header[8] = (unsigned char)(vars->map.res_h);
	info_header[9] = (unsigned char)(vars->map.res_h >> 8);
	info_header[10] = (unsigned char)(vars->map.res_h >> 16);
	info_header[11] = (unsigned char)(vars->map.res_h >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(BYTES_PER_PIXEL * 8);
}

void	ft_bmp_write_pixels(int	fd, t_vars *vars, t_byte *data)
{
	int				height;
	int				width;
	t_byte			padding[3];
	int				padding_size;
	unsigned int 	color;

	printf("==== ft_bmp_write_pixels ====\n");
	ft_bzero(padding, 3);
	padding_size = (4 - (vars->map.res_w * BYTES_PER_PIXEL) % 4) % 4;
	height = vars->map.res_h;
	while (--height >= 0)
	{
		width = -1;
		while (++width < (int)vars->map.res_w)
		{
			// color = mlx->data[width + (height * vars->map.res_w)];
			// TODO WHICH IMAGE? 0 or 1?
			color = my_mlx_pixel_get(vars->img[vars->current_img], width, height);
			data[3 * width + 2] = color / (256 * 256);
			data[3 * width + 1] = (color / 256) % 256;
			data[3 * width + 0] = color % 256;
		}
		write(fd, data, vars->map.res_w * 3);
		write(fd, padding, padding_size);
	}
}

int		ft_bmp_write(t_vars *vars, t_byte file_header[FILE_HEADER_SIZE],
		t_byte info_header[INFO_HEADER_SIZE])
{
	printf("==== ft_bmp_write ====\n");
	int		fd;
	t_byte	*data;

	if ((fd = open(BMP_FILENAME, O_WRONLY | O_CREAT, 0644)) < 0)
		return (-1);
	if (!(data = malloc(sizeof(t_byte)*(vars->map.res_w * BYTES_PER_PIXEL))))
		exit_cub3d(vars, ERROR_MALLOC, __FILE__, __LINE__);
	write(fd, file_header, FILE_HEADER_SIZE);
	write(fd, info_header, INFO_HEADER_SIZE);
	ft_bmp_write_pixels(fd, vars, data);
	free(data);
	close(fd);
	return (0);
}


void    ft_create_bmp_file(t_vars *vars)
{
	printf("==== ft_create_bmp_file ====\n");
	
	t_byte	file_header[FILE_HEADER_SIZE];
	t_byte	info_header[INFO_HEADER_SIZE];

	ft_bmp_fill_header(vars, file_header, info_header);
	if (ft_bmp_write(vars, file_header, info_header) != 0)
		exit_cub3d(vars, ERROR_BMP_WRITE, __FILE__, __LINE__);
}

/*
**	First function that checks if bmpfile needs to be created by checking arg.
*/

void	ft_handle_bmp(int argc, char *argv[], t_vars *vars)
{
	if (argc > 2)
	{
		if (argc == 3 && ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) == 0)
		{
			vars->bmp_done = 0;
		}
		else
			exit_cub3d(vars, ERROR_ARG, __FILE__, __LINE__);
	}
} 
