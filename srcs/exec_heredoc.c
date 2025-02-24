/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:42:52 by yehara            #+#    #+#             */
/*   Updated: 2025/02/13 21:18:41 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <invoke_commands.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <utils.h>

bool	is_heredoc(char *argv)
{
	if (ft_strncmp(argv, "<<", 3) == 0)
		return (true);
	return (false);
}

char *expand_heredoc(char **line, t_kvs *environ)
{
	size_t	i;
	int		start;
	char *result;

	i = 0;
	start = 0;
	result = ft_strdup("");
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
		{
			i = expand_variable(&result, *line, environ, start, i);
			start = i;
		}
		else
			i++;
	}
	free(*line);
	return (result);
}

static void	heredoc_child_process(char *delimiter, int fds[2], t_kvs *environ)
{
	char	*line;

	wrap_close(fds[IN]);
	line = NULL;
	while (true)
	{
		line = readline("> ");
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter) + 1) == 0)
			break ;
		if (ft_strchr(line, '$'))
			line = expand_heredoc(&line, environ);
		ft_putstr_fd(line, fds[OUT]);
		ft_putstr_fd("\n", fds[OUT]);
		free(line);
	}
	wrap_close(fds[OUT]);
	exit(EXIT_SUCCESS);
}

static bool	heredoc_parent_process(t_node *parsed_tokens, int fds[2], pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	wrap_close(fds[OUT]);
	parsed_tokens->fds[IN] = fds[IN];
	return (EXIT_SUCCESS);
}

static bool	setup_heredoc(t_node *parsed_tokens, int i, t_kvs *environ)
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
		heredoc_child_process(parsed_tokens->argv[i + 1], fds, environ);
	if (heredoc_parent_process(parsed_tokens, fds, pid))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static bool	exec_heredoc(t_node *current, t_kvs *environ)
{
	int	i;

	i = 0;
	while (current->argv[i])
	{
		if (is_heredoc(current->argv[i]))
		{
			if (!(current->argv[i + 1]))
				return (printf("heredoc error\n"), EXIT_FAILURE);
			if (!(setup_heredoc(current, i, environ)))
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
			if (exec_heredoc(current, context->environ) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
