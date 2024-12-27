#include <invoke_commands.h>

char *find_executable_path(const t_node *parsed_tokens, char **path_list)
{
    int		i;
	char	*slash_cmd;
	char	*path;

    i = 0;
    path = NULL;
    slash_cmd = ft_strjoin("/", parsed_tokens->argv[0]);
    while (path_list[i])
    {
        path = ft_strjoin(path_list[i], slash_cmd);
        if (access(path, F_OK) == 0)
        {
            free(slash_cmd);
            return (path);
        }
        i++;
    }
    return (NULL);
}

int child_process(t_node *parsed_tokens, t_exe_info *info, char **path_list)
{
    // 最後以外のコマンドの場合
    // STDOUT → current_pipefd[1]
    if (info->exec_count < info->pipe_num)
    {
        wrap_dup2(parsed_tokens->fds[OUT], STDOUT_FILENO);
        wrap_close(parsed_tokens->fds[OUT]);
        wrap_close(parsed_tokens->fds[IN]);
    }
    // 初めのコマンド以外は、入力を前のpipefd[0]にリダイレクトする
    // STDIN → before_pipe_fd[0]
    if (info->exec_count > 0)
    {
        wrap_dup2(info->before_cmd_fd, STDIN_FILENO);
        wrap_close(info->before_cmd_fd);
    }
    execute(parsed_tokens, path_list);
    exit(EXIT_FAILURE);
}

int parent_process(t_node *parsed_tokens, t_exe_info *info)
{
    wrap_close(parsed_tokens->fds[OUT]);
    info->before_cmd_fd = parsed_tokens->fds[IN];
    return (EXIT_SUCCESS);
}

int execute(t_node *parsed_tokens, char **path_list)
{
	// TODO ビルトイン 作成
	// exec_builtin(parsed_tokens);
    execve(find_executable_path(parsed_tokens, path_list), parsed_tokens->argv, NULL);
    exit(EXIT_FAILURE);
}
