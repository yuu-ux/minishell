/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:19:20 by yehara            #+#    #+#             */
/*   Updated: 2025/02/23 17:31:50 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

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
