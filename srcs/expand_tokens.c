/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:05:08 by yehara            #+#    #+#             */
/*   Updated: 2025/02/26 18:19:01 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "invoke_commands.h"
#include "expand.h"
#include "tokenize.h"
#include "utils.h"

static size_t	delete_single_quote(char **result, t_expand expand, int start, int i)
{
	*result = free_strjoin(*result, ft_substr(expand.token, start, i - start));
	start = ++i;
	while (expand.token[i] != SINGLE_QUOTE)
		i++;
	*result = free_strjoin(*result, ft_substr(expand.token, start, i - start));
	// 「'」の次を指すために、+1
	return (i + 1);
}

static size_t	expand_double_quote(char **result, t_expand expand,
		bool flg_heredoc)
{
	int	i;
	int	start;

	i = 1;
	start = 1;
	while (expand.token[i] != DOUBLE_QUOTE)
	{
		if (is_expand(expand.token, i) && !flg_heredoc)
		{
			*result = free_strjoin(*result, ft_substr(expand.token, start,
						i - start));
			i += insert_env(result, &expand.token[i], expand.context);
			// 「"」と「$」のため、i+1
			start = i + 1;
		}
		i++;
	}
	*result = free_strjoin(*result, ft_substr(expand.token, start, i - start));
	return (i + 1);
}

size_t	expand_variable(char **result, t_expand expand, int start, int i)
{
	*result = free_strjoin(*result, ft_substr(expand.token, start, i - start));
	i += insert_env(result, &expand.token[i], expand.context);
	return (i + 1);
}

static char	*expand_token(t_expand expand, bool flg_heredoc)
{
	int		i;
	char	*result;
	int		start;

	i = 0;
	start = 0;
	result = ft_strdup("");
	while (expand.token[i])
	{
		if (expand.token[i] == SINGLE_QUOTE)
			i = delete_single_quote(&result, expand, start, i);
		else if (expand.token[i] == DOUBLE_QUOTE)
			i = expand_double_quote(&result, expand, flg_heredoc);
		else if (is_expand(expand.token, i) && !flg_heredoc)
			i = expand_variable(&result, expand, start, i);
		else
		{
			if (is_quote(expand.token[i++]))
				result = free_strjoin(result, ft_substr(expand.token, start,
							i - start));
			// 変数展開したときのみ、start を更新したいため、continue する
			continue ;
		}
		start = i;
	}
	result = free_strjoin(result, ft_substr(expand.token, start, i - start));
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
