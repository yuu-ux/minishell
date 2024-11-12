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
    token = NULL;
    tokens = ft_split(line, ' ');
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
