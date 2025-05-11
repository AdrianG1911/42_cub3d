# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jidler <jidler@student.42tokyo.jp >        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 20:11:53 by adrgutie          #+#    #+#              #
#    Updated: 2025/05/06 11:44:32 by jidler           ###   ########.fr        #
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
				src/renderer.c \
				src/renderer_2.c \
				src/map_validation.c \
				src/build_2d_grid.c \
				src/check_borders.c \
				src/check_color_texture.c \
				src/check_file_type.c \
				src/extract_header_data.c \
				src/extract_header_data_utils.c \
				src/find_map_start_index.c \
				src/load_lines_to_memory.c \
				src/check_border_helper.c \
				src/free_game.c \
				src/extract_header_data_helper.c \
				src/load_lines_to_memory_helper.c \
				src/load_lines_to_memory_extra_helper.c


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
