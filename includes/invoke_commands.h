#ifndef INVOKE_COMMANDS_H
#define INVOKE_COMMANDS_H

#include "tokenize.h"
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

typedef struct s_node
{
    t_token_type	kind;
    char			**argv;
    int				fd_in;
    int				fd_out;
    struct s_node	*next;
    struct s_node	*prev;
}	t_node;

void    invoke_commands(t_token *tokens);
#endif
