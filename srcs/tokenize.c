#include "../includes/tokenize.h"
#include "../libft/libft.h"

int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

int ft_isoperator(int c)
{
    return (c == '|' || c == '<' || c == '>');
}

int ft_isquote(int c)
{
    return (c == '\'' || c == '\"');
}

size_t  count_tokens(char *line)
{
    size_t  result;

    result = 0;
    while (*line)
    {
        while (ft_isspace(*line))
            line++;
        if (ft_isquote(*line))
        {
            result++;
            line++;
            while (!ft_isquote(*line) && *line)
                line++;
            line++;
        }
        if (ft_isalnum(*line) || ft_isoperator(*line))
        {
            result++;
            while ((ft_isalnum(*line) || ft_isoperator(*line)) && *line)
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
        while (ft_isspace(*line))
            line++;
        if (ft_isquote(*line))
        {
            line++;
            j++;
            while (!ft_isquote(*line) && *line)
            {
                line++;
                j++;
            }
            tokens[i] = (char *)malloc((j + 1) * sizeof(char));
            tokens[i][j] = '\0';
            line++;
            j++;
            ft_memcpy(tokens[i], line-j, j);
        }
        if (ft_isalnum(*line) || ft_isoperator(*line))
        {
            while ((ft_isalnum(*line) || ft_isoperator(*line)) && *line)
            {
                line++;
                j++;
            }
            tokens[i] = (char *)malloc((j + 1) * sizeof(char));
            ft_memcpy(tokens[i], line-j, j);
            tokens[i][j] = '\0';
        }
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
        new = new_token(tokens[i], ARG);
        if (!head)
            head = new;
        else
            token->next = new;
        token = new;
        i++;
    }
    return (head);
}
