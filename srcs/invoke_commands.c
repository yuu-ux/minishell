#include "invoke_commands.h"

t_node  *new_node()
{
    t_node *node;

    node = (t_node *)malloc(sizeof(t_node));
    if (node == NULL)
        return (NULL);
    node->fd_in = INVALID_FD;
    node->fd_out = INVALID_FD;
    node->next = NULL;
    node->prev = NULL;
    return (node);
}

t_node	*last_node(t_node *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

static size_t count_word_node(t_token *tokens)
{
    size_t count;

    count = 0;
    while (tokens->data && tokens->type != TOKEN_PIPE)
        count++;
    return (count);
}

static char **create_argv(t_token **tokens)
{
    char **result;
    int i;
    size_t word_num;

    i = 0;
    word_num = count_word_node(*tokens);
    result = (char **)malloc(word_num * sizeof(char *));
    while (i < (int)word_num)
    {
        result[i++] = ft_strdup((*tokens)->data);
        free((*tokens)->data);
        *tokens = (*tokens)->next;
    }
    return (result);
}

static t_node *parse(t_token *tokens)
{
    t_node *head;
    t_node *current;

    head = NULL;
    while (tokens->data)
    {
        current = last_node(head);
        current->next = new_node();
        if (current == NULL)
            return (NULL);
        current->argv = create_argv(&tokens);
        // kind 判定
        if (head == current)
            current->next->prev = NULL;
        else
            current->next->prev = current;
    }
    //while (current)
    //{
    //    int i = 0;
    //    printf("kind:%d\n", current->kind);
    //    while (current->argv[i])
    //        printf("argv:%s\n", current->argv[i++]);
    //    printf("in:%d\n", current->fd_in);
    //    printf("out:%d\n", current->fd_out);
    //    printf("---------------------------------\n");
    //    current = current->next;
    //}
    return (head);
}

void    invoke_commands(t_token *tokens)
{
    // パース
    // シグナル設定
    // 実行
    parse(tokens);
    //argv = (char **)malloc(sizeof(char*) * 3);
    //argv[0] = ft_strdup(tokens->data);
    //execve(tokens->data, argv, NULL);
    //while (tokens)
    //{
    //    printf("%s\n", tokens->data);
    //    tokens = tokens->next;
    //}
}
