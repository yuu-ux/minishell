#ifndef EXPAND_H
#define EXPAND_H

typedef struct {
    char *key;
    char *value;
} kvs;

#include "tokenize.h"

t_token *expand_tokens(t_token **_tokens, kvs *path_list);
#endif
