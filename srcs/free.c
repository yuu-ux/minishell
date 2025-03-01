/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:14:52 by yehara            #+#    #+#             */
/*   Updated: 2025/02/26 18:20:48 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_after_invoke(char **path_list, t_node *parsed_tokens,
		t_exe_info *info)
{
	int		i;
	t_node	*before_tokens;

	i = 0;
	if (path_list)
	{
		while (path_list[i])
			free(path_list[i++]);
		free(path_list);
	}
	free(info->pid);
	free(info);
	while (parsed_tokens)
	{
		i = 0;
		while (parsed_tokens->kind != PIPE && parsed_tokens->argv[i])
			free(parsed_tokens->argv[i++]);
		free(parsed_tokens->argv);
		before_tokens = parsed_tokens;
		parsed_tokens = parsed_tokens->next;
		free(before_tokens);
	}
}

void	free_context(t_context *context)
{
	int	i;

	i = 0;
	if (context->environ)
	{
		while (context->environ[i].key)
		{
			free(context->environ[i].key);
			free(context->environ[i].value);
			i++;
		}
		free(context->environ);
	}
	free(context);
	wrap_close(STDIN_FILENO);
	wrap_close(STDOUT_FILENO);
}
