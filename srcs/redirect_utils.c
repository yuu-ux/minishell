/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:20:24 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/02/26 18:21:39 by hana/hmori       ###   ########.fr       */
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
