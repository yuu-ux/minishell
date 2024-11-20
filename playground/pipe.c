#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void change_stream(int i, int argc, int *pipefd, int prev_fd)
{
    if (i != 1)
    {
        dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
    }
    if (i + 1 != argc)
    {
        dup2(pipefd[1], STDOUT_FILENO);
    }
    close(pipefd[0]);
    close(pipefd[1]);
}

void update_prev_fd(int i, int argc, int *pipefd, int *prev_fd)
{
    if (i != 1)
    {
        close(*prev_fd);
    }
    if (i + 1 != argc)
    {
        *prev_fd = pipefd[0];
        close(pipefd[1]);
    }
    else
    {
        close(pipefd[0]);
        close(pipefd[1]);
    }
}

void exec_cmd(char *cmd)
{
    char *args[4];  // コマンドと引数用の配列
    int arg_count = 0;

    // スペースで分割して配列に格納
    char *token = strtok(cmd, " ");
    while (token != NULL && arg_count < 3)
    {
        args[arg_count++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL;  // 配列の最後をNULLで終端

    execvp(args[0], args);
    perror("execvp failed");
    _exit(1);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s command1 command2 ...\n", argv[0]);
        return 1;
    }

    int i = 0;
    pid_t pid;
    int pipefd[2];
    int prev_fd = -1;

    while (++i < argc)
    {
        if (pipe(pipefd) == -1)
        {
            perror("pipe failed");
            return 1;
        }

        pid = fork();
        if (pid == 0)
        {
            change_stream(i, argc, pipefd, prev_fd);
            // コマンドの文字列をコピーして処理（元の文字列を変更しないため）
            char *cmd_copy = strdup(argv[i]);
            if (cmd_copy == NULL)
            {
                perror("strdup failed");
                _exit(1);
            }
            exec_cmd(cmd_copy);
            free(cmd_copy);  // 実際にはここには到達しない
        }
        else if (pid > 0)
        {
            update_prev_fd(i, argc, pipefd, &prev_fd);
        }
        else
        {
            perror("fork failed");
            return 1;
        }
    }

    while (wait(NULL) > 0);

    return 0;
}
