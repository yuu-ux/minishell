#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int pipefd[2];
    pid_t   pid1;
    pid_t   pid2;
    char *argv[2] = {"/bin/ls", NULL};
    char *argv2[3] = {"/usr/bin/grep", "a.out", NULL};

    // パイプの作成
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // プロセスの複製
    if ((pid1 = fork()) == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // 子プロセスの出力先をパイプの書き込み専用に変更する
    if (pid1 == 0)
    {
        // 使わない方のpipefdは閉じる
        close(pipefd[0]);
        // 標準出力をパイプの書き込みに複製
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execve("/bin/ls", argv, NULL);
        perror("ls");
        exit(EXIT_FAILURE);
    }

    if ((pid2 = fork()) == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execve("/usr/bin/grep", argv2, NULL);
        perror("grep");
        exit(EXIT_FAILURE);
    }

    // 親プロセスのpipefdを閉じる
    close(pipefd[0]);
    close(pipefd[1]);

    // 子プロセスの終了を待つ
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}
