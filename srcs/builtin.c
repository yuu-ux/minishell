#include <invoke_commands.h>
#include <builtin.h>
#include <minishell.h>

int    built_exit()
{
    ft_printf("exit\n");
    exit(EXIT_SUCCESS);
}

 int exec_builtin(const t_node *parsed_tokens, t_context *context)
{
	if (!(ft_strncmp(parsed_tokens->argv[0], "echo", 5)))
		return (built_echo(parsed_tokens));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "cd", 3)))
		return (built_cd(parsed_tokens, context));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "pwd", 4)))
		return (built_pwd());
	else if (!(ft_strncmp(parsed_tokens->argv[0], "export", 7)))
		return (built_export(parsed_tokens, context));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "unset", 6)))
		return (built_unset(parsed_tokens, context));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "env", 4)))
		return (built_env(context));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "exit", 5)))
		return (built_exit());
	return (EXIT_FAILURE);
}
