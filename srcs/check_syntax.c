#include "tokenize.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void    check_quote_error(t_token *token)
{
    int last_index;

    last_index = ft_strlen(token->data) - 1;
    if (last_index == 0)
        exit(SYNTAX_ERROR);
    if (token->data[0] != token->data[last_index])
        exit(SYNTAX_ERROR);
    return ;
}

void    check_operators_error(t_token *token)
{
    if (!token->next)
        exit(SYNTAX_ERROR);
    if (token->next->type != TOKEN_WORD)
        exit(SYNTAX_ERROR);
    if (token->data[0] == '|' && token->data[1] == '|')
        exit(SYNTAX_ERROR);
}

void    check_syntax(t_token *token)
{
    if (is_operators(token->type))
        exit(SYNTAX_ERROR);
    while (token)
    {
        if (is_quote(token->data[0]))
            check_quote_error(token);
        if (is_operators(token->data[0]))
            check_operators_error(token);
        token = token->next;
    }
}
