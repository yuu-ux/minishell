#include "tokenize.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static  void    print_syntax_error()
{
    ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
    exit(SYNTAX_ERROR);
}

static void    check_quote_error(t_token *token)
{
    int last_index;

    last_index = ft_strlen(token->data) - 1;
    if (last_index == 0)
        print_syntax_error();
    if (token->data[0] != token->data[last_index])
        print_syntax_error();
    return ;
}

static void    check_operators_error(t_token *token)
{
    if (!token->next)
        print_syntax_error();
    if (token->next->type != TOKEN_WORD)
        print_syntax_error();
    if (token->data[0] == '|' && token->data[1] == '|')
        print_syntax_error();
}

void    check_syntax(t_token *token)
{
    if (is_operators(token->type))
        print_syntax_error();
    while (token)
    {
        if (is_quote(token->data[0]))
            check_quote_error(token);
        if (is_operators(token->data[0]))
            check_operators_error(token);
        token = token->next;
    }
}
