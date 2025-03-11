/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:53:37 by yehara            #+#    #+#             */
/*   Updated: 2025/03/04 20:54:06 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

int	is_operators(int c)
{
	return ('|' == c || c == '<' || c == '>');
}

int	is_quote(int c)
{
	return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

bool	is_pipe(char *str)
{
	if (ft_strncmp(str, "|", 2) == 0)
		return (true);
	return (false);
}

bool	is_redirect(char *str)
{
	if (ft_strncmp(str, ">", 2) == 0 || ft_strncmp(str, "<", 2) == 0
		|| ft_strncmp(str, ">>", 3) == 0)
		return (true);
	return (false);
}

bool	is_absolute(char *argv)
{
	return (ft_strncmp(argv, "./", 2) == 0);
}
