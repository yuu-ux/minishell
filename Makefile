NAME = minishell

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I./includes/ -Ilibft
FILES = main.c tokenize.c check_syntax.c utils.c debug.c expand_tokens.c invoke_commands.c signal_setting.c
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

debug: CFLAGS += -fsanitize=address
debug: all

test:
	make -C $(TEST_DIR) test

re: fclean all

.PHONY: all clean fclean re test debug
