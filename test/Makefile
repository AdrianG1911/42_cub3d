# Simple Makefile for testing parser and map validation

NAME = test_parser

SRC = \
	../src/testing_main.c \
	../src/map_validation.c \
	../src/check_file_type.c \
	../src/load_lines_to_memory.c \
	../src/extract_header_data.c \
	../src/find_map_start_index.c \
	../src/build_2d_grid.c \
	../src/check_color_texture.c \
	../src/check_borders.c \
	../src/init_player.c \
	../src/player.c
OBJ = $(SRC:.c=.o)

INCLUDES = -I../include -I../libft
LIBFT = ../libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(SRC) $(LIBFT)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re 