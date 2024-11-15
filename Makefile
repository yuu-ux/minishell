NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
FILES = main.c tokenize.c
SRCS = $(addprefix ./srcs/, $(FILES))
LIBFT = libft
TEST_DIR = ./test/tokenize/

all: $(NAME)

$(NAME): $(SRCS)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) -lreadline $^ -o $@ ./libft/libft.a

clean:
	make -C $(LIBFT) clean
	rm -f *.o

fclean: clean
	make -C $(LIBFT) fclean
	$(RM) $(NAME)

test:
	make -C $(TEST_DIR) test

re: fclean all

.PHONY: all clean fclean re test
