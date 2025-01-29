#include <invoke_commands.h>
#include <utils.h>

static int	exec_single_cmd(const t_node *parsed_tokens, char **path_list)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("error\n");
	if (pid == 0)
	{
		if (access(parsed_tokens->argv[0], F_OK) == 0)
			execve(parsed_tokens->argv[0], parsed_tokens->argv, NULL);
		else
			execute(parsed_tokens, path_list);
	}
	else
		waitpid(pid, NULL, 0);
	return (EXIT_FAILURE);
}

int	exec_pipe(t_node *parsed_tokens, t_exe_info *info, char **path_list)
{
	pipe(parsed_tokens->fds);
	info->pid[info->exec_count] = fork();
	if (info->pid[info->exec_count] == -1)
		return (EXIT_FAILURE);
	if (info->pid[info->exec_count] == 0)
		child_process(parsed_tokens, info, path_list);
	parent_process(parsed_tokens, info);
	info->exec_count++;
	return (EXIT_SUCCESS);
}

int	exec_last_pipe_cmd(t_node *parsed_tokens, t_exe_info *info,
		char **path_list)
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
    t_exe_info	*info;

	if (process_heredoc(parsed_tokens)) // 失敗したら false
		return (EXIT_FAILURE);
	if (is_builtin(parsed_tokens))
		exec_builtin(parsed_tokens);
	// TODO hoge/test.sh ようなケースを実行できるようにする
	if (parsed_tokens->next == NULL && parsed_tokens->argv != NULL)
		return (exec_single_cmd(parsed_tokens, path_list));
	info = (t_exe_info *)malloc(sizeof(t_exe_info));
	if (info == NULL)
		exit(EXIT_FAILURE);
	if (initialize_info(info, parsed_tokens))
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
    all_free(NULL, path_list, parsed_tokens);
}

