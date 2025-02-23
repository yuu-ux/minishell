#ifndef MINISHELL_H
# define MINISHELL_H

#define SUCCESS 0
#define FAILURE 1

#include <stdbool.h>
#include <libft.h>

typedef struct s_kvs {
    char *key;
    char *value;
} t_kvs;

typedef struct s_context
{
	t_kvs	*environ;
	int		exit_status;
}	t_context;

t_context	*init_context(char *envp[]);

#endif
