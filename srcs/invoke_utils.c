#include <invoke_commands.h>

char	**get_path(char *path)
{
    char	**result;

    result = ft_split(path, ':');
    return (result);
}

size_t	count_pipe(t_node *parsed)
{
	size_t  count;

	count = 0;
	while (parsed)
	{
		if (parsed->kind == PIPE)
			count++;
		parsed = parsed->next;
	}
	return (count);
}

void wrap_dup2(int old_fd, int new_fd)
{
    if (dup2(old_fd, new_fd) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
}

void wrap_close(int fd)
{
    if (fd != -1 && close(fd) == -1)
    {
        perror("close");
        exit(EXIT_FAILURE);
    }
}

int    initialize_node(t_exe_info *info, t_node *parsed_tokens)
{
    info->pipe_num = count_pipe(parsed_tokens);
    info->exec_count = 0;
    info->before_cmd_fd = INVALID_FD;
    info->pid = (pid_t *)malloc((info->pipe_num + 1) * sizeof(pid_t));
    if (info->pid == NULL)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
