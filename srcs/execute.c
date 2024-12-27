#include <invoke_commands.h>

char *find_executable_path(const t_node *parsed_tokens, char **path_list)
{
    int		i;
	char	*slash_cmd;
	char	*path;

    i = 0;
    path = NULL;
    slash_cmd = ft_strjoin("/", parsed_tokens->argv[0]);
    while (path_list[i])
    {
        path = ft_strjoin(path_list[i], slash_cmd);
        if (access(path, F_OK) == 0)
        {
            free(slash_cmd);
            return (path);
        }
        i++;
    }
    return (NULL);
}

int execute(t_node *parsed_tokens, char **path_list)
{
    execve(find_executable_path(parsed_tokens, path_list), parsed_tokens->argv, NULL);
    exit(EXIT_FAILURE);
}
