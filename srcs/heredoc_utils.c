/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 22:03:21 by yehara            #+#    #+#             */
/*   Updated: 2025/03/01 22:04:53 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "expand.h"
#include "invoke_commands.h"
#include "signal_setting.h"

void	heredoc_print_error_message(char *delimiter)
{
	print_err("minishell: ");
	print_err("warning: here-document delimited by end-of-file (wanted `");
	print_err(delimiter);
	print_err("')\n");
}

void	print_line(char **line, int fds[2])
{
	ft_putstr_fd(*line, fds[OUT]);
	ft_putstr_fd("\n", fds[OUT]);
	free(*line);
}

int	here_document_rl_event_hook(void)
{
	if (g_sig == SIGINT)
		rl_done = 1;
	return (EXIT_SUCCESS);
}

bool	is_heredoc(char *argv)
{
	if (ft_strncmp(argv, "<<", 3) == 0)
		return (true);
	return (false);
}

char	*expand_heredoc(char **line, t_context *context)
{
	char		*result;
	t_expand	expand;

	expand.context = context;
	expand.token = *line;
	expand.index = 0;
	expand.start = 0;
	result = ft_strdup("");
	while (expand.token[expand.index])
	{
		if (expand.token[expand.index] == '$')
		{
			expand.index = expand_variable(&result, expand);
			expand.start = expand.index;
		}
		else
			expand.index++;
	}
	free(expand.token);
	return (result);
}
