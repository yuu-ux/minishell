#include <unistd.h>
#include <sys/wait.h>

void    exec_cmd(char *argv)
{
    char *option[] = {argv, NULL};
    execve(argv, option, NULL);
}

int main(int argc, char **argv)
{
    int i = 0;
    pid_t   pid;

    while (i++ < argc - 1)
    {
        pid = fork();
        if (pid == 0)
            exec_cmd(argv[i]);
    }
    while (i-- > 0)
        wait(NULL);
}
