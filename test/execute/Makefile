NAME = execute_test
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../../libft -I../../includes
TEST_FILE = exe.c
FILES = tokenize.c \
		utils.c \
		tokenize_utils.c \
		expand_tokens.c \
		expand_utils.c \
		execute.c \
		invoke_utils.c \
		invoke_commands.c \
		parse.c \

SRCS = $(TEST_FILE)
SRCS += $(addprefix ../../srcs/, $(FILES))
LIBFT = ../../libft/libft.a

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $^ $(LIBFT) -o $@

test: all
	@./test.sh
	@$(RM) $(NAME)
