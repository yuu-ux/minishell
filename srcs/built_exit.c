/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:40:48 by yehara            #+#    #+#             */
/*   Updated: 2025/02/26 18:10:38 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>
#include <utils.h>

bool	is_numeric(char *argv)
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

bool	is_greater_than_LONG_MAX(t_node *parsed_tokens)
{
	long	ret;
	int	i;
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
		if ((ret > LONG_MAX / 10) || (ret == LONG_MAX / 10 && parsed_tokens->argv[1][i] > '7'))
			return (true);
		else if ((ret < LONG_MIN / 10) || (ret == LONG_MIN / 10 && parsed_tokens->argv[1][i] > '8'))
			return (true);
		ret = ret * 10 + (parsed_tokens->argv[1][i] - '0') * sign;
		i++;
	}
	return (false);
}

bool	built_exit(t_node *parsed_tokens, char **path_list, t_context *context, t_exe_info *info)
{
	ft_printf("exit\n");
	// 引数のひとつめが数字以外
	if ((!(is_numeric(parsed_tokens->argv[1]))) || is_greater_than_LONG_MAX(parsed_tokens))
	{
		ft_printf("bash: exit: %s: numeric argument required\n", parsed_tokens->argv[1]);
		context->exit_status = 2;
	}
	// 引数の２つ目が存在しない
	else if (parsed_tokens->argv[2] != NULL)
	{
		context->exit_status = EXIT_FAILURE;
		ft_printf("bash: exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	context->exit_status = ft_atol(parsed_tokens->argv[1]);
	reset_fd(info);
	free_after_invoke(path_list, parsed_tokens, info);
	free_context(context);
	exit(EXIT_SUCCESS);
}

