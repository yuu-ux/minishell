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

void	setting_status(t_context *context)
{
	if (g_sig != 0)
		context->exit_status = 128 + g_sig;
	g_sig = 0;
}

bool	setting_exit_status(t_context *context, int status)
{
	context->exit_status = status;
	return (status);
}
