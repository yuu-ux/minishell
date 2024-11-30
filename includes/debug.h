#ifndef DEBUG_H
#define DEBUG_H

#include "tokenize.h"
#include "invoke_commands.h"

const char *get_token_type_string(t_token_type type);
void	print_node(t_node *head);

#endif
