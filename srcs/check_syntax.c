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

static int	print_syntax_error(void)
{
	ft_putstr_fd("bash: syntax error near unexpected token `newline'\n",
		STDERR_FILENO);
	return (EXIT_STATUS_SYNTAX_ERROR);
}

static bool	check_quote_error(t_token *token)
{
	char	quote;
	int		i;

	i = 0;
	if (ft_strlen(token->data) == 1)
		return (EXIT_FAILURE);
	while (token->data[i])
	{
		if (is_quote(token->data[i]))
		{
			quote = token->data[i++];
			while (token->data[i] != quote)
			{
				if (!token->data[i])
					return (EXIT_FAILURE);
				i++;
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static bool	check_operators_error(t_token *token)
{
	if (token->next == NULL)
		return (EXIT_FAILURE);
	if (token->next->type != TOKEN_WORD)
		return (EXIT_FAILURE);
	if (token->data[0] == '|' && token->data[1] == '|')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	check_syntax(t_token *token, t_context *context)
{
	int	i;

	if (token->data[0] == '|')
		return (setting_exit_status(context, print_syntax_error()));
	while (token)
	{
		i = 0;
		while (token->data[i])
		{
			if (is_quote(token->data[i]))
			{
				if (check_quote_error(token) == EXIT_FAILURE)
					return (setting_exit_status(context, print_syntax_error()));
			}
			i++;
		}
		if (is_operators(token->data[0]))
		{
			if (check_operators_error(token) == EXIT_FAILURE)
				return (setting_exit_status(context, print_syntax_error()));
		}
		token = token->next;
	}
	return (EXIT_SUCCESS);
}
