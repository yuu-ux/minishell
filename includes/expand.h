#ifndef EXPAND_H
#define EXPAND_H

typedef struct {
    char *key;
    char *value;
} kvs;

#include "tokenize.h"

t_token *expand_tokens(t_token **_tokens, kvs *path_list);

// expand_utils
char	*search_env(const char *key, kvs *path_list);
size_t	count_key_len(char *token, int t_index);
size_t	insert_env(char **buffer, char *token, kvs *path_list);

#endif
