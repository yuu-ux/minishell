/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:19:24 by yehara            #+#    #+#             */
/*   Updated: 2025/02/26 17:27:29 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	xunsetenv(const char *name, t_context *context)
{
	int	i;

	i = 0;
	while (context->environ[i].key)
	{
		if (ft_strncmp(context->environ[i].key, name, ft_strlen(name) + 1) == 0)
		{
			free(context->environ[i].key);
			free(context->environ[i].value);
			while (context->environ[i].key)
			{
				context->environ[i] = context->environ[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
}

bool	built_unset(const	t_node *parsed_tokens, t_context *context)
{
	int	i;

	i = 1;
	while (parsed_tokens->argv[i])
		xunsetenv(parsed_tokens->argv[i++], context);
	return (EXIT_SUCCESS);
}

