/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:48:21 by yehara            #+#    #+#             */
/*   Updated: 2025/02/23 18:23:23 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <invoke_commands.h>
#include <minishell.h>
#include <utils.h>
#include <builtin.h>

static int	exec_single_cmd(t_node *parsed_tokens, char **path_list,
		t_context *context)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("error\n");
	if (pid == 0)
	{
		if (access(parsed_tokens->argv[0], F_OK) == 0)
			execve(parsed_tokens->argv[0], parsed_tokens->argv, convert_to_envp(context->environ));
		else
			execute(parsed_tokens, path_list, context);
	}
	else
	{
		waitpid(pid, NULL, 0);
		wrap_close(parsed_tokens->fds[IN]);
	}
	return (EXIT_FAILURE);
}

static int	exec_pipe(t_node *parsed_tokens, t_exe_info *info, char **path_list,
		t_context *context)
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

static int	exec_last_pipe_cmd(t_node *parsed_tokens, t_exe_info *info,
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

static int	exec_cmd(t_node *parsed_tokens, char **path_list,
		t_context *context, t_exe_info *info)
{

	// TODO unset PATH 時の挙動
	// TODO 'EOF'のとき変数を展開しないようにする
	process_heredoc(parsed_tokens, context);
	// TODO hoge/test.sh ようなケースを実行できるようにする
	if (parsed_tokens->next == NULL && parsed_tokens->argv != NULL)
	{
		if (is_builtin(parsed_tokens))
			return (exec_builtin(parsed_tokens, context));
		return (exec_single_cmd(parsed_tokens, path_list, context));
	}
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
	t_exe_info	*info;

	path_list = get_path_list(xgetenv("PATH", context)->value);
	parsed_tokens = parse(tokens);
	info = (t_exe_info *)ft_xmalloc(sizeof(t_exe_info));
	initialize_info(info, parsed_tokens);
	exec_cmd(parsed_tokens, path_list, context, info);
	free_after_invoke(path_list, parsed_tokens, info);
}
