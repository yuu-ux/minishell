#include <tokenize.h>

int ft_isspace(int c)
{
    return ('\t' == c || '\n' == c || '\v' == c
            || '\f' == c || '\r' == c || ' ' == c);
}
int is_operators(int c)
{
    return ('|' == c || c == '<' || c == '>');
}

int is_quote(int c)
{
    return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}
