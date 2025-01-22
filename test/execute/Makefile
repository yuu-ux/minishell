NAME = execute_test
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../../libft -I../../includes
TEST_FILE = exe.c
FILES = builtin.c \
		builtin_utils.c \
		check_syntax.c \
		debug.c \
		execute.c \
		expand_tokens.c \
		expand_utils.c \
		free.c \
		invoke_commands.c \
		invoke_utils.c \
		parse.c \
		signal_setting.c \
		tokenize.c \
		tokenize_utils.c \
		utils.c \

SRCS = $(TEST_FILE)
SRCS += $(addprefix ../../srcs/, $(FILES))
LIBFT = ../../libft/libft.a

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $^ $(LIBFT) -o $@ -lreadline

test: all
	@./test.sh
	@$(RM) $(NAME)
