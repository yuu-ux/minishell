/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:10:18 by yehara            #+#    #+#             */
/*   Updated: 2025/03/09 04:09:33 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "invoke_commands.h"
#include "minishell.h"
#include "redirect.h"
#include "signal_setting.h"
#include "utils.h"

static uint8_t	find_executable_path(const t_node *parsed_tokens,
		char **path_list, t_exe_info *info)
{
	int		i;
	char	*slash_cmd;

	if (path_list == NULL)
		return (info->error_message = ft_strdup("No such file or directory"),
			EXIT_STATUS_COMMAND_NOT_FOUND);
	if (ft_strncmp(parsed_tokens->argv[0], "..", 3) == 0)
		return (info->error_message = ft_strdup("command not found"),
			EXIT_STATUS_COMMAND_NOT_FOUND);
	i = 0;
	slash_cmd = ft_strjoin("/", parsed_tokens->argv[0]);
	while (path_list[i])
	{
		info->path = ft_strjoin(path_list[i++], slash_cmd);
		if (access(info->path, F_OK) == 0)
		{
			free(slash_cmd);
			return (EXIT_SUCCESS);
		}
		free(info->path);
	}
	free(slash_cmd);
	info->path = NULL;
	info->error_message = ft_strdup("command not found");
	return (EXIT_STATUS_COMMAND_NOT_FOUND);
}

int	child_process(t_node *parsed_tokens, t_exe_info *info, char **path_list,
		t_context *context)
{
	child_signal_setting();
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
	if (info->exec_count > 0)
	{
		wrap_dup2(info->before_cmd_fd, STDIN_FILENO);
		wrap_close(info->before_cmd_fd);
	}
	execute(parsed_tokens, path_list, context, info);
	all_free(info, path_list, parsed_tokens, context);
	exit(EXIT_SUCCESS);
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
	char	**envp;

	init_saved_fd(info);
	do_redirections(parsed_tokens);
	set_redirect_fd(parsed_tokens);
	if (is_builtin(parsed_tokens))
	{
		exec_builtin(parsed_tokens, path_list, context, info);
		reset_fd(info);
		return (context->exit_status);
	}
	if (is_absolute(parsed_tokens->argv[0]) == true)
		exec_abcolute(parsed_tokens, path_list, info, context);
	context->exit_status = find_executable_path(parsed_tokens, path_list, info);
	check_path(parsed_tokens, info, path_list, context);
	double_close_fd(&info->saved_stdin, &info->saved_stdout);
	envp = convert_to_envp(context->environ);
	execve(info->path, parsed_tokens->argv, envp);
	free_envp(envp);
	free(info->path);
	all_free(info, path_list, parsed_tokens, context);
	exit(EXIT_FAILURE);
}
