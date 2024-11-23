#include "test.h"

int main(void)
{
    char **argv = NULL;
    argv[0] = "./prog";
    argv[1] = NULL;

    int fd = open("./test.txt", O_RDONLY);

    pid_t   pid = fork();

    if (pid < 0)
    {
        perror("Failed Precess!");
        printf("%ld\n", (long)errno);
    }

    if (pid == 0)
    {
        dup2(fd, STDOUT_FILENO);
        execve(argv[0], argv, NULL);
    }
    else
    {
        wait(NULL);
    }
    return (0);
}