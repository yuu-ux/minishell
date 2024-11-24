#include "tokenize.h"
#include "expand.h"
#include "libft.h"

static char *search_path(kvs *path_list, const char *key)
{
    int i;

    i = 0;
    while (path_list[i].key)
    {
        // null 文字まで比較させるための+1
        if (!ft_strncmp(path_list[i].key, key, ft_strlen(path_list[i].key)+1))
            return (path_list[i].value);
        i++;
    }
    return (NULL);
}

static char *expand_double_quote(kvs *path_list, char *token)
{
    int i;
    int j;
    int start;
    char *result;
    size_t len;
    char *value;
    char *temp;

    i = 0;
    j = 0;
    len = ft_strlen(token);
    result = (char *)ft_xmalloc((len + 1) * sizeof(char));
    while (token[i])
    {
        if (token[i] == '$')
        {
            start = i+1;
            while (token[++i] && (ft_isalpha(token[i]) || token[i] == '_'))
                ;
            value = search_path(path_list, ft_substr(token, start, i-start));
            // PATH 以外の文字 + PATH 展開後の文字数
            temp = (char *)ft_realloc(result, ft_strlen(value)+1);
            ft_strlcat(temp, value, ft_strlen(value)+1);
        }
        else if (token[i] != DOUBLE_QUOTE)
            result[j++] = token[i];
        i++;
    }
    return (temp);
}

t_token    *expand_tokens(t_token **_tokens, kvs *path_list)
{
    t_token *head;
    t_token *tokens;

    // TODO main の方で一回よびだす
    // unset で消えることもある
    // environは自動で更新されないため、更新する必要がある
    head = *_tokens;
    tokens = *_tokens;
    while (tokens)
    {
        if (tokens->data[0] == DOUBLE_QUOTE)
            tokens->data = expand_double_quote(path_list, tokens->data);
        //else if (tokens->data[0] == '$')
        //    tokens->data = search_path(path_list, &tokens->data[1]);
        else if (tokens->data[0] == SINGLE_QUOTE)
            tokens->data = ft_substr(tokens->data, 1, ft_strlen(tokens->data)-2);
        tokens = tokens->next;
    }
    return (head);
}
