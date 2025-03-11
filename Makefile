# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/26 14:55:58 by hana/hmori        #+#    #+#              #
#    Updated: 2025/03/09 03:19:02 by yehara           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	cc
CFLAGS			=	-g -Wall -Wextra -Werror
FLAGS			=	-I$(HEADER_MAIN) -I$(HEADER_UNIT) -I$(LIBFT_DIR)/include
LIBREADL		=	-lreadline
MAKEFLAGS		+=	--no-print-directory


HEADER_MAIN		=	./includes
HEADER_UNIT		=	$(HEADER_MAIN)/units

LIBFT_DIR		=	./libft
LIBFTA			=	$(LIBFT_DIR)/libft.a

SRC_DIR			=	./srcs
SRC_FILES		=	main.c \
					init.c \
					tokenize.c \
					check_syntax.c \
					utils.c \
					expand_tokens.c \
					expand_utils.c \
					signal_setting.c \
					signal_handler.c \
					parse.c \
					tokenize_utils.c \
					invoke_commands.c \
					invoke_utils.c \
					execute.c \
					execute_utils.c \
					builtin.c \
					builtin_utils.c \
					free.c \
					heredoc.c \
					heredoc_utils.c \
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
					environ_units.c \
					status_utils.c \
					is_utils.c

OBJ_DIR 		=	./objs
OBJS 			=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

DEPENDENCY		=	$(patsubst %.c, $(OBJ_DIR)/%.d, $(SRC_FILES))


TEST_DIR = ./test
RED = "\033[31m"
GREEN = "\033[32m"
RESET = "\033[0m"


all: $(LIBFT_DIR) $(NAME)

$(NAME): $(OBJS) $(LIBFTA)
	$(CC) $(CFLAGS) $(FLAGS) $^ -o $@ $(LIBREADL)

$(LIBFT_DIR):
	@git submodule update --init --remote
	@make -C $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPENDENCY)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

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

.DEFAULT_GOAL	:=	all

.PHONY: all clean fclean re test debug $(LIBFT_DIR)
