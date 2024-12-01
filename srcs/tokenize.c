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

static size_t  count_tokens(const char *line)
{
    size_t  result;
    char quote_char;

    result = 0;
    while (*line)
    {
        if (ft_isspace(*line))
        {
            while (ft_isspace(*line) && *line)
                line++;
        }
        else if (is_operators(*line))
        {
            result++;
            while (is_operators(*line) && *line)
                line++;
        }
        else if (is_quote(*line))
        {
            result++;
            quote_char = *line++;
            while (*line)
            {
                // echo "hello""world"をひとつのトークンとして持ちたいため次がスペースかチェックする
                if (*line == quote_char && *(line+1) == ' ')
                {
                    line++;
                    break;
                }
                line++;
            }
        }
        else
        {
            result++;
            while (!(is_operators(*line) || is_quote(*line) || ft_isspace(*line)) && *line)
                line++;
        }
    }
    return (result);
}

static char    **tokenize(const char *line)
{
    char **tokens = NULL;
    size_t  word_num;
    size_t  i;
    size_t  j;
    char    quote_char;

    i = 0;
    word_num = count_tokens(line);
    tokens = (char **)ft_xmalloc((word_num + 1) * sizeof(char *));
    if (!tokens)
        return (NULL);
    while (i < word_num)
    {
        j = 0;
        while (ft_isspace(*line) && *line)
            line++;
        if (is_operators(*line))
        {
            while (is_operators(*line) && *line)
            {
                line++;
                j++;
            }
        }
        else if (is_quote(*line))
        {
            quote_char = *line;
            while (*line)
            {
                line++;
                j++;
                if (*line == quote_char && *(line+1) == ' ')
                {
                        line++;
                        j++;
                        break;
                }
            }
        }
        else
        {
            while (!(is_operators(*line) || is_quote(*line) || ft_isspace(*line)) && *line)
            {
                j++;
                line++;
            }
        }
        tokens[i] = (char *)malloc((j + 1) * sizeof(char));
        ft_memcpy(tokens[i], line-j, j);
        tokens[i][j] = '\0';
        i++;
    }
    tokens[i] = NULL;
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
    t_token *token;
    t_token *new;
    char    **tokens;
    t_token *head = NULL;
    int i;

    i = 0;
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
    return (head);
}

