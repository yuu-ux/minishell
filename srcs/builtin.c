#include <invoke_commands.h>
#include <builtin.h>
#include <minishell.h>

int exec_builtin(t_node *parsed_tokens, char **path_list, t_context *context, t_exe_info *info)
{
	if (!(ft_strncmp(parsed_tokens->argv[0], "echo", 5)))
		return (built_echo(parsed_tokens));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "cd", 3)))
		return (built_cd(parsed_tokens, context));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "pwd", 4)))
		return (built_pwd(context));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "export", 7)))
		return (built_export(parsed_tokens, context));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "unset", 6)))
		return (built_unset(parsed_tokens, context));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "env", 4)))
		return (built_env(context));
	else if (!(ft_strncmp(parsed_tokens->argv[0], "exit", 5)))
		return (built_exit(parsed_tokens, path_list, context, info));
	return (EXIT_FAILURE);
}
