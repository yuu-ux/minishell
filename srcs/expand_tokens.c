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

#include "expand.h"
#include "invoke_commands.h"
#include "tokenize.h"
#include "utils.h"

static size_t	delete_single_quote(char **result, t_expand expand)
{
	*result = free_strjoin(*result, ft_substr(expand.token, expand.start,
				expand.index - expand.start));
	expand.start = ++expand.index;
	while (expand.token[expand.index] != SINGLE_QUOTE)
		expand.index++;
	*result = free_strjoin(*result, ft_substr(expand.token, expand.start,
				expand.index - expand.start));
	return (expand.index + 1);
}

static size_t	expand_double_quote(char **result, t_expand expand,
		bool flg_heredoc)
{
	*result = free_strjoin(*result, ft_substr(expand.token, expand.start,
				expand.index - expand.start));
	expand.start = ++expand.index;
	while (expand.token[expand.index] != DOUBLE_QUOTE)
	{
		if (is_expand(expand.token, expand.index) && !flg_heredoc)
		{
			*result = free_strjoin(*result, ft_substr(expand.token,
						expand.start, expand.index - expand.start));
			expand.index += insert_env(result, &expand.token[expand.index],
					expand.context);
			expand.start = expand.index + 1;
		}
		expand.index++;
	}
	*result = free_strjoin(*result, ft_substr(expand.token, expand.start,
				expand.index - expand.start));
	return (expand.index + 1);
}

size_t	expand_variable(char **result, t_expand expand)
{
	*result = free_strjoin(*result, ft_substr(expand.token, expand.start,
				expand.index - expand.start));
	expand.index += insert_env(result, &expand.token[expand.index],
			expand.context);
	return (expand.index + 1);
}

static char	*expand_token(t_expand expand, bool flg_heredoc)
{
	char	*result;

	expand.index = 0;
	expand.start = 0;
	result = ft_strdup("");
	while (expand.token[expand.index])
	{
		if (expand.token[expand.index] == SINGLE_QUOTE)
			expand.index = delete_single_quote(&result, expand);
		else if (expand.token[expand.index] == DOUBLE_QUOTE)
			expand.index = expand_double_quote(&result, expand, flg_heredoc);
		else if (is_expand(expand.token, expand.index) && !flg_heredoc)
			expand.index = expand_variable(&result, expand);
		else
		{
			if (is_quote(expand.token[expand.index++]))
				result = free_strjoin(result, ft_substr(expand.token,
							expand.start, expand.index - expand.start));
			continue ;
		}
		expand.start = expand.index;
	}
	result = free_strjoin(result, ft_substr(expand.token, expand.start,
				expand.index - expand.start));
	return (result);
}

t_token	*expand_tokens(t_token **_tokens, t_context *context)
{
	t_token		*head;
	t_token		*tokens;
	char		*temp;
	bool		flg_heredoc;
	t_expand	expand;

	flg_heredoc = false;
	head = *_tokens;
	tokens = *_tokens;
	expand.context = context;
	while (tokens)
	{
		temp = tokens->data;
		if (is_heredoc(tokens->data))
		{
			flg_heredoc = true;
			set_flg_heredoc_expand(tokens->next, context);
		}
		expand.token = tokens->data;
		tokens->data = expand_token(expand, flg_heredoc);
		free(temp);
		tokens = tokens->next;
	}
	return (head);
}
