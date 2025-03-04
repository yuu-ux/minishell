/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:34:01 by yehara            #+#    #+#             */
/*   Updated: 2025/03/03 21:35:21 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_exit_status(t_context *context, int status)
{
	if (WIFEXITED(status))
		context->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		context->exit_status = (WTERMSIG(status) + EXIT_STATUS_INVALID);
}

void	setting_status(t_context *context)
{
	if (g_sig != 0)
		context->exit_status = EXIT_STATUS_INVALID + g_sig;
	g_sig = 0;
}

uint8_t	setting_exit_status(t_context *context, uint8_t status)
{
	context->exit_status = status;
	return (status);
}

