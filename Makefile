# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 20:11:53 by adrgutie          #+#    #+#              #
#    Updated: 2025/04/27 21:38:54 by adrgutie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
LDFLAGS		=	-Llibft -Lminilibx-linux
LDLIBS		=	-lft -lmlx_Linux -lm -lXext -lX11
RM			=	rm -fr
OBJ_DIR		=	obj

SRCS		=	src/main.c \
				src/input.c \
				src/raycaster.c \
				src/raycaster_2.c \
				src/player.c \
				#src/map_validation.c \
				#src/parse.c \
				#src/renderer.c 

OBJS		=	$(SRCS:src/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C minilibx-linux
	make -C libft
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -g -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ_DIR)
	make clean -C libft
	make clean -C minilibx-linux

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY : all clean fclean re
