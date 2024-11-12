#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type {
    ARG,      // 関数の引数
    VARIABLE, // コマンドラインでの任意の単語やトークン（e.g. PATH, DISPLAY）
    BILTIN,   // 定義したビルトイン関数
    COMMAND,  // ビルトイン以外のコマンド可変長引数でわたす
    OPERATER, // パイプとかリダイレクトとか
} t_token_type;

typedef enum e_token_status {
    NORMAL,
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
} t_token_status;

typedef struct s_token t_token;
struct s_token {
    char            *data;
    t_token         *next;
    t_token_status  status;
    t_token_type    type;
};

t_token    *tokenization(char *line);
#endif
