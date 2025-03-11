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

void	print_error(t_node *parsed_tokens, t_exe_info *info)
{
	if (!(ft_strncmp(info->error_message, "command not found",
				COMMAND_NOT_FOUND_NUM) == 0))
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

	if (stat(path, &st) == -1)
	{
		perror("stat error\n");
		exit(EXIT_FAILURE);
	}
	if (S_ISDIR(st.st_mode))
		return (true);
	return (false);
}

uint8_t	setting_message_and_status(t_exe_info *info, t_context *context,
		char *message, uint8_t status)
{
	free(info->error_message);
	info->error_message = ft_strdup(message);
	return (setting_exit_status(context, status));
}

int	exec_abcolute(t_node *parsed_tokens, char **path_list, t_exe_info *info,
		t_context *context)
{
	char	**envp;

	double_close_fd(&info->saved_stdin, &info->saved_stdout);
	if (access(parsed_tokens->argv[0], F_OK) == -1)
		setting_message_and_status(info, context, "No such file or directory",
			EXIT_STATUS_COMMAND_NOT_FOUND);
	else if (is_directory(parsed_tokens->argv[0]) == true)
		setting_message_and_status(info, context, "Is a directory",
			EXIT_STATUS_PERMISSION_DENIED);
	else if (access(parsed_tokens->argv[0], X_OK) == EXIT_SUCCESS)
	{
		envp = convert_to_envp(context->environ);
		execve(parsed_tokens->argv[0], parsed_tokens->argv, envp);
		free_envp(envp);
		all_free(info, path_list, parsed_tokens, context);
		exit(setting_exit_status(context, EXIT_FAILURE));
	}
	else
		setting_message_and_status(info, context, "Permission denied",
			EXIT_STATUS_PERMISSION_DENIED);
	print_error(parsed_tokens, info);
	exit(context->exit_status);
}

void	check_path(t_node *parsed_tokens, t_exe_info *info, char **path_list,
		t_context *context)
{
	if (info->path == NULL)
	{
		if (!(ft_strncmp(parsed_tokens->argv[0], "..", 3) == 0))
			exec_abcolute(parsed_tokens, path_list, info, context);
		print_error(parsed_tokens, info);
		free(info->path);
		all_free(info, path_list, parsed_tokens, context);
		exit(context->exit_status);
	}
}
