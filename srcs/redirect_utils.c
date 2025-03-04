/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:20:24 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/03/04 20:55:52 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_token_type(const char *token)
{
	if (ft_strncmp(token, ">>", 3) == 0)
		return (TOKEN_REDIRECT_APPEND);
	else if (ft_strncmp(token, ">", 2) == 0)
		return (TOKEN_REDIRECT_OUT);
	else if (ft_strncmp(token, "<", 2) == 0)
		return (TOKEN_REDIRECT_IN);
	else if (ft_strncmp(token, "|", 2) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(token, "<<", 3) == 0)
		return (TOKEN_REDIRECT_HEREDOC);
	else
		return (TOKEN_WORD);
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

bool	redirect_in(t_node *parsed_tokens, int i)
{
	int	fd;

	fd = open(parsed_tokens->argv[i + 1], O_RDONLY);
	if (fd == -1)
		return (printf("fd error\n"), false);
	parsed_tokens->fds[IN] = fd;
	return (true);
}

bool	redirect_out(t_node *parsed_tokens, int i)
{
	int	fd;

	fd = open(parsed_tokens->argv[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (printf("fd error\n"), false);
	parsed_tokens->fds[OUT] = fd;
	return (true);
}

bool	redirect_append(t_node *parsed_tokens, int i)
{
	int	fd;

	fd = open(parsed_tokens->argv[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		return (printf("fd error\n"), false);
	parsed_tokens->fds[OUT] = fd;
	return (true);
}
