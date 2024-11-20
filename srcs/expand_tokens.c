#include "tokenize.h"
#include "expand.h"
#include "libft.h"

static char *expnad_nomal(kvs *path_list, const char *key)
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

static kvs *create_path(char **environ)
{
    kvs *path_list;
    char **temp;
    int i;
    int count;

    i = 0;
    count = 0;
    while (environ[i])
    {
        count++;
        i++;
    }
    path_list = (kvs *)malloc(sizeof(kvs) * (count+1));
    if (!path_list)
        return NULL;
    ft_memset(path_list, 0, sizeof(kvs));
    i = 0;
    while (environ[i])
    {
        temp = ft_split(environ[i], '=');
        path_list[i].key = temp[0];
        path_list[i].value = temp[1];
        free(temp);
        i++;
    }
    return (path_list);
}

static char *expand_double_quote(kvs *path_list, char *token)
{
    int variable_start_index;
    int variable_last_index;
    char *before_path_char;
    char *path;
    char *after_path_char;
    int i;
    char *result;

    i = 0;
    while (token[i])
    {
        if (token[i] == '$')
        {
            variable_start_index = i+1;
            while (token[++i] && ft_isalpha(token[i]))
                ;
            variable_last_index = i-variable_start_index;
        }
        i++;
    }
    // $PATH であれば start_index は P のインデックスで設定されているため、-2 する
    // ダブルクウォートを除きたいため、インデックス 1 から始める
    before_path_char = ft_substr(token, 1, variable_start_index-2);
    path = expnad_nomal(path_list, ft_substr(token, variable_start_index, variable_last_index));
    // ダブルクウォートを除きたいため、+1する
    after_path_char = ft_substr(token, variable_start_index+variable_last_index, i-(variable_start_index+variable_last_index+1));
    result = ft_strjoin(ft_strjoin(before_path_char, path), after_path_char);
    free(before_path_char);
    free(path);
    free(after_path_char);
    return (result);
}

t_token    *expand_tokens(t_token **_tokens)
{
    extern char **environ;
    kvs *path_list;
    t_token *head;
    t_token *tokens;

    path_list = create_path(environ);
    head = *_tokens;
    tokens = *_tokens;
    // TODO シングルクウォート外す
    // TODO シェル変数の展開が必要かどうか聞く
    while (tokens)
    {
        if (tokens->data[0] == DOUBLE_QUOTE)
            tokens->data = expand_double_quote(path_list, tokens->data);
        else if (tokens->data[0] == '$')
            tokens->data = expnad_nomal(path_list, &tokens->data[1]);
        tokens = tokens->next;
    }
    return (head);
}
