#include "../includes/tokenize.h"
#include "../libft/libft.h"

int ft_isspace(int c)
{
    return ('\t' == c || '\n' == c || '\v' == c
            || '\f' == c || '\r' == c || ' ' == c);
}
int is_metacharacter(int c)
{
    return ('|' == c || c == '<' || c == '>');
}

int is_quote(int c)
{
    return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

size_t  count_tokens(char *line)
{
    size_t  result;

    result = 0;
    while (*line)
    {
        if (ft_isspace(*line))
        {
            while (ft_isspace(*line) && *line)
                line++;
        }
        else if (is_metacharacter(*line))
        {
            result++;
            while (is_metacharacter(*line) && *line)
                line++;
        }
        else if (is_quote(*line++))
        {
            result++;
            while (!is_quote(*line) && *line)
                line++;
            line++;
        }
        else
        {
            result++;
            while (!(is_metacharacter(*line) || is_quote(*line) || ft_isspace(*line)) && *line)
                line++;
        }
    }
    return (result);
}

char    **tokenize(char *line)
{
    char **tokens = NULL;
    size_t  word_num;
    size_t  i;
    size_t  j;

    i = 0;
    word_num = count_tokens(line);
    tokens = (char **)malloc((word_num + 1) * sizeof(char *));
    if (!tokens)
        return (NULL);
    while (i < word_num)
    {
        j = 0;
        while (ft_isspace(*line) && *line)
            line++;
        if (is_metacharacter(*line))
        {
            while (is_metacharacter(*line) && *line)
            {
                line++;
                j++;
            }
        }
        else if (is_quote(*line))
        {
            j++;
            line++;
            while (!is_quote(*line) && *line)
            {
                line++;
                j++;
            }
            line++;
            j++;
        }
        else
        {
            while (!(is_metacharacter(*line) || is_quote(*line) || ft_isspace(*line)) && *line)
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

t_token *new_token(char *line, t_token_type type)
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

t_token_type    get_token_type(char *token)
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

t_token    *tokenization(char *line)
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
    return (head);
}

