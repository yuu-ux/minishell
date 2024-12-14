NAME = tokenize_test
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../../libft -I../../includes
SRCS = tokenize.c ../../srcs/tokenize.c ../../srcs/utils.c \
	   ../../srcs/tokenize_utils.c
LIBFT = ../../libft/libft.a

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $^ $(LIBFT) -o $@

test: all
	python3 tokenize.py
	$(RM) $(NAME)
