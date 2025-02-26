/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:27:42 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/02/26 17:27:43 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_builtin(const t_node *parsed_tokens, t_context *context)
{
	if (!(ft_strncmp(parsed_tokens->argv[0], "echo", 5)))
		return (built_echo(parsed_tokens));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "cd", 3)))
		return (built_cd(parsed_tokens, context));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "pwd", 4)))
		return (built_pwd(context));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "export", 7)))
		return (built_export(parsed_tokens, context));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "unset", 6)))
		return (built_unset(parsed_tokens, context));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "env", 4)))
		return (built_env(context));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "exit", 5)))
		return (built_exit());
	return (EXIT_FAILURE);
}
