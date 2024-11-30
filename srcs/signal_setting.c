#include "signal_setting.h"

static void	handler(int signum)
{
    (void)signum;
    write(STDOUT_FILENO, "\nminishell$", 11);
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
