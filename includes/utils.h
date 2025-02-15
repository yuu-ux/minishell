#ifndef UTILS_H
# define UTILS_H

#include <expand.h>
#include <invoke_commands.h>
void    all_free(kvs *env_list, char **path_list, t_node *parsed_tokens);
void    wrap_double_close(int fd1, int fd2);
void	close_redirect_fd(int *fd);
#endif

