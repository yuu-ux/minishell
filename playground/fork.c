#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../libft/libft.h"

int main(int argc, char **argv) {
    char **PATH = ft_split(getenv("PATH"), ':');
    if (argc == 2)
    {
        for (int i = 0; PATH[i]; i++)
        {
            strlcat(PATH[i], "/", ft_strlen(PATH[i]) + 2);
            strlcat(PATH[i], argv[1], ft_strlen(PATH[i]) + ft_strlen(argv[1]) + 1);
            execve(PATH[i], (char *[]){PATH[i], NULL}, NULL);
        }
    }
    //pid_t pid = fork();
    //if (pid < 0) {
    //    perror("fork failed");
    //    exit(1);
    //} else if (pid == 0) {
    //    // 子プロセスでexecveを使って/bin/lsを実行
    //    char *args[] = {"/bin/ls", NULL};  // 引数の配列
    //    char *envp[] = {"PATH=/bin:/usr/bin", "HOME=/home/user", NULL};  // 環境変数の配列
    //    if (execve("/bin/ls", args, envp) == -1) {
    //        perror("execve failed");
    //        exit(1);
    //    }
    //} else {
    //    // 親プロセスは子プロセスが終了するのを待つ
    //    int status;
    //    if (waitpid(pid, &status, 0) == -1) {
    //        perror("waitpid failed");
    //        exit(1);
    //    }
    //    printf("Child process finished with status: %d\n", WEXITSTATUS(status));
    //}
    return 0;
}

