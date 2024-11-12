NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = main.c tokenize.c
SRCS = $(addprefix ./src/, $(FILES))
LIBFT = libft

all: $(NAME)

$(NAME): $(SRCS)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) -lreadline $^ -o $@ ./libft/libft.a

clean:
	make -C $(LIBFT) clean
	rm -f *.o

fclean:
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re:
	fclean all

.PHONY: all clean fclean re
