/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:42:52 by yehara            #+#    #+#             */
/*   Updated: 2025/03/03 17:02:27 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "invoke_commands.h"
#include "signal_setting.h"
#include "utils.h"

static unsigned char	heredoc_child_process(char *delimiter, int fds[2],
		t_context *context)
{
	char	*line;

	heredoc_child_signal_setting();
	rl_event_hook = here_document_rl_event_hook;
	wrap_close(fds[IN]);
	while (true)
	{
		line = readline("> ");
		if (line == NULL)
			heredoc_print_error_message(delimiter);
		if (g_sig == SIGINT)
		{
			rl_done = 0;
			wrap_close(fds[OUT]);
			return (free(line), EXIT_STATUS_INVALID + SIGINT);
		}
		if (line == NULL || ft_strncmp(delimiter, line, ft_strlen(delimiter)
				+ 1) == 0)
			break ;
		if (ft_strchr(line, '$') && context->flg_heredoc_expand)
			line = expand_heredoc(&line, context);
		print_line(&line, fds);
	}
	return (wrap_close(fds[OUT]), EXIT_SUCCESS);
}

static bool	heredoc_parent_process(t_node *parsed_tokens, int fds[2], pid_t pid,
		t_context *context)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == (EXIT_STATUS_INVALID + SIGINT))
	{
		catch_exit_status(context, status);
		wrap_close(fds[IN]);
		wrap_close(fds[OUT]);
		return (EXIT_FAILURE);
	}
	wrap_close(fds[OUT]);
	parsed_tokens->fds[IN] = fds[IN];
	context->flg_heredoc_expand = true;
	return (EXIT_SUCCESS);
}

static bool	setup_heredoc(t_node *parsed_tokens, t_context *context,
		char **path_list, t_exe_info *info)
{
	int				fds[2];
	pid_t			pid;
	unsigned char	child_exit_status;

	if (pipe(fds) == -1)
	{
		print_err("pipe error\n");
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		return (wrap_close(fds[IN]), wrap_close(fds[OUT]),
			print_err("fork error\n"), EXIT_FAILURE);
	if (pid == 0)
	{
		child_exit_status = heredoc_child_process(info->heredoc_delimiter, fds,
				context);
		free_after_invoke(path_list, parsed_tokens, info);
		free_environ(context);
		exit(child_exit_status);
	}
	if (heredoc_parent_process(parsed_tokens, fds, pid,
			context) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static bool	exec_heredoc(t_node *current, char **path_list, t_context *context,
		t_exe_info *info)
{
	int	i;

	i = 0;
	while (current->argv[i])
	{
		if (is_heredoc(current->argv[i]))
		{
			info->heredoc_delimiter = current->argv[i + 1];
			if (setup_heredoc(current, context, path_list,
					info) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

bool	process_heredoc(t_node *parsed_tokens, char **path_list,
		t_context *context, t_exe_info *info)
{
	t_node	*current;

	current = parsed_tokens;
	while (current)
	{
		if (current->kind == CMD)
		{
			if (exec_heredoc(current, path_list, context, info) == EXIT_FAILURE
				|| (current->prev == NULL && is_heredoc(current->argv[0])))
			{
				close_redirect_fd(&parsed_tokens->fds[IN]);
				return (EXIT_FAILURE);
			}
		}
		current = current->next;
	}
	rl_event_hook = NULL;
	return (EXIT_SUCCESS);
}
