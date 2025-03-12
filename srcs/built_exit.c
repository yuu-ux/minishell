/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:40:48 by yehara            #+#    #+#             */
/*   Updated: 2025/03/12 11:32:34 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "error.h"
#include "utils.h"

bool	built_exit(t_node *parsed_tokens, char **path_list, t_context *context,
		t_exe_info *info)
{
	if (info->pid[info->exec_count] == -1)
		print_err("exit\n");
	if (parsed_tokens->argv[1] == NULL)
		;
	else if (parsed_tokens->argv[1])
	{
		context->exit_status = ft_atoi(parsed_tokens->argv[1]);
		if (errno == ERANGE || ft_isvalue(parsed_tokens->argv[1]) == 0)
		{
			print_err("minishell: exit: ");
			print_err(parsed_tokens->argv[1]);
			print_err(": numeric argument required\n");
			context->exit_status = 2;
		}
	}
	else if (parsed_tokens->argv[2])
	{
		print_err("minishell: exit: too many arguments\n");
		context->exit_status = EXIT_FAILURE;
		return (context->exit_status);
	}
	all_free(info, path_list, parsed_tokens, context);
	exit(context->exit_status);
}
