# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/07 21:00:40 by cduvivie          #+#    #+#              #
#    Updated: 2020/10/12 19:02:01 by cduvivie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3d
CC = gcc
CFLAGS = -I. -c
OPTIONS = -Wall -Wextra -Werror
FRAMEWORK = -framework OpenGl -framework AppKit
RM = /bin/rm -f

MLX_TAR_FILE = minilibx_opengl.tgz
MLX_TAR_LINUX_FILE = minilibx-linux-master
MLX_DIR = minilibx_opengl_20191021/
MLX_DIR_LINUX = minilibx-linux-master

LIBFT_DIR = libft/
FILES = cub3d.c ft_draw.c ft_colors_1.c ft_colors_2.c ft_t_vars_init.c \
	ft_map_reader_1.c ft_map_reader_2.c \
	ft_exit_cub3d.c \
	ft_hook.c ft_window.c \
	ft_bmp.c ft_cub_map.c \
	ft_player_rotation.c ft_player_movements.c \
	ft_draw_helper.c ft_sprite.c \
	ft_dda.c ft_check_map_validity.c \
	ft_put_my_error_text.c

OBJ	= $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): setup lib $(OBJ)
	$(CC) $(OPTIONS) $(MLX_DIR)libmlx.a libft.a $(FRAMEWORK) -lz -L $(MLX_DIR) $(FILES) -o $(NAME)

$(OBJ): $(FILES)
	@ $(CC) $(CFLAGS) $(FILES) -I$(MLX_DIR) -Iinc


# linux: lib $(OBJ_LINUX)
# 	make -C mlx
	# $(CC) -o $(NAME) $(OBJ) -Lmlx -lmlx -lXext -lX11 -lm libft.a 

# $(OBJ): $(FILES)
# 	@ $(CC) $(CFLAGS) $(FILES) -Imlx -I.

setup:
	@ tar -xvzf $(MLX_TAR_FILE)
	@ $(MAKE) -C $(MLX_DIR)
	@ cp $(MLX_DIR)/mlx.h ./

lib:
	@ $(MAKE) -C $(LIBFT_DIR) all
	@ cp $(LIBFT_DIR)/libft.a ./

clean:
	@ $(RM) $(OBJ)

fclean: clean
	@ $(RM) $(NAME)
	@ $(RM) libft.a
	@ $(RM) mlx.h
	@ $(RM) -rf minilibx_opengl_20191021/
	@ $(RM) output.bmp
	@ $(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re