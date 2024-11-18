#include "tokenize.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void    check_quote_error(t_token *token)
{
    int last_index;

    last_index = ft_strlen(token->data) - 1;
    if (token->data[0] == token->data[last_index])
        return ;
    exit(SYNTAX_ERROR);
}

void    check_operators_error(t_token *token)
{
    if (!token->next)
        exit(SYNTAX_ERROR);
    if (token->next->type != TOKEN_WORD)
        exit(SYNTAX_ERROR);
    if (token->data[0] == '|' && token->data[1] == '|')
        exit(SYNTAX_ERROR);
}

void    check_syntax(t_token *token)
{
    while (token)
    {
        if (is_quote(token->data[0]))
            check_quote_error(token);
        if (is_operators(token->data[0]))
            check_operators_error(token);
        token = token->next;
    }
}

//echo "=== 正常系テスト ==="
//echo "ls -la | grep .txt"
//echo "echo 'hello world'"
//echo 'echo "hello world"'
//echo "cat file | grep pattern | sort"
//
//# クォートエラー
//echo -e "\n=== クォートエラー ==="
//echo "echo "hello world"              # ダブルクォート内にダブルクォート
//echo "hello world                     # 閉じ忘れ
//echo 'hello "world                    # シングルクォート閉じ忘れ
//echo "hello 'world"                   # 異なる種類のクォート
//
//# パイプエラー
//echo -e "\n=== パイプエラー ==="
//echo "ls |"                          # パイプの後に何もない
//echo "ls | | grep test"              # 連続したパイプ
//echo "| ls"                          # パイプで始まる
//echo "ls ||"                         # 無効な二重パイプ
//
//# 追加で考慮すべきケース
//echo -e "\n=== その他のケース ==="
//echo "|"                             # パイプのみ
//echo "''"                            # 空のクォート
//echo '""'                            # 空のダブルクォート
//echo "ls 'file1' 'file2'"           # 複数のクォート
//echo "echo \"hello' world\""         # 混在したクォート
//echo "ls |||"                        # 3連続パイプ
//echo "ls | > file.txt"              # パイプとリダイレクトの組み合わせ
