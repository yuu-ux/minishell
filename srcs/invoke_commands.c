#include <debug.h>
#include <invoke_commands.h>

// int exec_builtin(t_node *parsed_tokens)
//{
//    if (ft_strncmp(parsed_tokens->argv[0], "echo", 5))
//        built_echo();
//    else if (ft_strncmp(parsed_tokens->argv[0], "cd", 3))
//        built_cd();
//    else if (ft_strncmp(parsed_tokens->argv[0], "pwd", 4))
//        built_pwd();
//    else if (ft_strncmp(parsed_tokens->argv[0], "export", 7))
//        built_export();
//    else if (ft_strncmp(parsed_tokens->argv[0], "unset", 6))
//        built_unset();
//    else if (ft_strncmp(parsed_tokens->argv[0], "env", 4))
//        built_env();
//    else if (ft_strncmp(parsed_tokens->argv[0], "exit", 5))
//        built_exit();
//    else
//        return (1);
//}

static size_t	count_pipe(t_node *parsed)
{
	size_t	count;

	count = 0;
	while (parsed)
	{
		if (parsed->kind == PIPE)
			count++;
		parsed = parsed->next;
	}
	return (count);
}

static void	free_pipe(int **pipefds, int index)
{
	while (0 < index)
	{
		free(pipefds[index]);
		index--;
	}
}

static int	create_pipe(int ***pipefds, t_node *parsed_tokens)
{
	int	pipe_num;
	int	i;

	i = 0;
	pipe_num = count_pipe(parsed_tokens);
	*pipefds = (int **)malloc(pipe_num * sizeof(int *));
	while (i < pipe_num)
	{
		*pipefds[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(*pipefds[i]) == -1)
		{
			free_pipe(*pipefds, i);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
static int	exec_single_cmd(const t_node *parsed_tokens, char **path)
{
	int		i;
	char	*temp;
	char	*res;
	pid_t	pid;

	// TODO ビルトイン 作成
	// exec_builtin(parsed_tokens);
	pid = fork();
	if (pid == -1)
		perror("error\n");
	if (pid == 0)
	{
		if (parsed_tokens->argv[0][0] == '/')
		{
			if (access(parsed_tokens->argv[0], F_OK) == 0)
				execve(parsed_tokens->argv[0], parsed_tokens->argv, NULL);
		}
		else
		{
			i = 0;
			while (path[i])
			{
				temp = ft_strjoin(path[i], "/");
				res = ft_strjoin(temp, parsed_tokens->argv[0]);
				if (access(res, F_OK) == 0)
				{
					execve(res, parsed_tokens->argv, NULL);
					break ;
				}
				i++;
			}
		}
	}
	else
		waitpid(pid, NULL, 0);
	return (EXIT_FAILURE);
}

int	exec_cmd(t_node *parsed_tokens, char **path)
{
	int	**pipefds;

	exec_single_cmd(parsed_tokens, path);
	if (create_pipe(&pipefds, parsed_tokens) == -1)
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}

char	**get_path(char *path)
{
	char	**result;

	result = ft_split(path, ':');
	return (result);
}

void	invoke_commands(t_token *tokens)
{
	t_node	*parsed_tokens;
	char	**path;

	path = get_path(getenv("PATH"));
	parsed_tokens = parse(tokens);
	exec_cmd(parsed_tokens, path);
}
