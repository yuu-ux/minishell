#include "tokenize.h"

const char *get_token_type_string(t_token_type type)
{
    switch (type) {
        case TOKEN_WORD: return "TOKEN_WORD";
        case TOKEN_EOF: return "TOKEN_EOF";
        case TOKEN_UNKNOWN: return "TOKEN_UNKNOWN";
        case TOKEN_PIPE: return "TOKEN_PIPE";
        case TOKEN_REDIRECT_IN: return "TOKEN_REDIRECT_IN";
        case TOKEN_REDIRECT_OUT: return "TOKEN_REDIRECT_OUT";
        case TOKEN_REDIRECT_APPEND: return "TOKEN_REDIRECT_APPEND";
        case TOKEN_REDIRECT_HEREDOC: return "TOKEN_REDIRECT_HEREDOC";
        default: return "UNKNOWN_TYPE";
    }
}
