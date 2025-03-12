/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:14:52 by yehara            #+#    #+#             */
/*   Updated: 2025/03/09 03:50:02 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "invoke_commands.h"
#include "utils.h"

void	all_free(t_exe_info *info, char **path_list, t_node *parsed_tokens,
		t_context *context)
{
	reset_fd(info);
	free_after_invoke(path_list, parsed_tokens, info);
	free_environ(context);
}

void	free_tokens(t_token **tokens)
{
	t_token	*temp;
	char	*data;

	while (*tokens)
	{
		temp = *tokens;
		data = (*tokens)->data;
		*tokens = (*tokens)->next;
		free(temp);
		free(data);
	}
	tokens = NULL;
}

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
	while (parsed_tokens->prev)
		parsed_tokens = parsed_tokens->prev;
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

void	free_environ(t_context *context)
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
	wrap_close(STDIN_FILENO);
	wrap_close(STDOUT_FILENO);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}
