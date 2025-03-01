/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:04:57 by yehara            #+#    #+#             */
/*   Updated: 2025/02/26 19:06:19 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_space_while(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

void	shell_loop(t_context *context)
{
	char		*line;
	t_token		*tokens;

	line = NULL;
	while (true)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		else if (is_space_while(line))
			continue ;
		tokens = tokenization(line);
		check_syntax(tokens);
		tokens = expand_tokens(&tokens, context);
		invoke_commands(tokens, context);
		add_history(line);
		free(line);
	}
}

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)), char *envp[])
{
	t_context	*context;

	context = init_context(envp);
	signal_setting();
	shell_loop(context);
	free_context(context);
	return (context->exit_status);
}

