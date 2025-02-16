/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:18:11 by yehara            #+#    #+#             */
/*   Updated: 2025/02/16 21:05:19 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <invoke_commands.h>
#include <minishell.h>
#include <expand.h>
#include <unistd.h>

kvs	*xgetenv(const char *name, t_context *context)
{
	int	i;

	i = 0;
	while (context->environ[i].key)
	{
		if (ft_strncmp(context->environ[i].key, name, ft_strlen(name) + 1) == 0)
			return (&context->environ[i]);
		i++;
	}
	return (NULL);
}

int	xsetenv(char *name, char *value, t_context *context)
{
	kvs	*env;

	env = xgetenv(name, context);
	if (env == NULL)
		return (EXIT_FAILURE);
	env->value = value;
	return (EXIT_SUCCESS);
}

bool	built_cd(const t_node *parsed_tokens, t_context *context)
{
	chdir(parsed_tokens->argv[1]);
	xsetenv("PWD", getcwd(NULL, 0), context);
	return (EXIT_SUCCESS);
}

