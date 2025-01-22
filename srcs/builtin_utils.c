#include <invoke_commands.h>

bool    is_builtin(const t_node *parsed_tokens)
{
    if (!(ft_strncmp(parsed_tokens->argv[0], "echo", 5))
        || !(ft_strncmp(parsed_tokens->argv[0], "cd", 3))
        || !(ft_strncmp(parsed_tokens->argv[0], "pwd", 4))
        || !(ft_strncmp(parsed_tokens->argv[0], "export", 7))
        || !(ft_strncmp(parsed_tokens->argv[0], "unset", 6))
        || !(ft_strncmp(parsed_tokens->argv[0], "env", 4))
        || !(ft_strncmp(parsed_tokens->argv[0], "exit", 5))
        )
        return (true);
    return (false);
}
