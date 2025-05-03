# Simple Makefile for testing parser and map validation

NAME = test_parser

SRC = \
	../src/testing_main.c \
	../src/map_validation.c \
	../src/check_file_type.c 
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