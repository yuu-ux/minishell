#include <invoke_commands.h>
#include <debug.h>
#include <signal_setting.h>

static t_node  *new_node()
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
            current->kind = CMD;
            while (tokens && tokens->type != TOKEN_PIPE)
                tokens = tokens->next;
        }
        else
        {
            current->kind = PIPE;
            tokens = tokens->next;
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

//int exec_builtin(t_node *parsed_tokens)
//{
//    if (ft_strncmp(parsed_tokens->argv[0], "echo", 5))
//        built_echo();
//    else if (ft_strncmp(parsed_tokens->argv[0], "cd", 3))
//        built_cd();
//    else if (ft_strncmp(parsed_tokens->argv[0], "pwd", 4))
//        built_pwd();
//    else if (ft_strncmp(parsed_tokens->argv[0], "export", 7))
//        built_export();
//    else if (ft_strncmp(parsed_tokens->argv[0], "unset", 6))
//        built_unset();
//    else if (ft_strncmp(parsed_tokens->argv[0], "env", 4))
//        built_env();
//    else if (ft_strncmp(parsed_tokens->argv[0], "exit", 5))
//        built_exit();
//    else
//        return 1;
//}

int exec_cmd(t_node *parsed_tokens, char **path)
{
    int i;
    //print_node(parsed_tokens);
    // ビルトイン
    //exec_builtin(parsed_tokens);
    if (parsed_tokens->argv[0][0] == '/')
    {
        // 絶対パス
        while (parsed_tokens)
        {
            if (access(parsed_tokens->argv[0], F_OK) == 0)
                execve(parsed_tokens->argv[0], parsed_tokens->argv, NULL);
            parsed_tokens = parsed_tokens->next;
        }
    }
    else
    {
        // 相対パスで渡されたパターン
        while (parsed_tokens)
        {
            i = 0;
            while (path[i])
            {
                char *temp = ft_strjoin(path[i], "/");
                char *res = ft_strjoin(temp, parsed_tokens->argv[0]);
                if (access(res, F_OK) == 0)
                    execve(res, parsed_tokens->argv, NULL);
                i++;
            }
            parsed_tokens = parsed_tokens->next;
        }
    }
    return 1;
}

char **get_path(char *path)
{
    char **result;

    result = ft_split(path, ':');
    return (result);
}

void    invoke_commands(t_token *tokens)
{
    t_node *parsed_tokens;
    char **path;

    path = get_path(getenv("PATH"));
    parsed_tokens = parse(tokens);
    signal_setting();
    exec_cmd(parsed_tokens, path);
}
