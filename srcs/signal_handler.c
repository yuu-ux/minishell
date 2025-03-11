/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehara <yehara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:23:41 by yehara            #+#    #+#             */
/*   Updated: 2025/03/02 15:35:39 by yehara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_setting.h"

void	signal_handler(int signum)
{
	g_sig = signum;
}

void	heredoc_parent_sigint_handler(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void	sigint_handler(int signum)
{
	g_sig = signum;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	parent_override_signal_handler(int signum)
{
	if (signum == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (signum == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
}
