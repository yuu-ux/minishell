#include "tokenize.h"
#include "expand.h"
#include "libft.h"

static char *search_path(kvs *path_list, const char *key)
{
    int i;

    i = 0;
    key++;
    while (path_list[i].key)
    {
        if (!ft_strncmp(path_list[i].key, key, ft_strlen(key)))
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
    i = 0;
    while (environ[i])
    {
        temp = ft_split(environ[i], '=');
        path_list[i].key = temp[0];
        path_list[i].value = temp[1];
        i++;
    }
    path_list[i].key = NULL;
    path_list[i].value = NULL;
    return (path_list);
}

t_token    *expand_tokens(t_token **tokens)
{
    extern char **environ;
    kvs *path_list;
    t_token *head;

    path_list = create_path(environ);
    head = *tokens;
    while (*tokens)
    {
        if ((*tokens)->data[0] == '$')
            (*tokens)->data = search_path(path_list, (*tokens)->data);
        *tokens = (*tokens)->next;
    }
    return (head);
}
