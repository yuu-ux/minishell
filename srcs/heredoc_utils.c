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

#include "signal_setting.h"

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

char *expand_heredoc(char **line, t_context *context)
{
	size_t	i;
	int		start;
	char *result;
	t_expand expand;

	expand.context = context;
	expand.token = *line;
	i = 0;
	start = 0;
	result = ft_strdup("");
	while (expand.token[i])
	{
		if (expand.token[i] == '$')
		{
			i = expand_variable(&result, expand, start, i);
			start = i;
		}
		else
			i++;
	}
	free(expand.token);
	return (result);
}
