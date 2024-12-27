#include <debug.h>
#include <invoke_commands.h>

// int exec_builtin(t_node *parsed_tokens)
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
//        return (1);
//}


static int	exec_single_cmd(const t_node *parsed_tokens, char **path_list)
{
    pid_t	pid;

	// TODO ビルトイン 作成
	// exec_builtin(parsed_tokens);
	pid = fork();
	if (pid == -1)
		perror("error\n");
	if (pid == 0)
	{
		if (parsed_tokens->argv[0][0] == '/')
		{
			if (access(parsed_tokens->argv[0], F_OK) == 0)
				execve(parsed_tokens->argv[0], parsed_tokens->argv, NULL);
		}
		else
            execve(find_executable_path(parsed_tokens, path_list), parsed_tokens->argv, NULL);
	}
	else
		waitpid(pid, NULL, 0);
	return (EXIT_FAILURE);
}

int exec_child(t_node *parsed_tokens, t_exe_info *info, char **path_list)
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

int exec_parent(t_node *parsed_tokens, t_exe_info *info)
{
    wrap_close(parsed_tokens->fds[OUT]);
    info->before_cmd_fd = parsed_tokens->fds[IN];
    return (EXIT_SUCCESS);
}

int exec_pipe(t_node *parsed_tokens, t_exe_info *info, char **path_list)
{
    pipe(parsed_tokens->fds);
    info->pid[info->exec_count] = fork();
    if (info->pid[info->exec_count] == -1)
        return (EXIT_FAILURE);
    if (info->pid[info->exec_count] == 0)
        exec_child(parsed_tokens, info, path_list);
   exec_parent(parsed_tokens, info);
    info->exec_count++;
   return (EXIT_SUCCESS);
}

int exec_last_pipe_cmd(t_node *parsed_tokens, t_exe_info *info, char **path_list)
{
    info->pid[info->exec_count] = fork();
    if (info->pid[info->exec_count] == -1)
        return (ft_printf("error\n"), EXIT_FAILURE);
    if (info->pid[info->exec_count] == 0)
    {
        wrap_dup2(info->before_cmd_fd, STDIN_FILENO);
        wrap_close(info->before_cmd_fd);
        execute(parsed_tokens, path_list);
        exit(EXIT_FAILURE);
    }
    wrap_close(info->before_cmd_fd);
    while (info->exec_count >= 0)
    {
        waitpid(info->pid[info->exec_count], NULL, 0);
        info->exec_count--;
    }
    return (EXIT_SUCCESS);
}

int	exec_cmd(t_node *parsed_tokens, char **path_list)
{
    t_exe_info *info;

    if (parsed_tokens->next == NULL && parsed_tokens->argv != NULL)
        return (exec_single_cmd(parsed_tokens, path_list));
    info = (t_exe_info *)malloc(sizeof(t_exe_info));
    if (info == NULL)
        exit(EXIT_FAILURE);
    if (initialize_node(info, parsed_tokens))
        return (EXIT_FAILURE);
    while (parsed_tokens->next)
    {
        if (parsed_tokens->kind == CMD)
        {
            if (exec_pipe(parsed_tokens, info, path_list) == 1)
                return (EXIT_FAILURE);
        }
        parsed_tokens = parsed_tokens->next;
    }
	return (exec_last_pipe_cmd(parsed_tokens, info, path_list));
}


void	invoke_commands(t_token *tokens)
{
	t_node	*parsed_tokens;
	char	**path_list;

	path_list = get_path_list(getenv("PATH"));
	parsed_tokens = parse(tokens);
	exec_cmd(parsed_tokens, path_list);
}
