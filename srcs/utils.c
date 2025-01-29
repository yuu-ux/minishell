#include <tokenize.h>
#include <invoke_commands.h>

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

void    wrap_double_close(int fd1, int fd2)
{
    wrap_close(fd1);
    wrap_close(fd2);
}
