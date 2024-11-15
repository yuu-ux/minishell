#include "tokenize.h"
#include "libft.h"

int main(int argc, char **argv)
{
    t_token *result;

    if (1 < argc)
    {
        result = tokenization(argv[1]);
        while (result)
        {
            printf("%s\n", result->data);
            result = result->next;
        }
    }
}
