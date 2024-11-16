#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
	char **env;

	extern char **environ;
	int	i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
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

    //return 0;
}

