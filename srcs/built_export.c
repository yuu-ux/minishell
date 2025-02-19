/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:20:02 by yehara            #+#    #+#             */
/*   Updated: 2025/02/18 18:20:04 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

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

int	count_environ(kvs	*environ)
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

	env_count = count_environ(context->environ);
	// 追加と null 終端のサイズ確保のために +2 する
	context->environ = (kvs *)ft_realloc(context->environ, sizeof(kvs) * (env_count + 2));
	context->environ[env_count].key = ft_strdup(name);
	context->environ[env_count].value = ft_strdup(value);
}

static	bool	update_env(const t_node *parsed_tokens, t_context	*context)
{
	char **temp;
	int	i;

	i = 1;
	while (parsed_tokens->argv[i])
	{
		temp = ft_split(parsed_tokens->argv[i], '=');
		if (xsetenv(temp[0], temp[1], context))
			xaddenv(temp[0], temp[1], context);
		while (temp[i])
			free(temp[i++]);
		free(temp[i]);
		free(temp);
		i++;
	}
	return (EXIT_SUCCESS);
}

bool	built_export(const	t_node *parsed_tokens, t_context *context)
{
	int	i;

	i = 0;
	if (!(parsed_tokens->argv[1]))
	{
		while (context->environ[i].key)
		{
			if (context->environ[i].value)
				ft_printf("delare -x %s=%s\n", context->environ[i].key, context->environ[i].value);
			else
				ft_printf("delare -x %s\n", context->environ[i].key, context->environ[i].value);
			i++;
		}
	}
	else
	{
		update_env(parsed_tokens, context);
	}
	return (EXIT_SUCCESS);
}

