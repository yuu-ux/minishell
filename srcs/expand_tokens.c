#include <tokenize.h>
#include <expand.h>
#include <libft.h>

static char *search_path(const char *key, kvs *path_list)
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
    return (ft_strdup(""));
}

static size_t  count_path_len(char *token, int t_index)
{
    size_t  i;

    i = 0;
    while ((ft_isalnum(token[t_index]) || token[t_index] == '_') && token[t_index])
    {
        i++;
        t_index++;
    }
    return (i);
}

static char *expand_token(char *token, kvs *path_list)
{
    int t_index;
    int r_index;
    char *value;
    char *result;
    size_t key_len;

    t_index = 0;
    r_index = 0;
    result = (char *)ft_xmalloc((ft_strlen(token) + 1) * sizeof(char));
    while (token[t_index])
    {
        if (token[t_index] == '$')
        {
            key_len = count_path_len(token, t_index+1);
            value = search_path(ft_substr(token, t_index+1, key_len), path_list);
            result = ft_strjoin(result, value);
            // value を展開した長さ + 元々の token の長さ
            result = (char *)ft_realloc(result, ft_strlen(result) + ft_strlen(token));
            t_index += key_len+1;
            r_index += ft_strlen(value);
        }
        else if (token[t_index] == DOUBLE_QUOTE)
        {
            t_index++;
            continue;
        }
        else
        {
            result[r_index] = token[t_index];
            r_index++;
            t_index++;
        }
    }
    return (result);
}

static char    *delete_single_quote(char *token)
{
    char *result;
    int t_index;
    int r_index;

    // token の文字数 - シングルクウォートの文字数 + nul 文字
    result = (char *)ft_xmalloc((ft_strlen(token) - 2 + 1) * sizeof(char));
    t_index = 0;
    r_index = 0;
    while (token[t_index])
    {
        if (token[t_index] == SINGLE_QUOTE)
        {
            t_index++;
            continue;
        }
        result[r_index] = token[t_index];
        t_index++;
        r_index++;
    }
    return result;
}

t_token    *expand_tokens(t_token **_tokens, kvs *path_list)
{
    t_token *head;
    t_token *tokens;

    head = *_tokens;
    tokens = *_tokens;
    while (tokens)
    {
        if (tokens->data[0] == SINGLE_QUOTE)
            tokens->data = delete_single_quote(tokens->data);
        else
            tokens->data = expand_token(tokens->data, path_list);
        tokens = tokens->next;
    }
    return (head);
}
