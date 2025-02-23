/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:20:02 by yehara            #+#    #+#             */
/*   Updated: 2025/02/23 15:43:33 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

static	char	*analysis_token(char *argv, char *value)
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

static	void	kvs_swap(t_kvs *env1, t_kvs *env2)
{
	t_kvs	temp;

	temp = *env1;
	*env1 = *env2;
	*env2 = temp;
}

static	void	sorted_print(t_context *context)
{
	int		i;
	int		j;

	i = 0;
	while (context->environ[i + 1].key)
	{
		j = i + 1;
		while (context->environ[j].key)
		{
			if (strcmp(context->environ[i].key, context->environ[j].key) > 0)
				kvs_swap(&context->environ[i], &context->environ[j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (context->environ[i].key)
	{
		if (context->environ[i].value)
			ft_printf("declare -x %s=\"%s\"\n", context->environ[i].key,
				context->environ[i].value);
		else
			ft_printf("declare -x %s\n", context->environ[i].key);
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

