/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:04:57 by yehara            #+#    #+#             */
/*   Updated: 2025/02/27 19:03:34 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)), char *envp[])
{
	char		*line;
	t_context	*context;
	t_token		*tokens;

	line = NULL;
	context = init_context(envp);
	signal_setting();
	while (true)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		else if (*line == '\0')
			continue ;
		tokens = tokenization(line);
		check_syntax(tokens);
		tokens = expand_tokens(&tokens, context);
		invoke_commands(tokens, context);
		add_history(line);
		free(line);
	}
	free_context(context);
	return (SUCCESS);
}

