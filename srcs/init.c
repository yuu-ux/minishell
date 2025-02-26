/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:26:05 by yehara            #+#    #+#             */
/*   Updated: 2025/02/26 17:51:02 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static t_kvs	*create_env(char **envp)
{
	t_kvs		*environ;
	char	**temp;
	int		i;
	int		j;
	size_t	count;

	count = count_env(envp);
	environ = (t_kvs *)ft_xmalloc(sizeof(t_kvs) * (count + 1));
	i = 0;
	while (envp[i])
	{
		j = 0;
		temp = ft_split(envp[i], '=');
		environ[i].key = ft_strdup(temp[0]);
		environ[i].value = ft_strdup(temp[1]);
		while (temp[j])
			free(temp[j++]);
		free(temp[j]);
		free(temp);
		i++;
	}
	return (environ);
}

t_context	*init_context(char *envp[])
{
	t_context *context;

	context = (t_context *)ft_xmalloc(sizeof(t_context));
	context->environ = create_env(envp);
	context->exit_status = EXIT_SUCCESS;
	context->flg_heredoc_expand = true;
	return (context);
}

