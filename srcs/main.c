/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:04:57 by yehara            #+#    #+#             */
/*   Updated: 2025/02/16 20:49:17 by yehara           ###   ########.fr       */
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

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_context	*context;
	t_token		*tokens;

	line = NULL;
	(void)argc;
	(void)argv;
	context = init_context(envp);
	signal_setting();
	while (true)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			ft_printf("exit\n");
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
	all_free(context->environ, NULL, NULL);
	return (SUCCESS);
}

