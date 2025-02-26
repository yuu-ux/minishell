#include <readline/readline.h>
#include <signal_setting.h>

static void	sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1); // 改行
	rl_replace_line("", 0);        // 入力中の行をクリア
	rl_on_new_line();              // 新しい行を設定
	rl_redisplay();                // プロンプトを再描画
}

void	signal_setting(void)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	ft_memset(&sa_sigint, 0, sizeof(struct sigaction));
	ft_memset(&sa_sigquit, 0, sizeof(struct sigaction));
	sa_sigint.sa_handler = sigint_handler;
	sa_sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sa_sigint.sa_mask);
	sigemptyset(&sa_sigquit.sa_mask);
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

