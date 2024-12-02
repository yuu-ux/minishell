#include <signal_setting.h>
#include <readline/readline.h>

static void	handler(int signum)
{
    (void)signum;
    write(STDOUT_FILENO, "\n", 1); // 改行
    rl_replace_line("", 0);       // 入力中の行をクリア
    rl_on_new_line();             // 新しい行を設定
    rl_redisplay();               // プロンプトを再描画
}
void    signal_setting()
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

