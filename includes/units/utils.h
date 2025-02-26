#ifndef UTILS_H
# define UTILS_H

// # include "expand.h"
// # include "invoke_commands.h"

void    free_context(t_context *context);
void	close_redirect_fd(int *fd);
char	**convert_to_envp(t_kvs *environ);
void	free_after_invoke(char **path_list, t_node *parsed_tokens, t_exe_info *info);
void	init_saved_fd(t_exe_info *info);
void	reset_fd(t_exe_info *info);
#endif

