/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:04:57 by yehara            #+#    #+#             */
/*   Updated: 2025/03/01 15:33:24 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	signal_setting(t_context *context)
{
	parent_signal_setting();
	if (g_sig != 0)
		context->exit_status = 128 + g_sig;
	g_sig = 0;
}

bool	is_space_while(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\0')
		return (true);
	while (line[i])
	{
		if (ft_isspace(line[i]) == false)
			return (false);
		i++;
	}
	add_history(line);
	return (true);
}

bool	preprocess_line(char *line, t_context *context, t_token **tokens)
{
	if (line == NULL)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (is_space_while(line))
		return (EXIT_SUCCESS);
	*tokens = tokenization(line);
	if (check_syntax(*tokens) == EXIT_FAILURE)
	{
		free_tokens(tokens);
		return (EXIT_SUCCESS);
	}
	*tokens = expand_tokens(tokens, context);
	return (EXIT_SUCCESS);
}

void	shell_loop(t_context *context)
{
	char		*line;
	t_token		*tokens;

	line = NULL;
	while (true)
	{
		signal_setting(context);
		line = readline("minishell$ ");
		tokens = NULL;
		if (preprocess_line(line, context, &tokens) == EXIT_FAILURE)
			break ;
		if (tokens == NULL)
			continue ;
		invoke_commands(tokens, context);
		add_history(line);
		free(line);
	}
}

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)), char *envp[])
{
	t_context	context;

	context = init_context(envp);
	shell_loop(&context);
	rl_clear_history();
	free_context(&context);
	return (context.exit_status);
}
