#include <debug.h>
#include <invoke_commands.h>
#include <signal_setting.h>

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

int	exec_cmd(t_node *parsed_tokens, char **path)
{
	int		i;
	char	*temp;
	char	*res;

	if (fork() == -1)
		perror("error\n");
	// TODO ビルトイン 作成
	// exec_builtin(parsed_tokens);
	if (parsed_tokens->argv[0][0] == '/')
	{
		// 絶対パス
		while (parsed_tokens)
		{
			if (access(parsed_tokens->argv[0], F_OK) == 0)
				execve(parsed_tokens->argv[0], parsed_tokens->argv, NULL);
			parsed_tokens = parsed_tokens->next;
		}
	}
	else
	{
		// 相対パスで渡されたパターン
		while (parsed_tokens)
		{
			i = 0;
			while (path[i])
			{
				temp = ft_strjoin(path[i], "/");
				res = ft_strjoin(temp, parsed_tokens->argv[0]);
				if (access(res, F_OK) == 0)
					execve(res, parsed_tokens->argv, NULL);
				i++;
			}
			parsed_tokens = parsed_tokens->next;
		}
	}
	return (1);
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
	signal_setting();
	exec_cmd(parsed_tokens, path);
}
