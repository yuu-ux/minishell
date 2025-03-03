/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:42:52 by yehara            #+#    #+#             */
/*   Updated: 2025/03/02 15:23:59 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_child_process(char *delimiter, int fds[2], t_context *context)
{
	char	*line;

	heredoc_child_signal_setting();
	wrap_close(fds[IN]);
	line = NULL;
	while (true)
	{
		line = readline("> ");
		if (g_sig == SIGINT)
		{
			wrap_close(fds[OUT]);
			ft_putchar_fd('\n', STDOUT_FILENO);
			free(line);
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter) + 1) == 0)
			break ;
		if (ft_strchr(line, '$') && context->flg_heredoc_expand)
			line = expand_heredoc(&line, context);
		ft_putstr_fd(line, fds[OUT]);
		ft_putstr_fd("\n", fds[OUT]);
		free(line);
	}
	wrap_close(fds[OUT]);
	exit(EXIT_SUCCESS);
}


static bool	heredoc_parent_process(t_node *parsed_tokens, int fds[2], pid_t pid, t_context *context)
{
	int	status;

	signal(SIGINT, sigint_handler);
	waitpid(pid, &status, 0);
	if (context->exit_status)
	{
		wrap_close(fds[IN]);
		wrap_close(fds[OUT]);
		return (false);
	}
	parsed_tokens->fds[IN] = fds[IN];
	context->flg_heredoc_expand = true;
	if (status)
		return (false);
	return (true);
}

static bool	setup_heredoc(t_node *parsed_tokens, int i, t_context *context)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
	{
		printf("error\n");
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		return (wrap_close(fds[IN]), wrap_close(fds[OUT]), printf("error\n"),
			EXIT_FAILURE);
	if (pid == 0)
		heredoc_child_process(parsed_tokens->argv[i + 1], fds, context);
	if (heredoc_parent_process(parsed_tokens, fds, pid, context) == false)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static bool	exec_heredoc(t_node *current, t_context *context)
{
	int	i;

	i = 0;
	while (current->argv[i])
	{
		if (is_heredoc(current->argv[i]))
		{
			if (setup_heredoc(current, i, context) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

bool	process_heredoc(t_node *parsed_tokens, t_context *context)
{
	t_node	*current;

	current = parsed_tokens;
	while (current)
	{
		if (current->kind == CMD)
		{
			if (exec_heredoc(current, context) == EXIT_FAILURE
				|| (current->prev == NULL && is_heredoc(current->argv[0])))
			{
				close_redirect_fd(&parsed_tokens->fds[IN]);
				return (EXIT_FAILURE);
			}
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
