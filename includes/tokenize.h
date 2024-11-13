#ifndef LEXER_H
# define LEXER_H

#define DOUBLE_QUOTE '\"'
#define SINGLE_QUOTE '\''

typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_EOF,
    TOKEN_UNKOWN,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_REDIRECT_APPEND,
    TOKEN_REDIRECT_HEREDOC,
} t_token_type;

typedef struct s_token t_token;
struct s_token {
    char            *data;
    t_token         *next;
    t_token_type    type;
};

t_token    *tokenization(char *line);
#endif
