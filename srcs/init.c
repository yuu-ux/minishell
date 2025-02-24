/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:26:05 by yehara            #+#    #+#             */
/*   Updated: 2025/02/23 18:11:14 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <invoke_commands.h>
#include <libft.h>
#include <minishell.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal_setting.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenize.h>
#include <utils.h>

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

