/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:04:06 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/02/26 18:04:54 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static  void    print_syntax_error()
{
    ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
    exit(SYNTAX_ERROR);
}

static void    check_quote_error(t_token *token)
{
    char quote;
    int i;

    i = 0;
    if (ft_strlen(token->data) == 1)
        print_syntax_error();
    while (token->data[i])
    {
        if (is_quote(token->data[i]))
        {
            quote = token->data[i++];
            while (token->data[i] != quote)
            {
                if (!token->data[i])
                    print_syntax_error();
                i++;
            }
        }
        i++;
    }
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
	int	i;

    if (token->data[0] == '|')
        print_syntax_error();
    while (token)
    {
		i = 0;
		while (token->data[i])
		{
			if (is_quote(token->data[i]))
				check_quote_error(token);
			i++;
		}
        if (is_operators(token->data[0]))
            check_operators_error(token);
        token = token->next;
    }
}
