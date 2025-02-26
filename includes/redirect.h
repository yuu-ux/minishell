#ifndef REDIRECT_H
#define REDIRECT_H

#include <stdbool.h>
#include <invoke_commands.h>

// redirect_utils.c
bool	is_pipe(char *str);
bool	is_redirect(char *str);
t_token_type	get_token_type(char *token);

// redirect.c
bool    do_redirections(t_node *parsed_tokens);

#endif
