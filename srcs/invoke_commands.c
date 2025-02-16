/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:48:21 by yehara            #+#    #+#             */
/*   Updated: 2025/02/16 20:58:58 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <invoke_commands.h>
#include <utils.h>

static int	exec_single_cmd(t_node *parsed_tokens, char **path_list, t_context *context)
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
			execute(parsed_tokens, path_list, context);
	}
	else
		waitpid(pid, NULL, 0);
	return (EXIT_FAILURE);
}

static	int	exec_pipe(t_node *parsed_tokens, t_exe_info *info, char **path_list, t_context *context)
{
	pipe(parsed_tokens->fds);
	info->pid[info->exec_count] = fork();
	if (info->pid[info->exec_count] == -1)
		return (EXIT_FAILURE);
	if (info->pid[info->exec_count] == 0)
		child_process(parsed_tokens, info, path_list, context);
	parent_process(parsed_tokens, info);
	info->exec_count++;
	return (EXIT_SUCCESS);
}

static	int	exec_last_pipe_cmd(t_node *parsed_tokens, t_exe_info *info,
		char **path_list, t_context *context)
{
	info->pid[info->exec_count] = fork();
	if (info->pid[info->exec_count] == -1)
		return (ft_printf("error\n"), EXIT_FAILURE);
	if (info->pid[info->exec_count] == 0)
	{
		wrap_dup2(info->before_cmd_fd, STDIN_FILENO);
		wrap_close(info->before_cmd_fd);
		execute(parsed_tokens, path_list, context);
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

static int	exec_cmd(t_node *parsed_tokens, char **path_list, t_context *context)
{
	t_exe_info	*info;

	// TODO unset PATH 時の挙動
	// TODO 'EOF'のとき変数を展開しないようにする
	process_heredoc(parsed_tokens);
	if (is_builtin(parsed_tokens))
		return (exec_builtin(parsed_tokens, context));
	// TODO hoge/test.sh ようなケースを実行できるようにする
	if (parsed_tokens->next == NULL && parsed_tokens->argv != NULL)
		return (exec_single_cmd(parsed_tokens, path_list, context));
	info = (t_exe_info *)malloc(sizeof(t_exe_info));
	if (info == NULL)
		exit(EXIT_FAILURE);
	if (initialize_info(info, parsed_tokens))
		return (EXIT_FAILURE);
	while (parsed_tokens->next)
	{
		if (parsed_tokens->kind == CMD)
		{
			if (exec_pipe(parsed_tokens, info, path_list, context) == 1)
				return (EXIT_FAILURE);
		}
		parsed_tokens = parsed_tokens->next;
	}
	return (exec_last_pipe_cmd(parsed_tokens, info, path_list, context));
}

void	invoke_commands(t_token *tokens, t_context *context)
{
	t_node	*parsed_tokens;
	char	**path_list;

	path_list = get_path_list(getenv("PATH"));
	parsed_tokens = parse(tokens);
	exec_cmd(parsed_tokens, path_list, context);
	all_free(NULL, path_list, parsed_tokens);
}
