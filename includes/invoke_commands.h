#ifndef INVOKE_COMMANDS_H
#define INVOKE_COMMANDS_H

#include <tokenize.h>
#include <unistd.h>
#include <fcntl.h>
#include <libft.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <minishell.h>

typedef struct s_exe_info {
    pid_t   *pid;
    int pipe_num;
    int exec_count;
    int				before_cmd_fd;
} t_exe_info;

typedef enum e_node_type {
    CMD,
    PIPE,
} t_node_type;

typedef enum e_std_fd {
    IN,
    OUT,
    ERR,
    INVALID_FD = -1,
} t_std_fd;

typedef struct s_node {
    int fds[2];
    t_node_type	    kind; // CMD:0 PIPE:1
    char			**argv;
    struct s_node	*next;
    struct s_node	*prev;
}	t_node;

// invoke_commands.c
void    invoke_commands(t_token *tokens, t_context *context);
t_node *parse(t_token *tokens);

// invoke_utils.c
char	**get_path_list(char *env_path);
size_t	count_pipe(t_node *parsed);
int    initialize_info(t_exe_info *info, t_node *parsed_tokens);
void wrap_close(int fd);
void wrap_dup2(int old_fd, int new_fd);
int execute(t_node *parsed_tokens, char **path_list, t_context *context);

// execute.c
char *find_executable_path(const t_node *parsed_tokens, char **path_list);
int child_process(t_node *parsed_tokens, t_exe_info *info, char **path_list, t_context *context);
int parent_process(t_node *parsed_tokens, t_exe_info *info);

// builtin.c
int exec_builtin(const t_node *parsed_tokens, t_context *context);

// builtin_utils.c
bool is_builtin(const t_node *parsed_tokens);

// exec_heredoc.c
bool    is_heredoc(char *argv);
bool    process_heredoc(t_node *parsed_tokens, t_context *context);


#endif
