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

void	signal_setting(void)
{
	// t_sigaction	sa_sigint;
	// t_sigaction	sa_sigquit;

	// ft_memset(&sa_sigint, 0, sizeof(t_sigaction));
	// ft_memset(&sa_sigquit, 0, sizeof(t_sigaction));
	// sa_sigint.sa_handler = sigint_handler;
	// sa_sigquit.sa_handler = SIG_IGN;
	// sigemptyset(&sa_sigint.sa_mask);
	// sigemptyset(&sa_sigquit.sa_mask);
	// sigaction(SIGINT, &sa_sigint, NULL);
	// sigaction(SIGQUIT, &sa_sigquit, NULL);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	test(int signum __attribute__((unused)))
{
	ft_putnbr_fd(signum, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	pear_signal_setting(void)
{
	signal(SIGINT, test);
}

