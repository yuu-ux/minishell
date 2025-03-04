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

#include "minishell.h"

void	signal_handler(int signum)
{
	g_sig = signum;
}

void	sigint_handler(int signum)
{
	g_sig = signum;
	ft_putchar_fd('\n', STDOUT_FILENO); // 改行
	rl_replace_line("", 0);        // 入力中の行をクリア
	rl_on_new_line();              // 新しい行を設定
	rl_redisplay();                // プロンプトを再描画
}

void	parent_override_signal_handler(int signum)
{
	if (signum == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (signum == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
}

void	heredoc_parent_sigint_handler(int signum)
{
	g_sig = signum;
}
