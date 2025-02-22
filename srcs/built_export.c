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

char	*analysis_token(char *argv, char *value)
{
	char	*equal_char;

	equal_char = ft_strchr(argv, '=');
	if (equal_char)
	{
		free(value);
		value = ft_strdup(equal_char + 1);
	}
	return (value);
}

static bool	update_env(const t_node *parsed_tokens, t_context *context)
{
	char	**temp;
	int		i;

	i = 1;
	while (parsed_tokens->argv[i])
	{
		temp = ft_split(parsed_tokens->argv[i], '=');
		temp[1] = analysis_token(parsed_tokens->argv[i], temp[1]);
		if (xsetenv(temp[0], temp[1], context))
			xaddenv(temp[0], temp[1], context);
		free(temp[0]);
		free(temp[1]);
		free(temp);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	kvs_swap(kvs *env1, kvs *env2)
{
	kvs	temp;

	temp = *env1;
	*env1 = *env2;
	*env2 = temp;
}

void	sorted_print(t_context *context)
{
	int		i;
	int		j;
	bool	swapped;

	i = 0;
	while (context->environ[i + 1].key)
	{
		j = i + 1;
		swapped = 0;
		while (context->environ[j].key)
		{
			if (strcmp(context->environ[i].key, context->environ[j].key) > 0)
			{
				kvs_swap(&context->environ[i], &context->environ[j]);
				swapped = 1;
			}
			j++;
		}
		if (swapped == 0)
			break ;
		i++;
	}
	i = 0;
	while (context->environ[i].key)
	{
		if (context->environ[i].value)
			ft_printf("delare -x %s=\"%s\"\n", context->environ[i].key,
				context->environ[i].value);
		else
			ft_printf("delare -x %s\n", context->environ[i].key,
				context->environ[i].value);
		i++;
	}
}

bool	built_export(const t_node *parsed_tokens, t_context *context)
{
	if (!(parsed_tokens->argv[1]))
		sorted_print(context);
	else
		update_env(parsed_tokens, context);
	return (EXIT_SUCCESS);
}
