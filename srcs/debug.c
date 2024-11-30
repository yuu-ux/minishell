#include "tokenize.h"
#include "invoke_commands.h"

const char *get_token_type_string(t_token_type type)
{
    switch (type) {
        case TOKEN_WORD: return "TOKEN_WORD";
        case TOKEN_EOF: return "TOKEN_EOF";
        case TOKEN_UNKNOWN: return "TOKEN_UNKNOWN";
        case TOKEN_PIPE: return "TOKEN_PIPE";
        case TOKEN_REDIRECT_IN: return "TOKEN_REDIRECT_IN";
        case TOKEN_REDIRECT_OUT: return "TOKEN_REDIRECT_OUT";
        case TOKEN_REDIRECT_APPEND: return "TOKEN_REDIRECT_APPEND";
        case TOKEN_REDIRECT_HEREDOC: return "TOKEN_REDIRECT_HEREDOC";
        default: return "UNKNOWN_TYPE";
    }
}

void	print_node(t_node *head)
{
	t_node *current;
	int	i;

    current = head;
    while (current)
    {
        printf("kind:%d\n", current->kind);
        if (current->argv != NULL)
        {
			i = 0;
            while (current->argv[i])
                printf("argv:%s\n", current->argv[i++]);
        }
        printf("in:%d\n", current->fd_in);
        printf("out:%d\n", current->fd_out);
        printf("---------------------------------\n");
        current = current->next;
    }
}
