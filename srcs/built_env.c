/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:19:20 by yehara            #+#    #+#             */
/*   Updated: 2025/03/02 17:00:28 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	built_env(t_context *context)
{
	int	i;

	i = 0;
	while (context->environ[i].key)
	{
		if (context->environ[i].value)
			printf("%s=%s\n",
				context->environ[i].key, context->environ[i].value);
		i++;
	}
	return (setting_exit_status(context, EXIT_SUCCESS));
}
