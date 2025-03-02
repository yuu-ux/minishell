/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:19:20 by yehara            #+#    #+#             */
/*   Updated: 2025/02/26 17:27:06 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	built_env(t_context *context)
{
	int	i;

	i = 0;
	while (context->environ[i].key)
	{
		if (context->environ[i].value)
			printf("%s=%s\n", context->environ[i].key, context->environ[i].value);
		i++;
	}
    return (EXIT_SUCCESS);
}
