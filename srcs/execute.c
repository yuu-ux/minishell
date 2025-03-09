/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:10:18 by yehara            #+#    #+#             */
/*   Updated: 2025/03/03 17:32:42 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "invoke_commands.h"
#include "redirect.h"
#include "signal_setting.h"
#include "utils.h"

static char	*find_executable_path(const t_node *parsed_tokens, char **path_list,
		char **error_message)
{
	int		i;
	char	*slash_cmd;
	char	*path;

	if (path_list == NULL)
	{
		*error_message = ft_strdup("No such file or directory");
		return (NULL);
	}
	i = 0;
	path = NULL;
	slash_cmd = ft_strjoin("/", parsed_tokens->argv[0]);
	while (path_list[i])
	{
		path = ft_strjoin(path_list[i++], slash_cmd);
		if (access(path, F_OK) == 0)
		{
			free(slash_cmd);
			return (path);
		}
		free(path);
	}
	free(slash_cmd);
	*error_message = ft_strdup("command not found");
	return (NULL);
}

int	child_process(t_node *parsed_tokens, t_exe_info *info, char **path_list,
		t_context *context)
{
	child_signal_setting();
	// 最後以外のコマンドの場合
	// STDOUT → current_pipefd[OUT]
	if (info->exec_count < info->pipe_num)
	{
		if (parsed_tokens->fds[IN] != INVALID_FD)
		{
			wrap_dup2(parsed_tokens->fds[IN], STDIN_FILENO);
			close_redirect_fd(&parsed_tokens->fds[IN]);
		}
		wrap_dup2(parsed_tokens->fds[OUT], STDOUT_FILENO);
		close_redirect_fd(&parsed_tokens->fds[OUT]);
	}
	// 初めのコマンド以外は、入力を前のpipefd[IN]にリダイレクトする
	// STDIN → before_pipe_fd[IN]
	if (info->exec_count > 0)
	{
		wrap_dup2(info->before_cmd_fd, STDIN_FILENO);
		wrap_close(info->before_cmd_fd);
	}
	execute(parsed_tokens, path_list, context, info);
	exit(EXIT_FAILURE);
}

int	parent_process(t_node *parsed_tokens, t_exe_info *info)
{
	parent_override_signal_setting();
	close_redirect_fd(&parsed_tokens->fds[OUT]);
	wrap_close(info->before_cmd_fd);
	info->before_cmd_fd = parsed_tokens->fds[IN];
	return (EXIT_SUCCESS);
}

void	set_redirect_fd(t_node *parsed_tokens)
{
	if (parsed_tokens->fds[IN] != INVALID_FD)
	{
		wrap_dup2(parsed_tokens->fds[IN], STDIN_FILENO);
		close_redirect_fd(&parsed_tokens->fds[IN]);
	}
	if (parsed_tokens->fds[OUT] != INVALID_FD)
	{
		wrap_dup2(parsed_tokens->fds[OUT], STDOUT_FILENO);
		close_redirect_fd(&parsed_tokens->fds[OUT]);
	}
}

int	execute(t_node *parsed_tokens, char **path_list, t_context *context,
		t_exe_info *info)
{
	char	*path;
	char	*error_message;
	unsigned char	exit_status;

	init_saved_fd(info);
	do_redirections(parsed_tokens);
	set_redirect_fd(parsed_tokens);
	if (is_builtin(parsed_tokens))
	{
		exit_status = exec_builtin(parsed_tokens, path_list, context, info);
		reset_fd(info);
		// ビルトインの終了ステータスを返したい
		exit(exit_status);
	}
	path = find_executable_path(parsed_tokens, path_list, &error_message);
	if (path == NULL)
	{
		ft_printf("minishell: %s: %s\n", parsed_tokens->argv[0], error_message);
		free(error_message);
		free(path);
		all_free(info, path_list, parsed_tokens, context);
		exit(EXIT_STATUS_COMMAND_NOT_FOUND);
	}
	double_close_fd(&info->saved_stdin, &info->saved_stdout);
	execve(path, parsed_tokens->argv, convert_to_envp(context->environ));
	exit(EXIT_FAILURE);
}

