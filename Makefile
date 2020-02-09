# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/07 21:00:40 by cduvivie          #+#    #+#              #
#    Updated: 2020/02/07 21:10:14 by cduvivie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3d.a
CC = gcc
CFLAGS = -I. -c
OPTIONS = -Wall -Wextra -Werror
RM = /bin/rm -f

FILES = main.c
	
OBJ	= $(FILES:%.c=%.o)

# @ echo "\033[32mlibftprintf.a compiled\033[0m"
all: $(NAME)

# %.o: %.c
# 	@printf "Compiling $<"
# 	@gcc -Wall -Wextra -Werror -Imlx -Iinc -Ilibft -c $< -o $@

# main:
# 	@ $(CC) main.c -L. -lftprintf

$(NAME): $(OBJ)
	 $(CC) -Lmlx/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(OBJ): $(FILES)
	@ $(CC) $(CFLAGS) $(FILES) -Iminilibx_opengl_20191021 -Iinc

clean:
	@ $(RM) $(OBJ)

fclean: clean
	@ $(RM) $(NAME)
	@ echo "\033[32mFCLEAN DONE\033[0m"

re: fclean all

.PHONY: all clean fclean re