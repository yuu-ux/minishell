/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:33:54 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/03/02 15:26:02 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_signal_setting(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	parent_override_signal_setting(void)
{
	signal(SIGINT, parent_override_signal_handler);
	signal(SIGQUIT, parent_override_signal_handler);
}

void	child_signal_setting(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	heredoc_parent_signal_setting(void)
{
	signal(SIGINT, heredoc_parent_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_child_signal_setting(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
