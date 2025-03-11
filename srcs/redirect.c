/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:11:09 by yehara            #+#    #+#             */
/*   Updated: 2025/03/04 20:56:05 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "invoke_commands.h"
#include "redirect.h"
#include "utils.h"

static bool	set_redirect(t_node *parsed_tokens, int i)
{
	t_token_type	type;

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
		if (is_redirect(parsed_tokens->argv[i])
			|| is_heredoc(parsed_tokens->argv[i]))
		{
			if (set_redirect(parsed_tokens, i) == false)
				return (true);
			i++;
		}
		i++;
	}
	return (true);
}

char	**remove_redirect(t_node *parsed_tokens)
{
	char	**new_argv;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_argv = (char **)ft_xmalloc(sizeof(char *)
			* (count_argv_cmd(parsed_tokens->argv) + 1));
	while (parsed_tokens->argv[i])
	{
		if (is_redirect(parsed_tokens->argv[i])
			|| is_heredoc(parsed_tokens->argv[i]))
		{
			free(parsed_tokens->argv[i]);
			free(parsed_tokens->argv[i + 1]);
			i += 2;
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
	char	**new_argv;

	if (!(find_set_redirect(parsed_tokens)))
		return (true);
	new_argv = remove_redirect(parsed_tokens);
	if (!new_argv)
		return (false);
	parsed_tokens->argv = new_argv;
	return (true);
}
