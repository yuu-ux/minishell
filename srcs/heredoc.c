/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:42:52 by yehara            #+#    #+#             */
/*   Updated: 2025/03/03 18:11:04 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	heredoc_child_process(char *delimiter, int fds[2], t_context *context)
{
	char	*line;

	wrap_close(fds[PIPE_OUT]);
	heredoc_child_signal_setting();
	while (true)
	{
		line = readline("> ");
		if (g_sig == SIGINT)
		{
			wrap_close(fds[PIPE_IN]);
			free(line);
			return (EXIT_FAILURE);
		}
		if (line == NULL)
			ft_printf("-minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
		if (line == NULL || ft_strncmp(delimiter, line, ft_strlen(delimiter) + 1) == 0)
			break ;
		if (ft_strchr(line, '$') && context->flg_heredoc_expand)
			line = expand_heredoc(&line, context);
		ft_putstr_fd(line, fds[PIPE_IN]);
		ft_putstr_fd("\n", fds[PIPE_IN]);
		free(line);
	}
	wrap_close(fds[PIPE_IN]);
	return (EXIT_SUCCESS);
}

static bool	heredoc_parent_process(t_node *parsed_tokens, int fds[2], pid_t pid, t_context *context)
{
	int	status;

	wrap_close(fds[PIPE_IN]);
	heredoc_parent_signal_setting();
	waitpid(pid, &status, 0);
	if (context->exit_status)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		wrap_close(fds[PIPE_OUT]);
		return (false);
	}
	// dup2(fds[PIPE_OUT], STDOUT_FILENO);
	parsed_tokens->fds[PIPE_OUT] = fds[PIPE_OUT];
	context->flg_heredoc_expand = true;
	if (status)
		return (false);
	return (true);
}

static bool	setup_heredoc(t_node *parsed_tokens, int i, t_context *context, char **path_list, t_exe_info *info)
{
	int		fds[2];
	pid_t	pid;
	bool	child_exit_st;

	if (pipe(fds) == -1)
	{
		printf("error\n");
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		return (wrap_close(fds[PIPE_OUT]), wrap_close(fds[PIPE_IN]), printf("error\n"),
			EXIT_FAILURE);
	if (pid == 0)
	{
		child_exit_st = heredoc_child_process(parsed_tokens->argv[i + 1], fds, context);
		free_after_invoke(path_list, parsed_tokens, info);
		free_context(context);
		exit(child_exit_st);
	}
	if (heredoc_parent_process(parsed_tokens, fds, pid, context) == false)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static bool	exec_heredoc(t_node *current, char **path_list,
		t_context *context, t_exe_info *info)
{
	int	i;

	i = 0;
	while (current->argv[i])
	{
		if (is_heredoc(current->argv[i]))
		{
			if (setup_heredoc(current, i, context, path_list, info) == EXIT_FAILURE)
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
				close_redirect_fd(&parsed_tokens->fds[PIPE_OUT]);
				return (EXIT_FAILURE);
			}
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
