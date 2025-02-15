#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define IN 0
#define OUT 1

bool	is_heredoc(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
			return (true);
		i++;
	}
	return (false);
}

void	wrap_close(int fd)
{
	if (close(fd) == -1)
		exit(EXIT_FAILURE);
}

void	wrap_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		exit(EXIT_FAILURE);
}

void	child_process(int fds[2])
{
	char	*temp;

	wrap_close(fds[IN]);
	while (true)
	{
		temp = readline("> ");
		if (strncmp(temp, "EOF", 4) == 0)
		{
			free(temp);
			break ;
		}
		write(fds[OUT], temp, strlen(temp));
		write(fds[OUT], "\n", 1);
		free(temp);
	}
	wrap_close(fds[OUT]);
}

int	parent_process(pid_t pid, int fds[2])
{
	int	status;

	waitpid(pid, &status, 0);
	wrap_close(fds[OUT]);
	return (fds[IN]);
}

int	exec_heredoc(void)
{
	int		fds[2];
	pid_t	pid;
	int		in;

	in = -1;
	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		child_process(fds);
	if (pid > 0)
		in = parent_process(pid, fds);
	return (in);
}

void	execuve(int in)
{
	int		status;
	pid_t	pid;
	char	**argv;

	argv = (char **)malloc(sizeof(char *) * 2);
	argv[0] = strdup("/bin/cat");
	argv[1] = NULL;
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		wrap_dup2(in, STDIN_FILENO);
		wrap_close(in);
		execve("/bin/cat", argv, NULL);
	}
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		wrap_close(in);
	}
	free(argv);
}

int	main(void)
{
	char	*line;
	int		in;

	while (true)
	{
		line = readline("mish: ");
		if (is_heredoc(line))
		{
			in = exec_heredoc();
			execuve(in);
		}
		add_history(line);
		free(line);
	}
}
