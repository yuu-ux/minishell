/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:24:59 by yehara            #+#    #+#             */
/*   Updated: 2025/03/01 00:51:43 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_tokens(const char *line)
{
	size_t	count;

	count = 0;
	while (*line)
	{
		if (ft_isspace(*line))
			skip_while(ft_isspace, &line);
		else if (is_operators(*line))
		{
			count++;
			skip_while(is_operators, &line);
		}
		else if (is_quote(*line))
		{
			count++;
			skip_quoted_token(*line, &line);
		}
		else
		{
			count++;
			skip_non_delimiter(&line);
		}
	}
	return (count);
}

static char	**tokenize(const char *line)
{
	char	**tokens;
	size_t	word_num;
	size_t	index;
	size_t	moved;

	word_num = count_tokens(line);
	tokens = (char **)ft_xmalloc((word_num + 1) * sizeof(char *));
	index = 0;
	while (index < word_num)
	{
		moved = 0;
		skip_while(ft_isspace, &line);
		if (is_operators(*line))
			moved += skip_while(is_operators, &line);
		else if (is_quote(*line))
			moved += skip_quoted_token(*line, &line);
		else
			moved += skip_non_delimiter(&line);
		tokens[index] = (char *)ft_xmalloc((moved + 1) * sizeof(char));
		ft_memcpy(tokens[index], line - moved, moved);
		tokens[index][moved] = '\0';
		index++;
	}
	tokens[index] = NULL;
	return (tokens);
}

t_token	*tokenization(const char *line)
{
	t_token	*token;
	t_token	*new;
	char	**tokens;
	t_token	*head;
	int		i;

	head = NULL;
	token = NULL;
	i = 0;
	tokens = tokenize(line);
	while (tokens[i])
	{
		new = new_token(tokens[i], get_token_type(tokens[i]));
		if (head == NULL)
			head = new;
		else
			token->next = new;
		token = new;
		i++;
	}
	token->next = NULL;
	while (i >= 0)
		free(tokens[i--]);
	free(tokens);
	return (head);
}
