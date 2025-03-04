/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:11:09 by yehara            #+#    #+#             */
/*   Updated: 2025/02/26 18:20:21 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	redirect_in(t_node *parsed_tokens, int i)
{
	int	fd;

	fd = open(parsed_tokens->argv[i + 1], O_RDONLY);
	if (fd == -1)
		return (printf("fd error\n"), false);
	parsed_tokens->fds[PIPE_OUT] = fd;
	return (true);
}

bool	redirect_out(t_node *parsed_tokens, int i)
{
	int	fd;

	fd = open(parsed_tokens->argv[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (printf("fd error\n"), false);
	parsed_tokens->fds[PIPE_IN] = fd;
	return (true);
}

bool	redirect_append(t_node *parsed_tokens, int i)
{
	int	fd;

	fd = open(parsed_tokens->argv[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		return (printf("fd error\n"), false);
	parsed_tokens->fds[PIPE_IN] = fd;
	return (true);
}

static	bool set_redirect(t_node *parsed_tokens, int i)
{
	t_token_type type;

	type = get_token_type(parsed_tokens->argv[i]);
	if (type == TOKEN_REDIRECT_IN)
		return (redirect_in(parsed_tokens, i));
	else if (type == TOKEN_REDIRECT_OUT)
		return (redirect_out(parsed_tokens, i));
	else if (type == TOKEN_REDIRECT_APPEND)
		return (redirect_append(parsed_tokens, i));
	else if (type == TOKEN_REDIRECT_HEREDOC)
		return (true);
	return (false);
}

static bool	find_set_redirect(t_node *parsed_tokens)
{
	int	i;

	i = 0;
	while (parsed_tokens->argv[i])
	{
		if (is_redirect(parsed_tokens->argv[i]) || is_heredoc(parsed_tokens->argv[i]))
		{
			if (set_redirect(parsed_tokens, i))
				return (true);
			i++;
		}
		i++;
	}
	return (false);
}

int	count_argv_cmd(char **argv)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (argv[i])
	{
		if (is_redirect(argv[i]) || is_heredoc(argv[i]))
		{
			i += 2;
			continue ;
		}
		count++;
		i++;
	}
	return (count);
}

char	**remove_redirect(t_node *parsed_tokens)
{
	char **new_argv;
	int	i;
	int	j;

	i = 0;
	j = 0;
	new_argv = (char **)ft_xmalloc(sizeof(char *) * (count_argv_cmd(parsed_tokens->argv) + 1));
	while (parsed_tokens->argv[i])
	{
		if (is_redirect(parsed_tokens->argv[i]) || is_heredoc(parsed_tokens->argv[i]))
		{
			free(parsed_tokens->argv[i]);
			free(parsed_tokens->argv[i+1]);
			i += 2; // リダイレクトとファイル名までとばしたいため +2
			continue ;
		}
		new_argv[j] = ft_strdup(parsed_tokens->argv[i]);
		free(parsed_tokens->argv[i]);
		j++;
		i++;
	}
	free(parsed_tokens->argv);
	return (new_argv);
}

bool	do_redirections(t_node *parsed_tokens)
{
	char **new_argv;

	if (!(find_set_redirect(parsed_tokens)))
		return (true);
	new_argv = remove_redirect(parsed_tokens);
	if (!new_argv)
		return (false);
	//TODO free
	parsed_tokens->argv = new_argv;
	return (true);
}

