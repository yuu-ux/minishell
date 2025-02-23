#ifndef UTILS_H
# define UTILS_H

#include <expand.h>
#include <invoke_commands.h>
void    all_free(kvs *environ, char **path_list, t_node *parsed_tokens);
void	close_redirect_fd(int *fd);
char	**convert_to_envp(kvs *environ);
#endif

