#include <invoke_commands.h>
#include <debug.h>

static t_node  *new_node()
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->fds[IN] = INVALID_FD;
	node->fds[OUT] = INVALID_FD;
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

static void    advance_token_after_free(t_token **token)
{
    t_token *temp;
    char *data;

    temp = *token;
    data = (*token)->data;
    (*token) = (*token)->next;
    free(data);
    free(temp);
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


t_node *parse(t_token *tokens)
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
            current->kind = CMD;
            while (tokens && tokens->type != TOKEN_PIPE)
                advance_token_after_free(&tokens);
        }
        else
        {
            current->kind = PIPE;
            advance_token_after_free(&tokens);
        }
        if (tokens)
        {
            current->next = new_node();
            current->next->prev = current;
            current = current->next;
        }
    }
    return head;
}

