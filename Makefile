NAME = minishell

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I./includes/ -Ilibft
SRCS = main.c tokenize.c check_syntax.c utils.c debug.c expand_tokens.c invoke_commands.c signal_setting.c parse.c tokenize_utils.c
SRC_DIR = ./srcs
OBJ_DIR = ./objs
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
LIBFT = libft
TEST_DIR = ./test/tokenize/

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ ./libft/libft.a -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT) clean
	rm -f $(OBJ_DIR)/*.o

fclean: clean
	make -C $(LIBFT) fclean
	$(RM) $(NAME)

debug: CFLAGS += -fsanitize=address -fsanitize=leak
debug: all

test:
	make -C $(TEST_DIR) test

re: fclean all

.PHONY: all clean fclean re test debug
