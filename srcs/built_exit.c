/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:40:48 by yehara            #+#    #+#             */
/*   Updated: 2025/02/26 02:33:59 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>
#include <utils.h>

bool	is_numeric(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!(ft_isdigit(argv[i])))
			return (false);
		i++;
	}
	return (true);
}

bool	built_exit(t_node *parsed_tokens, char **path_list, t_context *context, t_exe_info *info)
{
	ft_printf("exit\n");
	if (!(is_numeric(parsed_tokens->argv[1]))) // && LONG_MAX より大きければ
	{
		printf("bash: exit: %s: numeric argument required\n", parsed_tokens->argv[1]);
		context->exit_status = 2;
	}
	else if (parsed_tokens->argv[1] != NULL)
	{
		context->exit_status = EXIT_FAILURE;
		ft_printf("bash: exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	reset_fd(info);
	free_after_invoke(path_list, parsed_tokens, info);
	free_context(context);
    exit(EXIT_SUCCESS);
}
