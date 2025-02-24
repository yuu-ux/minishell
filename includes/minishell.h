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
	bool	flg_heredoc_expand;
}	t_context;

t_context	*init_context(char *envp[]);

#endif
