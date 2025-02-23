#ifndef UTILS_H
# define UTILS_H

#include <expand.h>
#include <invoke_commands.h>
void    env_free(t_kvs *environ);
void	close_redirect_fd(int *fd);
char	**convert_to_envp(t_kvs *environ);
void	free_after_invoke(char **path_list, t_node *parsed_tokens, t_exe_info *info);
#endif

