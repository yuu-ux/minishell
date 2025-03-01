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

#include "minishell.h"

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

	i = 0;
	start = 0;
	result = ft_strdup("");
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
		{
			i = expand_variable(&result, *line, context, start, i);
			start = i;
		}
		else
			i++;
	}
	free(*line);
	return (result);
}
