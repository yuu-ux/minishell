#include <invoke_commands.h>

int    built_echo()
{
    return (EXIT_SUCCESS);
}

int    built_cd()
{
    return (EXIT_SUCCESS);
}

int    built_pwd()
{
    return (EXIT_SUCCESS);
}

int    built_export()
{
    return (EXIT_SUCCESS);
}

int    built_unset()
{
    return (EXIT_SUCCESS);
}

int    built_env()
{
    return (EXIT_SUCCESS);
}

int    built_exit()
{
    ft_printf("exit\n");
    exit(EXIT_SUCCESS);
}

 int exec_builtin(const t_node *parsed_tokens)
{
    if (!(ft_strncmp(parsed_tokens->argv[0], "echo", 5)))
        return (built_echo());
    else if (!(ft_strncmp(parsed_tokens->argv[0], "cd", 3)))
        return (built_cd());
    else if (!(ft_strncmp(parsed_tokens->argv[0], "pwd", 4)))
        return (built_pwd());
    else if (!(ft_strncmp(parsed_tokens->argv[0], "export", 7)))
        return (built_export());
    else if (!(ft_strncmp(parsed_tokens->argv[0], "unset", 6)))
        return (built_unset());
    else if (!(ft_strncmp(parsed_tokens->argv[0], "env", 4)))
        return (built_env());
    else if (!(ft_strncmp(parsed_tokens->argv[0], "exit", 5)))
        return (built_exit());
    return (EXIT_FAILURE);
}
