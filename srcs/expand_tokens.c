/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:05:08 by yehara            #+#    #+#             */
/*   Updated: 2025/02/26 18:19:01 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	delete_single_quote(char **result, char *token)
{
	size_t	i;

	i = 0;
	i++;
	while (token[i] != SINGLE_QUOTE)
		i++;
	*result = free_strjoin(*result, ft_substr(token, 1, i - 1));
	// 「'」の次を指すために、+1
	return (i + 1);
}

static size_t	expand_double_quote(char **result, char *token, bool flg_heredoc, t_context *context)
{
	int	i;
	int		start;

	i = 1;
	start = 1;
	while (token[i] != DOUBLE_QUOTE)
	{
		if (is_expand(token, i) && !flg_heredoc)
		{
			*result = free_strjoin(*result, ft_substr(token, start, i - start));
			i += insert_env(result, &token[i], context);
			// 「"」と「$」のため、i+1
			start = i + 1;
		}
		i++;
	}
	*result = free_strjoin(*result, ft_substr(token, start, i - start));
	return (i + 1);
}

size_t	expand_variable(char **result, char *token, t_context *context,
		int start, int i)
{
	*result = free_strjoin(*result, ft_substr(token, start, i - start));
	i += insert_env(result, &token[i], context);
	return (i + 1);
}

static char	*expand_token(char *token, bool flg_heredoc, t_context *context)
{
	int		i;
	char	*result;
	int		start;

	i = 0;
	start = 0;
	result = ft_strdup("");
	while (token[i])
	{
		if (token[i] == SINGLE_QUOTE)
			i = delete_single_quote(&result, &token[i]);
		else if (token[i] == DOUBLE_QUOTE)
			i = expand_double_quote(&result, &token[i], flg_heredoc, context);
		else if (is_expand(token, i) && !flg_heredoc)
			i = expand_variable(&result, token, context, start, i);
		else
		{
			i++;
			if (is_quote(token[i]))
				result = free_strjoin(result, ft_substr(token, start, i - start));
			// 変数展開したときのみ、start を更新したいため、continue する
			continue ;
		}
		start = i;
	}
	result = free_strjoin(result, ft_substr(token, start, i - start));
	return (result);
}

static void	set_flg_heredoc_expand(t_token *token, t_context *context)
{
	if (ft_strchr(token->data, SINGLE_QUOTE) != NULL || ft_strchr(token->data, DOUBLE_QUOTE) != NULL)
		context->flg_heredoc_expand = false;
}

t_token	*expand_tokens(t_token **_tokens, t_context *context)
{
	t_token	*head;
	t_token	*tokens;
    char    *temp;
	bool	flg_heredoc;

	flg_heredoc = false;
	head = *_tokens;
	tokens = *_tokens;
	while (tokens)
	{
        temp = tokens->data;
		if (is_heredoc(tokens->data))
		{
			flg_heredoc = true;
			set_flg_heredoc_expand(tokens->next, context);
		}
		tokens->data = expand_token(tokens->data, flg_heredoc, context);
        free(temp);
		tokens = tokens->next;
	}
	return (head);
}

