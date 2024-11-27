#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char *argv[2] = {"/bin/ls", NULL};
    extern char **environ;

    int fd2 = open("./playground/output", O_RDWR | O_CREAT);
    if (fd2 == -1)
    {
        perror("fd2");
        return 1;
    }
    dup2(fd2, STDOUT_FILENO);
    close(fd2);
    execve("/bin/ls", argv, environ);
    return 0;
}
