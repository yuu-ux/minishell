#ifndef BUILTIN_H
#define BUILTIN_H
#include <invoke_commands.h>
#include <minishell.h>

// built_func
bool	built_echo(const t_node *parsed_tokens);
bool	built_cd(const t_node *parsed_tokens, t_context *context);
bool	built_pwd();
bool	built_export(const	t_node *parsed_tokens, t_context *context);
bool	built_unset(const	t_node *parsed_tokens, t_context *context);
bool	built_env(t_context *context);
bool	built_exit();

// builtin_utils.c
kvs	*xgetenv(const char *name, t_context *context);
int	xsetenv(char *name, char *value, t_context *context);
int	count_environ(kvs *environ);
void	xaddenv(char *name, char *value, t_context *context);
#endif
