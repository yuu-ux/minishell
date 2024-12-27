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

typedef struct s_node
{
    int fds[2];
    t_node_type	    kind; // CMD:0 PIPE:1
    char			**argv;
    struct s_node	*next;
    struct s_node	*prev;
}	t_node;

// invoke_commands.c
void    invoke_commands(t_token *tokens);
t_node *parse(t_token *tokens);

// invoke_utils.c
char	**get_path(char *path);
size_t	count_pipe(t_node *parsed);
int    initialize_node(t_exe_info *info, t_node *parsed_tokens);
void wrap_close(int fd);
void wrap_dup2(int old_fd, int new_fd);

#endif
