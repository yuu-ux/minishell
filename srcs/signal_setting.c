/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:33:54 by hana/hmori        #+#    #+#             */
/*   Updated: 2025/03/01 13:48:42 by hana/hmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int signum __attribute__((unused)))
{
	ft_putchar_fd('\n', STDOUT_FILENO); // 改行
	rl_replace_line("", 0);        // 入力中の行をクリア
	rl_on_new_line();              // 新しい行を設定
	rl_redisplay();                // プロンプトを再描画
}

void	parent_signal_setting(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	heredoc_parent_sigint_handler(int signum)
{
	if (signum == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (signum == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
}

void	parent_override_signal_setting(void)
{
	signal(SIGINT, heredoc_parent_sigint_handler);
	signal(SIGQUIT, heredoc_parent_sigint_handler);
}

void	child_override_signal_setting(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
