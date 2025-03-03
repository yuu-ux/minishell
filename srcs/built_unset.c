/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:19:24 by yehara            #+#    #+#             */
/*   Updated: 2025/03/02 17:06:55 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	is_variable(char *argv)
{
	int	i;

	i = 0;
	if (ft_isdigit(argv[i]))
		return (false);
	while (argv[i])
	{
		if (!(ft_isalnum(argv[i]) || argv[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

bool	built_unset(const	t_node *parsed_tokens, t_context *context)
{
	int	i;

	i = 1;
	while (parsed_tokens->argv[i])
	{
		if (is_variable(parsed_tokens->argv[i]))
			xunsetenv(parsed_tokens->argv[i], context);
		else
		{
			ft_printf("minishell: unset: `%s': not a valid identifier\n", parsed_tokens->argv[i]);
			return (setting_exit_status(context, EXIT_FAILURE));
		}
		i++;
	}
	return (setting_exit_status(context, EXIT_SUCCESS));
}

