/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:41:32 by yehara            #+#    #+#             */
/*   Updated: 2025/02/23 15:41:41 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <invoke_commands.h>
#include <builtin.h>

bool    is_builtin(const t_node *parsed_tokens)
{
    if (!(ft_strncmp(parsed_tokens->argv[0], "echo", 5))
        || !(ft_strncmp(parsed_tokens->argv[0], "cd", 3))
        || !(ft_strncmp(parsed_tokens->argv[0], "pwd", 4))
        || !(ft_strncmp(parsed_tokens->argv[0], "export", 7))
        || !(ft_strncmp(parsed_tokens->argv[0], "unset", 6))
        || !(ft_strncmp(parsed_tokens->argv[0], "env", 4))
        || !(ft_strncmp(parsed_tokens->argv[0], "exit", 5))
        )
        return (true);
    return (false);
}

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
	if (value == NULL)
		return (EXIT_SUCCESS);
	free(env->value);
	env->value = ft_strdup(value);
	return (EXIT_SUCCESS);
}

int	count_environ(kvs *environ)
{
	int	i;

	i = 0;
	while (environ[i].key)
		i++;
	return (i);
}

void	xaddenv(char *name, char *value, t_context *context)
{
	int	env_count;
	kvs	*new_environ;
	int	i;

	i = 0;
	env_count = count_environ(context->environ);
	// 追加と null 終端のサイズ確保のために +2 する
	new_environ = (kvs *)ft_xmalloc(sizeof(kvs) * (env_count + 2));
	while (context->environ[i].key)
	{
		new_environ[i].key = ft_strdup(context->environ[i].key);
		free(context->environ[i].key);
		new_environ[i].value = ft_strdup(context->environ[i].value);
		free(context->environ[i].value);
		i++;
	}
	new_environ[env_count].key = ft_strdup(name);
	new_environ[env_count].value = ft_strdup(value);
	free(context->environ);
	context->environ = new_environ;
}

