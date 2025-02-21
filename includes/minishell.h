#ifndef MINISHELL_H
# define MINISHELL_H

#define SUCCESS 0
#define FAILURE 1

#include <stdbool.h>

typedef struct {
    char *key;
    char *value;
} kvs;

typedef struct s_context
{
	kvs	*environ;
	char	**envp;
	int		exit_status;
}	t_context;

t_context	*init_context(char *envp[]);

#endif
