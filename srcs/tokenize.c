/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmogami <kmogami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:45:02 by kmogami           #+#    #+#             */
/*   Updated: 2024/11/16 20:45:03 by kmogami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenize.h>
#include <libft.h>
#include <debug.h>

static size_t	skip_quoted_token(char quote_char, const char **line)
{
	size_t moved;

	moved = 0;
	while (**line)
	{
		// echo "hello""world"をひとつのトークンとして持ちたいため次がスペースかチェックする
		if (**line == quote_char && **(line+1) == ' ')
		{
			(*line)++;
			moved++;
			break;
		}
		(*line)++;
		moved++;
	}
	return (moved);
}

static size_t	skip_while(int	(*is_skip)(int), const char **line)
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

static size_t  count_tokens(const char *line)
{
    size_t  count;

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
			skip_quoted_token(*(line++), &line);
        }
        else
        {
            count++;
            while (!(is_operators(*line) || is_quote(*line) || ft_isspace(*line)) && *line)
                line++;
        }
    }
    return (count);
}


static char    **tokenize(const char *line)
{
    char **tokens = NULL;
    size_t  word_num;
    size_t  index;
    size_t  moved;

    index = 0;
    word_num = count_tokens(line);
    tokens = (char **)malloc((word_num + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	moved = 0;
    while (index < word_num)
    {
		skip_while(ft_isspace, &line);
        if (is_operators(*line))
			moved += skip_while(is_operators, &line);
        else if (is_quote(*line))
			moved += skip_quoted_token(*(line++), &line);
        else
        {
            while (!(is_operators(*line) || is_quote(*line) || ft_isspace(*line)) && *line)
            {
                moved++;
                line++;
            }
        }
        tokens[index] = (char *)malloc((moved + 1) * sizeof(char));
        ft_memcpy(tokens[index], line-moved, moved);
        tokens[index][moved] = '\0';
        index++;
    }
    tokens[index] = NULL;
    return (tokens);
}

static t_token *new_token(const char *line, t_token_type type)
{
    t_token *token;

    if (!line)
        return (NULL);
    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->data = ft_strdup(line);
    token->next = NULL;
    token->type = type;
    return (token);
}

static t_token_type    get_token_type(const char *token)
{
    if (*token == '|')
        return (TOKEN_PIPE);
    else if (*token == '<' && *(token+1) == '<')
        return (TOKEN_REDIRECT_HEREDOC);
    else if (*token == '>' && *(token+1) == '>')
        return (TOKEN_REDIRECT_APPEND);
    else if (*token == '<')
        return (TOKEN_REDIRECT_IN);
    else if (*token == '>')
        return (TOKEN_REDIRECT_OUT);
    else
        return (TOKEN_WORD);
}

t_token    *tokenization(const char *line)
{
    t_token	*token;
    t_token	*new;
    char    **tokens;
    t_token *head = NULL;
    int i;

    i = 0;
	if (line == NULL)
		return (NULL);
    tokens = tokenize(line);
    while (tokens[i])
    {
        new = new_token(tokens[i], get_token_type(tokens[i]));
        if (!head)
            head = new;
        else
            token->next = new;
        token = new;
        i++;
    }
	token->next = NULL;
	print_token(head);
    return (head);
}

