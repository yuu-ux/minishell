/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:40:48 by yehara            #+#    #+#             */
/*   Updated: 2025/03/02 17:05:48 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "error.h"
#include "utils.h"

static bool	is_numeric(char *argv)
{
	int	i;

	i = 0;
	if (argv[i] == '+' || argv[i] == '-')
		i++;
	while (argv[i])
	{
		if (!(ft_isdigit(argv[i])))
			return (false);
		i++;
	}
	return (true);
}

static bool	is_greater_than_long_max(t_node *parsed_tokens)
{
	long	ret;
	int		i;
	int		sign;

	ret = 0;
	i = 0;
	sign = 1;
	if (parsed_tokens->argv[1][i] == '+' || parsed_tokens->argv[1][i] == '-')
	{
		if (parsed_tokens->argv[1][i] == '-')
			sign = -1;
		i++;
	}
	while (parsed_tokens->argv[1][i])
	{
		if ((ret > LONG_MAX / 10) || (ret == LONG_MAX / 10
				&& parsed_tokens->argv[1][i] > '7'))
			return (true);
		else if ((ret < LONG_MIN / 10) || (ret == LONG_MIN / 10
				&& parsed_tokens->argv[1][i] > '8'))
			return (true);
		ret = ret * 10 + (parsed_tokens->argv[1][i] - '0') * sign;
		i++;
	}
	return (false);
}

bool	built_exit(t_node *parsed_tokens, char **path_list, t_context *context,
		t_exe_info *info)
{
	if (info->pid[info->exec_count] == -1)
		print_err("exit\n");
	if (parsed_tokens->argv[1] == NULL)
		;
	else if ((!(is_numeric(parsed_tokens->argv[1])))
		|| is_greater_than_long_max(parsed_tokens))
	{
		print_err("minishell: exit: ");
		print_err(parsed_tokens->argv[1]);
		print_err(": numeric argument required\n");
		context->exit_status = 2;
	}
	else if (parsed_tokens->argv[2] != NULL)
	{
		print_err("minishell: exit: too many arguments\n");
		context->exit_status = EXIT_FAILURE;
		return (context->exit_status);
	}
	if (context->exit_status == 0 && parsed_tokens->argv[1])
		context->exit_status = ft_atol(parsed_tokens->argv[1]);
	all_free(info, path_list, parsed_tokens, context);
	exit(context->exit_status);
}
