#ifndef LEXER_H
# define LEXER_H

#define DOUBLE_QUOTE '\"'
#define SINGLE_QUOTE '\''
#define SYNTAX_ERROR 1

#include <libft.h>
typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_EOF,
    TOKEN_UNKNOWN,
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

t_token    *tokenization(const char *line);
void    check_syntax(t_token *token);

// utils
int ft_isspace(int c);
int is_operators(int c);
int is_quote(int c);

// tokenize_utils
size_t	skip_quoted_token(char quote_char, const char **line);
size_t	skip_while(int (*is_skip)(int), const char **line);
size_t	skip_non_delimiter(const char **line);
t_token	*new_token(const char *line, t_token_type type);

// debug
const char *get_token_type_string(t_token_type type);
#endif
