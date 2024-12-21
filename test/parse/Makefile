NAME = parse_test
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../../libft -I../../includes
SRCS = parse.c ../../srcs/tokenize.c ../../srcs/utils.c \
	   ../../srcs/tokenize_utils.c ../../srcs/expand_tokens.c \
	   ../../srcs/expand_utils.c ../../srcs/parse.c ../../srcs/debug.c

LIBFT = ../../libft/libft.a

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $^ $(LIBFT) -o $@

test: all
	@./test.sh
	@$(RM) $(NAME)
