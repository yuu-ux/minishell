/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:20:13 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/02/26 18:20:14 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "utils.h"

t_token	*new_token(const char *line, t_token_type type)
{
	t_token	*token;

	if (!line)
		return (NULL);
	token = (t_token *)ft_xmalloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->data = ft_strdup(line);
	token->next = NULL;
	token->type = type;
	return (token);
}

size_t	skip_quoted_token(char quote_char, const char **line)
{
	size_t	moved;
	bool	flg_close;

	moved = 0;
	flg_close = false;
	while (**line)
	{
		(*line)++;
		moved++;
		if (**line == quote_char)
		{
			(*line)++;
			moved++;
			if (flg_close == false)
				flg_close = true;
			else
				flg_close = false;
			if (**line == '\0')
				break ;
			if ((**line == ' ' || **line == '\t') && (flg_close == true))
				break ;
			continue ;
		}
	}
	return (moved);
}

size_t	skip_while(int (*is_skip)(int), const char **line)
{
	size_t	moved;

	moved = 0;
	while (**line && is_skip(**line))
	{
		(*line)++;
		moved++;
	}
	return (moved);
}

size_t	skip_non_delimiter(const char **line)
{
	size_t	moved;

	moved = 0;
	while (!(is_operators(**line) || ft_isspace(**line)) && **line)
	{
		moved++;
		(*line)++;
		if (is_quote(**line))
			moved += skip_quoted_token(**line, line);
	}
	return (moved);
}
