#ifndef EXPAND_H
#define EXPAND_H


#include <minishell.h>
#include "tokenize.h"

t_token *expand_tokens(t_token **_tokens, t_context *context);

// expand_utils
char	*search_env(const char *key, kvs *environ);
size_t	count_key_len(char *token, int t_index);
size_t	insert_env(char **buffer, char *token, kvs *environ);

#endif
