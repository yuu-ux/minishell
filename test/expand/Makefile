NAME = expand_test
CC = cc
CFLAGS = -Wall -Wextra -Werror -I../../libft -I../../includes
SRCS = expand.c ../../srcs/tokenize.c ../../srcs/utils.c \
	   ../../srcs/tokenize_utils.c ../../srcs/expand_tokens.c
LIBFT = ../../libft/libft.a

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $^ $(LIBFT) -o $@

test: all
	@./test.sh
	@$(RM) $(NAME)
