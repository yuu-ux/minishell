#ifndef BUILTIN_H
#define BUILTIN_H
#include <invoke_commands.h>
#include <minishell.h>

bool	built_echo(const t_node *parsed_tokens);
bool	built_cd(const t_node *parsed_tokens, t_context *context);
bool	built_pwd();
bool	built_export(const	t_node *parsed_tokens, t_context *context);
bool	built_unset(const	t_node *parsed_tokens, t_context *context);
#endif
