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

static size_t count_word_node(t_token *tokens)
{
    size_t count;

    count = 0;
    while (tokens && (tokens->type != TOKEN_PIPE))
	{
        count++;
		tokens = tokens->next;
	}
    return (count);
}

static char **create_argv(t_token *tokens)
{
    char **result;
    int i;
    size_t word_num;

    word_num = count_word_node(tokens);
	if (word_num == 0)
		return NULL;
    result = (char **)malloc((word_num+1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
    i = 0;
    while (i < (int)word_num)
    {
        result[i++] = ft_strdup(tokens->data);
        tokens = tokens->next;
    }
	result[i] = NULL;
    return (result);
}

void	print_node(t_node *head)
{
	t_node *current;
	int	i;

    current = head;
    while (current)
    {
        if (current->argv != NULL)
        {
			i = 0;
            while (current->argv[i])
                printf("argv:%s\n", current->argv[i++]);
        }
        printf("in:%d\n", current->fd_in);
        printf("out:%d\n", current->fd_out);
        printf("---------------------------------\n");
        current = current->next;
    }
}

static t_node *parse(t_token *tokens)
{
    t_node *head = NULL;
    t_node *current = NULL;

    while (tokens)
    {
        if (head == NULL)
        {
            head = new_node();
            current = head;
        }
        current->argv = create_argv(tokens);
        if (current->argv != NULL)
        {
            while (tokens && tokens->type != TOKEN_PIPE)
                tokens = tokens->next;
        }
        else
        {
            if (tokens && tokens->type == TOKEN_PIPE)
                tokens = tokens->next;
            else
                tokens = tokens->next;
        }
        if (tokens)
        {
            current->next = new_node();
            current->next->prev = current;
            current = current->next;
        }
    }
    print_node(head);
    return head;
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
