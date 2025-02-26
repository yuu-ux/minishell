NAME = minishell

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I./includes/ -Ilibft
SRCS = 	main.c \
		init.c \
		tokenize.c \
		check_syntax.c \
		utils.c \
		expand_tokens.c \
		expand_utils.c \
		signal_setting.c \
		parse.c \
		tokenize_utils.c \
		invoke_commands.c \
		invoke_utils.c \
		execute.c \
		debug.c \
		builtin.c \
		builtin_utils.c \
		free.c \
		exec_heredoc.c \
		redirect.c \
		redirect_utils.c \
		built_echo.c \
		built_cd.c \
		built_pwd.c \
		built_export.c \
		built_unset.c \
		built_env.c \
		built_exit.c \
		error_utils.c \

SRC_DIR = ./srcs
OBJ_DIR = ./objs
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
LIBFT = libft
TEST_DIR = ./test
RED = "\033[31m"
GREEN = "\033[32m"
RESET = "\033[0m"
all: $(NAME)

$(NAME): $(OBJS)
	git submodule update --init --remote
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
	@echo $(RED)'[-----------tokenize test-----------]'$(RESET)
	@make -C $(TEST_DIR)/tokenize test
	@echo $(RED)'[-----------expand test-----------]'$(RESET)
	@make -C $(TEST_DIR)/expand test
	@echo $(RED)'[-----------parse test-----------]'$(RESET)
	@make -C $(TEST_DIR)/parse test
	@echo $(RED)'[-----------execute test-----------]'$(RESET)
	@make -C $(TEST_DIR)/execute test

re: fclean all

.PHONY: all clean fclean re test debug
