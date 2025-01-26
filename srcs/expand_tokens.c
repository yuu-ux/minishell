/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:05:08 by yehara            #+#    #+#             */
/*   Updated: 2025/01/23 21:38:04 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <debug.h>
#include <expand.h>
#include <libft.h>
#include <tokenize.h>

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

static size_t	expand_double_quote(char **result, char *token, kvs *env_list)
{
	size_t	i;
	int		start;

	i = 1;
	start = 1;
	while (token[i] != DOUBLE_QUOTE)
	{
		if (token[i] == '$')
		{
			*result = free_strjoin(*result, ft_substr(token, start, i - start));
			i += insert_env(result, &token[i], env_list);
			// 「"」と「$」のため、i+1
			start = i + 1;
		}
		i++;
	}
	*result = free_strjoin(*result, ft_substr(token, start, i - start));
	return (i + 1);
}

static size_t	expand_variable(char **result, char *token, kvs *env_list,
		int start, int i)
{
	*result = free_strjoin(*result, ft_substr(token, start, i - start));
	i += insert_env(result, &token[i], env_list);
	return (i + 1);
}

static char	*expand_token(char *token, kvs *env_list)
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
			i += delete_single_quote(&result, &token[i]);
		else if (token[i] == DOUBLE_QUOTE)
			i += expand_double_quote(&result, &token[i], env_list);
		else if (token[i] == '$')
			i += expand_variable(&result, token, env_list, start, i);
		else
		{
			i++;
			// 変数展開したときのみ、start を更新したいため、continue する
			continue ;
		}
		start = i;
	}
	result = free_strjoin(result, ft_substr(token, start, i - start));
	return (result);
}

t_token	*expand_tokens(t_token **_tokens, kvs *env_list)
{
	t_token	*head;
	t_token	*tokens;
    char    *temp;

	head = *_tokens;
	tokens = *_tokens;
	while (tokens)
	{
        temp = tokens->data;
		tokens->data = expand_token(tokens->data, env_list);
        free(temp);
		tokens = tokens->next;
	}
	return (head);
}

