#include "../include/tokenize.h"
#include "../libft/libft.h"

t_token *new_token(char *line, t_token_type type)
{
    t_token *token;

    if (!line)
        return (NULL);
    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->data = line;
    token->next = NULL;
    token->type = type;
    return (token);
}

t_token    *tokenization(char *line)
{
    t_token *token;
    t_token *next;
    char **result;
    int i;

    i = 0;
    result = ft_split(line, ' ');
    while (result[i] && result[i+1])
    {
        token = new_token(result[i], ARG);
        token->next = new_token(result[i+1], ARG);
        token->next = next;
        i++;
    }
    return (token);
}
