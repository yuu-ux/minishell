/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:10:18 by yehara            #+#    #+#             */
/*   Updated: 2025/02/26 18:20:55 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static	char	*find_executable_path(const t_node *parsed_tokens, char **path_list, char **error_message)
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
		path = ft_strjoin(path_list[i], slash_cmd);
		if (access(path, F_OK) == 0)
		{
			free(slash_cmd);
			return (path);
		}
		free(path);
		i++;
	}
	free(slash_cmd);
	*error_message = ft_strdup("command not found");
	return (NULL);
}

int	child_process(t_node *parsed_tokens, t_exe_info *info, char **path_list,
		t_context *context)
{
	child_override_signal_setting();
	// 最後以外のコマンドの場合
	// STDOUT → current_pipefd[OUT]
	if (info->exec_count < info->pipe_num)
	{
		wrap_dup2(parsed_tokens->fds[OUT], STDOUT_FILENO);
		close_redirect_fd(&parsed_tokens->fds[OUT]);
		close_redirect_fd(&parsed_tokens->fds[IN]);
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


int	execute(t_node *parsed_tokens, char **path_list, t_context *context, t_exe_info *info)
{
	char	*path;
	char *error_message;

	init_saved_fd(info);
	do_redirections(parsed_tokens);
	set_redirect_fd(parsed_tokens);
	if (is_builtin(parsed_tokens))
	{
		exec_builtin(parsed_tokens, path_list, context, info);
		reset_fd(info);
		// ビルトインの終了ステータスを返したい
		return (EXIT_SUCCESS);
	}
	path = find_executable_path(parsed_tokens, path_list, &error_message);
	if (path == NULL)
	{
		ft_printf("bash: %s: %s\n", parsed_tokens->argv[0], error_message);
		free(error_message);
		free(path);
		reset_fd(info);
		exit(EXIT_FAILURE);
	}
	close_redirect_fd(&info->saved_stdin);
	close_redirect_fd(&info->saved_stdout);
	execve(path, parsed_tokens->argv, convert_to_envp(context->environ));
	exit(EXIT_FAILURE);
}

