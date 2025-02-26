/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:41:32 by yehara            #+#    #+#             */
/*   Updated: 2025/02/26 17:27:37 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_kvs	*xgetenv(const char *name, t_context *context)
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
	t_kvs	*env;

	env = xgetenv(name, context);
	if (env == NULL)
		return (EXIT_FAILURE);
	if (value == NULL)
		return (EXIT_SUCCESS);
	free(env->value);
	env->value = ft_strdup(value);
	return (EXIT_SUCCESS);
}

int	count_environ(t_kvs *environ)
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
	t_kvs	*new_environ;
	int	i;

	i = 0;
	env_count = count_environ(context->environ);
	// 追加と null 終端のサイズ確保のために +2 する
	new_environ = (t_kvs *)ft_xmalloc(sizeof(t_kvs) * (env_count + 2));
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

