/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:48:21 by yehara            #+#    #+#             */
/*   Updated: 2025/03/03 17:19:12 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "invoke_commands.h"
#include "redirect.h"
#include "signal_setting.h"
#include "utils.h"

static int	exec_single_cmd(t_node *parsed_tokens, char **path_list,
		t_context *context, t_exe_info *info)
{
	pid_t	pid;
	int		status;

	do_redirections(parsed_tokens);
	if (parsed_tokens->argv[0] == NULL)
		return (setting_exit_status(context, EXIT_SUCCESS));
	if (is_builtin(parsed_tokens))
		return (execute(parsed_tokens, path_list, context, info));
	pid = fork();
	if (pid == -1)
		perror("error\n");
	if (pid == 0)
	{
		child_signal_setting();
		if (access(parsed_tokens->argv[0], F_OK) == 0)
			execve(parsed_tokens->argv[0], parsed_tokens->argv,
				convert_to_envp(context->environ));
		else
			execute(parsed_tokens, path_list, context, info);
	}
	parent_override_signal_setting();
	waitpid(pid, &status, 0);
	catch_exit_status(context, status);
	wrap_close(parsed_tokens->fds[IN]);
	return (context->exit_status);
}

static int	exec_pipe(t_node *parsed_tokens, t_exe_info *info, char **path_list,
		t_context *context)
{
	int	saved_fd;

	saved_fd = INVALID_FD;
	do_redirections(parsed_tokens);
	if (parsed_tokens->fds[IN] != INVALID_FD)
		saved_fd = parsed_tokens->fds[IN];
	pipe(parsed_tokens->fds);
	info->pid[info->exec_count] = fork();
	if (info->pid[info->exec_count] == -1)
		return (EXIT_FAILURE);
	if (info->pid[info->exec_count] == 0)
	{
		close_redirect_fd(&parsed_tokens->fds[IN]);
		if (saved_fd != INVALID_FD)
			parsed_tokens->fds[IN] = saved_fd;
		child_process(parsed_tokens, info, path_list, context);
	}
	wrap_close(saved_fd);
	parent_process(parsed_tokens, info);
	info->exec_count++;
	return (EXIT_SUCCESS);
}

static int	exec_last_pipe_cmd(t_node *parsed_tokens, t_exe_info *info,
		char **path_list, t_context *context)
{
	int	status;

	info->pid[info->exec_count] = fork();
	if (info->pid[info->exec_count] == -1)
		return (ft_printf("error\n"), EXIT_FAILURE);
	if (info->pid[info->exec_count] == 0)
	{
		wrap_dup2(info->before_cmd_fd, STDIN_FILENO);
		close_redirect_fd(&info->before_cmd_fd);
		execute(parsed_tokens, path_list, context, info);
		exit(EXIT_FAILURE);
	}
	close_redirect_fd(&info->before_cmd_fd);
	while (info->exec_count >= 0)
	{
		waitpid(info->pid[info->exec_count], &status, 0);
		catch_exit_status(context, status);
		info->exec_count--;
	}
	return (EXIT_SUCCESS);
}

static int	exec_cmd(t_node *parsed_tokens, char **path_list,
		t_context *context, t_exe_info *info)
{
	if (process_heredoc(parsed_tokens, path_list, context,
			info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parsed_tokens->next == NULL && parsed_tokens->argv != NULL)
		return (exec_single_cmd(parsed_tokens, path_list, context, info));
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
	t_node		*parsed_tokens;
	char		**path_list;
	t_exe_info	*info;
	t_kvs		*kvs_path;

	path_list = NULL;
	kvs_path = xgetenv("PATH", context);
	if (kvs_path != NULL)
		path_list = get_path_list(kvs_path->value);
	parsed_tokens = parse(tokens, NULL);
	info = (t_exe_info *)ft_xmalloc(sizeof(t_exe_info));
	initialize_info(info, parsed_tokens);
	exec_cmd(parsed_tokens, path_list, context, info);
	free_after_invoke(path_list, parsed_tokens, info);
}
