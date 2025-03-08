/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:10:11 by yehara            #+#    #+#             */
/*   Updated: 2025/03/09 04:37:07 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "invoke_commands.h"
#include "utils.h"

bool	is_absolute(char *argv)
{
	return (ft_strncmp(argv, "./", 2) == 0);
}

void	print_error(t_node *parsed_tokens, t_exe_info *info)
{
	if (!(ft_strncmp(info->error_message, "command not found", COMMAND_NOT_FOUND_NUM) == 0))
		ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(parsed_tokens->argv[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(info->error_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(info->error_message);
}

bool	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		return (false);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}

int	exec_abcolute(t_node *parsed_tokens, char **path_list, t_exe_info *info, t_context *context)
{
	char **envp;

	if (access(parsed_tokens->argv[0], F_OK) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (is_directory(parsed_tokens->argv[0]) == false)
	{
		free(info->error_message);
		all_free(info, path_list, parsed_tokens, context);
		exit(setting_exit_status(context, EXIT_STATUS_PERMISSION_DENIED));
	}
	envp = convert_to_envp(context->environ);
	double_close_fd(&info->saved_stdin, &info->saved_stdout);
	if (access(parsed_tokens->argv[0], X_OK) == EXIT_SUCCESS)
	{
		execve(parsed_tokens->argv[0], parsed_tokens->argv, envp);
		free_envp(envp);
		double_close_fd(&info->saved_stdin, &info->saved_stdout);
		all_free(info, path_list, parsed_tokens, context);
		exit(setting_exit_status(context, EXIT_FAILURE));
	}
	else
	{
		free(info->error_message);
		info->error_message = ft_strdup("Permission denied");
		print_error(parsed_tokens, info);
		all_free(info, path_list, parsed_tokens, context);
		exit(setting_exit_status(context, EXIT_STATUS_PERMISSION_DENIED));
	}
	exit(setting_exit_status(context, EXIT_SUCCESS));
}

void	check_path(t_node *parsed_tokens, t_exe_info *info, char **path_list, t_context *context)
{
	if (info->path == NULL)
	{
		exec_abcolute(parsed_tokens, path_list, info, context);
		print_error(parsed_tokens, info);
		free(info->path);
		all_free(info, path_list, parsed_tokens, context);
		if (context->exit_status == 0)
			context->exit_status = EXIT_STATUS_COMMAND_NOT_FOUND;
		exit(context->exit_status);
	}
}

