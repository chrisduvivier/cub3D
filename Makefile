# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/07 21:00:40 by cduvivie          #+#    #+#              #
#    Updated: 2020/10/04 02:18:18 by cduvivie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3d
CC = gcc
CFLAGS = -I. -c
OPTIONS = -Wall -Wextra -Werror
RM = /bin/rm -f
MLX_DIR = minilibx_opengl_20191021/
LIBFT_DIR = libft/
FILES = cub3d.c ft_draw.c ft_colors_1.c ft_colors_2.c ft_t_vars_init.c \
	ft_map_reader_1.c ft_map_reader_2.c \
	ft_exit_cub3d.c \
	ft_hook.c ft_window.c \
	ft_bmp.c ft_cub_map.c \
	ft_player_rotation.c ft_player_movements.c \
	ft_draw_helper.c ft_sprite.c \
	ft_dda.c

OBJ	= $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): lib $(OBJ)
	$(CC) $(OPTIONS) $(MLX_DIR)libmlx.a libft.a -framework OpenGl -framework AppKit -lz -L $(MLX_DIR) $(FILES) -o $(NAME)

$(OBJ): $(FILES)
	@ $(CC) $(CFLAGS) $(FILES) -Iminilibx_opengl_20191021 -Iinc

setup:
	@ $(MAKE) -C $(MLX_DIR)

lib:
	@ $(MAKE) -C $(LIBFT_DIR) all
	@ cp $(LIBFT_DIR)/libft.a ./

clean:
	@ $(RM) $(OBJ)

fclean: clean
	@ $(RM) $(NAME)
	@ $(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re